/**
 * Copyright (c) William Niemiec.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "../../../../include/wniemiec/task/cpp/Scheduler.hpp"

#include <ctime>
#include <chrono>
#include <thread>

using namespace wniemiec::task::cpp;

std::function<void(void)> null_routine = [](){};

//-------------------------------------------------------------------------
//		Attributes
//-------------------------------------------------------------------------
std::map<unsigned long, bool> Scheduler::delay_routines = std::map<unsigned long, bool>();
std::map<unsigned long, bool> Scheduler::interval_routines = std::map<unsigned long, bool>();
std::map<unsigned long, bool> Scheduler::timeout_routine = std::map<unsigned long, bool>();
std::function<void(void)>& Scheduler::current_routine = null_routine;
unsigned long Scheduler::current_routine_id;
pthread_t Scheduler::control_thread;


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
unsigned long Scheduler::set_timeout(const std::function<void(void)>& routine, long delay)
{
    initialize_routine_id();
    current_routine = routine;

    pthread_t thread;
    pthread_create(&thread, nullptr, delay_control_routine, (void*) delay);

    return current_routine_id;
}

void Scheduler::initialize_routine_id()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    current_routine_id = get_current_time();
}

void* Scheduler::delay_control_routine(void* arg)
{
    long delay = (long) arg;
    unsigned long id = current_routine_id;
    const std::function<void(void)> routine = current_routine;

    if (delay < 0)
        throw std::invalid_argument("Delay cannot be negative");

    delay_routines[id] = true;

    std::this_thread::sleep_for(std::chrono::milliseconds(delay));

    if (delay_routines[id])
        routine();

    return nullptr;
}

void Scheduler::clear_timeout(unsigned long id)
{
    delay_routines[id] = false;
}

unsigned long Scheduler::set_interval(const std::function<void(void)>& routine, long interval)
{
    initialize_routine_id();
    current_routine = routine;

    pthread_t thread;
    pthread_create(&thread, nullptr, interval_control_routine, (void*) interval);

    return current_routine_id;
}

void* Scheduler::interval_control_routine(void* arg)
{
    long interval = (long) arg;
    unsigned long id = current_routine_id;
    const std::function<void(void)> routine = current_routine;

    if (interval < 0)
        throw std::invalid_argument("Interval cannot be negative");

    interval_routines[id] = true;

    while (interval_routines[id])
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        routine();
    }

    return nullptr;
}

void Scheduler::clear_interval(unsigned long id)
{
    interval_routines[id] = false;
}

bool Scheduler::set_timeout_to_routine(const std::function<void(void)>& routine, long timeout)
{
    run_routine(routine);
    wait_routine_for(timeout);
    finish_routine();

    return !has_routine_finished();
}

void Scheduler::run_routine(const std::function<void(void)>& routine)
{
    initialize_routine_id();

    timeout_routine[current_routine_id] = false;
    current_routine = routine;

    pthread_create(&control_thread, nullptr, control_routine, nullptr);
}

time_t Scheduler::get_current_time()
{
    return std::time(nullptr);
}

void* Scheduler::control_routine(void* args)
{
    time_t id = current_routine_id;
    std::function<void(void)>& routine = current_routine;

    routine();
    timeout_routine[id] = true;

    return nullptr;
}

void Scheduler::wait_routine_for(long time)
{
    time_t start = get_current_time();

    while ((time_elapsed_in_milliseconds(start) < (double) time) && !has_routine_finished())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

double Scheduler::time_elapsed_in_milliseconds(time_t start)
{
    return (difftime(get_current_time(), start) * 1000);
}

bool Scheduler::has_routine_finished()
{
    return timeout_routine[current_routine_id];
}

void Scheduler::finish_routine()
{
    pthread_cancel(control_thread);
}

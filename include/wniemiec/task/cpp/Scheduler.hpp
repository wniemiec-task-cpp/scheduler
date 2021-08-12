/**
 * Copyright (c) William Niemiec.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <functional>
#include <pthread.h>
#include <map>

namespace wniemiec { namespace task { namespace cpp {

    /**
     * Responsible for executing routines within time intervals.
     *
     * @author     William Niemiec &lt; williamniemiec@hotmail.com &gt;
     */
    class Scheduler
    {
    //-------------------------------------------------------------------------
    //		Attributes
    //-------------------------------------------------------------------------
    private:
        static std::map<unsigned long, bool> delay_routines;
        static std::map<unsigned long, bool> interval_routines;
        static std::map<unsigned long, bool> timeout_routine;
        static unsigned long current_routine_id;
        static std::function<void(void)>& current_routine;
        static pthread_t control_thread;


    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    private:
        Scheduler();


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        /**
         * Sets a timer which executes a routine once the timer expires.
         *
         * @param       routine Routine to be performed
         * @param       delay Waiting time before the routine is executed (in
         * milliseconds)
         *
         * @return      Routine id, being useful for future cancellation
         */
        static unsigned long set_timeout(const std::function<void(void)>& routine, long delay);

        /**
         * Cancels a timed action which was previously established by a call
         * to {@link Scheduler::set_timeout}.
         *
         * @param       id Routine id
         */
        static void clear_timeout(unsigned long id);

        /**
         * Repeatedly calls a routine with a fixed time delay between each
         * call.
         *
         * @param       routine Routine to be performed
         * @param       interval Interval that the routine will be invoked (in
         * milliseconds)
         *
         * @return      Routine id, being useful for future cancellation
         *
         * @see         Scheduler::clear_interval
         */
        static unsigned long set_interval(const std::function<void(void)>& routine, long interval);

        /**
         * Cancels a timed, repeating action, which was previously established
         * by a call to {@link Scheduler::set_interval}.
         *
         * @param       id Routine identifier
         */
        static void clear_interval(unsigned long id);

        /**
         * Runs a routine within a timeout.
         *
         * @param       routine Routine
         * @param       timeout Maximum execution time (in milliseconds)
         *
         * @return      True if the routine has not finished executing within
         * the time limit; false otherwise
         */
        static bool set_timeout_to_routine(const std::function<void(void)>& routine, long timeout);
    private:
        static void run_routine(const std::function<void(void)>& routine);
        static void initialize_routine_id();
        static time_t get_current_time();
        static void* delay_control_routine(void* arg);
        static void* interval_control_routine(void* args);
        static void* control_routine(void* args);
        static void wait_routine_for(long time);
        static double time_elapsed_in_milliseconds(time_t start);
        static bool has_routine_finished();
        static void finish_routine();
    };
}}}

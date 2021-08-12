![](https://github.com/wniemiec-io-cpp/scheduler/blob/master/docs/img/logo/logo.jpg)

<h1 align='center'>Scheduler</h1>
<p align='center'>Schedule routines to run after a certain time or whenever the the timer expires.</p>
<p align="center">
	<a href="https://github.com/wniemiec-io-cpp/scheduler/actions/workflows/windows.yml"><img src="https://github.com/wniemiec-io-cpp/scheduler/actions/workflows/windows.yml/badge.svg" alt=""></a>
	<a href="https://github.com/wniemiec-io-cpp/scheduler/actions/workflows/macos.yml"><img src="https://github.com/wniemiec-io-cpp/scheduler/actions/workflows/macos.yml/badge.svg" alt=""></a>
	<a href="https://github.com/wniemiec-io-cpp/scheduler/actions/workflows/ubuntu.yml"><img src="https://github.com/wniemiec-io-cpp/scheduler/actions/workflows/ubuntu.yml/badge.svg" alt=""></a>
	<a href="https://codecov.io/gh/wniemiec-io-cpp/scheduler"><img src="https://codecov.io/gh/wniemiec-io-cpp/scheduler/branch/master/graph/badge.svg?token=R2SFS4SP86" alt="Coverage status"></a>
	<a href="https://docs.microsoft.com/en-us/cpp/"><img src="https://img.shields.io/badge/C++-17+-D0008F.svg" alt="Cpp compatibility"></a>
	<a href="https://github.com/wniemiec-task-cpp/scheduler/releases"><img src="https://img.shields.io/github/v/release/wniemiec-task-cpp/scheduler" alt="Release"></a>
	<a href="https://github.com/wniemiec-io-cpp/scheduler/blob/master/LICENSE"><img src="https://img.shields.io/github/license/wniemiec-io-cpp/scheduler" alt="License"></a>
</p>
<hr />

## ❇ Introduction
Scheduler allows you to perform operations with routines so that they are executed according to a criterion.

## ❓ How to use
1. Add the content of the [`src`](https://github.com/wniemiec-io-cpp/scheduler/blob/master/src) folder to the folder containing your project's source files

2. Add the content of the [`include`](https://github.com/wniemiec-io-cpp/scheduler/blob/master/include) folder to the folder containing your project's header files

3. Copy the [`Makefile`](https://github.com/wniemiec-io-cpp/scheduler/blob/master/Makefile) to your project's root folder (if you already has one, merge the files)

4. Run the following commands:
```
$ make clean
$ make
```

5. Use it
```
[...]

#include "wniemiec/task/scheduler/Scheduler.hpp";

[...]

std::cout << "Hello... " << std::endl;

Scheduler::set_timeout([]() {
	std::cout << "World!" << std::endl;
}, 2000);

[...]
```

**Note:** You can use cmake if you wish. To do this, use the [`CMakestd::lists.txt`](https://github.com/wniemiec-io-cpp/scheduler/blob/master/CMakestd::lists.txt) file.

## 📖 Documentation
|        Property        |Parameter type|Return type|Description|Default parameter value|
|----------------|-------------------------------|--|---------------------------|--------|
|set_iimeout |`routine: std::function<void(void)>&, delay: long`|`unsigned long`|Sets a timer which executes a routine once the timer expires| - |
|set_interval |`routine: std::function<void(void)>&, delay: long`|`unsigned long`|Repeatedly calls a routine with a fixed time delay between each call| - |
|clear_interval |`id: unsigned long`|`void`|Cancels a timed, repeating action| - |
|clear_timeout |`id: unsigned long`|`void`|Cancels a timed action| - |
|clear_all_timeout | `void`|`void`|Clear all timeouts| - |
|clear_all_intervals | `void`|`void`|Clear all intervals| - |
|set_timeout_to_routine|`routine: std::function<void(void)>&, delay: long`|`bool`|Runs a routine within a timeout. If the routine does not end on time, an interrupt signal will be sent to it| - |

## 🚩 Changelog
Details about each version are documented in the [releases section](https://github.com/williamniemiec/wniemiec-io-cpp/scheduler/releases).

## 🤝 Contribute!
See the documentation on how you can contribute to the project [here](https://github.com/wniemiec-io-cpp/scheduler/blob/master/CONTRIBUTING.md).

## 📁 Files

### /
|        Name        |Type|Description|
|----------------|-------------------------------|-----------------------------|
|dist |`Directory`|Released versions|
|docs |`Directory`|Documentation files|
|src     |`Directory`| Source files|

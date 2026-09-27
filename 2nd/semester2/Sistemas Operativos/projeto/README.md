<div align="center">

# 🧵 Multi-Runner Environment Orchestrator

A command scheduling and execution system developed in **C**, using **FIFOs**, **pipes** and process management.

![C](https://img.shields.io/badge/C-A8B9CC?style=for-the-badge\&logo=c\&logoColor=black)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge\&logo=linux\&logoColor=black)
![Makefile](https://img.shields.io/badge/Makefile-000000?style=for-the-badge\&logo=gnu\&logoColor=white)

</div>

## 📖 About the Project

This project implements a process execution controller and a set of runners in **C**.

The **controller** receives execution requests through a **FIFO**, manages the submitted processes and applies different scheduling policies. The **runners** communicate with the controller and execute the requested commands.

The system also supports limited parallel execution, allowing a configurable number of processes to run simultaneously.

## ✨ Features

* ⚙️ Process execution through dedicated runners
* 📡 Communication using FIFOs and pipes
* 🔄 Multiple scheduling policies
* 🚀 Configurable parallel process execution
* 📋 Process status monitoring
* 🛑 Graceful controller shutdown
* 🧪 Automated testing and benchmarking

## ⚙️ Compilation

Build the complete project:

```bash
make
```

Build only the controller:

```bash
make controller
```

Build only the runner:

```bash
make runner
```

Clean generated files:

```bash
make clean
```

## 🖥️ Usage

### Start the Controller

```bash
./bin/controller <max_parallel> <scheduling_policy>
```

Example:

```bash
./bin/controller 4 FCFS
```

The first argument defines the maximum number of processes that can run simultaneously, while the second selects the scheduling policy.

### Start a Runner

```bash
./bin/runner
```

Runners communicate with the controller and execute the commands assigned to them.

## 🧪 Testing

The `tests/` directory contains scripts for testing and evaluating the system.

```bash
bash tests/run_tests.sh
bash tests/benchmark.sh
bash tests/analyze.sh
```

Additional tests are available for concurrency and scheduling behaviour.

## 🛠️ Technologies

* C
* Linux
* FIFOs
* Pipes
* Process Management
* Makefile
* Shell Scripts

## 📁 Project Structure

```text
.
├── include/       # Header files and shared definitions
├── src/           # C source code
├── tests/         # Test and benchmark scripts
├── relatorio/     # Project report
├── Makefile
└── README.md
```

## 🎯 Objective

The main objective of the project is to apply **Operating Systems** concepts such as process management, inter-process communication, concurrency and scheduling in a practical C application.

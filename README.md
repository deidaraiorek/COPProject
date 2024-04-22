# Task Scheduler

## Overview

The Task Scheduler is a C++ application designed to organize and execute tasks based on different scheduling algorithms. It handles complex task dependencies and manages scheduling based on task durations and deadlines, using strategies such as Earliest Due Date (EDD), Shortest Processing Time (SPT), and Moore's algorithm. This application is particularly useful in environments where tasks have specific time constraints and interdependencies.

## Getting Started

### Prerequisites

- GCC, Clang, or any C++17 compatible compiler

### Compilation

To compile the project, navigate to the project directory in your terminal and run:

```bash
g++ -Wall -std=c++17 -o main main.cpp Scheduler.cpp Task.cpp
```

This command compiles the source files and generates an executable named `main`.

Usage
-----

### Running the Application

To run the program, use the following command:

```bash

./main
```

When executed, the program will prompt you to input the number of tasks, and for each task, you will need to enter details such as the task ID, duration, deadline, and dependencies.

#### Input Details

-   Task ID: A unique identifier for the task.
-   Duration: The time required to complete the task, specified in hours.
-   Deadline: The latest completion time for the task, formatted as YYYY-MM-DD HH:MM.
-   Dependencies: A list of task IDs that this task depends on, entered as a comma-separated string without spaces.

### Features

-   Task Management: Enables the addition of tasks with unique IDs, specific durations, precise deadlines, and defined dependencies.
-   Dependency Resolution: Implements a modified topological sort to handle task dependencies while considering deadlines.
-   Scheduling Algorithms:
    -   EDD: Schedules tasks based on the earliest due dates.
    -   SPT: Orders tasks from the shortest to the longest duration.
    -   Moore: Aims to minimize the number of late tasks by potentially removing the longest pending tasks to accommodate more urgent ones.
-   Real-Time Scheduling: Uses actual date and time data for realistic scheduling scenarios.


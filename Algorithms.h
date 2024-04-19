#pragma once
#include "Scheduler.h"
#include <algorithm>

// Function to sort tasks based on duration
void shortestProcessingTime(std::vector<Task>& tasks) {
    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.duration < b.duration;
    });
}

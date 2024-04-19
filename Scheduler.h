#pragma once
#include "Task.h"
#include <vector>
#include <map>
#include <queue>

class Scheduler {
private:
    std::vector<Task> tasks;

public:
    Scheduler(const std::vector<Task>& tasks);
    void addTask(const Task& task);
    std::vector<Task> scheduleTasks(const std::string& algorithm);
    const std::vector<Task>& getTasks() const { return tasks; }
    void solveDependencies();
};

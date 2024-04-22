#include "Scheduler.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <map>
#include <chrono>

// Constructor initializing the task list
Scheduler::Scheduler(const std::vector<Task>& tasks) : tasks(tasks) {}

// Add a task to the scheduler
void Scheduler::addTask(const Task& task) {
    tasks.push_back(task);
}

// Compare tasks by their deadlines (used for sorting)
static bool compareByDeadline(const Task& a, const Task& b) {
    return a.getDeadline() < b.getDeadline();
}

// Compare tasks by their durations (used for sorting by largest to smallest)
static bool compareByDuration(const Task& a, const Task& b) {
    return a.getDuration() > b.getDuration();
}

// Solve dependencies using a modified topological sort that respects deadlines
void Scheduler::solveDependencies() {
    // Create a map to easily find task indices by their IDs
    std::map<std::string, int> taskIndex;
    for (size_t i = 0; i < tasks.size(); ++i) {
        taskIndex[tasks[i].getId()] = i;
    }

    // Prepare adjacency list and in-degree count for topological sorting
    std::vector<std::vector<int>> graph(tasks.size());
    std::vector<int> inDegree(tasks.size(), 0);
    for (const auto& task : tasks) {
        for (const std::string& dep : task.getDependencies()) {
            if (taskIndex.count(dep)) {
                graph[taskIndex[dep]].push_back(taskIndex[task.getId()]);
                inDegree[taskIndex[task.getId()]]++;
            }
        }
    }

    // Priority queue to ensure tasks with earlier deadlines are processed first
    auto cmp = [this](int left, int right) { return tasks[left].getDeadline() > tasks[right].getDeadline(); };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);

    // Initialize the priority queue with all tasks that have no incoming edges
    for (size_t i = 0; i < inDegree.size(); ++i) {
        if (inDegree[i] == 0) {
            pq.push(i);
        }
    }

    // List to hold sorted tasks
    std::vector<Task> sortedTasks;
    std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        sortedTasks.push_back(tasks[u]);

        // Update current time and check for missed deadlines
        currentTime += std::chrono::hours(tasks[u].getDuration());
        if (currentTime > tasks[u].getDeadline()) {
            auto currentTime_t = std::chrono::system_clock::to_time_t(currentTime);
            auto deadline_t = std::chrono::system_clock::to_time_t(tasks[u].getDeadline());
            std::cout << "Missed Deadline: Task " << tasks[u].getId() << " scheduled to finish at " 
                      << std::ctime(&currentTime_t) << ", past its deadline of " << std::ctime(&deadline_t) << "." << std::endl;
        }

        // Process all adjacent tasks
        for (int v : graph[u]) {
            if (--inDegree[v] == 0) {
                pq.push(v);
            }
        }
    }

    // Check for any cycles which would indicate an unsolvable dependency
    if (sortedTasks.size() != tasks.size()) {
        std::cerr << "Cycle detected in tasks dependencies, scheduling not possible." << std::endl;
    } else {
        tasks = sortedTasks; // Successfully sorted tasks
        std::cout << "Dependencies resolved, tasks re-ordered based on earliest deadlines." << std::endl;
    }
}

// Schedule tasks based on the chosen algorithm
std::vector<Task> Scheduler::scheduleTasks(const std::string& algorithm) {
    if (algorithm == "Dependency") {
        solveDependencies();
        return tasks; // Return sorted tasks if dependencies were the focus
    }

    // Vectors to hold scheduled and late tasks
    std::vector<Task> scheduled;
    std::vector<Task> removed;

    // Sorting tasks based on the algorithm choice
    if (algorithm == "EDD" || algorithm == "SPT") {
        std::sort(tasks.begin(), tasks.end(), algorithm == "EDD" ? compareByDeadline : [](const Task& a, const Task& b) { return a.getDuration() < b.getDuration(); });
        scheduled = tasks;
    } else if (algorithm == "Moore") {
        std::sort(tasks.begin(), tasks.end(), compareByDeadline);

        std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
        for (auto& task : tasks) {
            auto deadline_t = std::chrono::system_clock::to_time_t(task.getDeadline());
            // std::cout << "Evaluating Task: " << task.getId() << " with Duration: " << task.getDuration() << " and Deadline: " << std::ctime(&deadline_t) << std::endl;
            if (currentTime + std::chrono::hours(task.getDuration()) <= task.getDeadline()) {
                scheduled.push_back(task);
                currentTime += std::chrono::hours(task.getDuration());
                auto currentTime_t = std::chrono::system_clock::to_time_t(currentTime);
                // std::cout << "Finish Task: " << task.getId() << " at Current Time: " << std::ctime(&currentTime_t) << std::endl;
            } else {
                auto toRemove = std::max_element(scheduled.begin(), scheduled.end(), compareByDuration);
                if (toRemove != scheduled.end() && toRemove->getDuration() > task.getDuration()) {
                    currentTime -= std::chrono::hours(toRemove->getDuration());
                    removed.push_back(*toRemove);
                    scheduled.erase(toRemove);
                    std::cout << "Removed Task: " << toRemove->getId() << " to make room." << std::endl;
                    if (currentTime + std::chrono::hours(task.getDuration()) <= task.getDeadline()) {
                        scheduled.push_back(task);
                        currentTime += std::chrono::hours(task.getDuration());
                        auto currentTime_t = std::chrono::system_clock::to_time_t(currentTime);
                        std::cout << "Scheduled Task: " << task.getId() << " after removal at Current Time: " << std::ctime(&currentTime_t) << std::endl;
                    } else {
                        removed.push_back(task);
                        std::cout << "Could not schedule Task: " << task.getId() << "; added to late tasks." << std::endl;
                    }
                } else {
                    removed.push_back(task);
                    std::cout << "Task: " << task.getId() << " is late and cannot be scheduled." << std::endl;
                }
            }
        }
    }
    // Print late tasks
    if (!removed.empty()) {
        std::cout << "\nLate Tasks:" << std::endl;
        for (const auto& task : removed) {
            auto deadline_t = std::chrono::system_clock::to_time_t(task.getDeadline());
            std::cout << "Task ID: " << task.getId() << " - missed the deadline " << std::ctime(&deadline_t) << std::endl;
        }
    }

    return scheduled;
}

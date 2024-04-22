#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <iostream>

class Task {
private:
    std::string id;
    int duration; // Duration in hours
    std::chrono::system_clock::time_point deadline; // Deadline as a date-time
    std::vector<std::string> dependencies;

public:
    Task(std::string id, int duration, std::chrono::system_clock::time_point deadline, std::vector<std::string> dependencies);

    std::string getId() const;
    int getDuration() const;
    std::chrono::system_clock::time_point getDeadline() const;
    std::vector<std::string> getDependencies() const;

    bool operator==(const Task& other) const;
};

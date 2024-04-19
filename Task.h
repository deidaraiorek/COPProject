#pragma once
#include <string>
#include <vector>

class Task {
private:
    std::string id; // Unique identifier for the task
    int duration;
    int deadline;
    std::vector<std::string> dependencies;

public:
    Task(std::string id, int duration, int deadline, std::vector<std::string> dependencies);

    std::string getId() const;
    int getDuration() const;
    int getDeadline() const;
    std::vector<std::string> getDependencies() const;

    // Define equality based on task ID
    bool operator==(const Task& other) const;
};

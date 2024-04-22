#include "Task.h"

Task::Task(std::string id, int duration, std::chrono::system_clock::time_point deadline, std::vector<std::string> dependencies)
    : id(id), duration(duration), deadline(deadline), dependencies(dependencies) {}

std::string Task::getId() const {
    return id;
}

int Task::getDuration() const {
    return duration;
}

std::chrono::system_clock::time_point Task::getDeadline() const {
    return deadline;
}

std::vector<std::string> Task::getDependencies() const {
    return dependencies;
}

bool Task::operator==(const Task& other) const {
    return id == other.id;
}

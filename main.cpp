#include "Scheduler.h"
#include <iostream>
#include <map>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <vector>

int main() {
    std::vector<Task> tasks;
    int numTasks;
    std::cout << "Enter the number of tasks: ";
    std::cin >> numTasks;
    std::cin.ignore(); // Flush the newline character out of the buffer

    for (int i = 0; i < numTasks; ++i) {
        std::string id;
        int duration;
        std::string deadlineStr;
        std::vector<std::string> dependencies;
        std::cout << "Enter Task ID: ";
        std::getline(std::cin, id);
        std::cout << "Enter Duration (hours): ";
        std::cin >> duration;
        std::cin.ignore();
        std::cout << "Enter Deadline (YYYY-MM-DD HH:MM): ";
        std::getline(std::cin, deadlineStr);
        std::tm tm = {};
        std::istringstream ss(deadlineStr);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
        auto deadline = std::chrono::system_clock::from_time_t(std::mktime(&tm));

        std::string dep;
        std::cout << "Enter Dependencies (comma separated, no spaces, hit enter if none): ";
        std::getline(std::cin, dep);
        std::istringstream depstream(dep);
        std::string token;
        while (getline(depstream, token, ',')) {
            dependencies.push_back(token);
        }

        tasks.emplace_back(id, duration, deadline, dependencies);
    }

    Scheduler scheduler(tasks);

    std::map<int, std::string> algorithmChoices = {
        {1, "EDD"},
        {2, "Moore"},
        {3, "SPT"},
        {4, "Dependency"}
    };

    int choice;
    do {
        std::cout << "\nChoose an algorithm (Enter 0 to finish):\n";
        std::cout << "1: EDD (Earliest Due Date) - Schedules tasks based on the earliest deadlines.\n";
        std::cout << "2: Moore - Minimizes the number of late tasks, removing the task with the longest duration if necessary.\n";
        std::cout << "3: SPT (Shortest Processing Time) - Schedules tasks in order of shortest to longest duration.\n";
        std::cout << "4: Dependency - Resolves task dependencies before scheduling.\n";
        std::cout << "Enter your choice (1-4, 0 to end): ";
        std::cin >> choice;

        if (choice != 0) {
            if (algorithmChoices.find(choice) != algorithmChoices.end()) {
                std::cout << "Selected: " << algorithmChoices[choice] << std::endl;
                auto scheduledTasks = scheduler.scheduleTasks(algorithmChoices[choice]);
                std::cout << "\nScheduled Tasks Order for " << algorithmChoices[choice] << ":\n";
                for (const auto& task : scheduledTasks) {
                    auto deadline_time_t = std::chrono::system_clock::to_time_t(task.getDeadline());
                    std::cout << "Task ID: " << task.getId() << " with deadline " << std::ctime(&deadline_time_t);
                }
            } else {
                std::cout << "Invalid choice. Please try again.\n";
            }
        }
    } while (choice != 0);

    return 0;
}

#include "Scheduler.h"
#include <iostream>
#include <map>


int main() {
    std::vector<Task> tasks = {
         Task("Task1", 8, 18, {}), 
        Task("Task2", 3, 15, {"Task1"}), 
        Task("Task3", 5, 20, {}), 
        Task("Task4", 4, 16, {"Task2", "Task3"}),
        Task("Task5", 1, 12, {}), 
        Task("Task6", 3, 15, {"Task5"}),
        Task("Task7", 6, 22, {}), 
    };


    Scheduler scheduler(tasks);

    std::map<int, std::string> algorithmChoices = {
        {1, "EDD"},
        {2, "Moore"},
        {3, "SPT"},
        {4, "Dependency"}
    };

    std::cout << "Choose an algorithm:\n";
    std::cout << "1: EDD (Earliest Due Date) - Schedules tasks based on the earliest deadlines.\n";
    std::cout << "2: Moore - Minimizes the number of late tasks, removing the task with the longest duration if necessary.\n";
    std::cout << "3: SPT (Shortest Processing Time) - Schedules tasks in order of shortest to longest duration.\n";
    std::cout << "4: Dependency - Resolves task dependencies before scheduling.\n";

    int choice;
    std::cin >> choice;

    if (algorithmChoices.find(choice) != algorithmChoices.end()) {
        std::cout << "Selected: " << algorithmChoices[choice] << std::endl;
        auto scheduledTasks = scheduler.scheduleTasks(algorithmChoices[choice]);
        std::cout << "\nScheduled Tasks Order:\n";
        for (const auto& task : scheduledTasks) {
            std::cout << "Task ID: " << task.getId() << " with deadline " << task.getDeadline() << "\n";
        }
    } else {
        std::cout << "Invalid choice. Exiting program.\n";
    }

    return 0;
}

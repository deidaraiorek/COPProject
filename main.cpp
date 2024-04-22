#include "Scheduler.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <map>

using namespace std;
using namespace chrono;

int main() {
    vector<Task> tasks;
    int numTasks;
    cout << "Enter the number of tasks: ";
    cin >> numTasks;
    cin.ignore(); // Flush the newline character out of the buffer

    for (int i = 0; i < numTasks; ++i) {
        string id;
        int duration;
        string deadlineStr;
        vector<string> dependencies;

        cout << "Enter Task ID: ";
        getline(cin, id);
        cout << "Enter Duration (hours): ";
        cin >> duration;
        cin.ignore();
        cout << "Enter Deadline (YYYY-MM-DD HH:MM): ";
        getline(cin, deadlineStr);

        istringstream ss(deadlineStr);
        system_clock::time_point deadlineTime;
        tm tm = {};
        ss >> get_time(&tm, "%Y-%m-%d %H:%M"); 
        tm.tm_isdst = -1; 
        time_t tt = mktime(&tm);
        deadlineTime = system_clock::from_time_t(tt);

        cout << "Enter Dependencies (comma separated, no spaces, hit enter if none): ";
        string deps;
        getline(cin, deps);
        stringstream depstream(deps);
        string dep;
        while (getline(depstream, dep, ',')) {
            if (!dep.empty()) {
                dependencies.push_back(dep);
            }
        }

        tasks.emplace_back(id, duration, deadlineTime, dependencies);
    }

    Scheduler scheduler(tasks);

    map<int, string> algorithmChoices = {
        {1, "EDD"},
        {2, "Moore"},
        {3, "SPT"},
        {4, "Dependency"}
    };

    int choice;
    do {
        cout << "\nChoose an algorithm (Enter 0 to finish):\n";
        cout << "1: EDD (Earliest Due Date) - Schedules tasks based on the earliest deadlines.\n";
        cout << "2: Moore - Minimizes the number of late tasks, removing the task with the longest duration if necessary.\n";
        cout << "3: SPT (Shortest Processing Time) - Schedules tasks in order of shortest to longest duration.\n";
        cout << "4: Dependency - Resolves task dependencies before scheduling.\n";
        cout << "Enter your choice (1-4, 0 to end): ";
        cin >> choice;

        if (choice != 0 && algorithmChoices.find(choice) != algorithmChoices.end()) {
            auto scheduledTasks = scheduler.scheduleTasks(algorithmChoices[choice]);
            cout << "\nScheduled Tasks Order for " << algorithmChoices[choice] << ":\n";
            for (const auto& task : scheduledTasks) {
                auto deadline_time_t = system_clock::to_time_t(task.getDeadline());
                cout << "Task ID: " << task.getId() << " with deadline " << put_time(localtime(&deadline_time_t), "%c") << endl;
            }
        }
    } while (choice != 0);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>

// Structure to hold a task
struct Task {
    int id;
    std::string description;
    bool completed;
};

// Functions declarations
void displayMenu();
void createTask(std::vector<Task>& tasks);
void readTasks(const std::vector<Task>& tasks);
void updateTask(std::vector<Task>& tasks);
void deleteTask(std::vector<Task>& tasks);

int main() {
    std::vector<Task> tasks;
    int choice;

    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // To handle newline character

        switch (choice) {
            case 1:
                createTask(tasks);
                break;
            case 2:
                readTasks(tasks);
                break;
            case 3:
                updateTask(tasks);
                break;
            case 4:
                deleteTask(tasks);
                break;
            case 5:
                std::cout << "Exiting the application.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

void displayMenu() {
    std::cout << "\nTo-Do App - Menu\n";
    std::cout << "1. Create Task\n";
    std::cout << "2. View Tasks\n";
    std::cout << "3. Update Task\n";
    std::cout << "4. Delete Task\n";
    std::cout << "5. Exit\n";
}

void createTask(std::vector<Task>& tasks) {
    Task newTask;
    newTask.id = tasks.empty() ? 1 : tasks.back().id + 1;
    std::cout << "Enter task description: ";
    std::getline(std::cin, newTask.description);
    newTask.completed = false;

    tasks.push_back(newTask);
    std::cout << "Task created successfully!\n";
}

void readTasks(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks available.\n";
        return;
    }

    std::cout << "\nList of Tasks:\n";
    for (const auto& task : tasks) {
        std::cout << "ID: " << task.id
                  << ", Description: " << task.description
                  << ", Completed: " << (task.completed ? "Yes" : "No") << "\n";
    }
}

void updateTask(std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks available to update.\n";
        return;
    }

    int id;
    std::cout << "Enter the task ID to update: ";
    std::cin >> id;
    std::cin.ignore(); // To handle newline character

    for (auto& task : tasks) {
        if (task.id == id) {
            std::cout << "Enter new description: ";
            std::getline(std::cin, task.description);
            char completionChoice;
            std::cout << "Is the task completed? (y/n): ";
            std::cin >> completionChoice;
            std::cin.ignore(); // To handle newline character

            task.completed = (completionChoice == 'y' || completionChoice == 'Y');
            std::cout << "Task updated successfully!\n";
            return;
        }
    }

    std::cout << "Task ID not found.\n";
}

void deleteTask(std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks available to delete.\n";
        return;
    }

    int id;
    std::cout << "Enter the task ID to delete: ";
    std::cin >> id;
    std::cin.ignore(); // To handle newline character

    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            tasks.erase(it);
            std::cout << "Task deleted successfully!\n";
            return;
        }
    }

    std::cout << "Task ID not found.\n";
}

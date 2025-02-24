// DSA_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <queue>
#include <limits>
using namespace std;

//node
class Task {
public:
    int id;                  
    string description;      
    Task* next;              

    // Constructor
    Task(int taskId, string taskDesc) {
        id = taskId;
        description = taskDesc;
        next = nullptr;
    }
};


class TaskManager {
private:
    Task* head;               
    int taskCounter;          
    queue<Task*> completedTasks; // Queue for completed tasks

    // Validate Task Description (Only Alphabets)
    bool isValidTask(const string& task) {
        for (char c : task) {
            if (isdigit(c) || ispunct(c)) return false;
        }
        return true;
    }

    // Validate Numeric Input for Task ID
    bool isValidNumeric(const string& input) {
        for (char c : input) {
            if (!isdigit(c)) return false;
        }
        return true;
    }

public:
    TaskManager() : head(nullptr), taskCounter(1) {}

    // Add Task Function
    void addTask() {
        string taskDesc;
        cout << "Enter Task Description: ";
        cin.ignore();
        getline(cin, taskDesc);

        // Task Description Validation
        while (!isValidTask(taskDesc)) {
            cout << "Invalid task! Please enter alphabets only: ";
            getline(cin, taskDesc);
        }

        // Create New Task
        Task* newTask = new Task(taskCounter++, taskDesc);
        if (head == nullptr) {
            head = newTask;
        }
        else {
            Task* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newTask;
        }
        cout << "Task Added Successfully! Task ID: " << newTask->id << endl;
    }

    // Complete Task by ID
    void completeTask() {
        if (head == nullptr) {
            cout << "No tasks available to complete!" << endl;
            return;
        }

        string taskIdInput;
        cout << "Enter Task ID to Mark as Complete: ";
        cin >> taskIdInput;

        while (!isValidNumeric(taskIdInput)) {
            cout << "Invalid ID! Please enter a valid numeric ID: ";
            cin >> taskIdInput;
        }

        int taskId = stoi(taskIdInput);

        Task* temp = head;
        Task* prev = nullptr;

        while (temp != nullptr && temp->id != taskId) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Task ID not found!" << endl;
            return;
        }

        if (prev == nullptr) {
            head = temp->next;
        }
        else {
            prev->next = temp->next;
        }

        completedTasks.push(temp);
        cout << "Task Completed: " << temp->description << " (ID: " << temp->id << ")" << endl;
    }

    // Undo Last Completed Task
    void undoLastCompletedTask() {
        if (completedTasks.empty()) {
            cout << "No completed tasks to undo!" << endl;
            return;
        }

        Task* restoredTask = completedTasks.front();
        completedTasks.pop();

        restoredTask->next = head;
        head = restoredTask;

        cout << "Task Restored: " << restoredTask->description << " (ID: " << restoredTask->id << ")" << endl;
    }

    // Delete Task by ID
    void deleteTask() {
        if (head == nullptr) {
            cout << "No tasks available to delete!" << endl;
            return;
        }

        string taskIdInput;
        cout << "Enter Task ID to Delete: ";
        cin >> taskIdInput;

        while (!isValidNumeric(taskIdInput)) {
            cout << "Invalid ID! Please enter a valid numeric ID: ";
            cin >> taskIdInput;
        }

        int taskId = stoi(taskIdInput);

        Task* temp = head;
        Task* prev = nullptr;

        while (temp != nullptr && temp->id != taskId) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Task ID not found!" << endl;
            return;
        }

        if (prev == nullptr) {
            head = temp->next;
        }
        else {
            prev->next = temp->next;
        }

        cout << "Task Deleted: " << temp->description << " (ID: " << temp->id << ")" << endl;
        delete temp;
    }

    // Display All Tasks
    void displayTasks() {
        if (head == nullptr && completedTasks.empty()) {
            cout << "No tasks to display!" << endl;
            return;
        }

        cout << "\n--- Active Task List ---\n";
        Task* temp = head;
        while (temp != nullptr) {
            cout << "ID: " << temp->id << " | Task: " << temp->description << endl;
            temp = temp->next;
        }

        cout << "\n--- Completed Task List ---\n";
        queue<Task*> tempQueue = completedTasks;
        while (!tempQueue.empty()) {
            Task* completed = tempQueue.front();
            tempQueue.pop();
            cout << "ID: " << completed->id << " | Task: " << completed->description << endl;
        }
    }
};

// Get Valid Menu Choice
int getValidMenuChoice() {
    int choice;
    while (true) {
        cout << " \n      --- Welcome to Task Management System ---\n";
        cout << "We would love to assist you to manage your routinely tasks\n";
        cout << "1. Add Task\n";
        cout << "2. Complete Task\n";
        cout << "3. Undo Last Completed Task\n";
        cout << "4. Delete Task by ID\n";
        cout << "5. Display All Tasks\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        if (cin >> choice && choice >= 1 && choice <= 6) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
        else {
            cout << "Invalid input! Please enter a number between 1 and 6.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Main Function
int main() {
    TaskManager manager;
    int choice;

    do {
        choice = getValidMenuChoice();

        switch (choice) {
        case 1: manager.addTask(); break;
        case 2: manager.completeTask(); break;
        case 3: manager.undoLastCompletedTask(); break;
        case 4: manager.deleteTask(); break;
        case 5: manager.displayTasks(); break;
        case 6: cout << "Exiting Program. Goodbye!" << endl; break;
        default: cout << "Unexpected error!" << endl;
        }
    } while (choice != 6);

    return 0;
}







// Run program: Ctrl + F5 or Debug > Start Without Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
// Debug program: F5 or Debug > Start Debugging menu
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#include <iostream>
#include <string>
#include <limits> // For input validation
using namespace std;

// Node structure to represent a student
struct Student {
    int rollNumber;
    string name;
    Student* next;

    Student(int roll, string studentName) {
        rollNumber = roll;
        name = studentName;
        next = nullptr;
    }
};

// Class to manage the linked list
class StudentList {
private:
    Student* head;

public:
    StudentList() : head(nullptr) {}

    // Add a new student
    void addStudent(int roll, string name) {
        Student* newStudent = new Student(roll, name);
        if (!head) {
            head = newStudent;
        } else {
            Student* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newStudent;
        }
        cout << "Student added successfully.\n";
    }

    // Display all students
    void displayStudents() {
        if (!head) {
            cout << "No students found.\n";
            return;
        }
        Student* temp = head;
        cout << "Student List:\n";
        while (temp) {
            cout << "Roll Number: " << temp->rollNumber << ", Name: " << temp->name << endl;
            temp = temp->next;
        }
    }

    // Search for a student by roll number
    void searchStudent(int roll) {
        Student* temp = head;
        while (temp) {
            if (temp->rollNumber == roll) {
                cout << "Student Found: Roll Number: " << temp->rollNumber << ", Name: " << temp->name << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Student with Roll Number " << roll << " not found.\n";
    }

    // Delete a student by roll number
    void deleteStudent(int roll) {
        if (!head) {
            cout << "No students to delete.\n";
            return;
        }
        if (head->rollNumber == roll) {
            Student* temp = head;
            head = head->next;
            delete temp;
            cout << "Student deleted successfully.\n";
            return;
        }

        Student* temp = head;
        while (temp->next && temp->next->rollNumber != roll) {
            temp = temp->next;
        }
        if (!temp->next) {
            cout << "Student with Roll Number " << roll << " not found.\n";
            return;
        }
        Student* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        cout << "Student deleted successfully.\n";
    }
};

// Function to validate numeric input
bool validateNumericInput(int& input) {
    if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "Invalid input! Please enter a number.\n";
        return false;
    }
    return true;
}

// Main function
int main() {
    StudentList studentList;
    int choice, roll;
    string name;

    do {
        cout << "\nStudent Management System:\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search for a Student\n";
        cout << "4. Delete a Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (!validateNumericInput(choice) || choice < 1 || choice > 5) {
            cout << "Invalid option! Please choose a valid menu option.\n";
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter Roll Number: ";
                cin >> roll;
                if (!validateNumericInput(roll)) break;
                cout << "Enter Name: ";
                cin.ignore(); // To handle the newline character
                getline(cin, name);
                studentList.addStudent(roll, name);
                break;

            case 2:
                studentList.displayStudents();
                break;

            case 3:
                cout << "Enter Roll Number to Search: ";
                cin >> roll;
                if (!validateNumericInput(roll)) break;
                studentList.searchStudent(roll);
                break;

            case 4:
                cout << "Enter Roll Number to Delete: ";
                cin >> roll;
                if (!validateNumericInput(roll)) break;
                studentList.deleteStudent(roll);
                break;

            case 5:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
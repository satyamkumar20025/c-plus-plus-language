#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    int roll;
    string name;
    float marks;
};

class StudentManager {
public:
    void addStudent();
    void viewStudents();
    void searchStudent();
    void deleteStudent();
};

void StudentManager::addStudent() {
    ofstream file("student.txt", ios::app);
    if (!file) {
        cout << "File error." << endl;
        return;
    }

    Student s;
    cout << "\nEnter Roll Number: ";
    cin >> s.roll;
    cout << "Enter Name: ";
    cin >> s.name;
    cout << "Enter Marks: ";
    cin >> s.marks;

    file << s.roll << " " << s.name << " " << s.marks << endl;
    file.close();
    cout << "Student added successfully." << endl;
}

void StudentManager::viewStudents() {
    ifstream file("student.txt");
    if (!file) {
        cout << "No records found." << endl;
        return;
    }

    Student s;
    cout << "\n--- Student Records ---\n";
    while (file >> s.roll >> s.name >> s.marks) {
        cout << "Roll: " << s.roll << ", Name: " << s.name << ", Marks: " << s.marks << endl;
    }

    file.close();
}

void StudentManager::searchStudent() {
    ifstream file("student.txt");
    if (!file) {
        cout << "File not found." << endl;
        return;
    }

    int roll;
    bool found = false;
    cout << "\nEnter Roll Number to Search: ";
    cin >> roll;

    Student s;
    while (file >> s.roll >> s.name >> s.marks) {
        if (s.roll == roll) {
            cout << "Found: Roll: " << s.roll << ", Name: " << s.name << ", Marks: " << s.marks << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student with Roll " << roll << " not found." << endl;
    }

    file.close();
}

void StudentManager::deleteStudent() {
    ifstream file("student.txt");
    ofstream temp("temp.txt");
    if (!file || !temp) {
        cout << "File error." << endl;
        return;
    }

    int roll;
    bool found = false;
    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    Student s;
    while (file >> s.roll >> s.name >> s.marks) {
        if (s.roll == roll) {
            found = true;
        } else {
            temp << s.roll << " " << s.name << " " << s.marks << endl;
        }
    }

    file.close();
    temp.close();

    remove("student.txt");
    rename("temp.txt", "student.txt");

    if (found)
        cout << "Student record deleted." << endl;
    else
        cout << "Roll number not found." << endl;
}

int main() {
    StudentManager manager;
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search Student by Roll No\n";
        cout << "4. Delete Student by Roll No\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manager.addStudent(); break;
            case 2: manager.viewStudents(); break;
            case 3: manager.searchStudent(); break;
            case 4: manager.deleteStudent(); break;
            case 5: cout << "Thank you. Exiting program." << endl; break;
            default: cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 5);

    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Employee {
    int id;
    string name;
    string address;
    float salary;
};

class EmployeeManager {
public:
    void addEmployee();
    void displayEmployees();
    void searchEmployee();
    void updateEmployee();
    void removeEmployee();
};

void EmployeeManager::addEmployee() {
    ofstream file("employee.dat", ios::binary | ios::app);
    if (!file) {
        cout << "File not found!" << endl;
        return;
    }

    Employee e;
    cout << "Enter Employee ID: ";
    cin >> e.id;
    cout << "Enter Employee Name: ";
    cin >> e.name;
    cout << "Enter Employee Address: ";
    cin >> e.address;
    cout << "Enter Employee Salary: ";
    cin >> e.salary;

    file.write(reinterpret_cast<char*>(&e), sizeof(Employee));
    file.close();
    cout << " New employee added successfully!" << endl;
}

void EmployeeManager::displayEmployees() {
    ifstream file("employee.dat", ios::binary);
    if (!file) {
        cout << "No records found!" << endl;
        return;
    }

    Employee e;
    cout << "\n--- Employee List ---\n";
    while (file.read(reinterpret_cast<char*>(&e), sizeof(Employee))) {
        cout << "ID: " << e.id << " | Name: " << e.name
             << " | Address: " << e.address << " | Salary: " << e.salary << endl;
    }
    file.close();
}

void EmployeeManager::searchEmployee() {
    ifstream file("employee.dat", ios::binary);
    if (!file) {
        cout << "No records found!" << endl;
        return;
    }

    int id;
    bool found = false;
    cout << "Enter Employee ID to search: ";
    cin >> id;

    Employee e;
    while (file.read(reinterpret_cast<char*>(&e), sizeof(Employee))) {
        if (e.id == id) {
            cout << "\n Record Found!\n";
            cout << "ID: " << e.id << " | Name: " << e.name
                 << " | Address: " << e.address << " | Salary: " << e.salary << endl;
            found = true;
            break;
        }
    }
    file.close();

    if (!found) cout << " No employee found with ID: " << id << endl;
}

void EmployeeManager::updateEmployee() {
    fstream file("employee.dat", ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "No records found!" << endl;
        return;
    }

    int id;
    bool found = false;
    cout << "Enter Employee ID to update: ";
    cin >> id;

    Employee e;
    while (file.read(reinterpret_cast<char*>(&e), sizeof(Employee))) {
        if (e.id == id) {
            cout << "Current Name: " << e.name << "\nEnter New Name: ";
            cin >> e.name;
            cout << "Current Address: " << e.address << "\nEnter New Address: ";
            cin >> e.address;
            cout << "Current Salary: " << e.salary << "\nEnter New Salary: ";
            cin >> e.salary;

            file.seekp(-static_cast<int>(sizeof(Employee)), ios::cur);
            file.write(reinterpret_cast<char*>(&e), sizeof(Employee));
            cout << " Employee updated successfully!" << endl;
            found = true;
            break;
        }
    }
    file.close();

    if (!found) cout << " No employee found with ID: " << id << endl;
}

void EmployeeManager::removeEmployee() {
    ifstream file("employee.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);
    if (!file || !temp) {
        cout << "No records found!" << endl;
        return;
    }

    int id;
    bool found = false;
    cout << "Enter Employee ID to remove: ";
    cin >> id;

    Employee e;
    while (file.read(reinterpret_cast<char*>(&e), sizeof(Employee))) {
        if (e.id != id) {
            temp.write(reinterpret_cast<char*>(&e), sizeof(Employee));
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("employee.dat");
    rename("temp.dat", "employee.dat");

    if (found) cout << " Employee removed successfully!" << endl;
    else cout << " No employee found with ID: " << id << endl;
}

int main() {
    EmployeeManager manager;
    int choice;

    do {
        cout << "\n===== Employee Management System =====\n";
        cout << "1. Add Employee\n";
        cout << "2. Display All Employees\n";
        cout << "3. Search Employee\n";
        cout << "4. Update Employee\n";
        cout << "5. Remove Employee\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manager.addEmployee(); break;
            case 2: manager.displayEmployees(); break;
            case 3: manager.searchEmployee(); break;
            case 4: manager.updateEmployee(); break;
            case 5: manager.removeEmployee(); break;
            case 6: cout << "Exiting program..." << endl; break;
            default: cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 6);

    return 0;
}

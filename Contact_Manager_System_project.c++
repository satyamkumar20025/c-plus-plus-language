#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
};

class ContactManager {
public:
    void addContact();
    void displayContacts();
    void searchContact();
    void updateContact();
    void deleteContact();
};

void ContactManager::addContact() {
    ofstream file("contacts.txt", ios::app);
    if (!file) {
        cout << "File not found!" << endl;
        return;
    }

    Contact c;
    cout << "Enter the Name: ";
    cin >> c.name;
    cout << "Enter the Mobile Phone number: ";
    cin >> c.phone;
    cout << "Enter Email: ";
    cin >> c.email;

    file << c.name << " " << c.phone << " " << c.email << endl;
    file.close();

    cout << "Contact added successfully!" << endl;
}

void ContactManager::displayContacts() {
    ifstream file("contacts.txt");
    if (!file) {
        cout << "No contacts found!" << endl;
        return;
    }

    Contact c;
    cout << "\n--- Contact List ---\n";
    while (file >> c.name >> c.phone >> c.email) {
        cout << "Name: " << c.name << "\nPhone: " << c.phone << "\nEmail: " << c.email << "\n-------------------\n";
    }
    file.close();
}

void ContactManager::searchContact() {
    ifstream file("contacts.txt");
    if (!file) {
        cout << "No contacts found!" << endl;
        return;
    }

    string name, number;
    bool found = false;
    cout << "Enter name to search: ";
    cin >> name;
    cout << "Enter phone to search: ";
    cin >> number;

    Contact c;
    while (file >> c.name >> c.phone >> c.email) {
        if (c.name == name || c.phone == number) {
            cout << "Found Contact:\nName: " << c.name << "\nPhone: " << c.phone << "\nEmail: " << c.email << endl;
            found = true;
            break;
        }
    }
    file.close();

    if (!found)
        cout << "Contact not found!" << endl;
}

void ContactManager::updateContact() {
    ifstream file("contacts.txt");
    ofstream temp("temp.txt");
    if (!file || !temp) {
        cout << "File error!" << endl;
        return;
    }

    string name;
    bool found = false;
    cout << "Enter name of contact to update: ";
    cin >> name;

    Contact c;
    while (file >> c.name >> c.phone >> c.email) {
        if (c.name == name) {
            cout << "Current -> Name: " << c.name << ", Phone: " << c.phone << ", Email: " << c.email << endl;
            cout << "Enter new Phone: ";
            cin >> c.phone;
            cout << "Enter new Email: ";
            cin >> c.email;
            found = true;
        }
        temp << c.name << " " << c.phone << " " << c.email << endl;
    }

    file.close();
    temp.close();

    remove("contacts.txt");
    rename("temp.txt", "contacts.txt");

    if (found)
        cout << "Contact updated successfully!" << endl;
    else
        cout << "Contact not found!" << endl;
}

void ContactManager::deleteContact() {
    ifstream file("contacts.txt");
    ofstream temp("temp.txt");
    if (!file || !temp) {
        cout << "File error!" << endl;
        return;
    }

    string name;
    bool found = false;
    cout << "Enter name of contact to delete: ";
    cin >> name;

    Contact c;
    while (file >> c.name >> c.phone >> c.email) {
        if (c.name == name) {
            found = true;
            continue;
        }
        temp << c.name << " " << c.phone << " " << c.email << endl;
    }

    file.close();
    temp.close();

    remove("contacts.txt");
    rename("temp.txt", "contacts.txt");

    if (found)
        cout << "Contact deleted successfully!" << endl;
    else
        cout << "Contact not found!" << endl;
}

int main() {
    ContactManager manager;
    int choice;

    do {
        cout << "\n===== Contact Management System =====\n";
        cout << "1. Add Contact\n";
        cout << "2. Display Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Update Contact\n";
        cout << "5. Delete Contact\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manager.addContact(); break;
            case 2: manager.displayContacts(); break;
            case 3: manager.searchContact(); break;
            case 4: manager.updateContact(); break;
            case 5: manager.deleteContact(); break;
            case 6: cout << "Exiting program..." << endl; break;
            default: cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 6);

    return 0;
}

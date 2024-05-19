#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Structure to store information about a guest
struct Note {
    string lastName;
    string firstName;
    string phoneNumber;
    int birthDate[3]; // day, month, year
};

class OpenHashTable {
private:
    static const int TABLE_SIZE = 10; // Example table size
    vector<list<Note>> table;

    int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % TABLE_SIZE;
        }
        return hash;
    }

public:
    OpenHashTable() {
        table.resize(TABLE_SIZE);
    }

    // Add a guest note
    void addNote(const Note& note) {
        string fullName = note.firstName + " " + note.lastName;
        int hashValue = hashFunction(fullName);
        table[hashValue].push_front(note);
    }

    // Delete guest note
    void deleteNote(const string& lastName, const string& firstName) {
        string fullName = firstName + " " + lastName;
        int hashValue = hashFunction(fullName);
        auto& notes = table[hashValue];
        notes.remove_if([&](const Note& n) {
            return n.lastName == lastName && n.firstName == firstName;
            });
    }

    // Find guest note by last name
    bool findNoteByLastName(const string& lastName, vector<Note>& result) {
        for (const auto& bucket : table) {
            for (const auto& note : bucket) {
                if (note.lastName == lastName) {
                    result.push_back(note);
                }
            }
        }
        return !result.empty();
    }

    // Save to file
    void saveToFile(const string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const auto& bucket : table) {
                for (const auto& note : bucket) {
                    outFile << note.lastName << " " << note.firstName << " " << note.phoneNumber << " "
                        << note.birthDate[0] << " " << note.birthDate[1] << " " << note.birthDate[2] << "\n";
                }
            }
            outFile.close();
            cout << "Data saved to file successfully.\n";
        }
        else {
            cerr << "Error opening file for writing.\n";
        }
    }

    // Load from file
    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                istringstream iss(line);
                Note note;
                iss >> note.lastName >> note.firstName >> note.phoneNumber >> note.birthDate[0] >> note.birthDate[1] >> note.birthDate[2];
                addNote(note);
            }
            inFile.close();
        }
        else {
            cerr << "Error opening file for reading.\n";
        }
    }

    // Display all guest notes
    void displayAllNotes() {
        for (const auto& bucket : table) {
            for (const auto& note : bucket) {
                cout << note.lastName << " " << note.firstName << " " << note.phoneNumber << " "
                    << note.birthDate[0] << " " << note.birthDate[1] << " " << note.birthDate[2] << "\n";
            }
        }
    }
};

// Function to input guest information from keyboard
Note inputNoteInfo() {
    Note note;
    cout << "Enter last name: ";
    cin >> note.lastName;
    cout << "Enter first name: ";
    cin >> note.firstName;
    cout << "Enter phone number: ";
    cin >> note.phoneNumber;
    cout << "Enter birth date (day month year): ";
    for (int i = 0; i < 3; ++i) {
        while (!(cin >> note.birthDate[i])) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid date: ";
        }
    }
    return note;
}

int main() {
    OpenHashTable hashTable;
    int choice;
    do {
        cout << "1. Add a guest note\n";
        cout << "2. Delete a guest note\n";
        cout << "3. Find a guest note by last name\n";
        cout << "4. Save data to a file\n";
        cout << "5. Load data from a file\n";
        cout << "6. Display all guest notes\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            Note note = inputNoteInfo();
            hashTable.addNote(note);
            break;
        }
        case 2: {
            string lastName, firstName;
            cout << "Enter last name: ";
            cin >> lastName;
            cout << "Enter first name: ";
            cin >> firstName;
            hashTable.deleteNote(lastName, firstName);
            break;
        }
        case 3: {
            string lastName;
            cout << "Enter last name: ";
            cin >> lastName;
            vector<Note> result;
            if (hashTable.findNoteByLastName(lastName, result)) {
                for (const auto& note : result) {
                    cout << "Found: " << note.lastName << " " << note.firstName << " " << note.phoneNumber << " "
                        << note.birthDate[0] << "." << note.birthDate[1] << "." << note.birthDate[2] << endl;
                }
            }
            else {
                cout << "No guest notes found with last name " << lastName << ".\n";
            }
            break;
        }
        case 4: {
            string filename;
            cout << "Enter the filename to save: ";
            cin >> filename;
            hashTable.saveToFile(filename);
            break;
        }
        case 5: {
            string filename;
            cout << "Enter the filename to load: ";
            cin >> filename;
            hashTable.loadFromFile(filename);
            break;
        }
        case 6: {
            cout << "Displaying all guest notes:\n";
            hashTable.displayAllNotes();
            break;
        }
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 7);
    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Guest {
    string name;
    int roomNumber{};
    Guest* prev{};
    Guest* next{};
};

Guest* head = nullptr;
Guest* tail = nullptr;

void loadGuestsFromFile(const string& fileName) {
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error: could not open file \"" << fileName << "\"" << endl;
        return;
    }
    string name;
    int roomNumber; 
    while (inFile >> name >> roomNumber) {
        auto* guest = new Guest();
        guest->name = name;
        guest->roomNumber = roomNumber;
        guest->prev = tail;
        guest->next = nullptr;
        if (tail == nullptr) {
            head = tail = guest;
        } else {
        tail->next = guest;
        tail = guest;
        }
    }
    inFile.close();
}

void saveGuestsToFile(const string& fileName) {
    ofstream outFile(fileName);
    if (!outFile) {
        cerr << "Error: could not create file \"" << fileName << "\"" << endl;
        return;
    }
    for (Guest* guest = head; guest != nullptr; guest = guest->next) {
        outFile << guest->name << " " << guest->roomNumber << endl;
    }   
    outFile.close();
}

void insertGuest() {
    string name;
    int roomNumber;
    cout << "Enter guest name: ";
    cin >> name;
    cout << "Enter room number: ";
    cin >> roomNumber;
    auto* guest = new Guest();
    guest->name = name;
    guest->roomNumber = roomNumber;
    guest->prev = tail;
    guest->next = nullptr;
    if (tail == nullptr) {
        head = tail = guest;
    } else {
        tail->next = guest;
        tail = guest;
    }
    saveGuestsToFile("hotel.txt");
    cout << "Guest added successfully." << endl;
}

Guest* findGuestByName(const string& name) {
    for (Guest* guest = head; guest != nullptr; guest = guest->next) {
        if (guest->name == name) {
            return guest;
        }
    }
    return nullptr;
}

Guest* findGuestByRoomNumber(int roomNumber) {
    for (Guest* guest = head; guest != nullptr; guest = guest->next) {
        if (guest->roomNumber == roomNumber) {
            return guest;
        }
    }
    return nullptr;
}

void searchGuest() {
    cout << "Enter guest name or room number: ";
    string input;
    cin >> input;
    Guest* guest;
    if (isdigit(input[0])) {
        int roomNumber = stoi(input);
        guest = findGuestByRoomNumber(roomNumber);
    } else {
        guest = findGuestByName(input);
    }
    if (guest == nullptr) {
        cout << "Guest not found." << endl;
    } else {
        cout << "Guest found: " << guest->name << ", room number: " << guest->roomNumber << endl;
    }
}

void printGuestListSortedByName() {
    vector<Guest*> guests;
    for (Guest *guest = head; guest != nullptr; guest = guest->next)
        guests.push_back(guest);

    sort(guests.begin(), guests.end(),[](Guest* a,Guest* b){return a->name <b->name;});
    
    cout << "Guest list sorted by name:" << endl;
    for (Guest* guest : guests) {
        cout << guest->name <<"room number: "<< guest->roomNumber << endl;
    }

}

#include <iostream>

using namespace std;

void loadGuestsFromFile(const string& fileName);
void saveGuestsToFile(const string& fileName);
void insertGuest();
void searchGuest();
void printGuestListSortedByName();

int main() {
    string fileName = "hotel.txt";
    int choice;

    do {
        cout << "-----------------------------" << endl;
        cout << "1. Load guests from file" << endl;
        cout << "2. Save guests to file" << endl;
        cout << "3. Insert a new guest" << endl;
        cout << "4. Search for a guest" << endl;
        cout << "5. Print guest list sorted by name" << endl;
        cout << "6. Exit" << endl;
        cout << "-----------------------------" << endl;
        cout << "Enter your choice (1-6): ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1:
                loadGuestsFromFile(fileName);
                break;
            case 2:
                saveGuestsToFile(fileName);
                break;
            case 3:
                insertGuest();
                break;
            case 4:
                searchGuest();
                break;
            case 5:
                printGuestListSortedByName();
                break;
            case 6:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number from 1 to 6." << endl;
                break;
        }

        cout << endl;

    } while (choice != 6);

    return 0;
}

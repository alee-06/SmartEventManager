#include <iostream>
#include<vector>
#include<string>
using namespace std;

class Event {
public:
    int id;
    string name, date, time, type, location;

    Event(int id, string name, string date, string time, string type, string location = "")
        : id(id), name(name), date(date), time(time), type(type), location(location) {}
};

class EventManager {
private:
    vector<Event> events;
    int nextId = 1; // auto increment ID

public:
    void addEvent(string name, string date, string time, string type, string location = "") {
        Event e(nextId++, name, date, time, type, location);
        events.push_back(e);
        cout << "Event added successfully!\n";
    }

    void viewEvents() {
        if (events.empty()) {
            cout << "No events scheduled.\n";
            return;
        }

        cout << "\nID | Name | Date | Time | Type | Location\n";
        cout << "-------------------------------------------\n";
        for (auto &e : events) {
            cout << e.id << " | " << e.name << " | " << e.date << " " << e.time
                 << " | " << e.type << " | " << e.location << endl;
        }
    }

    void deleteEvent(int id) {
        for (auto it = events.begin(); it != events.end(); ++it) {
            if (it->id == id) {
                events.erase(it);
                cout << "Event deleted successfully!\n";
                return;
            }
        }
        cout << "Event with ID " << id << " not found.\n";
    }
};

void showMenu() {
    cout << "\n===== Smart Event Manager =====\n";
    cout << "1. Add Event\n";
    cout << "2. Edit Event\n";
    cout << "3. Delete Event\n";
    cout << "4. View Events\n";
    cout << "5. Search Events\n";
    cout << "6. View Today's Events\n";
    cout << "7. Send Reminders (Admin)\n";
    cout << "8. Statistics (Admin)\n";
    cout << "0. Exit\n";
    cout << "================================\n";
    cout << "Enter your choice: ";
}

int main() {
    EventManager manager;
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Add Event\n";
                string name, date, time, type, location;
                cout << "Enter Event Name: ";
                cin.ignore(); getline(cin, name);
                cout << "Enter Date (DD-MM-YYYY): ";
                getline(cin, date);
                cout << "Enter Time (HH:MM): ";
                getline(cin, time);
                cout << "Enter Type: ";
                getline(cin, type);
                cout << "Enter Location (optional): ";
                getline(cin, location);
                manager.addEvent(name, date, time, type, location);
                break;
            }
            case 2:
                cout << "Edit Event (to be implemented)\n";
                break;
            case 3: {
                int id;
                cout << "Enter Event ID to delete: ";
                cin >> id;
                manager.deleteEvent(id);
                break;
            }
            case 4:
                cout << "View Events (to be implemented)\n";
                manager.viewEvents();                manager.viewEvents();
                break;
            case 5:
                cout << "Search Events (to be implemented)\n";
                break;
            case 6:
                cout << "Today's Events (to be implemented)\n";
                break;
            case 7:
                cout << "Send Reminders (to be implemented)\n";
                break;
            case 8:
                cout << "Statistics (to be implemented)\n";
                break;
            case 0:
                cout << "Exiting Smart Event Manager...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}

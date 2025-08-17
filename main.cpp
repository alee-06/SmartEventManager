#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
using namespace std;

class Event
{
public:
    int id;
    string name, date, time, type, location;

    Event(int id, string name, string date, string time, string type, string location = "")
        : id(id), name(name), date(date), time(time), type(type), location(location) {}
};

class EventManager
{
private:
    vector<Event> events;
    int nextId = 1; // auto increment ID

    // helper function to convert a string to lowercase
    string toLowercase(string text)
    {
        for (char &c : text)
        {
            c = tolower(c); // convert each character
        }
        return text;
    }

public:
    void addEvent(string name, string date, string time, string type, string location = "")
    {
        // normalize input: store name and type in lowercase
        name = toLowercase(name);
        type = toLowercase(type);
        if (hasConflict(date, time))
        {
            string suggestion = suggestNextSlot(date, time);
            cout << "Suggested available slot: " << suggestion << endl;
            return;
        }
        Event e(nextId++, name, date, time, type, location);
        events.push_back(e);
        cout << "Event added successfully!\n";
        saveToFile();
    }

    void viewEvents()
    {
        if (events.empty())
        {
            cout << "No events scheduled.\n";
            return;
        }

        cout << "\nID | Name | Date | Time | Type | Location\n";
        cout << "-------------------------------------------\n";
        for (auto &e : events)
        {
            cout << e.id << " | " << e.name << " | " << e.date << " " << e.time
                 << " | " << e.type << " | " << e.location << endl;
        }
    }

    void deleteEvent(int id)
    {
        for (auto it = events.begin(); it != events.end(); ++it)
        {
            if (it->id == id)
            {
                events.erase(it);
                cout << "Event deleted successfully!\n";
                saveToFile();
                return;
            }
        }
        cout << "Event with ID " << id << " not found.\n";
    }

    void searchEvents(string keyword)
    {
        keyword = toLowercase(keyword); // normalize search keyword
        bool found = false;

        cout << "\nSearch Results:\n";
        cout << "ID | Name | Date | Time | Type | Location\n";
        cout << "-------------------------------------------\n";

        for (auto &e : events)
        {
            if (e.name.find(keyword) != string::npos || e.type.find(keyword) != string::npos)
            {
                cout << e.id << " | " << e.name << " | " << e.date << " " << e.time
                     << " | " << e.type << " | " << e.location << endl;
                found = true;
            }
        }

        if (!found)
        {
            cout << "No events found matching \"" << keyword << "\".\n";
        }
    }

    void editEvent(int id)
    {
        for (auto &e : events)
        {
            if (e.id == id)
            {
                cout << "Editing Event ID " << id << ":\n";
                string input;

                cout << "Enter new name (or press Enter to keep \"" << e.name << "\"): ";
                cin.ignore();
                getline(cin, input);
                if (!input.empty())
                    e.name = toLowercase(input);

                cout << "Enter new date (or press Enter to keep \"" << e.date << "\"): ";
                getline(cin, input);
                if (!input.empty())
                    e.date = input;

                cout << "Enter new time (or press Enter to keep \"" << e.time << "\"): ";
                getline(cin, input);
                if (!input.empty())
                {
                    if (hasConflict(e.date, input))
                    {
                        string suggestion = suggestNextSlot(e.date, input);
                        cout << "Suggested available slot: " << suggestion << endl;
                    }
                    else
                    {
                        e.time = input;
                    }
                }
                cout << "Enter new type (or press Enter to keep \"" << e.type << "\"): ";
                getline(cin, input);
                if (!input.empty())
                    e.type = toLowercase(input);

                cout << "Enter new location (or press Enter to keep \"" << e.location << "\"): ";
                getline(cin, input);
                if (!input.empty())
                    e.location = input;

                cout << "Event updated successfully!\n";
                saveToFile();
                return;
            }
        }
        cout << "Event with ID " << id << " not found.\n";
    }

    void viewTodaysEvents()
    {
        // get current date
        time_t now = time(0);
        tm *ltm = localtime(&now);

        // convert day and month to strings
        string day = to_string(ltm->tm_mday);
        string month = to_string(ltm->tm_mon + 1);
        string year = to_string(1900 + ltm->tm_year);

        // pad with leading zero if length == 1
        if (day.size() == 1)
            day = "0" + day;
        if (month.size() == 1)
            month = "0" + month;

        // final format: dd-mm-yyyy
        string today = day + "-" + month + "-" + year;

        bool found = false;
        cout << "\nToday's Events (" << today << "):\n";
        cout << "ID | Name | Date | Time | Type | Location\n";
        cout << "-------------------------------------------\n";

        for (auto &e : events)
        {
            if (e.date == today)
            {
                cout << e.id << " | " << e.name << " | " << e.date << " " << e.time
                     << " | " << e.type << " | " << e.location << endl;
                found = true;
            }
        }

        if (!found)
        {
            cout << "No events scheduled for today.\n";
        }
    }

    void saveToFile(string filename = "events.csv")
    {
        ofstream fout(filename);
        if (!fout.is_open())
        {
            cout << "Error saving file!\n";
            return;
        }

        for (auto &e : events)
        {
            fout << e.id << "," << e.name << "," << e.date << "," << e.time << ","
                 << e.type << "," << e.location << "\n";
        }
        fout.close();
    }

    void loadFromFile(string filename = "events.csv")
    {
        ifstream fin(filename);
        if (!fin.is_open())
        {
            return; // no file yet
        }

        events.clear();
        string line;
        while (getline(fin, line))
        {
            stringstream ss(line);
            string id, name, date, time, type, location;

            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, date, ',');
            getline(ss, time, ',');
            getline(ss, type, ',');
            getline(ss, location, ',');

            events.push_back(Event(stoi(id), name, date, time, type, location));
            nextId = max(nextId, stoi(id) + 1); // maintain auto increment
        }
        fin.close();
    }

    bool hasConflict(string date, string time)
    {
        for (auto &e : events)
        {
            if (e.date == date && e.time == time)
            {
                cout << "Conflict: Event \"" << e.name
                     << "\" already scheduled at " << time << " on " << date << ".\n";
                return true;
            }
        }
        return false;
    }

    // Suggest nearest available slot (next 30-min intervals)
    string suggestNextSlot(string date, string time)
    {
        int hh, mm;
        sscanf(time.c_str(), "%d:%d", &hh, &mm);

        do
        {
            mm += 30;
            if (mm >= 60)
            {
                mm = 0;
                hh++;
            }
            if (hh >= 24)
                break; // no slots left today

            char buf[6];
            sprintf(buf, "%02d:%02d", hh, mm);
            string newTime = buf;

            if (!hasConflict(date, newTime))
            {
                return newTime;
            }
        } while (hh < 24);

        return "No available slots today.";
    }
};

void showMenu()
{
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

int main()
{
    EventManager manager;
    manager.loadFromFile(); // load existing events at start
    int choice;

    // manager.addEvent("Team Meeting", "17-08-2025", "10:00", "Work", "Conference Room"); test inputs
    // manager.addEvent("Friend's Birthday", "18-08-2025", "19:00", "Personal", "Cafe");
    // manager.addEvent("Hackathon", "25-08-2025", "09:00", "Competition", "Tech Park");

    do
    {
        showMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "Add Event\n";
            string name, date, time, type, location;
            cout << "Enter Event Name: ";
            cin.ignore();
            getline(cin, name);
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
        {
            int id;
            cout << "Enter Event ID to edit: ";
            cin >> id;
            manager.editEvent(id);
            break;
        }
        case 3:
        {
            int id;
            cout << "Enter Event ID to delete: ";
            cin >> id;
            manager.deleteEvent(id);
            break;
        }
        case 4:
            cout << "View Events\n";
            manager.viewEvents();
            break;
        case 5:
        {
            cout << "Enter keyword to search (name/type): ";
            cin.ignore();
            string keyword;
            getline(cin, keyword);
            manager.searchEvents(keyword);
            break;
        }
        case 6:
            cout << "Today's Events\n";
            manager.viewTodaysEvents();
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
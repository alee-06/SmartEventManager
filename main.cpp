#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

class Event
{
public:
    int id;
    string name, date, time, type, location;

    Event(int id, string name, string date, string time, string type, string location = "")
        : id(id), name(name), date(date), time(time), type(type), location(location) {}
};

struct User {
    string username;
    string password;
    string role; // "admin" or "user"
};

User login() {
    string username, password;
    cout << "===== Login =====\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    // For now, hardcode accounts
    if (username == "admin" && password == "admin123") {
        cout << "Welcome Admin!\n";
        return {username, password, "admin"};
    }
    else {
        cout << "Welcome User!\n";
        return {username, password, "user"};
    }
}

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
                getline(cin, input);
                if (!input.empty())
                    e.name = toLowercase(input);

                cout << "Enter new date (or press Enter to keep \"" << e.date << "\"): ";
                getline(cin, input);
                if (!input.empty())
                {
                    while (!isValidDate(input))
                    {
                        cout << "Invalid date format! Please enter again (DD-MM-YYYY): ";
                        getline(cin, input);
                    }
                    e.date = input;
                }
                cout << "Enter new time (or press Enter to keep \"" << e.time << "\"): ";
                getline(cin, input);
                if (!input.empty())
                {
                    while (!isValidTime(input))
                    {
                        cout << "Invalid time format! Please enter again (HH:MM): ";
                        getline(cin, input);
                    }
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
    bool isValidDate(const string &date)
    {
        if (date.size() != 10 || date[2] != '-' || date[5] != '-')
            return false;

        int day = stoi(date.substr(0, 2));
        int month = stoi(date.substr(3, 2));
        int year = stoi(date.substr(6, 4));

        if (month < 1 || month > 12)
            return false;

        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        // leap year check
        if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
            daysInMonth[1] = 29;

        if (day < 1 || day > daysInMonth[month - 1])
            return false;

        return true;
    }

    bool isValidTime(const string &time)
    {
        if (time.size() != 5 || time[2] != ':')
            return false;

        int hour = stoi(time.substr(0, 2));
        int minute = stoi(time.substr(3, 2));

        return (hour >= 0 && hour < 24 && minute >= 0 && minute < 60);
    }

    void viewDayEvents(const string &date)
    {
        vector<Event> dayEvents;

        // collect events for that date
        for (auto &ev : events)
        {
            if (ev.date == date)
                dayEvents.push_back(ev);
        }

        if (dayEvents.empty())
        {
            cout << "No events found for " << date << endl;
            return;
        }

        // sort by time (HH:MM)
        sort(dayEvents.begin(), dayEvents.end(), [](const Event &a, const Event &b)
             { return a.time < b.time; });

        cout << "\nEvents on " << date << ":\n";
        for (auto &ev : dayEvents)
        {
            cout << "ID: " << ev.id
                 << " | Name: " << ev.name
                 << " | Time: " << ev.time
                 << " | Type: " << ev.type
                 << " | Location: " << ev.location << endl;
        }
    }
};

void showMenu(const string &role)
{
    cout << "\n===== Smart Event Manager =====\n";
    cout << "1. View Events\n";
    cout << "2. Search Events\n";
    cout << "3. View Today's Events\n";
    cout << "4. View a specific Date's Events\n";

    if (role == "admin") {
        cout << "5. Add Event\n";
        cout << "6. Edit Event\n";
        cout << "7. Delete Event\n";
        cout << "8. Send Reminders\n";
        cout << "9. Statistics\n";
    }

    cout << "0. Exit\n";
    cout << "================================\n";
    cout << "Enter your choice: ";
}


int main()
{
    EventManager manager;
    manager.loadFromFile(); // load events
    User currentUser = login();
    int choice;

    do
    {
        showMenu(currentUser.role);
        cin >> choice;

        if (currentUser.role == "admin")
        {
            switch (choice)
            {
            case 1: manager.viewEvents(); break;
            case 2: {
                cout << "Enter keyword: ";
                cin.ignore();
                string keyword;
                getline(cin, keyword);
                manager.searchEvents(keyword);
                break;
            }
            case 3: manager.viewTodaysEvents(); break;
            case 4: {
                string date;
                cout << "Enter date (DD-MM-YYYY): ";
                cin >> date;
                manager.viewDayEvents(date);
                break;
            }
            case 5: {
                cout << "Add Event\n";
                string name, date, time, type, location;
                cin.ignore();
                cout << "Enter Event Name: "; getline(cin, name);
                cout << "Enter Date (DD-MM-YYYY): "; getline(cin, date);
                while (!manager.isValidDate(date)) {
                    cout << "Invalid! Enter again: "; getline(cin, date);
                }
                cout << "Enter Time (HH:MM): "; getline(cin, time);
                while (!manager.isValidTime(time)) {
                    cout << "Invalid! Enter again: "; getline(cin, time);
                }
                cout << "Enter Type: "; getline(cin, type);
                cout << "Enter Location: "; getline(cin, location);
                manager.addEvent(name, date, time, type, location);
                break;
            }
            case 6: {
                int id;
                cout << "Enter Event ID to edit: ";
                cin >> id;
                manager.editEvent(id);
                break;
            }
            case 7: {
                int id;
                cout << "Enter Event ID to delete: ";
                cin >> id;
                manager.deleteEvent(id);
                break;
            }
            case 8: cout << "Send Reminders (to be implemented)\n"; break;
            case 9: cout << "Statistics (to be implemented)\n"; break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
            }
        }
        else // user mode
        {
            switch (choice)
            {
            case 1: manager.viewEvents(); break;
            case 2: {
                cout << "Enter keyword: ";
                cin.ignore();
                string keyword;
                getline(cin, keyword);
                manager.searchEvents(keyword);
                break;
            }
            case 3: manager.viewTodaysEvents(); break;
            case 4: {
                string date;
                cout << "Enter date (DD-MM-YYYY): ";
                cin >> date;
                manager.viewDayEvents(date);
                break;
            }
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
            }
        }

    } while (choice != 0);

    return 0;
}
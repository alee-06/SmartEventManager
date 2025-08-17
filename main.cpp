#include <iostream>
using namespace std;

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
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Add Event (to be implemented)\n";
                break;
            case 2:
                cout << "Edit Event (to be implemented)\n";
                break;
            case 3:
                cout << "Delete Event (to be implemented)\n";
                break;
            case 4:
                cout << "View Events (to be implemented)\n";
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

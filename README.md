# Smart Event Manager (CLI-Based)

A **Command-Line Interface (CLI) Event Manager** built in **C++** using **Object-Oriented Programming (OOP)** and **file handling concepts**.
This project was developed as part of the ACM Technical Team Recruitment Task.

The system allows users to **schedule, manage, and organize events**, with support for **conflict detection, editing, searching, and admin-only controls**. Events are stored persistently in a CSV file for reuse across sessions.

---

## 🚀 Features Implemented

### ✅ Core Features

* **Add Event**

  * Inputs: Name, Date (`DD-MM-YYYY`), Time (`HH:MM`), Type, Location (optional)
  * Date & Time validation
  * Prevents scheduling conflicts
  * Suggests next available slot if conflict detected

* **Edit Event**

  * Modify any field (name, date, time, type, location) by **Event ID**
  * Validates input and checks for conflicts when changing date/time

* **Delete Event**

  * Remove an event using its **Event ID**

* **View Events**

  * **All Events** (chronological order)
  * **Day View**: Display events for a specific date
  * **Today’s Events**: Show events for the current system date

* **Search Events**

  * Search by keyword (**name/type**) – case-insensitive

* **Conflict Detection**

  * Alerts when an event already exists at the same date/time
  * Suggests nearest available **30-minute time slot**

* **Persistent Storage**

  * Events stored in **CSV (`events.csv`)** for persistence
  * Automatically loads/saves events between sessions

* **Admin Control**

  * Admin login (`admin/admin123`)
  * Admin has exclusive access to:

    * Add/Edit/Delete events
    * View Statistics (event analytics)

* **Statistics Module**

  * Events in the last 7 days
  * Event frequency by type
  * Most common event time slot

* **Mock Reminder System**

  * Added as a **demonstration feature** (not full email integration)
  * Uses a **CSV file (`emails.csv`)** containing attendees' emails
  * When admin selects **“Send Reminders”**, the system **simulates sending emails** by printing messages in the console
  * Serves as a placeholder for future integration with **SMTP libraries** or APIs (Gmail/Outlook)

---

## ❌ Features Not Implemented

* Sending **real email reminders** to attendees
* Optional bonus features (ASCII timeline, recurring events, undo, SQLite, timezone support, etc.)

---

## 🖥️ CLI Menu

### User Menu

```
===== Smart Event Manager =====
1. View Events
2. Search Events
3. View Today's Events
4. View a specific Date's Events
0. Exit
```

### Admin Menu

```
===== Smart Event Manager =====
1. View Events
2. Search Events
3. View Today's Events
4. View a specific Date's Events
5. Add Event
6. Edit Event
7. Delete Event
8. Send Reminders (mock implementation)
9. Statistics
0. Exit
```

---

## 📂 Project Structure

```
SmartEventManager/
│── main.cpp         # Main program (all logic)
│── events.csv       # Persistent storage for events
│── emails.csv       # Mock attendee list for reminders
│── README.md        # Documentation
```

---

## ⚡ How to Run

### 1. Clone the repository

```bash
git clone https://github.com/alee-06/SmartEventManager.git
cd SmartEventManager
```

### 2. Compile the program

```bash
g++ main.cpp -o SmartEventManager
```

### 3. Run the executable

```bash
./SmartEventManager
```

---

## 📌 Sample Usage

### Login

```
===== Login =====
Username: admin
Password: admin123
Welcome Admin!
```

### Add Event (Admin only)

```
Enter Event Name: Hackathon
Enter Date (DD-MM-YYYY): 18-08-2025
Enter Time (HH:MM): 10:00
Enter Type: Workshop
Enter Location: Lab 1
Event added successfully!
```

### Conflict Detection Example

```
Conflict: Event "Hackathon" already scheduled at 10:00 on 18-08-2025.
Suggested available slot: 10:30
```

### Mock Reminder Example

```
===== Sending Reminders =====
Sending reminder to: alice@example.com
Sending reminder to: bob@example.com
Sending reminder to: charlie@example.com
All reminders sent successfully (simulation).
```

---

## 📊 Example Statistics Output

```
===== Event Statistics =====
Events in last 7 days: 3

Events by Type:
  Workshop: 2
  Meeting: 1

Most common event time slot: 10:00 (2 events)
```

---

## 🛠️ Tech Stack

* **Language:** C++
* **Concepts Used:** OOP (Classes, Structs, Encapsulation), File Handling (CSV), Vectors, STL Algorithms
* **Storage:** CSV file (`events.csv` + `emails.csv` for mock reminders)

---

## 📌 Notes & Challenges

* Initially faced issues with **date/time validation** – resolved by implementing helper functions `isValidDate()` and `isValidTime()`.
* Implementing **conflict detection** required careful iteration through stored events and adding a **suggestion algorithm** for nearest available slots.
* Ensured **modularity** by structuring functionality inside an `EventManager` class.
* Added a **mock reminder system** to simulate notifications without actual email integration.

---

## ✅ Current Status

This project fulfills **all core requirements** except the **real event reminders** module.
A **mock implementation** for reminders has been added to simulate the functionality.

Future improvements may include:

* Real Email/SMS notifications
* SQLite-based backend
* Recurring events
* Undo functionality

---

✨ **Author:** [Ali (alee-06)](https://github.com/alee-06)

---
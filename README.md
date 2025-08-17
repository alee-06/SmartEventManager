# Smart Event Manager (CLI-Based)

A Command-Line Interface (CLI) Event Manager built in C++ using Object-Oriented Programming (OOP) and file handling concepts.
This project was developed as part of the ACM Technical Team Recruitment Task.

The system allows users to schedule, manage, and organize events, with support for conflict detection, editing, searching, and admin-only controls. Events are stored persistently in a CSV file for reuse across sessions.

🚀 Features Implemented
✅ Core Features

Add Event

Inputs: Name, Date (DD-MM-YYYY), Time (HH:MM), Type, Location (optional)

Date & Time validation

Prevents scheduling conflicts

Suggests next available slot if conflict detected

Edit Event

Modify any field (name, date, time, type, location) by Event ID

Validates input and checks for conflicts when changing date/time

Delete Event

Remove an event using its Event ID

View Events

All Events (chronological order)

Day View: Display events for a specific date

Today’s Events: Show events for the current system date

Search Events

Search by keyword (name/type) – case-insensitive

Conflict Detection

Alerts when an event already exists at the same date/time

Suggests nearest available 30-minute time slot

Persistent Storage

Events stored in CSV (events.csv) for persistence

Automatically loads/saves events between sessions

Admin Control

Admin login (admin/admin123)

Admin has exclusive access to:

Add/Edit/Delete events

View Statistics (event analytics)

Statistics Module

Events in the last 7 days

Event frequency by type

Most common event time slot

❌ Features Not Implemented

Sending email reminders to attendees

Optional bonus features (ASCII timeline, recurring events, undo, SQLite, timezone support, etc.)

🖥️ CLI Menu
User Menu
# Bahria Transport Management System

A standalone, console-based application written in object-oriented C++ designed to automate student transport registration, bus scheduling, allocation, and roster tracking at Bahria University. This system aims to eliminate manual data inaccuracies and replace paper-based bus tracking workflows with a sub-second optimized command-line experience.

## 📋 Project Context
* **Course:** SEN-120: Introduction to Software Engineering
* **Instructor:** Rafia Mumtaz
* **Authors/Engineers:** Minahil Khushid Chaudhry, Zunaira, Khaula Khalid
* **Development Term:** Spring 2025

---

## 🚀 Key Features

* **Vehicle & Route Management:** Allows administrators to register transit vehicles, map routes, and hardcode distinct service stops.
* **Smart Student Allocation:** Validates student registration via fee status checkpoints. Matches requested stops dynamically against known routes to offer matching vehicle picks.
* **Attendance Ledger:** Tracks a rolling 30-day attendance history loop (`P` records) directly mapped within the nested individual student profiles.
* **Roster Generation:** Instantly outputs complete manifests detailing lists of students assigned onto specific active campus vehicles.

---

## 🛠️ Architecture & OOP Design

The core system architecture adopts a clean modular approach following standard Object-Oriented Programming (OOP) paradigms:

* **`Person` (Abstract Base Class):** Enforces interface structure via the pure virtual function `ViewDetails()`.
* **`Student` (Derived Class):** Inherits from `Person`. Encapsulates specialized attributes like fee verification status, dynamic vehicle pointer assignments, and attendance logs.
* **`Vehicle`:** Handles state properties concerning individual units (routes, capacity checks, fixed arrays of 5 distinct destination stops, and registered student references).
* **`Manage` (System Controller):** Functions as the primary execution engine. Implements robust object management, memory cleanup loops via its destructor, string inputs with robust workspace streaming (`getline`), and formatted UI alignments using `<iomanip>`.

---

## ⚙️ Compilation & Deployment Constraints

Per the project requirements specification, this app is built as a lightweight context manager mapping in-memory records exclusively to optimize response latency to under 2 seconds.

### Prerequisites
* A standard PC running Windows OS.
* A legacy C++ compiler supporting the standard library headers (`GCC` or `Visual Studio C++ compiler toolsets`).

### Local Terminal Build Steps
1. Open your standard terminal inside the development workspace folder.
2. Compile the source file using `g++`:
   ```bash
   g++ -o TransportSystem OOP_Project_045_095.cpp

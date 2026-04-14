# 🎮 Arcade System (C++)

## 📌 Overview

The Arcade System is a modular, object-oriented C++ application that simulates the core functionality of a real-world arcade. It supports player registration, token purchasing, machine gameplay, and leaderboard tracking with persistent storage.

This project demonstrates strong use of data structures, clean architecture, and file handling in C++.
As well as:

* Backend logic design
* Clean C++ coding practices
* Problem-solving with real-world systems

---

## 🚀 Features

* **Player Management**: Register players with unique IDs and track token balances.
* **Token System**: Players can purchase tokens through token booths.
* **Arcade Machines**: Multiple machines with different play costs.
* **Gameplay Simulation**: Players spend tokens to play and generate scores.
* **Leaderboard**: Automatically ranks top scores using efficient data structures.
* **File Persistence**: Save and load leaderboard data from files.

---

## 🧠 Concepts Used

* Object-Oriented Programming (OOP)
* Smart Pointers (`std::unique_ptr`)
* STL Containers (`map`, `vector`, `multiset`)
* File I/O (`fstream`)
* Encapsulation and Modular Design

---

## 📂 Project Structure

```
arcade.cc        # Core system logic (players, machines, gameplay)
machine.cc       # Machine class implementation
leaderboard.cc   # Leaderboard management and file operations

Arcade.h         # Manager class coordinating players, machines, and transactions
Machine.h        # Base machine class
Shooter.h        # Example derived machine (inheritance/polymorphism)
Puzzle.h         # Example derived machine (inheritance/polymorphism)
Player.h         # Manages player state and wallet logic
TokenBooth.h     # Handles token distribution logic
Leaderboard.h    # Ranking system and file persistence logic
```

---

## ⚙️ How It Works

1. Register players in the system.
2. Add arcade machines and token booths.
3. Players purchase tokens.
4. Players play machines using tokens.
5. Scores are recorded and ranked in the leaderboard.
6. Leaderboard can be saved or loaded from a file.

---

## 🛠️ Compilation & Run

```bash
g++ -std=c++17 arcade.cc machine.cc leaderboard.cc -o arcade
./arcade
```

---

## 👨‍💻 Author

**Rawad Abboud**

Developed as a C++ course project to demonstrate system design, data structures, and real-world simulation skills.

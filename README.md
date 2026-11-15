# Skill-Based Hackathon Team Builder

A menu-driven C++ console application designed to automate hackathon team formation by matching participants based on their technical skills, role balance, and interpersonal compatibility.

## Project Overview

Forming teams manually during hackathons often results in unbalanced groups where some teams have too many developers and no designers or presenters. This system registers participants, classifies them into primary roles based on their skill scores, manages waiting queues, evaluates member compatibility using a graph, ranks formed squads via a Max-Heap, and saves team records to disk.

## Objectives

- Classify participants automatically into **Developer**, **Designer**, or **Pitch Lead** based on their highest skill score.
- Form balanced 6-member squads in a strict **2:2:2** role ratio using fair first-come-first-served (FIFO) allocation.
- Handle role shortages with live alerts and allocate leftover participants into hybrid squads.
- Evaluate pairwise team compatibility using a Graph Adjacency Matrix to calculate a team synergy score.
- Maintain a real-time leaderboard and persistent disk storage for formed teams.

## Technologies & Data Structures Used

- **Language:** C++ (Standard Template Library: `<iostream>`, `<string>`, `<queue>`, `<fstream>`)
- **Object-Oriented Programming (OOP):** `Participant` class for encapsulation and automated role assignment.
- **Binary Search Tree (BST):** Stores student records indexed by roll number for $O(\log N)$ search, ascending sorted display via in-order traversal, and safe memory cleanup via post-order traversal on exit.
- **FIFO Queues:** Three separate role queues (`devQ`, `designQ`, `pitchQ`) to ensure fair team selection.
- **Graph (2D Adjacency Matrix):** Stores pairwise compatibility scores (1–10) between students to compute total team synergy.
- **Max-Heap:** Array-based priority structure keeping the highest-scoring team at the root (`heap[0]`) for $O(1)$ top-rank access.
- **File Handling:** Two-way persistence in `squad.txt` using `ofstream` (append mode) and `ifstream` (history viewer).

## Key Features (Menu Options)

1. **Participant Registration:** Registers students with duplicate roll number prevention, BST indexing, and queue insertion.
2. **Queue Status & Shortage Alert:** Displays current queue counts and exact missing candidates required for the next 2:2:2 team.
3. **Balanced 2:2:2 Squad Formation:** Pops 2 Developers, 2 Designers, and 2 Pitch Leads, calculates `Skill + Synergy` score, updates the leaderboard, and saves to `squad.txt`.
4. **Fast Roll Number Search:** Searches any student record in $O(\log N)$ time using BST lookup.
5. **Sorted Student Directory:** Uses BST in-order traversal to list all registered participants in ascending roll-number order.
6. **Real-Time Leaderboard:** Displays the top-ranked squad at the Max-Heap root along with all formed teams.
7. **Compatibility Graph Management:** Allows viewing and adding pairwise synergy links (1–10) between participants.
8. **Leftover Candidate Allocation:** Groups remaining candidates in the queues into a Hybrid Leftover Squad.
9. **Saved Squad History:** Reads and displays previously saved teams directly from `squad.txt`.
10. **One-Click Demo Loader:** Loads 9 sample students and pre-configured compatibility edges for quick testing.

## Team Members & Module Distribution (Team Binary Minds)

- **Mujtaba Hasan (Team Lead):** OOP `Participant` model, role classification logic, and Binary Search Tree (`insertBST`, `searchBST`, `inOrderBST`, `deleteBST`).
- **Manmeet Kaur:** FIFO waiting queues, 2:2:2 squad engine, exact role shortage alerts, and leftover hybrid team allocation.
- **Tanishk Vashisth:** 2D Graph Adjacency Matrix for team synergy calculation and array-based Max-Heap leaderboard.
- **Mohd Aszad:** Two-way file persistence (`squad.txt` write/read), interactive console menu, and demo dataset loader.

## Project Files

- `main.cpp` — Complete Phase-3 source code containing all data structures and menu logic.
- `squad.txt` — Auto-generated text file storing formed team rosters and scores.

## How to Compile and Run

1. Clone or download this repository:
   ```bash
   git clone [https://github.com/mujtaba-hsn/Skill-Based-Hackathon-Team-Builder-.git](https://github.com/mujtaba-hsn/Skill-Based-Hackathon-Team-Builder-.git)

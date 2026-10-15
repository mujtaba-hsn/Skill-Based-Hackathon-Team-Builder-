#include <iostream>
#include <string>
#include <queue>
#include <fstream>

using namespace std;

// ============================================================================
// 1. MODULE: MUJTABA HASAN (Team Lead)
// Core OOP Architecture (Participant Class) & Binary Search Tree (BST)
// ============================================================================

class Participant {
public:
    string name;
    string rollNo;
    string role;
    int coding, design, pitch;
    int primaryScore;

    Participant() {}

    // Constructor: Auto-assigns role based on highest score
    Participant(string n, string r, int c, int d, int p) {
        name = n;
        rollNo = r;
        coding = c;
        design = d;
        pitch = p;

        if (coding >= design && coding >= pitch) {
            role = "Developer";
            primaryScore = coding;
        } else if (design >= coding && design >= pitch) {
            role = "Designer";
            primaryScore = design;
        } else {
            role = "Pitch Lead";
            primaryScore = pitch;
        }
    }

    void display() {
        cout << "Name: " << name << " | Roll No: " << rollNo 
             << " | Role: " << role << " | Score: " << primaryScore << endl;
    }
};

// Standard BST Node Structure
struct Node {
    Participant data;
    Node* left;
    Node* right;
};

// Helper function to allocate memory for a new BST node
Node* createNode(Participant p) {
    Node* newNode = new Node();
    newNode->data = p;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Recursive BST Insertion (Left child < Root < Right child)
Node* insertBST(Node* root, Participant p) {
    if (root == NULL) {
        return createNode(p);
    }
    if (p.rollNo < root->data.rollNo) {
        root->left = insertBST(root->left, p);
    } else {
        root->right = insertBST(root->right, p);
    }
    return root;
}

// O(log N) Search by Roll Number
void searchBST(Node* root, string roll) {
    if (root == NULL) {
        cout << "\n[BST Search] Student with Roll No " << roll << " not found!\n";
        return;
    }
    if (root->data.rollNo == roll) {
        cout << "\n[BST Search Hit in O(log N)] Student Found:\n";
        root->data.display();
        return;
    }
    if (roll < root->data.rollNo) {
        searchBST(root->left, roll);
    } else {
        searchBST(root->right, roll);
    }
}


// ============================================================================
// 2. MODULE: MANMEET
// Linear DSA: FIFO Queues & 6-Member Balanced Team Engine (2:2:2 Rule)
// ============================================================================

struct Team {
    int teamId;
    Participant members[6]; // Fixed 6-member squad (2 Devs + 2 Designers + 2 Pitch Leads)
    int totalScore;
};

// Three FIFO role queues
queue<Participant> devQueue;
queue<Participant> designQueue;
queue<Participant> pitchQueue;

int teamCounter = 1;

bool checkCanFormTeam() {
    if (devQueue.size() >= 2 && designQueue.size() >= 2 && pitchQueue.size() >= 2) {
        return true;
    }
    return false;
}

Team formTeam() {
    Team t;
    t.teamId = teamCounter++;
    t.totalScore = 0;

    // Dequeue 2 Developers (FIFO)
    for (int i = 0; i < 2; i++) {
        t.members[i] = devQueue.front();
        t.totalScore = t.totalScore + devQueue.front().primaryScore;
        devQueue.pop();
    }
    // Dequeue 2 Designers (FIFO)
    for (int i = 2; i < 4; i++) {
        t.members[i] = designQueue.front();
        t.totalScore = t.totalScore + designQueue.front().primaryScore;
        designQueue.pop();
    }
    // Dequeue 2 Pitch Leads (FIFO)
    for (int i = 4; i < 6; i++) {
        t.members[i] = pitchQueue.front();
        t.totalScore = t.totalScore + pitchQueue.front().primaryScore;
        pitchQueue.pop();
    }

    return t;
}


// ============================================================================
// 3. MODULE: TANISHK
// Non-Linear DSA: Array-Based Max-Heap for Real-Time Leaderboard
// ============================================================================

Team heap[50]; // Fixed array representation of binary heap
int heapSize = 0;

void insertHeap(Team t) {
    heap[heapSize] = t;
    int i = heapSize;
    heapSize++;

    // Heapify-Up algorithm to maintain max-heap property
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[i].totalScore > heap[parent].totalScore) {
            Team temp = heap[i];
            heap[i] = heap[parent];
            heap[parent] = temp;
            i = parent;
        } else {
            break;
        }
    }
}

void showLeaderboard() {
    if (heapSize == 0) {
        cout << "\nLeaderboard is empty. Form a team first (Option 3)!\n";
        return;
    }
    cout << "\n============================================\n";
    cout << "   REAL-TIME TEAM LEADERBOARD (MAX-HEAP)    \n";
    cout << "============================================\n";
    cout << "Rank 1 (Root Node in O(1)): Team #" << heap[0].teamId 
         << " with Score: " << heap[0].totalScore << "/60\n";
    cout << "--------------------------------------------\n";
    for (int i = 0; i < heapSize; i++) {
        cout << "Rank " << (i + 1) << " -> Team #" << heap[i].teamId 
             << " | Total Score: " << heap[i].totalScore << "/60" << endl;
    }
}


// ============================================================================
// 4. MODULE: ASZAD
// Persistence Layer: File Handling (fstream) & Console Interface
// ============================================================================

void saveTeamToFile(Team t) {
    ofstream file("squad.txt", ios::app);
    file << "=== Team #" << t.teamId << " (Total Score: " << t.totalScore << ") ===\n";
    for (int i = 0; i < 6; i++) {
        file << t.members[i].name << " (" << t.members[i].role << ") - Roll: " << t.members[i].rollNo << "\n";
    }
    file << "====================================\n\n";
    file.close();
}


// ============================================================================
// MAIN APPLICATION ENGINE
// ============================================================================

int main() {
    Node* root = NULL; // Root pointer for BST
    int choice;

    do {
        cout << "\n=========================================\n";
        cout << " SKILL-BASED HACKATHON TEAM BUILDER (40%) \n";
        cout << " Team: Binary Minds (Phase-2 Prototype)   \n";
        cout << "=========================================\n";
        cout << "1. Register Student\n";
        cout << "2. Check Queue Status (FIFO)\n";
        cout << "3. Form 6-Member Team (2:2:2 Rule)\n";
        cout << "4. Search Student by Roll No (BST)\n";
        cout << "5. Show Leaderboard (Max-Heap)\n";
        cout << "6. Load 6 Test Students (Instant Demo)\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, roll;
                int c, d, p;
                cout << "Enter Name: "; cin >> name;
                cout << "Enter Roll No: "; cin >> roll;
                cout << "Enter Scores (Coding, Design, Pitch): "; cin >> c >> d >> p;

                Participant student(name, roll, c, d, p);
                root = insertBST(root, student);

                if (student.role == "Developer"){
                devQueue.push(student);
                }
                else if (student.role == "Designer"){
                designQueue.push(student);
                }
                else{
                pitchQueue.push(student);
                }
                cout << "[Success] Student Registered! Assigned Role: " << student.role << endl;
                break;
            }

            case 2:
                cout << "\n--- WAITING QUEUE STATUS ---\n";
                cout << "Developers in Queue : " << devQueue.size() << endl;
                cout << "Designers in Queue  : " << designQueue.size() << endl;
                cout << "Pitch Leads in Queue: " << pitchQueue.size() << endl;
                break;

            case 3:
                if (!checkCanFormTeam()) {
                    cout << "\n[Notice] Cannot form team! Minimum 2 students required in each role queue.\n";
                } else {
                    Team newTeam = formTeam();
                    insertHeap(newTeam);
                    saveTeamToFile(newTeam);

                    cout << "\n>>> TEAM #" << newTeam.teamId << " FORMED SUCCESSFULLY! <<<\n";
                    cout << "Total Base Score: " << newTeam.totalScore << "/60\n";
                    cout << "Record saved permanently to 'squad.txt'\n";
                    cout << "Assigned Squad Members:\n";
                    for (int i = 0; i < 6; i++) {
                        cout << " - " << newTeam.members[i].name << " (" 
                             << newTeam.members[i].role << ") | Roll: " 
                             << newTeam.members[i].rollNo << endl;
                    }
                }
                break;

            case 4: {
                string roll;
                cout << "Enter Roll No to search in BST: ";
                cin >> roll;
                searchBST(root, roll);
                break;
            }

            case 5:
                showLeaderboard();
                break;

            case 6: {
                // Pre-configured test dataset for quick evaluation demo
                Participant s1("Arjun", "101", 9, 3, 2);
                Participant s2("Rohan", "102", 8, 4, 3);
                Participant s3("Kavya", "103", 2, 9, 4);
                Participant s4("Priya", "104", 3, 8, 5);
                Participant s5("Aman",  "105", 2, 3, 9);
                Participant s6("Sara",  "106", 4, 2, 8);

                Participant list[6] = {s1, s2, s3, s4, s5, s6};

                for (int i = 0; i < 6; i++) {
                    root = insertBST(root, list[i]);
                    if (list[i].role == "Developer")
                    devQueue.push(list[i]);
                    else if (list[i].role == "Designer")
                    designQueue.push(list[i]);
                    else
                    pitchQueue.push(list[i]);
                }
                cout << "\n[Demo Loaded] 6 test students added across queues (2 Devs, 2 Designers, 2 Pitch Leads)!\n";
                break;
            }

            case 7:
                cout << "Exiting system. Best of luck for Phase-2!\n";
                break;

            default:
                cout << "Invalid choice! Please enter a value between 1 and 7.\n";
        }

    } while (choice != 7);

    return 0;
}
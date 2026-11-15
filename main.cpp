#include <iostream>
#include <string>
#include <queue>
#include <fstream>

using namespace std;

// --- Module 1 (Part A): Mujtaba Hasan - OOP Participant Model & Role Assignment ---
class Participant {
public:
    string name;
    int rollNo;
    string role;
    int devScore;
    int designScore;
    int pitchScore;

    Participant() {
        name = "";
        rollNo = 0;
        role = "";
        devScore = 0;
        designScore = 0;
        pitchScore = 0;
    }

    Participant(string n, int r, int d, int des, int p) {
        name = n;
        rollNo = r;
        devScore = d;
        designScore = des;
        pitchScore = p;
        assignRole();
    }

    void assignRole() {
        if (devScore >= designScore && devScore >= pitchScore) {
            role = "Developer";
        } else if (designScore >= devScore && designScore >= pitchScore) {
            role = "Designer";
        } else {
            role = "Pitch Lead";
        }
    }

    int getBestScore() {
        if (role == "Developer") return devScore;
        if (role == "Designer") return designScore;
        return pitchScore;
    }
};

struct Team {
    int teamID;
    string type;
    Participant members[6];
    int memberCount;
    int skillScore;
    int synergyScore;
    int totalScore;
};

// --- Module 1 (Part B): Mujtaba Hasan - Binary Search Tree (Search, In-Order & Cleanup) ---
struct Node {
    Participant data;
    Node* left;
    Node* right;
};

Node* createNode(Participant p) {
    Node* newNode = new Node();
    newNode->data = p;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertBST(Node* root, Participant p) {
    if (root == NULL) {
        return createNode(p);
    }
    if (p.rollNo < root->data.rollNo) {
        root->left = insertBST(root->left, p);
    } else if (p.rollNo > root->data.rollNo) {
        root->right = insertBST(root->right, p);
    }
    return root;
}

Node* searchBST(Node* root, int roll) {
    if (root == NULL || root->data.rollNo == roll) {
        return root;
    }
    if (roll < root->data.rollNo) {
        return searchBST(root->left, roll);
    }
    return searchBST(root->right, roll);
}

// In-order traversal prints students sorted by roll number
void inOrderBST(Node* root) {
    if (root == NULL) return;
    inOrderBST(root->left);
    cout << "Roll No: " << root->data.rollNo
         << " | Name: " << root->data.name
         << " | Role: " << root->data.role
         << " (Scores: " << root->data.devScore << "/"
         << root->data.designScore << "/" << root->data.pitchScore << ")\n";
    inOrderBST(root->right);
}

// Post-order traversal frees dynamically allocated BST nodes
int deleteBST(Node* root) {
    if (root == NULL) return 0;
    int leftCount = deleteBST(root->left);
    int rightCount = deleteBST(root->right);
    delete root;
    return leftCount + rightCount + 1;
}

// --- Module 2: Tanishk Vashisth - Graph Compatibility Matrix & Max-Heap Leaderboard ---
int studentRolls[50];
int totalStudents = 0;
int graph[50][50];

int getStudentIndex(int roll) {
    for (int i = 0; i < totalStudents; i++) {
        if (studentRolls[i] == roll) {
            return i;
        }
    }
    return -1;
}

void registerInGraph(int roll) {
    if (getStudentIndex(roll) == -1 && totalStudents < 50) {
        studentRolls[totalStudents] = roll;
        totalStudents++;
    }
}

void addSynergyEdge(int roll1, int roll2, int score) {
    int u = getStudentIndex(roll1);
    int v = getStudentIndex(roll2);
    if (u == -1 || v == -1 || u == v) {
        cout << "Error: Invalid roll numbers.\n";
        return;
    }
    graph[u][v] = score;
    graph[v][u] = score;
    cout << "Compatibility between Roll " << roll1 << " and Roll " << roll2 << " saved (" << score << "/10).\n";
}

int calculateTeamSynergy(Participant members[], int count) {
    int synergy = 0;
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            int u = getStudentIndex(members[i].rollNo);
            int v = getStudentIndex(members[j].rollNo);
            if (u != -1 && v != -1 && graph[u][v] > 0) {
                synergy += graph[u][v];
            } else if (members[i].role != members[j].role) {
                synergy += 2;
            }
        }
    }
    return synergy;
}

void displayGraphMatrix() {
    cout << "\n--- Student Compatibility Links ---\n";
    bool found = false;
    for (int i = 0; i < totalStudents; i++) {
        for (int j = i + 1; j < totalStudents; j++) {
            if (graph[i][j] > 0) {
                cout << "Roll " << studentRolls[i] << " <-> Roll " << studentRolls[j]
                     << " : " << graph[i][j] << "/10\n";
                found = true;
            }
        }
    }
    if (!found) {
        cout << "No compatibility links added yet.\n";
    }
}

// Array-based Max-Heap for team leaderboard
Team heap[50];
int heapSize = 0;

void heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].totalScore > heap[parent].totalScore) {
            Team temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;
            index = parent;
        } else {
            break;
        }
    }
}

void insertHeap(Team t) {
    heap[heapSize] = t;
    heapifyUp(heapSize);
    heapSize++;
}

void displayLeaderboard() {
    cout << "\n--- Max-Heap Team Leaderboard ---\n";
    if (heapSize == 0) {
        cout << "No teams formed yet.\n";
        return;
    }
    cout << "Top Ranked Team (Root): Team " << heap[0].teamID << " (" << heap[0].type << ")"
         << " | Total Score: " << heap[0].totalScore
         << " (Skill: " << heap[0].skillScore << " + Synergy: " << heap[0].synergyScore << ")\n";
    cout << "---------------------------------\n";

    for (int i = 0; i < heapSize; i++) {
        cout << "Index [" << i << "] -> Team " << heap[i].teamID
             << " (" << heap[i].type << ")"
             << " | Total: " << heap[i].totalScore << "\n";
    }
}

// --- Module 3: Mohd Aszad - File Handling (ofstream Write & ifstream Read) ---
void saveTeamToFile(Team t) {
    ofstream out("squad.txt", ios::app);
    out << "-------------------------------------------------\n";
    out << "TEAM ID: " << t.teamID << " | TYPE: " << t.type << "\n";
    out << "Skill: " << t.skillScore << " | Synergy: " << t.synergyScore
        << " | Total: " << t.totalScore << "\n";
    for (int i = 0; i < t.memberCount; i++) {
        out << (i + 1) << ". [" << t.members[i].role << "] "
            << t.members[i].name << " (Roll: " << t.members[i].rollNo << ")\n";
    }
    out << "-------------------------------------------------\n\n";
    out.close();
}

void viewHistoryFromFile() {
    cout << "\n--- Saved Squad History (squad.txt) ---\n";
    ifstream in("squad.txt");
    if (!in) {
        cout << "No history file found yet.\n";
        return;
    }
    string line;
    while (getline(in, line)) {
        cout << line << "\n";
    }
    in.close();
}

// --- Module 4: Manmeet Kaur - FIFO Queues, Shortage Alerts & Leftover Engine ---
queue<Participant> devQ;
queue<Participant> designQ;
queue<Participant> pitchQ;
int nextTeamID = 101;

void addToQueue(Participant p) {
    if (p.role == "Developer") {
        devQ.push(p);
    } else if (p.role == "Designer") {
        designQ.push(p);
    } else {
        pitchQ.push(p);
    }
}

void showQueueStatus() {
    cout << "\n--- Waiting Queues Status ---\n";
    cout << "Developers Waiting  : " << devQ.size() << "\n";
    cout << "Designers Waiting   : " << designQ.size() << "\n";
    cout << "Pitch Leads Waiting : " << pitchQ.size() << "\n";

    if (devQ.size() >= 2 && designQ.size() >= 2 && pitchQ.size() >= 2) {
        cout << "Status: Ready to form a balanced 2:2:2 team.\n";
    } else {
        cout << "Shortage Alert - Missing members for next 2:2:2 team:\n";
        if (devQ.size() < 2)    cout << "  Need " << (2 - devQ.size()) << " more Developer(s)\n";
        if (designQ.size() < 2) cout << "  Need " << (2 - designQ.size()) << " more Designer(s)\n";
        if (pitchQ.size() < 2)  cout << "  Need " << (2 - pitchQ.size()) << " more Pitch Lead(s)\n";
    }
}

void formBalancedTeam() {
    if (devQ.size() < 2 || designQ.size() < 2 || pitchQ.size() < 2) {
        cout << "\nCannot form 2:2:2 team right now.\n";
        showQueueStatus();
        return;
    }

    Team t;
    t.teamID = nextTeamID++;
    t.type = "Balanced 2:2:2";
    t.memberCount = 6;
    t.skillScore = 0;

    for (int i = 0; i < 2; i++) {
        t.members[i] = devQ.front();
        t.skillScore += devQ.front().getBestScore();
        devQ.pop();
    }
    for (int i = 2; i < 4; i++) {
        t.members[i] = designQ.front();
        t.skillScore += designQ.front().getBestScore();
        designQ.pop();
    }
    for (int i = 4; i < 6; i++) {
        t.members[i] = pitchQ.front();
        t.skillScore += pitchQ.front().getBestScore();
        pitchQ.pop();
    }

    t.synergyScore = calculateTeamSynergy(t.members, 6);
    t.totalScore = t.skillScore + t.synergyScore;

    insertHeap(t);
    saveTeamToFile(t);

    cout << "\nBalanced Team " << t.teamID << " formed successfully!\n";
    for (int i = 0; i < 6; i++) {
        cout << "  - [" << t.members[i].role << "] " << t.members[i].name
             << " (Roll: " << t.members[i].rollNo << ")\n";
    }
    cout << "Skill Score: " << t.skillScore << " | Synergy: " << t.synergyScore
         << " | Total: " << t.totalScore << "\n";
    cout << "Team saved to squad.txt\n";
}

void formLeftoverTeam() {
    int totalLeft = devQ.size() + designQ.size() + pitchQ.size();
    if (totalLeft == 0) {
        cout << "\nNo leftover students waiting in queues.\n";
        return;
    }

    Team t;
    t.teamID = nextTeamID++;
    t.type = "Hybrid Leftover";
    t.memberCount = 0;
    t.skillScore = 0;

    while (t.memberCount < 6 && (!devQ.empty() || !designQ.empty() || !pitchQ.empty())) {
        if (!devQ.empty() && t.memberCount < 6) {
            t.members[t.memberCount++] = devQ.front();
            t.skillScore += devQ.front().getBestScore();
            devQ.pop();
        }
        if (!designQ.empty() && t.memberCount < 6) {
            t.members[t.memberCount++] = designQ.front();
            t.skillScore += designQ.front().getBestScore();
            designQ.pop();
        }
        if (!pitchQ.empty() && t.memberCount < 6) {
            t.members[t.memberCount++] = pitchQ.front();
            t.skillScore += pitchQ.front().getBestScore();
            pitchQ.pop();
        }
    }

    t.synergyScore = calculateTeamSynergy(t.members, t.memberCount);
    t.totalScore = t.skillScore + t.synergyScore;

    insertHeap(t);
    saveTeamToFile(t);

    cout << "\nHybrid Leftover Team " << t.teamID << " formed with " << t.memberCount << " members!\n";
    for (int i = 0; i < t.memberCount; i++) {
        cout << "  - [" << t.members[i].role << "] " << t.members[i].name
             << " (Roll: " << t.members[i].rollNo << ")\n";
    }
    cout << "Skill Score: " << t.skillScore << " | Synergy: " << t.synergyScore
         << " | Total: " << t.totalScore << "\n";
}

// --- Demo Data Loader (Mohd Aszad) & Main Menu Controller ---
bool demoLoaded = false;

Node* loadDemoStudents(Node* root) {
    if (demoLoaded) {
        cout << "\nDemo data is already loaded.\n";
        return root;
    }

    Participant demo[9] = {
        Participant("Aarav",  105, 92, 65, 70),
        Participant("Rohan",  101, 88, 60, 68),
        Participant("Priya",  108, 60, 94, 72),
        Participant("Sneha",  103, 58, 89, 75),
        Participant("Kabir",  109, 64, 70, 95),
        Participant("Ananya", 102, 62, 68, 90),
        Participant("Vikram", 107, 85, 55, 60),
        Participant("Meera",  104, 50, 86, 65),
        Participant("Aditya", 106, 60, 62, 87)
    };

    for (int i = 0; i < 9; i++) {
        root = insertBST(root, demo[i]);
        addToQueue(demo[i]);
        registerInGraph(demo[i].rollNo);
    }

    addSynergyEdge(105, 108, 9);
    addSynergyEdge(101, 109, 8);
    addSynergyEdge(103, 102, 10);
    addSynergyEdge(107, 104, 8);

    demoLoaded = true;
    cout << "\n9 Demo students and compatibility links loaded.\n";
    return root;
}

int main() {
    Node* root = NULL;
    int choice;

    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            graph[i][j] = 0;
        }
    }

    while (true) {
        cout << "\n======================================================\n";
        cout << "         SKILL-BASED HACKATHON TEAM BUILDER           \n";
        cout << "======================================================\n";
        cout << "  1. Register New Student\n";
        cout << "  2. View Queue Status & Shortage Alert\n";
        cout << "  3. Form Balanced 2:2:2 Team\n";
        cout << "  4. Search Student by Roll No (BST)\n";
        cout << "  5. Display All Students Sorted (BST In-Order)\n";
        cout << "  6. View Max-Heap Leaderboard\n";
        cout << "  7. Add / View Graph Compatibility Matrix\n";
        cout << "  8. Allocate Leftover Students (Hybrid Team)\n";
        cout << "  9. View Saved Teams from File\n";
        cout << " 10. Load 9 Demo Students\n";
        cout << "  0. Exit\n";
        cout << "------------------------------------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 0) {
            int freed = deleteBST(root);
            cout << "\nCleaned up " << freed << " BST nodes from memory. Exiting...\n";
            break;
        }

        if (choice == 1) {
            string name;
            int roll, d, des, p;
            cin.ignore(1000, '\n');
            cout << "Enter Student Name: ";
            getline(cin, name);
            cout << "Enter Roll Number (e.g. 110): ";
            cin >> roll;

            if (searchBST(root, roll) != NULL) {
                cout << "Error: Roll number already exists.\n";
                continue;
            }

            cout << "Developer Score (1-100): ";
            cin >> d;
            cout << "Designer Score (1-100): ";
            cin >> des;
            cout << "Pitching Score (1-100): ";
            cin >> p;

            Participant newStudent(name, roll, d, des, p);
            root = insertBST(root, newStudent);
            addToQueue(newStudent);
            registerInGraph(roll);
            cout << "\nRegistered " << name << " as " << newStudent.role << ".\n";
        }
        else if (choice == 2) {
             showQueueStatus();
        }
        else if (choice == 3) {
            formBalancedTeam();
        }
        else if (choice == 4) {
            int r;
            cout << "Enter Roll Number to search: ";
            cin >> r;
            Node* ans = searchBST(root, r);
            if (ans == NULL) {
                cout << "Student not found in database.\n";
            } else {
                cout << "\nStudent Found -> Name: " << ans->data.name
                     << " | Role: " << ans->data.role
                     << " | Scores: " << ans->data.devScore << "/"
                     << ans->data.designScore << "/" << ans->data.pitchScore << "\n";
            }
        }
        else if (choice == 5) {
            cout << "\n--- Registered Students (Sorted by Roll No) ---\n";
            if (root == NULL) cout << "Database is empty.\n";
            else inOrderBST(root);
        }
        else if (choice == 6) {
            displayLeaderboard();
        }
        else if (choice == 7) {
            int sub;
            cout << "1. View Compatibility Links\n2. Add Compatibility Score\nChoose: ";
            cin >> sub;
            if (sub == 1) {
                displayGraphMatrix();
            } else if (sub == 2) {
                int r1, r2, sc;
                cout << "Enter Student 1 Roll No: ";
                cin >> r1;
                cout << "Enter Student 2 Roll No: ";
                cin >> r2;
                cout << "Enter Synergy Score (1-10): ";
                cin >> sc;
                addSynergyEdge(r1, r2, sc);
            }
        }
        else if (choice == 8) {
            formLeftoverTeam();
        }
        else if (choice == 9) {
            viewHistoryFromFile();
        }
        else if (choice == 10) {
            root = loadDemoStudents(root);
        }
        else {
            cout << "Invalid choice. Enter 0 to 10.\n";
        }
    }

    return 0;
}
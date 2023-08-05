#include <iostream>
#include <limits> 
#include <bits/stdc++.h>
using namespace std;

class Process {
    friend class Scheduler;
    string name;
    int id, priority, arrivalTime, completionTime, burstTime, turnaroundTime, waitingTime, remainingBurstTime;

public:
    Process() {
        name = "";
        priority = id = arrivalTime = completionTime = burstTime = turnaroundTime = waitingTime = remainingBurstTime = 0;
    }

    void input() {
        cout << "Enter the name of the process: ";
        cin >> name;

        cout << "Enter the id of the process: ";
        cin >> id;

        cout << "Enter the arrival time of the process: ";
        cin >> arrivalTime;

        cout << "Enter the burst time of the process: ";
        cin >> burstTime;

        remainingBurstTime = burstTime;
    }

    friend bool compareByArrivalTime(const Process& a, const Process& b);
    friend bool compareByBurstTime(const Process& a, const Process& b);
    friend bool compareByPriorityTime(const Process& a, const Process& b);
};

class Scheduler {
    int noOfJobs;
    float avgWaitingTime, avgTurnaroundTime;
    Process* processes; // Pointer to array of objects

public:
    Scheduler(int n) {
        noOfJobs = n;
        avgWaitingTime = avgTurnaroundTime = 0.0;
        processes = new Process[n];
    }

    ~Scheduler() {
        delete[] processes;
    }

    void setProcesses() {
        for (int i = 0; i < noOfJobs; i++) {
            processes[i].input();
        }
    }
    void resetProcesses();
    void display();
    void displayTabular();
    void calculateTimesP();
    void calculateTimesNP();
    void sortProcesses(bool (*comparisonFunction)(const Process& a, const Process& b));
    void FCFS();
    void SJF(); // Preemptive SJF
    void PriorityS(); // Non-preemptive Priority
    void RR(); // Preemptive Round Robin
};

void Scheduler::calculateTimesP() {
    processes[0].completionTime = processes[0].burstTime;
    for (int i = 1; i < noOfJobs; i++) {
        processes[i].completionTime = processes[i - 1].completionTime + processes[i].burstTime;
    }
    int totalTurnaroundTime = 0, totalWaitingTime = 0;
    for (int i = 0; i < noOfJobs; i++) {
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        totalTurnaroundTime += processes[i].turnaroundTime;
        totalWaitingTime += processes[i].waitingTime;
    }

    avgTurnaroundTime = static_cast<float>(totalTurnaroundTime) / noOfJobs;
    avgWaitingTime = static_cast<float>(totalWaitingTime) / noOfJobs;
}

void Scheduler::calculateTimesNP() {
    int totalTurnaroundTime = 0, totalWaitingTime = 0;

    for (int i = 0; i < noOfJobs; i++) {
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        totalTurnaroundTime += processes[i].turnaroundTime;
        totalWaitingTime += processes[i].waitingTime;
    }

    avgTurnaroundTime = static_cast<float>(totalTurnaroundTime) / noOfJobs;
    avgWaitingTime = static_cast<float>(totalWaitingTime) / noOfJobs;
}

// comparison functions begin
bool compareByArrivalTime(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

bool compareByBurstTime(const Process& a, const Process& b) {
    return a.burstTime < b.burstTime;
}

bool compareByPriorityTime(const Process& a, const Process& b) {
    return a.priority < b.priority;
}

void Scheduler::sortProcesses(bool (*comparisonFunction)(const Process& a, const Process& b)) {
    for (int i = 0; i < noOfJobs; i++) {
        for (int j = i + 1; j < noOfJobs; j++) {
            if (comparisonFunction(processes[j], processes[i])) {
                Process t = processes[j];
                processes[j] = processes[i];
                processes[i] = t;
            }
        }
    }
}

void Scheduler::display() {
    cout << "\nGantt Chart:\n";
    int totaltime = processes[noOfJobs - 1].completionTime; // Total time
    vector<string> timeline(totaltime, " "); // Create a timeline vector to store the Gantt chart

    // Fill in the timeline with process names
    for (int i = 0; i < noOfJobs; i++) {
        int startTime = max(processes[i].arrivalTime, processes[i].completionTime - processes[i].burstTime); // Account for processes that start before completion
        int endTime = processes[i].completionTime;
        for (int j = startTime; j < endTime; j++) {
            if (timeline[j] == " ") {
                timeline[j] = processes[i].name;
            }
        }
    }

    // Display the Gantt chart
    cout << "+";
    for (int i = 0; i < totaltime; i++) {
        cout << "-";
    }
    cout << "+\n";

    for (int i = 0; i < totaltime; i++) {
        cout << "|" << timeline[i];
    }
    cout << "|\n";

    cout << "+";
    for (int i = 0; i < totaltime; i++) {
        cout << "-";
    }
    cout << "+\n";

   // Display the time units at the bottom of the chart
cout << "+";
for (int i = 0; i < totaltime; i++) {
    if (i % 10 == 0) {
        cout << i / 10;
    } else {
        cout << " ";
    }
}
cout << totaltime << "\n";
}

void Scheduler::displayTabular() {
    cout << "\nProcess\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n";
    for (int i = 0; i < noOfJobs; i++) {
        cout << processes[i].name << "\t" << processes[i].arrivalTime << "\t" << processes[i].burstTime << "\t" << processes[i].priority << "\t\t" << processes[i].completionTime << "\t\t" << processes[i].turnaroundTime << "\t\t" << processes[i].waitingTime << "\n";
    }
}

void Scheduler::FCFS() {
    sortProcesses(compareByArrivalTime);
    calculateTimesP();
    display();
}

void Scheduler::SJF() { // Preemptive SJF
    int is_completed[100] = {0}; // Initialize to 0
    int curr_time = 0;
    int completed_jobs = 0; // Keep track of the number of completed jobs

    while (completed_jobs < noOfJobs) {
        int shortest_job = -1;
        int shortest_burst = INT_MAX;

        // Find the shortest job at the current time
        for (int i = 0; i < noOfJobs; i++) {
            if (processes[i].arrivalTime <= curr_time && is_completed[i] == 0 && processes[i].remainingBurstTime < shortest_burst) {
                shortest_burst = processes[i].remainingBurstTime;
                shortest_job = i;
            }
        }

        // If no job is found at the current time, move time to the next arrival time
        if (shortest_job == -1) {
            int next_arrival = INT_MAX;
            for (int i = 0; i < noOfJobs; i++) {
                if (processes[i].arrivalTime > curr_time && processes[i].arrivalTime < next_arrival) {
                    next_arrival = processes[i].arrivalTime;
                }
            }
            curr_time = next_arrival;
        } else {
            // Execute the shortest job for 1 unit of time (preemptive)
            processes[shortest_job].remainingBurstTime--;
            curr_time++;

            // Check if the job is completed
            if (processes[shortest_job].remainingBurstTime == 0) {
                is_completed[shortest_job] = 1;
                processes[shortest_job].completionTime = curr_time;
                completed_jobs++;
            }
        }
    }

    calculateTimesNP();
    display();
}

void Scheduler::PriorityS() { // Non-preemptive Priority
    for (int i = 0; i < noOfJobs; i++) {
        cout << "Enter priority of process " << processes[i].name << ": ";
        cin >> processes[i].priority;
    }

    sortProcesses(compareByPriorityTime);
    calculateTimesP();
    display();
}

void Scheduler::RR() { // Preemptive Round Robin
    // Sort the processes based on arrival time (similar to FCFS)
    sortProcesses(compareByArrivalTime);

    int time_quantum; // Time quantum for each process, you can set this value as needed (e.g., 2, 3, etc.)

    cout << "Enter the time quantum: ";
    cin >> time_quantum;

    // Clear the input buffer
     cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int remaining_jobs = noOfJobs; // Number of jobs remaining to be completed
    int curr_time = processes[0].arrivalTime; // Initialize to the arrival time of the first process

    while (remaining_jobs > 0) {
        for (int i = 0; i < noOfJobs; i++) {
            // Rest of the RR function remains unchanged...
        }
    }

    calculateTimesNP();
    display();
}

void Scheduler::resetProcesses() {
    for (int i = 0; i < noOfJobs; i++) {
        processes[i].completionTime = 0; // Set completionTime to 0 to indicate the process is not completed yet.
    }
}
int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Scheduler s(n); // Create the Scheduler object

    // Set the processes array in the Scheduler object
    s.setProcesses();

    int choice;
    do {
        cout << "\nSelect the CPU Scheduling Algorithm:\n";
        cout << "1. FCFS\n";
        cout << "2. SJF (Preemptive)\n";
        cout << "3. Priority (Non-preemptive)\n";
        cout << "4. Round Robin (Preemptive)\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nFCFS Scheduling Algorithm:\n";
                s.resetProcesses();  
                s.FCFS();
                s.displayTabular();
                break;
            case 2:
                cout << "\nSJF (Preemptive) Scheduling Algorithm:\n";
                s.resetProcesses(); 
                s.SJF();
                s.displayTabular();
                break;
            case 3:
                cout << "\nPriority (Non-preemptive) Scheduling Algorithm:\n";
                s.resetProcesses(); 
                s.PriorityS();
                s.displayTabular();
                break;
            case 4:
                cout << "\nRound Robin (Preemptive) Scheduling Algorithm:\n";
                s.resetProcesses();  
                s.RR();
                s.displayTabular();
                break;
            case 0:
                cout << "\nExiting the program.\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}

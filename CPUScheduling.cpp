/*Write a program to simulate CPU Scheduling Algorithms :
FCFS , SJF (Preemptive) , Priority (Non-preemptive) and Round Robin (Preemptive). */

#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Process{ friend class Schedular;
    string name;
    int id,priority,arrivalt,completiont,burstt,turnaroundt,waitingt;

    public:
    Process(){
        name="";
        priority=id=arrivalt=completiont=burstt=turnaroundt=waitingt=0;

    }

    void input(){
        cout<<"Enter the name of the process: ";
        cin>>name;

        cout<<"Enter the id of the process: ";
        cin>>id;

        cout<<"Enter the arrival time of the process: ";
        cin>>arrivalt;

        cout<<"Enter the completion time of the process: ";
        cin>>completiont;

        cout<<"Enter the burst time of the process: ";
        cin>>burstt;
    }

};

class Schedular{

};

int main(){
    int n;
    
}

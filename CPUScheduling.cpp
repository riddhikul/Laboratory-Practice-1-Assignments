/*Write a program to simulate CPU Scheduling Algorithms :
FCFS , SJF (Preemptive) , Priority (Non-preemptive) and Round Robin (Preemptive). */
//author : riddhikul
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
    int noOfJobs;
    float avgwt,avgtat;
    Process* arr; //pointer to array of objects

    public:
    Schedular(int n){
         noOfJobs = n;
         avgwt=avgtat=0.0;
         arr = new Process[n];
    }
    
    void display();
    void calculateTimes();
    void FCFS();
    void SJF();
    void PriorityS();
    void RR();

};

void Schedular::calculateTimes(){

    arr[0].completiont=arr[0].burstt;
    for(int i=1;i<noOfJobs;i++){
        arr[i].completiont=arr[i-1].completiont+arr[i].burstt;
    }
    int totaltat =0 , totalwt=0;
    for(int i=0;i<noOfJobs;i++){
        arr[i].turnaroundt=arr[i].completiont-arr[i].arrivalt;
        arr[i].waitingt=arr[i].turnaroundt-arr[i].burstt;

        totaltat+=arr[i].turnaroundt;
        totalwt+=arr[i].waitingt;
    }

    avgtat=totaltat/noOfJobs;
    avgwt=totalwt/noOfJobs;
}

void Schedular::display(){
    

}

void Schedular::FCFS(){
    

}

void Schedular::SJF(){


}

void Schedular::PriorityS(){

}

void Schedular::RR(){

}

int main(){
    int n;
    Schedular s(5);
    s.calculateTimes();

    
}

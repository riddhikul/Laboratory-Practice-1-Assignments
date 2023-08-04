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

        cout<<"Enter the burst time of the process: ";
        cin>>burstt;
    }
friend bool compareByArrivalTime(const Process& a, const Process& b);
    friend bool compareByBurstTime(const Process& a, const Process& b);
    friend bool compareByPriorityTime(const Process& a, const Process& b);
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
    void sortProcesses(bool (*comparisonFunction)(const Process& a, const Process&b));
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

//comparison functions begin
bool compareByArrivalTime(const Process& a,const Process& b){
return a.arrivalt<b.arrivalt;
}

bool compareByBurstTime(const Process& a,const Process& b){
return a.burstt<b.burstt;
}

bool compareByPriorityTime(const Process& a,const Process& b){
return a.priority<b.priority;
}

void Schedular::sortProcesses(bool (*comparisonFunction)(const Process& a , const Process& b)){
    for(int i=0;i<noOfJobs;i++){
        for (int j=i+1;j<noOfJobs; j++){
            if(comparisonFunction(arr[j],arr[i])){
                Process t= arr[j];
                arr[j]=arr[i];
                arr[i]=t;
            }
        }
    }
}


void Schedular::display(){
    cout<<"\nGantt Chart:\n";
    int totaltime=arr[noOfJobs-1].completiont; //Total time
    int currTime=0; //Current time in the chart

    //timeline header
    cout<<"+";
    for(int i=0; i<totaltime;i++){
        cout<<"-";
    }
    cout<<"+\n";

    //Timeline for the process
    for(int i=0;i<noOfJobs;i++){
        cout<<"yo";
        while(currTime<arr[i].completiont){
            if(currTime>=arr[i].arrivalt && currTime < arr[i].completiont){
                 cout<<arr[i].name;
            }
            else
            cout<<" ";
            currTime++;   
        }
    }
    cout<<"|\n";

    //displayin the time units below each process

    cout<<" ";
    currTime=0;
    for(int i=0;i<noOfJobs;i++){
        while(currTime<arr[i].completiont){
            if(currTime>=arr[i].arrivalt && currTime<arr[i].completiont){
                cout<<currTime;
            }
            else
            cout<<" ";
            currTime++;
        }
    }
cout<<totaltime<<endl;
}

void Schedular::FCFS(){
    for(int i=0;i<noOfJobs;i++){
        arr[i].input();
    }  
    
    sortProcesses(compareByArrivalTime);
    calculateTimes();
    display();

    

}

void Schedular::SJF(){


}

void Schedular::PriorityS(){

}

void Schedular::RR(){

}

int main() {
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;

    Schedular s(n);

    // Call the FCFS function to input the data and display the Gantt chart
    s.FCFS();

    return 0;
}


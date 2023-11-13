#include <bits/stdc++.h>
using namespace std;

class Job {
    int id;
    string name;
    int bursttime;
    int arrivaltime;
    int waitingtime;
    int turnaroundtime;
    int completiontime;



public : //non parameterized constructor
Job(){
bursttime=waitingtime=arrivaltime=completiontime=turnaroundtime=id=0;
name="";

}

Job(int id,string name,int arrivaltime , int bursttime){
    //parameterized constructor
    this->id=id;
    this->name=name;
    this->bursttime=bursttime;
    this->arrivaltime=arrivaltime;
    waitingtime=turnaroundtime=completiontime=0;

}

friend class Schedular;
};

class Schedular {
    int n;
    Job *processes;
    vector<Job> readyQueue;
    queue<Job> waitingQueue;

    public: 
    Schedular(int n){
        this->n=n;
        processes= new Job[n];
    }

    void input(){
        // string id , name ;
        int at , bt;
        for(int i=0;i<n;i++){
            cout<<"Enter arrival time and burst time of P"<<i+1<<endl;
            cin>>at>>bt;
            Job j(i+1,"P"+ to_string(i+1),at,bt);
            processes[i]=j;
        }
    }

    void display(){
        cout<<"id\tTa\tTs\tTc\ttat\ttw"<<endl;
        for(int i=0;i<n;i++){
            cout<<processes[i].id<<"\t"<<processes[i].arrivaltime<<"\t"<<processes[i].bursttime<<"\t"<<processes[i].completiontime<<"\t"<<processes[i].turnaroundtime<<"\t"<<processes[i].waitingtime<<endl;
        }
    double sumTat=0;
    double sumWt=0;
    for(int i=0;i<n;i++){
        sumTat+=processes[i].turnaroundtime;
        sumWt+=processes[i].waitingtime;
    }
    cout<<"Average turn around time: "<<sumTat/n<<endl;
    cout<<"Average waiting time: "<<sumWt/n<<endl;
    }

    void displayGantt(vector<Job> readyQueue , int currentTime){
        cout<<"Ready queue at time"<<currentTime<<"sec"<<endl;
        for(int i=0;i<readyQueue.size();i++){
            cout<<readyQueue[i].name<<"("<<readyQueue[i].bursttime<<"sec)"<<"\t";
        }
        cout<<endl<<endl;
    }

    void fcfs(){
    int totaltime=0;
    int currenttimme=0;
    int processcompleted=0;

    sort(processes , processes+n,[](const Job &lhs , const Job rhs){
        return lhs.arrivaltime<rhs.arrivaltime;
    });
    for ( int i =0;i<n;i++){
      totaltime += processes[i].bursttime;  
    }

    while(currenttimme<=totaltime){
        if(processcompleted<n && processes[processcompleted].arrivaltime<=currenttimme){
            readyQueue.push_back(processes[processcompleted]);
            processcompleted ++;
        }
        this->displayGantt(readyQueue,currenttimme);
        if(readyQueue.size()>0){
          readyQueue[0].bursttime--;
          if(readyQueue[0].bursttime==0){
            for (int i=0;i<n;i++){
                if(readyQueue[0].id == processes[i].id){
                    processes[i].completiontime=currenttimme+1;
                    processes[i].turnaroundtime=processes[i].completiontime-processes[i].arrivaltime;
                    processes[i].waitingtime=processes[i].turnaroundtime-processes[i].bursttime;
                }
            }
            readyQueue.erase(readyQueue.begin());

          } 
        
        }
          currenttimme++; 
      
    }
      this->display();
}

void shortestJobFirst(){
    int currenttime=0;
    int processComplete=0;
    int totaltime =0;
    sort(processes,processes+n,[] (const Job &lhs , const Job &rhs){
        return lhs.arrivaltime<rhs.arrivaltime;
    });

    for(int i=0;i<n;i++){
        totaltime+=processes[i].bursttime;
    }

    while(currenttime<=totaltime){
        if(processes[processComplete].arrivaltime <=currenttime && processComplete !=n){
          readyQueue.push_back(processes[processComplete]);
          processComplete++;

        }
        sort(readyQueue.begin(),readyQueue.end(),[](const Job &lhs , const Job &rhs){
            return lhs.bursttime<rhs.bursttime;
        });
        this->displayGantt(readyQueue,currenttime);
    
if(readyQueue.size()>0){
    readyQueue[0].bursttime--;
    if(readyQueue[0].bursttime==0){
        for(int i =0 ; i<n ; i++){
            if(readyQueue[0].id==processes[i].id){
                processes[i].completiontime=currenttime+1;
                processes[i].turnaroundtime=processes[i].completiontime-processes[i].arrivaltime;
                processes[i].waitingtime=processes[i].turnaroundtime-processes[i].bursttime;
            }
        }
        readyQueue.erase(readyQueue.begin());
    } }
    currenttime++;
}
this->display();
}

void srtf() {
    int currentTime = 0;
    int remainingTime[n];
    fill(remainingTime, remainingTime + n, 0);

    int completedProcesses = 0;

    while (completedProcesses < n || !readyQueue.empty() || !waitingQueue.empty()) {
        while (!waitingQueue.empty() && waitingQueue.front().arrivaltime <= currentTime) {
            readyQueue.push_back(waitingQueue.front());
            waitingQueue.pop();
        }

        if (!readyQueue.empty()) {
            Job currentJob = readyQueue.front();
            readyQueue.pop_back();

            currentJob.bursttime--;

            if (currentJob.bursttime == 0) {
                completedProcesses++;
                currentJob.completiontime = currentTime + 1;
                currentJob.turnaroundtime = currentJob.completiontime - currentJob.arrivaltime;
                currentJob.waitingtime = currentJob.turnaroundtime - currentJob.bursttime;

            } else {
                waitingQueue.push(currentJob);
            }
        } else {
            int nextProcess = findNextArrival(currentTime);
            currentTime = max(currentTime, processes[nextProcess].arrivaltime);
        }

        currentTime++;
    }
    this->display();
}

 int findNextArrival(int currentTime) {
        int nextProcess = -1;
        int shortestArrival = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivaltime > currentTime && processes[i].arrivaltime < shortestArrival) {
                nextProcess = i;
                shortestArrival = processes[i].arrivaltime;
            }
        }

        return nextProcess;
    }





void priority (){
    int totatltime=0;
    int currenttime =0 ;
    int processcompleted=0;
    int priority[n];

    cout<<"Enter priorities"<<endl;
    for(int i=0;i<n;i++){
        cin>>priority[i];
    }
    for(int i=0;i<=n-1;i++){
        for(int j=0;j<=n-i-1;j++){
            if(priority[j]>priority[j+1]){
                swap(priority[j],priority[j+1]);
                swap(processes[j],processes[j+1]);
            }
        }
    }
    for(int i=0;i<n;i++){
        totatltime+=processes[i].bursttime;
        }

      while(currenttime<=totatltime){
        if(processcompleted<n){
            readyQueue.push_back(processes[processcompleted]);
            processcompleted++;
        }
        this->displayGantt(readyQueue,currenttime);
        if(readyQueue.size()>0){
            readyQueue[0].bursttime--;
            if(readyQueue[0].bursttime==0){
             for(int i=0;i<n;i++){
                if(readyQueue[0].id==processes[i].id){
                    processes->completiontime=currenttime+1;
                    processes[i].turnaroundtime = (processes[i].completiontime - processes[i].arrivaltime) > 0 ? processes[i].completiontime - processes[i].arrivaltime : 0;
					processes[i].waitingtime = (processes[i].turnaroundtime - processes[i].bursttime) > 0 ? processes[i].turnaroundtime - processes[i].bursttime : 0;

                }
             }
             readyQueue.erase(readyQueue.begin());

            }
        }
        currenttime++;
      }  
      this->display();
    }

    void roundRobin(){
        int totaltime=0;
        int currenttime=0;
        int processcompleted=0;
        int interval;
        int addedBurst=0;
        Job addedJob;
        addedJob.bursttime=0;

        cout<<"enter time interval: ";
        cin>>interval;

        for(int i=0;i<n;i++){
            totaltime+=processes[i].bursttime;
        }

        sort(processes,processes+n,[](const Job &lhs, const Job &rhs){
             return lhs.arrivaltime<rhs.arrivaltime;
        });

        while(currenttime<totaltime){
            while(processcompleted<n && processes[processcompleted].arrivaltime<=currenttime){
                readyQueue.push_back(processes[processcompleted]);
                processcompleted++;
            }
            if(addedJob.bursttime>0){
                readyQueue.push_back(addedJob);
            }

            if(readyQueue.size()>0){
                addedJob=readyQueue[0];
                readyQueue.erase(readyQueue.begin());
                if(addedJob.bursttime>interval){
                    addedJob.bursttime=addedJob.bursttime-interval;
                    addedBurst = interval;
                }
                else{
                    addedBurst = addedJob.bursttime;
                    addedJob.bursttime=0;
                }

                if(addedJob.bursttime==0){
                    for(int i=0;i<n;i++){
                        if(addedJob.id==processes[i].id){
                            processes[i].completiontime=currenttime+addedBurst;
                            processes[i].turnaroundtime=processes[i].completiontime-processes[i].arrivaltime;
                            processes[i].waitingtime=processes[i].turnaroundtime-processes[i].bursttime;
                        }
                    }
                }
                else{
                    waitingQueue.push(addedJob);
                }
            }
            currenttime+=addedBurst;
        }
        this->display();
    }
};

int main(){
    int n;
    int choice;
    cout<<"Enter the number of processes: ";
    cin>>n;
    Schedular s(n);
    s.input();
    while(true){
        cout<<"MENU"<<endl;
        cout<<"1.Fcfs"<<endl;
        cout<<"2.SJF"<<endl;
        cout<<"3.SRTF"<<endl;
        cout<<"4.Priority"<<endl;
        cout<<"5.RR"<<endl;
        cout<<"6.Exit"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
            s.fcfs();
            break;

            case 2:
            s.shortestJobFirst();
            break;

            case 3:
            s.srtf();
            break;

            case 4:
            s.priority();
            break;

            case 5: 
            s.roundRobin();
            break;

            case 6: exit(0);
            default:cout<<"Enter valid option"<<endl;
            break;
        }
    }
}



















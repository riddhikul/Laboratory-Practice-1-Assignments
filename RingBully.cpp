#include<bits/stdc++.h>
using namespace std;
class Process{
public:
int id , priority;
bool isDown;
Process(){ //default constructor
    id=priority=-1;
}

Process(int id , int priority =-1 , bool isDown =  false){
    //parameterized constructor 
    this->id=id;
    if(priority==-1)this->priority=id;
    else this->priority=priority;
    this->isDown=isDown;
}

void fail(){
    isDown=true;
}

bool message(Process p , string message){//For Bully 
    cout<<"Process p"<<id<<" messaged p"<<p.id<<" : "<<message<<endl;
    bool response = p.respondMessage(this->id,message);
    if(response)cout<<"Process p"<<p.id<<" messaged p"<<id<<" : OK"<<endl;
    return response;
}

bool message(set<int> & successors){ // ring sathi 
    //returns true only if this process was also the initiator 
    if(!this->isDown){
        if(successors.find(this->id)!=successors.end()){
            //this process is already present in  set
            return true;
        }
        else{
            successors.insert(this->id);
        }
    }
    return false;
}

bool respondMessage(int senderId , string message){
    if(!this->isDown){
        if(message=="ELECTION") return true;
    }
    return false;
}
friend ostream& operator << (ostream& out , const Process& p){
    out<<"Process { "<<"\n"<<"id: "<<p.id<<", priority: "<<p.priority<<", isDown: "<<p.isDown<<"\n"<<" }"<<endl;
    return out;
}
};

class ProcessSystem{
    public:
    int n;
    int coordinator;
    vector<Process> processes;
    ProcessSystem(int n){
    this->n=n;
    processes= vector<Process>(n);
    for(int i=0;i<n;i++){
        processes[i]=Process(i);
    }
    }

    void display(){
        for(int i=0;i<n;i++){
            cout<<processes[i];
        }
    }

    void downProcess(int i){
        processes[i].fail();
    }

    void electionBully(int id){
        if(processes[id].isDown){
            cout<<"Election cannot be initiated as process is down"<<endl;
            return;
        }

        vector<int> successors;
        for(int j=0; j<n;j++){
        
                if(processes[j].priority>processes[id].priority && j!=id){
                    bool response =processes[id].message(processes[j],"ELECTION");
                    if(response){
                        successors.push_back(j);
                    }
                }
        }
            for(int j=0;j<successors.size();j++){
                electionBully(successors[j]);
            }
            if(successors.size()==0){
                coordinator = id;
                for(int j=0;j<n;j++){
                    if(j!=id){
                        processes[this->coordinator].message(processes[j],"COORDINATOR");
                    }
                }
            }
        }
    

    void ringBully(int id){
        if(processes[id].isDown){
            cout<<"Ring Election cannot be initiated as process is down"<<endl;
            return;
        }
        bool cycleTerminated=false;
        set<int> successors;
        while(!cycleTerminated){
            int nextId = (id+1)%n;
            cout<<"Process p"<<id<<" messages process p"<<nextId<<endl;
            cycleTerminated=processes[id].message(successors);
            id=nextId;
        }
        int coordinator =*successors.rbegin();
        cout<<"Coordinator is p"<<coordinator<<endl;
    }

};

int main(){
    int p , d ;
 cout<<"Enter the number of processes: "<<endl;
 cin>>p;
 ProcessSystem pro = ProcessSystem(p);
 cout<<"Enter the number of processes which are down "<<endl;
cin>>d;
for(int i=0;i<d;i++){
    int dw=0;
    cout<<"Enter the id of the process which is down: "<<endl;
    cin>>dw;
    pro.downProcess(dw);
}

pro.display();
int choice;
while(true){
    cout<<"Enter your choice"<<endl;
    cout<<"Enter 1 for Bully Election"<<endl;
    cout<<"Enter 2 for Ring Algorithm"<<endl;
    cout<<"Enter 3 to exit "<<endl;
    cin>>choice;

    switch(choice){
        case 1: int initiator;
         cout<<"Enter the process which is initiator: "<<endl;
         cin>>initiator;
         pro.electionBully(initiator);
         cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------";
         break;

        case 2 :  int init;
         cout<<"Enter the process which is initiator: "<<endl;
         cin>>init;
         pro.ringBully(init);
         cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------------";
         break;

         case 3: exit(0);

         default: cout<<"Enter correct choice"<<endl;
         break;

    }
}
}
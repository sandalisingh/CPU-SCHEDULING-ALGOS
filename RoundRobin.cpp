#include <iostream> 
//#include <stdlib.h>
#include "Queue_LLImplementation.h"

using namespace std;

class Processes{
    enum T{
        P,  AT, BT, CT, TAT, WT, RT
    };  //0-P 1-AT 2-BT 3-CT 4-TAT 5-WT 6-RT

    //int GanttChart[7];

    int M[4][7];    //processes and thier AT,BT,CT,TAT,WT,RT
    int n;  //number of process

    public:
        //Processes();

        void arrangeAT();

        void getData();

        void Display();
        void DisplayResult();

        void RoundRobin(int TQ);

        void Average_TAT_WT();
};

// Processes :: Processes(){
//     n = 4;

//     for(int i = 0; i < 7; i++){
//         GanttChart[i] = 0;
//     }
    
//     for (int i = 0; i < n; i++) {
//         M[i][P] = 0;
//         M[i][AT] = 0;
//         M[i][BT] = 0;
//         M[i][CT] = 0;
//         M[i][TAT] = 0;
//         M[i][WT] = 0;
//         M[i][RT] = 0;
//     }
// }

void Processes :: getData(){
    cout << "\n\nNumber of Processs = ";
    cin >> n;
    cout<<endl;
 
    for (int i = 0; i < n; i++) {
        cout << "Process Id: ";
        cin >> M[i][P];
        cout << "Arrival Time: ";
        cin >> M[i][AT];
        cout << "Burst Time: ";
        cin >> M[i][BT];
        cout<<endl;
    }
}

void Swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void Processes :: arrangeAT(){     //BUBBLE SORT
    cout<<"\nArranging AT...\n";

    for (int i = 0; i < (n-1); i++) {
        for (int j = 0; j < (n-i-1); j++) {
            if (M[j][AT] > M[j + 1][AT]) {    //comparing AT 
                for (int k = 0; k < 5; k++) {
                    Swap(M[j][k], M[j + 1][k]); //(asc oder)
                }
            }
        }
    }
}

// Function to find the waiting time for all processes//


void Processes :: RoundRobin(int TQ) {
    //GanttChart = new int[7];

    Queue Ready;
    int i = 1;

    int rem_BT[n];  //remaining burst time of the processes
    for (int i = 0; i < n; i++){
        rem_BT[i] = M[i][BT];
    }
    
    int t =  M[0][AT];  //starting time
    Ready.Enqueue( 0 ); //0th index process

    int k = 0;
    
    // Keep traversing processes in round robin manner until all of them are not done. //
    while( !Ready.isEmpty() ) {
        // cout<<"\n\n\nTIME = "<<t;
        // Ready.Display();
        
        int Running = Ready.Dequeue();   //this index process is running 
        
        //this process have been taken out of ready queue
        //this process takes cpu
        //running state
        

        // GanttChart[k] = M[Running][P];
        // cout<<"\nGC = "<<GanttChart[k];
        // k++;

        // RT
        if(rem_BT[Running] == M[Running][BT]){   //first time takes CPU
            M[Running][RT] = t - M[Running][AT];    //[RT] = [when got CPU for first time] - [AT]
            //cout<<"\nM[Running][RT] = "<<M[Running][RT];
        }
        
        //PROCCESSING
        if (rem_BT[Running] > TQ) {
            t = t + TQ;
            rem_BT[Running] = rem_BT[Running] - TQ; //given cpu for the given time slice
        }else{  //process is competed here   //<=TQ

            t = t + rem_BT[Running];

            M[Running][CT] = t; //CT
            //cout<<"\nM[Running][cT] = "<<M[Running][CT];

            M[Running][TAT] = M[Running][CT] - M[Running][AT];    //[TAT] = [CT] - [AT]
            M[Running][WT] = M[Running][TAT] - M[Running][BT];    //[WT] = [TAT] - [BT]
            
            rem_BT[Running] = 0;

            //this process is completed
            //hence
            //this process wont be added to ready queue
        } 

        //line up the processes which have arrived in the ready queue at this particular time
        //i = i + 1;
        for( ;(M[i][AT] <= t) && (i < n); i++){
            Ready.Enqueue(i);       
        }

        //add this process to the end of ready queue if it is not yet completed
        if(rem_BT[Running] > 0){
            Ready.Enqueue(Running);   
        }
    }
}

// Function to calculate average time
void Processes :: Average_TAT_WT(){
    float AvgTAT = 0, AvgWT = 0;
    
    for (int i = 0; i < n; i++) {
        AvgTAT = AvgTAT + M[i][TAT];
        AvgWT = AvgWT + M[i][WT];
    }

    AvgTAT = AvgTAT / n;
    AvgWT = AvgWT / n;
    
    cout << "\n\nAverage WT = "<< AvgWT;
    cout << "\nAverage TAT = "<< AvgTAT<<"\n\n"; 
}
 
void Processes :: Display(){
    cout << "P\t\tAT\t\tBT\n";
    for (int i = 0; i < n; i++) {
        cout << M[i][P] << "\t\t" << M[i][AT] << "\t\t"
             << M[i][BT] << "\n";
    }
}

void Processes :: DisplayResult(){
    // cout<<"\n\n\nGANTT CHART = \t";
    // for(int i = 0; i < 7; i++){
    //     cout<<GanttChart[i]<<" ";
    // }
    // cout<<"\n\n";

    cout << "\nRESULT\n";
    cout << "P\t\tAT\t\tBT\t\tCT\t\tTAT\t\tWT\t\tRT\n";
    for (int i = 0; i < n; i++) {
        cout << M[i][P] << "\t\t" << M[i][AT] << "\t\t"
             << M[i][BT] << "\t\t" << M[i][CT] << "\t\t"
             << M[i][TAT] << "\t\t" << M[i][WT] << "\t\t"
             << M[i][RT] << "\n";
    }
}



int main(){
    int TQ;

    Processes P;
    P.getData();

    system("clear");
    
    P.arrangeAT();
    P.Display();

    cout<<"\n\nTime Quantum = ";
    cin>>TQ;

    system("clear");

    P.RoundRobin(TQ);
    P.DisplayResult();

    P.Average_TAT_WT();

    return 0;
}
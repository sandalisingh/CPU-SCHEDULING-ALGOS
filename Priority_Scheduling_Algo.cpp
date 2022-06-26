#include <iostream> 
using namespace std;
					
struct Process {					
    int pid;
    int bt;
    int priority;	
};
					
// Function to sort the Process acc. to priority 
bool comparison(Process a, Process b){					
    return (a.priority > b.priority); 
}
					
// Function to find the waiting time for all processes//
					
void findWaitingTime(Process proc[], int n, int wt[]) {					
    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = proc[i - 1].bt + wt[i - 1];					
}
					
// Function to calculate turn around time
void findTurnAroundTime(Process proc[], int n, int wt[], int tat[]) {				
    for (int i = 0; i < n; i++) 
        tat[i] = proc[i].bt + wt[i];	
}
					
//Function to calculate average time 
void findavgTime(Process proc[], int n) {
	int wt[n], tat[n], total_wt = 0, total_tat = 0;
					
    //Function to find waiting time of all processes 
    findWaitingTime(proc, n, wt);
                        
    //Function to find turn around time for all processes 
    findTurnAroundTime(proc, n, wt, tat);
                        
    cout << "\nProcesses "<<" Burst time "<<" Waiting time "<<" Turn around time\n";
					
    for (int i = 0; i < n; i++) {
					
        total_wt = total_wt + wt[i]; 
        total_tat = total_tat + tat[i]; 
        cout << " " << proc[i].pid << "\t\t"<< proc[i].bt << "\t " << wt[i]<< "\t\t " << tat[i] << endl;
    }

    cout << "\nAverage waiting time = "<< (float)total_wt / (float)n;
    cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
					
}
					
void priorityScheduling(Process proc[], int n) {             
    // Sort processes by priority 
    sort(proc, proc + n, comparison);
                        
    cout << "\nProcesses get executed in this order:- "; 

    for (int i = 0; i < n; i++)
        cout << proc[i].pid << " ";
    cout << endl;

    findavgTime(proc, n); 
}
					
int main() {
    Process proc[] = {{3, 8, 1},{1, 10, 2}, {2, 5, 0}}; 
    int n = sizeof proc / sizeof proc[0]; 
    priorityScheduling(proc, n);
    return 0;					
}
					
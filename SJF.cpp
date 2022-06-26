// Shortest Job first with AT
// Criteria : BT
// NON PREEMPTIVE

#include <iostream>

using namespace std;

class Processes{
    int M[4][7];
    int n;

    public:
        void arrangeAT();
        void arrangeBT();

        void CT_TAT_WT_RT();

        void getData();
        
        void Display();
        void DisplayResult();
};

void Processes :: getData(){
    cout << "Enter number of Process: ";
    cin >> n;
    cout<<endl;
 
    for (int i = 0; i < n; i++) {
        cout << "Process Id: ";
        cin >> M[i][0];
        cout << "Arrival Time: ";
        cin >> M[i][1];
        cout << "Burst Time: ";
        cin >> M[i][2];
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
            if (M[j][1] > M[j + 1][1]) {    //comparing AT 
                for (int k = 0; k < 5; k++) {
                    Swap(M[j][k], M[j + 1][k]); //(asc oder)
                }
            }
        }
    }
}

void Processes :: arrangeBT(){
    cout<<"\nArranging BT...\n";

    for (int i = 0; i < (n-1); i++) {
        if ( M[i][1] == M[i + 1][1] ) {  //same AT
            if (M[i][2] > M[i + 1][2]) {    //comparing BT 
                for (int k = 0; k < 5; k++) {
                    Swap(M[i][k], M[i + 1][k]); //( BT in asc oder)
                }
            }
        }
    }
}
 
void Processes :: CT_TAT_WT_RT(){
    int temp, val;
    M[0][3] = M[0][1] + M[0][2];    //[0][CT] = [0][AT] + [0][BT]
    M[0][4] = M[0][3] - M[0][1];    //[TAT] = [CT] - [AT]
    M[0][5] = M[0][4] - M[0][2];    //[WT] = [TAT] - [BT]
    M[0][6] = 0;
 
    for (int i = 1; i < n; i++) {
        M[i][3] = M[i][2] + M[i-1][3];    //[CT] 
        M[i][4] = M[i][3] - M[i][1];    //[TAT] = [CT] - [AT]
        M[i][5] = M[i][4] - M[i][2];    //[WT] = [TAT] - [BT]
        M[i][6] = M[i-1][3] - M[i][1];  //[RT] = [isse pehle wala CT] - [AT]
    }
}
 
void Processes :: Display(){
    cout << "P\t\tAT\t\tBT\n";
    for (int i = 0; i < n; i++) {
        cout << M[i][0] << "\t\t" << M[i][1] << "\t\t"
             << M[i][2] << "\n";
    }
}

void Processes :: DisplayResult(){
    cout << "\nRESULT\n";
    cout << "P\t\tAT\t\tBT\t\tCT\t\tTAT\t\tWT\t\tRT\n";
    for (int i = 0; i < n; i++) {
        cout << M[i][0] << "\t\t" << M[i][1] << "\t\t"
             << M[i][2] << "\t\t" << M[i][3] << "\t\t"
             << M[i][4] << "\t\t" << M[i][5] << "\t\t"
             << M[i][6] << "\n";
    }
}

int main(){
    int temp;

    Processes P;
    P.getData();
 
    P.Display();
 
    P.arrangeAT();
    P.Display();

    P.arrangeBT();
    P.Display();

    P.CT_TAT_WT_RT();

    P.DisplayResult();

    return 0;
}
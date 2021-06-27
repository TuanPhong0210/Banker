#include<iostream>
using namespace std;

int need[50][50];

void calculateNeed(int need[][50], int maxm[][50], int allot[][50], int P, int R)
{
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++) {
            need[i][j] = maxm[i][j] - allot[i][j];
        }
}
bool CheckNeed(int need[][50], int P, int R) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            if (need[i][j] < 0) return false;
        }
    }
    return true;
}

void OutputProcess(int need[][50], int avail[], int maxm[][50], int allot[][50], int P, int R) {
    calculateNeed(need, maxm, allot, P, R);
    if (CheckNeed(need, P, R) == false) {
        return;
    }
    else {
        cout << "Available: ";
        for (int i = 0; i < R; i++) {
            cout << avail[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < P; i++) {
            cout << "PROCESS " << i + 1 << ":   MAX: ";
            for (int j = 0; j < R; j++) {
                cout << maxm[i][j] << " ";
            }
            cout << "   ALLOCATION: ";
            for (int j = 0; j < R; j++) {
                cout << allot[i][j] << " ";
            }
            cout << "   NEED: ";
            for (int j = 0; j < R; j++) {
                cout << need[i][j] << " ";
            }
            cout << endl;
        }
    }
    
}


bool isSafe(int processes[], int avail[], int maxm[][50], int allot[][50], int P, int R)
{
    calculateNeed(need, maxm, allot, P, R);
    if (CheckNeed(need, P, R) == false) {
        cout << "System is not in safe state.\n";
        return false;
    }
    else {
        bool finish[100] = { 0 };

        int safeSeq[100];

        int work[100];
        for (int i = 0; i < R; i++) {
            work[i] = avail[i];
        }
        int count = 0;
        while (count < P)
        {
            bool found = false;
            for (int p = 0; p < P; p++)
            {
                if (finish[p] == 0)
                {
                    int j;
                    for (j = 0; j < R; j++) {
                        if (need[p][j] > work[j]) {
                            break;
                        }
                    }
                    if (j == R)
                    {
                        cout << "P" << p + 1 << ":   WORK: ";
                        for (int k = 0; k < R; k++) {
                            work[k] += allot[p][k];
                            cout << work[k] << " ";
                        }
                        cout << endl;
                        safeSeq[count++] = p;
                        finish[p] = 1;

                        found = true;
                    }
                }
            }
            if (found == false)
            {
                cout << "System is not in safe state.\nDeadlock";
                return false;
            }
        }
        cout << "System is in safe state.\nSafe sequence is: ";
        for (int i = 0; i < P; i++) {
            cout << "P" << safeSeq[i] + 1;
            if (i < P - 1) cout << " --> ";
            else cout << endl;
        }

        return true;
    }
    
}

int main()
{
    int P, R;
    cout << "The number of process: ";
    cin>>P;
    while ( P<0){
    	cout<<"you entered wrong, please re-enter: ";
    	cin>>P;
	}
    
    cout << "The kinds number of resource: ";
    cin >> R;
    while (R<0){
    	cout<<"you entered wrong, please re-enter: ";
    	cin>>R;
	}
    int processes[100];
    int avail[100];
    int maxm[50][50];
    int allot[50][50];
    for (int i = 1; i <= P; i++) {
        processes[i] = i;
    }
    cout << "Initial Available number of " << R << " resource: ";
    for (int i = 0; i < R; i++) {
        cin >> avail[i];
    }
    cout << "Initial Maximum demand: " << endl;
    for (int i = 0; i < P; i++) {
        cout << "Process " << i + 1 << ": ";
        for (int j = 0; j < R; j++) {
            cin >> maxm[i][j];
            
        }
        
    }
    cout << "Initial Allocation already: " << endl;
    for (int i = 0; i < P; i++) {
        cout << "Process " << i + 1 <<": ";
        for (int j = 0; j < R; j++) {
            cin >> allot[i][j];
            cout<<endl;
            
        }
    }
    cout << "============================================================" << endl;
    OutputProcess(need, avail, maxm, allot, P, R);
    isSafe(processes, avail, maxm, allot, P, R);
    system("pause");
    return 0;
}

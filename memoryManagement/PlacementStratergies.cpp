#include<iostream>
using namespace std ;

void firstfit(int blocksize[] , int m , int process[] , int n){

    int allocation[100];
    for (int i=0;i<n;i++){
        allocation[i] = -1;
    }

    for (int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(blocksize[j]>=process[i]){
                allocation[i] = j;
                blocksize[j] -= process[i];
                break;
            }
        }
    }

    cout << "\n process id\tprocess size\tallocated\n ";
    for(int i=0 ;i<n;i++){
        cout <<" " <<i+1 << "\t\t"<< process[i] << "\t\t" ;
        if(allocation[i]!=-1){
            cout << allocation[i]+ 1 ;
        }
        else{
            cout <<" Not allocated ";
        }
        cout << endl;
    }

}

void nextfit(int blocksize[],int m,int process[],int n){
    int allocation[100];
    int k = -1;
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
        int j = (k + 1) % m;
        int count = 0;

        while (count < m) { 
            if (blocksize[j] >= process[i]) {
                allocation[i] = j;
                blocksize[j] -= process[i];
                k = j; 
                break;
            }
            j = (j + 1) % m;
            count++;
        }
    }
    cout << "\n process id\tprocess size\tallocated\n ";
    for(int i=0 ;i<n;i++){
        cout <<" " <<i+1 << "\t\t"<< process[i] << "\t\t" ;
        if(allocation[i]!=-1){
            cout << allocation[i]+ 1 ;
        }
        else{
            cout <<" Not allocated ";
        }
        cout << endl;
    }

}

void worstfit(int blocksize[],int m,int process[],int n){
    int allocation[100];
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;

        for (int j = 0; j < m; j++) {
            if (blocksize[j] >= process[i]) {
                if (worstIdx == -1 || blocksize[j] > blocksize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blocksize[worstIdx] -= process[i];
        }
    }
    cout << "\n process id\tprocess size\tallocated\n ";
    for(int i=0 ;i<n;i++){
        cout <<" " <<i+1 << "\t\t"<< process[i] << "\t\t" ;
        if(allocation[i]!=-1){
            cout << allocation[i]+ 1 ;
        }
        else{
            cout <<" Not allocated ";
        }
        cout << endl;
    }
}

void bestfit(int blocksize[],int m,int process[],int n){
    int allocation[100];

    for(int i=0; i<n ;i++){
        allocation[i] = -1;
    }

    for(int i=0 ;i<n ;i++){
        int bestindx = -1;
        for(int j=0 ;j <m ;j++){
            if(blocksize[j] >= process[i]){
                if(bestindx == -1 || blocksize[j]<blocksize[bestindx]){
                    bestindx = j;
                }
            }
        }
        if(bestindx !=-1 ){
            allocation[i] = bestindx;
            blocksize[bestindx] -= process[i];
        }
    }



    cout << "\n process id\tprocess size\tallocated\n ";
    for(int i=0 ;i<n;i++){
        cout <<" " <<i+1 << "\t\t"<< process[i] << "\t\t" ;
        if(allocation[i]!=-1){
            cout << allocation[i]+ 1 ;
        }
        else{
            cout <<" Not allocated ";
        }
        cout << endl;
    }
}

int main(){
    int m,n;
    int blocksize[100] , process[100];
    cout << "Enter the No of Memory Blocks ";
    cin >> m;
    cout << "Enter the No of Processes ";
    cin >> n;

    cout << "Enter the size of each memory Block";
    for(int i=0;i<m;i++){
        cin >> blocksize[i];
    }

    cout << "Enter the size of each process";
    for(int i=0;i<n;i++){
        cin >> process[i];
    }
    
    int num;
    cout << " Which Placement Startegies You Want to use \n";
    cout <<" 1 first fit \n 2 next fit \n 3 worst fit \n 4 best fit \n";
    cin >> num;

    switch(num){
        case 1 : firstfit(blocksize,m,process,n);
                 break;
        case 2 : nextfit(blocksize,m,process,n);
                 break;
        case 3 : worstfit(blocksize,m,process,n);
                 break;
        case 4 : bestfit(blocksize,m,process,n);
                 break;

    }

}
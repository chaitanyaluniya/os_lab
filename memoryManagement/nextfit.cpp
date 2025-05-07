# include<iostream>
using namespace std ;


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
int main(){
    int m,n;
    int blocksize[100], process[100];
    cout << "Enter the no of memory blocks";
    cin >> m;
    cout << "Enter the no of processes ";
    cin >> n;
    cout << "Enter the memory blocks size";
    for(int i=0;i<m;i++){
        cin >> blocksize[i];
    }
    cout << "Enter the Process Size";
    for(int j=0;j<n;j++){
        cin >> process[j];
    }

    nextfit(blocksize,m,process,n);
    return 0;
}

// 212 417 112 426
#include<iostream>
using namespace std;

int main(){
    int  numsegments, base[100] , limit[100];
    int segmentno ,physicaladr , logicaladr, offset;

    cout <<"Enter No of Segments ";
    cin >> numsegments;

    cout << "Enter Limits And Base For Each Segments\n ";
    for(int i=0;i<numsegments;i++){
        cout << "Segment " << i << " Base\n";
        cin >> base[i];
        cout << "Segment " << i << " limit\n";
        cin >> limit[i];
    }
    cout << "Enter Segment no";
    cin >> segmentno;

    cout << "Enter The Offset";
    cin >> offset;
    
    if(segmentno >= numsegments || offset >= limit[segmentno]){
        cout << "Invalid logical Address";
    }

    physicaladr = base[segmentno] + offset;
    cout << "Physical Address is " << physicaladr ;

    return 0;
}
/*
 * Program: Horizontal Implementation of SBA.
 * @author: M Santosh Dora
 * @date: 2 March 2016
 */


#include<iostream>
#include<algorithm>

using namespace std;

int totalSlots;                     //Global Variable

bool check(int currentSlot);
void changeTotalSlot(int currentSlot);
void allocateFrame(int **p,int f,int t,int slots, int rank);
void initializeFrame(int **p,const int f, const int t);
void display(int **p, const int f,const int t);
int unused(int **p, const int f, const int t);
int main(){
 int f;                                  //Frequency
 int t;                                  //Time
 static int unusedSlots;
 cout<<"FRAME ALLOCATION:\n";
 cout<<"Enter Frequency:\n";
 cin>>f;
 cout<<"Enter Time(Even Number):\n";
 cin>>t;
int **frame = new int*[f];                //Frame Declaration
for(int i=0;i<f;i++)
  frame[i]=new int[t];                   //Frame Dynamically creation
                        
 initializeFrame(frame,f,t);
  cout<<"Initial Status:\n";
  display(frame,f,t);
  cout<<endl;

//int slots[7];
totalSlots = f*t;
int numberOfFrames;
cout<<"Enter number of slots you want to allcoate in the frame\n";
cin>>numberOfFrames;
int slots[numberOfFrames];
cout<<"Enter "<<numberOfFrames<<" slots to insert in the frame:\n";
for(int i=0;i<numberOfFrames;i++){
    cin>>slots[i];
}

sort(slots,slots+numberOfFrames);                        //Sorting of the slots in ascending order
int rank = 1;                              // Burst Rank


for(int i=numberOfFrames-1;i>=0;i--){
  if(check(slots[i])){
      allocateFrame(frame, f, t, slots[i], rank);
      rank++;
  }else{
    cout<<"Cannot Allocate as Space is insuffficient in the frame for: "<<slots[i]<<" slots\n";
  }
}

cout<<"Final Display:\n";
display(frame,f,t);
cout<<"Slots left in the frame:\n";
if(totalSlots){
 // cout<<"0\n";
  cout<<"SLots for the next frame:\n";
  cout<<abs(totalSlots)<<endl;
}
else
  cout<<totalSlots<<endl;


  unusedSlots = unused(frame,f,t);
 cout<<"UnusedSlots: "<<unusedSlots<<endl;
 return 0;
}
int unused(int **p, int f,int t){
 static int result;
 for(int i=0;i<f;i++){
    for(int j=0;j<t;j++){
       if(p[i][j]==0){
         result+=1;
       }
    }
 }
 return result;
}
void display( int **p,const int f,const int t){
  for(int i=0;i<f;i++){
    for(int j=0;j<t;j++){
      cout<<p[i][j];
    }
  cout<<endl;
  }
}

void initializeFrame(int **p,const int f,const int t){
   for(int i=0;i<f;i++){
     for(int j=0;j<t;j++){
       p[i][j] = 0;
     }
   }  
}/* End of initializeFrame*/

bool  check(int currentSlot){
  if(totalSlots >= currentSlot){
    return true;
  }
 return false;
}

void changeTotalSlot(int currentSlot){
 if(currentSlot %2!=0){
    currentSlot++;
 }
 totalSlots-=currentSlot;
}


void allocateFrame(int **p, int f, int t, int currentSlot, int rank) {
 static int ii, jj, first =0;  
 int tempSlot = currentSlot;

 if(first==0){
    ii = f-1;
    jj = 0;
    first=-1;
 }
   
  if(jj>t-1){
    jj = 0;
  }else{
    if(jj == t-1-1){
      jj=0;
      ii-=2;
    }
  }
  
 if(ii<0){
  cout<<"Full:\n";
  return; 
}
  while(currentSlot) {
         
           p[ii][jj] = rank;
             currentSlot--;
          if(currentSlot && (ii-1)>=0){
              p[ii-1][jj] = rank;
              currentSlot--;
           }      

         jj++;
        if(jj>t-1){
            ii -=2;
            jj=0;
        }
    if(ii<0){
      changeTotalSlot(tempSlot-currentSlot);
      return;  
    }
  }//End of while 
     changeTotalSlot(tempSlot);
} 

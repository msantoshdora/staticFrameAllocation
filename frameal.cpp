/*
 * Program: A simple implementation of SBA algorithm but with a little modification. Here, addititonal slots for considering fragementation overhead is not considered.
 *
 * @author: M Santosh Dora
 * @date: Feb 21 2016
 */




#include<iostream>
#include<algorithm>

using namespace std;

int totalSlots,first = 0,ii,jj;                     //Global Variable

bool check(int currentSlot);
void changeTotalSlot(int currentSlot);
void allocateFrame(int **p,int f,int t,int slots, int rank);
void initializeFrame(int **p,const int f, const int t);
void display(int **p, const int f,const int t);

int main(){
 int f;                                  //Frequency
 int t;                                  //Time
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
cout<<"Enter total number of frames to allocate\n";
cin>>numberOfFrames;
int slots[numberOfFrames];
cout<<"Enter "<<numberOfFrames<<" slots to insert in the frame:\n";
for(int i=0;i<numberOfFrames;i++){
 cin>>slots[i];
}

sort(slots,slots+numberOfFrames);                        //Sorting of the slots in ascending order
int rank = 1;                              // Burst Rank
for(int i=numberOfFrames-1;i>=0;i--){
   if(!check(slots[i])){
      allocateFrame(frame,f,t,slots[i],rank);
      rank++;
   }else{
       cout<<"Can't allocate slot: "<<slots[i]<<endl;
   }
}
cout<<"Final Display:\n";
display(frame,f,t);
cout<<"Slots left in the frame:\n";
if(totalSlots<0){
  cout<<"0\n";
  cout<<"SLots for the next frame:\n";
  cout<<abs(totalSlots)<<endl;
}
else
  cout<<totalSlots<<endl;
 return 0;
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
  if(totalSlots <= currentSlot){
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


void allocateFrame(int **p,int f,int t,int currentSlot, int rank){

  int slot;
  if(first==0){
 	 ii = f-1;
 	 jj = t-1;
         first= -1;
  }
  if(ii<0){
    ii = f -1;
  }
  slot = currentSlot;
  while(currentSlot){
              if(p[ii][jj]==0){
                 p[ii][jj] = rank;
                 currentSlot--;
              }
            
              if(currentSlot && (jj-1)>=0){
                p[ii][jj-1] = rank;
                currentSlot--;
              }
       ii--;
       if(ii<0){
        ii = f-1;
        jj -=2;
       }
  }
 
  changeTotalSlot(slot);
      
}

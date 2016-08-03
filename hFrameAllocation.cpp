/*
 * Program: Minimise wasteage of slots by reservation.
 * @author:M Santosh Dora
 * @date: 10 March 2016
 */

#include<iostream>
#include<algorithm>

using namespace std;

int totalSlots;                     //Global Variable
int fi, fj;
int rank;
int extraSlot;

bool check(int currentSlot);
void changeTotalSlot(int currentSlot);
void allocateFrame(int **p,int f,int t,int slots);
void initializeFrame(int **p,const int f, const int t);
void display(int **p, const int f,const int t);
void fillExtraSlots(int **p, const int f, const int t, int rank);
bool checkForExtraSlot(int currentSlot);
int unused(int **p, const int f, const int t);

int main(){
 static int nextFrameSlot;
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

//  int slots[7];
  totalSlots = f*t;
  int numberOfFrames;
  extraSlot=0;                         //To divide the slots
  cout<<"Enter number of slots you want to allcoate in the frame\n";
  cin>>numberOfFrames;
  int slots[numberOfFrames];
  cout<<"Enter "<<numberOfFrames<<" slots to insert in the frame:\n";

  for(int i=0;i<numberOfFrames;i++){
      cin>>slots[i];
    if(slots[i]%2!=0){
       extraSlot+=1;
    }
    
}

  totalSlots-=extraSlot;                                    //This line reserves extra Slots for impact utilisation


  sort(slots,slots+numberOfFrames);                        //Sorting of the slots in ascending order

  int currentSlot;
//static int rank =1;
  rank =1;
  for(int i=numberOfFrames-1;i>=0;i--){
      if(slots[i]%2!=0){
      if(slots[i]!=1){
         currentSlot=(slots[i]-1);
      }else{
         currentSlot=1;
     }
     }else{
        currentSlot = slots[i];
     }
  if(check(currentSlot)){
     cout<<"slot: "<<slots[i]<<endl; 

     // allocateFrame(frame, f, t, slots[i]);

	  if(slots[i]%2!=0){
		  //cout<<"Slot: "<<slots[i]<<endl;
                 //     if(checkForExtraSlot(currentSlot)){
             fillExtraSlots(frame, f, t,rank);
        // rank++;
             extraSlot--;
          }

     //    }else{

         //   cout<<"Can't Allocate this slot: "<<currentSlot<<endl;
       // }
       //  cout<<"After Extra Slots: \n";
         //display(frame, f,t);
        // slots[i]-=1;
     // }else{
           cout<<"Allocation for the currentSlot: "<<currentSlot<<endl;
           allocateFrame(frame,f, t,currentSlot);
  //   }
    //  cout<<"After allocate Frame: \n";
    // display(frame, f, t);
     // cout<<endl;
        }else{
            nextFrameSlot+=slots[i];
            cout<<"Cannot Allocate,as space is insufficient,in the frame for: "<<slots[i]<<" "<<totalSlots<<endl;
        }  


/*else if(checkForExtraSlot(currentSlot)){
           cout<<"Current Value:"<<currentSlot<<endl;          
            while(currentSlot--){
                 fillExtraSlots(frame,f,t,rank);
                 extraSlot--;
           }
         // rank++;
 }else{
    
    cout<<"Cannot Allocate as Space is insuffficient in the frame for: "<<slots[i]<<" slots\n";
  }*/
}

  cout<<"Final Display:\n";
  display(frame,f,t);
  cout<<"Slots left in the frame: ";
  if(totalSlots<0){
     cout<<"0"<<endl;
  }else
     cout<<totalSlots<<endl;
//if(totalSlots){
 
  cout<<"SLots for the next frame: ";
  cout<<nextFrameSlot<<endl;
//}
//else
 // cout<<totalSlots<<endl;
 //
 int unusedSlots = unused(frame,f,t);
 cout<<"Unused Slots: "<<unusedSlots<<endl;

 return 0;
}

int unused(int **p,const int f, const int t){
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


void allocateFrame(int **p, int f, int t, int currentSlot) {
 static int ii, jj, first =0;            //ii for x-axis, jj for y-axis and first for initial status
 //static int rank;                                       //Burst Rank
// rank++;                   
 int tempSlot = currentSlot;

 if(first==0){
    ii = f-1;
    jj = 0;
    first=-1;
 }
   
 /* if(jj>t-1){
    jj = 0;
  }else{
    if(jj == t-1-1){
      jj=0;
      ii-=2;
    }
  }
  */
 if(ii<0){
  cout<<"Frame is Full to downlink...\n";
  return; 
}
  while(currentSlot) {
            
           if(p[ii][jj]==0){
               p[ii][jj] = rank;
               currentSlot--;
           }
          if(currentSlot && (ii-1)>=0){
              if((ii-1)==fi){
                 jj++;
                 continue;
              }
              if(p[ii-1][jj]==0 ){
                 p[ii-1][jj] = rank;
                 currentSlot--;
             }
           }      

          jj++;
        if(jj>t-1){
           if(p[ii-1][0]==0){
              ii--;
            }else{
            ii -=2;
            }
            jj=0;
        }
    if(ii<0){
       changeTotalSlot(tempSlot-currentSlot);
       return;  
    }
  
  }//End of while 
     changeTotalSlot(tempSlot);
  rank++;
}




void fillExtraSlots(int **p, const int f, const int t, int rank){
     static int first;
     if(first==0){
        fi = 0;
        fj = 0;
        first=-1;
     }
    
    if(fj>(t-1)){
      fi++;
      fj = 0;
    }else{
      p[fi][fj++]=rank;

    }
} 

bool checkForExtraSlot(int currentSlot){
    if(currentSlot<=extraSlot){
       return true;
     }
  return false;
}

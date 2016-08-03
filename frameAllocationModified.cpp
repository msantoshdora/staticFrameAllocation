/*
 * Program: Allocating all Odd Bursts Together And All Even Bursts together.
 * @author:M Santosh Dora
 * @date: 15 March 2016
 */

#include<iostream>
#include<algorithm>

using namespace std;

int totalSlots;                     //Global Variable



bool check(int currentSlot); //To check if slots are available in the frame
void changeTotalSlot(int currentSlot);//To update available slots
void allocateFrame(int **p,int f,int t,int slots);//Allocation Algorithm
void initializeFrame(int **p,const int f, const int t);
void display(int **p, const int f,const int t);


int main(){
 static int nextFrameSlot;
 int f;                                  //Frequency
 int t;                                  //Time
 cout<<"Frame:\n";
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


  totalSlots = f*t;
  int numberOfFrames;
                         
  cout<<"Enter number of Bursts you want to allcoate in the frame\n";
  cin>>numberOfFrames;
  int evenSlots[numberOfFrames];
  int oddSlots[numberOfFrames];

  cout<<"Enter "<<numberOfFrames<<" Bursts to insert in the frame:\n";
   int e=0,o=0;
  for(int i=0;i<numberOfFrames;i++){
      int burst;
      cin>>burst;
      if(burst%2==0){
         evenSlots[e++]=burst;
      }else{
         oddSlots[o++]=burst;
      }
    
  }

  sort(evenSlots,evenSlots+e); //Sort Even bursts
  sort(oddSlots, oddSlots+o); // Sort Odd bursts

  int x=0,y=0;
  int slots[e+o];             //Contains all the even & Odd burst Together
  for(int i=0;i<numberOfFrames;i++){
     
     if(e){
       slots[i]=evenSlots[x++];
       e--;
      
      }else if(o){
      
        slots[i]=oddSlots[y++];
        o--;
       
      }
      
  }

 cout<<endl;
  int currentSlot;

  for(int i=0;i<numberOfFrames;i++){
     if(check(slots[i])){
        cout<<"\nAllocating Burst: "<<slots[i];
        allocateFrame(frame,f,t,slots[i]);   
      
     }else{
        cout<<"\nCannot Allocate burst for: "<<slots[i];
     }   
  }    		 
            

  cout<<"\nFinal Staus:\n";
  display(frame,f,t);
  cout<<"\nSlots left in the frame: ";
  if(totalSlots<0){
     cout<<"0"<<endl;
  }else
     cout<<totalSlots<<endl;

 
  cout<<"\nSlots for the next frame: ";
  cout<<nextFrameSlot<<endl;
 

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
  if(totalSlots >= currentSlot){
    return true;
  }
 return false;
}//End of check


void changeTotalSlot(int currentSlot){
 totalSlots-=currentSlot;
}//end of changeTotalSlot

void allocateFrame(int **p, int f, int t, int currentSlot) {
 static int ii, jj, first =0;            //ii for x-axis, jj for y-axis and first for initial status
 static int rank;
 rank++;                
 int tempSlot = currentSlot;

 if(first==0){
    ii = f-1;
    jj = 0;
    first=-1;
 }
 
  while(currentSlot) {
            
       if(p[ii][jj]==0){
          p[ii][jj] = rank;
          currentSlot--;
       }     
       if(jj>t-1){
         jj=0;
       }      
       if(currentSlot && (ii-1)>=0){
          if(p[ii-1][jj]==0){
             p[ii-1][jj]=rank;
            // jj++;
             currentSlot--;
          }
       }
      
      if(p[ii-1][jj]!=0 && (ii-1)>=0){
         jj++;
      }
      
       if(jj>t-1){
          jj=0;
          if((ii-2)>=0){
             ii-=2;
          }
       }
      
  }//End of while 
     changeTotalSlot(tempSlot);

}//End of AllocateFrame






#include <iostream>
using namespace std;
#include<math.h>
#include <fstream>
#include "Lib.h"
#include <windows.h>
#include<time.h>

// Constants



#define FloorNum 22
//Moving Up Takes Number (0,2,4,6,8,10,12,14,16,18,20) and Follow The relation ((2*Source_Floor)-2)
//Moving Down Takes Number (1,3,5,7,9,11,13,15,17,19,21) and Follow The relation ((2*Source_Floor)-1)


#define MaxWait 60
	
char* FILENAME =new char [20];
char* OUTPUT=new char [20];

//A Function Used To Choose Sample
void ChooseSample(int NUM)
{
	switch (NUM)
	{
		case 1: FILENAME ="Sample1_Simple.txt";
					OUTPUT= "Output1_Simple.txt";
		break;

		case 2: FILENAME ="Sample2_Average.txt";
					OUTPUT= "Output2_Average.txt";
		break;

		case 3: FILENAME ="Sample3_Crowded.txt";
					OUTPUT= "Output3_Crowded.txt";
		break;

		case 4: FILENAME ="Sample4_Overloaded.txt";
					OUTPUT= "Output4_Overloaded.txt";
		break;

		case 5: FILENAME ="Sample 5.txt";
					OUTPUT= "Output 5.txt";
		break;

		case 6: FILENAME ="Sample 6.txt";
					OUTPUT= "Output 6.txt";
		break;

		case 7: FILENAME ="Sample 7.txt";
					OUTPUT= "Output 7.txt";
		break;

		case 8: FILENAME ="Sample 8.txt";
					OUTPUT= "Output 8.txt";
		break;

		case 9: FILENAME ="Sample 9.txt";
					OUTPUT= "Output 9.txt";
		break;

		case 10: FILENAME ="Sample 10.txt";
					OUTPUT= "Output 10.txt";
		break;

		case 11: FILENAME ="Sample 11.txt";
					OUTPUT= "Output 11.txt";
		break;

		case 12: FILENAME ="Sample 12.txt";
					OUTPUT= "Output 12.txt";
		break;

		case 13: FILENAME ="Sample 13.txt";
					OUTPUT= "Output 13.txt";
		break;

		case 14: FILENAME ="Sample 14.txt";
					OUTPUT= "Output 14.txt";
		break;

		case 15: FILENAME ="Sample 15.txt";
					OUTPUT= "Output 15.txt";
		break;

		case 16: FILENAME ="Sample 16.txt";
					OUTPUT= "Output 16.txt";
		break;

		case 17: FILENAME ="Sample 17.txt";
					OUTPUT= "Output 17.txt";
		break;

		case 18: FILENAME ="Sample 18.txt";
					OUTPUT= "Output 18.txt";
		break;

		case 19: FILENAME ="Sample 19.txt";
					OUTPUT= "Output 19.txt";
		break;

		case 20: FILENAME ="Sample 20.txt";
					OUTPUT= "Output 20.txt";
		break;
	}
}

//_____________________________________________________________

//Initilaze And Creates Functions

list *CreateList()
{
	list * temp=new list;

	if (temp==NULL)
	{
		std::cout<<"Not enough memory"<<endl;
		return NULL;
	}
	temp->head=NULL;
	temp->count=0;
	return temp;
}

head * createHead()
{
	head * temp=new head;

	if (temp==NULL)
	{
		std::cout<<"Not enough memory"<<endl;
		return NULL;
	}
	temp->front=temp->rear=NULL;
	temp->count=0;
	return temp;
}

void CreateElev(elev &E,int E_Num)
{
	E.PassHead=CreateList();
	E.PassCnt=0;
	E.E_ID=E_Num;
	E.Dir=STOP;
}

void CreateFloors(head* Floors[])
{
	for(int i=0;i<FloorNum;i++)  	Floors[i]=createHead();
}
//_____________________________________________________________

//Queue Functions

bool EnList(head *&H,pass P)
{
	Node* NewPass= new Node;
	if (!NewPass)
		return false;

	NewPass->P.ID=P.ID;
	NewPass->P.Req_Time=P.Req_Time;
	NewPass->P.Source_floor=P.Source_floor;
	NewPass->P.Dest_floor=P.Dest_floor;
	NewPass->P.Leave_Time=P.Leave_Time;
	NewPass->P.Service_Time=P.Service_Time;
	NewPass->P.Waiting_Time=P.Waiting_Time;
	NewPass->P.Pick_Time=P.Pick_Time;
	NewPass->P.Current_floor=P.Current_floor;
	NewPass->P.Stairs=P.Stairs;
	NewPass->P.num=P.num;
	NewPass->P.E_ID=P.E_ID;
	NewPass->Next = NULL;

	if(H->front==NULL)
	{
		H->front = H->rear = NewPass;
		H->rear->Next = NULL;
		H->count++;
	}
	else
	{
		H->rear->Next= NewPass;
		H->rear = NewPass;
		H->rear->Next=NULL;
		H->count++;
	}
	return true;
}

bool DeList(head *&H,pass & passOut)
{
	
	if (H->front==NULL)	return false;
	else if(H->front->Next==NULL)
	{
		Node * DelNode=H->front;
		passOut=H->front->P;
		H->front=NULL;
		H->rear=NULL;
		delete DelNode;
		H->count--;
		return true;
	}
	else
	{
		Node * DelNode=H->front;
		passOut=H->front->P;
		H->front=H->front->Next;
		delete DelNode;
		H->count--;
		return true;
	}
}
//_____________________________________________________________

// Linked List Functions

bool insertAtEnd(elev &E1,pass passIN)
{
	Node *addedNode=new Node;
	if (E1.PassHead->count==E1.Capacity)	return false;

	addedNode->P.ID=passIN.ID;
	addedNode->P.E_ID=passIN.E_ID;
	addedNode->P.Source_floor=passIN.Source_floor;
	addedNode->P.Req_Time=passIN.Req_Time;
	addedNode->P.Dest_floor=passIN.Dest_floor;
	addedNode->P.Service_Time=passIN.Service_Time;
	addedNode->P.Waiting_Time=passIN.Waiting_Time;
	addedNode->P.Leave_Time=passIN.Leave_Time;
	addedNode->P.Pick_Time=passIN.Pick_Time;
	addedNode->P.Stairs=passIN.Stairs;
	addedNode->P.Current_floor=E1.floor;
	addedNode->P.num=E1.PassHead->count;
	addedNode->Next=NULL;
	

	if (E1.PassHead->head==NULL)
	{
		E1.PassHead->head=addedNode;
		E1.PassHead->count++;
		E1.PassCnt++;
			return true;
	}
	Node *last=E1.PassHead->head;
	while (last->Next!=NULL)
		last=last->Next;
	last->Next=addedNode;
	E1.PassHead->count++;
	E1.PassCnt++;
	return true;
}

bool delFromBeg(elev &E,pass & PassOut)
{
	if(E.PassHead->head==NULL)	return false;

	Node *delNode=E.PassHead->head;

	PassOut.Dest_floor=delNode->P.Dest_floor;
	PassOut.ID=delNode->P.ID;
	PassOut.Source_floor=delNode->P.Source_floor;
	PassOut.Req_Time=delNode->P.Req_Time;
	PassOut.Service_Time=delNode->P.Service_Time;
	PassOut.Waiting_Time=delNode->P.Waiting_Time;
	PassOut.Leave_Time=delNode->P.Leave_Time;
	PassOut.Pick_Time=delNode->P.Pick_Time;
	PassOut.Stairs=delNode->P.Stairs;
	PassOut.Current_floor=0;
	PassOut.E_ID=0;
	PassOut.num=0;

	E.PassHead->head=E.PassHead->head->Next;
	E.PassHead->count--;
	E.PassCnt--;
	delete delNode;
	return true;
}

bool delFromBeg(elev &E)
{
	if(E.PassHead->head==NULL)
	{
		std::cout<<"Empty List"<<endl;
		return false;
	}
	Node *delNode=E.PassHead->head;
	E.PassHead->head=E.PassHead->head->Next;
	E.PassHead->count--;
	E.PassCnt--;
	delete delNode;
	return true;
}

//_____________________________________________________________

//Moving Functions
// Move Passenger from AllPAssList to his floor
bool MoveToFloor(head *&AllPassList, head**Floors ,int Sys_Time)
{
	if(AllPassList==NULL)return false;
	pass MovedPass;
	while(ValidReq(AllPassList,Sys_Time))
	{
		DeList(AllPassList,MovedPass);
		MovedPass.Current_floor=MovedPass.Source_floor;
		MovedPass.E_ID=0;
		if(MovedPass.Dest_floor>MovedPass.Source_floor)
		{
			MovedPass.num=(Floors[2*(MovedPass.Source_floor-1)]->count);//For Drawing
			EnList(Floors[2*(MovedPass.Source_floor-1)],MovedPass);		//Moving Up
		}
		else
		{
			MovedPass.num=(Floors[2*(MovedPass.Source_floor-1)+1]->count);//For Drawing
			EnList(Floors[2*(MovedPass.Source_floor-1)+1],MovedPass);		//Moving Down
		}
	}
	return true;
}

bool MoveFromElev(elev& E,list*&PassList,int &Sys_Time)
{
	if(E.PassHead->head == NULL)	return false;
	pass PassOut;

	while(E.PassHead->head != NULL && E.PassHead->head->P.Dest_floor==E.floor)
	{
		delFromBeg(E,PassOut);
		PassOut.Leave_Time=Sys_Time;
		PassOut.Service_Time=Sys_Time-PassOut.Pick_Time;
		PassOut.E_ID=E.E_ID;
		AddToList(PassList,PassOut);
	}
	if(E.PassHead->head == NULL) return true;

	Node*pre=E.PassHead->head;
	Node*curr = E.PassHead->head->Next;
	while(curr!=NULL)
	{
		if(curr->P.Dest_floor==E.floor)
		{
			PassOut= curr->P;
			PassOut.Leave_Time=Sys_Time;
			PassOut.Service_Time=Sys_Time-PassOut.Pick_Time;
			AddToList(PassList,PassOut);
			pre->Next=curr->Next;
			delete curr;
			E.PassCnt--;
			E.PassHead->count--;
			curr=pre->Next;
		}
		else
		{
			curr=curr->Next;
			pre=pre->Next;
		}
	}
	Sys_Time++;
	return true;
} //ana shakek feha

bool FloorToElev(head *Floors ,elev  &E,int &Sys_Time) //Nazel el Passenger el 2awel
{
	pass PassOut;
	int count=E.PassHead->count;
	if(Floors->front==NULL)return false;
	if(E.PassHead->head==NULL ||(E.PassHead->head->P.Dest_floor>E.floor&&Floors->front->P.Dest_floor>Floors->front->P.Source_floor))
		{
			while(Floors->front!=NULL &&E.Capacity!=E.PassHead->count)
			{
				DeList(Floors,PassOut);
				PassOut.Pick_Time=Sys_Time-1;
				PassOut.Waiting_Time=Sys_Time-PassOut.Req_Time;
				PassOut.E_ID=E.E_ID;
				insertAtEnd(E,PassOut);
			}
			if (count<E.PassHead->count)
			{
				E.Dir=STOP;
				Sys_Time++;
				return true;
			}
	}

	else if(E.PassHead->head==NULL ||(E.PassHead->head->P.Dest_floor<E.floor&&Floors->front->P.Dest_floor<Floors->front->P.Source_floor))
		{
			while(Floors->front!=NULL &&E.Capacity!=E.PassHead->count)
				{
					DeList(Floors,PassOut);
					PassOut.Pick_Time=Sys_Time;
					PassOut.Waiting_Time=Sys_Time-PassOut.Req_Time;
					PassOut.E_ID=E.E_ID;
					insertAtEnd(E,PassOut);
				}
			if (count<E.PassHead->count)
			{
				E.Dir=STOP;
				Sys_Time++;
				return true;
			}
		}
		return false;
}

bool MovingElev(elev &E1,elev &E2,head*Floors[],head *&AllPassList,list*&OutPutList,int &Sys_Time,int Mode)
{
	pass  Pass,Pass2;
	Pass.Source_floor=0;
	if(E1.Dir==STOP && E2.Dir==STOP)	
	{
		if(E1.PassHead->count==0 &&E2.PassHead->count!=0)
		{
			if(FindClosest(E1,Floors,Pass))MoveToPass(E1,Pass);
			if(E2.PassHead->head->P.Dest_floor>E2.floor)
			{
				E2.Dir=UP;
				E2.floor++;
			}
			else
			{
				E2.Dir=DOWN;
				E2.floor--;
			}
			if(PassEnterAndLeave(E1,Floors))
				{
					EnterAndLeave(E1,E2,Floors,AllPassList,OutPutList,Sys_Time,Mode);
					DrawAll (E1,E2,Floors,Sys_Time,Mode);
					return true;
				}
			
			else if(EnterAndLeave(E1,E2,Floors,AllPassList,OutPutList,Sys_Time,Mode))
				{
					Sys_Time++;
					Stairs(Floors,OutPutList,Sys_Time);
					DrawAll (E1,E2,Floors,Sys_Time,Mode);
					return true;
				}
			else
			{
				Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
				DrawAll (E1,E2,Floors,Sys_Time,Mode);
				Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
				DrawAll (E1,E2,Floors,Sys_Time,Mode);
				return true;
			}
		}
		else if(E1.PassHead->count!=0 &&E2.PassHead->count==0)
		{
			if(FindClosest(E2,Floors,Pass))MoveToPass(E2,Pass);
			if(E1.PassHead->head->P.Dest_floor>E1.floor)
			{
				E1.Dir=UP;
				E1.floor++;
			}
			else
			{
				E1.Dir=DOWN;
				E1.floor--;
			}
			if(PassEnterAndLeave(E2,Floors))
			{
				EnterAndLeave(E2,E1,Floors,AllPassList,OutPutList,Sys_Time,Mode);
				DrawAll (E1,E2,Floors,Sys_Time,Mode);
				return true;
			}
			
			else if(EnterAndLeave(E2,E1,Floors,AllPassList,OutPutList,Sys_Time,Mode))
				{
					Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
					DrawAll (E1,E2,Floors,Sys_Time,Mode);
					return true;
				}
			else
			{
				Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
				DrawAll (E1,E2,Floors,Sys_Time,Mode);
				Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
				DrawAll (E1,E2,Floors,Sys_Time,Mode);
				return true;
			}
		}
		else if(E1.PassHead->count==0 &&E2.PassHead->count==0)
		{
			if(FindClosest(E1,Floors,Pass)&&FindClosest(E2,Floors,Pass2)) 
				{
					if(Pass.Source_floor==Pass2.Source_floor&&((Pass.Dest_floor>Pass.Source_floor)&&(Pass2.Dest_floor>Pass2.Source_floor)||(Pass.Dest_floor<Pass.Source_floor)&&(Pass2.Dest_floor<Pass2.Source_floor)))		//Pass=Pass2
						{
							if(abs(E1.floor-Pass.Source_floor)<=abs(E2.floor-Pass.Source_floor))
								{
									MoveToPass(E1,Pass);
									if(PassEnterAndLeave(E1,Floors))
										{
											EnterAndLeave(E1,E2,Floors,AllPassList,OutPutList,Sys_Time,Mode);
											DrawAll (E1,E2,Floors,Sys_Time,Mode);
											return true;
										}
									else if(EnterAndLeave(E2,E1,Floors,AllPassList,OutPutList,Sys_Time,Mode))
										{
											Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
											DrawAll (E1,E2,Floors,Sys_Time,Mode);
											return true;
										}
									else
									{
										Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
										DrawAll (E1,E2,Floors,Sys_Time,Mode);
										Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
										DrawAll (E1,E2,Floors,Sys_Time,Mode);
										return true;
									}
							}
							else 
								{
									MoveToPass(E2,Pass);	
									if(PassEnterAndLeave(E1,Floors))
										{
											EnterAndLeave(E1,E2,Floors,AllPassList,OutPutList,Sys_Time,Mode);
											DrawAll(E1,E2,Floors,Sys_Time,Mode);
											return true;
										}
									else if(EnterAndLeave(E1,E2,Floors,AllPassList,OutPutList,Sys_Time,Mode))
										{
											Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
											DrawAll (E1,E2,Floors,Sys_Time,Mode);
											return true;
										}
									else
									{
										Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
										DrawAll (E1,E2,Floors,Sys_Time,Mode);
										Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
										DrawAll (E1,E2,Floors,Sys_Time,Mode);
										return true;
									}
								}
						}
					else
						{
							MoveToPass(E1,Pass);
							MoveToPass(E2,Pass2);
							
							Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
							DrawAll (E1,E2,Floors,Sys_Time,Mode);
							Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
							DrawAll (E1,E2,Floors,Sys_Time,Mode);
							return true;
						}
				}
			else
			{
				if(!PassInFloors(Floors)&&AllPassList->count==0)return true;
				Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
				EnterAndLeave(E1,E2,Floors,AllPassList,OutPutList,Sys_Time,Mode);
				DrawAll (E1,E2,Floors,Sys_Time,Mode);
				return MovingElev(E1,E2,Floors,AllPassList,OutPutList,Sys_Time,Mode);
			}
		}
		else if(E1.PassHead->count!=0 &&E2.PassHead->count!=0)
		{
			if(E1.PassHead->head->P.Dest_floor>E1.floor)E1.Dir=UP;
			else E1.Dir=DOWN;

			if(E2.PassHead->head->P.Dest_floor>E2.floor)E2.Dir=UP;
			else E2.Dir=DOWN;
		}
	}

if (E2.Dir==STOP&&E1.Dir!=STOP)
	{
		if(E1.PassHead->head!=NULL)
		{
			if (E1.Dir==UP)E1.floor++;
			else E1.floor--;
		}
		else if(FindClosest(E1,Floors,Pass))	MoveToPass(E1,Pass);
		else E1.Dir=STOP;

		if(PassEnterAndLeave(E2,Floors))
			{
				EnterAndLeave(E2,E1,Floors,AllPassList,OutPutList,Sys_Time,Mode);
				DrawAll (E1,E2,Floors,Sys_Time,Mode);
				return true;
			}
			
		else if(EnterAndLeave(E2,E1,Floors,AllPassList,OutPutList,Sys_Time,Mode))
			{
				Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
				DrawAll (E1,E2,Floors,Sys_Time,Mode);
				return true;
			}
		else
			{
				if(E2.PassHead->head==NULL)
					{
						if(FindClosest(E2,Floors,Pass2))
							if(Pass.Source_floor!=Pass2.Source_floor||Pass.Dest_floor!=Pass2.Dest_floor)	
								MoveToPass(E2,Pass2);
					}
				else if(E2.PassHead->head->P.Dest_floor>E2.floor)	
					{
						E2.Dir=UP;
						E2.floor++;
					}
				else
					{
						E2.Dir=DOWN;
						E2.floor--;
					}
					Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
					DrawAll (E1,E2,Floors,Sys_Time,Mode);
					Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
					DrawAll (E1,E2,Floors,Sys_Time,Mode);
					return true;
				}
		return true;
	}
	if (E1.Dir==STOP&&E2.Dir!=STOP)
	{
		if(E2.PassHead->head!=NULL)
		{
			if (E2.Dir==UP)E2.floor++;
			else E2.floor--;
		}
		else if(FindClosest(E2,Floors,Pass))	MoveToPass(E2,Pass);
		else E2.Dir=STOP;

		if(PassEnterAndLeave(E1,Floors))
			{
				EnterAndLeave(E1,E2,Floors,AllPassList,OutPutList,Sys_Time,Mode);
				DrawAll (E1,E2,Floors,Sys_Time,Mode);
				return true;
			}
			
		else if(EnterAndLeave(E1,E2,Floors,AllPassList,OutPutList,Sys_Time,Mode))
			{
				Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
				DrawAll (E1,E2,Floors,Sys_Time,Mode);
				return true;
			}
		else
			{
				if(E1.PassHead->head==NULL)
					{
						if(FindClosest(E1,Floors,Pass2))
							if(Pass.Source_floor!=Pass2.Source_floor||Pass.Dest_floor!=Pass2.Dest_floor)	
								MoveToPass(E1,Pass2);
					}
				else if(E1.PassHead->head->P.Dest_floor>E1.floor)	
					{
						E1.Dir=UP;
						E1.floor++;
					}
				else
					{
						E1.Dir=DOWN;
						E1.floor--;
					}
					Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
					DrawAll (E1,E2,Floors,Sys_Time,Mode);
					Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
					DrawAll (E1,E2,Floors,Sys_Time,Mode);
					return true;
				}
		return true;
	}
		
	if(E1.Dir!=STOP &&E2.Dir!=STOP)
	{
		if(E1.PassHead->head!=NULL)
		{
			if (E1.Dir==UP)E1.floor++;
			else 	E1.floor--;
		}
		else 
		{
			if(FindClosest(E1,Floors,Pass))MoveToPass(E1,Pass);
			else E1.Dir=STOP;
		}
		if(E2.PassHead->head!=NULL)
		{
			if (E2.Dir==UP)E2.floor++;
			else 	E2.floor--;
		}
		else 
		{
			if(FindClosest(E2,Floors,Pass))MoveToPass(E2,Pass);
			else E2.Dir=STOP;
		}
		Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
		DrawAll (E1,E2,Floors,Sys_Time,Mode);
		Sys_Time++;Stairs(Floors,OutPutList,Sys_Time);
		DrawAll (E1,E2,Floors,Sys_Time,Mode);
		return true;
	}
	return false;
}

bool MoveToPass(elev &E,pass Pass)
{
	if(E.floor<Pass.Source_floor)
		{
			E.Dir=UP;
			E.floor++;
			return true;
		}
	else if(E.floor>Pass.Source_floor)
		{
			E.Dir=DOWN;
			E.floor--;
			return true;
		}
			E.Dir=STOP;
			return false;
}

//_____________________________________________________________

//Functions Used in ElevSimulation

void AddToList(list*&PassList, pass passIN)
{
	Node* NewNode = new Node;
	NewNode->P.ID=passIN.ID;
	NewNode->P.E_ID=passIN.E_ID;
	NewNode->P.Source_floor=passIN.Source_floor;
	NewNode->P.Req_Time=passIN.Req_Time;
	NewNode->P.Dest_floor=passIN.Dest_floor;
	NewNode->P.Pick_Time=passIN.Pick_Time;
	NewNode->P.Service_Time=passIN.Service_Time;
	NewNode->P.Leave_Time=passIN.Leave_Time;
	NewNode->P.Waiting_Time=passIN.Waiting_Time;
	NewNode->P.Stairs=passIN.Stairs;
	NewNode->Next=NULL;

	if(PassList->head==NULL)
	{
		PassList->head=NewNode;
		PassList->count++;
		return;
	}

	//Arrange Them in an Ascending Order according to their Tsrv "Pick_Time"
	Node*Curr=PassList->head;
	if(NewNode->P.Pick_Time<PassList->head->P.Pick_Time)
	{
		NewNode->Next=PassList->head;
		PassList->head=NewNode;
		PassList->count++;
		return;
	}
	else if(PassList->head->Next==NULL)
	{
		if(NewNode->P.Pick_Time>PassList->head->P.Pick_Time)
		{
			PassList->head->Next=NewNode;
			PassList->count++;
			return;
		}
		if(NewNode->P.Pick_Time=PassList->head->P.Pick_Time&&NewNode->P.ID>PassList->head->P.ID)
		{
			PassList->head->Next=NewNode;
			PassList->count++;
			return;
		}
		else
		{
			NewNode->Next=PassList->head;
			PassList->head=NewNode;
			PassList->count++;
			return;
		}
	}
	else
	{
		while(Curr->Next!=NULL&&Curr->Next->P.Pick_Time<NewNode->P.Pick_Time)
			Curr=Curr->Next;
		while(Curr->Next!=NULL&&Curr->Next->P.Pick_Time==NewNode->P.Pick_Time&&Curr->Next->P.ID<NewNode->P.ID)
			Curr=Curr->Next;
		NewNode->Next=Curr->Next;
		Curr->Next=NewNode;
		PassList->count++;
		return;
	}
	
}	

bool FindClosest(elev E,head*Floors[],pass& passOut)
{
	int min=INT_MAX;
	pass Addedpass;
	for(int i=0;i<FloorNum;i++)
		if(Floors[i]->front!=NULL)
		{
			Addedpass=Floors[i]->front->P;
			if(min>abs(E.floor-Addedpass.Current_floor))
			{
					passOut=Floors[i]->front->P;
					min=abs(E.floor-passOut.Current_floor);
			}
		}
	if (min==INT_MAX) return false;
	return true;
}

bool Stop(elev &E)
{
	Node*Curr=E.PassHead->head;
	while(Curr!=NULL)
	{
		if(Curr->P.Dest_floor==E.floor)
		{
			E.Dir=STOP;
			return true;
		}
		else
			Curr=Curr->Next;
	}
	return false;
}

bool PassInFloors(head*Floors[])
{
	for(int i=0;i<FloorNum;i++)
		if(Floors[i]->front!=NULL) return true;
	return false;
}

bool EnterAndLeave(elev &E1,elev E2,head* Floors[],head *&AllPassList,list*&OutPutList,int &Sys_Time,int Mode)
{
	int x=Sys_Time;
	MoveToFloor(AllPassList,Floors,Sys_Time);
	Stairs(Floors,OutPutList,Sys_Time);

	if(Stop(E1))
	{
		MoveFromElev(E1,OutPutList,Sys_Time);
		if(E1.E_ID==1)DrawAll (E1,E2,Floors,Sys_Time,Mode);
		else DrawAll (E2,E1,Floors,Sys_Time,Mode);
	}

	if(E1.E_ID==1)
	{
		if(FloorToElev(Floors[2*(E1.floor-1)],E1,Sys_Time))DrawAll (E1,E2,Floors,Sys_Time,Mode);
		if(FloorToElev(Floors[2*(E1.floor-1)+1],E1,Sys_Time))DrawAll (E1,E2,Floors,Sys_Time,Mode);
	}
	else
	{
		if(FloorToElev(Floors[2*(E1.floor-1)],E1,Sys_Time))DrawAll (E2,E1,Floors,Sys_Time,Mode);
		if(FloorToElev(Floors[2*(E1.floor-1)+1],E1,Sys_Time))DrawAll (E2,E1,Floors,Sys_Time,Mode);
	}
	if (Sys_Time-x==0)return false;
	return true;
}

bool PassEnterAndLeave(elev E,head *Floors[])
{
	int x=0;
		if(E.PassHead->head != NULL && E.PassHead->head->P.Dest_floor==E.floor)x++;
		if(Floors[2*(E.floor)-2]->front!=NULL&&(E.PassHead->head==NULL ||(E.PassHead->head->P.Dest_floor>E.floor&&Floors[2*(E.floor)-2]->front->P.Dest_floor>Floors[2*(E.floor)-2]->front->P.Source_floor)))x++;
		else if(Floors[2*(E.floor)-1]->front!=NULL&&(E.PassHead->head==NULL ||(E.PassHead->head->P.Dest_floor<E.floor&&Floors[2*(E.floor)-1]->front->P.Dest_floor<Floors[2*(E.floor)-1]->front->P.Source_floor)))x++;
		if(x==2)return true;
		return false;
}

//_____________________________________________________________

//Read From File and Write To File Function

void ReadFile(elev &E1,elev &E2,head *&AllPassList) 
{
	ifstream in;
	pass P; 
	AllPassList=createHead();

	in.open(FILENAME,ios::in);

	if (in.is_open())
	{
		in>>E1.floor>>E1.Capacity>>E2.floor>>E2.Capacity;
		E1.floor++; //because we made our floors start from 1 to 11 not from 0 to 10
		E2.floor++;
	}

	while (in>>P.ID>>P.Req_Time>>P.Source_floor>>P.Dest_floor)
	{
		P.Stairs=false;
		P.E_ID=0;
		P.Service_Time=0;
		P.Waiting_Time=0;
		P.Leave_Time=0;
		P.Pick_Time=0;
		P.Current_floor=0;
		P.num=0;
		P.Source_floor++;
		P.Dest_floor++;
		EnList(AllPassList,P);
	}
	in.close();
}

void DisplayOutput(list*PassList)  //assume list is ordered according to Picktime then ID (if same Picktime)
{
	Node*ptr = PassList->head;
	if (!ptr) return;
	ofstream outputfile(OUTPUT, ios::out);
	outputfile << "Tsrv\tP_ID\tE_ID\tWT\tST" << endl;
	int Sum_WT=0, Sum_ST=0, Sum_stairs=0;
	while (ptr) {
		outputfile << ptr->P.Pick_Time << "\t" << ptr->P.ID << "\t" << ptr->P.E_ID << "\t" << ptr->P.Waiting_Time << "\t" << ptr->P.Service_Time << endl;
		Sum_WT += ptr->P.Waiting_Time;
		Sum_ST += ptr->P.Service_Time;
		if (ptr->P.Stairs) Sum_stairs++;			//boolean variable Stairs
		ptr = ptr->Next;
	}
	outputfile << "Avg passengers waiting time=" << Sum_WT / PassList->count<<endl;
	outputfile << "Avg passengers service time=" << Sum_ST / PassList->count<<endl;
	outputfile << "The percentage of passengers who used stairs instead of the elevators=" << (Sum_stairs / (PassList->count/1.00)) * 100 << "%" << endl;
	outputfile.close();
}

//_____________________________________________________________

// Functions That are used to check on Validation, Using Stairs

bool ValidReq(head *AllPassList,int Sys_time)

{
	if(AllPassList->front==NULL)	return false;
	 if(AllPassList->front->P.Req_Time <= Sys_time)	return true;
	return false;
}

bool Stairs(head*Floors[],list*&PassList,int Sys_Time)
{
	pass PassOut;
	for(int i = 0; i<FloorNum;i++)
		if(Floors[i]->front!=NULL&&(Sys_Time-Floors[i]->front->P.Req_Time)>=MaxWait)
		{
			DeList(Floors[i],PassOut);
			PassOut.Waiting_Time=60;
			PassOut.Leave_Time=Sys_Time+(7*(abs(PassOut.Dest_floor-PassOut.Source_floor)));
			PassOut.Service_Time= PassOut.Leave_Time-PassOut.Req_Time-PassOut.Waiting_Time;
			PassOut.E_ID=0;
			PassOut.Pick_Time=Sys_Time;
			PassOut.Stairs=true;
			AddToList(PassList,PassOut);
		}
	return true;
}

//_____________________________________________________________

// Functions That are Used to Print

void	PrintElev(elev E)
{
	cout<<"Elevator "<<E.E_ID;
	cout<<"\tFloor = "<<E.floor<<"\tDirection= ";
	if(E.Dir==STOP)cout<<"STOP";
	else if(E.Dir==UP)cout<<"UP";
	else if(E.Dir==DOWN)cout<<"DOWN";
	cout<<"\t\tCapacity= "<<E.Capacity<<"\tPassengers Count= "<<E.PassHead->count<<endl;
}

void PrintWaitList(head*Floor[])
{
	int Sum=0;
	for(int i=0;i<FloorNum;i++)Sum+=Floor[i]->count;
	cout<<"Waiting Valid List= "<<Sum<<endl;
}
//_____________________________________________________________

// Elevator Simulation Function

bool ElevSim(elev &E1,elev &E2,head *AllpassList,int Mode)
{
	const clock_t begin_time = clock();
	CreateElev(E1,1);
	CreateElev(E2,2);
	AllpassList=new head;
	AllpassList=createHead();
	list* OutPutList=new list;
	OutPutList=CreateList();
	head *  Floors[FloorNum];
	CreateFloors(Floors);

	ReadFile(E1,E2,AllpassList);

	int Sys_Time=0;
	if(Mode==1||Mode==2)SetWindow();

	while(AllpassList->count!=0 || E1.PassHead->count!=0 || E2.PassHead->count!=0 || PassInFloors(Floors))
	{
		EnterAndLeave(E1,E2,Floors,AllpassList,OutPutList,Sys_Time,Mode);
		EnterAndLeave(E2,E1,Floors,AllpassList,OutPutList,Sys_Time,Mode);
		MovingElev(E1,E2,Floors,AllpassList,OutPutList,Sys_Time,Mode);
	}
	DisplayOutput(OutPutList);
	if(Mode!=1&&Mode!=2)
	{
		float Time=(float( clock () - begin_time ) /  CLOCKS_PER_SEC)*1000;
		ofstream outputfile(OUTPUT, ios::app);
		outputfile<<endl<<"Time Takken = ";
		outputfile<< Time<<" MilliSecond "<<(char)126<<" "<<ceil(Time/1000)<<" Second ";
		outputfile<<(char)126<<" "<<((int)Time/60000)<<" Minute "<<(char)126<<" "<<((int)Time/3600000)<<" Hour "<<endl;
		outputfile.close();
	}
	return true;
} 
//_____________________________________________________________

/*A function to set the position of cursor on the screen*/
void gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	_COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hConsole, pos);
}

/*A function to set the command window lenght and height for the GUI specification*/
void SetWindow()
{
	system("mode 150,55");   //Set mode to ensure window does not exceed buffer size
	SMALL_RECT WinRect = { 0, 0, CmdWidth, CmdHeight };   //New dimensions for window in 8x12 pixel chars
	SMALL_RECT* WinSize = &WinRect;
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize);   //Set new size for window
}

/*A function to color the cmd text*/
void color(int thecolor)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,
		thecolor | FOREGROUND_INTENSITY);
}

//_____________________________________________________________

//Draw Functions

/*A function to draw the 11 floors*/
void DrawFloors()
{
	system("CLS");
	color(FOREGROUND_RED|FOREGROUND_BLUE);
	
	for (int j = NumberOfFloors; j >=0  ; j--)
	{
		gotoxy(0, (NumberOfFloors-j)*FloorHeight);
		if (j == NumberOfFloors)	cout << "Roof          "; 
		else if( j == 0) cout<<"Ground Floor ";
		else { cout << "Floor number " << j; }
		
		for (int i = 0; i < CmdWidth-15; i++)
			cout << "-";
	
	}
	color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	//gotoxy(0, CmdHeight - 6);

}

/* A function that draws an elevator*/
void DrawElev(elev & E)
{
	E.Xstrt = (E.E_ID -1)* (E.W+2) + WTG_list_Wdth + 5;
	E.Ystrt = GND_LINE - (E.floor)*FloorHeight;
	gotoxy(E.Xstrt, E.Ystrt );
	if(E.Dir!=STOP)color(FOREGROUND_BLUE | FOREGROUND_GREEN);
	else color(FOREGROUND_RED);
	for (int i = 0; i < E.W; i++)
	{
		cout << "=";
	}

	gotoxy(E.Xstrt, (E.Ystrt +1));
	cout << " Elev " << E.E_ID;
	gotoxy(E.Xstrt, (E.Ystrt + FloorHeight));
	for (int i = 0; i < E.W; i++)
	{
		cout << "=";
	}

	for (int j = 0; j < FloorHeight+1; j++)
	{
		gotoxy(E.Xstrt, E.Ystrt+j);
		cout << "|";
		gotoxy(E.Xstrt+E.W, E.Ystrt + j);
		cout << "|";
	}

	color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(0, CmdHeight - 6);

	//Now draw the passengers inside this elevator
	//DrawPassengers(E.PassHead, E.PassCnt, &E);
}

/*A function that draws a passanger */
void DrawPass(pass P, elev pE )
{
	int xpass;
	int ypass;
	if (P.E_ID==0)	//Not in an elevator
	{
		if (P.Dest_floor>P.Source_floor)//Moving UP
		{
			xpass = 20 + P.num*4;
			ypass = GND_LINE - ((P.Current_floor-1)* FloorHeight)-1;
			color(FOREGROUND_GREEN);
			gotoxy(xpass+1, ypass);
			std::cout << (char)PassShape << P.ID; //Draw the passanger
		}
		else
		{
			xpass = 20 + P.num*4;
			ypass = GND_LINE - ((P.Current_floor+1)* FloorHeight)+5;
			color(FOREGROUND_BLUE);
			gotoxy(xpass+1, ypass);
			std::cout << (char)PassShape << P.ID; //Draw the passanger
		}
		
	}
	else 
	{
		if (P.Dest_floor>P.Source_floor)//Moving UP
		{
			xpass = pE.Xstrt+P.num*4;
			ypass = pE.Ystrt+FloorHeight-1;
			color(FOREGROUND_GREEN);
			gotoxy(xpass+1, ypass);
			std::cout << (char)PassShape << P.ID; //Draw the passanger
		}
		else
		{
			xpass = pE.Xstrt+P.num*4;
			ypass = pE.Ystrt+FloorHeight-1;
			color(FOREGROUND_BLUE);
			gotoxy(xpass+1, ypass);
			std::cout << (char)PassShape << P.ID; //Draw the passanger
		}
	}
	color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(0, CmdHeight - 6);
}

/*A Function to Draw passengers in Floors*/ 
void DrawPassengersInFloors(head* Floors[],elev pE)
{
	Node*Curr;
	for(int i=0; i<FloorNum; i++)
	{
		Curr=Floors[i]->front;
		
		while(Curr!=NULL)
		{
			DrawPass(Curr->P, pE);
			Curr=Curr->Next;
		}
	}
}

/*A Function to Draw passengers in Elevator*/ 
void	DrawPassengersInElevator(elev E)
{
	Node*Curr=E.PassHead->head;
	int i=0;
	while(Curr!=NULL)	//passenger is inside an elevator
	{
		Curr->P.Current_floor = E.floor; //update passenger floor
		Curr->P.num=i;
		DrawPass(Curr->P, E);
		Curr=Curr->Next;
		i++;
	}
}

/*A function to draw a list of passnegers exist in all regions and ensure there is no overflow in the drawing*/
void DrawAll(elev E1,elev E2,head*Floors[],int Sys_Time,int Mode)
{
	if (Mode==1||Mode==2)
	{
		//system("color 70");
		DrawFloors();
		DrawElev(E1);
		DrawElev(E2);
		//system("color 70");
		DrawPassengersInFloors(Floors,E1);
		DrawPassengersInElevator(E1);
		DrawPassengersInElevator(E2);
		cout<<"Simulation Time= "<<Sys_Time<<endl;
		PrintElev(E1);
		PrintElev(E2);
		PrintWaitList(Floors);
		if(Mode==1) cin.get();
		if(Mode==2)Sleep(1000);
		return;
		}
	else return;
}

//_____________________________________________________________
#include <iostream>
using namespace std;

#include <fstream>

#include <windows.h>

// Constants

#define NumberOfFloors  11
#define FloorHeight	    4

#define CmdWidth		150
#define CmdHeight		55

#define ElevWidth		40
#define ElevHeight	    3

#define WTG_list_Wdth   50	//Width of the waiting list on the screen

#define ELEV1XStrt		60
#define ELEV1YStrt		FloorHeight*NumberOfFloors
//Ground line position on the screen
#define GND_LINE		FloorHeight*NumberOfFloors

#define ELEV2XStrt		ELEV1XStrt + ElevWidth + 5 
#define ELEV2YStrt		FloorHeight*NumberOfFloors

//#define PassShape		219
#define PassShape		178//ASCII code of passenger char shape 
//define PassShape		254,221,222,178

#define DUMMY 10
//_____________________________________________________________

//Structures and Enumartion

enum DIRECTION
{
	STOP, UP, DOWN  //Possible elevator states 
};

struct pass
{
	int ID;				//Each passenger has a unique ID (sequence number)
	int E_ID;			//which elevator 1 or 2 (0 if not inside any elevator)
	int Current_floor;	//For drawing (Graphical info) 
	int Source_floor;	//Source Floor
	int Dest_floor;		//Destination Floor
	int Req_Time;		//Request Time
	bool Stairs;			//initially false
	int num;  // refers to the passenger's number in the elev or on the floor , just to draw without overlapping
	int Waiting_Time;
	int Pick_Time;
	int Leave_Time;
	int Service_Time;
};

struct Node
{
	pass P;
	Node* Next;
};

struct list
{
	Node * head;
	int count ;
};

struct head
{
	Node * front;
	Node * rear;
	int count;
};

struct elev
{
	//Graphical info for elevator
	int Xstrt;
	int Ystrt;
	const static int W = ElevWidth;	//width
	const static int L = ElevHeight;  //Height

	//Simulation info for elevetor
	int floor;		//current floor
	DIRECTION Dir;	//elevator moving direction
	int E_ID;		// elevator ID
	int Capacity;	//elevator capacity

	int PassCnt;	//number of current passengers in this elevator
	list* PassHead; //Linked List of passengers

	//Note: for the sake of demo, passengers list in the elevator is created using very simple
	//Data Structure
	//You MUST change that to a more suitable DS
};
//_____________________________________________________________

//Functions Prototype

//A Function Used To Choose Sample
void ChooseSample(int NUM);

//_____________________________________________________________

//Initilaze And Creates Functions

list *CreateList();

head * createHead();

void CreateElev(elev &E,int E_Num);

void CreateFloors(head* Floors[]);
//_____________________________________________________________

//Queue Functions

bool EnList(head *&H,pass P);

bool DeList(head *&H,pass & passOut);
//_____________________________________________________________

// Linked List Functions

bool insertAtEnd(elev &E1,pass passIN);

bool delFromBeg(elev &E,pass & PassOut);

bool delFromBeg(elev &E);

//_____________________________________________________________

//Moving Functions

bool MoveToFloor(head *&AllPassList, head**Floors ,int Sys_Time);

bool MoveFromElev(elev& E,list*&PassList,int &Sys_Time);

bool FloorToElev(head *Floors ,elev  &E,int &Sys_Time);

bool MovingElev(elev &E1,elev &E2,head*Floors[],head *&AllPassList,list*&OutPutList,int &Sys_Time,int Mode);

bool MoveToPass(elev &E,pass Pass);

//_____________________________________________________________

//Functions Used in ElevSimulation

void AddToList(list*&PassList, pass passIN);	

bool FindClosest(elev E,head*Floors[],pass& passOut);

bool Stop(elev &E);

bool PassInFloors(head*Floors[]);

bool EnterAndLeave(elev &E1,elev E2,head* Floors[],head *&AllPassList,list*&OutPutList,int &Sys_Time,int Mode);

bool PassEnterAndLeave(elev E,head *Floors[]);

//_____________________________________________________________

//Read From File and Write To File Function

void ReadFile(elev &E1,elev &E2,head *&AllPassList);

void DisplayOutput(list*PassList);

//_____________________________________________________________

// Functions That are used to check on Validation, Using Stairs

bool ValidReq(head *AllPassList,int time);

bool Stairs(head*Floors[],list*&PassList,int Sys_Time);

//_____________________________________________________________

// Functions That are Used to Print

void	PrintElev(elev E);

void PrintWaitList(head*Floor[]);
//_____________________________________________________________

// Elevator Simulation Function

bool ElevSim(elev &E1,elev &E2,head *AllpassList,int Mode); 
//_____________________________________________________________

/*A function to set the position of cursor on the screen*/
void gotoxy(int x, int y);

/*A function to set the command window lenght and height for the GUI specification*/
void SetWindow();

/*A function to color the cmd text*/
void color(int thecolor);

//_____________________________________________________________

//Draw Functions

/*A function to draw the 11 floors*/
void DrawFloors();

/* A function that draws an elevator*/
void DrawElev(elev & E);

/*A function that draws a passanger */
void DrawPass(pass P, elev pE );

/*A Function to Draw passengers in Floors*/ 
void DrawPassengersInFloors(head* Floors[],elev pE);

/*A Function to Draw passengers in Elevator*/ 
void	DrawPassengersInElevator(elev E);

/*A function to draw a list of passnegers exist in all regions and ensure there is no overflow in the drawing*/
void DrawAll(elev E1,elev E2,head*Floors[],int Sys_Time,int Mode);

//_____________________________________________________________
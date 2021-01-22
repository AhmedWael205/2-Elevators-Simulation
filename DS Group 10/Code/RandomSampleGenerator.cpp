#include<iostream>
#include<time.h>
#include<fstream>
#define FILENAME "Sample.txt"
using namespace std;
int getrand(int min,int max);
int main()
{
	//Initializing random seed
	srand((unsigned int) time(NULL));

	int max,min,Rate,Time=0,Capc1,Capc2,Start1,Start2,GND,ROOF,num;

	ofstream file(FILENAME,ios::out);

	char ch='N';
	cout<<"Do you want to enter elevators capcities(Y/N) ?";
	cin>>ch;

	if(ch=='Y'||ch=='y')
	{
		cout<<"Elevator 1 Capcity: ";
		cin>>Capc1;
		cout<<"Elevator 2 Capcity: ";
		cin>>Capc2;
	}

	else
	{
		cout<<"Enter the Range of generated number :-"<<endl;
		cout<<"Minimum: ";
		cin>>min;
		cout<<"Maximum: ";
		cin>>max;

		Capc1=getrand(min,max);
		Capc2=getrand(min,max);
	}
	cout<<"Enter your floors range [0,10] OR [1,11] :-"<<endl;
	cout<<"Ground: ";
	cin>>GND;
	cout<<"Roof: ";
	cin>>ROOF;

	Start1=getrand(GND,ROOF);
	Start2=getrand(GND,ROOF);

	file<<Start1<<"\t"<<Capc1<<"\t"<<Start2<<"\t"<<Capc2<<endl;

	cout<<"Enter the number of passengers: ";
	cin>>num;
	cout<<"Enter the Min and Max interval between any two successive arrivals "<<endl;

	cout<<"Min : ";
	cin>>min;
	cout<<"Max : ";
	cin>>max;

	for(int i=0;i<num;i++)
	{
		int Source_Floor,Dest_Floor;

		Time+=getrand(min,max);

		Source_Floor=getrand(GND,ROOF);
		Dest_Floor=getrand(GND,ROOF);

		while(Dest_Floor==Source_Floor)
			Dest_Floor=getrand(GND,ROOF);

		file<<i+1<<"\t"<<Time<<"\t"<<Source_Floor<<"\t"<<Dest_Floor<<endl;
	}
	file<<"-1";
	file.close();
	cout<<"Done the file is ready in ";
	system("cd");
	system("pause");
return 0;
}

int getrand(int min,int max)
{
	return min+rand()%((max-min)+1);
}
#include <iostream>
using namespace std;

#include "Lib.h"
int main ()
{
	int Mode,NUM;
	elev E1,E2;
	head *AllPass=NULL;

	cout<<"Enter Sample Number : ";
	cin>>NUM;
	while(NUM>20||NUM<1)
	{
		cout<<"Sample Doesn't Exist\nEnter Sample Number : ";
		cin>>NUM;
	}
	ChooseSample(NUM);

	cout<<"Enter Mode ( Interactive= 1, Step By Step= 2, Silent = Z-{1,2} ) :  ";cin>>Mode;
	ElevSim(E1,E2,AllPass,Mode);
	return 0;
}
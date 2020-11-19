/*******************************************
      9A417018
*******************************************/

#include "MAIN.H" 
//extern int count[];

void UP_COUNTER(int *count,int min,int max)
{
	if(*count>=max|*count<min)
	{
		*count=min;
	}
	else
	{
		*count+=1;
	}
}

void DOWN_COUNTER(int *count,int max,int min)
{
	if(*count>max|*count<=min)
	{
		*count=max;
	}
	else
	{
		*count-=1;
	}
}




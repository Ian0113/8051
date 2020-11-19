/*******************************************
      9A417018
*******************************************/

#include "MAIN.H" 
//extern int count[];

void UP_CARRY( int *count_array , uint count_len )
{
	uint i;
	uint count_index = count_len-1;
	if(count_index>=0)
	{
		if( count_array[count_index] == 10 )
		{
			count_array[count_index]=0;
			if(count_index > 0)
			{
				count_array[count_index-1]+=1;
				UP_CARRY( count_array , count_index );
			}
			else
			{
				//start
				for(i=0;i<count_len;i++)
				{
					count_array[i]=0;
				}
			}
		}
	}
}
void CALL_UP( int *count_array , uint count_len )
{
	count_array[count_len-1] += 1;
	UP_CARRY( count_array , count_len );
}



void DOWN_CARRY( int *count_array , uint count_len )
{
	uint i;
	uint count_index = count_len-1;
	if(count_index>=0)
	{
		if( count_array[count_index] == -1 )
		{
			count_array[count_index]=9;
			if(count_index > 0)
			{
				count_array[count_index-1]-=1;
				DOWN_CARRY( count_array , count_index );
			}
			else
			{
				//start
				for(i=0;i<count_len;i++)
				{
					count_array[i]=9;
				}
			}
		}
	}
}
void CALL_DOWN( int *count_array , uint count_len )
{
	count_array[count_len-1] -= 1;
	DOWN_CARRY( count_array , count_len );
}




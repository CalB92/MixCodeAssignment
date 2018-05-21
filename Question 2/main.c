#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Author: Caleb Birch
//Problem: Write a program that outputs all possibilities to put + or - or nothing between the numbers 1, 2, ..., 9 (in this order) such that the result is always 100.

//The 9 numbers have 8 gaps between them. The gaps are filled with every possible permutation of either a minus sign, a plus sign or a "concatenate sign". 
//8 Digit ternary (base 3) numbers (00000000,00000001,00000002,00000010 etc..) are used to represent the arrangement of the gaps. 0 will represent +, 1 will be -, and 2 will be concatenate 
//The totals that equal 100 are printed out

void processNumbers(int *counter, int operations[8]);

int main(int argc, char *argv[]) {

	int operations[8] = {0, 0, 0, 0, 0, 0, 0, 0}; 	   //0 will represent +, 1 will be -, and 2 will be concatenate
	int resultCount = 0;                                //Variable used to counter the number of possible solutions
	int j;

	printf("The following possibilities result in 100:\n");

    //Process the combination of numbers and operators, and check if answer equals 100
	for(j = 0; j <= pow(3,8)-1; j++)
	{
		processNumbers(&resultCount, operations);

		//Increment the sequence of operators
		operations[7]++;
		  if (operations[7]==3){
		    operations[7]=0;
		    operations[6]++;
		    if (operations[6]==3){
		      operations[6]=0;
		      operations[5]++;
		      if (operations[5]==3){
		        operations[5]=0;
		        operations[4]++;
		        if (operations[4]==3){
		          operations[4]=0;
		          operations[3]++;
		          if (operations[3]==3){
		            operations[3]=0;
		            operations[2]++;
		            if (operations[2]==3){
		              operations[2]=0;
		              operations[1]++;
		              if (operations[1]==3){
		                operations[1]=0;
		                operations[0]++;
		                if (operations[0]==3){
		                  operations[0]=0;
		                }
		              }
		            }
		          }
		        }
		      }
		    }
		  }
	}

	printf("\nThere were %d possible combinations\n", resultCount);

	return 0;
}

void processNumbers(int *counter, int operations[8])
{
    int values[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };     //The sequence of numbers which are used in the sums
    int targetSum = 100;
	char addSubs[10][5];                               //An array of strings to store the +, - or ' 'symbols between the numbers of the sum
	char numberStrings[10][4];                         //An Array of strings to store the sequence of numbers to be used in the sum
    long int total;
    int i;

    for(i = 0; i < 10; i++)
		{
			strcpy(addSubs[i], "a");
		}

		for(i = 0; i < 9; i++)
		{
			values[i] = i+1;
		}

		for(i = 0; i < 8; i++)
		{
			if(operations[i] == 2)
			{
				if(operations[i-1] == 2)
				{
					if(operations[i-2] == 2)
					{
						sprintf(numberStrings[i+1], "%d", values[i+1]);
						strcat(numberStrings[i-2], numberStrings[i+1]);
					}

					sprintf(numberStrings[i+1], "%d", values[i+1]);
					strcat(numberStrings[i-1], numberStrings[i+1]);
				}
				sprintf(numberStrings[i], "%d", values[i]);
				sprintf(numberStrings[i+1], "%d", values[i+1]);

				strcat(numberStrings[i], numberStrings[i+1]);
				values[i] = atoi(numberStrings[i]);

				strcpy(addSubs[i], " ");
			}

			if(operations[i] == 1)
			{
				strcpy(addSubs[i], "-");
				sprintf(numberStrings[i], "%d", values[i]);
			}

			if(operations[i] == 0)
			{
				strcpy(addSubs[i], "+");
				sprintf(numberStrings[i], "%d", values[i]);
			}

			if(i == 7)
			{
				if(operations[i] != 2)
				{
					sprintf(numberStrings[i+1], "%d", values[i+1]);
				}
			}
		}

		total = atoi(numberStrings[0]);

	 	i=0;
	  	while (strcmp(addSubs[i], "a") != 0){
		    if(strcmp(addSubs[i], "+") == 0){
		      total = total + atoi(numberStrings[i + 1]);
		    }
		    else if(strcmp(addSubs[i], "-") == 0){
		      total = total - atoi(numberStrings[i + 1]);
		    }
		    i++;
	  	}

		//Display the result to the command line
		if (total == targetSum)
		{
		    for(i=0;i<9;i++)
			{
				if(i == 8)
				{
					if(strcmp(addSubs[i-1], " ") != 0)
					{
						printf("%s ", numberStrings[i]);
					}

				}
				else
				{
					if(strcmp(addSubs[i-1], " ") != 0)
					{
						if(strcmp(addSubs[i], " ") == 0)
						{
							printf("%s ", numberStrings[i]);
						}
						else
						{
							printf("%s %s ", numberStrings[i], addSubs[i]);
						}
					}
					else
					{
						if(strcmp(addSubs[i], " ") != 0)
						{
							printf("%s ", addSubs[i]);
						}
					}
				}
		    }
		    printf("= 100\n");
		    *counter = *counter + 1;
		}
}


#include <stdio.h>
#include <stdlib.h>

//Author: Caleb Birch
//Problem: In GPS devices, GPS data is commonly sent via NMEA strings. Write a simple NMEA parser to decode the VTG and RMC strings, extract Heading (as a double), speed (as an integer), and latitude (as a double) and display them. 
//The parser should follow the Unix convention of reading from standard input and writing to standard output.

//This program uses the keyboard as STDIN. The Console will prompt the user to enter an RMC or VTG NMEA string.
//The Heading, speed, and latitude(only RMC) will be displayed.
int main(int argc, char *argv[]) {
	
	char line[512];  							//Array to store the line entered for the packet
	char *eof = NULL;
	char *packet1;								//Holder to be used with strtok function
	char *token[20];                    		//Stores each token obtained with strtok()
	char delimiter = ',';						//The delimiter separating the tokens in the input line
	double Heading;
	int speed;
	double latitude;
	int i;
	int j;
	
	//Program continues to loop until invalid data entered
	while(strcmp("end\n" , line) != 0)
	{
		//Gets the input line from stdin and checks if its valid
		while(eof == NULL)
		{
			j = 1;
			printf("\nPlease enter NMEA string:\n");
			eof = fgets(line, sizeof(line), stdin);			
		}
		
		fflush(stdin);
		eof = NULL;
		
		//Divide the input string up into tokens
		for (j = 1, packet1 = line; ; j++, packet1 = NULL) 
		{
	        token[j] = strtok(packet1, &delimiter);
	        if (token[j] == NULL)
	            break;
		}
		
		if(j < 2)
		{
			fprintf(stderr, "Invalid NMEA data entered\n");
			return 0;
		}
		
		//Extract data from NMEA string and store them in variables
		if(strcmp(token[1], "GPRMC") == 0)
		{
			printf("RMC NMEA Sentence:\n");
			sscanf(token[4], "%lf", &latitude);
			printf("Latitude: %.3lf\n", latitude);
			
			speed = atoi(token[8]);
			printf("Speed in knots: %d\n", speed);
			speed = speed*1.852;
			printf("Speed in Km/h: %d\n", speed);
			
			sscanf(token[9], "%lf", &Heading);
			printf("Heading: %.2lf\n", Heading);	
		}
		else if(strcmp(token[1], "GPVTG") == 0)
		{
			printf("VTG NMEA Sentence:\n");

			sscanf(token[2], "%lf", &Heading);
			printf("Heading: %.2lf\n", Heading);
			speed = atoi(token[6]);
			printf("Speed in knots: %d\n", speed);
			speed = atoi(token[8]);
			printf("Speed in Km/h: %d\n", speed);
		}
		else 
		{
			fprintf(stderr, "Invalid NMEA data entered\n");
		}
	}
	
	return 0;
}

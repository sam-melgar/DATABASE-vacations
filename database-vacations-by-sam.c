/*DATABASE: vacations */ 
//Samantha Melgar

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

struct vacation {
	 char city[30];
	 char country[30];
	 float flight_cost;
	 int flight_hours; //from JFK airport to place
	 int days_staying;
	 }; //I will be referring to this as vacation_t 
	 
typedef struct vacation vacation_t; 

/* declaration of functions */
/*Colors */ 
void red();
void green();
void blue();
void purple();
void cyan();
void reset();
/*actual functions */ 	 
void intro(void); 
void display(struct vacation vacation_array[], int array_length, int sort_array[]);
void mainscreen_instructions(void);
int menu_input(void);
void search(struct vacation vacation_array[], int array_length);
void sort(int sort_array[], int array_length, struct vacation vacation_array[]);
int add(struct vacation vacation_array[], int array_length);
int delete(struct vacation vacation_array[], int array_length, int sort_array[]);
void save(struct vacation vacation_array[], int array_length, int sort_array[], char filename[]);

/*main program*/
int main(void){
	char filename[30]; //30 characters for a file name for "what file?"
	FILE *ifile;
	int i,userchoice; 
	int array_length=0;   
	char again; 
	int sort_array[50];   //matches with vacation_array[50]
	
	for(i=0; i<50; i++) { //populate for the sort array
		sort_array[i]= i;
	}	
	
	/* array of structures*/  
	vacation_t vacation_array[50]; //theres 30 entries originally (array lenghth) + 20 entries bonus 
	
	/*scan File into Array of structures*/ 
	printf("Please enter the name of the file: \n");
	scanf("%s",filename); //array of strings does not need an &
	ifile = fopen(filename, "r"); 
	
	if (ifile == NULL){
		printf("Sorry this file does not exits.");
	}else {
		i=0;
		while(fscanf(ifile,"%[^,],%[^,],%f,%d,%d\n",vacation_array[i].city, vacation_array[i].country, &vacation_array[i].flight_cost, &vacation_array[i].flight_hours, &vacation_array[i].days_staying) != EOF){
		//found this %[^,] from https://www.codegrepper.com/code-examples/c/fscanf+reading+a+comma+separated+value
			i++;
			array_length++;
		}
	}

	printf("There are %d rows.", array_length); //30
	printf("\n\n"); //organization
	
	intro(); //what my data is about function
	
	display(vacation_array, array_length, sort_array); //show what the data looks like first 
	
	
	
	do {
		mainscreen_instructions();//prints what options to select 
		userchoice = menu_input();  //store the user input 
		switch(userchoice) //pass the user input and leads to the functions that execute the user's command
        { 
        		case 1:
        			search(vacation_array, array_length);
        			break;
        	
        		case 2:
        			sort(sort_array, array_length, vacation_array);
        			break;
        		
        		case 3:  
        			display(vacation_array, array_length, sort_array);
        			break;
        		
        		case 4:
        			array_length = add(vacation_array, array_length); //add function will return the updated array length
        			display(vacation_array, array_length, sort_array);
        			break;
        		
        		case 5:
        			array_length = delete(vacation_array, array_length, sort_array);
        			display(vacation_array, array_length, sort_array);
        			break;
        	
        		case 6:
        			save(vacation_array, array_length, sort_array, filename);
        			break;
        		
        		default:
        			red();
        			printf("\n Your choice is incorrect\n Please try again...\n");
        			reset();
        }
    	printf("Press 'n' to quit, 'y' to continue:\n");
		scanf("%c", &again); 
	} while (again != 'n'); //class notes: ask a user to continue  



	return(0);
}
	 
void intro(void) {
	purple();
	printf("----------------------------------------------------------------------------------------------------\n");
	printf("| My data is a set of cities from different countries that I want to go to.                        |\n");
	printf("| This data set has 1) name of city 2) name of country 3) cost of flight                           |\n");
	printf("| 4)hours of travel from JFK airport to country 5)how many days I plan to stay                     |\n");
	printf("| I chose this because I am burned out from Dartmouth and a vacation is well needed                |\n");
	printf("| I might not be able to travel right now, but definitely keeping this list for future reference   |\n");
	printf("|--------------------------------------(=^x^=)-----------------------------------------------------|\n");
	reset();
}	 //what my data is about and why I chose it 

void display(struct vacation vacation_array[], int array_length, int sort_array[]){
	int i;
	red();
	printf("CITY, COUNTRY, FLIGHT COST, HOURS ON PLANE, DAYS\n"); 
	reset();
	
	for(i=0; i<array_length; i++){
		printf(" %s, %s, $%.2f, %d, %d \n", vacation_array[sort_array[i]].city, vacation_array[sort_array[i]].country, vacation_array[sort_array[i]].flight_cost, vacation_array[sort_array[i]].flight_hours, vacation_array[sort_array[i]].days_staying);
	}	
}
void mainscreen_instructions(void){ 
	  red();
	  printf("\n\n -----------------------Select your choice-----------------------\n");
	  reset();
      printf("\n 1. SEARCH \n 2. SORT \n 3. DISPLAY \n 4. ADD \n 5. DELETE \n 6. SAVE \n");
      red();
      printf(" ------------------------------------------------------------------\n");
      reset();

} //just print statements that show options 
int menu_input(void) {
	int userchoice;
	    
	printf("\nEnter your choice:\n");
	scanf("%d", &userchoice); //saves what the user inputted to then match it with the following cases
    return(userchoice);
}

void search(struct vacation vacation_array[], int array_length) {
	int userchoice, days,i;
	char country[10]; //name of country string 
	red();
	printf("\n\nWelcome to Search \n");
	printf("\n\n -----------------------Select your choice-----------------------\n");
	reset();
	printf("1. Search by COUNTRY \n2. Search by amount of DAYS STAYING:\n");
	red();
	printf(" ------------------------------------------------------------------\n");
	reset();
	printf("Enter an option:\n");
	scanf("%d", &userchoice);
	
	
	switch (userchoice)
	{ 	case 1: //search by city
			printf("Enter country name:\n");
			scanf("%s", country);
			red();
			printf("CITY, COUNTRY, FLIGHT COST, HOURS ON PLANE, DAYS\n");
			reset();
			for (i=0; i<array_length;i++){
				if(strcmp(vacation_array[i].country, country)==0)
				{
					printf(" %s, %s, $%.2f, %d, %d \n",vacation_array[i].city, vacation_array[i].country, vacation_array[i].flight_cost, vacation_array[i].flight_hours, vacation_array[i].days_staying);	
				}
		}
			printf("\n");
			break;
		case 2:
			printf("Enter number of days:\n");
			scanf("%d",&days);
			
			printf("\n\n");
			red();
			printf("CITY, COUNTRY, FLIGHT COST, HOURS ON PLANE, DAYS\n");
			reset();
			for (i=0; i < array_length; i++) {
				if (vacation_array[i].days_staying == days)
				{ 
					printf(" %s, %s, $%.2f, %d, %d \n",vacation_array[i].city, vacation_array[i].country, vacation_array[i].flight_cost, vacation_array[i].flight_hours, vacation_array[i].days_staying);
				}
			}
			break;
	}
} 
	
void sort(int sort_array[], int array_length, struct vacation vacation_array[]){
	int userchoice,i,j, num;
	

	blue();
	printf("\n\nWelcome to SORT! \n");
	printf("\n\n -----------------------Select your choice-----------------------\n");
	reset();
	printf("1. Sort A-Z by COUNTRY \n2. Sort by CHEAPEST flight cost\n");
	blue();
	printf(" ------------------------------------------------------------------\n");
	reset();
	printf("\nEnter an option:\n");
	scanf("%d", &userchoice);

	switch (userchoice)
	{ 	case 1:
			printf("You chose alphabetical sort of countries\n");
			for (i=0; i<(array_length-1); i++) {
        		for (j= i+1; j < array_length; j++) { //the subsequent element of i 
            		if (strcmp(vacation_array[sort_array[i]].country,vacation_array[sort_array[j]].country) > 0) { 
            		// if Return value > 0 then it indicates sort_array[j].countries is less than sort_array[i].countries
            			num = sort_array[i];
            			sort_array[i] = sort_array[j];
            			sort_array[j]= num;	

            		}
            	
			}//j loop
		}//iloop
		
			printf("\n \n");
   		    printf("Countries after sorting in alphabetical order \n");
   		    blue();
    		printf("\n\nCITY, COUNTRY, FLIGHT COST, HOURS ON PLANE, DAYS\n");
    		reset();
    		for(i=0; i< array_length; i++) {
        		printf(" %s, %s, $%.2f, %d, %d \n",vacation_array[sort_array[i]].city, vacation_array[sort_array[i]].country, vacation_array[sort_array[i]].flight_cost, vacation_array[sort_array[i]].flight_hours, vacation_array[sort_array[i]].days_staying);
    		}
    		break;
    	case 2:
    		printf("You chose lowest to highest sort of flight cost\n");
			for (i=0; i<(array_length-1); i++) {
        		for (j= i+1; j < array_length; j++) { //the subsequent element of i 
            		if (vacation_array[sort_array[i]].flight_cost > vacation_array[sort_array[j]].flight_cost)  { 
            		// if Return value > 0 then it indicates sort_array[j].countries is less than sort_array[i].countries
            			num = sort_array[i];
            			sort_array[i] = sort_array[j];
            			sort_array[j]= num;	

            		}
            	
			}//j loop
		}//iloop
			printf("\n \n");
   		    printf("vacations in low to high flight cost order:  \n");
   		    blue();
    		printf("\n\nCITY, COUNTRY, FLIGHT COST, HOURS ON PLANE, DAYS\n");
    		reset();
    		for(i=0; i< array_length; i++) {
        		printf(" %s, %s, $%.2f, %d, %d \n",vacation_array[sort_array[i]].city, vacation_array[sort_array[i]].country, vacation_array[sort_array[i]].flight_cost, vacation_array[sort_array[i]].flight_hours, vacation_array[sort_array[i]].days_staying);
    		}
    		break;
    		
    	
    		
	}//switch

}//function

int add(struct vacation vacation_array[], int array_length){
	//Add a record to the data.
	int rows,i;
	green();
	
	printf("Welcome to ADD!\n\n");
	printf("How many rows would you like to add?\n\n"); //asks user how many rows plans to add
	scanf("%d", &rows);
	reset();
	
	for(i=0; i<rows; i++){ //user input information to be added 
		green();
		printf("Row %d: \n", (i+1));
		reset();
		printf("Enter CITY Name:\n");
		scanf("%s",vacation_array[array_length].city);
		printf("Enter COUNTRY Name:\n");
		scanf("%s", vacation_array[array_length].country);
		printf("Enter FLIGHT COST:\n");
		scanf("%f", &vacation_array[array_length].flight_cost);
		printf("Enter FLIGHT HOURS:\n");
		scanf("%d",&vacation_array[array_length].flight_hours);
		printf("Enter DAYS STAYING:\n");
		scanf("%d", &vacation_array[array_length].days_staying);
		array_length++;
		printf("\n");
		
	}
	return(array_length);//communicate with main function that the array length has increase by the user's desired amount of rows
} //function bracket 

int delete(struct vacation vacation_array[], int array_length, int sort_array[]){
//Delete a record from the data 
	int i,j;
	char city[15]; //space for city name
	cyan();
	printf("Welcome to DELETE!\n\n");
	
	printf("Enter city you would like to delete:\n");
	scanf("%s", city);
	reset();
	printf("%s\n", city);

	for (i=0; i<array_length; i++){
		if( strcmp(city, vacation_array[sort_array[i]].city)==0){ //sort_array[i] just returns a number sort_array[0] = 0 SO vacation_array[sort_array[0]].city= vacation_array[0].city = first row CITY component
		
			for(j=i; j<array_length; j++){ //make j the isolated i row we want to delete and update sort[j] to represent the NEXT row and push the unwanted row toward the end and just reduce the display of numbers so it cuts off the unwanted row
				sort_array[j] = sort_array[j+1];	
			}//j bracket	
		
			i = array_length;  
		
		}
		
	}//for bracket
	array_length--; //reducing the array length so the unwanted row will not be displayed
	
	return(array_length); //communicate back to the main function that we have decreased the amount of rows

} //function bracket

void save(struct vacation vacation_array[], int array_length, int sort_array[], char filename[]){
//The user should be prompted for a filename, and your program should first 
//check whether that file already exists. If so, the user should be warned that they are
// about to overwrite an existing file and given the option to reconsider
    FILE *ifile;
    char user_input[15]; //user gets 15 characters to type a filename
    int i;
    int overwrite;
    
    do{
    	purple();
    	printf(":-) Welcome to SAVE!\n\nPlease enter a file name:\n");
    	reset();
    	scanf("%s", user_input);
    
    	if (strcmp(user_input, filename)==0){
    		printf("You are about to overwrite a file is that ok?\n 1. YES\n 2. NO");
    		scanf("%d", &overwrite);
    	}
    	else{
    	printf("Your save file name is %s. Press 1 to continue. ", user_input);
    	scanf("%d", &overwrite);
    	}
    
    }while(overwrite != 1);
    
    ifile= fopen(user_input, "w"); //will create the file in the thayer server 
    for(i=0; i<array_length; i++) {
        fprintf(ifile, "%s,%s,%.2f,%d,%d\n", vacation_array[sort_array[i]].city, vacation_array[sort_array[i]].country, vacation_array[sort_array[i]].flight_cost, vacation_array[sort_array[i]].flight_hours, vacation_array[sort_array[i]].days_staying); //space to separate each number
    }

    fclose(ifile);
    purple();
	printf("FILE SAVED.");
	reset();

}





/*colors*/
void red() {
    printf("\033[1;31m");
}
void green() {
    printf("\033[1;32m");
}
void blue() {
    printf("\033[1;34m");
}
void purple() {
    printf("\033[1;35m");
}
void cyan() {
    printf("\033[1;36m");
}
void reset(){
    printf("\033[0m");
}

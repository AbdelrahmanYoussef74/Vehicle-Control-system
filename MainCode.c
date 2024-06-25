/* Name: Abdelrahman Youssef
  Gmail: booodyusf@gmail.com*/

#include<stdio.h>
#define WITH_ENGINE_TEMP_CONTROLLER 0

int User_Int_Input;
int *const UII_ptr = &User_Int_Input; /* this two lines will keep me away from create a new
variable (int) each time the user insert an input such as temperatures or speed. */

char User_Char_Input ;
char *const UCI_ptr = &User_Char_Input;  /* also this two lines will keep me away from create a new
variable (char) each time the user insert an input such as set the traffic lights or choosing the next function. */

/* the previous four lines will change the original value then check the new value to continue,
  by using a constant pointer to non constant data.*/


void (*functionPtr)();  // make a void pointer to using it in calling function instead of using a pointer to each function

struct settings{
    char *engine;
    char *ac;
    int vehicle_speed;
    int room_temp  ;
    char *engine_temp_control;
    int engine_temp ;
}settin={"OFF","OFF",100,35,"OFF",90},*struc_ptr = &settin; // elements initialization is depend on the video.

/* a global structure to use it in print & a global pointer to structure to be able to use
              it in any function to modify the elements inside the main structure easily */

  void Func_Selector (char * );                  //     All Functions Prototypes
  void When_Engine_On();
  void Print_Engine_On_Menu();
  void Set_Traffic_Lights();
  void Set_Engine_Temp();
  void Set_Room_Temp();
  void When_Engine_Off();
  void Check_Speed_30_B4_Print();
  void Print_Results();
  void Quit_System();


int main(){ // main function to send the first character (input from user) to the function that take the responsibility to select the next function.
	setvbuf(stdout, NULL, _IONBF, 0);

    printf("a. Turn on the vehicle engine\nb. Turn off the vehicle engine\nc. Quit the system\n");
    scanf(" %c",UCI_ptr);
    Func_Selector(UCI_ptr);

    return 0;
}


void Func_Selector(char *UCI_ptr){ /* this function is used for take the user choice
                                                   then send to the next function to be executed*/

	 switch(*UCI_ptr){
	        case 'a' :
	        	functionPtr = When_Engine_On; // call the function by a void pointer
	        	break;
	        case 'b' :
	        	functionPtr = When_Engine_Off;
	           break ;
	        case 'c':
	        	functionPtr = Quit_System ;
	          break ;



	    }
	 functionPtr(); // this line is to complete a syntax to call the function by a void pointer

}

void When_Engine_On(){ // this function is to run when the user choose to turn on the engine and also to let the user choose to set again


	struc_ptr-> engine = "ON"; // use the global pointer to modify the (engine) element

		            Print_Engine_On_Menu();
		        	scanf(" %c", UCI_ptr);

		        	switch(*UCI_ptr){          // this switch case is used for to let the user set whatever he want to
		        	case 'a' : functionPtr = When_Engine_Off ;  break;
		        	case 'b' : functionPtr =  Set_Traffic_Lights;  break;
		        	case 'c' : functionPtr =  Set_Room_Temp;  break ;
                   #if( WITH_ENGINE_TEMP_CONTROLLER == 1) // For Bonus Requirement
		        	case 'd' : functionPtr =  Set_Engine_Temp;
		        	break ;
		        	#endif

		        	}

		        	functionPtr();
}

void Print_Engine_On_Menu(){
	printf("a. Turn off the engine \n");
	printf("b. Set the traffic light color.\n");
	printf("c. Set the room temperature \n");
#if  (WITH_ENGINE_TEMP_CONTROLLER == 1)
	printf("d. Set the engine temperature \n");
#endif
}



void Set_Traffic_Lights(){ /* Function to let the user set the traffic lights then print the modified elements */


	printf("Please Enter Traffic Light: ");
	scanf(" %c", UCI_ptr);

	switch(*UCI_ptr){ // this switch case is used to first set the vehicle speed then go to print
	case 'g' :
	case 'G' :
	struc_ptr-> vehicle_speed = 100;
	functionPtr = Check_Speed_30_B4_Print;
	          break;
	case 'o' :
	case 'O' :
	struc_ptr-> vehicle_speed = 30;
	functionPtr = Check_Speed_30_B4_Print;
	          break;
	case 'r':
	case 'R':
	struc_ptr-> vehicle_speed = 0;
	functionPtr = Check_Speed_30_B4_Print;
	          break;

	}

	functionPtr();

}

void Set_Engine_Temp(){ //function to let the user to set the room temperature then print the desired values


			printf("Please Enter The Engine Temperature: ");
			scanf(" %d",UII_ptr);

			if( *UII_ptr <= 100) {
			struc_ptr-> engine_temp_control = "ON";
			struc_ptr-> engine_temp = 125;
			functionPtr = Check_Speed_30_B4_Print;}

			else if (*UII_ptr >= 150) {

			struc_ptr-> engine_temp_control = "ON" ;
			struc_ptr-> engine_temp = 125;
			functionPtr = Check_Speed_30_B4_Print;}

			else {
			struc_ptr-> engine_temp_control = "OFF";
			functionPtr = Check_Speed_30_B4_Print; }

			functionPtr();
}

void Set_Room_Temp(){ //function to let the user to set the room temperature then print the desired values

		printf("Please Enter The Room Temperature: ");
		scanf(" %d", UII_ptr);
//if condition to determine the limit of the input number of room temperature

		 if (*UII_ptr<=10) {
		 struc_ptr-> ac = "ON";
		 struc_ptr-> room_temp = 20;
		 functionPtr = Check_Speed_30_B4_Print; }

		 else if (*UII_ptr>=10) {
		 struc_ptr-> ac = "ON";
		 struc_ptr-> room_temp = 20;
		 functionPtr = Check_Speed_30_B4_Print; }

		 else {   struc_ptr-> ac = "OFF";
		 functionPtr = Check_Speed_30_B4_Print;
		 }

		 functionPtr();
}




void When_Engine_Off(){ /* this function is to let the user to turn the engine on or off or quit the system */


	 printf("\n a. Turn on the vehicle engine\n b. Turn off the vehicle engine\n c. Quit the system\n");
	 scanf(" %c",UCI_ptr);
	 Func_Selector(UCI_ptr); // send the input from user to the function that determine the rest functions
}




void Check_Speed_30_B4_Print(){                // this is the print function that all other function call it when need to print te desired valuse to the user
	if (struc_ptr -> vehicle_speed == 30 ){
		struc_ptr-> room_temp = struc_ptr-> room_temp *(5/4) + 1;
		struc_ptr-> engine_temp_control = "ON";
		struc_ptr-> ac = "ON";
		struc_ptr-> engine_temp = struc_ptr-> engine_temp *(5/4) + 1;
	}


	Print_Results();
}



void Print_Results(){
	            printf("\n") ;
	            printf("Engine is %s \n",   struc_ptr -> engine);
			    printf("AC is %s \n",   struc_ptr -> ac);
			    printf("Vehicle Speed is %d Km per hr \n",  struc_ptr -> vehicle_speed);
			    printf("The Room Temperature is %d \n",  struc_ptr -> room_temp);
#if(WITH_ENGINE_TEMP_CONTROLLER == 1)
			    printf("Engine Temperature Control is %s \n",   struc_ptr -> engine_temp_control);
			    printf("The Engine Temperature is %d Celsius \n",  struc_ptr -> engine_temp);
#endif
			    printf(" \n");

			    functionPtr = When_Engine_On;
			    functionPtr();
}

void Quit_System(){ // this is a simple function that when the user want to quit the whole system
	printf(" Quit System ");
	return ;
}




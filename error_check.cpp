#include "error_check.h"
#include <string>

//takes in a string that user has used as their choice to a question,
//checks if string is only numbers, and then checks if those characters as integer
//match a valid choice, given the low and high parameters
int check_choice_in_range(string choice_string, int low, int high) {

	int choice;

	int len = choice_string.length();
	if (len == 0) return 0;
		
	for (int i = 0; i < len; i++) {

		//check if current char is not an integer, if so exit function and return a 0
		if (choice_string[i] < '0' || choice_string[i] > '9') {
			choice = 0;
			return choice;
		}
	}
	choice = stoi(choice_string);	//choice has to be an integer, this converts string to int

	if (choice < low || choice > high) 
        return 0;	
	return choice;

}

/*
Take user input without the user of 'Enter' being pressed
 */
char getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    //printf("%c\n", buf);	//option to print out char
    return buf;
 }


 /* pauses, waits for user to press enter */
 void user_pause()
 {
    std::cout << "Press 'enter' to continue: ";
    std::cin.ignore(256, '\n');
 }
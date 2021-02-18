#ifndef ERROR_CHECK_H
#define ERROR_CHECK_H

#include <iostream>
#include <string>
#include <unistd.h>
#include <termios.h>

using namespace std;

int check_choice_in_range(string, int, int);	//checks if user's card choice is valid or not


//gets char from user input without use of 'enter' key
//TAKEN DIRECTLY FROM: 
//https://stackoverflow.com/questions/7469139/what-is-the-equivalent-to-getch-getche-in-linux/7469410#7469410
//
char getch(void);


#endif
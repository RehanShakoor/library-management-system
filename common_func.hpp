//this file contains function declarations, which is common to
//student login and new account creation

#ifndef COMMON_FUNC_HPP
#define COMMON_FUNC_HPP

//include all required libraries
#include <iostream>
#include <string>
#include <fstream>
#include <format>
#include <termios.h>
#include <unistd.h>
#include <cstdlib> 

//define general macros
#define SUCCESS    0
#define FAILURE    1
#define LIST_EMPTY 2
#define DUPLICATE  3

using namespace std;

//class to store username and password, password is kept private to class.
//friend functions are use to set and get class members.
//class member functions are not to set and get class members.

//friend functions will be more secure, if someone have pointer to a class 
//then using class member functions, they can easily change private member,
//but with friend function we need that function and class pointer to change it
//which is more secure, as two things are required.

//friend functions can be declared in public, private or protected section.

class uname_pwd_class
{
	public : 
		string uname;
		uname_pwd_class *next;

	private:
		//friend function declaration to store pwd to uname_pwd_class
        //for this project uname is kept fixed
		friend void store_pwd(uname_pwd_class *usr_ptr, string pwd);

		//friend function declaration to get pwd from class uname_pwd_class
		//uname is public, no need for its separate get_function
		friend string get_pwd(uname_pwd_class *usr_ptr);

		string pwd;
};


//class to store all books present in the library.
//this class also stored list of borrowers for a book
class book_class
{
	public :
		string title;
		string author;
		int count;
		uname_pwd_class *borrowers_list = NULL;
		book_class *next;
};


//Declare global variables

//string to store uname pwd file name
extern string uname_pwd_filename;

//linked list to store all username and password
extern uname_pwd_class *uname_pwd_list;

//below pointer will always point to the last node of list
//by using this pointer, we dont have to iterate over the whole
//list each time, when we want to get the last node
extern uname_pwd_class *uname_pwd_last_node;


//string to store filename which contains books details
extern string books_details_filename;

//linked list to store all books details
extern book_class *books_list;

//below pointer will always point to the last node of list,
//by using this pointer, we dont have to iterate over the whole
//list each time, when we want to get the last node
extern book_class *book_last_node;


//string to store filename which contains borrowers details
extern string borrowers_details_filename;


//function declaration to hide password while user enter it
string getPassword(string msg);

//function declaration to wait till, user press "SPACE"
void key_wait(void);


//function declaration to store pwd to uname_pwd_class
//for this project uname is kept fixed
void store_pwd(uname_pwd_class *usr_ptr, string pwd);

//function declaration to get pwd from class uname_pwd_class
//uname is public, no need for its separate get_function
string get_pwd(uname_pwd_class *usr_ptr);

#endif
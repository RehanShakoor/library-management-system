//include user-defined header files
#include "common_func.hpp"
#include "login_func.hpp"
#include "library_func.hpp"

//Initialise global variables
//string to store uname pwd file name
string uname_pwd_filename = "uname_pwd.txt";

//linked list to store all username and password
uname_pwd_class *uname_pwd_list = NULL;

//below pointer will always point to the last node of list
//by using this pointer, we dont have to iterate over the whole
//list each time, when we want to get the last node
uname_pwd_class *uname_pwd_last_node = NULL;

//string to store filename which contains books details
string books_details_filename = "books_details.txt";

//linked list to store all books details
book_class *books_list = NULL;

//below pointer will always point to the last node of list,
//by using this pointer, we dont have to iterate over the whole
//list each time, when we want to get the last node
book_class *book_last_node = NULL;

//string to store filename which contains borrowers details
string borrowers_details_filename = "borrowers_details.txt";

int main()
{
	//read "uname_pwd.txt", "books_details.txt" and "borrowers_details.txt"
	//for once, in the begining, to initilize all list with already existing data
	read_uname_pwd_file();
	read_books_details_file();
	read_borrowers_details_file();

	char choice = 0;
	do
	{
		//clear screen before calling next function
		system("clear");
		//read choice from user
		cout << "Library management system" << endl << endl;
		cout << "1) Admin login" << endl;
		cout << "2) Student login" << endl;
		cout << "3) Create new student account" << endl;
		cout << "4) Exit" << endl << endl;
		cout << "Enter choice : ";
		cin  >> choice;

		//login for admin
		if(choice == '1')
		{
			//clear screen before calling next function
			system("clear");
			//call function to print menu for admin login
			admin_login_menu();
		}
		//login for already existing student
		else if(choice == '2')
		{
			//clear screen before calling next function
			system("clear");
			//call function to print menu for student login
			student_login_menu();
		}
		//create a new student account
		else if(choice == '3')
		{	
			//clear screen before calling next function
			system("clear");
            //call function to print new account creation menu
            create_new_account_menu();
		}
		//exit from current menu
		else if(choice == '4')
		{
			break;
		}
		else
		{
			cout << endl << "Error   : Please enter a valid choice" << endl;
			key_wait();
		}
	}
	while(1);

	return 0;
}
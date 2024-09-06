//this file contains function definitions, which are
//related to admin, student logging and new account creation

#include "common_func.hpp"
#include "library_func.hpp"

#include <format>

//admin logging functions definitions

//function definition to print admin login menu
void admin_login_menu(void)
{
    //read username and password for login
    string uname, pwd;
	cout << "Admin login menu" << endl << endl;
	cout << "Enter username : ";
	cin  >> uname;
    getchar(); // to clear input buffer
	pwd = getPassword("Enter password : ");

    //check uname and pwd matched or not
    if(uname == "admin" && pwd == "root" )
    {
        cout << format("\nSuccess : Logged into admin user \"{}\"",uname) << endl;
        key_wait();

        //function definition to print library menu for admin
        admin_library_view();
    }
    else
    {
        //print error and wait for DELAY_SEC seconds
        cout << endl <<  "Error   : Entered username or password is incorrect" << endl;
        key_wait();
    }
}



//student logging functions definitions

//function definition to read file "uname_pwd.txt", which contains all 
//usernames and their passwords and store read uname, pwd in a linked list 
//named as "uname_pwd_list".
char read_uname_pwd_file(void)
{
	//open file for reading
	ifstream read_file(uname_pwd_filename);

    //Check if the file was opened successfully
    if(!read_file) 
	{
        cout << format("Error   : Can't open file \"{}\"\n",uname_pwd_filename);
        return FAILURE;
    }

    //Read words one by one
	//temp is used to iterate over linked list
	uname_pwd_class *temp = NULL;
    while(1) 
	{
		//read uname and pwd from file
		string uname, pwd;
		read_file >> uname;
		read_file >> pwd;

		if(uname.length() > 0)
		{
			//if linked list is empty
			if(uname_pwd_list == NULL)
			{
				//store uname and pwd in head node
				uname_pwd_list = new uname_pwd_class;
				uname_pwd_list->uname = uname;
				store_pwd(uname_pwd_list, pwd);
				uname_pwd_list->next = NULL;
				temp = uname_pwd_list;
				continue;
			}

			//store uname and pwd in next node
			temp->next = new uname_pwd_class;
			temp->next->uname = uname;
			store_pwd(temp->next, pwd);
			temp->next->next = NULL;
			temp = temp->next;
		}
		else
		{
			break;
		}
    }

    //close the file
    read_file.close();
	uname_pwd_last_node = temp;
	return SUCCESS;
}

//function definition to check given uname and pwd is correct or not
uname_pwd_class* uname_pwd_match(string uname, string pwd)
{
    //iterate over uname_pwd_list
    uname_pwd_class *temp = uname_pwd_list;
    while(temp)
    {
        //if uname and pwd matches, then return pointer of that node
        if(uname == temp->uname && pwd == get_pwd(temp))
            return temp;
        temp = temp->next;
    }

    //if uname and pwd doesnt matches, then return NULL
    return NULL;
}

//function definition to print student login menu
void student_login_menu(void)
{
    //read username and password for login
    string uname, pwd;
	cout << "Student login menu" << endl << endl;
	cout << "Enter username : ";
	cin  >> uname;
    getchar(); // to clear input buffer
	pwd = getPassword("Enter password : ");

    //check uname and pwd matched or not
    uname_pwd_class *ptr = uname_pwd_match(uname, pwd);
    if(ptr == NULL)
    {
        //print error and wait for user key pressed
        cout << endl << "Error   : Entered username or password is incorrect" << endl;
        key_wait();
    }
    else
    {
        cout << format("\nSuccess : Logged into username \"{}\"",uname) << endl;
		key_wait();

        //function definition to print library menu of current student
        student_library_view(ptr);
    }
}


//function definiton to create new account
//add new account node to the last of the linked list
void create_new_account(string uname, string pwd)
{
	//if no account is created till now
	if(uname_pwd_list == NULL)
	{
		//store uname and pwd in head node
		uname_pwd_list = new uname_pwd_class;
		uname_pwd_list->uname = uname;
		store_pwd(uname_pwd_list, pwd);
		uname_pwd_list->next = NULL;
		uname_pwd_last_node = uname_pwd_list;
		return;
	}

	//use last node pointer to get the last node
	//store uname and pwd in next node
	uname_pwd_last_node->next = new uname_pwd_class;
	uname_pwd_last_node->next->uname = uname;
	store_pwd(uname_pwd_last_node->next, pwd);
	uname_pwd_last_node->next->next = NULL;
	uname_pwd_last_node = uname_pwd_last_node->next;
}

//Function definition to write "uname_pwd.txt" with the updated list
char write_uname_pwd_file(void)
{
	//open file for writing
	ofstream write_file(uname_pwd_filename);

	//Check if the file was opened successfully
	if(!write_file) 
	{
		cout << format("Error   : Can't open file \"{}\"\n",uname_pwd_filename);
		return FAILURE;
	}

	//iterate over uname_pwd_list
    uname_pwd_class *temp = uname_pwd_list;
    while(temp)
    {
        //write uname and pwd of each node to the file
		write_file << format("{}\t{}\n",temp->uname, get_pwd(temp)); 
        temp = temp->next;
    }

	//close the file
	write_file.close();
	return SUCCESS;
}

//Function definition to append new user details to "uname_pwd.txt"
char append_uname_pwd_file(string uname, string pwd)
{
	//open file for writing in append mode
	ofstream write_file(uname_pwd_filename, ios::app);

	//Check if the file was opened successfully
	if(!write_file) 
	{
		cout << format("Error   : Can't open file \"{}\"\n",uname_pwd_filename);
		return FAILURE;
	}

    //write uname and pwd to the last of the file
	write_file << format("{}\t{}\n",uname, pwd);

	//close the file
	write_file.close();
	return SUCCESS;
}

//Function definition to check, given "uname" is a unique one or not.
//This function will read "uname_pwd_list" linked list and check given
//"uname" is a unique one or not (returns SUCCESS on unique else FAILURE).
char is_unique_uname(string uname)
{
	//before this function call, "uname_pwd.txt" file is read
	//if list is empty, that means no user is created till now
	if(uname_pwd_list == NULL)
	{
		return LIST_EMPTY;
	}
	else
	{
		//iterate over list
		uname_pwd_class *temp = uname_pwd_list;
		while(temp)
		{
			//return FAILURE if uname matches
			if(uname == temp->uname)
				return FAILURE;
			temp = temp->next;
		}

		return SUCCESS;
	}
}

//function definition to print uname_pwd_list (used for testing purpose only)
void print_uname_pwd_list(void)
{
	uname_pwd_class *temp = uname_pwd_list;
	while(temp)
	{
		cout << format("{}\t{}\n",temp->uname, get_pwd(temp));
		temp = temp->next;
	}
}

//function definition to change user password
void change_user_pwd(uname_pwd_class *usr_ptr)
{
	//read new and old password from user
	string old_pwd, new_pwd, re_new_pwd;
	cout << format("Change password for student \"{}\"\n\n",usr_ptr->uname);

	//read all passwords
	getchar(); //clear input buffer
	old_pwd = getPassword("Enter old password    : ");
	new_pwd = getPassword("Enter new password    : ");
	re_new_pwd = getPassword("Re-enter new password : ");

	//check if old password entered is correct or not
	if(old_pwd == get_pwd(usr_ptr))
	{
		//check if re-entered password matched or not
		if(new_pwd == re_new_pwd)
		{
			//change user password
			store_pwd(usr_ptr, new_pwd);
			cout << format("\nSuccess : Password for student \"{}\" is changed",usr_ptr->uname) << endl;
			cout << "Info    : Login again with the new password" << endl;

			//before exit, update "uname_pwd.txt" file with updated list
			write_uname_pwd_file();
		}
		else
		{
			cout << endl << "Error   : Re-entered password doesn't matches" << endl;
		}
	}
	else
	{
		cout << endl << "Error   : Old password entered is incorrect" << endl;
	}
}



//new account creation functions definitions

//function definiton to print menu for new account creation
void create_new_account_menu(void)
{
	//read username and password to create new account
	string uname, pwd, repwd;
	cout << "Create new student account menu" << endl << endl;
	cout << "Enter username    : ";
	cin  >> uname;
    getchar(); // to clear input buffer
    pwd = getPassword("Enter Password    : ");
	repwd = getPassword("Re-enter password : ");

	//check if new username already exists or not
	char res = is_unique_uname(uname);
	if(res == SUCCESS || res == LIST_EMPTY)
	{
		//check if re-entered password matched or not
		if(pwd == repwd)
		{
			//create new account (update linked list)
			create_new_account(uname, pwd);
			//before exit, append new user to "uname_pwd.txt" file 
			append_uname_pwd_file(uname, pwd);

			cout << endl <<"Success : New account is created" << endl;
		}
		else
		{
            //print error and wait for DELAY_SEC seconds
			cout << endl << "Error   : Can't create new student account" << endl;
			cout << "Info    : Re-entered password doesn't matched" << endl;
		}
	}
	else
	{
		//format() is used to do format printing in C++ (gcc13, c++20)
        //print error and wait for DELAY_SEC seconds
		cout << endl << "Error   : Can't create new student account" << endl;
		cout << format("Info    : \"{}\" username already exists\n",uname);
		cout << "Info    : Use some other username" << endl;
	}
	key_wait();
}

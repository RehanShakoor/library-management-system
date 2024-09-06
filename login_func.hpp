//this file contains function declarations, which are
//related to admin, student logging and new account creation

#ifndef LOGIN_FUNC_HPP
#define LOGIN_FUNC_HPP

#include "common_func.hpp"

//admin logging functions declarations

//function declaration to print admin login menu
void admin_login_menu(void);



//student logging functions declarations

//function declaration to print student login menu
void student_login_menu(void);

//function declaration to ckeck given uname and pwd is correct or not
uname_pwd_class* uname_pwd_match(string uname, string pwd);

//function declaration to read file "uname_pwd.txt", which contains all 
//usernames and their passwords and store read uname, pwd in a linked list 
//named as "uname_pwd_list".
char read_uname_pwd_file(void);

//function declaration to print uname_pwd_list (used for testing purpose only)
void print_uname_pwd_list(void);

//function declaration to change user password
void change_user_pwd(uname_pwd_class *usr_ptr);



//new account creation functions declarations

//function declaration to check, given "uname" is a unique one or not.
//This function will read "uname_pwd_list" linked list and check given
//"uname" is a unique one or not (returns SUCCESS on unique else FAILURE).
char is_unique_uname(string uname);

//function declaration to create new account
//add new account node to the last of the linked list
void create_new_account(string uname, string pwd);

//Function declaration to write "uname_pwd.txt" with the updated list
char write_uname_pwd_file(void);

//Function declaration to append new user details to "uname_pwd.txt"
char append_uname_pwd_file(string uname, string pwd);

//function declaration to print menu for new account creation
void create_new_account_menu(void);

#endif
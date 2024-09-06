//this file contains function definitions and varibale, class, which is common to
//student login and new account creation

#include "common_func.hpp"

//function definition to store pwd to uname_pwd_class
//for this project uname is kept fixed
void store_pwd(uname_pwd_class *usr_ptr, string pwd)
{
	usr_ptr->pwd = pwd;
}

//function definition to get pwd from class uname_pwd_class
//uname is public, no need for its separate get_function
string get_pwd(uname_pwd_class *usr_ptr)
{
    return usr_ptr->pwd;
}


//function definition to hide password while user enter it
string getPassword(string msg) 
{
    string password;
    char ch;
    struct termios oldt, newt;

    //get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    //disable echo and canonical mode
	//by disabling echo, entered characters are not printed on the screen
	//by disabling canonical mode, input stream is unbuffered 
    // and '*' is printed after each entered character
    newt.c_lflag &= ~(ECHO | ICANON);  
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    cout << msg;
    while (true) 
	{
		//read one character at a time
        ch = getchar();  

		//exit loop on Enter key
        if (ch == '\n') 
		{ 
            break;  
        } 
		//handle backspace (as canonical mode is diabled)
		//'\b' is backspace character with ASCII value decimal 8
		//Backspace key on keyboard corresponds to DEL character (127 ASCII)
		else if (ch == '\b' || ch == 127) 
		{  
            if (!password.empty()) 
			{
				//remove the last character from password
                password.pop_back();  
				//erase the last '*' displayed
                cout << "\b \b";  
            }
        } 
		else
		{
			//add character to password
            password += ch;  
			//display *
            cout << '*';  
        }
    }

	//move to the next line after enter
    cout << endl;  

    //restore original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return password;
}

//function definition to wait till, user press "SPACE"
void key_wait(void)
{
    char ch;
    struct termios oldt, newt;

    //get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    //disable canonical mode
	//by disabling canonical mode, input stream is unbuffered
    newt.c_lflag &= ~ICANON;  
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    cout << "Press \"SPACE\" to continue";
    while(1)
    {
        ch = getchar();
        if(ch == '\n')
        {
            continue;
        }
        else if(ch == ' ')
        {
            break;
        }
        else
        {
            cout << "Error   : Invalid key pressed" << endl;
            cout << "Info    : Please press \"SPACE\" to continue" << endl;
        }
    }

    //restore original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

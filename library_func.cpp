//this file contains function definitions, which are
//related to library operation

#include "common_func.hpp"
#include "login_func.hpp"

//function definition to read file "books_details.txt", which contains list of
//all books and its details, all these details are stored in a list "books_list"
char read_books_details_file(void)
{
	//open file for reading
	ifstream read_file(books_details_filename);

    //Check if the file was opened successfully
    if(!read_file) 
	{
        cout << format("Error   : Can't open file \"{}\"\n",books_details_filename);
        return FAILURE;
    }

    //Read words by word
	//temp is used to iterate over linked list
	book_class *temp = NULL;
    while(1) 
	{
		//read book title, book author, and book counts from file
		string book_title, book_author;
        int book_count;
		read_file >> book_title;
		read_file >> book_author;
        read_file >> book_count;

		if(book_title.length() > 0)
		{
			//if linked list is empty
			if(books_list == NULL)
			{
				//store book details in head node
				books_list = new book_class;
				books_list->title = book_title;
                books_list->author = book_author;
                books_list->count = book_count;
				books_list->next = NULL;
				temp = books_list;
				continue;
			}

			//store book details in next node
			temp->next = new book_class;
			temp->next->title = book_title;
            temp->next->author = book_author;
            temp->next->count = book_count;
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
	book_last_node = temp;
	return SUCCESS;
}

//function definiton to add new book details in the linked list
void add_book_details(string book_title, string book_author,int book_count)
{
	//if no account is created till now
	if(books_list == NULL)
	{
		//store book details in head node
		books_list = new book_class;
		books_list->title = book_title;
        books_list->author = book_author;
        books_list->count = book_count;
		books_list->next = NULL;
		book_last_node = books_list;
		return;
	}

	//use last node pointer to get the last node
	//store book details in next node
    book_last_node->next = new book_class;
	book_last_node->next->title = book_title;
    book_last_node->next->author = book_author;
    book_last_node->next->count = book_count;
	book_last_node->next->next = NULL;
	book_last_node = book_last_node->next;
}

//Function definition to append new book details to the file "books_details.txt",
//which contains all books information.
char append_books_details_file(string book_title, string book_author,int book_count)
{
	//open file for writing in append mode
	ofstream write_file(books_details_filename, ios::app);

	//Check if the file was opened successfully
	if(!write_file) 
	{
		cout << format("Error   : Can't open file \"{}\"\n",books_details_filename);
		return FAILURE;
	}

	//append new uname and pwd to the file
    string sentance = format("{}\t{}\t{}\n",book_title, book_author, book_count);
	write_file << sentance;

	//close the file
	write_file.close();
	return SUCCESS;
}

//function definition to write write book_list back to the file "books_details.txt"
char write_books_details_file(void)
{
	//open file for writing
	ofstream write_file(books_details_filename);

	//Check if the file was opened successfully
	if(!write_file) 
	{
		cout << format("Error   : Can't open file \"{}\"\n",books_details_filename);
		return FAILURE;
	}

    //iterate over list and write each book details
	book_class *temp = books_list;
    while(temp)
	{
        string sentance = format("{}\t{}\t{}\n",temp->title, temp->author, temp->count);
		write_file << sentance;
		temp = temp->next;
	}

    //close the file
	write_file.close();
	return SUCCESS;
}

//function definition to check given book already exists in list or not
char book_exists(string book_title)
{
    ///iterate over list
	book_class *temp = books_list;
    while(temp)
	{
        //if book already exists
        if(book_title == temp->title)
        {
            //read number of new units
            int new_units = 0;
            cout << format("\nInfo    : Book \"{}\" already exists in the list\n",book_title);
            cout << format("Info    : Current count of book \"{}\" is/are {}\n\n",book_title, temp->count);
            cout << "Enter number of new units to be added : ";
            cin  >> new_units;

            //update book count and print it
            temp->count += new_units;
            cout << format("\nSuccess : {} units of book \"\" is/are added\n",new_units, book_title);
            cout << format("Info    : Current count of book \"{}\" is/are {}\n",book_title, temp->count);

            //write updated book details in the file "books_details.txt"
            write_books_details_file();

            //return SUCCESS after updating count
            return SUCCESS;
        }
		temp = temp->next;
	}

    //return FAILURE if given book is new
    return FAILURE;
}


//function definition to print books_list
void print_books_list(void)
{
    if(books_list == NULL)
    {
        cout << "There is no book present in the library" << endl;
        return;
    }

    //print header info
    cout << format("\nBOOK_TITLE\t BOOK_AUTHOR\t BOOK_COUNT\n");

    //iterate over list and print each book details
	book_class *temp = books_list;
    while(temp)
	{
        //print books details with left alignment
        cout << format("{:<10}\t {:<11}\t {:<10}\n",temp->title, temp->author, temp->count);
		temp = temp->next;
	}
    cout << endl;
}

//function definition to print available books, whose count is >= 1
void print_available_books(void)
{
    if(books_list == NULL)
    {
        cout << "There is no book present in the library" << endl;
        return;
    }

    //print header info
    cout << format("\nBOOK_TITLE\t BOOK_AUTHOR\t BOOK_COUNT\n");

    //iterate over list and print each book details
	book_class *temp = books_list;
    while(temp)
	{
        if(temp->count >= 1)
        {
		    //print books details with left alignment
            cout << format("{:<10}\t {:<11}\t {:<10}\n",temp->title, temp->author, temp->count);
        }
        temp = temp->next;
	}
    cout << endl;
}

//function definition to check given book is available or not
//pointer of that book node is returned
book_class* is_book_available(string book_title)
{
    //iterate over books_list
	book_class *temp = books_list;
    while(temp)
	{
        //if book title matches, and its count is >= 1
        if(temp->title == book_title && temp->count >= 1)
        {
            return temp;
        }
        temp = temp->next;
	}

    //return NULL if book is not available
    return NULL;
}


//function definition to write file "borrowers_details.txt" with the 
//updated borrowers_list of each books_list nodes
char write_borrowers_details_file(void)
{
	//open file for writing
	ofstream write_file(borrowers_details_filename);

	//Check if the file was opened successfully
	if(!write_file) 
	{
		cout << format("Error   : Can't open file \"{}\"\n",borrowers_details_filename);
		return FAILURE;
	}

    //iterate over books_list
	book_class *book_ptr = books_list;
    while(book_ptr)
	{
        //if borrowers_list of current books_list node is not NULL
        if(book_ptr->borrowers_list != NULL)
        {
            //write book title to the file
            write_file << format("{}",book_ptr->title);

            //iterate over borrowers_list of current books_list node
            uname_pwd_class *usr_ptr = book_ptr->borrowers_list;
            while(usr_ptr)
            {
                //write each uname to the file
                write_file << format("\t{}",usr_ptr->uname);
                
                //for last node, write new-line to file
                if(usr_ptr->next == NULL)
                {
                    write_file << endl;
                }
		        usr_ptr = usr_ptr->next;
            }
        }
        book_ptr = book_ptr->next;
	}

    //close the file
	write_file.close();
	return SUCCESS;
}

//function definition to read file "borrowers_details.txt" and update
//borrowers_list of each book_class node
char read_borrowers_details_file(void)
{
    //open file for reading
	ifstream read_file(borrowers_details_filename);

    //Check if the file was opened successfully
    if(!read_file) 
	{
        cout << format("Error   : Can't open file \"{}\"\n",borrowers_details_filename);
        return FAILURE;
    }

    //read word by word
    while(1)
    {
        //read book title, it is in first column
        string book_title;
        read_file >> book_title;
        //if some book name exists in this file, then books_list is not empty
        if(book_title.length() > 0)
        {
            //find same book_title in books_list
            book_class *book_ptr = books_list;
            //iterate over books_list
            while(book_ptr)
            {
                //if book title matches
                if(book_title == book_ptr->title)
                {
                    //read user name from file
                    string uname;
                    read_file >> uname;

                    //first store uname in the head node
                    book_ptr->borrowers_list = new uname_pwd_class;
                    book_ptr->borrowers_list->uname = uname;
                    book_ptr->borrowers_list->next = NULL;

                    //now store each uname in borrowers_list
                    uname_pwd_class *usr_ptr = book_ptr->borrowers_list;
                    while(1)
                    {
                        //if next char is a new line
                        char ch = read_file.peek();
                        if(ch == '\n')
                        {
                            //then break out of inner loop
                            break;
                        }

                        //store uname in the next node
                        read_file >> uname;
                        usr_ptr->next = new uname_pwd_class;
                        usr_ptr->next->uname = uname;
                        usr_ptr->next->next = NULL;
                        usr_ptr = usr_ptr->next;
                    }

                    //break out of loop, after storing borrowers list
                    break;
                }
                book_ptr = book_ptr->next;
            }
        }
        else
        {
            //break after reading last book
            break;
        }
    }
    //close the file
	read_file.close();
    return SUCCESS;
}

//function definition to add given username in the borrowers_list of book
char borrow_book(book_class *book_ptr, string uname)
{
    //no borrow user is added yet
    if(book_ptr->borrowers_list == NULL)
    {
        //add given uname in the borrow_list of book_ptr
        book_ptr->borrowers_list = new uname_pwd_class;
        book_ptr->borrowers_list->uname = uname;
        book_ptr->borrowers_list->next = NULL;

        //decrement the book count
        book_ptr->count--;

        //write updated book details in the file "books_details.txt"
        write_books_details_file();
        //write updated borrowers details in the file "borrowers_details.txt"
        write_borrowers_details_file();

        return SUCCESS;
    }

    //iterate over borrow_list 
    uname_pwd_class *temp = book_ptr->borrowers_list;
    while(temp)
    {
        //if user is already present in the list
        if(uname == temp->uname)
        {
            cout << uname << "" << temp->uname << endl;
            sleep(5);
            return DUPLICATE;
        }
        //if current node is the last node
        else if(temp->next == NULL)
        {
            //add given user at the last
            temp->next = new uname_pwd_class;
            temp->next->uname = uname;
            temp->next->next = NULL; 

            //decrement the book count
            book_ptr->count--;

            //write updated book details in the file "books_details.txt"
            write_books_details_file();
            //write updated borrowers details in the file "borrowers_details.txt"
            write_borrowers_details_file();
            return SUCCESS;
        }
        temp = temp->next;
    }
    return SUCCESS;
}

//function definition to print all books borrowed by the given user
void print_borrowed_books(string uname)
{
    if(books_list == NULL)
    {
        cout << format("No book is borrowed by user \"{}\"\n",uname) << endl;
        return;
    }

    //iterate over books_list and find out given borrower name
    int books_borrowed_count = 0;
    book_class *book_ptr = books_list;
    while(book_ptr)
    {
        //iterate over each borrow user of current book node
        uname_pwd_class *usr_ptr = book_ptr->borrowers_list;
        while(usr_ptr)
        {
            //if username matches
            if(uname == usr_ptr->uname)
            {
                //print header only for once
                if(books_borrowed_count == 0)
                {
                    //print header info
                    cout << format("\nBOOK_TITLE\t BOOK_AUTHOR\n");
                }

                //then increment the count and print book title
                books_borrowed_count++;
                //print books details with left alignment
                cout << format("{:<10}\t {:<11}\n",book_ptr->title, book_ptr->author);
                break;
            }
            usr_ptr = usr_ptr->next;
        }
        book_ptr = book_ptr->next;
    }

    if(books_borrowed_count == 0)
    {
        cout << format("No book is borrowed by user \"{}\"",uname) << endl;
    }
    cout << endl;
}


//function definition to check given book is borrowed by given user or not
book_class* is_book_borrowed(string book_title, string uname)
{
    if(books_list == NULL)
    {
        return NULL;
    }

    //iterate over books_list and check if given is borrowed or not
    book_class *book_ptr = books_list;
    while(book_ptr)
    {
        //if book title matches
        if(book_title == book_ptr->title)
        {
            //iterate over each borrow user of current book node
            uname_pwd_class *usr_ptr = book_ptr->borrowers_list;
            while(usr_ptr)
            {
                //if username matches
                if(uname == usr_ptr->uname)
                {
                    //then return pointer to book node
                    return book_ptr;
                }
                usr_ptr = usr_ptr->next;
            }

            //return NULL if no user matches
            return NULL;
        }
        book_ptr = book_ptr->next;
    }

    //return NULL at last
    return NULL;
}

//function definition to remove given username from borrowers_list of book
void return_book(book_class *book_ptr, string uname)
{
    //if given user is a head node
    if(uname == book_ptr->borrowers_list->uname)
    {
        //remove head node (free the dynamic memory used by it)
        uname_pwd_class *temp = book_ptr->borrowers_list->next;
        free(book_ptr->borrowers_list);
        book_ptr->borrowers_list = temp;

        //increment the book count
        book_ptr->count++;

        //write updated book details in the file "books_details.txt"
        write_books_details_file();
        //write updated borrowers details in the file "borrowers_details.txt"
        write_borrowers_details_file();
        return;
    }

    //iterate over borrow_list 
    uname_pwd_class *temp1 = book_ptr->borrowers_list;
    while(temp1)
    {
        //if next node username matches
        if(uname == temp1->next->uname)
        {
            //remove next node (free the dynamic memory used by it)
            uname_pwd_class *temp2 = temp1->next->next;
            free(temp1->next);
            temp1->next = temp2;

            //increment the book count
            book_ptr->count++;

            //write updated book details in the file "books_details.txt"
            write_books_details_file();
            //write updated borrowers details in the file "borrowers_details.txt"
            write_borrowers_details_file();
            return;
        }
        temp1 = temp1->next;
    }
}


//function definition to print library menu for admin
void admin_library_view(void)
{
    //print and read choices
    char choice = 0;
    do
    {
        //clear screen before calling next function
		system("clear");
        cout << "Library menu for admin" << endl << endl;
        cout << "1) Books present" << endl;
        cout << "2) Add book" << endl;
        cout << "3) Exit" << endl << endl;
        cout << "Enter your choice : ";
        cin  >> choice;

        //considering exit condition before
        if(choice == '3')
        {
            cout << endl;
            break;
        }

        //variables to store book details
        string book_title, book_author;
        int book_count;

        switch(choice)
        {
            //print books list
            case '1':
                //clear screen before calling next function
		        system("clear");
                cout << "List of books available in the library" << endl;
                print_books_list();
                break;
            
            //add a new book
            case '2':
                //clear screen before calling next function
		        system("clear");

                //read book title, book author, and book counts from user
                cout << "Add a book in the library" << endl;
                cout << "Enter book title  : ";
                cin  >> book_title;

                //if book is new
                if(book_exists(book_title) == FAILURE)
                {
                    cout << "Enter book author : ";
                    cin  >> book_author;
                    cout << "Enter book count  : ";
                    cin  >> book_count;

                    //call function to add new book details in the linked list
                    add_book_details(book_title, book_author, book_count);
                    //call function to append new book details to the file "books_details.txt"
                    append_books_details_file(book_title, book_author, book_count);

                    cout << format("\nSuccess : Book \"{}\" is added\n",book_title);
                }

                break;
            
            default:
                //print error and wait for DELAY_SEC seconds
                cout << endl << "Error   : Please enter a valid choice" << endl;     
        }
        key_wait();
    }
    while(1);
}

//function definition to print library menu of current student
void student_library_view(uname_pwd_class *usr_ptr)
{
    char choice = 0;
    do
    {
        //clear screen before calling next function
		system("clear");
        cout << format("Libray menu for student \"{}\"\n\n",usr_ptr->uname);
        cout << "1) List of books available" << endl;
        cout << "2) List of books borrowed" << endl;
        cout << "3) Borrow book" << endl;
        cout << "4) Return book" << endl;
        cout << "5) Change password" << endl;
        cout << "6) Exit" << endl << endl;
        cout << "Enter your choice : ";
        cin  >> choice;

        //considering exit condition separately
        if(choice == '6')
        {
            break;
        }
        //change password option is considered separately, because after
        //this main login menu should be displayed
        else if(choice == '5')
        {
            //change user password
            //clear screen before calling next function
		    system("clear");
            change_user_pwd(usr_ptr);
            key_wait();
            break;
        }

        switch(choice)
        {
            //print books available
            case '1':
                //clear screen before calling next function
		        system("clear");
                cout << "List of books available in the library" << endl;
                print_available_books();
                break;


            //print list of borrowed books 
            case '2':
                //clear screen before calling next function
		        system("clear");
                cout << format("List of books borrowed by user \"{}\"\n",usr_ptr->uname);
                print_borrowed_books(usr_ptr->uname);
                break;
            

            //borrow a book from library
            case '3':
                {
                    //clear screen before calling next function
		            system("clear");

                    //read borrow book name from user
                    string book_title;
                    cout << format("Borrow a book from library for user \"{}\"",usr_ptr->uname) << endl;
                    cout << "Enter book title : ";
                    cin  >> book_title;

                    //check if book is available or not
                    book_class *book_ptr = is_book_available(book_title);
                    if(book_ptr == NULL)
                    {
                        cout << format("\nInfo    : Book \"{}\" is not available\n",book_title);
                    }
                    else
                    {
                        //call function to add this user in the borrow_list of book
                        char res = borrow_book(book_ptr, usr_ptr->uname);
                        if(res == DUPLICATE)
                        {
                            cout << format("\nInfo    : Book \"{}\" is already borrowed by this user\n",book_title);  
                        }
                        else
                        {
                            cout << format("\nSuccess : Book \"{}\" is borrowed\n",book_title);
                        }
                    }
                }
                break;


            //return a book to library
            case '4':
                {
                    //clear screen before calling next function
		            system("clear");

                    //read book name to be returned
                    string book_title;
                    cout << format("Return a book to library for user \"{}\"",usr_ptr->uname) << endl;
                    cout << "Enter book title : ";
                    cin  >> book_title;

                    //check if given book is borrowed by current user or not
                    book_class *book_ptr = is_book_borrowed(book_title, usr_ptr->uname);
                    if(book_ptr == NULL)
                    {
                        cout << format("\nInfo    : Book \"{}\" is not borrowed by this user\n",book_title);
                    }
                    else
                    {
                        //call function to add return given book
                        //current user is removed from the borrowers_list of given book node
                        return_book(book_ptr, usr_ptr->uname);
                        cout << format("\nSuccess : Book \"{}\" is returned\n",book_title);
                    }
                }
                break;


            default:
                cout << endl << "Error   : Please enter a valid choice" << endl;
        }
        key_wait();
    }
    while(1);
}

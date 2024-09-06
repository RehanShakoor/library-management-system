//this file contains function declarations, which are
//related to library operations

#ifndef LIBRARY_FUNC_HPP
#define LIBRARY_FUNC_HPP

#include "common_func.hpp"

//function declaration to read file "books_details.txt", which contains list of
//all books and its details, all these details are stored in a list "books_list"
char read_books_details_file(void);

//function declaration to add new book details in the linked list
void add_book_details(string book_title, string book_author,int book_count);

//Function declaration to append new book details to the file "books_details.txt",
//which contains all books information.
char append_books_details_file(string book_title, string book_author,int book_count);

//function definition to write updated book_list back to the file "books_details.txt"
char update_books_details_file(void);

//function declaration to print books_list
void print_books_list(void);

//function declaration to print available books, whose count is >= 1
void print_available_books(void);

//function declaration to check given book already exists in list or not
char book_exists(string book_title);

//function declaration to check given book is available or not
//pointer of that book node is returned
book_class* is_book_available(string book_title);

//function declaration to add given username in the borrow_list of book
char borrow_book(book_class *book_ptr, string uname);

//function declaration to read file "borrowers_details.txt" and update
//borrowers_list of each book_class node
char read_borrowers_details_file(void);

//function declaration to write file "borrowers_details.txt" with the 
//updated borrowers_list of each books_list nodes
char write_borrowers_details_file(void);

//function declaration to print all books borrowed by the given user
void print_borrowed_books(string uname);

//function declaration to remove given username from borrowers_list of book
void return_book(book_class *book_ptr, string uname);

//function declaration to print library menu for admin
void admin_library_view(void);

//function declaration to print library menu of current student
void student_library_view(uname_pwd_class *ptr);

#endif
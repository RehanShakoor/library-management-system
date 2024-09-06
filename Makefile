CC = g++
CFLAGS = -std=c++20
TARGET = lib_man

all : main.o login_func.o library_func.o common_func.o
	$(CC) $(CFLAGS) main.o login_func.o library_func.o common_func.o -o $(TARGET)

main.o : main.cpp
	$(CC) $(CFLAGS) -c main.cpp

login_func.o : login_func.cpp
	$(CC) $(CFLAGS) -c login_func.cpp  

library_func.o : library_func.cpp
	$(CC) $(CFLAGS) -c library_func.cpp 

common_func.o : common_func.cpp 
	$(CC) $(CFLAGS) -c common_func.cpp  

clean : 
	rm *.o $(TARGET)

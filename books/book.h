#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>

#define BUFFER_SIZE 100

struct BOOK
{
	char author[BUFFER_SIZE];
	char header[BUFFER_SIZE];
	int year;
	int price;
	char category[BUFFER_SIZE];
};

extern BOOK ScanBook();
extern void PrintBook(const BOOK& printingBook);
extern void MyScanf(char** buffer, int sizeOfBuffer);
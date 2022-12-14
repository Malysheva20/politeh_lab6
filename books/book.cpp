#include "book.h"

void MyScanf(char** buffer, int sizeOfBuffer) {
	// memory allocation
	*buffer = (char*)malloc(sizeof(char) * sizeOfBuffer);

	// checking memory
	if (buffer == nullptr)
		return;

	char sym;
	int cnt = 0;
	// writing in buffer
	while ((sym = _getch()) && sym != 13 && sym != 27 && cnt < sizeOfBuffer) {
		if (sym == 8) {
			printf("\b");
			cnt--;
		}
		else {
			printf("%c", sym);
			(*buffer)[cnt++] = sym;
		}
	}
	while (cnt < sizeOfBuffer)
		(*buffer)[cnt++] = 0;
	printf("\n");
}

bool IsNumber(char* stringToCheck, int numOfElements) {
	bool flag = true;
	int i = 0;

	// checking digit symbols
	while (flag && i < numOfElements && stringToCheck[i] != 0) {
		if (stringToCheck[i] - '0' < 0 || stringToCheck[i] - '0' > 9)
			flag = false;
		i++;
	}
	return flag;
}

int StringToNumber(char* stringToTransform, int numOfElements) {
	int result = 0, i = 0;

	// converting string to integer number
	for (i = 0; i < numOfElements && stringToTransform[i] != 0; i++)
		result = result * 10 + stringToTransform[i] - '0';

	return result;
}

/* Printing book data function.
 * ARGUMENTS:
 *  - const BOOK& printingBook;
 * RETURNS:
 * (None).
 */
void PrintBook(const BOOK& printingBook) {
	// printing book elements
	printf("author: %s\n", printingBook.author);
	printf("header: %s\n", printingBook.header);
	printf("year of publication: %i\n", printingBook.year);
	printf("price: %i\n", printingBook.price);
	printf("category: %s\n", printingBook.category);
}

int CheckYear(int year) {
	// checking year
	if (year < 2022 && year > 0)
		return year;
	printf("Ooops, error! :'(\n");
	return 2021;
}

int CheckPrice(int price) {
	// checking price
	if (price > 0)
		return price;

	printf("Ooops, error! Now your price is 100 :'(\n");
	return 100;
}

char* CheckCategory(char* category) {
	// category array
	char list[4][BUFFER_SIZE] = { "fantasy", "manga", "classic", "roman" };
	
	while (true) {
		for (int i = 0; i < 4; i++) {
			// checking category
			if (strcmp(list[i], category) == 0) {
				return category;
			}
		}

		// scanning new input
		printf("Sorry, but choose category from list: fantasy, manga, classic, roman:'(\n");
		char* tmpbuf;
		MyScanf(&tmpbuf, BUFFER_SIZE);
		strcpy(category, tmpbuf);
		free(tmpbuf);
	}
}

BOOK ScanBook() {
	BOOK newBook;
	char st[BUFFER_SIZE] = { 0 };
	char* tmpbuf;

	// scanning author
	printf("author: ");
	MyScanf(&tmpbuf, BUFFER_SIZE);
	strcpy(newBook.author, tmpbuf);
	free(tmpbuf);

	// scanning header
	printf("header: ");
	MyScanf(&tmpbuf, BUFFER_SIZE);
	strcpy(newBook.header, tmpbuf);

	// scanning year
	int flagnum = true;
	do {
		free(tmpbuf);
		printf("year of publication: ");
		MyScanf(&tmpbuf, BUFFER_SIZE);
		flagnum = !IsNumber(tmpbuf, BUFFER_SIZE);
	} while (flagnum);
	newBook.year = CheckYear(StringToNumber(tmpbuf, BUFFER_SIZE));

	// scanning price
	do {
		free(tmpbuf);
		printf("price: ");
		MyScanf(&tmpbuf, BUFFER_SIZE);
		flagnum = !IsNumber(tmpbuf, BUFFER_SIZE);
	} while (flagnum);
	newBook.price = CheckPrice(StringToNumber(tmpbuf, BUFFER_SIZE));

	// scanning category
	printf("Choose category from list: fantasy, manga, classic, roman\n");
	MyScanf(&tmpbuf, BUFFER_SIZE);
	strcpy(st, tmpbuf);
	free(tmpbuf);
	strcpy(newBook.category, CheckCategory(st));

	return newBook;
}

#include "book.h"

void MyScanf(char** buffer, int sizeOfBuffer) {
	*buffer = (char*)malloc(sizeof(char) * sizeOfBuffer);

	if (buffer == nullptr)
		return;

	char sym;
	int cnt = 0;
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

	while (flag && i < numOfElements && stringToCheck[i] != 0) {
		if (stringToCheck[i] - '0' < 0 || stringToCheck[i] - '0' > 9)
			flag = false;
		i++;
	}
	return flag;
}

int StringToNumber(char* stringToTransform, int numOfElements) {
	int result = 0, i = 0;

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
	printf("author: %s\n", printingBook.author);
	printf("header: %s\n", printingBook.header);
	printf("year of publication: %i\n", printingBook.year);
	printf("price: %i\n", printingBook.price);
	printf("category: %s\n", printingBook.category);
}

int CheckYear(int year) {
	if (year < 2022 && year > 0)
		return year;
	printf("Ooops, error! :'(\n");
	return 2021;
}

int CheckPrice(int price) {
	if (price > 0)
		return price;

	printf("Ooops, error! :'(\n");
	return 100;
}

char* CheckCategory(char* category) {
	char list[4][BUFFER_SIZE] = { "fantasy", "manga", "classic", "roman" };
	while (true) {
		for (int i = 0; i < 4; i++) {
			if (strcmp(list[i], category) == 0) {
				return category;
			}
		}

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

	printf("author: ");
	MyScanf(&tmpbuf, BUFFER_SIZE);
	strcpy(newBook.author, tmpbuf);
	free(tmpbuf);

	printf("header: ");
	MyScanf(&tmpbuf, BUFFER_SIZE);
	strcpy(newBook.header, tmpbuf);

	int flagnum = true;
	do {
		free(tmpbuf);
		printf("year of publication: ");
		MyScanf(&tmpbuf, BUFFER_SIZE);
		flagnum = !IsNumber(tmpbuf, BUFFER_SIZE);
	} while (flagnum);
	newBook.year = CheckYear(StringToNumber(tmpbuf, BUFFER_SIZE));

	do {
		free(tmpbuf);
		printf("price: ");
		MyScanf(&tmpbuf, BUFFER_SIZE);
		flagnum = !IsNumber(tmpbuf, BUFFER_SIZE);
	} while (flagnum);

	newBook.price = CheckPrice(StringToNumber(tmpbuf, BUFFER_SIZE));

	printf("Choose category from list: fantasy, manga, classic, roman\n");
	MyScanf(&tmpbuf, BUFFER_SIZE);
	strcpy(st, tmpbuf);
	free(tmpbuf);
	strcpy(newBook.category, CheckCategory(st));

	return newBook;
}

BOOK bookglobal = { "Masashi Kishimoto", "Naruto", 23, 840, "manga" };

void BookTask() {
	BOOK booklocal = { "Masashi Kishimoto", "Naruto", 23, 840, "manga" };
	static BOOK bookstat = { "Masashi Kishimoto", "Naruto", 23, 840, "manga" };
	BOOK* bookdynamic = new BOOK{ "Masashi Kishimoto", "Naruto", 23, 840, "manga" };

	printf("%i\n", (int)sizeof(bookglobal));
	printf("%i\n", (int)sizeof(booklocal));
	printf("%i\n", (int)sizeof(bookstat));
	printf("%i\n", (int)sizeof(bookdynamic));

	PrintBook(bookglobal);
	PrintBook(booklocal);
	PrintBook(bookstat);
	PrintBook(*bookdynamic);

	BOOK bookTest = ScanBook();
	PrintBook(bookTest);
}
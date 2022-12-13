#include "book.h"
#include "library.h"

void PrintLibrary(BOOK* library, int numOfElements) {
	BOOK* ptr = library;
	int cnt = 0;

	while (numOfElements-- > 0) {
		printf("Book #%i\n", cnt);
		PrintBook(*ptr);
		cnt++;
		ptr++;
	}
}

void AddNewBook(BOOK **library, int *numOfElements ) {
	BOOK * ptr = (BOOK*)malloc((*numOfElements + 1) * sizeof(char) * BUFFER_SIZE * 3 + sizeof(int) * 2);

	if (ptr == nullptr) {
		printf("Memory error\n");
		return;
	}

	for (int i = 0; i < *numOfElements; i++)
		ptr[i] = (*library)[i];

	free(*library);
	*library = ptr;
	
	*(*library + *numOfElements) = ScanBook();
	printf("Book added\n");
	(*numOfElements)++;
}

void DeleteBook(BOOK** library, int* numOfElements, int elementToDelete) {
	if (*numOfElements < 1) {
		printf("No elements in library\n");
		return;
	}
	if (elementToDelete < 0 || elementToDelete >= *numOfElements) {
		printf("No such element in library\n");
		return;
	}

	BOOK *ptr = (BOOK*)malloc((*numOfElements - 1) * sizeof(char) * BUFFER_SIZE * 3 + sizeof(int) * 2);

	if (ptr == nullptr) {
		printf("Memory error\n");
		return;
	}

	int flagnoelement = 0;
	for (int i = 0; i < *numOfElements - 1; i++) {
		if (i == elementToDelete)
			flagnoelement = 1;
		ptr[i] = (*library)[i + flagnoelement];
	}

	free(*library);
	*library = ptr;
	(*numOfElements)--;

	printf("Book #%i deleted\n", elementToDelete);
}

void PrintInFile(BOOK* library, int numOfElements, const char* fileName) {
	FILE* F;

	if ((F = fopen(fileName, "wb")) == nullptr) {
		printf("Error loading file");
		return;
	}

	fwrite(&numOfElements, sizeof(int), 1, F);

	for (int i = 0; i < numOfElements; i++)
		fwrite(&(library[i]), sizeof(char) * BUFFER_SIZE * 3 + sizeof(int) * 2, 1, F);

	fclose(F);
}

void LoadFromFile(BOOK** library, int *numOfElements, const char* fileName) {
	FILE* F;

	if ((F = fopen(fileName, "rb")) == nullptr) {
		printf("Error loading file");
		return;
	}

	fread(numOfElements, sizeof(int), 1, F);

	free(*library);
	*library = (BOOK*)malloc(sizeof(BOOK) * *numOfElements);

	if (*library == nullptr) {
		printf("Memory error\n");
		return;
	}

	for (int i = 0; i < *numOfElements; i++)
		fread(*library + i, sizeof(char) * BUFFER_SIZE * 3 + sizeof(int) * 2, 1, F);

	fclose(F);
}

int CmpStr(void* a, void* b) {
	char* a1 = (char*)a;
	char* b1 = (char*)b;

	int flag = 0;
	int i;

	for (i = 0; flag == 0 && ((*a1 + i) != 0 || (*b1 + i) != 0); i++)
		if ((*a1 + i) < (*b1 + i))
			flag = 1;
		else if ((*a1 + i) > (*b1 + i))
			flag = -1;
	if (flag && ((*a1 + i) == 0))
		flag = 1;
	return -flag;
}

void SortLibrary(BOOK** library, int numofElements, int param) {
	if (param == 0)
		for (int i = 0; i < numofElements; i++)
			for (int j = i + 1; j < numofElements; j++)
				if (CmpStr(&((*library)[i].author), &((*library)[j].author)) == 1) {
					BOOK tmp = (*library)[i];
					(*library)[i] = (*library)[j];
					(*library)[j] = tmp;
				}
	if (param == 1)
		for (int i = 0; i < numofElements; i++)
			for (int j = i + 1; j < numofElements; j++)
				if (CmpStr(&((*library)[i].header), &((*library)[j].header)) == 1) {
					BOOK tmp = (*library)[i];
					(*library)[i] = (*library)[j];
					(*library)[j] = tmp;
				}
	if (param == 2)
		for (int i = 0; i < numofElements; i++)
			for (int j = i + 1; j < numofElements; j++)
				if ((*library)[i].year > (*library)[j].year) {
					BOOK tmp = (*library)[i];
					(*library)[i] = (*library)[j];
					(*library)[j] = tmp;
				}
	if (param == 3)
		for (int i = 0; i < numofElements; i++)
			for (int j = i + 1; j < numofElements; j++)
				if ((*library)[i].price > (*library)[j].price) {
					BOOK tmp = (*library)[i];
					(*library)[i] = (*library)[j];
					(*library)[j] = tmp;
				}
	if (param == 4)
		for (int i = 0; i < numofElements; i++)
			for (int j = i + 1; j < numofElements; j++)
				if (CmpStr(&((*library)[i].category), &((*library)[j].category)) == 1) {
					BOOK tmp = (*library)[i];
					(*library)[i] = (*library)[j];
					(*library)[j] = tmp;
				}
}

void LibraryHandler(void) {
	bool isWorking = true;
	int size = 0;
	BOOK* library = nullptr;

	while (isWorking) {
		printf("Options:\n0 - exit\n1 - print library\n2 - add new book to library\n3 - delete book from library\n4 - upload library in file\n5 - load library from file\n6 - sort library\n");
		char* fileName = nullptr;
		switch (_getch())
		{
		case '0':
			isWorking = false;
			break;
		case '1':
			PrintLibrary(library, size);
			break;
		case '2':
			AddNewBook(&library, &size);
			break;
		case '3':
			int bookToDelete;
			printf("Input book number: ");
			scanf("%i", &bookToDelete);
			DeleteBook(&library, &size, bookToDelete);
			break;
		case '4':
			printf("Input file name: ");
			MyScanf(&fileName, BUFFER_SIZE);
			PrintInFile(library, size, fileName);
			free(fileName);
			break;
		case '5':
			printf("Input file name: ");
			MyScanf(&fileName, BUFFER_SIZE);
			LoadFromFile(&library, &size, fileName);
			free(fileName);
			break;
		case '6':
			printf("Sort by:\n0 - author\n1 - header\n2 - year\n3 - price\n4 - category\n");
			SortLibrary(&library, size, _getch() - '0');
		default:
			break;
		}
	}

	free(library);
}
#include "book.h"
#include "library.h"

void PrintLibrary(BOOK* library, int numOfElements) {
	int cnt = 0;

	// printing library books
	while (numOfElements-- > 0) {
		printf("Book #%i\n", cnt);
		PrintBook(*library);
		cnt++;
		library++;
	}
}

void AddNewBook(BOOK **library, int *numOfElements ) {
	// memory allocation
	BOOK * ptr = (BOOK*)malloc((*numOfElements + 1) * sizeof(char) * BUFFER_SIZE * 3 + sizeof(int) * 2);

	// checking memory
	if (ptr == nullptr) {
		printf("Memory error\n");
		return;
	}

	// copying elements
	for (int i = 0; i < *numOfElements; i++)
		ptr[i] = (*library)[i];

	// deleting old memory
	free(*library);

	// copying pointer
	*library = ptr;
	
	// adding new element
	*(*library + *numOfElements) = ScanBook();
	printf("Book added\n");
	(*numOfElements)++;
}

void DeleteBook(BOOK** library, int* numOfElements, int elementToDelete) {
	// checking number of elements
	if (*numOfElements < 1) {
		printf("No elements in library\n");
		return;
	}

	// checking number to delete
	if (elementToDelete < 0 || elementToDelete >= *numOfElements) {
		printf("No such element in library\n");
		return;
	}

	// memory allocation
	BOOK *ptr = (BOOK*)malloc((*numOfElements - 1) * sizeof(char) * BUFFER_SIZE * 3 + sizeof(int) * 2);

	// checking memory
	if (ptr == nullptr) {
		printf("Memory error\n");
		return;
	}

	// copying elements
	int flagnoelement = 0;
	for (int i = 0; i < *numOfElements - 1; i++) {
		if (i == elementToDelete)
			flagnoelement = 1;
		ptr[i] = (*library)[i + flagnoelement];
	}

	// deleting old memory
	free(*library);

	// copying pointer
	*library = ptr;
	(*numOfElements)--;
	printf("Book #%i deleted\n", elementToDelete);
}

void PrintInFile(BOOK* library, int numOfElements, const char* fileName) {
	FILE* F;

	// opening file
	if ((F = fopen(fileName, "wb")) == nullptr) {
		printf("Error loading file");
		return;
	}

	// writing number of elements
	fwrite(&numOfElements, sizeof(int), 1, F);

	// writing books
	for (int i = 0; i < numOfElements; i++)
		fwrite(&(library[i]), sizeof(char) * BUFFER_SIZE * 3 + sizeof(int) * 2, 1, F);

	// closing file
	fclose(F);
}

void LoadFromFile(BOOK** library, int *numOfElements, const char* fileName) {
	FILE* F;

	// opening file
	if ((F = fopen(fileName, "rb")) == nullptr) {
		printf("Error loading file");
		return;
	}

	// reading number of elements
	fread(numOfElements, sizeof(int), 1, F);

	// deleting old memory
	free(*library);

	// memory allocation
	*library = (BOOK*)malloc(sizeof(BOOK) * *numOfElements);

	// checking memory
	if (*library == nullptr) {
		printf("Memory error\n");
		return;
	}

	// reading books
	for (int i = 0; i < *numOfElements; i++)
		fread(*library + i, sizeof(char) * BUFFER_SIZE * 3 + sizeof(int) * 2, 1, F);

	// closing file
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
	// sorting
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
			// exit
			isWorking = false;
			break;
		case '1':
			// printing library
			PrintLibrary(library, size);
			break;
		case '2':
			// adding new book
			AddNewBook(&library, &size);
			break;
		case '3':
			// deleting book
			int bookToDelete;
			printf("Input book number: ");
			scanf("%i", &bookToDelete);
			DeleteBook(&library, &size, bookToDelete);
			break;
		case '4':
			// file writing
			printf("Input file name: ");
			MyScanf(&fileName, BUFFER_SIZE);
			PrintInFile(library, size, fileName);
			free(fileName);
			break;
		case '5':
			// file reading
			printf("Input file name: ");
			MyScanf(&fileName, BUFFER_SIZE);
			LoadFromFile(&library, &size, fileName);
			free(fileName);
			break;
		case '6':
			// sorting
			printf("Sort by:\n0 - author\n1 - header\n2 - year\n3 - price\n4 - category\n");
			SortLibrary(&library, size, _getch() - '0');
		default:
			break;
		}
	}

	// deleting memory
	free(library);
}
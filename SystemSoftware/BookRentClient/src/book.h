#define START_ID 1

typedef struct book
{
	int id;
	char title[30];
	int price;
	int rentCnt;
} BOOK;

void inputBook(int fd);
void searchBook(int fd);
void updateBook(int fd);
void deleteBook(int fd);
void showBook(int fd);

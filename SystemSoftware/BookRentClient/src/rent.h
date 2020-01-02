#define START_ID 1

typedef struct rent
{
	int id;
	int bookId;
	int cusId;
	char rentTime[30];
	char returnTime[30];
} RENT;

void rentBook(int fd);
void returnBook(int fd);
void showMyRent(int fd);

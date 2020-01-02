#define START_ID 1

typedef struct book
{
	int id;
	char title[30];
	int price;
	int rentCnt;
} BOOK;

void inputBook(int fd, FILE *fp_b);
void searchBook(int fd, FILE *fp_b);
void updateBook(int fd, FILE *fp_b);
void deleteBook(int fd, FILE **fp_b);
void showBook(int fd, FILE *fp_b);

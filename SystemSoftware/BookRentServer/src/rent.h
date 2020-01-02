#define START_ID 1

typedef struct rent
{
	int id;
	int bookId;
	int cusId;
	char rentTime[30];
	char returnTime[30];
} RENT;

void rentBook(int fd, FILE *fp_b,FILE *fp_r,int nowId);
void returnBook(int fd, FILE *fp_b,FILE *fp_r,int nowId);
void showMyRent(int fd,FILE *fp_r,int nowId);
char *getTime();

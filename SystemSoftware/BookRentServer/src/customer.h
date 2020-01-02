#define START_ID 1

typedef struct customer
{
	int id;
	char name[10];
	char phone[20];
	int point;
	char password[20];
} CUSTOMER;

void inputCustomer(int fd, FILE *fp_c);
void searchCustomer(int fd, FILE *fp_c);
void updateCustomer(int fd, FILE *fp_c);
void deleteCustomer(int fd, FILE **fp_c);
void showCustomer(int fd, FILE *fp_c);

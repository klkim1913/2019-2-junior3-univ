#define START_ID 1

typedef struct customer
{
	int id;
	char name[10];
	char phone[20];
	int point;
	char password[20];
} CUSTOMER;

void inputCustomer(int fd);
void searchCustomer(int fd);
void updateCustomer(int fd);
void deleteCustomer(int fd);
void showCustomer(int fd);

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <signal.h>
#include "book.h"
#include "customer.h"
#include "rent.h"

int nowLoginId = 0;

void runServer();
void runHome(int fd);
int login();
int runBook(int fd, FILE *fp_b);
int runCustomer(int fd, FILE *fp_c);

int main() {
	runServer();
	return 0;
}

void runServer() {
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(9734);
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr*) &server_address, server_len);

	listen(server_sockfd, 5);

	signal(SIGCHLD, SIG_IGN);

	while (1) {
		printf("server waiting\n");
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd,
				(struct sockaddr*) &client_address, &client_len);
		printf("client connect\n");
		if (fork() == 0) {
			runHome(client_sockfd);
			close(client_sockfd);
			printf("client disconnect\n");
			break;
		} else {
			close(client_sockfd);
		}
	}
}

void runHome(int fd) {
	int sel, ch, ch2 = 0;
	FILE *fp_b, *fp_c, *fp_r;

	fp_b = fopen("book.dat", "rb+");
	if (fp_b == NULL) {
		fp_b = fopen("book.dat", "wb+");
	}

	fp_c = fopen("customer.dat", "rb+");
	if (fp_c == NULL) {
		fp_c = fopen("customer.dat", "wb+");
	}

	fp_r = fopen("rent.dat", "rb+");
	if (fp_r == NULL) {
		fp_r = fopen("rent.dat", "wb+");
	}
	while (1) {
		rewind(fp_b);
		rewind(fp_c);
		rewind(fp_r);
		ch = read(fd, &sel, sizeof(sel));
		if (ch == 0)	// 홈에서 입력 없을때
			break;
		switch (sel) {
		case 0:
			ch2 = login(fd, fp_c);
			break;
		case 1:
			ch2 = runBook(fd, fp_b);
			break;
		case 2:
			ch2 = runCustomer(fd, fp_c);
			break;
		case 3:
			rentBook(fd, fp_b, fp_r, nowLoginId);
			break;
		case 4:
			returnBook(fd, fp_b, fp_r, nowLoginId);
			break;
		case 5:
			showMyRent(fd, fp_r, nowLoginId);
			break;
		}
		if (ch2 == -1) {	// 각 메뉴에서 입력 없을때
			break;
		}
	}
	fclose(fp_b);
	fclose(fp_c);
}

int login(int fd, FILE *fp_c) {
	CUSTOMER record;
	int id, ch, isSuc;
	char pw[20];

	ch = read(fd, &id, sizeof(id));
	if (ch == 0)
		return -1;
	ch = read(fd, pw, sizeof(pw));
	if (ch == 0)
		return -1;
	fseek(fp_c, (id - START_ID) * sizeof(record), SEEK_SET);
	if ((fread(&record, sizeof(record), 1, fp_c) > 0) && (record.id == id)
			&& (strcmp(record.password, pw) == 0)) {
		nowLoginId = record.id;
		isSuc = 0;
		write(fd, &isSuc, sizeof(isSuc));
	} else {
		isSuc = -1;
		write(fd, &isSuc, sizeof(isSuc));
	}
	return 0;
}
int runBook(int fd, FILE *fp_b) {
	int sel, key, ch;
	key = 1;
	while (key) {
		rewind(fp_b);
		ch = read(fd, &sel, sizeof(sel));
		if (ch == 0)
			return -1;
		switch (sel) {
		case 1:
			inputBook(fd, fp_b);
			break;
		case 2:
			searchBook(fd, fp_b);
			break;
		case 3:
			updateBook(fd, fp_b);
			break;
		case 4:
			deleteBook(fd, &fp_b);
			break;
		case 5:
			showBook(fd, fp_b);
			break;
		case 6:
			key = 0;
			break;
		}
	}
	return 0;
}

int runCustomer(int fd, FILE *fp_c) {

	int sel, key, ch;

	key = 1;
	while (key) {
		rewind(fp_c);
		ch = read(fd, &sel, sizeof(sel));
		if (ch == 0)	// 입력 없을때
			return -1;
		switch (sel) {
		case 1:
			inputCustomer(fd, fp_c);
			break;
		case 2:
			searchCustomer(fd, fp_c);
			break;
		case 3:
			updateCustomer(fd, fp_c);
			break;
		case 4:
			deleteCustomer(fd, &fp_c);
			break;
		case 5:
			showCustomer(fd, fp_c);
			break;
		case 6:
			key = 0;
			break;
		}
	}
	return 0;
}

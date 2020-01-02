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
#include "buffer.h"
#include "rent.h"

int nowLoginId = 0;

void runClient();
void runHome(int sid);
int login();
void runBook(int sid);
void runCustomer(int sid);
void alarmHandler();

int main() {
	signal(SIGALRM, alarmHandler);
	runClient();
	return 0;
}

void runClient() {
	int fd;

	struct sockaddr_in ssock;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	ssock.sin_family = AF_INET;
	ssock.sin_addr.s_addr = inet_addr("127.0.0.1");
	ssock.sin_port = htons(9734);

	connect(fd, (struct sockaddr*) &ssock, sizeof(ssock));

	while (1) {
		runHome(fd);
	}
	close(fd);
}

void runHome(int fd) {
	int sel, scanCh;

	while (1) {
		printf(
				"\n0. 로그인\n1. 책 정보관리\n2. 고객 정보관리\n3. 책 빌리기\n4. 책 반납하기\n5. 나의 대여기록 보기\n");
		printf("선택: ");
		alarm(60);
		scanCh = scanf("%d", &sel);
		clearBuffer();
		if ((scanCh == 1) && (0 <= sel) && (sel <= 5)) {
			alarm(0);
			write(fd, &sel, sizeof(sel));
			switch (sel) {
			case 0:
				nowLoginId = login(fd);
				break;
			case 1:
				runBook(fd);
				break;
			case 2:
				runCustomer(fd);
				break;
			case 3:
				if (nowLoginId == 0) {
					printf("로그인 하세요!\n");
				} else {
					rentBook(fd);
				}
				break;
			case 4:
				if (nowLoginId == 0) {
					printf("로그인 하세요!\n");
				} else {
					returnBook(fd);
				}
				break;
			case 5:
				if (nowLoginId == 0) {
					printf("로그인 하세요!\n");
				} else {
					showMyRent(fd);
				}
				break;
			}
		} else {
			printf("잘못 입력\n");
		}
	}
}
int login(int fd) {
	int inputId, isSuc;
	char inputPw[20];

	printf("고객 id 입력: ");
	alarm(60);
	scanf("%d", &inputId);
	alarm(0);
	clearBuffer();
	write(fd, &inputId, sizeof(inputId));
	printf("고객 비밀번호 입력: ");
	alarm(60);
	scanf("%s", inputPw);
	alarm(0);
	write(fd, inputPw, sizeof(inputPw));
	read(fd, &isSuc, sizeof(isSuc));
	if (isSuc == 0) {
		printf("로그인 성공!\n");
		return inputId;
	} else {
		printf("로그인 실패!\n");
		return 0;
	}
}
void runBook(int fd) {
	int sel, key, scanCh;

	key = 1;
	while (key) {
		printf(
				"\n1. 책 정보입력\n2. 책 정보검색\n3. 책 정보갱신\n4. 책 정보삭제\n5. 책 정보보기\n6. 이전으로\n");
		printf("선택: ");
		alarm(60);
		scanCh = scanf("%d", &sel);
		alarm(0);
		clearBuffer();
		if (scanCh == 1 && (1 <= sel) && (sel <= 6)) {
			write(fd, &sel, sizeof(sel));
			switch (sel) {
			case 1:
				inputBook(fd);
				break;
			case 2:
				searchBook(fd);
				break;
			case 3:
				updateBook(fd);
				break;
			case 4:
				deleteBook(fd);
				break;
			case 5:
				showBook(fd);
				break;
			case 6:
				key = 0;
				break;
			}
		} else {
			printf("잘못 입력\n");
		}
	}
}

void runCustomer(int fd) {

	int sel, key, scanCh;

	key = 1;
	while (key) {
		printf(
				"\n1. 고객 정보입력\n2. 고객 정보검색\n3. 고객 정보갱신\n4. 고객 정보삭제\n5. 고객 정보보기\n6. 이전으로\n");
		printf("선택: ");
		alarm(60);
		scanCh = scanf("%d", &sel);
		alarm(0);
		clearBuffer();
		if (scanCh == 1 && (1 <= sel) && (sel <= 6)) {
			write(fd, &sel, sizeof(sel));
			switch (sel) {
			case 1:
				inputCustomer(fd);
				break;
			case 2:
				searchCustomer(fd);
				break;
			case 3:
				updateCustomer(fd);
				break;
			case 4:
				deleteCustomer(fd);
				break;
			case 5:
				showCustomer(fd);
				break;
			case 6:
				key = 0;
				break;
			}
		} else {
			printf("잘못 입력\n");
		}
	}
}

void alarmHandler() {
	printf("\n1분간 입력이 없어 종료합니다\n");
	exit(0);
}

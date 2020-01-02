#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include "rent.h"
#include "buffer.h"

void rentBook(int fd) {
	int key = 1, scanCh, inputId, msg;

	showBook(fd);
	while (key) {
		printf("빌릴 책 id: ");
		scanCh = scanf("%d", &inputId);
		clearBuffer();
		if (scanCh == 1) {
			write(fd, &inputId, sizeof(inputId));
			key = 0;
		} else {
			printf("잘못된 입력\n");
		}
	}
	read(fd, &msg, sizeof(msg));
	if (msg == 0) {
		printf("대여 성공!\n");
	} else if (msg == -1) {
		printf("없는 책!\n");
	} else if (msg == 999) {
		printf("대여중인 책!\n");
	}
}

void returnBook(int fd) {
	int key = 1, scanCh, inputId, msg;

	showMyRent(fd);
	while (key) {
		printf("반납할 rentid: ");
		scanCh = scanf("%d", &inputId);
		clearBuffer();
		if (scanCh == 1) {
			write(fd, &inputId, sizeof(inputId));
			key = 0;
		} else {
			printf("잘못된 입력\n");
		}
	}
	read(fd, &msg, sizeof(msg));
	if (msg == 0) {
		printf("반납 성공!\n");
	} else {
		printf("반납 실패!\n");
	}
}
void showMyRent(int fd) {
	RENT record;

	printf("rentid bookid cid        time         ReturnTime\n");
	while (1) {
		read(fd, &record, sizeof(record));
		if (record.id == -1)
			break;
		printf("%4d %6d %6d   %10s %10s\n", record.id, record.bookId,
				record.cusId, record.rentTime, record.returnTime);
	}
}

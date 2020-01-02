#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include "buffer.h"

void inputBook(int fd) {
	BOOK record;
	int key = 1;
	int scanCh;

	while (key) {
		printf("%-2s %-6s %-4s\n", "id", "제목", "가격");
		scanCh = scanf("%d %s %d", &record.id, record.title, &record.price);
		clearBuffer();
		if ((scanCh == 3) && (record.id > 0)) {
			write(fd, &record, sizeof(record));
			key = 0;
		}
	}
}

void searchBook(int fd) {
	BOOK record;
	int id, key = 1, scanCh;

	while (key) {
		printf("검색할 도서 id 입력: ");
		scanCh = scanf("%d", &id);
		clearBuffer();
		if ((scanCh == 1) && (id > 0)) {
			write(fd, &id, sizeof(id));
			read(fd, &record, sizeof(record));
			if (record.id > 0)
				printf("id: %d 제목: %s 가격: %d\n", record.id, record.title,
						record.price);
			else
				printf("id %d 결과 없음\n", id);
			key = 0;
		} else {
			printf("잘못된 입력\n");
		}
	}
}

void updateBook(int fd) {
	BOOK record;
	int id, key = 1, scanCh;

	showBook(fd);
	while (key) {
		printf("수정할 도서 id 입력:");
		scanCh = scanf("%d", &id);
		clearBuffer();
		if ((scanCh == 1) && (id > 0)) {
			write(fd, &id, sizeof(id));
			read(fd, &record, sizeof(record));
			if (record.id > 0) {
				printf("id: %d 제목: %s 가격: %d\n", record.id, record.title,
						record.price);
				printf("새로운 가격 입력: ");
				scanf("%d", &record.price);
				clearBuffer();
				write(fd, &record, sizeof(record));
			} else {
				printf("id %d 없음\n", id);
			}
			key = 0;
		} else {
			printf("잘못된 입력\n");
		}
	}
}

void deleteBook(int fd) {
	int id, key = 1, scanCh;

	showBook(fd);
	while (key) {
		printf("삭제할 도서 id 입력: ");
		scanCh = scanf("%d", &id);
		clearBuffer();
		if ((scanCh == 1) && (id > 0)) {
			write(fd, &id, sizeof(id));
			key = 0;
		} else {
			printf("잘못된 입력\n");
		}
	}
}

void showBook(int fd) {
	BOOK record;

	printf("id  제목    가격\n");
	while (1) {
		read(fd, &record, sizeof(record));
		if (record.id == -1)
			break;
		printf("%-2d %-6s %-4d\n", record.id, record.title, record.price);
	}
}

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"
#include "buffer.h"

void inputCustomer(int fd) {
	CUSTOMER record;
	int key = 1;
	int scanCh;

	while (key) {
		printf("%-2s %-6s %-4s %-6s %2s\n", "id", "이름", "전화번호", "포인트", "비밀번호");
		scanCh = scanf("%d %s %s %d %s", &record.id, record.name, record.phone,
				&record.point, record.password);
		clearBuffer();
		if ((scanCh == 5) && (record.id > 0)) {
			write(fd, &record, sizeof(record));
			key = 0;
		}
	}
}

void searchCustomer(int fd) {
	CUSTOMER record;
	int id, key = 1, scanCh;

	while (key) {
		printf("검색할 고객 id 입력: ");
		scanCh = scanf("%d", &id);
		clearBuffer();
		if ((scanCh == 1) && (id > 0)) {
			write(fd, &id, sizeof(id));
			read(fd, &record, sizeof(record));
			if (record.id > 0)
				printf("id: %d 이름: %s 전화번호: %s 포인트: %d\n", record.id,
						record.name, record.phone, record.point);
			else
				printf("id %d 결과 없음\n", id);
			key = 0;
		} else {
			printf("잘못된 입력\n");
		}
	}
}

void updateCustomer(int fd) {
	CUSTOMER record;
	int id, key = 1, scanCh;

	showCustomer(fd);
	while (key) {
		printf("수정할 고객 id 입력:");
		scanCh = scanf("%d", &id);
		clearBuffer();
		if ((scanCh == 1) && (id > 0)) {
			write(fd, &id, sizeof(id));
			read(fd, &record, sizeof(record));
			if (record.id > 0) {
				printf("id: %d 이름: %s 전화번호: %s 포인트: %d\n", record.id,
						record.name, record.phone, record.point);
				printf("포인트 입력: ");
				scanf("%d", &record.point);
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

void deleteCustomer(int fd) {
	int id, key = 1, scanCh;

	showCustomer(fd);
	while (key) {
		printf("삭제할 고객 id 입력: ");
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

void showCustomer(int fd) {
	CUSTOMER record;

	printf("id  이름    전화번호   포인트\n");
	while (1) {
		read(fd, &record, sizeof(record));
		if (record.id == -1)
			break;
		printf("%-2d %-6s %-4s %2d\n", record.id, record.name, record.phone,
				record.point);
	}
}

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "book.h"
#include "rent.h"

int nowRentId = 0;

void rentBook(int fd, FILE *fp_b, FILE *fp_r, int nowCusId) {
	BOOK bookRecord;
	RENT rentRecord;
	int rentBookId, msg, ch = 1;
	char *tmpTime;

	fseek(fp_r, -sizeof(rentRecord), SEEK_END);
	if (fread(&rentRecord, sizeof(rentRecord), 1, fp_r) > 0) {
		nowRentId = rentRecord.id;
	}

	showBook(fd, fp_b);
	rewind(fp_b);
	read(fd, &rentBookId, sizeof(rentBookId));
	fseek(fp_b, (rentBookId - START_ID) * sizeof(bookRecord), SEEK_SET);
	if ((fread(&bookRecord, sizeof(bookRecord), 1, fp_b) > 0)
			&& (bookRecord.id != 0)) {
		if (bookRecord.rentCnt > 0) {
			bookRecord.rentCnt--;
			fseek(fp_b, -sizeof(bookRecord), SEEK_CUR);
			fwrite(&bookRecord, sizeof(bookRecord), 1, fp_b);
			rentRecord.id = ++nowRentId;
			rentRecord.bookId = rentBookId;
			rentRecord.cusId = nowCusId;
			tmpTime = getTime();
			strcpy(rentRecord.rentTime, tmpTime);
			strcpy(rentRecord.returnTime, "-");
			fseek(fp_r, (rentRecord.id - START_ID) * sizeof(rentRecord),
			SEEK_SET);
			fwrite(&rentRecord, sizeof(rentRecord), 1, fp_r);
			msg = 0;
			write(fd, &msg, sizeof(msg));
		} else {
			msg = 999;
			write(fd, &msg, sizeof(msg));
			ch = 0;
		}
	} else if (ch != 0) {
		msg = -1;
		write(fd, &msg, sizeof(msg));
	}
}

void returnBook(int fd, FILE *fp_b, FILE *fp_r, int nowCusId) {
	RENT returnRecord;
	BOOK bookRecord;
	int returnBookId, msg;

	showMyRent(fd, fp_r, nowCusId);
	rewind(fp_r);
	read(fd, &returnBookId, sizeof(returnBookId));
	fseek(fp_r, (returnBookId - START_ID) * sizeof(returnRecord), SEEK_SET);
	if ((fread(&returnRecord, sizeof(returnRecord), 1, fp_r) > 0)
			&& (returnRecord.cusId == nowCusId)) {
		fseek(fp_b, (returnRecord.bookId - START_ID) * sizeof(bookRecord),
				SEEK_SET);
		fread(&bookRecord, sizeof(bookRecord), 1, fp_b);
		bookRecord.rentCnt++;	// 반납후 수량 증가
		strcpy(returnRecord.returnTime, getTime());
		fseek(fp_r, -sizeof(returnRecord), SEEK_CUR);
		fwrite(&returnRecord, sizeof(returnRecord), 1, fp_r);
		msg = 0;
		write(fd, &msg, sizeof(msg));
	} else {
		msg = -1;
		write(fd, &msg, sizeof(msg));
	}
}
void showMyRent(int fd, FILE *fp_r, int nowCusId) {
	RENT record;
	int readCnt;

	while (1) {
		readCnt = fread(&record, sizeof(record), 1, fp_r);
		if (readCnt > 0) {
			if (nowCusId == record.cusId) {
				write(fd, &record, sizeof(record));
			}
		} else {
			record.id = -1;
			write(fd, &record, sizeof(record));
			break;
		}
	}
}

char* getTime() {
	struct tm *date;
	const time_t t = time(NULL);
	static char timestr[30];

	date = localtime(&t);
	strftime(timestr, sizeof(timestr), "%Y-%m-%d %X", date);
	return timestr;
}

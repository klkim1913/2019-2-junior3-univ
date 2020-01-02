#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

void inputBook(int fd, FILE *fp_b) {
	BOOK record;

	read(fd, &record, sizeof(record));
	record.rentCnt = 1;
	fseek(fp_b, (record.id - START_ID) * sizeof(record), SEEK_SET);
	fwrite(&record, sizeof(record), 1, fp_b);
}

void searchBook(int fd, FILE *fp_b) {
	BOOK record;
	int id;

	read(fd, &id, sizeof(id));
	fseek(fp_b, (id - START_ID) * sizeof(record), SEEK_SET);
	if ((fread(&record, sizeof(record), 1, fp_b) > 0) && (record.id != 0))
		write(fd, &record, sizeof(record));
	else {
		record.id = -1;
		write(fd, &record, sizeof(record));
	}
}

void updateBook(int fd, FILE *fp_b) {
	BOOK record;
	int id;

	showBook(fd, fp_b);
	rewind(fp_b);
	read(fd, &id, sizeof(id));
	fseek(fp_b, (id - START_ID) * sizeof(record), SEEK_SET);
	if ((fread(&record, sizeof(record), 1, fp_b) > 0) && (record.id != 0)) {
		write(fd, &record, sizeof(record));
		read(fd, &record, sizeof(record));
		fseek(fp_b, -sizeof(record), SEEK_CUR);
		fwrite(&record, sizeof(record), 1, fp_b);
	} else {
		record.id = -1;
		write(fd, &record, sizeof(record));
	}
}

void deleteBook(int fd, FILE **fp_b) {
	BOOK record;
	int id;
	FILE *tmpfp;

	showBook(fd, *fp_b);
	rewind(*fp_b);
	tmpfp = fopen("tmp.dat", "wb");
	read(fd, &id, sizeof(id));
	while (fread(&record, sizeof(record), 1, *fp_b) > 0) {
		if (record.id != id) {
			fseek(tmpfp, (record.id - START_ID) * sizeof(record), SEEK_SET);
			fwrite(&record, sizeof(record), 1, tmpfp);
		}
	}
	fclose(*fp_b);
	fclose(tmpfp);
	remove("book.dat");
	rename("tmp.dat", "book.dat");
	*fp_b = fopen("book.dat", "rb+");
}

void showBook(int fd, FILE *fp_b) {
	BOOK record;
	int readCnt;

	while (1) {
		readCnt = fread(&record, sizeof(record), 1, fp_b);
		if (readCnt > 0) {
			if (record.id != 0) {
				write(fd, &record, sizeof(record));
			}
		} else {
			record.id = -1;
			write(fd, &record, sizeof(record));
			break;
		}
	}
}

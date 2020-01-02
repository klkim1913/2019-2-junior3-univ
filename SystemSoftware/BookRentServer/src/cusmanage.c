#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"

void inputCustomer(int fd, FILE *fp_c) {
	CUSTOMER record;

	read(fd, &record, sizeof(record));
	fseek(fp_c, (record.id - START_ID) * sizeof(record), SEEK_SET);
	fwrite(&record, sizeof(record), 1, fp_c);
}

void searchCustomer(int fd, FILE *fp_c) {
	CUSTOMER record;
	int id;

	read(fd, &id, sizeof(id));
	fseek(fp_c, (id - START_ID) * sizeof(record), SEEK_SET);
	if ((fread(&record, sizeof(record), 1, fp_c) > 0) && (record.id != 0))
		write(fd, &record, sizeof(record));
	else {
		record.id = -1;
		write(fd, &record, sizeof(record));
	}
}

void updateCustomer(int fd, FILE *fp_c) {
	CUSTOMER record;
	int id;

	showCustomer(fd, fp_c);
	rewind(fp_c);
	read(fd, &id, sizeof(id));
	fseek(fp_c, (id - START_ID) * sizeof(record), SEEK_SET);
	if ((fread(&record, sizeof(record), 1, fp_c) > 0) && (record.id != 0)) {
		write(fd, &record, sizeof(record));
		read(fd, &record, sizeof(record));
		fseek(fp_c, -sizeof(record), SEEK_CUR);
		fwrite(&record, sizeof(record), 1, fp_c);
	} else {
		record.id = -1;
		write(fd, &record, sizeof(record));
	}
}

void deleteCustomer(int fd, FILE **fp_c) {
	CUSTOMER record;
	int id;
	FILE *tmpfp;

	showCustomer(fd, *fp_c);
	rewind(*fp_c);
	tmpfp = fopen("tmp.dat", "wb");
	read(fd, &id, sizeof(id));
	while (fread(&record, sizeof(record), 1, *fp_c) > 0) {
		if (record.id != id) {
			fseek(tmpfp, (record.id - START_ID) * sizeof(record), SEEK_SET);
			fwrite(&record, sizeof(record), 1, tmpfp);
		}
	}
	fclose(*fp_c);
	fclose(tmpfp);
	remove("customer.dat");
	rename("tmp.dat", "customer.dat");
	*fp_c = fopen("customer.dat", "rb+");
}

void showCustomer(int fd, FILE *fp_c) {
	CUSTOMER record;
	int readCnt;

	while (1) {
		readCnt = fread(&record, sizeof(record), 1, fp_c);
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

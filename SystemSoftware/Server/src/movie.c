#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <signal.h>
#include "movie.h"

void showMovie(int fd, FILE *fp_m) {
	MOVIE record;
	MOVIE sortR[30];
	int readCnt, numR, i, j, ch;
	char data[30];

	numR = 0;
	ch = 0;
	while (1) {
		readCnt = fread(&record, sizeof(record), 1, fp_m);
		if (readCnt > 0) {
			sortR[numR] = record;
			numR++;
			ch = 1;
		} else {
			break;
		}
	}
	if (ch == 1) {
		for (i = 1; i < numR; i++) {
			strcpy(data, sortR[i].date);
			for (j = i - 1; j >= 0; j--) {
				if (strcpy(sortR[j].date, data) > 0) {
					sortR[j + 1] = sortR[j];
				} else {
					break;
				}
				sortR[j + 1] = sortR[i];
			}
		}
		for (i = 0; i < numR; i++) {
			record = sortR[i];
			write(fd, &record, sizeof(record));
		}
	}
	record.id = -1;
	write(fd, &record, sizeof(record));
}

void inputMovie(int fd, FILE *fp_m) {
	MOVIE inputR, searchR;
	int readCnt, key, isSame, msg;

	key = 1;
	isSame = 0;
	while (key) {
		read(fd, &inputR, sizeof(inputR));
		while (1) {
			readCnt = fread(&searchR, sizeof(searchR), 1, fp_m);
			if (readCnt > 0) {
				if ((strcpy(inputR.date, searchR.date) == 0)
						|| inputR.place == searchR.place) {
					isSame = 1;
				}
			} else {
				break;
			}
		}
		if (isSame == 1) {
			msg = -1;
			write(fd, &msg, sizeof(msg));
		} else if (isSame == 0) {
			msg = 0;
			write(fd, &msg, sizeof(msg));
			key = 0;
		}
	}
}

void updateMovie(int fd, FILE *fp_m) {
	MOVIE record;
	int id;

	read(fd, &id, sizeof(id));
	fseek(fp_m, (id - START_ID) * sizeof(record), SEEK_SET);
	if (fread(&record, sizeof(record), 1, fp_m) > 0 && (record.id != 0)) {
		write(fd, &record, sizeof(record));
		read(fd, &record, sizeof(record));
		fseek(fp_m, -sizeof(record, SEEK_CUR));
		fwrite(&record, sizeof(record), 1, fp_m);
	} else {
		record.id = -1;
		write(fd, &record, sizeof(record), sizeof(record));
	}
}

void deleteMovie(int fd, FILE *fp_m) {
	MOVIE record;
	int id;
	FILE *tmpfp;

	tmpfp=fopen("tmp.dat","wb");
	read(fd,&id,sizeof(id));
	while(fread(&record, sizeof(record), 1, fp_m) > 0) {
		if(record.id!=id) {
			fseek(tmpfp,(record.id-START_ID)*sizeof(record),SEEK_SET);
			fwrite(&record, sizeof(record), 1, fp_m);
		}
	}
	fclose(*fp_m);
	fclose(tmpfp);
	remove("movie.dat");
	rename("tmp.dat","movie.dat");
	*fp_m=fopen("movie.dat","rb+");
}

void searchMovie(int fd, FILE *fp_m) {

}

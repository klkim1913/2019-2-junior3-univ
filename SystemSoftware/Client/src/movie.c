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

void showMovie(int fd) {
	MOVIE record;

	printf("번호    상영일시   상영시간   상영관   영화제목   가격   최하시청가능나이\n");
	while (1) {
		read(fd, &record, sizeof(record));
		if (record.id == -1)
			break;
		printf("%d %s %d %d %s %d %d", record.id, record.date, record.runTime,
				record.place, record.title, record.price, record.overAge);
	}
}

void inputMovie(int fd) {
	MOVIE record;
	int msg, key;

	key = 1;
	while (key) {
		printf("번호    상영일시   상영시간   상영관   영화제목   가격   최하시청가능나이\n");
		if (scanf("%d %s %d %d %s %d %d,", &record.id, record.date,
				&record.runTime, &record.place, record.title, &record.price,
				&record.overAge) == 7) {
			write(fd, &record, sizeof(record));
		}
		read(fd, &msg, sizeof(msg));
		if (msg == 0) {
			key = 0;
			printf("성공적 추가\n");
		} else if (msg == -1) {
			printf("상영관,상영시간 겹침 다른거 입력\n");
		}
	}
}

void updateMovie(int fd) {
	MOVIE record;
	int id;

	printf("수정할 영화 번호: ");
	scanf("%d", &id);
	write(fd, &id, sizeof(id));
	read(fd, &record, sizeof(record));
	if (record.id > 0) {
		printf("번호    상영일시   상영시간   상영관   영화제목   가격   최하시청가능나이\n");
		if (scanf("%d %s %d %d %s %d %d,", &record.id, record.date,
				&record.runTime, &record.place, record.title, &record.price,
				&record.overAge) == 7) {
			write(fd, &record, sizeof(record));
		}
	}
	else {
		printf("id %d 없음\n");
	}
}

void deleteMovie(int fd) {

	int id;

	printf("삭제 id: ");
	scanf("%d",&id);
	write(fd,&id,sizeof(id));
}

void searchMovie(int fd) {

}

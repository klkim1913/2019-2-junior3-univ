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
//#include "movieseats.h"

void runClient();
void runHome(int fd);
void runMovie(int fd);
//void runSeats(int fd);

int main() {
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
	int sel,key;

	key=1;
	while (key) {
		printf("1.영화 상영 추가/삭제 관리\n2.영화별 좌석 예매\n3.종료\n");
		printf("선택: ");
		if (scanf("%d", &sel) == 1) {
			write(fd, &sel, sizeof(sel));
			switch (sel) {
			case 1:
				runMovie(fd);
				break;
//			case 2:
//				runSeats(fd);
//				break;
			case 3:
				key=0;
				break;
			}
		}
	}
}

void runMovie(int fd) {
	int sel, key;

	key = 1;
	while (key) {
		printf("1.영화 전체리스트\n2.영화 추가\n3.영화 갱신\n4.영화 삭제\n5.영화제목으로 검색\n");
		printf("선택: ");
		if(scanf("%d",&sel)==1) {
			write(fd,&sel,sizeof(sel));
			switch(sel) {
			case 1:
				showMovie(fd);
				break;
			case 2:
				inputMovie(fd);
				break;
			case 3:
				updateMovie(fd);
				break;
			case 4:
				deleteMovie(fd);
				break;
			case 5:
				searchMovie(fd);
				break;
			case 6:
				key=0;
				break;
			}
		}
	}
}

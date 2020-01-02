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

void runServer();
void runHome(int fd);
void runMovie(int fd, FILE *fp_m);
//void runSeats();

int main() {
	runServer();
	return 0;
}

void runServer() {
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(9734);
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr*) &server_address, server_len);

	listen(server_sockfd, 5);

	signal(SIGCHLD, SIG_IGN);

	while (1) {
		printf("server waiting\n");
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd,
				(struct sockaddr*) &client_address, &client_len);
		printf("client connect\n");
		if (fork() == 0) {
			runHome(client_sockfd);
			close(client_sockfd);
			printf("client_sockfd");
			printf("client disconnect\n");
			break;
		} else {
			close(client_sockfd);
		}
	}
}

void runHome(int fd) {
	int sel, key;
	FILE *fp_m, *fp_s;

	key = 1;
	fp_m = fopen("movie.dat", "rb+");
	if (fp_m == NULL) {
		fp_m = fopen("movie.dat", "wb+");
	}

	fp_s = fopen("movieseats.dat", "rb+");
	if (fp_s == NULL) {
		fp_s = fopen("movieseats.dat", "wb+");
	}

	while (key) {
		rewind(fp_m);
		rewind(fp_s);
		read(fd, &sel, sizeof(sel));
		switch (sel) {
		case 1:
			runMovie(fd, fp_m);
			break;
//		case 2:
//			runSeats(fd, fp_m);
//			break;
		case 3:
			key = 0;
			break;
		}
	}
	fclose(fp_m);
	fclose(fp_s);
}

void runMovie(int fd, FILE *fp_m) {
	int sel, key;

	key = 1;
	while (key) {
		rewind(fp_m);
		read(fd, &sel, sizeof(sel));
		switch (sel) {
		case 1:
			showMovie(fd, fp_m);
			break;
		case 2:
			inputMovie(fd, fp_m);
			break;
		case 3:
			updateMovie(fd, fp_m);
			break;
		case 4:
			deleteMovie(fd, &fp_m);
			break;
		case 5:
			searchMovie(fd, fp_m);
			break;
		case 6:
			key = 0;
			break;
		}
	}
}

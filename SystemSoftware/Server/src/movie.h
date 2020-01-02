#define START_ID 1

typedef struct movie
{
	int id;
	char date[30];
	int runTime;
	int place;
	char title[30];
	int price;
	int overAge;
} MOVIE;

void showMovie(int fd, FILE *fp_m);
void inputMovie(int fd, FILE *fp_m);
void updateMovie(int fd, FILE *fp_m);
void deleteMovie(int fd, FILE *fp_m);
void searchMovie(int fd, FILE *fp_m);

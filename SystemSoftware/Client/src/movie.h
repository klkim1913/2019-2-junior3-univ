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

void showMovie(int fd);
void inputMovie(int fd);
void updateMovie(int fd);
void deleteMovie(int fd);
void searchMovie(int fd);

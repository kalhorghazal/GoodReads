#include "Book.h"
#include "Review.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <pthread.h>
#include <algorithm>

#define NEW_LINE '\n'
#define ZERO 0
#define GENRE 1
#define NUMBER_OF_THREADS 4
#define BOOKS_FILE "books.csv"
#define REVIEWS_FILE "reviews.csv"

using namespace std;

typedef int Book_id;
typedef std::map<Book_id, Book*> _Books;
typedef vector<Book*> Books;
typedef vector<Review*> Reviews;

typedef struct 
{
	int offset;
	int len;
} Thread_data;

enum Book_feature
{
	ID,
	TITLE,
	GENRE_1,
	GENRE_2, 
	PAGES,
	AUTHOR_NAME,
	AUTHOR_AVERAGE_RATING
};

enum Review_feature
{
	BOOK_ID,
	RATING,
	NUMBER_OF_LIKES
};

pthread_t threads[NUMBER_OF_THREADS];
pthread_mutex_t mutex_read_book;
pthread_mutex_t mutex_read_review;
_Books books;
Reviews reviews;
int number_of_book_lines;
int number_of_review_lines;

void get_new_book_info(_Books& books, string line);
Review* get_new_review_info(string line);
void read_csv(_Books& books, string filename);
void read_csv(Reviews& reviews, string filename);
void count_ratings(Reviews reviews, _Books& books, string genre);
void find_best_book(_Books& books, string genre);
int get_number_of_lines(string filename);
void* read_books(void* args);
void* read_reviews(void* args);
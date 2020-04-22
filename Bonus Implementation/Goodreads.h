#include "Book.h"
#include "Review.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <pthread.h>
#include <map>

#define NEW_LINE '\n'
#define ONE 1
#define ZERO 0
#define GENRE 1
#define NUMBER_OF_BOOK_THREADS 4
#define NUMBER_OF_REVIEW_THREADS 6
#define BOOKS_FILE "books.csv"
#define REVIEWS_FILE "reviews.csv"

using namespace std;

typedef int Book_id;
typedef map<Book_id, Book*> Books;
typedef vector<Review*> Reviews;

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

typedef struct 
{
	int start; 
	int length; 
} Read_data;

Books books;
Reviews reviews;
pthread_t book_threads[NUMBER_OF_BOOK_THREADS];
pthread_t review_threads[NUMBER_OF_REVIEW_THREADS];
pthread_mutex_t mutex_read_book;
pthread_mutex_t mutex_read_review;

Review* get_new_review_info(string line);
void get_new_book_info(Books& books, string line);
void count_ratings(Reviews reviews, Books& books, string genre);
void find_best_book(Books& books, string genre);
int get_file_length(string filename);
void* read_books(void* arg);
void* read_reviews(void* arg);
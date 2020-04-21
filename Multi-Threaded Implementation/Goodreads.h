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
#define NUMBER_OF_BOOK_THREADS 4
#define NUMBER_OF_REVIEW_THREADS 6
#define SUFFIX ".csv"
#define BOOKS "Assets/books_"
#define REVIEWS "Assets/reviews_"

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

Books books;
Reviews reviews;
pthread_t book_threads[NUMBER_OF_BOOK_THREADS];
pthread_t review_threads[NUMBER_OF_REVIEW_THREADS];
pthread_mutex_t mutex_read_book;
pthread_mutex_t mutex_read_review;

Review* get_new_review_info(string line);
void get_new_book_info(Books& books, string line);
void read_csv(Books& books, string filename);
void read_csv(Reviews& reviews, string filename);
void count_ratings(Reviews reviews, Books& books, string genre);
void find_best_book(Books& books, string genre);
void* read_books(void* arg);
void* read_reviews(void* arg);
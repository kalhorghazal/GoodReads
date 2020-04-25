#include "Book.h"
#include "Review.h"

#include <map>
#include <omp.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define ZERO 0
#define GENRE 1
#define NEW_LINE '\n'
#define BOOKS_FILE "books.csv"
#define REVIEWS_FILE "reviews.csv"

using namespace std;

typedef int Book_id;
typedef string Genre;
typedef vector<Review*> Reviews;
typedef map<Book_id, Book*> Books;

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
Genre genre;
Reviews reviews;

bool contains_key(int key);
void find_best_book(Books& books);
void read_csv(Books& books, string filename);
void read_csv(Reviews& reviews, string filename);
void count_ratings(Reviews reviews, Books& books);
void extract_new_book_info(Books& books, string line);
void extract_new_review_info(Reviews& reviews, string line);
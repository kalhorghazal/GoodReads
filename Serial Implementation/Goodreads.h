#include "Book.h"
#include "Review.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

#define NEW_LINE '\n'
#define BOOKS "books"
#define REVIEWS "reviews"
#define SUFFIX ".csv"
#define GENRE 1

using namespace std;

typedef vector<Book*> Books;
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

Book* get_new_book_info(string line);
Review* get_new_review_info(string line);
void read_csv(Books& books, string filename);
void read_csv(Reviews& reviews, string filename);
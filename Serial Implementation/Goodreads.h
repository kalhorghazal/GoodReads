#include "Book.h"
#include "Review.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

#define NEW_LINE '\n'
#define BOOKS_FILE "books.csv"
#define REVIEWS_FILE "reviews.csv"
#define GENRE 1
#define BOOK_NOT_FOUND -1

using namespace std;

typedef int Book_id;
typedef std::map<Book_id, Book*> _Books;
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

//Book* get_new_book_info(string line);
void get_new_book_info(_Books& books, string line);
Review* get_new_review_info(string line);
void read_csv(_Books& books, string filename);
void read_csv(Reviews& reviews, string filename);
void count_ratings(Reviews reviews, _Books& books, string genre);
void find_best_book(_Books& books, string genre);
//int find_book_index_by_id(Books books, Book_id id);
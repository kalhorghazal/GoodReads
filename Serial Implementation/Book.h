#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#define SPACE ' '
#define COLON ':'
#define COMMA ','
#define NEW_LINE '\n'
#define TRUE true
#define FALSE false
#define ZERO 0
#define PRECISION 2
#define RATING_RATIO 0.1
#define ID_STR "id"
#define TITLE_STR "Title"
#define GENRES_STR "Genres"
#define AUTHOR_STR "Author"
#define AVERAGE_RATING_STR "Average Rating"
#define NUMBER_OF_PAGES_STR "Number of Pages"

typedef int Book_id;

using namespace std;

class Book
{
public:
	Book(Book_id _id, string _title, string _genre_1, string _genre_2, 
		int _pages, string _author_name, double _author_average_rating);
	Book_id get_id() const { return id; }
    string get_title() const { return title; }
    string get_genre_1() const { return genre_1; }
    string get_genre_2() const { return genre_2; }
    string get_author_name() const { return author_name; }
    int get_pages() const { return pages; }
    double get_average_rating() const { return average_rating; }
    void update_rating(int rating, int number_of_likes);
    void calulate_average_rating();
    bool has_genre(string genre);
private:
	Book_id id; 
	string title;
	string genre_1;
	string genre_2;
	string author_name;
	int pages; 
	int total_number_of_likes;
	double author_average_rating;
	double average_rating; 

	friend ostream& operator<<(ostream&, const Book&);
};
#endif
#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#define NEW_LINE '\n'
#define ZERO 0
#define ONE 1
#define SPACE ' '
#define COLON ':'
#define COMMA ','
#define FALSE false
#define TRUE true
//#define ID "id"
//#define TITLE "Title"
#define GENRES "Genres"
#define NUMBER_OF_PAGES "Number of Pages"
#define AUTHOR "Author"
#define AVERAGE_RATING "Averager Rating"
#define PRECISION 2
#define RATING_COEFFICIENT 1/10

//Type Defines

using namespace std;

class Book
{
public:
	Book(int _id, string _title, string _genre_1, string _genre_2, 
		int _pages, string _author_name, float _author_average_rating);
	int get_id() const { return id; }
    string get_title() const { return title; }
    string get_genre_1() const { return genre_1; }
    string get_genre_2() const { return genre_2; }
    string get_author_name() const { return author_name; }
    int get_pages() const { return pages; }
    float get_average_rating() const { return average_rating; }
    void update_rating(int rating, int number_of_likes);
    void calulate_average_rating();
    bool has_genre(string genre);
private:
	int id; 
	string title;
	string genre_1;
	string genre_2;
	string author_name;
	int pages; 
	float author_average_rating;
	float average_rating; 
	int number_of_reviews;

	friend ostream& operator<<(ostream&, const Book&);
};
#endif
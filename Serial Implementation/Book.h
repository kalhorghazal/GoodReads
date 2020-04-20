#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <vector>

#define NEW_LINE '\n'
#define ZERO 0
#define ONE 1
#define SPACE ' '
#define COLON ':'
#define COMMA ','
#define ID "id"
#define TITLE "Title"
#define GENRES "Genres"
#define NUMBER_OF_PAGES "Number of Pages"
#define AUTHOR "Author"

//Type Defines

using namespace std;

class Book
{
public:
	Book(int _id, string _title, string _genre_1, string _genre_2, 
		string _author_name, int _pages, float _author_average_rating);
	int get_id() const { return id; }
    string get_title() const { return title; }
    string get_genre_1() const { return genre_1; }
    string get_genre_2() const { return genre_2; }
    string get_author_name() const { return author_name; }
    int get_pages() const { return pages; }
private:
	int id; 
	string title;
	string genre_1;
	string genre_2;
	string author_name;
	int pages; 
	float author_average_rating;
	float average_rating; // ????????

	friend ostream& operator<<(ostream&, const Book&);
};
#endif
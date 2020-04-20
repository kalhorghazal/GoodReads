#include "Book.h"

Book::Book(int _id, string _title, string _genre_1, string _genre_2, 
		string _author_name, int _pages, float _author_average_rating)
{
	id = _id; 
	title = _title; 
	genre_1 = _genre_1;  
	genre_2 = _genre_2;
	author_name = _author_name; 
	pages = _pages; 
	author_average_rating = _author_average_rating;
}

ostream& operator<<(ostream& out, const Book& book)
{
    out << ID << COLON << SPACE << book.get_id() << NEWLINE;
    out << TITLE << COLON << SPACE << book.get_title() << NEWLINE;
    out << GENRES << COLON << SPACE << book.get_genre_1() << COMMA 
    	<< SPACE << book.get_genre_2() << NEWLINE;
    out << NUMBER_OF_PAGES << COLON << SPACE << book.get_pages() << NEWLINE;
    out << AUTHOR << COLON << SPACE << book.get_author_name() << NEWLINE;
        
    return out;
}
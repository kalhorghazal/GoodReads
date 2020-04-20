#include "Book.h"

Book::Book(int _id, string _title, string _genre_1, string _genre_2, 
		int _pages, string _author_name, float _author_average_rating)
{
	id = _id; 
	title = _title; 
	genre_1 = _genre_1;  
	genre_2 = _genre_2;
	pages = _pages; 
	author_name = _author_name; 
	author_average_rating = _author_average_rating;
	average_rating = 0;
	total_number_of_likes = 0;
}

void Book::update_rating(int rating, int number_of_likes)
{
	average_rating += (rating * number_of_likes);
	total_number_of_likes += number_of_likes;
}

void Book::calulate_average_rating()
{
	if (total_number_of_likes != ZERO)
		average_rating /= total_number_of_likes;
	else
		average_rating = 0;
	
	average_rating += author_average_rating;
	average_rating *= RATING_RATIO;
}

bool Book::has_genre(string genre)
{
	if (genre == genre_1 || genre == genre_2)
		return TRUE;
	return FALSE;
}

ostream& operator<<(ostream& out, const Book& book)
{
    out << "ID" << COLON << SPACE << book.get_id() << NEW_LINE;
    out << "TITLE" << COLON << SPACE << book.get_title() << NEW_LINE;
    out << GENRES << COLON << SPACE << book.get_genre_1() << COMMA 
    	<< SPACE << book.get_genre_2() << NEW_LINE;
    out << NUMBER_OF_PAGES << COLON << SPACE << book.get_pages() << NEW_LINE;
    out << AUTHOR << COLON << SPACE << book.get_author_name() << NEW_LINE;
    out << AVERAGE_RATING << COLON << SPACE << setprecision(PRECISION) << 
			fixed << book.get_average_rating() << NEW_LINE;
        
    return out;
}
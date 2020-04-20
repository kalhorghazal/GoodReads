#include "Book.h"

Book::Book(Book_id _id, string _title, string _genre_1, string _genre_2, 
		int _pages, string _author_name, double _author_average_rating)
{
	id = _id; 
	title = _title; 
	genre_1 = _genre_1;  
	genre_2 = _genre_2;
	pages = _pages; 
	author_name = _author_name; 
	author_average_rating = _author_average_rating;
	average_rating = ZERO;
	total_number_of_likes = ZERO;
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
		average_rating = ZERO;
	
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
    out << ID_STR << COLON << SPACE << book.get_id() << NEW_LINE;
    out << TITLE_STR << COLON << SPACE << book.get_title() << NEW_LINE;
    out << GENRES_STR << COLON << SPACE << book.get_genre_1() << COMMA 
    	<< SPACE << book.get_genre_2() << NEW_LINE;
    out << NUMBER_OF_PAGES_STR << COLON << SPACE << book.get_pages() << NEW_LINE;
    out << AUTHOR_STR << COLON << SPACE << book.get_author_name() << NEW_LINE;
    out << AVERAGE_RATING_STR << COLON << SPACE << setprecision(PRECISION) << 
			fixed << book.get_average_rating() << NEW_LINE;
        
    return out;
}
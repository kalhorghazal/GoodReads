#include "Goodreads.h"

int main(int argc, char const *argv[])
{
	string genre = argv[GENRE];
	_Books books;
	Reviews reviews;

	read_csv(books, BOOKS_FILE);
	read_csv(reviews, REVIEWS_FILE);

	count_ratings(reviews, books, genre);
	find_best_book(books, genre);

	return 0;
}

void extract_new_book_info(_Books& books, string line)
{
	istringstream templine(line);
	string data;
	vector<string> info;

	while (getline(templine, data, COMMA)){
		info.push_back(data);
	}

	Book *book = new Book(atoi(info[ID].c_str()), info[TITLE], info[GENRE_1], 
		info[GENRE_2], atoi(info[PAGES].c_str()), info[AUTHOR_NAME], 
		atof(info[AUTHOR_AVERAGE_RATING].c_str()));

	books[atoi(info[ID].c_str())] = book;
}

Review* get_new_review_info(string line)
{
	istringstream templine(line);
	string data;
	vector<string> info;

	while (getline(templine, data, COMMA)){
		info.push_back(data);
	}

	Review* review = new Review(atoi(info[BOOK_ID].c_str()), atoi(info[RATING].c_str()), 
		atoi(info[NUMBER_OF_LIKES].c_str()));

	return review;
}

void read_csv(_Books& books, string filename)
{
	ifstream file;
	file.open(filename);
	string line;
	getline(file, line, NEW_LINE);

	while (getline(file, line, NEW_LINE))
		extract_new_book_info(books, line);

	file.close();
}

void read_csv(Reviews& reviews, string filename)
{
	ifstream file;
	file.open(filename);
	string line;
	getline(file, line, NEW_LINE);

	while (getline(file, line, NEW_LINE))
		reviews.push_back(get_new_review_info(line));

	file.close();
}

/*int find_book_index_by_id(Books books, Book_id id)
{
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i]->get_id() == id)
        {
            return i;
        }
    }
    return BOOK_NOT_FOUND;
}*/

void count_ratings(Reviews reviews, _Books& books, string genre)
{
	for (int i = 0; i < reviews.size(); ++i)
	{
		Book_id book_id = reviews[i]->get_book_id();
		if (books[book_id]->has_genre(genre)){
			books[book_id]->update_rating(reviews[i]->get_rating(), 
				reviews[i]->get_number_of_likes());

			
}
	}
}

void find_best_book(_Books& books, string genre)
{
	Book* best;
	float max_rating = 0;
	for (_Books::iterator it = books.begin(); 
		it != books.end(); ++it)
	{
		Book* book = it->second;
		
		if (book->has_genre(genre))
		{
    	 	book->calulate_average_rating();
    	 	if (book->get_average_rating() > max_rating)
    	 	{
    	 		best = book;
    	 		max_rating = book->get_average_rating();
    	 	}
    	 }
	}

	cout << *best;
}
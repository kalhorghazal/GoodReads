#include "Goodreads.h"

int main(int argc, char const *argv[])
{
	string genre = argv[GENRE];
	return 0;
}

Book* get_new_book_info(string line)
{
	istringstream templine(line);
	string data;
	vector<string> info;

	while (getline(templine, data, COMMA)){
		info.push_back(data);
	}

	Book *book = new Book(info[ID], info[TITLE], info[GENRE_1], 
		info[GENRE_2], info[PAGES], info[AUTHOR_NAME], 
		info[AUTHOR_AVERAGE_RATING]);

	return book;
}

Review* get_new_review_info(string line)
{
	istringstream templine(line);
	string data;
	vector<int> info;

	while (getline(templine, data, COMMA)){
		info.push_back(data);
	}

	Review* review = new Review(info[BOOK_ID], info[RATING], 
		info[NUMBER_OF_LIKES]);

	return review;
}

void read_csv(Books& books, string filename)
{
	ifstream file;
	file.open(filename);
	string line;
	getline(file, line, NEW_LINE);

	while (getline(file, line, NEW_LINE))
		books.push_back(get_new_book_info(line));

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
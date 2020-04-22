#include "Goodreads.h"

int main(int argc, char const *argv[])
{
	string genre = argv[GENRE];

	int books_length = get_file_length(BOOKS_FILE);
	int reviews_length = get_file_length(REVIEWS_FILE);

	void *status;

	pthread_mutex_init(&mutex_read_book, NULL);

	for(long i = ZERO; i < NUMBER_OF_BOOK_THREADS; i++)
	{
		Read_data* read_data = new Read_data();
		read_data->start = i*books_length/NUMBER_OF_BOOK_THREADS;
		read_data->length = books_length/NUMBER_OF_BOOK_THREADS;

		if (i == (NUMBER_OF_BOOK_THREADS-1))
			read_data->length += books_length%NUMBER_OF_BOOK_THREADS;

		pthread_create(&book_threads[i], NULL, read_books, (void*)read_data);
	}

	for(long i = ZERO; i < NUMBER_OF_BOOK_THREADS; i++)
		pthread_join(book_threads[i], &status);

	/*pthread_mutex_destroy(&mutex_read_book);

	pthread_mutex_init(&mutex_read_review, NULL);

	for(long i = ZERO; i < NUMBER_OF_REVIEW_THREADS; i++)
		pthread_create(&review_threads[i], NULL, read_reviews, (void*)i);

	for(long i = ZERO; i < NUMBER_OF_REVIEW_THREADS; i++) 
		pthread_join(review_threads[i], &status);

	pthread_mutex_destroy(&mutex_read_review);*/

	//read_csv(books, BOOKS_FILE);
	//read_csv(reviews, REVIEWS_FILE);

	//count_ratings(reviews, books, genre);
	//find_best_book(books, genre);

	//cout << books_length << endl << reviews_length << endl;

	pthread_exit(NULL);
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

	Review* review = new Review(atoi(info[BOOK_ID].c_str()), 
		atoi(info[RATING].c_str()), atoi(info[NUMBER_OF_LIKES].c_str()));

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

void count_ratings(Reviews reviews, _Books& books, string genre)
{
	for (int i = ZERO; i < reviews.size(); ++i)
	{
		Book_id book_id = reviews[i]->get_book_id();

		if (books[book_id]->has_genre(genre))
			books[book_id]->update_rating(reviews[i]->get_rating(), 
				reviews[i]->get_number_of_likes());
	}
}

void find_best_book(_Books& books, string genre)
{
	Book* best;
	double max_rating = ZERO;
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

int get_file_length(string filename)
{
	ifstream file(filename);
	file.seekg(0, file.end);
	int length = file.tellg();

	return length;

}

void* read_books(void* arg)
{
	Read_data* read_data = (Read_data*)arg;

	fstream file(BOOKS_FILE);
	file.seekg(read_data->start, ios::beg); 

	_Books my_books;

	string line;
	getline(file, line, NEW_LINE);

	while (getline(file, line, NEW_LINE))
	{
		extract_new_book_info(my_books, line);
		if (file.tellg() > (read_data->start + read_data->length))
			break;
	}

	pthread_mutex_lock (&mutex_read_book);

	if (books.size() == ZERO)
		books = my_books;
	else
		books.insert(my_books.begin(), my_books.end());

	pthread_mutex_unlock (&mutex_read_book);

	pthread_exit((void*)ZERO);
}
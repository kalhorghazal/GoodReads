#include "Goodreads.h"

int main(int argc, char const *argv[])
{
	string genre = argv[GENRE];

	void *status;

	number_of_book_lines = get_number_of_lines(BOOKS_FILE);

	pthread_mutex_init(&mutex_read_book, NULL);

	for(long i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_create(&threads[i], NULL, read_books, (void*)i);

	for(long i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_join(threads[i], &status);

	pthread_mutex_destroy(&mutex_read_book);

	number_of_review_lines = get_number_of_lines(REVIEWS_FILE);

	pthread_mutex_init(&mutex_read_review, NULL);

	for(long i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_create(&threads[i], NULL, read_reviews, (void*)i);

	for(long i = 0; i < NUMBER_OF_THREADS; i++) 
		pthread_join(threads[i], &status);

	pthread_mutex_destroy(&mutex_read_review);

	//count_ratings(reviews, books, genre);
	find_best_book(books, genre);
	pthread_exit(NULL);
	return ZERO;
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

int get_number_of_lines(string filename)
{
	ifstream file(filename);
	int number_of_lines = count(istreambuf_iterator<char>(file), 
		istreambuf_iterator<char>(), NEW_LINE);

	return number_of_lines;
}

void* read_books(void* arg)
{
	long offset = (long)arg;
	int len = number_of_book_lines / NUMBER_OF_THREADS;
	
	int start = offset * len + 1;
	int end = start + len;

	_Books my_books;

	ifstream file(BOOKS_FILE);

	for (int i = 0; i < start; ++i)
	{
    	file.ignore(numeric_limits<streamsize>::max(), file.widen(NEW_LINE));
	}

	string line;

	for (int i = start; i < end ; i++)
	{
		getline(file, line, NEW_LINE);
		extract_new_book_info(my_books, line);
	}

	pthread_mutex_lock (&mutex_read_book);

	if (books.size() == 0)
		books = my_books;
	else
		books.insert(my_books.begin(), my_books.end());

	pthread_mutex_unlock (&mutex_read_book);

	pthread_exit((void*)0);
}

void* read_reviews(void* arg)
{
	long offset = (long)arg;
	int len = number_of_review_lines / NUMBER_OF_THREADS;

	int start = offset * len + 1;
	int end = start + len;

	Reviews my_reviews;

	ifstream file(REVIEWS_FILE);

	for (int i = 0; i < start; ++i)
	{
    	file.ignore(numeric_limits<streamsize>::max(), file.widen(NEW_LINE));
	}

	string line;

	for (int i = start; i < end ; i++)
	{
		getline(file, line, NEW_LINE);
		my_reviews.push_back(get_new_review_info(line));
	}

	pthread_mutex_lock (&mutex_read_review);

	if (reviews.size() == 0)
		reviews = my_reviews;
	else
		reviews.insert(reviews.end(), my_reviews.begin(), my_reviews.end());

	pthread_mutex_unlock (&mutex_read_review);

	pthread_exit((void*)0);
}
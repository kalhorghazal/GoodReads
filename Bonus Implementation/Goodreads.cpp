#include "Goodreads.h"

int main(int argc, char const *argv[])
{
	genre = argv[GENRE];

	call_book_readers();
	call_review_readers();
	
	count_ratings(reviews, books);
	find_best_book(books);

	pthread_exit(NULL);
}

void call_book_readers()
{
	void *status;

	int books_length = get_file_length(BOOKS_FILE);

	pthread_mutex_init(&mutex_read_book, NULL);

	for(long i = ZERO; i < NUMBER_OF_BOOK_THREADS; i++)
	{
		Read_data* read_data = new Read_data();
		read_data->start = i*books_length/NUMBER_OF_BOOK_THREADS;
		read_data->length = books_length/NUMBER_OF_BOOK_THREADS;

		if (i == (NUMBER_OF_BOOK_THREADS-ONE))
			read_data->length += books_length%NUMBER_OF_BOOK_THREADS;

		pthread_create(&book_threads[i], NULL, read_books, (void*)read_data);
	}

	for(long i = ZERO; i < NUMBER_OF_BOOK_THREADS; i++)
		pthread_join(book_threads[i], &status);

	pthread_mutex_destroy(&mutex_read_book);
}

void call_review_readers()
{
	void *status;

	int reviews_length = get_file_length(REVIEWS_FILE);

	pthread_mutex_init(&mutex_read_review, NULL);

	for(long i = ZERO; i < NUMBER_OF_REVIEW_THREADS; i++)
	{
		Read_data* read_data = new Read_data();
		read_data->start = i*reviews_length/NUMBER_OF_REVIEW_THREADS;
		read_data->length = reviews_length/NUMBER_OF_REVIEW_THREADS;

		if (i == (NUMBER_OF_BOOK_THREADS-ONE))
			read_data->length += reviews_length%NUMBER_OF_REVIEW_THREADS;

		pthread_create(&review_threads[i], NULL, read_reviews, (void*)read_data);
	}

	for(long i = ZERO; i < NUMBER_OF_REVIEW_THREADS; i++) 
		pthread_join(review_threads[i], &status);

	pthread_mutex_destroy(&mutex_read_review);
}

void extract_new_book_info(Books& books, string line)
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

	if (book->has_genre(genre))
		books[atoi(info[ID].c_str())] = book;
}

void extract_new_review_info(Reviews& reviews, string line)
{
	istringstream templine(line);
	string data;
	vector<string> info;

	while (getline(templine, data, COMMA)){
		info.push_back(data);
	}

	Review* review = new Review(atoi(info[BOOK_ID].c_str()), 
		atoi(info[RATING].c_str()), atoi(info[NUMBER_OF_LIKES].c_str()));

	if (contains_key(atoi(info[BOOK_ID].c_str())))
		reviews.push_back(review);
}

void count_ratings(Reviews reviews, Books& books)
{
    #pragma omp parallel for 
	for (int i = ZERO; i < reviews.size(); ++i)
	{
		Book_id book_id = reviews[i]->get_book_id();

		books[book_id]->update_rating(reviews[i]->get_rating(), 
			reviews[i]->get_number_of_likes());
	}
}

void find_best_book(Books& books)
{
	Book* best;
	double max_rating = ZERO;
	
	#pragma omp parallel for 
	for (Books::iterator it = books.begin(); 
		it != books.end(); ++it)
	{
		Book* book = it->second;		
    	book->calulate_average_rating();

    	if (book->get_average_rating() > max_rating)
    	{
    		best = book;
    	 	max_rating = book->get_average_rating();
    	}
	}

	cout << *best;
}

int get_file_length(string filename)
{
	ifstream file(filename);
	file.seekg(ZERO, file.end);
	int length = file.tellg();

	return length;

}

bool contains_key(int key)
{
	if (books.find(key) != books.end())
		return TRUE;

	return FALSE;
}

void* read_books(void* arg)
{
	Read_data* read_data = (Read_data*)arg;

	fstream file(BOOKS_FILE);
	file.seekg(read_data->start, ios::beg); 

	Books my_books;

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

void* read_reviews(void* arg)
{
	Read_data* read_data = (Read_data*)arg;

	fstream file(REVIEWS_FILE);
	file.seekg(read_data->start, ios::beg); 

	Reviews my_reviews;

	string line;
	getline(file, line, NEW_LINE);

	while (getline(file, line, NEW_LINE))
	{
		extract_new_review_info(my_reviews, line);
		if (file.tellg() > (read_data->start + read_data->length))
			break;
	}

	pthread_mutex_lock (&mutex_read_review);

	if (reviews.size() == ZERO)
		reviews = my_reviews;
	else
		reviews.insert(reviews.end(), my_reviews.begin(), my_reviews.end());

	pthread_mutex_unlock (&mutex_read_review);

	pthread_exit((void*)ZERO);
}
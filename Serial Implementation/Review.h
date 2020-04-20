#ifndef REVIEW_H
#define REVIEW_H

#include <iostream>
#include <string>
#include <vector>

#define SPACE ' '
#define ONE 1
#define ZERO 0

typedef int Book_id;

using namespace std;

class Review
{
public:
	Review(int _book_id, int _rating, int _number_of_likes);
	Book_id get_book_id() const { return book_id; }
    int get_rating() const { return rating; }
    int get_number_of_likes() const { return number_of_likes; }
private:
	Book_id book_id; 
	int rating;
	int number_of_likes;
};
#endif
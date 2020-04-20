#ifndef REVIEW_H
#define REVIEW_H

#include <iostream>
#include <string>
#include <vector>

#define ZERO 0
#define ONE 1
#define SPACE ' '

//Type Defines

using namespace std;

class Review
{
public:
	Review(int _book_id, int _rating, int _number_of_likes);
	int get_book_id() const { return book_id; }
    int get_rating() const { return rating; }
    int get_number_of_likes() const { return number_of_likes; }
private:
	int book_id; 
	int rating;
	int number_of_likes;
};
#endif
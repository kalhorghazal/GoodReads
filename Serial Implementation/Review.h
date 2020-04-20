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
private:
	int book_id; 
	int rating;
	int number_of_likes;
};
#endif
COMPILER = g++
COMPILER_FLAGS = --std=c++11
LINK_FLAGS = -I $(INCLUDE_DIR) -I $(INLINE_DIR) -pthread
all : Goodreads.out

Goodreads.out: Goodreads.o Book.o Review.o
	${COMPILER} ${COMPILER_FLAGS} $(LINK_FLAGS) Goodreads.o Book.o Review.o -o Goodreads.out

Goodreads.o: Goodreads.cpp Goodreads.h Book.h Review.h
	${COMPILER} ${COMPILER_FLAGS} -c Goodreads.cpp -o Goodreads.o

Book.o: Book.cpp Book.h
	${COMPILER} ${COMPILER_FLAGS} -c Book.cpp -o Book.o

Review.o: Review.cpp Review.h
	${COMPILER} ${COMPILER_FLAGS} -c Review.cpp -o Review.o
	
rm:
	rm -rf *.out 
/*
 * Auditorium.h
 *
 *  Created on: Oct 1, 2020
 *      Author: xxdin
 */

#ifndef AUDITORIUM_H_
#define AUDITORIUM_H_
#include "Node.h"
#include "Seat.h"
#include<iostream>
using namespace std;
class Auditorium   : public Node<Seat>{
public:
	Auditorium(string filename, int rows, int cols);
	~Auditorium();

	Node<Seat>* getFirst(){return first;};
	void setFirst(Node<Seat> *&f){this->first = f;};

private:
	Node<Seat> *first;
	int numRows;
	int numCols;
};

#endif /* AUDITORIUM_H_ */

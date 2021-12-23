/*
 * Auditorium.cpp
 *
 *  Created on: Oct 1, 2020
 *      Author: xxdin
 */

#include "Auditorium.h"
#include "Node.h"
#include "Seat.h"
#include <fstream>
//This is where the linked list is created.
Auditorium::Auditorium(string filename, int rowNum, int colNum) {
	//This will be where the first node is initialized
	first = new Node<Seat>;
	numRows = rowNum;
	numCols = colNum;
	//These will help assign payload values.
	char seatAssigner = 'A';
	char ticketAssigner;
	//This will be the tail of the program in which the tail will be moved accordingly
	Node<Seat> *tail = new Node<Seat>;
	//this pointer will help keep track of the above nodes
	Node<Seat> *rowAbove = new Node<Seat>;
	//this will keep track of the above node head of the row.
	Node<Seat> *rowHeadAbove = new Node<Seat>;
	//this will be used to create the nodes
	Node<Seat> *temp;
	//infile is used to read values from the file.
	ifstream infile;
	infile.open(filename);
	if (infile) {
		//This is the loop that will create the linked list.
		for (int i = 0; i < rowNum; i++) {
			//Each for loop represents the rows and columns respectively.
			for (int j = 0; j < colNum; j++) {
				if (i == 0) {
					//This represents the first row.
					if (j == 0) {
						//This is where the start of the linked list is made.
						infile >> ticketAssigner;
						//This is the part that helps increment the seat assigner char to be the proper value. This is used in each row.
						seatAssigner = 'A';
						for (int i = 0; i < j; i++) {
							seatAssigner++;
						}
						Seat *s = new Seat(i + 1, seatAssigner, ticketAssigner);
						first->setUp(nullptr);
						first->setDown(nullptr);
						first->setLeft(nullptr);
						first->setRight(nullptr);
						first->setSeatObj(s);
						tail = first;
					} else if (j == colNum - 1) {
						//This is where the end of a row is signified, where the above node pointers will be given their values.
						infile >> ticketAssigner;
						seatAssigner = 'A';
						for (int i = 0; i < j; i++) {
							seatAssigner++;
						}
						Seat *s = new Seat(i + 1, seatAssigner, ticketAssigner);
						temp = new Node<Seat>;
						temp->setUp(nullptr);
						temp->setDown(nullptr);
						temp->setLeft(tail);
						temp->setRight(nullptr);
						temp->setSeatObj(s);
						tail->setRight(temp);
						tail = temp;
						rowAbove = first;
						rowHeadAbove = first;
						//This is where the rest of the row is created in the first row.
					} else {
						infile >> ticketAssigner;
						seatAssigner = 'A';
						for (int i = 0; i < j; i++) {
							seatAssigner++;
						}
						Seat *s = new Seat(i + 1, seatAssigner, ticketAssigner);
						temp = new Node<Seat>;
						temp->setUp(nullptr);
						temp->setDown(nullptr);
						temp->setLeft(tail);
						temp->setRight(nullptr);
						temp->setSeatObj(s);
						tail->setRight(temp);
						tail = temp;

					}
					//This is the instruction for the last row
				} else if (i == rowNum - 1) {
					if (j == 0) {
						infile >> ticketAssigner;
						seatAssigner = 'A';
						for (int i = 0; i < j; i++) {
							seatAssigner++;
						}
						Seat *s = new Seat(i + 1, seatAssigner, ticketAssigner);
						temp = new Node<Seat>;
						temp->setUp(rowAbove);
						temp->setDown(nullptr);
						temp->setLeft(nullptr);
						temp->setRight(nullptr);
						temp->setSeatObj(s);
						rowHeadAbove->setDown(temp);
						tail = temp;
						rowHeadAbove = temp;
						rowAbove = rowAbove->getRight();
					} else if (j == colNum - 1) {
						infile >> ticketAssigner;
						seatAssigner = 'A';
						for (int i = 0; i < j; i++) {
							seatAssigner++;
						}
						Seat *s = new Seat(i + 1, seatAssigner, ticketAssigner);
						temp = new Node<Seat>;
						temp->setUp(rowAbove);
						temp->setDown(nullptr);
						temp->setLeft(tail);
						temp->setRight(nullptr);
						temp->setSeatObj(s);
						tail->setRight(temp);
						tail = temp;
						rowAbove->setDown(temp);
						rowAbove = rowHeadAbove;
					} else {
						infile >> ticketAssigner;
						seatAssigner = 'A';
						for (int i = 0; i < j; i++) {
							seatAssigner++;
						}
						Seat *s = new Seat(i + 1, seatAssigner, ticketAssigner);
						temp = new Node<Seat>;
						temp->setUp(rowAbove);
						temp->setDown(nullptr);
						temp->setLeft(tail);
						temp->setRight(nullptr);
						temp->setSeatObj(s);
						tail->setRight(temp);
						tail = temp;
						rowAbove->setDown(temp);
						rowAbove = rowAbove->getRight();

					}
					//This is the instruction for every other row.
				} else {
					if (j == 0) {
						infile >> ticketAssigner;
						seatAssigner = 'A';
						for (int i = 0; i < j; i++) {
							seatAssigner++;
						}
						Seat *s = new Seat(i + 1, seatAssigner, ticketAssigner);
						temp = new Node<Seat>;
						temp->setUp(rowAbove);
						temp->setDown(nullptr);
						temp->setLeft(nullptr);
						temp->setRight(nullptr);
						temp->setSeatObj(s);
						rowHeadAbove->setDown(temp);
						tail = temp;
						//The above head is moved down the the current row head after it is used .
						rowHeadAbove = temp;
						rowAbove = rowAbove->getRight();
					} else if (j == colNum - 1) {
						infile >> ticketAssigner;
						seatAssigner = 'A';
						for (int i = 0; i < j; i++) {
							seatAssigner++;
						}
						Seat *s = new Seat(i + 1, seatAssigner, ticketAssigner);
						temp = new Node<Seat>;
						temp->setUp(rowAbove);
						temp->setDown(nullptr);
						temp->setLeft(tail);
						temp->setRight(nullptr);
						temp->setSeatObj(s);
						tail->setRight(temp);
						tail = temp;
						rowAbove->setDown(temp);
						rowAbove = rowHeadAbove;
					} else {
						infile >> ticketAssigner;
						seatAssigner = 'A';
						for (int i = 0; i < j; i++) {
							seatAssigner++;
						}
						Seat *s = new Seat(i + 1, seatAssigner, ticketAssigner);
						temp = new Node<Seat>;
						temp->setUp(rowAbove);
						temp->setDown(nullptr);
						temp->setLeft(tail);
						temp->setRight(nullptr);
						temp->setSeatObj(s);
						tail->setRight(temp);
						tail = temp;
						//YOu can see here how the above row point is used and incrimented along the row to help set the up and down values.
						rowAbove->setDown(temp);
						rowAbove = rowAbove->getRight();

					}

				}

			}
		}
	}

}
//This is the auditorium deleter, which frees all allocated memory.
//This destructor traverses the 2d array and deletes each node.
Auditorium::~Auditorium() {
	// TODO Auto-generated destructor stub
	Node<Seat> *head = first;
	Node<Seat> *deleter = new Node<Seat>;
	for(int r = 0;r < numRows; r++ ){
				for(int c = 0; c < numCols; c++){
					deleter = head;


					if(c < numCols-1){
					head = head->getRight();
					delete deleter;
					}
				}

				for(int c = 0; c < numCols-1; c++){
					if(r < numRows-1 && c == 0){
									head = head->getDown();
									}
					head = head->getLeft();
				}


			}

}


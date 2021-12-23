/*
 * Seat.h
 *
 *  Created on: Oct 1, 2020
 *      Author: xxdin
 */

#ifndef SEAT_H_
#define SEAT_H_
class Seat {
public:
	Seat();
	~Seat();
	Seat(int r, char st, char tt){row=r;seat=st;ticketType=tt;};

	int getRow(){return row;};
	void setRow(int r){this->row = r;};

	char getSeat(){return seat;};
	void setSeat(char st){this->seat = st;};

	char getTicketType(){return ticketType;};
	void setTicketType(char tt){this->ticketType = tt;};


protected:
	int row;
	char seat;
	char ticketType;


};

#endif /* SEAT_H_ */

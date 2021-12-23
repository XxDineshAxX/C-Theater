//============================================================================
// Name        : Main.cpp
// Author      : Dinesh Angadipeta DXA@190032
// Description : Project Zero for CS 2337
//============================================================================

//Importing necessary tools and repositories These essentially allow certain variables and functions to exist in this code.
#include "Seat.h"
#include "Node.h"
#include "Auditorium.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
//This struct will hold the orders, which will be held in a vector in the customer struct.
struct Order {
	int auditorium;
	vector<string> seats;
	int adult;
	int child;
	int senior;
};
//This struct will represent each user, and hold orders in a vector, and a password.
struct Customer {
	string password;
	vector<Order> orders;

};
//This will be used to sort the seat vector.
bool compareStr(string a, string b) {
	return a < b;
}
//This will be used in the View Orders menu selection.
void viewOrders(Customer user) {
	cout << endl;
	//This holds the orders to print.
	vector<Order> hold = user.orders;
	if (hold.size() == 0) {
		cout << "No orders" << endl;
	} else {
		//This loops through each order, printing them out in the proper format.
		for (unsigned int i = 0; i < hold.size(); i++) {
			Order orderHolder = hold.at(i);
			vector<string> seatHold = orderHolder.seats;
			sort(seatHold.begin(), seatHold.end(), compareStr);
			cout << "Auditorium " << orderHolder.auditorium << ", ";
			for (unsigned int j = 0; j < seatHold.size(); j++) {
				if (j == 0) {
					cout << seatHold.at(j);
				} else {
					cout << "," << seatHold.at(j);
				}
			}
			cout << endl;
			cout << orderHolder.adult << " adult, " << orderHolder.child
					<< " child, " << orderHolder.senior << " senior" << endl;
			cout << endl;
		}
	}
}
//This helps print out the receipt
void receiptPrint(Customer user) {
	vector<Order> hold = user.orders;
	double total;
	//This loops through each order, printing them out in the proper format.
	for (unsigned int i = 0; i < hold.size(); i++) {
		double aCount;
		double cCount;
		double sCount;
		double currSales;
		Order orderHolder = hold.at(i);
		vector<string> seatHold = orderHolder.seats;
		cout << "Auditorium " << orderHolder.auditorium << ", ";
		for (unsigned int j = 0; j < seatHold.size(); j++) {
			if (j == 0) {
				cout << seatHold.at(j);
			} else {
				cout << "," << seatHold.at(j);
			}
		}
		cout << endl;
		cout << orderHolder.adult << " adult, " << orderHolder.child
				<< " child, " << orderHolder.senior << " senior" << endl;
		aCount = orderHolder.adult * 10.00;
		cCount = orderHolder.child * 5.00;
		sCount = orderHolder.senior * 7.50;
		currSales = aCount + cCount + sCount;
		//This keeps track of the total sales
		total = total + currSales;
		cout << "Order Total: $" << fixed << setprecision(2) << currSales
				<< endl;
		cout << endl;
	}
	//This is the end of the receipt
	cout << "Customer Total: $" << fixed << setprecision(2) << total << endl;
}

//This function helps calculate the next best available seats if the one's the user requested weren't available.
Seat bestAvailable(Node<Seat> *head, int rN, int cN, int total) {
	//This var helps check if the seats checked were empty
	int empty = 0;
	int var;
	//This var is set as 1000 so the first distance value calculated will  be smaller, as it is read in.
	double distance = 1000.0;
	//This var holds the starting seat number.
	int strtSeat = -1;
	char seatLet = 'A';
	//Loops through the row, checking if there are other seats available consecutively.
	Seat startingSeat;
	Seat holderSeat;
	int rowCheck = 0;
	double midRow = (double) (rN + 1) / 2;
	double midCol = (double) (cN + 1) / 2;
	double currRow;
	double prevRow;
	for (int r = 0; r < rN; r++) {
		for (int i = 1; i <= cN - total + 1; i++) {
			for (int j = 0; j < total; j++) {
				holderSeat = head->getSeatObj();
				if (holderSeat.getTicketType() != '.') {
					empty = 1;
					var = j;
					break;
				} else {
					empty = 0;
				}
				if (j < total - 1) {
					head = head->getRight();
				}
				var = j;
			}
			for (int t = 0; t < var; t++) {
				head = head->getLeft();
			}
			if (i < cN - total + 1) {
				head = head->getRight();
			}
			if (empty == 0) {
//Calculates the smallest possible distance value, which in hand will return the smallest seat.
				if (distance
						> (double) sqrt(
								pow(
										midCol
												- ((double) i
														+ (((double) (total
																+ 1.0) / 2.0)
																- 1.0)), 2)
										+ pow(midRow - (r + 1), 2))) {
					distance = 0;
					distance = (double) sqrt(
							pow(
									midCol
											- ((double) i
													+ (((double) (total + 1.0)
															/ 2.0) - 1.0)), 2)
									+ pow(midRow - (r + 1), 2));
					strtSeat = i;
					rowCheck = r + 1;

				}
				if (distance
						== (double) sqrt(
								pow(
										midCol
												- ((double) i
														+ (((double) (total
																+ 1.0) / 2.0)
																- 1.0)), 2)
										+ pow(midRow - (r + 1), 2))) {
					currRow = abs(midRow - (r + 1));
					prevRow = abs(midRow - (rowCheck));
					if (currRow < prevRow) {
						rowCheck = r + 1;
						strtSeat = i;
					} else if (currRow == prevRow) {
						if (r + 1 < rowCheck) {
							rowCheck = r + 1;
							strtSeat = i;
						}
					}

				}

			}

		}
		//This helps set the nod pointer in its proper place.
		for (int c = 0; c < cN - total; c++) {
			head = head->getLeft();
		}

		if (r < rN - 1) {
			head = head->getDown();
		}
	}
	//This block of the method creates a seat object to store both the row and seat value of the best available seats.
	if (strtSeat == -1) {
		seatLet = ' ';
	} else {
		for (int l = 0; l < strtSeat - 1; l++) {
			seatLet++;
		}
	}
	startingSeat.setRow(rowCheck);
	startingSeat.setSeat(seatLet);
	return startingSeat;
}
//This method returns a visual representation of the auditorium for the user to be able to choose their seats.
void displayAudit(Node<Seat> *head, int rN, int cN) {
	//These 2 variables help show the lab'es of each row and column
	char letter = 'A';
	int counter = 0;
	Seat holderSeat;
	//This loop helps loop through the letter variable until it loops for the amount that is equal to the number of Columns.
	while (letter <= 'Z' && counter < cN) {
		if (letter == 'A') {
			//This helps print the initial space to line up the letters with the auditorium columns.
			cout << "  " << letter;
			++letter;
			counter++;
		} else {
			//Each time this loop loops, the letter is incremented up one, going in alphabetical order.
			cout << letter;
			++letter;
			counter++;
		}

	}
	cout << endl;
	//This helps print out each of the chars in the auditorium array, and also helps put a label on each row.
	for (int r = 0; r < rN; r++) {
		cout << r + 1 << " ";
		for (int c = 0; c < cN; c++) {
			holderSeat = head->getSeatObj();
			if (holderSeat.getTicketType() == '.') {
				cout << ".";
			} else {
				cout << "#";
			}
			if (c < cN - 1) {
				head = head->getRight();
			}
		}
		for (int c = 0; c < cN - 1; c++) {
			head = head->getLeft();
		}
		cout << endl;
		if (r < rN - 1) {
			head = head->getDown();
		}
	}
}
//This method checks if the seats requested are possible to book and returns a boolean value based on that information.
bool checkAvailable(Node<Seat> *head, int r, int s, int total) {
	Seat holderSeat;
	for (int j = 0; j < r; j++) {
		head = head->getDown();
	}
	for (int k = 0; k < s; k++) {
		head = head->getRight();
	}
	for (int i = 1; i <= total; i++) {
		holderSeat = head->getSeatObj();
		if (holderSeat.getTicketType() == '.') {
			if (i < total) {
				head = head->getRight();
			}
		} else {
			return false;
		}
	}
	return true;
}
//This helps delete the seat
char deleteTicket(Node<Seat> *head, int r, int s) {
	Seat holderSeat;
	char holderCh;
	//These loops brings the node over to the seat being deleted
	for (int j = 0; j < r; j++) {
		head = head->getDown();
	}
	for (int k = 0; k < s; k++) {
		head = head->getRight();
	}
	//The seat is set as available here.
	holderSeat = head->getSeatObj();
	holderCh = holderSeat.getTicketType();
	holderSeat.setTicketType('.');
	head->setSeatObj(&holderSeat);
	return holderCh;
}

//This method reserves the seats the user requests. This method is mainly effective if used after the implementation of the checkAvailable() method
void reserveSeats(Node<Seat> *head, int r, int s, int aNum, int sNum,
		int cNum) {
	//These loops change the respective seat to the respective ticket requested.
	Seat holderSeat;
	for (int j = 0; j < r; j++) {
		head = head->getDown();
	}
	for (int k = 0; k < s; k++) {
		head = head->getRight();
	}
	for (int i = 0; i < aNum; i++) {
		holderSeat = head->getSeatObj();
		holderSeat.setTicketType('A');
		head->setSeatObj(&holderSeat);
		head = head->getRight();
	}
	for (int j = 0; j < cNum; j++) {
		holderSeat = head->getSeatObj();
		holderSeat.setTicketType('C');
		head->setSeatObj(&holderSeat);
		head = head->getRight();
	}
	for (int k = 0; k < sNum; k++) {
		holderSeat = head->getSeatObj();
		holderSeat.setTicketType('S');
		head->setSeatObj(&holderSeat);
		head = head->getRight();
	}
}
//This method displays a report at the end of the ticket reservations, showing the user what they have requested and information on the rest of the auditorium.
void displayReport(Node<Seat> *head, int rN, int cN) {
	//Each of these vars are used in the final part of the report. The Counter helps increment the double up for each of the tickets for the final price. the Sold keeps track of how many tickets are sold.
	int seats = 0;
	double totalSales = 0.0;
	int aSold = 0;
	double aCounter = 0.0;
	int cSold = 0;
	double cCounter = 0.0;
	int sSold = 0;
	double sCounter = 0.0;
	Seat holderSeat;
	//This system of loops scans each letter of the 2D array, and increments the variable that is supposed to be incremented based on what is in the slot scanned.
	for (int i = 0; i < rN; i++) {
		for (int j = 0; j < cN; j++) {
			holderSeat = head->getSeatObj();
			//These loops increment the report for each ticket based on the scanned value from the 2D array at the points scanned.
			seats++;
			if (holderSeat.getTicketType() == 'A') {
				aSold++;
				aCounter++;
			} else if (holderSeat.getTicketType() == 'C') {
				cSold++;
				cCounter++;
			} else if (holderSeat.getTicketType() == 'S') {
				sSold++;
				sCounter++;
			}
			if (j < cN - 1) {
				head = head->getRight();
			}

		}
		for (int c = 0; c < cN - 1; c++) {
			head = head->getLeft();
		}

		if (i < rN - 1) {
			head = head->getDown();
		}
	}
	//This is where the final report is printed out.
	aCounter = aCounter * 10.00;
	cCounter = cCounter * 5.00;
	sCounter = sCounter * 7.50;
	totalSales = aCounter + cCounter + sCounter;
	//This is where the report is printed to the console
	cout << "Total Seats:	" << seats << endl;
	cout << "Total Tickets:	" << aSold + cSold + sSold << endl;
	cout << "Adult Tickets:	" << aSold << endl;
	cout << "Child Tickets:  " << cSold << endl;
	cout << "Senior Tickets: " << sSold << endl;
	cout << "Total Sales:	$" << fixed << setprecision(2) << totalSales << endl;
}
//This method pushes the array into a file
void pushFile(Node<Seat> *head, int rN, int cN, int audNum) {
	//This is where the out put file stream is initialized, which allows me to push out the 2D array to the external file.
	ofstream outfile;
	Seat holderSeat;
	if (outfile) {
		//A#Final.txt is the file being outputted to
		if (audNum == 1) {
			outfile.open("A1Final.txt");
		} else if (audNum == 2) {
			outfile.open("A2Final.txt");
		} else if (audNum == 3) {
			outfile.open("A3Final.txt");
		}
		for (int r = 0; r < rN; r++) {
			for (int c = 0; c < cN; c++) {
				holderSeat = head->getSeatObj();

				outfile << holderSeat.getTicketType();
				if (c < cN - 1) {
					head = head->getRight();
				}
			}
			outfile << "\n";
			for (int c = 0; c < cN - 1; c++) {
				head = head->getLeft();
			}

			if (r < rN - 1) {
				head = head->getDown();
			}
		}
		//Closing the file
		outfile.close();
	}
}
//This method helps to check if an inputed string can be validated and turned into an int.
bool isValid(string s) {
	for (int i = 0; (unsigned) i < s.length(); i++) {
		if (isdigit(s[i]) == false || s.at(i) == '.') {
			return false;

		}
	}
	return true;
}
int main() {
	unordered_map<string, Customer> users;
//This var helps validate each input
	int validate = 0;
//This var holds the row number value inputed
	int row = -1;
	string rowStr;
//This var holds the seat letter input
	string seatLet = "a";
	char seatCh = 'A';
//This var holds the converted seat letter input which is converted into the index of the column
	int seat;
//This var holds the total amount of tickets wanted, calculated in the end.
	int amount;
//This var assists in the conversion of the char to int.
	char charConvert;
//These vars helps with displaying the best available seats.
	char bestSeatLet2 = 'A';
//This char is the Y/N for the best available seats.
	string chooseBest;
	char chooseBestCh;
//File input stream initialized.
	ifstream infile;
//These hold each of the type of tickets
	int adult = -1;
	string adultStr;
	int child = -1;
	string childStr;
	int senior = -1;
	string seniorStr;
//This holds the file name
	string filename;
//This is used to calculate the number of col
	string holder;
//These will hold the number of rows and columns for each of the auditoriums
	int rowNum1 = 0;
	int colNum1 = 0;

	int rowNum2 = 0;
	int colNum2 = 0;

	int rowNum3 = 0;
	int colNum3 = 0;

	int numUsers = 0;
	//These hold the username and password
	string userName;
	string password;
	//This will hold the var of the user of the program at the time.
	Customer theaterUser;
	//This is where auditorium 1 is initialized.
	while (validate == 0) {
		infile.open("A1.txt");
		//This gets the number of columns
		if (infile) {
			validate = 1;
			infile.ignore(26, '\n');
			getline(infile, holder);
			colNum1 = (int) holder.length();

			infile.close();
			//This loop right here establishes the size of the auditorium file and checks if they are within the boundaries.
			infile.open("A1.txt");
			if (infile) {
				while (getline(infile, holder)) {
					rowNum1++;

				}

				if (rowNum1 > 10 || colNum1 > 26) {
					cout << endl;
					cout
							<< "Auditorium 1 file entered is invalid. Please try again.";
					cout << endl;
					validate = 0;
				}
			}
		} else {
			cout << endl;
			cout << "Auditorium 1 file entered is invalid. Please try again.";
			cout << endl;
			validate = 0;
		}
		infile.close();
	}
	validate = 0;
	cout << endl;
	Auditorium aud1 = Auditorium("A1.txt", rowNum1, colNum1);
	//This is where auditorium 2 is initialized.
	while (validate == 0) {
		infile.open("A2.txt");
		//This gets the number of columns
		if (infile) {
			validate = 1;
			infile.ignore(26, '\n');
			getline(infile, holder);
			colNum2 = (int) holder.length();

			infile.close();
			//This loop right here establishes the size of the auditorium file and checks if they are within the boundaries.
			infile.open("A2.txt");
			if (infile) {
				while (getline(infile, holder)) {
					rowNum2++;

				}

				if (rowNum2 > 10 || colNum2 > 26) {
					cout << endl;
					cout
							<< "Auditorium 2 file entered is invalid. Please try again.";
					cout << endl;
					validate = 0;
				}
			}
		} else {
			cout << endl;
			cout << "Auditorium 2 file entered is invalid. Please try again.";
			cout << endl;
			validate = 0;
		}
		infile.close();
	}
	validate = 0;
	cout << endl;
	Auditorium aud2 = Auditorium("A2.txt", rowNum2, colNum2);
	//This is where auditorium 3 is initialized.
	while (validate == 0) {
		infile.open("A3.txt");
		//This gets the number of columns
		if (infile) {
			validate = 1;
			infile.ignore(26, '\n');
			getline(infile, holder);
			colNum3 = (int) holder.length();

			infile.close();
			//This loop right here establishes the size of the auditorium file and checks if they are within the boundaries.
			infile.open("A3.txt");
			if (infile) {
				while (getline(infile, holder)) {
					rowNum3++;

				}

				if (rowNum3 > 10 || colNum3 > 26) {
					cout << endl;
					cout
							<< "Auditorium 3 file entered is invalid. Please try again.";
					cout << endl;
					validate = 0;
				}
			}
		} else {
			cout << endl;
			cout << "Auditorium 3 file entered is invalid. Please try again.";
			cout << endl;
			validate = 0;
		}
		infile.close();
	}
	validate = 0;
	cout << endl;
	Auditorium aud3 = Auditorium("A3.txt", rowNum3, colNum3);

	infile.open("userdb.dat");
	if (infile) {

		while (getline(infile, holder)) {
			numUsers++;
			stringstream line(holder);
			getline(line, userName, ' ');
			getline(line, password, ' ');
			Customer *c = new Customer;
			c->password = password;
			users[userName] = *c;

		}

	}
	infile.close();
	string introLoop;
	string mainLoop;
	string menuChoice = "0";
	int passValid = 0;
	do {
		//This is where the login sequence starts.
		while (introLoop != "2") {
			passValid = 0;
			cout << "--------------------------------------------------"
					<< endl;
			cout << "Login" << endl;
			cout << "--------------------------------------------------"
					<< endl;
			cout << "Enter Username: ";
			cin >> userName;
			cout << endl;
			//This loop helps the user have 3 attempts at the password
			while (passValid != 3) {
				theaterUser = users[userName];
				cout << "Enter Password: ";
				cin >> password;
				cout << endl;
				//validation of the password
				if (theaterUser.password != password) {
					cout << "Invalid password";
					cout << endl;
					cout << "Try Again.";
					cout << endl;
					passValid++;
				} else {
					introLoop = "2";
					passValid = 3;
				}

			}
		}
		//Admin menu
		if (userName == "admin") {
			cout << "--------------------------------------------------"
					<< endl;
			cout << "Admin Menu" << endl;
			cout << "--------------------------------------------------"
					<< endl;
			cout << "1. Print Report" << endl;
			cout << "2. Logout" << endl;
			cout << "3. Exit" << endl;
			cin >> menuChoice;
			//validation
			if (menuChoice != "1" && menuChoice != "2" && menuChoice != "3"
					&& menuChoice != "4" && menuChoice != "5") {
				cout << "Invalid Entry, Please Try Again." << endl;
				//This is where report was printed
			} else if (menuChoice == "1") {
				Auditorium *aud;
				int rowNum = 0;
				int colNum = 0;
				int seatsAccum = 0;
				int soldAccum = 0;
				int aSoldAccum = 0;
				int cSoldAccum = 0;
				int sSoldAccum = 0;
				double totalAccum = 0.0;
				for (int l = 1; l <= 3; l++) {
					//This is where the auditorium is passed by reference for each value of the for loop
					if (l == 1) {
						aud = &aud1;
						rowNum = rowNum1;
						colNum = colNum1;
					} else if (l == 2) {
						aud = &aud2;
						rowNum = rowNum2;
						colNum = colNum2;
					} else if (l == 3) {
						aud = &aud3;
						rowNum = rowNum3;
						colNum = colNum3;
					}

					int seats = 0;
					double totalSales = 0;
					int aSold = 0;
					double aCounter = 0;
					int cSold = 0;
					double cCounter = 0;
					int sSold = 0;
					double sCounter = 0;
					Seat holderSeat;
					Node<Seat> *head = aud->getFirst();
					//This system of loops scans each letter of the 2D array, and increments the variable that is supposed to be incremented based on what is in the slot scanned.
					for (int i = 0; i < rowNum; i++) {
						for (int j = 0; j < colNum; j++) {

							holderSeat = head->getSeatObj();
							//These loops increment the report for each ticket based on the scanned value from the 2D array at the points scanned.
							seats++;
							if (holderSeat.getTicketType() == 'A') {
								aSold++;
								aCounter++;
							} else if (holderSeat.getTicketType() == 'C') {
								cSold++;
								cCounter++;
							} else if (holderSeat.getTicketType() == 'S') {
								sSold++;
								sCounter++;
							}
							if (j < colNum - 1) {
								head = head->getRight();
							}

						}
						for (int c = 0; c < colNum - 1; c++) {
							head = head->getLeft();
						}

						if (i < rowNum - 1) {
							head = head->getDown();
						}
					}
					//This is where the final report is printed out.
					aCounter = aCounter * 10.00;
					cCounter = cCounter * 5.00;
					sCounter = sCounter * 7.50;
					totalSales = aCounter + cCounter + sCounter;
					//This is where the report is printed to the console
					cout << "Auditorium " << l;
					cout << "	" << seats - (aSold + cSold + sSold);
					cout << "	" << aSold + cSold + sSold;
					cout << "	" << aSold;
					cout << "	" << cSold;
					cout << "	" << sSold;
					cout << "	$" << fixed << setprecision(2) << totalSales
							<< endl;

					//The values for the final part of the report is incremented
					seatsAccum += (seats - (aSold + cSold + sSold));
					soldAccum += (aSold + cSold + sSold);
					aSoldAccum = aSoldAccum + aSold;
					cSoldAccum = cSoldAccum + cSold;
					sSoldAccum = sSoldAccum + sSold;
					totalAccum = totalAccum + totalSales;

				}
				//This is where the accumulated values are printed
				cout << "Total";
				cout << "		" << seatsAccum;
				cout << "	" << soldAccum;
				cout << "	" << aSoldAccum;
				cout << "	" << cSoldAccum;
				cout << "	" << sSoldAccum;
				cout << "	$" << fixed << setprecision(2) << totalAccum << endl;
				//This is where the logout is processed, setting the while loops for the program to activate.
			} else if (menuChoice == "2") {
				introLoop = "0";
				passValid = 0;
				//This values exits the program
			} else if (menuChoice == "3") {
				introLoop = "12";
			}

		} else {
			//This is the main menu of the user program
			cout << "--------------------------------------------------"
					<< endl;
			cout << "Main Menu" << endl;
			cout << "--------------------------------------------------"
					<< endl;
			cout << "1. Reserve Seats" << endl;
			cout << "2. View Orders" << endl;
			cout << "3. Update Order" << endl;
			cout << "4. Display Receipt" << endl;
			cout << "5. Log Out" << endl;
			cin >> menuChoice;
			//validation
			if (menuChoice != "1" && menuChoice != "2" && menuChoice != "3"
					&& menuChoice != "4" && menuChoice != "5") {
				cout << "Invalid Entry, Please Try Again." << endl;
				//This is where the reserve seats is called, which goes through the project 2 program.
			} else if (menuChoice == "1") {
				string audChoice;
				//This auditorium pointer points to the auditorium chosen
				Auditorium *aud;
				Order *o = new Order;
				int rowNum = 0;
				int colNum = 0;
				//This is where the user picks the auditorium.
				cout << "--------------------------------------------------"
						<< endl;
				cout << "Choose an Auditorium." << endl;
				cout << "--------------------------------------------------"
						<< endl;
				cout << "1. Auditorium 1" << endl;
				cout << "2. Auditorium 2" << endl;
				cout << "3. Auditorium 3" << endl;
				while (audChoice != "1" && audChoice != "2" && audChoice != "3") {

					cin >> audChoice;
					if (audChoice != "1" && audChoice != "2"
							&& audChoice != "3") {
						cout << "Invalid Entry, Please Try Again." << endl;
					} else if (audChoice == "1") {
						aud = &aud1;
						rowNum = rowNum1;
						colNum = colNum1;
					} else if (audChoice == "2") {
						aud = &aud2;
						rowNum = rowNum2;
						colNum = colNum2;
					} else if (audChoice == "3") {
						aud = &aud3;
						rowNum = rowNum3;
						colNum = colNum3;
					}
				}

				string orderSeats;
				string orderSeatsHelper;
				vector<string> orderSeatsHolder;
				char orderSeatsHelperCh;
				displayAudit(aud->getFirst(), rowNum, colNum);
				cout << "Enter desired row number: ";
				while (validate == 0) {
					cin >> rowStr;
					if (isValid(rowStr) == true) {
						row = stoi(rowStr);
					} else {
						cout << endl;
						cout << "Invalid row number, please try again";
						cout << endl;
					}

					if (row != -1) {
						if (row > rowNum || row < 1) {
							cout << endl;
							cout << "Invalid row number, please try again";
							cout << endl;

						} else {
							orderSeats = rowStr;
							validate = 1;
						}
					}
				}
				row = row - 1;
				cout << endl;
				//This is the start of the input requests
				validate = 0;
				cout << "Enter desired starting seat letter: ";
				while (validate == 0) {
					cin >> seatLet;
					if (seatLet.length() > 1) {
						cout << endl;
						cout << "Invalid seat letter, please try again";
						cout << endl;
					} else {
						seatCh = seatLet[0];
					}
					//This turns the char into an int to be put into the methods required.
					if (seatLet.length() == 1) {
						seatCh = (char) toupper(seatCh);
						charConvert = 'A';
						seat = 0;
						int counter = 0;
						while (counter != 1) {
							if (seatCh == charConvert) {
								counter = 1;
							} else {
								charConvert++;
								seat++;
							}
						}
						if (seat > colNum || colNum < 1) {
							cout << endl;
							cout << "Invalid seat letter, please try again";
							cout << endl;
						} else {
							validate = 1;
							orderSeats = orderSeats + seatCh;
						}
					}
				}
				cout << endl;
				validate = 0;
				cout << "Enter desired number of Adult Tickets: ";
				while (validate == 0) {
					cin >> adultStr;
					if (isValid(adultStr) == true) {
						adult = stoi(adultStr);
					} else {
						cout << endl;
						cout
								<< "Invalid number of Adult Tickets, please try again";
						cout << endl;
					}

					if (adult != -1) {
						if (adult < 0) {
							cout << endl;
							cout
									<< "Invalid number of Adult Tickets, please try again";
							cout << endl;

						} else {
							validate = 1;
						}
					}
				}
				cout << endl;
				validate = 0;
				cout << "Enter desired number of Child Tickets: ";
				while (validate == 0) {
					cin >> childStr;
					if (isValid(childStr) == true) {
						child = stoi(childStr);
					} else {
						cout << endl;
						cout
								<< "Invalid number of Child Tickets, please try again";
						cout << endl;
					}

					if (child != -1) {
						if (child < 0) {
							cout << endl;
							cout
									<< "Invalid number of Child Tickets, please try again";
							cout << endl;

						} else {
							validate = 1;
						}
					}
				}
				cout << endl;
				validate = 0;
				cout << "Enter desired number of Senior Tickets: ";
				while (validate == 0) {
					cin >> seniorStr;
					if (isValid(seniorStr) == true) {
						senior = stoi(seniorStr);
					} else {
						cout << endl;
						cout
								<< "Invalid number of Senior Tickets, please try again";
						cout << endl;
					}

					if (senior != -1) {
						if (senior < 0) {
							cout << endl;
							cout
									<< "Invalid number of Senior Tickets, please try again";
							cout << endl;

						} else {
							validate = 1;
						}
					}
				}

				//amount var gets its value here
				validate = 0;
				amount = adult + child + senior;

				//This is where most methods are called.
				cout << endl;
				if (checkAvailable(aud->getFirst(), row, seat, amount)) {
					reserveSeats(aud->getFirst(), row, seat, adult, senior,
							child);
					displayReport(aud->getFirst(), rowNum, colNum);
					pushFile(aud->getFirst(), rowNum, colNum, stoi(audChoice));
					orderSeatsHolder.push_back(orderSeats);
					//This is where the order object is fully created to be added to the user's order vector.
					for (int l = 1; l < amount; l++) {
						orderSeatsHelperCh = (char) (seatCh + l);
						orderSeatsHelper = rowStr;
						orderSeatsHelper += orderSeatsHelperCh;
						orderSeatsHolder.push_back(orderSeatsHelper);
					}
					o->auditorium = stoi(audChoice);
					o->adult = adult;
					o->child = child;
					o->senior = senior;
					o->seats = orderSeatsHolder;
					//appended to user's order vector here.
					theaterUser.orders.push_back(*o);

				}
				//This else statement is where the best available seats are requested
				else {
					//		cout << "no seats available." << endl;
					Seat bestChecker = bestAvailable(aud->getFirst(), rowNum,
							colNum, amount);
					bestSeatLet2 = 'A';
					if (bestChecker.getSeat() != ' ') {
						cout
								<< "No seats available at requested spots. Would you like to book the next best available seats?[Y/N]"
								<< endl;
						//This loop calculates the first best letter.
						orderSeats = to_string(bestChecker.getRow());
						orderSeats += bestChecker.getSeat();
						orderSeatsHolder.push_back(orderSeats);
						bestSeatLet2 = bestChecker.getSeat();
						for (int q = 0; q < amount - 1; q++) {
							bestSeatLet2++;
							orderSeatsHelperCh = bestSeatLet2;
							orderSeatsHelper = to_string(bestChecker.getRow());
							orderSeatsHelper += orderSeatsHelperCh;
							orderSeatsHolder.push_back(orderSeatsHelper);
						}
						cout << bestChecker.getRow() << bestChecker.getSeat()
								<< " - " << bestChecker.getRow() << bestSeatLet2
								<< endl;
						while (validate == 0) {
							cin >> chooseBest;
							if (chooseBest.length() > 1) {
								cout << endl;
								cout << "Invalid input, please try again";
								cout << endl;
							} else {
								chooseBestCh = chooseBest[0];
							}
							//This turns the char into an int to be put into the methods required.
							if (chooseBest.length() == 1) {
								chooseBestCh = (char) toupper(chooseBestCh);
								if (chooseBestCh != 'Y'
										&& chooseBestCh != 'N') {
									cout << endl;
									cout << "Invalid input, please try again";
									cout << endl;
								} else {
									validate = 1;
								}
							}
						}
						validate = 0;
						//Reserves the best seats available seats
						if (chooseBestCh == 'Y') {
							reserveSeats(aud->getFirst(),
									bestChecker.getRow() - 1,
									(int) bestChecker.getSeat() - 65, adult,
									senior, child);
							displayReport(aud->getFirst(), rowNum, colNum);
							pushFile(aud->getFirst(), rowNum, colNum,
									stoi(audChoice));
							o->auditorium = stoi(audChoice);
							o->adult = adult;
							o->child = child;
							o->senior = senior;
							o->seats = orderSeatsHolder;

							theaterUser.orders.push_back(*o);
						}
					}
					//If the bestAvailable function returns to -1, that means there are no seats available.
					else {
						cout << "no seats available." << endl;

					}

				}

				//This displays a report at the end of the loop when the user exits.
				//This is where the orders are porinted out.
			} else if (menuChoice == "2") {
				viewOrders(theaterUser);
				//This is where the orders are updated
			} else if (menuChoice == "3") {
				unsigned int orderSelected = 0;
				string orderSelectedStr;
				string selection;
				int rebound1 = 0;
				int rebound2 = 0;
				//Checks if there are orders
				if (theaterUser.orders.size() == 0) {
					rebound1 = 1;
					rebound2 = 1;
					cout << "No orders" << endl;
				}
				//This is where the user chooses an order.
				//This loop also helps to loop the program back if an incorrect value in inputted.
				while (rebound2 == 0) {
					cout << "Select an Order to Update." << endl;
					for (unsigned int i = 0; i < theaterUser.orders.size();
							i++) {
						//Prints out the orders here for the user to choose.
						cout << "Order " << i + 1 << ": Auditorium "
								<< theaterUser.orders.at(i).auditorium
								<< ", Seats: ";
						sort(theaterUser.orders.at(i).seats.begin(),
								theaterUser.orders.at(i).seats.end(),
								compareStr);
						for (unsigned int k = 0;
								k < theaterUser.orders.at(i).seats.size();
								k++) {
							if (k == 0) {
								cout << theaterUser.orders.at(i).seats.at(k);
							} else {
								cout << ","
										<< theaterUser.orders.at(i).seats.at(k);
							}

						}
						cout << endl;
					}
					//validation of the choice
					while (validate == 0) {
						cin >> orderSelectedStr;
						if (isValid(orderSelectedStr) == true) {
							orderSelected = stoi(orderSelectedStr);
						} else {
							cout << endl;
							cout << "Invalid entry, please try again";
							cout << endl;
						}

						if (orderSelected != 0) {
							if (orderSelected > theaterUser.orders.size()
									|| orderSelected < 1) {
								cout << endl;
								cout << "Invalid entry, please try again";
								cout << endl;

							} else {
								validate = 1;
							}
						}
					}
					validate = 0;
					int audChoice =
							theaterUser.orders.at(orderSelected - 1).auditorium;
					Auditorium *aud;
					int rowNum = 0;
					int colNum = 0;
					//sets the proper auditorium here
					if (audChoice == 1) {
						aud = &aud1;
						rowNum = rowNum1;
						colNum = colNum1;
					} else if (audChoice == 2) {
						aud = &aud2;
						rowNum = rowNum2;
						colNum = colNum2;
					} else if (audChoice == 3) {
						aud = &aud3;
						rowNum = rowNum3;
						colNum = colNum3;
					}
					//This is where the order update menu is printed
					//THis loop is used to loop back to this menu if a wrong input is put in.
					while (rebound1 == 0) {
						cout
								<< "--------------------------------------------------"
								<< endl;
						cout << "How Do You Want To Update Order "
								<< orderSelected << endl;
						cout
								<< "--------------------------------------------------"
								<< endl;
						cout << "1. Add tickets to order" << endl;
						cout << "2. Delete tickets from order" << endl;
						cout << "3. Cancel Order" << endl;
						//validation
						while (validate == 0) {
							cin >> selection;
							if (selection != "1" && selection != "2"
									&& selection != "3") {
								cout << "Invalid Entry, Please Try Again."
										<< endl;
							} else {
								validate = 1;
							}
						}
						validate = 0;
						//Goes through reservation process, using same order object.
						if (selection == "1") {
							rebound2 = 1;
							string orderSeats;
							string orderSeatsHelper;
							vector<string> orderSeatsHolder;
							char orderSeatsHelperCh;
							displayAudit(aud->getFirst(), rowNum, colNum);
							cout << "Enter desired row number: ";
							while (validate == 0) {
								cin >> rowStr;
								if (isValid(rowStr) == true) {
									row = stoi(rowStr);
								} else {
									cout << endl;
									cout
											<< "Invalid row number, please try again";
									cout << endl;
								}

								if (row != -1) {
									if (row > rowNum || row < 1) {
										cout << endl;
										cout
												<< "Invalid row number, please try again";
										cout << endl;

									} else {
										orderSeats = rowStr;
										validate = 1;
									}
								}
							}
							row = row - 1;
							cout << endl;
							//This is the start of the input requests
							validate = 0;
							cout << "Enter desired starting seat letter: ";
							while (validate == 0) {
								cin >> seatLet;
								if (seatLet.length() > 1) {
									cout << endl;
									cout
											<< "Invalid seat letter, please try again";
									cout << endl;
								} else {
									seatCh = seatLet[0];
								}
								//This turns the char into an int to be put into the methods required.
								if (seatLet.length() == 1) {
									seatCh = (char) toupper(seatCh);
									charConvert = 'A';
									seat = 0;
									int counter = 0;
									while (counter != 1) {
										if (seatCh == charConvert) {
											counter = 1;
										} else {
											charConvert++;
											seat++;
										}
									}
									if (seat > colNum || colNum < 1) {
										cout << endl;
										cout
												<< "Invalid seat letter, please try again";
										cout << endl;
									} else {
										validate = 1;
										orderSeats = orderSeats + seatCh;
									}
								}
							}
							cout << endl;
							validate = 0;
							cout << "Enter desired number of Adult Tickets: ";
							while (validate == 0) {
								cin >> adultStr;
								if (isValid(adultStr) == true) {
									adult = stoi(adultStr);
								} else {
									cout << endl;
									cout
											<< "Invalid number of Adult Tickets, please try again";
									cout << endl;
								}

								if (adult != -1) {
									if (adult < 0) {
										cout << endl;
										cout
												<< "Invalid number of Adult Tickets, please try again";
										cout << endl;

									} else {
										validate = 1;
									}
								}
							}
							cout << endl;
							validate = 0;
							cout << "Enter desired number of Child Tickets: ";
							while (validate == 0) {
								cin >> childStr;
								if (isValid(childStr) == true) {
									child = stoi(childStr);
								} else {
									cout << endl;
									cout
											<< "Invalid number of Child Tickets, please try again";
									cout << endl;
								}

								if (child != -1) {
									if (child < 0) {
										cout << endl;
										cout
												<< "Invalid number of Child Tickets, please try again";
										cout << endl;

									} else {
										validate = 1;
									}
								}
							}
							cout << endl;
							validate = 0;
							cout << "Enter desired number of Senior Tickets: ";
							while (validate == 0) {
								cin >> seniorStr;
								if (isValid(seniorStr) == true) {
									senior = stoi(seniorStr);
								} else {
									cout << endl;
									cout
											<< "Invalid number of Senior Tickets, please try again";
									cout << endl;
								}

								if (senior != -1) {
									if (senior < 0) {
										cout << endl;
										cout
												<< "Invalid number of Senior Tickets, please try again";
										cout << endl;

									} else {
										validate = 1;
									}
								}
							}

							//amount var gets its value here
							validate = 0;
							amount = adult + child + senior;

							//This is where most methods are called.
							cout << endl;
							if (checkAvailable(aud->getFirst(), row, seat,
									amount)) {
								reserveSeats(aud->getFirst(), row, seat, adult,
										senior, child);
								displayReport(aud->getFirst(), rowNum, colNum);
								pushFile(aud->getFirst(), rowNum, colNum,
										audChoice);
								orderSeatsHolder.push_back(orderSeats);
								for (int l = 1; l < amount; l++) {
									orderSeatsHelperCh = (char) (seatCh + l);
									orderSeatsHelper = rowStr;
									orderSeatsHelper += orderSeatsHelperCh;
									orderSeatsHolder.push_back(
											orderSeatsHelper);
								}
								theaterUser.orders.at(orderSelected - 1).adult +=
										adult;
								theaterUser.orders.at(orderSelected - 1).child +=
										child;
								theaterUser.orders.at(orderSelected - 1).senior +=
										senior;
								theaterUser.orders.at(orderSelected - 1).seats.insert(
										theaterUser.orders.at(orderSelected - 1).seats.end(),
										orderSeatsHolder.begin(),
										orderSeatsHolder.end());
								rebound1 = 1;

							}
							//This else statement is where the best available seats are requested
							else {
								cout << "no seats available." << endl;

							}
							//This is where the user deletes a seat.
						} else if (selection == "2") {
							string rowDelStr;
							int rowDel = -1;
							string seatDelLet = "a";
							char seatDelCh = 'A';
							int seatDel = -1;
							rebound1 = 1;
							//Prints out seats
							cout << "Seats:";
							sort(
									theaterUser.orders.at(orderSelected - 1).seats.begin(),
									theaterUser.orders.at(orderSelected - 1).seats.end(),
									compareStr);
							for (unsigned int k = 0;
									k
											< theaterUser.orders.at(
													orderSelected - 1).seats.size();
									k++) {
								if (k == 0) {
									cout
											<< theaterUser.orders.at(
													orderSelected - 1).seats.at(
													k);
								} else {
									cout << ","
											<< theaterUser.orders.at(
													orderSelected - 1).seats.at(
													k);
								}

							}
							cout << endl;
							cout
									<< "Enter the Row Number of the Seat being deleted: ";
							cin >> rowDelStr;
							cout << endl;
							cout
									<< "Enter the Seat Letter of the Seat being deleted: ";
							cin >> seatDelLet;
							cout << endl;
							//The validation of the choices essentially use the same validation logic from project 2 with a twist.
							if (isValid(rowDelStr) == true) {
								rowDel = 0; //stoi(rowDelStr);
							} else {
								cout << endl;
								cout << "Invalid row number.";
								cout << endl;
							}

							if (rowDel != -1) {
								for (unsigned int k = 0;
										k
												< theaterUser.orders.at(
														orderSelected - 1).seats.size();
										k++) {
									if (theaterUser.orders.at(orderSelected - 1).seats.at(
											k).at(0) == rowDelStr.at(0)) {
										rowDel = stoi(rowDelStr);
									}

								}
								if (rowDel == 0) {
									cout << endl;
									cout << "Invalid row number.";
									cout << endl;

								} else {
									if (seatDelLet.length() > 1) {
										cout << endl;
										cout << "Invalid seat letter.";
										cout << endl;
									} else {
										seatDelCh = seatDelLet[0];

									}
									//This turns the char into an int to be put into the methods required.
									if (seatDelLet.length() == 1) {
										seatDelCh = (char) toupper(seatDelCh);
										charConvert = 'A';
										seatDel = 0;
										int counter = 0;
										while (counter != 1) {
											if (seatDelCh == charConvert) {
												counter = 1;
											} else {
												charConvert++;
												seatDel++;
											}
										}
										unsigned int sizeHolder = unsigned (theaterUser.orders.at(
												orderSelected - 1).seats.size());
										for (unsigned int k = 0; k < sizeHolder; k++) {
											//This is where the inputs are validated to see if there exists a seat in the order with the values.
											if (theaterUser.orders.at(
													orderSelected - 1).seats.at(
													k).at(1) == seatDelCh
													&& theaterUser.orders.at(
															orderSelected - 1).seats.at(
															k).at(0)
															== rowDelStr.at(
																	0)) {
												counter = 10;
												theaterUser.orders.at(
														orderSelected - 1).seats.erase(
														theaterUser.orders.at(
																orderSelected
																		- 1).seats.begin()
																+ (k));
												sizeHolder--;

											}

										}
										//This checks if the values are validated.
										if (counter != 10) {
											cout << endl;
											cout << "Invalid seat letter.";
											cout << endl;
										} else {
											//This is where the seat is finally deleted.
											rowDel = rowDel - 1;
											cout << endl;
											cout << "Seat Deleted.";
											cout << endl;
											//Sets the while loop condition to false to break out of it
											rebound2 = 1;
											char ticketDel = deleteTicket(
													aud->getFirst(), rowDel,
													seatDel);
											ticketDel = (char) toupper(
													ticketDel);
											//This is where the proper ticket number value is decremented based on the value taken from the deleteTicket function.
											if (ticketDel == 'A') {
												theaterUser.orders.at(
														orderSelected - 1).adult =
														theaterUser.orders.at(
																orderSelected
																		- 1).adult
																- 1;
											} else if (ticketDel == 'C') {
												theaterUser.orders.at(
														orderSelected - 1).child =
														theaterUser.orders.at(
																orderSelected
																		- 1).child
																- 1;
											} else if (ticketDel == 'S') {
												theaterUser.orders.at(
														orderSelected - 1).senior =
														theaterUser.orders.at(
																orderSelected
																		- 1).senior
																- 1;
											}
											//Checks if after the seat is removed the order is empty, if so, it deletes the order completely.
											if (theaterUser.orders.at(
													orderSelected - 1).seats.empty()) {
												theaterUser.orders.erase(
														theaterUser.orders.begin()
																+ (orderSelected
																		- 1));
											}

										}
									}

								}
							}
//This is where an order is completely deleted.
						} else if (selection == "3") {
							rebound1 = 1;
							rebound2 = 1;
							string seat_deleted;
							//vector is sorted
							sort(
									theaterUser.orders.at(orderSelected - 1).seats.begin(),
									theaterUser.orders.at(orderSelected - 1).seats.end(),
									compareStr);
							unsigned int sizeHolder = unsigned (theaterUser.orders.at(
									orderSelected - 1).seats.size());
							//This is where all the seats are deleted.
							for (unsigned int k = 0; k < sizeHolder; k++) {
								seat_deleted = theaterUser.orders.at(
										orderSelected - 1).seats.at(k);
								int rDel = seat_deleted[0] - '0';
								rDel = rDel - 1;
								char sDelCh = (char) toupper(seat_deleted[1]);
								charConvert = 'A';
								int sDel = 0;
								int counter = 0;
								while (counter != 1) {
									if (sDelCh == charConvert) {
										counter = 1;
									} else {
										charConvert++;
										sDel++;
									}
								}
								//This is where each of the tickets are deleted
								deleteTicket(aud->getFirst(), rDel, sDel);

							}
							theaterUser.orders.erase(
									theaterUser.orders.begin()
											+ (orderSelected - 1));
							cout << "Order Deleted." << endl;

						}
					}
				}
//This is where the receipt is printed out by calling its method.
			} else if (menuChoice == "4") {
				receiptPrint(theaterUser);
				//This is where the user logs out to go back to the login menu.
			} else if (menuChoice == "5") {
				//Sets loop condition to tru to go back into the login sequence.
				introLoop = "0";
				passValid = 0;
				//Sets the user in hashmap to its updated self.
				users[userName] = theaterUser;

			}
		}
		//This loop is used to exit the program.
	} while (introLoop != "12");

//Standard return statement in c++ which symbolizes the end of the file.
	return 0;
}


////============================================================================
//// Name        : Main.cpp
//// Author      : Dinesh Angadipeta DXA@190032
//// Description : Project Zero for CS 2337
////============================================================================
//
////Importing necessary tools and repositories These essentially allow certain variables and functions to exist in this code.
//#include "Seat.h"
//#include "Node.h"
//#include "Auditorium.h"
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <iomanip>
//#include <math.h>
//using namespace std;
//
////This function helps calculate the next best available seats if the one's the user requested weren't available.
//Seat bestAvailable(Node<Seat> *head, int rN,int cN, int total){
//	//This var helps check if the seats checked were empty
//	int empty = 0;
//	int var;
//	//This var is set as 1000 so the first distance value calculated will  be smaller, as it is read in.
//	double distance =1000.0;
//	//This var holds the starting seat number.
//	int strtSeat=-1;
//	char seatLet = 'A';
//	//Loops through the row, checking if there are other seats available consecutively.
//	Seat startingSeat;
//	Seat holderSeat;
//	int rowCheck = 0;
//	double midRow = (double)(rN+1)/2;
//	double midCol = (double)(cN+1)/2;
//	double currRow;
//	double prevRow;
//	for(int r = 0; r < rN; r++){
//	for(int i = 1; i <= cN-total+1; i++){
//		for(int j = 0; j < total; j++){
//			holderSeat = head->getSeatObj();
//			if(holderSeat.getTicketType() != '.'){
//				empty = 1;
//				var = j;
//				break;
//			}
//			else{
//				empty = 0;
//			}
//			if(j < total-1){
//			head = head->getRight();
//			}
//			var = j;
//		}
//		for(int t = 0; t < var; t++){
//			head = head->getLeft();
//		}
//		if(i < cN-total+1){
//		 head = head->getRight();
//		}
//		if(empty == 0){
////Calculates the smallest possible distance value, which in hand will return the smallest seat.
//			if(distance > (double)sqrt(pow(midCol - ((double)i+(((double)(total+1.0)/2.0)-1.0)), 2) +
//	                pow(midRow - (r+1), 2) )){
//				distance =0;
//				distance = (double)sqrt(pow(midCol - ((double)i+(((double)(total+1.0)/2.0)-1.0)), 2) +
//		                pow(midRow - (r+1), 2) );
//				strtSeat = i;
//				rowCheck = r+1;
//
//			}
//			if(distance == (double)sqrt(pow(midCol - ((double)i+(((double)(total+1.0)/2.0)-1.0)), 2) +
//	                pow(midRow - (r+1), 2) )){
//				currRow = abs(midRow - (r+1));
//				prevRow = abs(midRow - (rowCheck));
//			if(currRow < prevRow){
//				rowCheck = r+1;
//				strtSeat = i;
//			}
//			else if(currRow == prevRow){
//				if(r+1 < rowCheck){
//				rowCheck = r+1;
//				strtSeat = i;
//				}
//			}
//
//			}
//
//
//		}
//
//	}
//	//This helps set the nod pointer in its proper place.
//	for(int c = 0; c < cN-total; c++){
//				head = head->getLeft();
//			}
//
//			if(r < rN-1){
//			head = head->getDown();
//			}
//}
//	//This block of the method creates a seat object to store both the row and seat value of the best available seats.
//	if(strtSeat == -1){
//		seatLet = ' ';
//	}
//	else{
//	for(int l = 0; l < strtSeat-1; l++){
//		seatLet++;
//	}
//	}
//	startingSeat.setRow(rowCheck);
//	startingSeat.setSeat(seatLet);
//	return startingSeat;
//}
////This method returns a visual representation of the auditorium for the user to be able to choose their seats.
//void displayAudit(Node<Seat> *head, int rN, int cN){
//	//These 2 variables help show the lab'es of each row and column
//	char letter = 'A';
//	int counter = 0;
//	Seat holderSeat;
//	//This loop helps loop through the letter variable until it loops for the amount that is equal to the number of Columns.
//	while(letter <='Z'&& counter < cN)
//	{
//		if(letter == 'A')
//		{
//			//This helps print the initial space to line up the letters with the auditorium columns.
//			cout << "  "<<letter;
//			++letter;
//			counter++;
//		}
//		else{
//			//Each time this loop loops, the letter is incremented up one, going in alphabetical order.
//			cout<<letter;
//			++letter;
//			counter++;
//		}
//
//	}
//	cout << endl;
//	//This helps print out each of the chars in the auditorium array, and also helps put a label on each row.
//	for(int r = 0;r < rN; r++ ){
//		cout << r+1<<" ";
//		for(int c = 0; c < cN; c++){
//			holderSeat = head->getSeatObj();
//			if(holderSeat.getTicketType()=='.')
//			{
//				cout << ".";
//			}
//			else{
//				cout << "#";
//			}
//			if(c < cN-1){
//			head = head->getRight();
//			}
//		}
//		for(int c = 0; c < cN-1; c++){
//			head = head->getLeft();
//		}
//		cout << endl;
//		if(r < rN-1){
//		head = head->getDown();
//		}
//	}
//}
////This method checks if the seats requested are possible to book and returns a boolean value based on that information.
//bool checkAvailable(Node<Seat> *head, int r, int s, int total){
//	Seat holderSeat;
//	for(int j = 0;j < r; j++ ){
//		head = head->getDown();
//	}
//	for(int k = 0; k < s; k++){
//		head = head->getRight();
//	}
//	for(int i = 1; i <= total; i++){
//		holderSeat = head->getSeatObj();
//		if(holderSeat.getTicketType() == '.')
//		{
//			if(i < total){
//			head = head->getRight();
//			}
//		}
//		else{
//			return false;
//		}
//	}
//	return true;
//}
////This method reserves the seats the user requests. This method is mainly effective if used after the implementation of the checkAvailable() method
//void reserveSeats(Node<Seat> *head, int r, int s, int aNum, int sNum, int cNum ){
//	//These loops change the respective seat to the respective ticket requested.
//	Seat holderSeat;
//	for(int j = 0;j < r; j++ ){
//			head = head->getDown();
//		}
//		for(int k = 0; k < s; k++){
//			head = head->getRight();
//		}
//	for(int i = 0; i < aNum; i++){
//		holderSeat = head->getSeatObj();
//		holderSeat.setTicketType('A');
//		head->setSeatObj(&holderSeat);
//		head = head->getRight();
//	}
//	for(int j = 0; j < cNum; j++){
//		holderSeat = head->getSeatObj();
//		holderSeat.setTicketType('C');
//		head->setSeatObj(&holderSeat);
//		head = head->getRight();
//		}
//	for(int k = 0; k < sNum; k++){
//		holderSeat = head->getSeatObj();
//		holderSeat.setTicketType('S');
//		head->setSeatObj(&holderSeat);
//		head = head->getRight();
//		}
//}
////This method displays a report at the end of the ticket reservations, showing the user what they have requested and information on the rest of the auditorium.
//void displayReport(Node<Seat> *head, int rN, int cN){
//	//Each of these vars are used in the final part of the report. The Counter helps increment the double up for each of the tickets for the final price. the Sold keeps track of how many tickets are sold.
//	int seats;
//	double totalSales;
//	int aSold = 0;
//	double aCounter = 0;
//	int cSold = 0;
//	double cCounter = 0;
//	int sSold = 0;
//	double sCounter = 0;
//	seats =0;
//	Seat holderSeat;
//	//This system of loops scans each letter of the 2D array, and increments the variable that is supposed to be incremented based on what is in the slot scanned.
//	for(int i = 0; i < rN; i++){
//		for(int j = 0; j < cN; j++){
//			holderSeat = head->getSeatObj();
//			//These loops increment the report for each ticket based on the scanned value from the 2D array at the points scanned.
//			seats++;
//			if(holderSeat.getTicketType() == 'A'){
//				aSold++;
//				aCounter++;
//			}
//			else if(holderSeat.getTicketType() == 'C'){
//				cSold++;
//				cCounter++;
//			}
//			else if(holderSeat.getTicketType() == 'S'){
//					sSold++;
//					sCounter++;
//			}
//			if(j < cN-1){
//						head = head->getRight();
//						}
//
//		}
//		for(int c = 0; c < cN-1; c++){
//					head = head->getLeft();
//				}
//
//				if(i < rN-1){
//				head = head->getDown();
//				}
//	}
//	//This is where the final report is printed out.
//	aCounter = aCounter*10.00;
//	cCounter = cCounter*5.00;
//	sCounter = sCounter*7.50;
//	totalSales = aCounter+cCounter+sCounter;
//	//This is where the report is printed to the console
//	cout << "Total Seats:	"<<seats<<endl;
//	cout << "Total Tickets:	"<<aSold+cSold+sSold<<endl;
//	cout << "Adult Tickets:	"<<aSold<<endl;
//	cout << "Child Tickets:  "<<cSold<<endl;
//	cout << "Senior Tickets: "<<sSold<<endl;
//	cout << "Total Sales:	$"<<fixed<<setprecision(2)<<totalSales<<endl;
//}
////This method pushes the array into a file
//void pushFile(Node<Seat> *head, int rN, int cN){
//	//This is where the out put file stream is initialized, which allows me to push out the 2D array to the external file.
//	ofstream outfile;
//	Seat holderSeat;
//	if(outfile){
//		//A1.txt is the file being outputted to
//	outfile.open("A1.txt");
//	for(int r = 0;r < rN; r++ ){
//			for(int c = 0; c < cN; c++){
//				holderSeat = head->getSeatObj();
//
//				outfile << holderSeat.getTicketType();
//				if(c < cN-1){
//				head = head->getRight();
//				}
//			}
//			outfile << "\n";
//			for(int c = 0; c < cN-1; c++){
//				head = head->getLeft();
//			}
//
//			if(r < rN-1){
//			head = head->getDown();
//			}
//		}
//	//Closing the file
//	outfile.close();
//}
//}
////This method helps to check if an inputed string can be validated and turned into an int.
//bool isValid(string s) {
//	for (int i = 0; (unsigned)i < s.length(); i++) {
//		if (isdigit(s[i]) == false || s.at(i) == '.') {
//			return false;
//
//		}
//	}
//	return true;
//}
//int main() {
//	//This var helps validate each input
//int validate=0;
////This var holds the row number value inputed
//int row=-1;
//string rowStr;
////This var holds the seat letter input
//string seatLet="a";
//char seatCh = 'A';
////This var holds the converted seat letter input which is converted into the index of the column
//int seat;
////This var holds the total amount of tickets wanted, calculated in the end.
//int amount;
////This var assists in the conversion of the char to int.
//char charConvert;
////These vars helps with displaying the best available seats.
//char bestSeatLet2='A';
////This char is the Y/N for the best available seats.
//string chooseBest;
//char chooseBestCh;
////File input stream initialized.
//ifstream infile;
////These hold each of the type of tickets
//int adult=-1;
//string adultStr;
//int child=-1;
//string childStr;
//int senior=-1;
//string seniorStr;
////This holds the file name
//string filename;
////This is used to calculate the number of col
//string holder;
////These will hold the number of rows and columns
//int rowNum=0;
//int colNum=0;
////Start of program
//
//cout << "Enter file name: ";
////Loop for input validation
//while(validate == 0){
//	cin >> filename;
//	//This opens the file input stream
//	infile.open(filename);
//	//This gets the number of columns
//	if(infile){
//	validate = 1;
//	infile.ignore(26, '\n');
//	getline(infile,holder);
//	colNum = (int)holder.length();
//
//	infile.close();
//	//This loop right here establishes the size of the auditorium file and checks if they are within the boundaries.
//		infile.open(filename);
//		if(infile){
//		while(getline(infile,holder))
//		{
//			rowNum++;
//
//		}
//
//
//		if(rowNum > 10 || colNum > 26)
//		{
//			cout << endl;
//			cout << "File entered is invalid. Please try again.";
//			cout << endl;
//			validate = 0;
//		}
//		}
//		}
//	else{
//		cout << endl;
//		cout << "File entered is invalid. Please try again.";
//		cout << endl;
//		validate = 0;
//	}
//		infile.close();
//}
//validate = 0;
//cout << endl;
//
////filename = "sample_theater.txt";
//
//
//
////This is the linked list which will hold the file
//Auditorium aud = Auditorium(filename, rowNum, colNum);
////This variable checks if the user wants to exit the upcoming loop.
//string exit;
////This is the start of the loop which requests for information on the tickets from the user, It checks if the user want to reserve seats, and continues the loop until the user wants to exit..
////Each while loop that starts with while(validate == 0){... is a loop for input validation in which a sequence of tests are implemented to check the validity of the user input.
//do{
//cout << "1. Reserve Seats";
//cout << endl;
//cout << "2. Exit";
//cout<< endl;
//cin >> exit;
//if(exit == "1"){
//	displayAudit(aud.getFirst(), rowNum, colNum);
//	cout << "Enter desired row number: ";
//	while(validate == 0){
//	cin >> rowStr;
//	if(isValid(rowStr)==true)
//	{
//		row = stoi(rowStr);
//	}
//	else{
//		cout << endl;
//		cout << "Invalid row number, please try again";
//		cout << endl;
//	}
//
//    if(row != -1){
//	if(row>rowNum || row < 1){
//			cout << endl;
//			cout << "Invalid row number, please try again";
//			cout << endl;
//
//		}
//	else {
//		validate = 1;
//	}
//    }
//	}
//	row=row-1;
//	cout << endl;
//	//This is the start of the input requests
//	validate = 0;
//	cout << "Enter desired starting seat letter: ";
//	while(validate == 0){
//	cin >> seatLet;
//	if(seatLet.length() > 1){
//		cout << endl;
//		cout << "Invalid seat letter, please try again";
//		cout << endl;
//	}
//	else{
//		seatCh = seatLet[0];
//	}
////This turns the char into an int to be put into the methods required.
//	if(seatLet.length() == 1){
//	seatCh =toupper(seatCh);
//	charConvert = 'A';
//	seat = 0;
//	int counter = 0;
//	while(counter != 1){
//		if(seatCh == charConvert){
//			counter = 1;
//		}
//		else{
//			charConvert++;
//			seat++;
//		}
//	}
//	if(seat>colNum || colNum < 1){
//			cout << endl;
//			cout << "Invalid seat letter, please try again";
//			cout << endl;
//		}
//	else {
//			validate = 1;
//		}
//	}
//	}
//	cout << endl;
//	validate = 0;
//	cout << "Enter desired number of Adult Tickets: ";
//	while(validate == 0){
//		cin >> adultStr;
//			if(isValid(adultStr)==true)
//			{
//				adult = stoi(adultStr);
//			}
//			else{
//				cout << endl;
//				cout << "Invalid number of Adult Tickets, please try again";
//				cout << endl;
//			}
//
//		    if(adult != -1){
//			if(adult < 0){
//					cout << endl;
//					cout << "Invalid number of Adult Tickets, please try again";
//					cout << endl;
//
//				}
//			else {
//				validate = 1;
//			}
//		    }
//	}
//	cout << endl;
//	validate = 0;
//	cout << "Enter desired number of Child Tickets: ";
//	while(validate == 0){
//		cin >> childStr;
//					if(isValid(childStr)==true)
//					{
//						child = stoi(childStr);
//					}
//					else{
//						cout << endl;
//						cout << "Invalid number of Child Tickets, please try again";
//						cout << endl;
//					}
//
//				    if(child != -1){
//					if(child < 0){
//							cout << endl;
//							cout << "Invalid number of Child Tickets, please try again";
//							cout << endl;
//
//						}
//					else {
//						validate = 1;
//					}
//				    }
//	}
//	cout << endl;
//	validate = 0;
//	cout << "Enter desired number of Senior Tickets: ";
//	while(validate == 0){
//		cin >> seniorStr;
//					if(isValid(seniorStr)==true)
//					{
//						senior = stoi(seniorStr);
//					}
//					else{
//						cout << endl;
//								cout << "Invalid number of Senior Tickets, please try again";
//								cout << endl;
//							}
//
//						    if(senior != -1){
//							if(senior < 0){
//									cout << endl;
//									cout << "Invalid number of Senior Tickets, please try again";
//									cout << endl;
//
//								}
//							else {
//								validate = 1;
//							}
//						    }
//	}
//
////amount var gets its value here
//	validate = 0;
//	amount = adult+child+senior;
//
//
////This is where most methods are called.
//	cout << endl;
//	if(checkAvailable(aud.getFirst(), row, seat, amount)){
//		reserveSeats(aud.getFirst(), row, seat, adult, senior, child);
//		displayReport(aud.getFirst(), rowNum, colNum);
//		pushFile(aud.getFirst(), rowNum, colNum);
//
//
//
//	}
//	//This else statement is where the best available seats are requested
//	else{
////		cout << "no seats available." << endl;
//		Seat bestChecker = bestAvailable(aud.getFirst(), rowNum, colNum, amount);
//		bestSeatLet2='A';
//		if(bestChecker.getSeat() != ' '){
//		cout << "No seats available at requested spots. Would you like to book the next best available seats?[Y/N]" << endl;
//		//This loop calculates the first best letter.
//		bestSeatLet2 = bestChecker.getSeat();
//				for(int q = 0; q<amount-1;q++){
//							bestSeatLet2++;
//						}
//		cout << bestChecker.getRow() << bestChecker.getSeat() <<" - "<<bestChecker.getRow()<<bestSeatLet2<<endl;
//		while(validate == 0){
//			cin >> chooseBest;
//				if(chooseBest.length() > 1){
//					cout << endl;
//					cout << "Invalid input, please try again";
//					cout << endl;
//				}
//				else{
//					chooseBestCh = chooseBest[0];
//				}
//			//This turns the char into an int to be put into the methods required.
//				if(chooseBest.length() == 1){
//					chooseBestCh =toupper(chooseBestCh);
//				if(chooseBestCh != 'Y' && chooseBestCh != 'N'){
//						cout << endl;
//						cout << "Invalid input, please try again";
//						cout << endl;
//					}
//				else {
//						validate = 1;
//					}
//				}
//		}
//		validate = 0;
//		//Reserves the best seats available seats
//		if(chooseBestCh == 'Y'){
//			reserveSeats(aud.getFirst(), bestChecker.getRow()-1, (int)bestChecker.getSeat()-65, adult, senior, child);
//			displayReport(aud.getFirst(), rowNum, colNum);
//			pushFile(aud.getFirst(), rowNum, colNum);
//		}
//		}
//		//If the bestAvailable function returns to -1, that means there are no seats available.
//		else{
//			cout << "no seats available." << endl;
//		}
//
//	}
//
//
//}
////This displays a report at the end of the loop when the user exits.
//else if (exit == "2"){
//	displayReport(aud.getFirst(), rowNum, colNum);
//}
//else{
//	cout << endl;
//	cout << "Invalid input, please try again";
//	cout << endl;
//}
////This determines what input the user uses when they want to exit.
//}while(exit != "2");
////This was used to debug the program. You can un-comment it to check how the distance works.
////cout << (double)sqrt(pow(8 - ((double)7+(((double)(2+1.0)/2.0)-1.0)), 2) +
////        pow(3 - (2+1), 2));
////cout << endl;
////cout << ((double)7+(((2+1)/2)-1));
////cout << endl;
//
////Standard return statement in c++ which symbolizes the end of the file.
//	return 0;
//}
//
//

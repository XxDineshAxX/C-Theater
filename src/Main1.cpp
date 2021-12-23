////============================================================================
//// Name        : Main.cpp
//// Author      : Dinesh Angadipeta DXA@190032
//// Description : Project Zero for CS 2337
////============================================================================
//
////Importing necessary tools and repositories These essentially allow certain variables and functions to exist in this code..
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <iomanip>
//using namespace std;
//
////This function helps calculate the next best available seats if the one's the user requested weren't available.
//int bestAvailable(char aud[10][26], int r,int cN, int total){
//	//This var helps check if the seats checked were empty
//	int empty = 0;
//	//This var is set as 1000 so the first distance value calculated will  be smaller, as it is read in.
//	int distance =1000;
//	//This var holds the starting seat number.
//	int strtSeat=-1;
//	//Loops through the row, checking if there are other seats available consecutively.
//	for(int i = 1; i <= cN-total+1; i++){
//		for(int j = 0; j < total; j++){
//
//			if(aud[r][(i+j)-1] != '.'){
//				empty = 1;
//				break;
//			}
//			else{
//				empty = 0;
//			}
//
//		}
//		if(empty == 0){
////Calculates the smallest possible distance value, which in hand will return the smalles starting seat number.
//			if(distance > abs((i + (total-1)/2)-(cN+1)/2 )){
//				distance =0;
//				distance = abs((i + (total-1)/2)-(cN+1)/2);
//				strtSeat = i;
//			}
//
//
//		}
//
//	}
//
//	return strtSeat;
//}
////This method returns a visual representation of the auditorium for the user to be able to choose their seats.
//void displayAudit(char aud[10][26], int rN, int cN){
//	//These 2 variables help show the lab'es of each row and column
//	char letter = 'A';
//	int counter = 0;
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
//			if(aud[r][c]=='.')
//			{
//				cout << ".";
//			}
//			else{
//				cout << "#";
//			}
//		}
//		cout << endl;
//	}
//}
////This method checks if the seats requested are possible to book and returns a boolean value based on that information.
//bool checkAvailable(char aud[10][26], int r, int s, int total){
//	for(int i = 1; i <= total; i++){
//		if(aud[r][s] == '.')
//		{
//			s++;
//		}
//		else{
//			return false;
//		}
//	}
//	return true;
//}
////This method reserves the seats the user requests. This method is mainly effective if used after the implementation of the checkAvailable() method
//void reserveSeats(char aud[10][26], int r, int s, int aNum, int sNum, int cNum ){
//	//These loops change the respective seat to the respective ticket requested.
//	for(int i = 0; i < aNum; i++){
//		aud[r][s] = 'A';
//		s++;
//	}
//	for(int j = 0; j < cNum; j++){
//		aud[r][s] = 'C';
//				s++;
//		}
//	for(int k = 0; k < sNum; k++){
//		aud[r][s] = 'S';
//				s++;
//		}
//}
////This method displays a report at the end of the ticket reservations, showing the user what they have requested and information on the rest of the auditorium.
//void displayReport(char aud[10][26], int rN, int cN){
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
//	//This system of loops scans each letter of the 2D array, and increments the variable that is supposed to be incremented based on what is in the slot scanned.
//	for(int i = 0; i < rN; i++){
//		for(int j = 0; j < cN; j++){
//			//These loops increment the report for each ticket based on the scanned value from the 2D array at the points scanned.
//			seats++;
//			if(aud[i][j] == 'A'){
//				aSold++;
//				aCounter++;
//			}
//			else if(aud[i][j] == 'C'){
//				cSold++;
//				cCounter++;
//			}
//			else if(aud[i][j] == 'S'){
//					sSold++;
//					sCounter++;
//			}
//
//		}
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
//void pushFile(char aud[10][26], int rN, int cN){
//	//This is where the out put file stream is initialized, which allows me to push out the 2D array to the external file.
//	ofstream outfile;
//	if(outfile){
//		//A1.txt is the file being outputted to
//	outfile.open("A1.txt");
//	for (int z = 0; z < rN; z++){
//					for(int x = 0; x < cN; x++){
//						outfile << aud[z][x];
//					}
//					outfile << "\n";
//				}
//	}
//	//Closing the file
//	outfile.close();
//}
//
//int main() {
//	//This var helps validate each input
//int validate=0;
////This var holds the row number value inputed
//int row=-1;
////This var holds the seat letter input
//char seatLet='a';
////This var holds the converted seat letter input which is converted into the index of the column
//int seat;
////This var holds the total amount of tickets wanted, calculated in the end.
//int amount;
////This var assists in the conversion of the char to int.
//char charConvert;
////These vars helps with displaying the best available seats.
//char bestSeatLet='A';
//char bestSeatLet2='A';
////This char is the Y/N for the best available seats.
//char chooseBest;
////File input stream initialized.
//ifstream infile;
////These hold each of the type of tickets
//int adult=-1;
//int child=-1;
//int senior=-1;
////This holds the file name
//string filename;
////This is used to calculate the number of col
//string holder;
////Start of program
//cout << "Enter file name: ";
//cin >> filename;
//cout << endl;
////These will hold the number of rows and columns
//int rowNum=0;
//int colNum=0;
////This opens the file input stream
//infile.open(filename);
////This gets the number of columns
//if(infile){
//infile.ignore(26, '\n');
//getline(infile,holder);
//colNum = (int)holder.length();
//}
//infile.close();
////This loop right here establishes the size of the auditorium file and checks if they are within the boundaries.
//	infile.open(filename);
//	if(infile){
//	while(getline(infile,holder))
//	{
//		rowNum++;
//
//	}
//
//
//	if(rowNum > 10 || colNum > 26)
//	{
//		cout << "File entered is invalid.";
//		return -1;
//	}
//	}
//	infile.close();
//
////This is the 2D array which will hold the file
//char auditorium[10][26];
//infile.open(filename);
//if(infile){
//for(int i = 0;i<rowNum; i++ ){
//	for(int j=0;j<colNum;j++){
//		infile >> auditorium[i][j];
//	}
//}
//}
//infile.close();
////This variable checks if the user wants to exit the upcoming loop.
//int exit = 0;
////This is the start of the loop which requests for information on the tickets from the user, It checks if the user want to reserve seats, and continues the loop until the user wants to exit..
//do{
//cout << "1. Reserve Seats";
//cout << endl;
//cout << "2. Exit";
//cout<< endl;
//cin >> exit;
//if(exit == 1){
//	displayAudit(auditorium, rowNum, colNum);
//	cout << "Enter desired row number: ";
//	while(validate == 0){
//	cin >> row;
//	if(row>rowNum || row < 1){
//			cout << endl;
//			cout << "Invalid row number, please try again";
//			cout << endl;
//
//		}
//	else {
//		validate = 1;
//	}
//	}
//	row=row-1;
//	cout << endl;
//	//This is the start of the input requests
//	validate = 0;
//	cout << "Enter desired starting seat letter: ";
//	while(validate == 0){
//	cin >> seatLet;
////This turns the char into an int to be put into the methods required.
//	seatLet =toupper(seatLet);
//	charConvert = 'A';
//	seat = 0;
//	int counter = 0;
//	while(counter != 1){
//		if(seatLet == charConvert){
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
//	cout << endl;
//	validate = 0;
//	cout << "Enter desired number of Adult Tickets: ";
//	while(validate == 0){
//	cin >> adult;
//	if(adult < 0){
//			cout << endl;
//			cout << "Invalid number of Adult Tickets, please try again";
//			cout << endl;
//		}
//	else {
//				validate = 1;
//			}
//	}
//	cout << endl;
//	validate = 0;
//	cout << "Enter desired number of Child Tickets: ";
//	while(validate == 0){
//	cin >> child;
//	if(child < 0){
//			cout << endl;
//			cout << "Invalid number of Child Tickets, please try again";
//			cout << endl;
//		}
//	else {
//					validate = 1;
//				}
//	}
//	cout << endl;
//	validate = 0;
//	cout << "Enter desired number of Senior Tickets: ";
//	while(validate == 0){
//	cin >> senior;
//	if(senior < 0){
//			cout << endl;
//			cout << "Invalid number of Senior Tickets, please try again";
//			cout << endl;
//		}
//	else {
//						validate = 1;
//					}
//	}
//
////amount var gets its value here
//	validate = 0;
//	amount = adult+child+senior;
//
//
////This is where most methods are called.
//	cout << endl;
//	if(checkAvailable(auditorium, row, seat, amount)){
//		reserveSeats(auditorium, row, seat, adult, senior, child);
//		displayReport(auditorium, rowNum, colNum);
//		pushFile(auditorium, rowNum, colNum);
//
//
//
//	}
//	//This else statement is where the best available seats are requested
//	else{
//		bestSeatLet='A';
//		bestSeatLet2='A';
//		if(bestAvailable(auditorium, row, colNum, amount) != -1){
//		cout << "No seats available at requested spots. Would you like to book the next best available seats?[Y/N]" << endl;
//		//This loop calculates the first best letter.
//		for(int p = 0; p<bestAvailable(auditorium, row, colNum, amount)-1;p++){
//			bestSeatLet++;
//		}
//		//The second best letter is calculated here
//		bestSeatLet2 = bestSeatLet;
//		for(int q = 0; q<amount-1;q++){
//					bestSeatLet2++;
//				}
//		cout << row+1 << bestSeatLet <<" - "<<row+1<<bestSeatLet2<<endl;
//		cin >> chooseBest;
//		//Reserves the best seats available seats
//		if(chooseBest == 'Y'){
//			reserveSeats(auditorium, row, bestAvailable(auditorium, row, colNum, amount)-1, adult, senior, child);
//			displayReport(auditorium, rowNum, colNum);
//			pushFile(auditorium, rowNum, colNum);
//		}
//		}
//		//If the bestAvailable function returns to -1, that means there are no seats available.
//		else{
//			cout << "No seats available." << endl;
//		}
//
//	}
//
//
//}
////This displays a report at the end of the loop when the user exits.
//else{
//	displayReport(auditorium, rowNum, colNum);
//}
////This determines what input the user uses when they want to exit.
//}while(exit != 2);
//
//
////Standard return statement in c++ which symbolizes the end of the file.
//	return 0;
//}
//
//

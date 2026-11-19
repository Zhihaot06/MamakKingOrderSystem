#include <iostream>
#include <string>
#include <iomanip>
#include <cctype> 
#include <limits>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

struct Order
{
	string item = "--";
	string addon = "--";
	int quantity = 0;
	double prices = 0.0;
	double addonprices = 0.0;
	double totalprices = 0.0;
	string type;
};

int customer = 0;
int orderCount = 0;
double subtotal = 0;
double total_payable = 0;

double tax = 0.0;
double service_charge = 0.0;
double item_total = 0.0;
int total_item = 0;

const int MAX_ORDERS = 100;
Order orders[MAX_ORDERS];


/* report */
int foodQty[10] = { 0 };
double foodSales[10] = { 0.0 };

int drinkHotQuantity[7] = { 0 }, drinkColdQuantity[7] = { 0 };
double drinkHotSales[7] = { 0.0 }, drinkColdSales[7] = { 0.0 };

int addonQuantity[3] = { 0 };
double addonSales[3] = { 0.0 };

double grandTotal = 0.00;

void saveData();


bool existsID(string id);
bool isBeverage(string id);
bool isAddonId(string id);

void displayMainMenu();
void displayMenu();
void getOrder();
int getDiscount();
void displayInvoice();
string getPaymentMethod(int discount);
void displayReceipt(string paymentType, double change, double payAmount,int discount);
void printDailySalesReport();


/*payment*/
void sendQR();
void outError();
void sendSuccess();
bool isDigitOrNot(string str, string type);
bool isValidCardNumber(string cardNumber);


const string menu[20] = { "Roti Canai","Roti Telur","Roti Boom","Nasi Goreng Pattaya","Nasi Goreng Kampung","Nasi Lemak","Nasi Kandar","Mee Goreng",
						  "Maggie Goreng","Mee Hoon","Teh Tarik","Teh C","Teh O Ais Limau","Milo","Sirap Bandung","100 Plus","Ais Suam","Ayam Goreng","Telur Mata","Nasi Putih" };

const float pricefood[10] = { 2.50,3.50,4.00,7.00,7.00,5.00,9.00,7.00,7.00,8.00 };
const float pricedrinkH[7] = { 3.50, 3.00, 3.50, 4.00, 4.50, 3.50, 1.50 };
const float pricedrinkC[7] = { 4.00, 3.50, 3.50, 4.50, 5.00, 4.00, 2.00 };


const string Idmenu[20] = { "M001","M002","M003","M004","M005","M006","M007","M008","M009","M010",
							"D001","D002","D003","D004","D005","D006","D007","A001","A002","A003" };
const float addonPrice[3] = { 6.00,2.00,3.00 };

bool existsID(string id) {
	for (int i = 0; i < 20; i++) {
		if (Idmenu[i] == id) return true;
	}
	return false;
}

bool isBeverage(string id) {
	return id.substr(0, 1) == "D";
}

bool isAddonId(string add_on) {
	return add_on.substr(0, 1) == "A";
}

void displayMainMenu() {
	int selection;
	do {
		system("cls");
		cout << "\033[1;35m";

		cout << " _   .-')      ('-.     _   .-')      ('-.    .-. .-')        .-. .-')               .-') _             \n";
		cout << "( '.( OO )_   ( OO ).-.( '.( OO )_   ( OO ).-.\  ( OO )       \\  ( OO )             ( OO ) )           \n";
		cout << " ,--.   ,--.) / . --. / ,--.   ,--.) / . --. /,--. ,--.       ,--. ,--.  ,-.-') ,--./ ,--,'  ,----.     \n";
		cout << " |   `.'   |  | \\-.  \\  |   `.'   |  | \\-.  \\ |  .'   /       |  .'   /  |  |OO)|   \\ |  |\\ '  .-./-')  \n";
		cout << " |         |.-'-'  |  | |         |.-'-'  |  ||      /,       |      /,  |  |  \\|    \\|  | )|  |_( O- ) \n";
		cout << " |  |'.'|  | \\| |_.'  | |  |'.'|  | \\| |_.'  ||     ' _)      |     ' _) |  |(_/|  .     |/ |  | .--, \\ \n";
		cout << " |  |   |  |  |  .-.  | |  |   |  |  |  .-.  ||  .   \\        |  .   \\  ,|  |_.'|  |\\    | (|  | '. (_/ \n";
		cout << " |  |   |  |  |  | |  | |  |   |  |  |  | |  ||  |\\   \\       |  |\\   \\(_|  |   |  | \\   |  |  '--'  |  \n";
		cout << " `--'   `--'  `--' `--' `--'   `--'  `--' `--'`--' '--'       `--' '--'  `--'   `--'  `--'   `------'   \n";

		cout << "\033[1;0m";

		cout << setw(60) << "WELCOME TO MAMAK KING" << endl;

		cout << "------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|1.| Menu\t" << endl;
		cout << "|2.| Report\t" << endl;
		cout << "|3.| Exit\t" << endl;
		cout << "------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Please enter your choice: ";
		cin >> selection;
		if (selection < 0 || selection > 3) continue;
		if (selection == 3) break;
		switch (selection) {
		case 1:
			customer++;
			displayMenu();
			break;
		case 2:
			printDailySalesReport();
			break;
		}
		break;
	} while (selection < 0 || selection > 3);
}

void displayMenu() {
	int i;
	string name;

	system("CLS");

	cout << "\033[1;35m";
	cout << R"(                               _ .-') _         _   .-')      ('-.      .-') _            
                                 ( (  OO) )       ( '.( OO )_  _(  OO)    ( OO ) )           
   ,------..-'),-----. .-'),-----.\     .'_        ,--.   ,--.(,------,--./ ,--,',--. ,--.   
('-| _.---( OO'  .-.  ( OO'  .-.  ,`'--..._)       |   `.'   | |  .---|   \ |  |\|  | |  |   
(OO|(_\   /   |  | |  /   |  | |  |  |  \  '       |         | |  |   |    \|  | |  | | .-') 
   |  '--.\_) |  |\|  \_) |  |\|  |  |   ' |       |  |'.'|  |(|  '--.|  .     |/|  |_|( OO )
\_)|  .--'  \ |  | |  | \ |  | |  |  |   / :       |  |   |  | |  .--'|  |\    | |  | | `-' /
  \|  |_)    `'  '-'  '  `'  '-'  |  '--'  /       |  |   |  | |  `---|  | \   |('  '-'(_.-' 
   `--'        `-----'     `-----'`-------'        `--'   `--' `------`--'  `--'  `-----'     
    )" << endl;

	cout << "\033[1;0m";

	cout << "\n";

	cout << "------------------------------------------------------------------------------" << endl;

	cout << "\033[1;35mID\033[0m" << setw(20) << "\033[1;35mFOOD\033[0m" << right << setw(77) << "\033[1;35mPrice\033[0m" << endl;

	cout << "------------------------------------------------------------------------------" << endl;

	for (i = 0; i <= 9; i++) {
		cout << "|" << Idmenu[i] << "| " << left << setw(63) << menu[i] << right << "|RM" << fixed << setprecision(2) << pricefood[i] << "| " << endl;
	}
	cout << "\n";

	cout << "------------------------------------------------------------------------------" << endl;

	cout << setw(23) << "\033[1;35mDRINK\033[0m" << right << setw(75) << "\033[1;35mHot     Cold\033[0m" << endl;

	for (i = 10; i <= 16; i++)
		cout << "|" << Idmenu[i] << "| " << left << setw(54) << menu[i] << "|RM" << fixed << setprecision(2) << pricedrinkH[i - 10] << "| |RM" << pricedrinkC[i - 10] << "| " << endl;

	cout << "\n";

	cout << "------------------------------------------------------------------------------" << endl;

	cout << setw(24) << "\033[1;35mAdd-on\033[0m" << endl;

	for (i = 17; i <= 19; i++)
		cout << "|" << Idmenu[i] << "| " << left << setw(63) << menu[i] << "|RM" << fixed << setprecision(2) << addonPrice[i - 17] << "|" << endl;

	cout << "\n";

	cout << "------------------------------------------------------------------------------" << endl;

	//cout << left << setw(81) << "\033[1;35m*Take Away\033[0m" << right << "|RM0.50|" << endl;
	getOrder();
}

void getOrder() {

	int newID;
	string id, add_on, name;
	char more_order = 'Y', type;

	cout << endl << "Customer " << customer << endl;

	while (more_order == 'Y' && orderCount < MAX_ORDERS) {
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "Order " << (orderCount + 1) << endl;
		cout << "Enter Food Id: ";
		cin >> id;

		while (!existsID(id) || isAddonId(id)) {
			cout << "Invalid id. Please type again: ";
			cin >> id;
		}

		Order neworder;

		/*FOOD*/
		if (!isBeverage(id)) {
			for (int b = 0; b < 10; b++) {
				if (id == Idmenu[b]) {
					neworder.item = menu[b];
					neworder.prices = pricefood[b];

					cout << "Quantity: ";
					while (!(cin >> neworder.quantity) || neworder.quantity <= 0) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Please enter a valid number: ";
					}

					cout << "Add On (N = NO): ";
					cin >> add_on;

					while ((!existsID(add_on) || !isAddonId(add_on)) && (add_on != "N" && add_on != "n")) {
						cout << "Invalid Add On Id. Please type again (or N for none): ";
						cin >> add_on;
						if (add_on == "N" || add_on == "n") {
							neworder.addon = "--";
							neworder.addonprices = 0;
							break;
						}
					}
					if (isAddonId(add_on)) {
						newID = stoi(add_on.substr(add_on.length() - 2, 2));
						neworder.addon = menu[newID + 16];
						neworder.addonprices = addonPrice[newID - 1];
					}
					neworder.prices = neworder.prices + neworder.addonprices;

					neworder.totalprices = neworder.prices * neworder.quantity;

					orders[orderCount] = neworder;  // store into array
					subtotal += neworder.totalprices;
					orderCount++;
				}
			}
		}

		else if (isBeverage(id)) {
			for (int b = 10; b < 17; b++) {
				if (id == Idmenu[b]) {
					neworder.item = menu[b];

					do {
						cout << "Cold(C) or Hot(H):";
						cin >> type;

						type = toupper(type);
						if (type != 'H' && type != 'C') {
							cout << "Invalid type . Please type again:" << endl;
						}

					} while (type != 'H' && type != 'C');

					if (type == 'H') {
						neworder.type = "Hot";
						neworder.prices = pricedrinkH[b - 10];
					}
					else {
						neworder.type = "Cold";
						neworder.prices = pricedrinkC[b - 10];
					}
					cout << "Quantity: ";
					while (!(cin >> neworder.quantity) || neworder.quantity <= 0) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Please enter a valid number: ";
					}

					neworder.totalprices = neworder.prices * neworder.quantity;

					orders[orderCount] = neworder;  // store into array
					subtotal += neworder.totalprices;
					orderCount++;
				}
			}
		}

		cout << "Anymore order? (Y/N): ";
		cin >> more_order;

		if (islower(more_order)) {
			more_order = toupper(more_order);
		}

		while (more_order != 'Y' && more_order != 'N') {
			cout << "*" << endl;
			cout << "Please enter Y/N only." << endl;
			cout << "Anymore order ? (Y/N): ";
			cin >> more_order;
			if (islower(more_order)) {
				more_order = toupper(more_order);
			}
		}
	}
	displayInvoice();
}

int getDiscount() {

	int luckyNumber;
	int discount = 0;

	if (subtotal < 50) return discount;
	
	cout << "Congratulations! You've spent over RM50 and earned a chance in the lucky draw. " << endl;
	cout << "Press any key to start the lucky draw...";
	cin.ignore();
	cin.get();

	srand(time(0));
	luckyNumber = rand() % 100 + 1;
	cout << "Your lucky number is : " << luckyNumber << endl;

	if (luckyNumber <= 10) {
		discount = 15;
	}
	else if (luckyNumber > 10 && luckyNumber <= 20) {
		discount = 10;
	}
	else if (luckyNumber > 40 && luckyNumber <= 55) {
		discount = 5;
	}
	else if (luckyNumber >= 70 && luckyNumber < 88) {
		discount = 8;
	}
	else cout << "Sorry, no prize this time.Better luck next time !" << endl;

	if(discount >= 1) cout << "Congratulations! You have won an RM" << discount << " off discount !" << endl;
	cin.get();
	return discount;
}

void displayInvoice() {

	int discount;
	discount = getDiscount();

	system("CLS");

	cout << "Thank you for your order ^_^" << endl;
	cout << "This is your invoice.Please review the details before generating." << endl;
	cout << "------------------------------------------------------------------------------------------" << endl;
	cout << "|" << right << setw(45) << "MAMAK KING" << right << setw(41) << "Invoice No:" << (1000 + customer) << "|" << endl;
	cout << "|                     9-1, Jalan 2A/6 , Taman Setapak Indah                                |" << endl;
	cout << "|                               55330 Kuala Lumpur                                         |" << endl;

	cout << "|" << right << setw(47) << " TEL 0617 2358837" << setw(44) << "|" << endl;
	cout << "+------------------------------------------------------------------------------------------+" << endl;
	cout << "|" << right << setw(22) << "ITEM" << right << setw(17) << "|" << right << setw(13) << "QUANTITY" << right << setw(5) << "|"
		<< right << setw(15) << "UNIT PRICE" << right << setw(5) << "|" << right << setw(12) << "TOTAL (RM)" << right << setw(2) << "|" << endl;
	cout << "+------------------------------------------------------------------------------------------+" << endl;

	int counter = 1;

	for (int i = 0; i < orderCount; i++) {
		string itemLine = orders[i].item;

		cout << "|" << counter << "." << left << setw(34) << itemLine
			<< right << setw(13) << orders[i].quantity
			<< right << setw(20) << fixed << setprecision(2) << orders[i].prices
			<< right << setw(21) << fixed << setprecision(2) << orders[i].totalprices
			<< "|" << endl;

		if (orders[i].addon != "--") {
			cout << "|" << setw(4) << " " << left << setw(26) << ("Add-on: " + orders[i].addon)
				<< right << setw(60) << " " << "|" << endl;
		}

		counter++;
	}

	service_charge = subtotal * 0.05;
	tax = subtotal * 0.05;
	total_payable = subtotal + service_charge + tax - discount;

	for (int i = 0; i < orderCount; ++i) total_item += orders[i].quantity;

	cout << "+------------------------------------------------------------------------------------------+" << endl;
	cout << "|" << right << setw(70) << "SUBTOTAL\t:" << fixed << setprecision(2) << right << setw(8) << subtotal << right << setw(11) << "|" << endl;
	cout << "|" << right << setw(70) << "SERVICE CHARGE (5%)\t:" << fixed << setprecision(2) << right << setw(8) << service_charge << right << setw(11) << "|" << endl;
	cout << "|" << right << setw(70) << "TAX\t:" << fixed << setprecision(2) << right << setw(8) << tax << right << setw(11) << "|" << endl;
	cout << "|" << right << setw(91) << "|" << endl;
	cout << "|" << right << setw(70) << "TOTAL ITEM\t:" << right << setw(8) << total_item << right << setw(11) << "|" << endl;
	cout << "|" << right << setw(70) << "DISCOUNT\t:" << right << setw(8) << -discount << right << setw(11) << "|" << endl;
	cout << "|" << right << setw(70) << "TOTAL PAYABLE\t:" << fixed << setprecision(2) << right << setw(8) << total_payable << right << setw(11) << "|" << endl;
	cout << "------------------------------------------------------------------------------------------" << endl;

	getPaymentMethod(discount);
}

bool isDigitOrNot(string str, string type = "no") {
	if (str.empty())
		return false;
	int num = 0;
	for (char c : str) {
		if (type == "money" && c == '.') {
			++num;
			if (num > 1) return false;
			continue;
		}
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}

bool isValidCardNumber(string cardNumber) {
	string digits;
	for (char c : cardNumber) {
		if (isdigit(c)) digits += c;

	}
	return digits.length() == 16;
}

void outError() {

	cout << "\033[1;31m";

	cout << "\n";

	cout << ",------.                             \n";
	cout << "|  .---',--.--.,--.--. ,---. ,--.--. \n";
	cout << "|  `--, |  .--'|  .--'| .-. ||  .--' \n";
	cout << "|  `---.|  |   |  |   ' '-' '|  |    \n";
	cout << "`------'`--'   `--'    `---' `--'    \n";

	cout << "\n";

	cout << "\033[0m";
}

void sendQR() {
	cout << "##################################################################################" << endl;
	cout << "##################################################################################" << endl;
	cout << "##################################################################################" << endl;
	cout << "##################################################################################" << endl;
	cout << "########              ######  ##  ##  ##  ##              ##              ########" << endl;
	cout << "########  ##########  ##  ##  ####  ##        ##    ####  ##  ##########  ########" << endl;
	cout << "########  ##      ##  ##########  ####  ####  ####  ##    ##  ##      ##  ########" << endl;
	cout << "########  ##      ##  ##      ##    ##      ##  ############  ##      ##  ########" << endl;
	cout << "########  ##      ##  ##      ##    ##      ##  ############  ##      ##  ########" << endl;
	cout << "########  ##########  ##    ##    ##      ######    ####  ##  ##########  ########" << endl;
	cout << "########              ##  ##  ##  ##  ##  ##  ##  ##  ##  ##              ########" << endl;
	cout << "##########################      ####      ##    ##  ##############################" << endl;
	cout << "########          ##        ##  ##    ####  ####  ########  ##  ##  ##  ##########" << endl;
	cout << "########  ######    ####  ##  ##  ##########                  ######      ########" << endl;
	cout << "########  ####    ##  ######  ####  ##    ######    ######  ##########  ##########" << endl;
	cout << "##################  ##  ########  ##    ######  ##  ####    ##  ##      ##########" << endl;
	cout << "########    ##  ##    ##      ##        ##    ##  ########  ####    ##  ##########" << endl;
	cout << "########      ##    ##    ########  ####                  ##  ####    ##  ########" << endl;
	cout << "##########    ##      ########            ######    ######  ####        ##########" << endl;
	cout << "########  ########  ##    ##    ####      ####          ##  ####      ############" << endl;
	cout << "##############  ##              ##    ####  ##  ######      ##      ##############" << endl;
	cout << "##########          ######    ##  ############    ####          ####      ########" << endl;
	cout << "##########      ##    ######  ######      ##########  ############  ##  ##########" << endl;
	cout << "########    ####    ##  ##    ##  ####    ##  ####            ##        ##########" << endl;
	cout << "########    ##        ##      ##        ##  ####  ##  ####  ##    ####  ##########" << endl;
	cout << "########    ######  ##    ##  ##########          ####  ##    ####        ########" << endl;
	cout << "########  ##    ##        ##      ##    ##  ####    ####    ####        ##########" << endl;
	cout << "########  ##      ####  ######  ####      ######        ########          ########" << endl;
	cout << "########  ####  ##    ######    ######          ####                ##############" << endl;
	cout << "########################  ######    ####        ##    ##  ######  ##      ########" << endl;
	cout << "########              ##    ######        ############    ##  ##  ####  ##########" << endl;
	cout << "########  ##########  ####    ##    ##  ########          ######  ##    ##########" << endl;
	cout << "########  ##      ##  ##  ##  ##  ##  ####  ####  ######          ################" << endl;
	cout << "########  ##      ##  ##  ##############  ####    ####  ##  ##      ##############" << endl;
	cout << "########  ##      ##  ##  ####    ####  ##  ####        ####  ########  ##########" << endl;
	cout << "########  ##########  ##        ####  ############    ######  ##      ############" << endl;
	cout << "########              ##  ##    ######      ##  ####        ##  ######  ##########" << endl;
	cout << "##################################################################################" << endl;
	cout << "##################################################################################" << endl;
	cout << "##################################################################################" << endl;
	cout << "##################################################################################" << endl;
}

void sendSuccess() {

	system("CLS");

	cout << "\033[1;32m";

	cout << R"(
   ___                           __    ____                         ___     __
  / _ \___ ___ ____ _  ___ ___  / /_  / __/_ _____________ ___ ___ / _/_ __/ /
 / ___/ _ `/ // /  ' \/ -_) _ \/ __/ _\ \/ // / __/ __/ -_|_-<(_-</ _/ // / / 
_/   \_,_/\_, /_/_/_/\__/_//_/\__/ /___/\_,_/\__/\__/\__/___/___/_/ \_,_/_/  
          /___/
)";
	cout << "\033[0m";
}

string getPaymentMethod(int discount) {

	string payment = "none";
	double change = 0;

	string cardNumber = "";

	string checkAmount;
	int payAmount2 = 0, totalPayable = 1000;
	double payAmount;

	string month, year, secureCode;

	/*cout << "\n";
	cout << "-----------------------------------------------\n";
	cout << "----------------Payment Method-----------------\n";
	cout << "-----------------------------------------------\n\n";*/
	cout << endl << "Please enter your payment method(cash/ewallet/card): ";

	do {
		if (payment != "none") {
			outError();
			cout << "Invalid payment method!!! Please type again(cash/ewallet/card): ";
		}
		cin >> payment;
		for (char& c : payment) {
			c = tolower(c);
		}
	} while (payment != "ewallet" and payment != "card" and payment != "cash");

	if (payment == "ewallet") {

		system("CLS");
		sendQR();
		cout << endl << "After payment please enter to continue";
		cin.get();
		cin.ignore();
		sendSuccess();
		payAmount = total_payable;

	}
	else if (payment == "card") {

		system("CLS");

		cout << "\n";
		cout << "-----------------------------------------------\n";
		cout << "--------------Credit Card Detail---------------\n";
		cout << "-----------------------------------------------\n\n";
		cout << "Please enter your card number(must be 16 digit): ";
		cin.ignore();
		getline(cin, cardNumber);//if including space...

		while (!isValidCardNumber(cardNumber)) {
			outError();
			cout << "Card number must be 16 digit, please type again...: ";
			getline(cin, cardNumber);
		}


		cout << "Please enter your expiration month and year (eg.12 27): ";
		cin >> month >> year;
		while (month.length() != 2 || year.length() != 2 || !isDigitOrNot(month) || !isDigitOrNot(year)) {

			outError();

			cout << "Expiration month and year must be 2 digit please type again...: ";
			cin >> month >> year;
		}

		cout << "Please enter your security code (eg.123): ";
		cin >> secureCode;
		while (secureCode.length() != 3 || !isDigitOrNot(secureCode)) {

			outError();

			cout << "Security code must be 3 digit please type again...: ";
			cin >> secureCode;
		}

		sendSuccess();
		payAmount = total_payable;
	}
	else {

		do {

			cout << endl << "Please enter pay amount: ";

			cin >> checkAmount;
			if (!isDigitOrNot(checkAmount, "money")) {
				outError();
				cout << "Pay amount must be digit" << endl;
				continue;
			}
			payAmount = stod(checkAmount);
			payAmount2 = (int)round(payAmount * 100);
			totalPayable = (int)round(total_payable * 100);

			if (payAmount2 <= 0 || payAmount2 < totalPayable) {
				outError();
				cout << "Pay amount must greater than 0 and atleast is RM" << total_payable << endl;
				continue;
			}
			break;
		} while (!isDigitOrNot(checkAmount, "money") || payAmount2 <= 0 || payAmount2 < totalPayable);

	}

	change = payAmount - total_payable;

	sendSuccess();
	cout << "Please enter to continue...";

	cin.ignore();

	displayReceipt(payment, change, payAmount,discount);

	return payment;
}

void displayReceipt(string paymentType, double change, double payAmount,int discount) {
	system("CLS");


	//display receipt
	cout << "--------------------------------------- RECEIPT ---------------------------------------" << endl;
	cout << right << setw(48) << "RECEIPT NO: " << (1000 + customer) << "\n\n";
	cout << right << setw(48) << "MAMAK KING" << endl;
	cout << "                          9-1, Jalan 2A/6 , Taman Setapak Indah" << endl;
	cout << "                                  55330 Kuala Lumpur" << endl;
	cout << "                                  TEL 0617 2358837 " << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << left << setw(35) << "ITEM" << setw(20) << "QUANTITY" << setw(20) << "PRICE" << setw(20) << "TOTAL (RM)" << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;

	//order items
	for (int i = 0; i < orderCount; i++) {
		string name = orders[i].item;
		if (!orders[i].type.empty()) {
			name += " (" + orders[i].type + ")";
		}

		cout << left << setw(38) << name.substr(0, 25) << setw(17) << orders[i].quantity << "RM " << setw(18) << fixed << setprecision(2) << orders[i].prices << "RM " << setw(12) << fixed << setprecision(2) << orders[i].totalprices << endl;


		if (orders[i].addon != "--") {
			string addonLine = "  + " + orders[i].addon;
			cout << left << setw(35) << addonLine.substr(0, 25) << setw(10) << " " << setw(15) << " " << setw(15) << " " << endl;



		}
	}

	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << left << setw(79) << "Total Items:" << total_item << endl;
	cout << left << setw(76) << "Subtotal:" << "RM " << fixed << setprecision(2) << subtotal << endl;
	cout << left << setw(76) << "Service Charge (5%):" << "RM " << service_charge << endl;
	cout << left << setw(76) << "Tax (5%):" << "RM " << tax << endl;
	cout << left << setw(76) << "Discount:" << "RM " << -discount << endl;
	cout << left << setw(76) << "Total:" << "RM " << fixed << setprecision(2) << total_payable << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << left << setw(76) << "Payment method:" << paymentType << endl;
	cout << left << setw(76) << "Payment amount:" << "RM " << payAmount << endl;
	cout << left << setw(76) << "Change:" << "RM " << change << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << right << setw(60) << "THANK YOU  PLEASE COME AGAIN!" << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;

	cout << "Please enter to continue...";

	saveData();

	orderCount = 0;

	subtotal = 0;
	tax = 0;
	service_charge = 0;
	total_item = 0;

	cin.ignore();
	displayMainMenu();
}

void saveData() {
	

	for (int i = 0; i < orderCount; i++) {
		for (int f = 0; f < 10; f++) {
			if (orders[i].item == menu[f]) {
				foodQty[f] += orders[i].quantity;
				foodSales[f] += orders[i].totalprices;
				grandTotal += orders[i].totalprices;
			}
		}

		for (int d = 0; d < 7; d++) {
			if (orders[i].item == menu[10 + d]) {
				if (orders[i].type == "Hot") {
					drinkHotQuantity[d] += orders[i].quantity;
					drinkHotSales[d] += orders[i].totalprices;
				}
				else if (orders[i].type == "Cold") {
					drinkColdQuantity[d] += orders[i].quantity;
					drinkColdSales[d] += orders[i].totalprices;
				}
				grandTotal += orders[i].totalprices;
			}
		}

		for (int a = 17; a <= 19; a++) {
			if (orders[i].addon == menu[a]) {
				addonQuantity[a - 17] += orders[i].quantity;
				addonSales[a - 17] += orders[i].addonprices * orders[i].quantity;
				grandTotal += orders[i].addonprices * orders[i].quantity;
			}
		}
	}
}

void printDailySalesReport() {

	cout << "\n--------------------------------------------------------------------------------------------------\n";
	cout << "|                                      Daily Sales Report                                        |\n";
	cout << "--------------------------------------------------------------------------------------------------\n";
	cout << "|  ID  |   Main                   |     Unit Price     |    Quantity    |       Total Price      |\n";
	cout << "--------------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < 10; i++) {
		cout << "| " << setw(4) << Idmenu[i] << " | "
			<< left << setw(25) << menu[i]
			<< "| RM " << setw(16) << left << fixed << setprecision(2) << pricefood[i]
			<< "| " << setw(13) << right << foodQty[i]
			<< "  | RM " << setw(20) << left << fixed << setprecision(2) << foodSales[i]
			<< "|\n";
	}

	cout << "--------------------------------------------------------------------------------------------------\n";
	cout << "|  ID  |   Drink                  |     Unit Price     |    Quantity    |       Total Price      |\n";
	cout << "|      |                          |   Hot      Cold    |   Hot    Cold  |                        |\n";
	cout << "--------------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < 7; i++) {
		cout << "| " << setw(4) << Idmenu[10 + i] << " | "
			<< left << setw(25) << menu[10 + i]
			<< "| RM " << setw(5) << fixed << setprecision(2) << pricedrinkH[i]
			<< "  RM " << setw(6) << fixed << setprecision(2) << pricedrinkC[i]
			<< "| " << setw(5) << right << drinkHotQuantity[i]
			<< setw(8) << right << drinkColdQuantity[i]
			<< "  | RM " << setw(19) << left << fixed << setprecision(2) << (drinkHotSales[i] + drinkColdSales[i])
			<< " |\n";
	}

	cout << "--------------------------------------------------------------------------------------------------\n";
	cout << "|  ID  |    Add On                |     Unit Price     |    Quantity    |       Total Price      |\n";
	cout << "--------------------------------------------------------------------------------------------------\n";
	for (int i = 17; i <= 19; i++){
		cout << "| " << setw(4) << Idmenu[i] << " | "
			<< left << setw(25) << menu[i]
			<< "| RM " << setw(15) << left << fixed << setprecision(2) << addonPrice[i - 17]
			<< " | " << setw(13) << right << addonQuantity[i - 17]
			<< "  | RM " << setw(20) << left << fixed << setprecision(2) << addonSales[i - 17]
			<< "|\n";
	}

	cout << "--------------------------------------------------------------------------------------------------\n";
	cout << "|                                                                       | Sub Total :RM "
		<< setw(9) << left << fixed << setprecision(2) << grandTotal << "|\n";
	cout << "|                                                                       |                        |\n";
	cout << "--------------------------------------------------------------------------------------------------\n";

	cout << "\nPress ENTER to return to main menu...";
	cin.ignore();
	cin.get();

	displayMainMenu();
}


int main()
{
	displayMainMenu();

	return 0;
}
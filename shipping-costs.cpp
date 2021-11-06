#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

// constants - title header
const char SYMBOLE = '.';
const int HEADER_LENGTH = 62;
const string TITLE = " Calculate Shipping Costs ";
const string doubleNewLine = "\n\n";

// constants - shipping destinations
const double itemFragileFee = 2.00;  // fragile item fee
const char CHOICE_YES = 'Y';
const char CHOICE_NO = 'N';

const double TOTAL_50 = 50.00;
const double TOTAL_100 = 100.00;
const double TOTAL_150 = 150.00;

const string SHIP_USA = "USA";
const double USA_50 = 6.00;     // shipping costs for items < $50.00 - $6.00
const double USA_100 = 9.00;    // shipping costs for items <= $100.00 - $9.00
const double USA_150 = 12.00;   // shipping costs for items <= $150.00 - $12.00
const double USA_OVER = 0.00;   // shipping costs for items > $150.00 - $0.00

const string SHIP_CAN = "CAN";  // canada
const double CAN_50 = 8.00;
const double CAN_100 = 12.00;
const double CAN_150 = 15.00;
const double CAN_OVER = 0.00;

const string SHIP_AUS = "AUS";  // australia
const double AUS_50 = 10.00;
const double AUS_100 = 14.00;
const double AUS_150 = 17.00;
const double AUS_OVER = 0.00;

const string SHIP_MAR = "MAR";  // mars
const double MAR_50 = 150000;
const double MAR_100 = 350000;
const double MAR_150 = 500000;
const double MAR_OVER = 75000;
const double MAR_FRAGILE_FEE = 20000;

// constants - output
const int OUTPUT_LENGTH = HEADER_LENGTH - 11;
const char CURRENCY_SIGN = '$';

// function declaration
void headerGenerator();
void calculateShippingCosts(char itemFragile, double& shippingCost, string itemDestination, double itemTotal);
void outputCosts(string itemName, double shippingCost, string itemDestination, double totalAmount);

int main()
{
    headerGenerator();

    // input - item name
    string itemName = "";
    const string itemMessage = "[>] Please enter the item name (no spaces)";

    cout << setfill(SYMBOLE);
    cout << itemMessage << setw(OUTPUT_LENGTH - itemMessage.length()) << ":";
    cin >> itemName;

    transform(itemName.begin(), itemName.end(), itemName.begin(), ::toupper);

    // input - is the item fragile
    char itemFragile = ' ';
    const string fragileMessage = "[>] Is the item fragile? (y=yes/n=no)";

    cout << fragileMessage << setw(OUTPUT_LENGTH - fragileMessage.length()) << ":";
    cin >> itemFragile;

    itemFragile = toupper(itemFragile);

    // if the input is neither 'Y' nor 'N' output an error message and then exit the program
    if (itemFragile != CHOICE_YES && itemFragile != CHOICE_NO)
    {
        cout << "\nInvalid entry. exiting" << endl;
        cout << "Press any key to continue . . .";
        // pause the program before exiting so that the user can see the error message
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.ignore();
        return 1;  // exit program
    }

    // input - item total amount
    double itemTotal = 0.00;
    const string totalMessage = "[>] PLease enter your item total";

    cout << totalMessage << setw(OUTPUT_LENGTH - totalMessage.length()) << ":";
    cin >> itemTotal;

    // input - item shipping destination
    string itemDestination = "";
    const string destinationMessage = "[>] Please enter destination. (usa/can/aus/mar)";

    cout << destinationMessage << setw(OUTPUT_LENGTH - destinationMessage.length()) << ":";
    cin >> itemDestination;

    // capitalize destination name
    transform(itemDestination.begin(), itemDestination.end(), itemDestination.begin(), ::toupper);

    // calculations
    double shippingCost = 0.0;
    double totalAmount = 0.0;
    calculateShippingCosts(itemFragile, shippingCost, itemDestination, itemTotal);

    // total shipping costs after calculations
    totalAmount = itemTotal + shippingCost; 

    // output to console and file
    outputCosts(itemName, shippingCost, itemDestination, totalAmount);

    cout << "Press any key to continue . . .";
    cin.ignore();

    return 0;
}

void headerGenerator()
{
    int titleLength = TITLE.length();
    int headerHalfLength = (HEADER_LENGTH - titleLength) / 2;

    cout << setfill(SYMBOLE);
    cout << setw(HEADER_LENGTH) << SYMBOLE << endl;
    cout << setw(static_cast<streamsize>(headerHalfLength) + titleLength) << TITLE << setw(headerHalfLength) << SYMBOLE << endl;
    cout << setw(HEADER_LENGTH) << SYMBOLE << doubleNewLine << endl;

    // Reset fill
    cout << setfill(' ');
}

void calculateShippingCosts(char itemFragile, double& shippingCost, string itemDestination, double itemTotal)
{
    if (itemFragile == CHOICE_YES)
        if (itemDestination == SHIP_MAR)
            shippingCost = shippingCost + MAR_FRAGILE_FEE;
        else
            shippingCost = shippingCost + itemFragileFee;

    if (itemDestination == SHIP_USA)  // if USA
    {
        if (itemTotal < TOTAL_50)
        {
            shippingCost = shippingCost + USA_50;  // + $6.00
        }
        else if (itemTotal <= TOTAL_100)
        {
            shippingCost = shippingCost + USA_100;  // + $9.00
        }
        else if (itemTotal <= TOTAL_150)
        {
            shippingCost = shippingCost + USA_150;  // + $12.00
        }
        else  // else if itemTotal is over 150, the shipping fee will be Free
        {
            shippingCost = shippingCost + USA_OVER;  // free - + $0.0
        }
    }
    else if (itemDestination == SHIP_CAN)  // else if CAN
    {
        if (itemTotal < TOTAL_50)
        {
            shippingCost = shippingCost + CAN_50;  // + $8.00
        }
        else if (itemTotal <= TOTAL_100)
        {
            shippingCost = shippingCost + CAN_100;  // + $12.00
        }
        else if (itemTotal <= TOTAL_150)
        {
            shippingCost = shippingCost + CAN_150;  // + $15.00
        }
        else
        {
            shippingCost = shippingCost + CAN_OVER;  // free - + $0.0
        }
    }
    else if (itemDestination == SHIP_AUS)  // else if AUS
    {
        if (itemTotal < TOTAL_50)
        {
            shippingCost = shippingCost + AUS_50;  // + $10.00
        }
        else if (itemTotal <= TOTAL_100)
        {
            shippingCost = shippingCost + AUS_100;  // + $14.00
        }
        else if (itemTotal <= TOTAL_150)
        {
            shippingCost = shippingCost + AUS_150;  // + 17.00
        }
        else
        {
            shippingCost = shippingCost + AUS_OVER;  // free - + $0.0
        }
    }
    else if (itemDestination == SHIP_MAR)  // else if MAR
    {
        if (itemTotal < TOTAL_50)
        {
            shippingCost = shippingCost + MAR_50;  // + $150000.00
        }
        else if (itemTotal <= TOTAL_100)
        {
            shippingCost = shippingCost + MAR_100;  // + $350000.00
        }
        else if (itemTotal <= TOTAL_150)
        {
            shippingCost = shippingCost + MAR_150;  // + 500000.00
        }
        else
        {
            shippingCost = shippingCost + MAR_OVER;  // + $75000.0
        }
    }
    else
    {
        cout << "\nInvalid entry. exiting" << endl;
        cout << "Press any key to continue . . .";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.ignore();
        exit(1);  // exit program
    }
}

// output to console and file
void outputCosts(string itemName, double shippingCost, string itemDestination, double totalAmount)
{
    // declare a file-stream variable
    ofstream fileOut;

    // open a file to write to
    fileOut.open("Order.txt");

    const string outputMessage = "Costs";
    cout << setfill('-');
    fileOut << setfill('-');
    cout << "\n" << left << setw(HEADER_LENGTH) << outputMessage << endl;
    fileOut << "\n" << left << setw(HEADER_LENGTH) << outputMessage << endl;

    cout << fixed << setprecision(2) << setfill(SYMBOLE) << left << endl;
    fileOut << fixed << setprecision(2) << setfill(SYMBOLE) << left << endl;

    const string oItemName = "[+] Your item is";
    cout << setw(OUTPUT_LENGTH) << oItemName << itemName << endl;
    fileOut << setw(OUTPUT_LENGTH) << oItemName << itemName << endl;

    // output format is right justified then left justified
    const string oShippingCost = "[+] Your shipping cost is";
    cout << setw(OUTPUT_LENGTH) << oShippingCost << CURRENCY_SIGN << shippingCost << endl;
    fileOut << setw(OUTPUT_LENGTH) << oShippingCost << CURRENCY_SIGN << shippingCost << endl;

    const string oitemDestination = "[+] You are shipping to";
    cout << setw(OUTPUT_LENGTH) << oitemDestination << itemDestination << endl;
    fileOut << setw(OUTPUT_LENGTH) << oitemDestination << itemDestination << endl;

    const string oItemTotal = "[+] Your total shipping costs are";
    cout << setw(OUTPUT_LENGTH) << oItemTotal << CURRENCY_SIGN << totalAmount << doubleNewLine;
    fileOut << setw(OUTPUT_LENGTH) << oItemTotal << CURRENCY_SIGN << totalAmount << doubleNewLine;

    // outputs Thank you message
    cout << setfill('-');
    fileOut << setfill('-');

    const string oEndMessage = "Thank You !";
    cout << right << setw(HEADER_LENGTH) << oEndMessage << doubleNewLine;
    fileOut << right << setw(HEADER_LENGTH) << oEndMessage << doubleNewLine;
    cin.ignore();

    // close the file stream
    fileOut.close();
}
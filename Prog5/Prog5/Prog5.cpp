//-----------------------------------------------------------------------
// Purpose: This program reads a command and processes:
//
//          1. Add: Makes sure the name does not exist or that the list
//             is full and if not, adds a new seller to the list.
//
//          2. Update: makes sure seller exists and adds the amount 
//             of sales made and the dollars earned.
//
//          3. Output: prints the seller names sales if seller exists
//
//          4. Quit: looks to see who reached the sales goals and ouputs
//             the winners and ends the program.
//
// Input:   Commands Add, Update, Output and Quit
//
// Output:  I wrote the output above more or less
//              
//-----------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
using namespace std;

const int MAX_SELLERS = 5;
const int NOT_FOUND = -1;
const float GOAL_IN_DOLLARS = 50000.0f;
const int GOAL_IN_COMPUTERS = 13;

class Seller
{
private:
   //running total of sales in dollars
   float salestotal;
   //running total of number of lap top computers sold
   int lapTopSold;
   //running total of number of desk top computers sold
   int deskTopSold;
   //running total of number of tablet computers sold
   int tabletSold;
   //name of the seller
   string name;

public:
   //member functions
   //Default constructer, initializes name to 
   //an empty string and all fields to 0.
   Seller()
   {
      name = "";
      salestotal = 0;
      lapTopSold = 0;
      deskTopSold = 0;
      tabletSold = 0;
   }

   //Constructor:
   //Initializes the Seller's name to newname and all other fields to 0.
   //Param: (in)
   Seller(string newname) : Seller()
   {
      name = newname;
   }

   //Returns true if the seller's name is the same as nameToSearch; 
   //false otherwise.
   //Param: (in)
   bool SellerHasName(string nameToSearch) const
   {
      return nameToSearch == name;
   }

   //Returns true if the seller sold at least GOAL_IN_COMPUTERS
   //computers or has a sale amount of at least GOAL_IN_DOLLARS.
   bool WinsPrize() const
   {
      return salestotal >= GOAL_IN_DOLLARS || lapTopSold + deskTopSold
         + tabletSold >= GOAL_IN_COMPUTERS;
   }

   //Adds the money and number of computers to the seller's 
   //accumulated sales total and number of computers sold based 
   //on the computer type. That is, if the computer type is 
   //“DESKTOP” then the desktop field is updated by numComputers, 
   //if the computer type is “LAPTOP” then the laptop field is 
   //updated by numComputers, if the computer type is “TABLET” 
   //then the tablet fields is updated by numComputers.
   //Param: (in, in, in)
   void UpdateSales(float totalDollars, int numComputers,
      string computerType)
   {
      if (computerType == "desktop")
      {
         deskTopSold += numComputers;
      }
      else if (computerType == "laptop")
      {
         lapTopSold += numComputers;
      }
      else if (computerType == "tablet")
      {
         tabletSold += numComputers;
      }
      salestotal += totalDollars;
   }

   // Print the salesperson's name, sales total, and number of 
   // computers sold. Checks for plurality.
   void PrintSales() const
   {
      cout << name << ": $" << salestotal << "; sold ";
      if (lapTopSold == 1)
      {
         cout << lapTopSold << " Laptop, ";
      }
      else
      {
         cout << lapTopSold << " Laptops, ";
      }
      if (deskTopSold == 1)
      {
         cout << deskTopSold << " Desktop and ";
      }
      else
      {
         cout << deskTopSold << " Desktops and ";
      }
      if (tabletSold == 1)
      {
         cout << tabletSold << " Tablet." << endl;
      }
      else
      {
         cout << tabletSold << " Tablets." << endl;
      }
   }
};


class SellerList
{
private:
   int numSellers;   // number of salespeople in the list
   Seller salespeople[MAX_SELLERS];

   //The Find function takes a name as the parameter.
   //It determines whether or not a salesperson with 
   //that name is in the SellerList.If it is, 
   //it returns the index of where the seller is stored.
   //If there is no seller in the list with that name, 
   //it returns - 1. 
   //params (in)
   int Find(string sellerName) const
   {
      for (int i = 0; i < numSellers; i++)
      {
         if (salespeople[i].SellerHasName(sellerName))
         {
            return i;
         }
      }
      return NOT_FOUND;
   }

public:
   //member functions
   //Default constructer, initializes number of sellers to 0.
   SellerList()
   {
      numSellers = 0;
   }

   //The AddSellerFunction adds a seller to the salespeople 
   //array only if there is enough room in the array defined 
   //by MAXSELLERS or if the name is not already in the list
   void AddSellerName()
   {
      string sellerName;
      cin >> sellerName;
      int index = Find(sellerName);
      if (index >= 0)
      {
         cout << sellerName << " is already in the list." << endl;
      }
      else if (numSellers >= MAX_SELLERS)
      {
         cout << sellerName << " not added. List is full." << endl;
      }
      else
      {
         salespeople[numSellers++] = Seller(sellerName);
         cout << sellerName << " is seller "
            << numSellers << "." << endl;
      }
   }

   //Update command.Update the seller with the 
   //given sales and the appropriate number of computers.
   //For this command:  Sellername designates the name 
   //of the sales person; typeOfComputer designates either laptop, 
   //desktop or tablet; total - Dollars designates 
   //the amount in dollars that was sold;/number - of - 
   //Computers - Sold designates the quantity of computers of 
   //this type that were sold.
   void UpdateSellerName()
   {
      string sellerName, typeOfComputer;
      float totalDollars;
      int numberOfComputersSold;
      cin >> sellerName >> typeOfComputer
         >> totalDollars >> numberOfComputersSold;
      for (int i = 0; i < typeOfComputer.length(); i++)
      {
         typeOfComputer[i] = tolower(typeOfComputer[i]);
      }
      int index = Find(sellerName);
      if (index >= 0)
      {
         salespeople[index].UpdateSales
         (totalDollars, numberOfComputersSold, typeOfComputer);
         cout << sellerName << " sold " << numberOfComputersSold
            << " " << typeOfComputer;
         if (numberOfComputersSold > 1)
            cout << " computers for ";
         else if (numberOfComputersSold == 1)
            cout << " computer for ";
         cout << totalDollars << " Dollars." << endl;
      }
      else
         cout << "Cannot update statistics. "
         << sellerName << " is not in the list." << endl;
   }

   //Looks to see if seller exists and if so 
   //prints the computer types and total sold
   //for the seller.
   void OutputSellerName() const
   {
      string sellerName;
      cin >> sellerName;
      int index = Find(sellerName);
      if (index >= 0)
      {
         salespeople[index].PrintSales();
      }
      else
      {
         cout << "Cannot output. " << sellerName
            << " is not in the list." << endl;
      }
   }

   //Looks to see who, if anyone, has reached the sales 
   //goals and prints the names and sales of each winnner.
   //Keeps count to see if there is no winner.
   void OutputWinners() const
   {
      int winCount = 0;
      cout << "The contest is over. The winners are:" << endl;
      for (int i = 0; i < numSellers; i++)
      {
         if (salespeople[i].WinsPrize())
         {
            salespeople[i].PrintSales();
            winCount++;
         }
      }
      if (winCount == 0)
      {
         cout << "There is no winner!" << endl;
      }
   }
};

int main()
{
   SellerList salespeople;

   string command;
   cin >> command;
   while (command != "Quit")
   {
      if (command == "Add")
      {
         salespeople.AddSellerName();
      }
      else if (command == "Update")
      {
         salespeople.UpdateSellerName();
      }
      else if (command == "Output")
      {
         salespeople.OutputSellerName();
      }
      cin >> command;
   }
   salespeople.OutputWinners();
   return 0;
}



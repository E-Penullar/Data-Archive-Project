#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

#include "llist.h"
#include "record.h"

/*****************************************************************
//
//    NAME:       ERIKA PENULLAR
//
//    HOMEWORK:   PROJECT2
//
//    CLASS:      ICS 212
//
//    INSTRUCTOR: RAVI NARAYAN
//
//    DATE:       NOVEMBER 29, 2025
//
//    FILE:       USER_INTERFACE.CPP
//
//    DESCRIPTION:
//        CONTAINS THE MAIN FUNCTION AND PROGRAM OF THE PROJECT
//        , WILL ALLOW USER TO INTERACT WITH LIST OF RECORDS
//
****************************************************************/


using namespace std;

void getAddress(string& address, int length);

void getaddress(string& address, int length)
{
    char c;

    #ifdef DEBUG
    cout << "\n--- DEBUG Function : getaddress ---" << endl;
    cout << "--- Parameters : address = " << address << " ---" << endl;
    cout << "--- Parameters : length = " << length << " ---" << endl;
    #endif

    address.clear();

    cout << "\nEnter Address.\nType ';' after your final input and before you hit ENTER to finish." << endl;

    while (cin.get(c) && c != ';')
    {
        if (address.size() < (unsigned int)length)
        {
            address += c;
        } else {
            cerr << "\nWarning: Input Buffer is Full, Stopping Input..." << endl;
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    char command[9];
    bool running = true;
    char c;

    llist records;

    cout << "Welcome.\n" << endl;
    cout << "Please select an option.\n" << endl;
    cout << "add: add a new record to the database." << endl;
    cout << "printall: print all records in the database." << endl;
    cout << "find: find record(s) with a specific account number." << endl;
    cout << "delete: given an account number, delete existing record(s) from the database." << endl;
    cout << "quit: quit the program." << endl;
    cout << "------------------------------\n" << endl;

    while (running)
    {
        cout << "\n----- Enter Menu Option: -----\n" << endl;

        if (!(cin >> command))
        {
            running = false;
            continue;
        }

        if (strlen(command) <= 4 && strncmp(command, "find", strlen(command)) == 0 && strlen(command) > 0)
        {
            int findNumber, findCount;

            cout << "\n----- Enter Account # to Find: -----\n" << endl;
  
            if (!(cin >> findNumber) || findNumber <= 0)
            {
                cerr << "\n--| Invalid Account #. Must be a Number Greater than 0. Please Try Again. |--\n" << endl;
                while (std::cin.get(c) && c != '\n') {}
                continue;
            }
            while (std::cin.get(c) && c != '\n') {}

            cout << "\n----- Finding Record(s)... -----\n" << endl;

            findCount = records.findRecord(findNumber);

            if (findCount == 0) {
                cout << "\n----- Record Successfully Found -----\n" << endl;
            } else if (findCount == -1) {
                cout << "\n----- Record was Unable to be Retrieved, Try Again -----\n" << endl;
            }
        }
        else if (strlen(command) <= 3 && strncmp(command, "add", strlen(command)) == 0 && strlen(command) > 0)
        {
            struct record newRecord;
            int addCount;

            cout << "\n----- Enter Account # to Add: -----\n" << endl;
            if (!(cin >> newRecord.accountno) || newRecord.accountno <= 0)
            {
                cerr << "\n--- Invalid Account #. Must be a Number Greater than 0. Please Try Again. ---" << endl;
                cin.clear();
                while (std::cin.get(c) && c != '\n') {} 
                continue;
            }
            while (std::cin.get(c) && c != '\n') {}

            cout << "\n--- Enter Account Name: -----" << endl;
            
            cin.getline(newRecord.name, sizeof(newRecord.name));

           if (cin.fail())
           {
               cerr << "\n--- Error reading input, Stopping input... ---" << endl;
               while (std::cin.get(c) && c != '\n') {}
           } else {
               newRecord.name[strcspn(newRecord.name, "\n")] = '\0';

               string tempAddress(newRecord.address);
               getaddress(tempAddress, sizeof(newRecord.address));
             
               strncpy(newRecord.address, tempAddress.c_str(), sizeof(newRecord.address) - 1);
               newRecord.address[sizeof(newRecord.address) - 1] = '\0';      

               cout << "\n--- Adding Record... ---" << endl;

               addCount = records.addRecord(newRecord.accountno, newRecord.name, newRecord.address);
             
               if (addCount == 0) {
                   cout << "\n--- New Record Added Successfully ---" << endl;
               } else if (addCount == -1) {
                   cout << "\n--- New Account was Unable to Be Added ---" << endl;
               }
           }  
        }
        else if (strlen(command) <= 8 && strncmp(command, "printall", strlen(command)) == 0 && strlen(command) > 0)
        {
            cout << "\n----- Printing All Records... -----\n" << endl;
            records.printAllRecords();
            /*cout << records << endl;*/
        }
        else if (strlen(command) <= 6 && strncmp(command, "delete", strlen(command)) == 0 && strlen(command) > 0)
        {
            int deleteNumber, deleteCount;      

            cout << "\n----- Enter Account # to Delete: -----" << endl;

            if (!(cin >> deleteNumber) || deleteNumber <= 0)
            {
                cerr << "\n--| Invalid Account #. Must be a Number Greater than 0. Please Try Again. |--" << endl;
                while (std::cin.get(c) && c != '\n') {}
                continue;
            }
            while (std::cin.get(c) && c != '\n') {}

            cout << "\n----- Deleting Record(s)... -----\n" << endl;

            deleteCount = records.deleteRecord(deleteNumber);

            if (deleteCount == 0) {
                cout << "-----  Record Deleted Successfully -----\n" << endl;
            } else if (deleteCount == -1) {
                cout << "----- Record was Unable to be Deleted, Try Again -----\n" << endl;
            }  
        }
        else if (strlen(command) <= 4 && strncmp(command, "quit", strlen(command)) == 0 && strlen(command) > 0)
        {
            cout << "\n----- Exiting Menu... -----\n" << endl;
            running = false;        
        } else {
            cerr << "\n--| Invalid Input. Please Enter a Menu Option. |--\n" << endl;
        }
    } 
    return 0;
}


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>

#include "llist.h"
#include "record.h"

#define maxAddressLen 44
/*****************************************************************
//
//    NAME:        ERIKA PENULLAR
//
//    HOMEWORK:    PROJECT2
//
//    CLASS:       ICS 212
//
//    INSTRUCTOR:  RAVI NARAYAN
//
//    DATE:        NOVEMBER 29, 2025
//
//    FILE:        LLIST.CPP
//
//    DESCRIPTION: CONTAINS THE FUNCTIONS DEFINED FROM LLIST.H
//    
****************************************************************/

using namespace std;

/*****************************************************************
//
//    CONSTRUCTOR
//
*****************************************************************/

llist::llist()
{
    #ifdef DEBUG
        cout << "\n|--- DEBUG Funcion: llist (readfile) ----|" << endl;
    #endif

    start = NULL;
    strcpy(filename, "Records.txt");
    
    int read = readfile();
    if (read != 0) {
        cerr << "Error reading file: " << filename << endl;
    }
}

/*****************************************************************
//
//    DESTRUCTOR
//
*****************************************************************/

llist::~llist()
{
    #ifdef DEBUG
        cout << "\n|--- DEBUG Funcion: ~llist (writefile) ---|" << endl;
    #endif

    int write = writefile();
    if (write != 0) {
        cerr << "Error writing data to file: " << filename << endl;
    }
    cleanup();   
}

/*****************************************************************
//
//    COPY CONSTRUCTOR
//
*****************************************************************/

llist::llist(const llist& other)
{
    #ifdef DEBUG
        cout << "\n--- DEBUG Funcion: llist (copy constructor) ---|" << endl;
    #endif

    start = NULL;

    strcpy(this->filename, other.filename);

    record* current_other = other.start;
    record* last_new = NULL;

    while (current_other != NULL)
    {
        record* new_node = new record;

        new_node->accountno = current_other->accountno;
        strcpy(new_node->name, current_other->name);
        strcpy(new_node->address, current_other->address);
  
        new_node->next = NULL;

        if (start == NULL)
        {
            start = new_node;
        } else {
            last_new->next = new_node;
        }

        last_new = new_node;
        current_other = current_other->next;
    }
}

/*****************************************************************
//
//    ASSIGNMENT OVERLOAD OPERTATOR
//
*****************************************************************/

llist& llist::operator=(const llist& other)
{
    #ifdef DEBUG
        cout << "\n--- DEBUG Function: operator= (copy assignment) ---|" << endl;
    #endif

    if (this == &other) {
        return *this;
    }

    llist temp(other);

    record* tempStart = start;
    start = temp.start;
    temp.start = tempStart;

    char tempFilename[20];
    strcpy(tempFilename, filename);
    strcpy(filename, temp.filename);
    strcpy(temp.filename, tempFilename);

    return *this;
}

/*****************************************************************
//
//    ALTERNATIVE PRINT-RECORD OPTION
//
*****************************************************************/

ostream& operator<<(ostream& os, const llist& list)
{
    os << "-------- Database Records  --------" << endl;    

    struct record* current = list.start;

    if (current == NULL) {
        os << "The database is empty." << endl;
    } else {
        while (current != NULL)
        {
            os << "Account No: " << current->accountno << endl;
            os << "Name : " << current->name << endl;
            os << "Address : " << endl << current->address << endl; 
            os << "----------------------" << endl;

            current = current->next;
        }
    }
    return os;
}   

/*****************************************************************
//
//    FUNCTION NAME:    addRecord
//
//    DESCRIPTION:      ADDS NEW RECORDS WITH ACCOUNTNO
//                      , NAME, AND ADDRESS TO THE LINKED LIST
//
//    PARAMETERS:       INT UACCOUNTNO : USER'S ACCOUNT NUMBER
//                      CHAR UNAME[] : USER'S ACCOUNT NAME
//                      CHAR UADDRESS[] : USER'S ACCOUNT ADDRESS
//
//    RETURN VALUES:    0 : SUCCESSFUL
//                      -1 : UNSUCCESSFUL
//
*****************************************************************/



int llist::addRecord(int uaccountno, char uname[], char uaddress[])
{
    #ifdef DEBUG
        cout << "\n|--- DEBUG Function: addRecord ---|" << endl;
        cout << "\n|--- DEBUG Parameter: accountno = " << uaccountno << " ---|" << endl;
        cout << "\n|--- DEBUG Parameter: name = \"" << uname << "\" ---|" << endl;
        cout << "\n|--- DEBUG Parameter: address = \"" << uaddress << "\" ---|\n" << endl;
    #endif

    struct record* current = start;
    struct record* previous = NULL;
    int returnVal = 0;

    while (current != NULL && current->accountno < uaccountno)
    {
        previous = current;
        current = current->next;
    }

    if (current != NULL && current->accountno == uaccountno)
    {
        cout << "----- This Account # has already been taken, Try Again -----" << endl;
        returnVal = -1;
    } else {

        struct record* newRecord = new record();

        newRecord->accountno = uaccountno;
        strncpy(newRecord->name, uname, sizeof(newRecord->name) - 1);
        newRecord->name[sizeof(newRecord->name) - 1] = '\0';
        strncpy(newRecord->address, uaddress, sizeof(newRecord->address) - 1);
        newRecord->address[sizeof(newRecord->address) - 1] = '\0';
 
        newRecord->next = NULL;

        if (previous == NULL)
        {
            newRecord->next = start;
            start = newRecord;
        } else {
            newRecord->next = current;
            previous->next = newRecord;
        }
    }

    return returnVal;
}

/*****************************************************************
//
//    FUNCTION NAME:    printAllRecords
//
//    DESCIPTION:       PRINTS ALL RECORDS WITHIN LIST
//
*****************************************************************/

void llist::printAllRecords()
{
    struct record* current = start;
    int count = 0;
    
    #ifdef DEBUG
        cout << "\n|--- DEBUG Function: printAllRecords ---|" << endl;
    #endif

    while (current != NULL)
    {
        count++;
        cout << "-- Record " << count << "--------" << endl;
        cout << "Account #: " << current->accountno << endl;
        cout << "Account Name: " << current->name << endl;
        cout << "Account Address: " << endl << current->address << endl;

        current = current->next;
    }
}

/*****************************************************************
//
//    FUNCTION NAME:    findRecord
//
//    DESCRIPTION:      FINDS A CERTAIN RECORDS WHEN GIVEN AN 
//                      ACCOUNT NUMBER
//
//    PARAMETERS:       INT UACCOUNTNO : USER'S ACCOUNT NUMBER
//
//    RETURN VALUES:    0 : SUCCESSFUL
//                      -1 : UNSUCCESSFUL
//
*****************************************************************/

int llist::findRecord(int uaccountno)
{
    struct record* current = start;
    int returnVal = 0;

    #ifdef DEBUG
        cout << "\n|--- DEBUG Function: findRecord ---|" << endl;
        cout << "\n|--- DEBUG Parameter: accountno = " << uaccountno << " ---|\n" << endl;
    #endif
  
    while (current != NULL && current->accountno < uaccountno) {
        current = current->next;
    }

    if (current != NULL && current->accountno == uaccountno)
    {
        cout << "----- Account Found -----" << endl;
        cout << "Account #: " << uaccountno << endl;
        cout << "Account Name: " << current->name << endl;
        cout << "Account Address: " << current->address << endl;
    } else {
        returnVal = -1;
    }
    return returnVal;
}

/*****************************************************************
//
//    FUNCTION NAME:    deleteRecord
//
//    DESCRIPTION:      DELETES A CERTAIN RECORD WHEN GIVEN AN 
//                      ACCOUNT NUMBER
//
//    PARAMETERS:       INT UACCOUNTNO : USER'S ACCOUNT NUMBER
//
//    RETURN VALUES:    0 : SUCCESSFUL
//                      -1 : UNSUCCESSFUL
//
*****************************************************************/

int llist::deleteRecord(int uaccountno)
{
    struct record* current = start;
    struct record* previous = NULL;
    int returnVal = 0;

    #ifdef DEBUG
        cout << "\n|--- DEBUG Function: deleteRecord ---|" << endl;
        cout << "\n|--- DEBUG Parameter: accountno = " << uaccountno << " ---|\n" << endl;
    #endif

    while (current != NULL && current->accountno < uaccountno)
    {
        previous = current;
        current = current->next;
    }

    if (current != NULL && current->accountno == uaccountno)
    {
        if (previous == NULL)
        {
            start = current->next;
        } else {
            previous->next = current->next;
        }
        delete current;
    } else {
        returnVal = -1;
    }
    return returnVal;
}

/*****************************************************************
//
//    FUNCTION NAME:    writefile
//
//    DESCRIPTION:      WRITES LINKED LIST INFO TO A FILE
//
//    RETURN VALUES:    0 : SUCCESSFUL
//                      -1 : UNSUCCESSFUL    
//
*****************************************************************/

int llist::writefile()
{
    ofstream ofs(filename);
    
    struct record* current = start;
    int returnVal = 0;

    #ifdef DEBUG
        cout << "\n|--- DEBUG Function: writefile ---|" << endl;
        cout << "\n|--- DEBUG Parameter: filename = " << filename << " ---|\n" << endl;
    #endif

    if (!ofs.is_open()) {
        returnVal = -1;
    } else {
        while (current != NULL)
        {
            ofs << current->accountno << std::endl;
            ofs << current->name << std::endl;
            ofs << current->address << std::endl;
            ofs << "----------" << std::endl;

            current = current->next;
        }
        ofs.close();
    }
    return returnVal;
}

/*****************************************************************
//
//    FUNCTION NAME:    readfile
//
//    DESCRIPTION:      READS INFO FROM A FILE TO A LINKED LIST
//
//    RETURN VALUES:    0 : SUCCESSFUL
//                      -1 : UNSUCCESSFUL
//
*****************************************************************/

int llist::readfile()
{
    ifstream ifs(filename);

    struct record* current = NULL;
    struct record* last = NULL;
    int returnVal = 0;
    
    const char *delimiter = "----------";
    char addressBuffer[maxAddressLen + 1];
 
    #ifdef DEBUG
        cout << "\n|--- DEBUG Function: readfile ---|" << endl;;
        cout << "\n|--- DEBUG Parameter: filename = " << filename << " ---|\n" << endl;
    #endif 
    
    if (!ifs.is_open())
    {
        returnVal = -1;
    } else {
        cleanup();

        while (ifs.peek() != EOF)
        {
            current = new struct record;
 
            if (current == NULL)
            {
                returnVal = -1;
                break;
            }
        
            if (!(ifs >> current->accountno))
            {
                delete current;
                break;
            }

            ifs.ignore(1000, '\n');

            if (!ifs.getline(current->name, sizeof(current->name)))
            {
                delete current;
                break;
            }
 
            current->address[0] = '\0';

            while (ifs.getline(addressBuffer, maxAddressLen))
            {
                if (strcmp(addressBuffer, delimiter) == 0) {
                    break;
                }

                if (strlen(current->address) + strlen(addressBuffer) + 2 < sizeof(current->address))
                {
                    strcat(current->address, addressBuffer);
                    strcat(current->address, "\n");
                } else {
                    break;
                }
            }
            
            current->next = NULL;
            if (start == NULL) {
                start = current;
            } else {
                last->next = current;
            }
            last = current;
        }
        ifs.close();
    }
    return returnVal;
}

/*****************************************************************
//
//    FUNCTION NAME:    cleanup
//
//    DESCRIPTION:      CLEANS UP ALL THE INFO LEFT IN THE LIST
//
*****************************************************************/

void llist::cleanup()
{
    struct record* current = start;
    struct record* nextNode;
 
    #ifdef DEBUG
        cout << "\n|--- DEBUG Function: cleanup ---|" << endl;
    #endif

    while (current != NULL)
    {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
    start = NULL;
}


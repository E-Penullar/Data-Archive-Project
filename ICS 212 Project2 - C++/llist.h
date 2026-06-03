#ifndef LLIST_H
#define LLIST_H

#include <string>
#include <iostream>
#include "record.h"

/*****************************************************************
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
//    FILE:        LLIST.H
//   
//    DESCRIPTION: CONTAINS CLASS DEFINITIONS FOR THIS PROJECT
//   
****************************************************************/

using namespace std;

class llist
{
    private:
        record * start;
        char filename[20];
        int readfile();
        int writefile();
        void cleanup();

    public:
        llist();
        llist(char[]);
        llist(const llist&);
        llist& operator=(const llist&);
        friend ostream& operator<<(ostream& os, const llist& list);
        ~llist();
        int addRecord(int ,char [],char []);
        int findRecord(int);
        void printAllRecords();
        int deleteRecord(int);
};

#endif

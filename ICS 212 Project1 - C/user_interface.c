#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "record.h"
#include "database.h"

void getaddress(char [], int);

int debugmode;

void getaddress(char* address, int size)
{
    int index = 0;
    int c;    

    if (debugmode)    
    {
        printf("\n--- DEBUG Function : getaddress ---\n");
        printf("\n--- Parameters : address = \"%s\" (string content) ---\n", address);
        printf("\n--- Parameters : size = %d ---\n\n", size);
    }

    printf("\n----- Enter Address.\nType ';' after your final input and before you hit ENTER to finish. -----\n");

    while ((c = fgetc(stdin)) != EOF && c != ';')
        {
            if(index < size - 1)
            {
                address[index] = (char)c;
                index++;
            } else {
                fprintf(stderr, "\n--| Warning: Input Buffer is Full, Stopping Input... |--\n");
                break;
            }
        }
    address[index] = '\0';
}

int main(int argc, char *argv[])
{
    struct record* start = NULL;

    char command[9];
    bool running = true;   
    int c;

    if (argc > 2)
    {
        fprintf(stderr, "\n--| Error: Too Many Arguments. |--\n\n");
        return 0;
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1], "debug") == 0)
        {
            debugmode = 1;
            printf("\n--- DEBUGMODE ACTIVATED ---\n\n");
        }
        else
        {
            fprintf(stderr, "\n--| Error: Invalid Command-Line Argument. Use 'debug' to Activate Debugmode. |--\n\n");
            return 0;
        }
    }

    readfile(&start, "Records.txt");

    printf("Welcome.\n\n");
    printf("Please select an option.\n\n");
    printf("add: add a new record to the database.\n");
    printf("printall: print all records in the database.\n");
    printf("find: find record(s) with a specific account number.\n");
    printf("delete: given an account number, delete existing record(s) from the database.\n");
    printf("quit: quit the program.\n");

    printf("------------------------------\n\n");

    while(running)
    {
        printf("\n----- Enter Menu Option: -----\n\n");

        if (scanf("%8s", command) != 1)
        {
            running = false;
            continue;
        }

        while((c = getchar()) != '\n' && c != EOF) {}

        if (strlen(command) <= 4 && strncmp(command, "find", strlen(command)) == 0 && strlen(command) > 0)
        {
            int find_number, find_count;

            printf("\n----- Enter Account # to Find: -----\n");
           
            if (scanf("%d", &find_number) != 1 || find_number <= 0)
            {
                fprintf(stderr, "\n--| Invalid Account #. Must be a Number Greater than 0. Please Try Again. |--\n");
                while((c = getchar()) != '\n' && c != EOF) {}
                continue;
            }
            
            while((c = getchar()) != '\n' && c != EOF) {}
            
            printf("\n----- Finding Record(s)... -----\n\n");
            find_count = findRecord(start,find_number);
            
            if (find_count == 0) {
                printf("----- Record Successfully Found -----\n\n");        
            }
            else if (find_count == -1) {
                printf("----- Record was Unable to be Retrieved, Try Again -----\n\n");
            }

        }
        else if (strlen(command) <= 3 && strncmp(command, "add", strlen(command)) == 0 && strlen(command) > 0)
        {
            struct record new_record;
            int result;            

            printf("\n----- Enter Account # to Add: -----\n");
         
            if (scanf("%d", &new_record.accountno) != 1 || new_record.accountno <= 0)
            {
                fprintf(stderr, "\n--| Invalid Account #. Must be a Number Greater than 0. Please Try Again. |--\n");  
                while((c = getchar()) != '\n' && c != EOF) {}
                continue;
            }

            while((c = getchar()) != '\n' && c != EOF) {}

            printf("\n----- Enter Account Name: -----\n");
            if (fgets(new_record.name, sizeof(new_record.name), stdin) == NULL)
            {
                fprintf(stderr, "\n--| Error reading input, Stopping input... |--\n");
                continue;
            }

            new_record.name[strcspn(new_record.name, "\n")] = 0;

            getaddress(new_record.address, sizeof(new_record.address));

            printf("\n----- Adding Record... -----\n\n");
            result = addRecord(&start, new_record.accountno, new_record.name, new_record.address);

            if (result == 0)
            {
                 printf("----- New Record Added Successfully -----\n\n");
            } else {
                 printf("----- New Account was Unable to Be Added -----\n\n");
            }
        }
        else if (strlen(command) <= 8 && strncmp(command, "printall", strlen(command)) == 0 && strlen(command) > 0) 
        {
            printf("\n----- Printing All Records... -----\n\n");
            if (start == NULL) {
                printf("----- There are no Records Saved -----\n\n");
            } else {
                printAllRecords(start);
            }
        }
        else if (strlen(command) <= 6 && strncmp(command, "delete", strlen(command)) == 0 && strlen(command) > 0)
        {
            int delete_number, delete_count;
         
            printf("\n----- Enter Account # to Delete: -----\n");

            if (scanf("%d", &delete_number) != 1 || delete_number <= 0)
            {
                fprintf(stderr, "\n--| Invalid Account #. Must be a Number Greater than 0. Please Try Again. |--\n");
                while((c = getchar()) != '\n' && c != EOF) {}
                continue;
            }
            while((c = getchar()) != '\n' && c != EOF) {}

            printf("\n----- Deleting Record(s)... -----\n\n");
            delete_count = deleteRecord(&start, delete_number);

            if (delete_count == 0) {
                printf("-----  Record Deleted Successfully -----\n\n");
            }
            else if (delete_count == -1) {
                printf("----- Record was Unable to be Deleted, Try Again -----\n\n");
            }
        }
        else if (strlen(command) <= 4 && strncmp(command, "quit", strlen(command)) == 0 && strlen(command) > 0)
        {
            printf("\n----- Exiting Menu... -----\n\n");
  
            writefile(start, "Records.txt");

            running = false;
        } else {
            fprintf(stderr, "\n--| Invalid Input. Please Enter a Menu Option. |--\n\n");
        }
    }
    
    cleanup(&start);

    return 0;
}


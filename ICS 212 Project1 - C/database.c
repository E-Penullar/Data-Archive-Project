#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "record.h"
#include "database.h"

#define maxAddressLen 44 

extern int debugmode;

int addRecord (struct record ** start, int uaccountno, char* uname, char* uaddress)
{
    struct record *current = *start;
    struct record *previous = NULL;
    struct record *temp;
    int returnVal;

    if (debugmode)
    {
        printf("\n|--- DEBUG Function: addRecord ---|\n");
        printf("\n|--- DEBUG Parameter: accountno = %d ---|\n", uaccountno);
        printf("\n|--- DEBUG Parameter: name = \"%s\" (string content) ---|\n", uname);
        printf("\n|--- DEBUG Parameter: address = \"%s\" (string content) ---|\n\n", uaddress);
    }

    while (current != NULL && current->accountno < uaccountno)
    {
        previous = current;
        current = current->next;
    }

    if (current != NULL && current->accountno == uaccountno) { 
         printf("----- This Account # has already been taken, Try Again -----\n"); 
         returnVal = -1;
    }
    else 
    {
        temp = (struct record *)malloc(sizeof(struct record));

        temp->accountno = uaccountno;
        strncpy(temp->name, uname, sizeof(temp->name) - 1);
        temp->name[sizeof(temp->name) - 1] = '\0';
        strncpy(temp->address, uaddress, sizeof(temp->address) - 1);
        temp->address[sizeof(temp->address) - 1] = '\0';

        if (previous == NULL)
        {
            temp->next = *start;
            *start = temp;
        }
        else
        {
            temp->next = current;
            previous->next = temp;
        }
    }
    return returnVal;
}

void printAllRecords(struct record * start)
{
    struct record *current = start;
    struct record *previous = NULL;
    int count = 0;

    if (debugmode)
    {
        printf("\n|--- DEBUG Function: printAllRecords ---|\n");
    }
  
    while (current != NULL)
    {
        count++;
        printf("-- Record %d --------\n", count);
        printf("Account #: %d\n", current->accountno);
        printf("Account Name: %s\n", current->name);
        printf("Account Address: \n%s\n\n", current->address);

        previous = current;
        current = current->next;
    }

}

int findRecord (struct record * start, int uaccountno)
{
    struct record *current = start;
    int returnVal = 0;

    if (debugmode)
    {
        printf("\n|--- DEBUG Function: findRecord ---|\n");
        printf("\n|--- DEBUG Parameter: accountno = %d ---|\n\n", uaccountno);   
    }

    while (current != NULL && current->accountno < uaccountno)
    {
        current = current->next;
    }
   
    if (current != NULL && current->accountno == uaccountno)
    {
        printf("----- Account Found -----\n");
        printf("Account #: %d\n", uaccountno);
        printf("Account Name: %s\n", current->name);
        printf("Account Address: %s\n", current->address);
        returnVal = 0;
    }
    else {
        returnVal = -1;
    }

    return returnVal;
}

int deleteRecord(struct record ** start, int uaccountno)
{
    struct record *current = *start;
    struct record *previous = NULL;
    int returnVal = -1;

    if (debugmode)
    {
        printf("\n|--- DEBUG Function: deleteRecord ---|\n");
        printf("\n|--- DEBUG Parameter: accountno = %d ---|\n\n", uaccountno);
    }
   
    while (current != NULL && current->accountno < uaccountno)
    {
        previous = current;
        current = current->next;
    }

    if (current != NULL && current->accountno == uaccountno)
    {
        if (previous == NULL) {
            *start = current->next;
        }
        else {
            previous->next = current->next;
        }
        free(current);
        returnVal = 0;
    }
    return returnVal;
}
int writefile(struct record *start, char filename[])
{
    FILE *fp;
    int returnVal;
    struct record *current = start;

    if (debugmode)
    {   
        printf("\n|--- DEBUG Function: writefile ---|\n");
        printf("\n|--- DEBUG Parameter: filename[]  = %s ---|\n\n", filename);
    }

    fp = fopen(filename, "w");

    if (fp == NULL) {
        returnVal = -1;
    }
    else
    {
        returnVal = 0;

        while (current != NULL)
        {
            fprintf(fp, "%d\n", current->accountno);
            fprintf(fp, "%s\n", current->name);
            fprintf(fp, "%s\n", current->address);
            fprintf(fp, "%s\n", "----------");       
 
            current = current->next;
    
        } 
        fclose(fp);
    }
    return returnVal;
}

int readfile(struct record **start, char filename[])
{
    FILE *fp;
    int returnVal, c;
    struct record *current = NULL;
    struct record *last = NULL;
    char *delimiter = "----------";
    char addressBuffer[maxAddressLen];

    if (debugmode)
    {
        printf("\n|--- DEBUG Function: readfile ---|\n");
        printf("\n|--- DEBUG Parameter: filename[] = %s ---|\n\n", filename);
    }

    fp = fopen(filename, "r");

    if (fp == NULL) {
        returnVal = -1;
    }
    else
    {
        returnVal = 0;

        while (1)
        {
            current = (struct record*)malloc(sizeof(struct record));

            if (current == NULL)
            {
                returnVal = 0;
                break;
            }
            if (fscanf(fp, "%d", &current->accountno) != 1)
            {
                free(current);
                break;
            }
            while ((c = fgetc(fp)) != '\n' && c != EOF);
            if (fgets(current->name, sizeof(current->name), fp) == NULL)
            {
                free(current);
                break;
            }

            current->name[strcspn(current->name, "\n")] = 0;

            current->address[0] = '\0';
            
            while (fgets(addressBuffer, maxAddressLen, fp) != NULL)
            {
                addressBuffer[strcspn(addressBuffer, "\n")] = '\0';

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
            if (*start == NULL) {
                *start = current;
            } else {
                last->next = current;
            }
            last = current;
        }

    fclose(fp);
    }
    return returnVal;
}

void cleanup(struct record **start) 
{
    struct record *current = *start;
    
    if (debugmode)
    {   
        printf("\n|--- DEBUG Function: cleanup ---|\n");
    }
    
    while (current != NULL)
    {   
        free(current);       
 
        current = current->next;
    }
    *start = NULL;
}

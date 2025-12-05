#include "sortedList.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define PROMPT " > "

static void printHelpInfo(void)
{
    printf("You are in interactive mode, enter:\n"
           "0 - to quit\n"
           "1 - to add new value to the sorted list\n"
           "2 - to remove value from the list\n"
           "3 - to print the list\n"
           "4 - to print help info\n");
}

/*
 * Skip spaces in string and return first non space character.
 */
static char skipSpaces(char* buf)
{
    while (isspace(*buf))
        buf++;

    return *buf;
}

/*
 * Returns pointer to statically allocated buffer,
 * that contains user input line.
 */
static char* getInput(void)
{
    static char buf[BUFSIZ];
    printf(PROMPT);
    return fgets(buf, sizeof(buf), stdin);
}

/*
 * Return true if number was read successfully.
 * Return false when user sent EOF or decided to quit.
 */
static bool getNum(int* num)
{
    printf("Enter a number or 'q' to quit:\n");
    char* data = NULL;
    while ((data = getInput()) != NULL) {
        if (skipSpaces(data) == 'q')
            return false;
        else if (sscanf(data, "%d", num) == 1)
            break;
        else
            printf("Not a valid number, please, try again or enter 'q' to quit.\n");
    }

    // User could send EOF
    return data != NULL;
}

/*
 * Interactively add value to the list.
 */
static void addValue(SortedList* list)
{
    int num = 0;
    if (getNum(&num))
        if (sortedListInsert(list, num))
            printf("Added the value successfully.\n");
}

/*
 * Interactively remove value from the list.
 */
static void removeValue(SortedList* list)
{
    if (isSortedListEmpty(list)) {
        printf("The list is already empty, aborting command...\n");
        return;
    }
    printf("Indexes start from 0.\n");

    int idx = 0;
    while (getNum(&idx)) {
        if (sortedListRemoveIndex(list, idx)) {
            printf("Removed successfully.\n");
            break;
        } else {
            printf("Index out of range, please, try again.\n");
        }
    }
}

/*
 * Operates with the given list.
 * Return false when user choose to quit.
 * Return true otherwise.
 */
static bool interactiveSortedList(SortedList* list, char command)
{
    switch (command) {
    case '0':
        return false;
    case '1':
        addValue(list);
        break;
    case '2':
        removeValue(list);
        break;
    case '3':
        sortedListPrint(list);
        break;
    case '4':
        printHelpInfo();
        break;
    default:
        printf("Undefined command, try again.\n");
    }
    return true;
}

int main(int argc, char** argv)
{
#ifdef DEBUG
    if (argc >= 2) {
        if (argc > 2 || (argc == 2 && strcmp("--test", argv[1]) != 0)) {
            fprintf(stderr, "Usage: %s [--test]\n", argv[0]);
            return 1;
        }
        return launchSortedListTesting();
    }
#else
    // unused parameters
    ((void)argc);
    ((void)argv);
#endif

    SortedList* pList = sortedListAlloc();
    if (pList == NULL)
        return 1;

    printHelpInfo();
    while (1) {
        // If user sent EOF or decided to quit - break.
        printf("Enter a command.\n");
        char* data = getInput();
        if (data == NULL)
            break;
        // Returns false, when user wants to quit.
        if (!interactiveSortedList(pList, skipSpaces(data)))
            break;
    }

    sortedListFree(&pList);
    return 0;
}
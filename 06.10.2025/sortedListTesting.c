#ifdef DEBUG

#include "sortedList.h"
#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

#define testFprintf(stream, ...) do { \
    fprintf(stream, "[Line: %d] ", __LINE__);\
    fprintf(stream, __VA_ARGS__);\
} while(0)

#define testPrintln(msg) testFprintf(stdout, "%s\n", msg)
#define testErrPrintln(msg, testResult) do { \
        testFprintf(stderr, "ERROR: %s\n", msg);\
        testResult = 1;\
    } while (0)

#define testSortedListExpectIndex(list, i, expect, testResult) do {\
    int value;\
    if (!sortedListGet(&list, i, &value)) \
            testErrPrintln("sortedListGet() - failed", testResult);\
    else if (value != expect) { \
            testFprintf(stderr,\
                "ERROR: testSortedListExpectIndex() - %d(value) != %d(expected)\n", \
                value, expect);\
            testResult = 1;\
    } \
} while(0)
#define testSortedListFree(list, testResult) do { \
    testPrintln("Cleaning the list");\
    sortedListFree(&list);\
    if (!isSortedListEmpty(&list))\
        testErrPrintln("isSortedListEmpty() - failed", testResult);\
} while(0)

#define testSortedListInit(msg, list) do {\
        testPrintln(msg); \
        sortedListInit(&list);\
} while(0)

#define testSortedListInsert(list, value, testResult) do { \
        if (!sortedListInsert(&list, value))\
            testErrPrintln("sortedListInsert() - failed", testResult);\
} while(0)

int launchSortedListTesting()
{
    testPrintln("Started tests");
    int testResult = 0;
    SortedList list;

    testSortedListInit("Inserting values in order", list);
    for(int i = 0; i < 10; i++)
        testSortedListInsert(list, i, testResult);

    for(int i = 0; i < 10; i++) {
        testSortedListExpectIndex(list, i, i, testResult);
    }

    if(!sortedListRemoveValue(&list, 5))
        testErrPrintln("sortedListRemoveValue() - failed", testResult);
    if(!sortedListRemoveValue(&list, 2))
        testErrPrintln("sortedListRemoveValue() - failed", testResult);

    testSortedListExpectIndex(list, 5, 7, testResult);

    testSortedListInsert(list, 2, testResult);
    testSortedListExpectIndex(list, 2, 2, testResult);
    
    testSortedListFree(list, testResult);

    testSortedListInit("Test inserting values in random order.", list);
    const int values[] = {5, 4, 1, 6, -2, 14};
    const int sortedValues[] = {-2, 1, 4, 5, 6, 14};
    const int valuesSize = ARRAY_SIZE(values);
    for (int i = 0; i < valuesSize; i++)
        testSortedListInsert(list, values[i], testResult);
    for (int i = 0; i < valuesSize; i++)
        testSortedListExpectIndex(list, i, sortedValues[i], testResult);

    if (sortedListRemoveIndex(&list, -1))
        testErrPrintln("sortedListRemoveIndex() - success", testResult);
    if (sortedListRemoveIndex(&list, 999))
        testErrPrintln("sortedListRemoveIndex() - success", testResult);
    if (sortedListRemoveValue(&list, 999))
        testErrPrintln("sortedListRemoveValue() - success", testResult);
    if (sortedListRemoveValue(&list, 0))
        testErrPrintln("sortedListRemoveValue() - success", testResult);

    testPrintln("Removing values from the list randomly");
    // index and value testcases
    const int valuesExpect[][2] = { {3, 6}, {2, 6}, {1, 6}, {1, 14}};
    for (int i = 0; i < valuesSize; i++) {
        if(!sortedListRemoveValue(&list, values[i]))
            testErrPrintln("sortedListRemoveValue() - failed", testResult);
        if (ARRAY_SIZE(valuesExpect) > (unsigned long long)i)
            testSortedListExpectIndex(list, valuesExpect[i][0], valuesExpect[i][1], testResult);
    }
    if (!isSortedListEmpty(&list))
        testErrPrintln("isSortedListEmpty() - failed", testResult);

    testSortedListFree(list, testResult);
    if (sortedListRemoveValue(&list, 0))
        testErrPrintln("sortedListRemoveValue() - success", testResult);
    int val = -1;
    if(sortedListGet(&list, 0, &val))
        testErrPrintln("sortedListGet() - success", testResult);
    
    testFprintf(stdout, "Ended testing with code %d.\n", testResult);
    return testResult;
}

#endif
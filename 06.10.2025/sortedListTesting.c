#ifdef DEBUG

#include "sortedList.h"
#include <stdarg.h>
#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

void testFprintf(int line, FILE* stream, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(stream, "[Line: %d] ", line);
    vfprintf(stream, fmt, args);
    va_end(args);
}

void testErrPrintln(int line, const char* msg, int* pTestResult)
{
    testFprintf(line, stderr, "ERROR: %s\n", msg);
    *pTestResult = 1;
}

void testPrintln(int line, const char* msg)
{
    testFprintf(line, stdout, "%s\n", msg);
}

void testSortedListExpectIndex(int line, SortedList* pList, int i, int expect, int* pTestResult)
{
    int value;
    if (!sortedListGet(pList, i, &value))
        testErrPrintln(line, "sortedListGet() - failed", pTestResult);
    else if (value != expect) {
        testFprintf(line, stderr,
            "ERROR: testSortedListExpectIndex() - %d(value) != %d(expected)\n",
            value, expect);
        *pTestResult = 1;
    }
}

void testSortedListFree(int line, SortedList** ppList, int* pTestResult)
{
    testPrintln(line, "Cleaning the list");
    sortedListFree(ppList);
    if (*ppList != NULL)
        testErrPrintln(line, "sortedListFree() - failed", pTestResult);
}

void testSortedListInsert(int line, SortedList* pList, int value, int* pTestResult)
{
    if (!sortedListInsert(pList, value))
        testErrPrintln(line, "sortedListInsert() - failed", pTestResult);
}

int launchSortedListTesting()
{
    testPrintln(__LINE__, "Started tests");
    int testResult = 0;
    SortedList* pList = sortedListAlloc();
    if (pList == NULL) {
        testErrPrintln(__LINE__, "Failed to allocated sorted list", &testResult);
        return 1;
    }

    for (int i = 0; i < 10; i++)
        testSortedListInsert(__LINE__, pList, i, &testResult);

    for (int i = 0; i < 10; i++) {
        testSortedListExpectIndex(__LINE__, pList, i, i, &testResult);
    }

    if (!sortedListRemoveValue(pList, 5))
        testErrPrintln(__LINE__, "sortedListRemoveValue() - failed", &testResult);
    if (!sortedListRemoveValue(pList, 2))
        testErrPrintln(__LINE__, "sortedListRemoveValue() - failed", &testResult);

    testSortedListExpectIndex(__LINE__, pList, 5, 7, &testResult);

    testSortedListInsert(__LINE__, pList, 2, &testResult);
    testSortedListExpectIndex(__LINE__, pList, 2, 2, &testResult);

    testSortedListFree(__LINE__, &pList, &testResult);

    pList = sortedListAlloc();
    if (pList == NULL) {
        testErrPrintln(__LINE__, "Failed to allocated sorted list", &testResult);
        return 1;
    }
    const int values[] = { 5, 4, 1, 6, -2, 14 };
    const int sortedValues[] = { -2, 1, 4, 5, 6, 14 };
    const int valuesSize = ARRAY_SIZE(values);
    for (int i = 0; i < valuesSize; i++)
        testSortedListInsert(__LINE__, pList, values[i], &testResult);
    for (int i = 0; i < valuesSize; i++)
        testSortedListExpectIndex(__LINE__, pList, i, sortedValues[i], &testResult);

    if (sortedListRemoveIndex(pList, -1))
        testErrPrintln(__LINE__, "sortedListRemoveIndex() - failed", &testResult);
    if (sortedListRemoveIndex(pList, 999))
        testErrPrintln(__LINE__, "sortedListRemoveIndex() - failed", &testResult);
    if (sortedListRemoveValue(pList, 999))
        testErrPrintln(__LINE__, "sortedListRemoveValue() - failed", &testResult);
    if (sortedListRemoveValue(pList, 0))
        testErrPrintln(__LINE__, "sortedListRemoveValue() - failed", &testResult);

    testPrintln(__LINE__, "Removing values from the list randomly");
    // index and value testcases
    const int valuesExpect[][2] = { { 3, 6 }, { 2, 6 }, { 1, 6 }, { 1, 14 } };
    for (int i = 0; i < valuesSize; i++) {
        if (!sortedListRemoveValue(pList, values[i]))
            testErrPrintln(__LINE__, "sortedListRemoveValue() - failed", &testResult);
        if (ARRAY_SIZE(valuesExpect) > (unsigned long long)i)
            testSortedListExpectIndex(__LINE__, pList, valuesExpect[i][0], valuesExpect[i][1], &testResult);
    }
    if (!isSortedListEmpty(pList))
        testErrPrintln(__LINE__, "isSortedListEmpty() - failed", &testResult);

    testSortedListFree(__LINE__, &pList, &testResult);
    if (sortedListRemoveValue(pList, 0))
        testErrPrintln(__LINE__, "sortedListRemoveValue() - failed", &testResult);
    int val = -1;
    if (sortedListGet(pList, 0, &val))
        testErrPrintln(__LINE__, "sortedListGet() - failed", &testResult);

    testFprintf(__LINE__, stdout, "Ended testing with code %d.\n", testResult);
    return testResult;
}

#endif
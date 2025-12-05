#ifdef DEBUG

#include "sortedList.h"
#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define testFprintf(stream, ...)                  \
    do {                                          \
        fprintf(stream, "[Line: %d] ", __LINE__); \
        fprintf(stream, __VA_ARGS__);             \
    } while (0)

#define testPrintln(msg) testFprintf(stdout, "%s\n", msg)
#define testErrPrintln(msg, testResult)          \
    do {                                         \
        testFprintf(stderr, "ERROR: %s\n", msg); \
        testResult = 1;                          \
    } while (0)

#define testSortedListExpectIndex(pList, i, expect, testResult)                     \
    do {                                                                            \
        int value;                                                                  \
        if (!sortedListGet(pList, i, &value))                                       \
            testErrPrintln("sortedListGet() - failed", testResult);                 \
        else if (value != expect) {                                                 \
            testFprintf(stderr,                                                     \
                "ERROR: testSortedListExpectIndex() - %d(value) != %d(expected)\n", \
                value, expect);                                                     \
            testResult = 1;                                                         \
        }                                                                           \
    } while (0)
#define testSortedListFree(pList, testResult)                        \
    do {                                                             \
        testPrintln("Cleaning the list");                            \
        sortedListFree(&pList);                                      \
        if (pList != NULL)                                           \
            testErrPrintln("sortedListFree() - failed", testResult); \
    } while (0)

#define testSortedListInit(msg, pList) \
    do {                               \
        testPrintln(msg);              \
        sortedListInit(pList);         \
    } while (0)

#define testSortedListInsert(pList, value, testResult)                 \
    do {                                                               \
        if (!sortedListInsert(pList, value))                           \
            testErrPrintln("sortedListInsert() - failed", testResult); \
    } while (0)

int launchSortedListTesting()
{
    testPrintln("Started tests");
    int testResult = 0;
    SortedList* pList = sortedListAlloc();
    if (pList == NULL) {
        testErrPrintln("Failed to allocated sorted list", testResult);
        return 1;
    }

    for (int i = 0; i < 10; i++)
        testSortedListInsert(pList, i, testResult);

    for (int i = 0; i < 10; i++) {
        testSortedListExpectIndex(pList, i, i, testResult);
    }

    if (!sortedListRemoveValue(pList, 5))
        testErrPrintln("sortedListRemoveValue() - failed", testResult);
    if (!sortedListRemoveValue(pList, 2))
        testErrPrintln("sortedListRemoveValue() - failed", testResult);

    testSortedListExpectIndex(pList, 5, 7, testResult);

    testSortedListInsert(pList, 2, testResult);
    testSortedListExpectIndex(pList, 2, 2, testResult);

    testSortedListFree(pList, testResult);

    pList = sortedListAlloc();
    if (pList == NULL) {
        testErrPrintln("Failed to allocated sorted list", testResult);
        return 1;
    }
    const int values[] = { 5, 4, 1, 6, -2, 14 };
    const int sortedValues[] = { -2, 1, 4, 5, 6, 14 };
    const int valuesSize = ARRAY_SIZE(values);
    for (int i = 0; i < valuesSize; i++)
        testSortedListInsert(pList, values[i], testResult);
    for (int i = 0; i < valuesSize; i++)
        testSortedListExpectIndex(pList, i, sortedValues[i], testResult);

    if (sortedListRemoveIndex(pList, -1))
        testErrPrintln("sortedListRemoveIndex() - success", testResult);
    if (sortedListRemoveIndex(pList, 999))
        testErrPrintln("sortedListRemoveIndex() - success", testResult);
    if (sortedListRemoveValue(pList, 999))
        testErrPrintln("sortedListRemoveValue() - success", testResult);
    if (sortedListRemoveValue(pList, 0))
        testErrPrintln("sortedListRemoveValue() - success", testResult);

    testPrintln("Removing values from the list randomly");
    // index and value testcases
    const int valuesExpect[][2] = { { 3, 6 }, { 2, 6 }, { 1, 6 }, { 1, 14 } };
    for (int i = 0; i < valuesSize; i++) {
        if (!sortedListRemoveValue(pList, values[i]))
            testErrPrintln("sortedListRemoveValue() - failed", testResult);
        if (ARRAY_SIZE(valuesExpect) > (unsigned long long)i)
            testSortedListExpectIndex(pList, valuesExpect[i][0], valuesExpect[i][1], testResult);
    }
    if (!isSortedListEmpty(pList))
        testErrPrintln("isSortedListEmpty() - failed", testResult);

    testSortedListFree(pList, testResult);
    if (sortedListRemoveValue(pList, 0))
        testErrPrintln("sortedListRemoveValue() - success", testResult);
    int val = -1;
    if (sortedListGet(pList, 0, &val))
        testErrPrintln("sortedListGet() - success", testResult);

    testFprintf(stdout, "Ended testing with code %d.\n", testResult);
    return testResult;
}

#endif
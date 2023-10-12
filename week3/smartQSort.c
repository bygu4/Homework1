#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define TEST_FAILED -1
#define BAD_ALLOCATION 1
#define RAND_RANGE 20000

void scanArray(int* const array, const size_t sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; ++i)
    {
        scanf_s("%d", &array[i]);
    }
}

void swap(int* const number1, int* const number2)
{
    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

int partition(int* const array, const int start, const int end, bool* const isSorted)
{
    int pointer = start + 1;
    while (array[pointer - 1] == array[pointer] && pointer + 1 < end)
    {
        ++pointer;
    }
    if (array[pointer - 1] > array[pointer])
    {
        *isSorted = false;
        --pointer;
    }
    int pivot = array[pointer];

    for (int i = pointer; i < end; ++i)
    {
        if (array[i] < pivot)
        {
            swap(&array[i], &array[pointer]);
            *isSorted = false;
            ++pointer;
        }
        if (isSorted && array[i - 1] > array[i])
        {
            *isSorted = false;
        }
    }
    return pointer;
}

void quicksort(int* const array, const int start, const int end)
{
    const size_t sizeOfArray = end - start;
    if (sizeOfArray <= 1)
    {
        return;
    }

    bool isSorted = true;
    int pointer = partition(array, start, end, &isSorted);

    if (isSorted)
    {
        return;
    }
    quicksort(array, start, pointer);
    quicksort(array, pointer, end);
}

int findMostCommonElement(const int* const array, const size_t sizeOfArray)
{
    int mostCommonElement = NULL;
    int maxNumberOfEntries = 0;
    int previousElement = NULL;
    int count = 0;
    for (int i = 0; i < sizeOfArray; ++i)
    {
        ++count;
        if (array[i] != previousElement)
        {
            previousElement = array[i];
            count = 1;
        }
        if (count > maxNumberOfEntries)
        {
            maxNumberOfEntries = count;
            mostCommonElement = array[i];
        }
    }
    return mostCommonElement;
}

int* createTestArray(const size_t sizeOfArray)
{
    int* array = (int*)calloc(sizeOfArray, sizeof(int));
    if (array == NULL)
    {
        return NULL;
    }
    srand(time(NULL));
    for (int i = 0; i < sizeOfArray; ++i)
    {
        array[i] = rand() % RAND_RANGE - RAND_RANGE / 2;
    }
    return array;
}

bool arraysAreEqual(const int* const array1, const int* const array2, const size_t sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; ++i)
    {
        if (array1[i] != array2[i])
        {
            return false;
        }
    }
    return true;
}

bool arrayIsSorted(const int* const array, const size_t sizeOfArray)
{
    for (int i = 1; i < sizeOfArray; ++i)
    {
        if (array[i - 1] > array[i])
        {
            return false;
        }
    }
    return true;
}

char* testForPartition()
{
    int array1[10] = { 5, 6, 1, 2, 3, 4, 7, 8, 9, 10 };
    int expectedArray1[10] = { 5, 1, 2, 3, 4, 6, 7, 8, 9, 10 };
    bool isSorted = true;
    int pointer = partition(array1, 0, 10, &isSorted);
    bool testOneIsPassed = pointer == 5 && !isSorted && arraysAreEqual(array1, expectedArray1, 10);
    if (!testOneIsPassed)
    {
        return "Test one has failed";
    }

    int array2[5] = { 1, 1, 1, 1, 1 };
    int expectedArray2[5] = { 1, 1, 1, 1, 1 };
    isSorted = true;
    pointer = partition(array2, 0, 5, &isSorted);
    bool testTwoIsPassed = pointer == 4 && isSorted && arraysAreEqual(array2, expectedArray2, 5);
    if (!testTwoIsPassed)
    {
        return "Test two has failed";
    }

    int array3[5] = { 15, 0, 0, 0, 0 };
    int expectedArray3[5] = { 0, 0, 0, 0, 15 };
    isSorted = true;
    pointer = partition(array3, 0, 5, &isSorted);
    bool testThreeIsPassed = pointer == 4 && !isSorted && arraysAreEqual(array3, expectedArray3, 5);
    if (!testThreeIsPassed)
    {
        return "Test three has failed";
    }

    return "All tests are passed";
}

bool testForQuicksortSupport(int* const array, const int* const expectedArray, const size_t sizeOfArray)
{
    quicksort(array, 0, sizeOfArray);
    return arraysAreEqual(array, expectedArray, sizeOfArray);
}

char* testForQuicksort()
{
    int array1[20] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10 };
    int expectedArray1[20] = { -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6 ,7, 8, 9 };
    bool testOneIsPassed = testForQuicksortSupport(array1, expectedArray1, 20);
    if (!testOneIsPassed)
    {
        return "Test one has failed";
    }

    int array2[] = { 0 };
    int expectedArray2[] = { 0 };
    bool testTwoIsPassed = testForQuicksortSupport(array2, expectedArray2, 0);
    if (!testTwoIsPassed)
    {
        return "Test two has failed";
    }

    int array3[10] = { 2, 2, 2, 2, 2, 4, 4, 4, 4, 4 };
    int expectedArray3[10] = { 2, 2, 2, 2, 2, 4, 4, 4, 4, 4 };
    bool testThreeIsPassed = testForQuicksortSupport(array3, expectedArray3, 10);
    if (!testThreeIsPassed)
    {
        return "Test three has failed";
    }

    const size_t sizeOfTestArray = 10000;
    int* testArray = createTestArray(sizeOfTestArray);
    if (testArray == NULL)
    {
        return "Bad allocation";
    }
    quicksort(testArray, 0, sizeOfTestArray);
    bool testFourIsPassed = arrayIsSorted(testArray, sizeOfTestArray);
    free(testArray);
    if (!testFourIsPassed)
    {
        return "Test four has failed";
    }

    return "All tests are passed";
}

char* testForFindMostCommonElement()
{
    int array1[5] = { 2, 2, 2, 2, 2 };
    int mostCommonElement = findMostCommonElement(array1, 5);
    bool testOneIsPassed = mostCommonElement == 2;
    if (!testOneIsPassed)
    {
        return "Test one has failed";
    }

    int array2[6] = { 1, 2, 3, 4, 5, 6 };
    mostCommonElement = findMostCommonElement(array2, 6);
    bool testTwoIsPassed = mostCommonElement == 1;
    if (!testTwoIsPassed)
    {
        return "Test two has failed";
    }

    int array3[] = { NULL };
    mostCommonElement = findMostCommonElement(array3, 0);
    bool testThreeIsPassed = mostCommonElement == NULL;
    if (!testThreeIsPassed)
    {
        return "Test three has failed";
    }

    int array4[7] = { -1, -1, -1, 3, 3, 3, 3 };
    mostCommonElement = findMostCommonElement(array4, 7);
    bool testFourIsPassed = mostCommonElement == 3;
    if (!testFourIsPassed)
    {
        return "Test four has failed";
    }

    return "All tests are passed";
}

bool stringsAreEqual(const char* const string1, const char* const string2)
{
    size_t size1 = strlen(string1);
    size_t size2 = strlen(string2);
    if (size1 != size2)
    {
        return false;
    }
    for (int i = 0; i < size1; ++i)
    {
        if (string1[i] != string2[i])
        {
            return false;
        }
    }
    return true;
}

char* stringSum(const char* const string1, const char* const string2)
{
    size_t size1 = strlen(string1);
    size_t size2 = strlen(string2);
    char* newString = (char*)calloc(size1 + size2 + 1, sizeof(char));
    if (newString == NULL)
    {
        return newString;
    }
    for (int i = 0; i < size1; ++i)
    {
        newString[i] = string1[i];
    }

    for (int i = 0; i < size2; ++i)
    {
        newString[size1 + i] = string2[i];
    }
    return newString;
}

char* test()
{
    char* test1 = testForPartition();
    if (!stringsAreEqual(test1, "All tests are passed"))
    {
        char* output = stringSum(test1, " in testForPartition");
        return output;
    }

    char* test2 = testForQuicksort();
    if (!stringsAreEqual(test2, "All tests are passed"))
    {
        char* output = stringSum(test2, " in testForQuicksort");
        return output;
    }

    char* test3 = testForFindMostCommonElement();
    if (!stringsAreEqual(test3, "All tests are passed"))
    {
        char* output = stringSum(test3, " in testForFindMostCommonElement");
        return output;
    }

    return "All tests are passed";
}

int main()
{
    char* testOutput = test();
    if (!stringsAreEqual(testOutput, "All tests are passed"))
    {
        printf("%s", testOutput);
        free(testOutput);
        return TEST_FAILED;
    }

    int sizeOfArray = 0;
    printf("Enter a size of array: ");
    scanf_s("%d", &sizeOfArray);
    int* inputArray = (int*)calloc(sizeOfArray, sizeof(int));
    if (inputArray == NULL)
    {
        printf("An error occured");
        return BAD_ALLOCATION;
    }
    printf("Enter an array: ");
    scanArray(inputArray, sizeOfArray);

    quicksort(inputArray, 0, sizeOfArray);

    int mostCommonElement = findMostCommonElement(inputArray, sizeOfArray);
    printf("\nThe most common element in array: %d", mostCommonElement);
    free(inputArray);
}
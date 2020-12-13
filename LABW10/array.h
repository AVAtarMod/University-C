#ifndef ARRAY
#define ARRAY

/*         Abbreviation:
    ar = array
    ln = number elements (length of array)
    minN = minimal number
    maxN = maximal number
    arRes = array for result

    fsNum = first number
 */

using std::cout;

int getLenghtUser();
int getLenghtRandom(int minN = 5, int maxN = 10);
int getIndexUser(const int lnArray, const char *reason);
int getElementUser(const char *reason);

int *generateFromUser(int *ar, int ln);
int *generateRandom(int *ar, int ln, int minN = -25, int maxN = 25);
void print(const int *ar, const int ln);

int searchElement(const int *ar, const int ln, const int number);
int searchMinMaxElement(const int *ar, int ln, bool *comparator(int fsNum, int secondNumber));
int searchMinMaxElementWithConditions(const int *ar, int ln, bool *comparator(int fsNum, int secondNumber), bool *condition(int number));
int *searchElements(const int *ar, int *arRes, const int ln, const int number);

int *elementsAppropriateConditions(int *ar, int *arRes, int ln, bool *condition(int number));

int *deleteElement(int *ar, int *arRes, int ln, int index);
int *deleteCoincidences(int *ar, int *arRes, int ln, int element);
//Return new array, use pointer
int *pasteElement(int *ar, int ln, int index, int element);

bool isMax(const int a, const int b);
bool isMin(const int a, const int b);
bool isOdd(const int number);
bool isEven(const int number);

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void task8();
void task9();
void task10();
void task11();
void task12();
void task13();
void task14();

#endif // ARRAY

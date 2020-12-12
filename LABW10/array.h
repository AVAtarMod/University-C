#ifndef ARRAY
#define ARRAY

/*         Abbreviation:
    ar = array
    nE = number elements
    minN = minimal number
    maxN = maximal number
    arRes = array for result

    fsNum = first number
 */

using std::cout;

int getLenghtUser();

int *generateFromUser(int *ar, int nE);
int *generateRandom(int *ar, int nE, int minN, int maxN);
void print(const int *ar, const int nE);

int searchElement(const int *ar, const int nE, const int number);
int searchMinMaxElement(const int *ar, int nE, bool *comparator(int fsNum, int secondNumber));
int searchMinMaxElementWithConditions(const int *ar, int nE, bool *comparator(int fsNum, int secondNumber), bool *condition(int number));
int *searchElements(const int *ar, int *arRes, const int nE, const int number);

int *elementsAppropriateConditions(int *ar, int *arRes, int nE, bool *condition(int number));

int *deleteElement(int *ar, int *arRes, int nE, int index);
int *deleteCoincidences(int *ar, int *arRes, int nE, int element);
int *pasteElement(int *ar, int *arRes, int nE, int index, int element);

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

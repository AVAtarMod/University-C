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
int getIndexUser(const int lnArray, const char *reason = "");
int getElementUser(const char *reason = "");

void generateFromUser(int *ar, int ln);
void generateRandom(int *ar, int ln, int minN = -25, int maxN = 25);
void print(const int *ar, const int ln, const char *text = "", const int offset = 0);

int indexElement(const int *ar, const int ln, const int number);
int indexMinMaxElement(const int *ar, int ln, bool comparator(int, int));
int indexMinMaxElementWithConditions(const int *ar, int ln, bool comparator(int, int), bool condition(int));

//Возвращает массив с длиной в 1 элементе.
int *searchIndexElements(const int *ar, const int ln, const int number);

int *elementsRelevantConditions(int *ar, int ln, bool condition(int));

//Возвращает массив с длиной в 1 элементе.
void deleteElements(int **array, int &numberElements, int element, int offset);
void deleteElement(int **array, int &numberElements, int element, int offset);

void pasteElement(int **array, int &numberElements, int index, int element);

bool isAMax(const int a, const int b);
bool isAMin(const int a, const int b);
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

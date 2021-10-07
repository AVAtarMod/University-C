// LABWORK1sec.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


//int main()
//{
//    return 0;
//}

//#include "pch.h"
#include "stdio.h"
#include "conio.h"
int main() {
    int age;
    printf("Input your age: ");
    scanf_s("%d", &age);
    printf("Hello, human! Your age is %d.\nArtificial Intelligence is immortal!)))", age);
    //_getch();
    return 0;
}

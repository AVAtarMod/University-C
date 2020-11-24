#include <cstdio>
#include <clocale>
int main(){
	setlocale(LC_ALL, "Russian");
	// Инициализация переменных, указание на использование стандартного
	// пространства имен
	using namespace std;
	int bool_, char_, wchar_t_, int_,short_int_, long_int_, long_long_int_, float_, double_, long_double_;
	printf("\n\n\n");
	// Следующий код выводит размеры типов данных
	bool_ = sizeof(bool);
	printf("Размер boolean (bool) = %d\n",bool_);

	char_ = sizeof(char);
	printf("Размер char = %d\n",char_);

	wchar_t_ = sizeof(wchar_t);
	printf("Размер wchar_t = %d\n",wchar_t_);

	int_ = sizeof(int);
	printf("Размер int = %d\n",int_);

	short_int_ = sizeof(short int);
	printf("Размер short int = %d\n",short_int_);

	long_int_ = sizeof(long int);
	printf("Размер long int = %d\n",long_int_);

	long_long_int_ = sizeof(long long int);
	printf("Размер long long int = %d\n",long_long_int_);

	float_ = sizeof(float);
	printf("Размер float = %d\n",float_);

	double_ = sizeof(double);
	printf("Размер double = %d\n",double_);

	long_double_ = sizeof(long double);
	printf("Размер long double = %d\n",long_double_);

}
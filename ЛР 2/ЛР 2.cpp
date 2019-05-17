// ЛР 2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS

#include "pch.h"
#include <iostream>
#include <string>
#include "ЛР 2.h"


using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	static int N, choice;
	static double result, E;

	cout << "Выберите способ вычисления функции" << endl;
	cout << "1) Задать точность (Е)" << endl;
	cout << "2) Вычислить сумму первых N членов" << endl;
	cout << "3) Вычислить точное значение sin X" << endl;
	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		countE();
		break;
	case 2:
		countN();
		break;
	case 3:
		normal();
		break;
	default:
		break;
	}

}

void normal() {
	static double RES, X;
	cout << "Введите X" << endl;
	scanf("%lf", &X);

	_asm{
		finit;
		fld X;
		fsin;
		fstp RES;
	}
	cout.precision(15);
	cout<<RES;
}

void countE() {
	static double RES, X, E;

	cout << "Введите E" << endl;
	scanf("%lf", &E);

	cout << "Введите X" << endl;
	scanf("%lf", &X);

	RES = X;

	_asm {
		push ecx;
		finit;

	INIT:fld X;
		fld1;
		fld1;		// (-1)^n
		fld1;		// последнее число факториала
		fld X;		// Х
		fld X;		// последний вычисленный член

		// Умножить на -1
		fxch st(3);
		fchs;
		fxch st(3);


	CALCULATE:
		// Умножить верхнюю часть на Хкв
		fmul st(0), st(1);
		fmul st(0), st(1);

		// Разделить верхнюю часть на нижнюю
		fxch st(2);
		fadd st(0), st(4);
		fxch st(2);
		fdiv st(0), st(2);

		fxch st(2);
		fadd st(0), st(4);
		fxch st(2);
		fdiv st(0), st(2);

		fmul st(0), st(3);

		//Добавление к результату
		fld1;
		fmul st(0), st(1);
		fld RES;
		fadd;
		fstp RES;

		//Работа с точностью
		fld1;
		fmul st(0), st(1);
		fcomp E;
		fstsw ax;
		sahf;
		jae _OUT;


		//fld1;
		//fmul st(0), st(6);	// Копирование предыдущего члена наверх стека
		//fld1;
		//fmul st(0), st(2);	// Копирование текущего члена наверз стека
		//fsub;				// Вычисление разности
		//fabs;				// Вычисление разницы
		//fcomp E;
		//fstsw ax;
		//sahf;
		//jbe _OUT;
		//fxch st(5);			// Удаление старого члена и замена его на новый
		//fdiv st(0), st(0);
		//fmul st(0), st(5);

		loop CALCULATE;

	_OUT: pop ecx;
	}
	cout.precision(15);
	cout << RES;
}

void countN()
{
	int N;
	static double RES, X;

	cout << "Введите N" << endl;
	scanf("%d", &N);

	cout << "Введите X" << endl;
	scanf("%lf", &X);

	RES = X;

	__asm {
		push ecx;
		finit;

	INIT:fld1;
		fld1;		// (-1)^n
		fld1;		// последнее число факториала
		fld X;		// Х
		fld X;		// последний вычисленный член

		mov ecx, N;
		dec ecx;

		// Умножить на -1
		fxch st(3);
		fchs;
		fxch st(3);


	CALCULATE:


		push ecx;
		// Умножить верхнюю часть на Хкв
		fmul st(0), st(1);
		fmul st(0), st(1);

		// Разделить верхнюю часть на нижнюю
		fxch st(2);
		fadd st(0), st(4);
		fxch st(2);
		fdiv st(0), st(2);

		fxch st(2);
		fadd st(0), st(4);
		fxch st(2);
		fdiv st(0), st(2);

		fmul st(0), st(3);

		//Добавление к результату
		fld1;
		fmul st(0), st(1);
		fld RES;
		fadd;
		fstp RES;
		pop ecx;
		loop CALCULATE;

		pop ecx;
	}
	cout.precision(15);
	cout << RES;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

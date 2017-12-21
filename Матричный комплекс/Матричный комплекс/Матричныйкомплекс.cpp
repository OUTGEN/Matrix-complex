#include "stdafx.h"
#include "iostream"
#include "string"
#include"iomanip"
#include "sstream"
#include "math.h"
#include "fstream"
#include "vector"
#include "windows.h"

using namespace std;

bool element(string str) {//проверка на ввод элемента матрицы
	for (int i = 0; i < str.length(); i++) {
		if (!isdigit(str[i]) && str[i] != '-'&&str[i] != '.') {
			return false;
		}
	}
	return true;
}

ofstream f("matrix.txt");

class MATRIX {
protected:
	double **mat;//двумерный массив(будующая матрица)
	int row, column;//кол-во строк и столбцов
public:

	MATRIX(int r, int c) {
		row = r; column = c;
		mat = new double*[row];
		for (int i = 0; i < row; i++) {
			mat[i] = new double[column];
		}
	}

	MATRIX(const MATRIX& x) {//конструктор копирования
		row = x.row; column = x.column;
		mat = new double*[row];
		for (int i = 0; i < row; i++) {
			mat[i] = new double[column];
		}
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				mat[i][j] = x.mat[i][j];
			}
		}
	}

	MATRIX() {
		ifstream in("download.txt");
		if (in.is_open()) {
			int count = 0;//число символов в файле
			int temp;

			while (!in.eof()) {
				in >> temp;//считываем символы в пустоту
				count++;
			}

			in.seekg(0, ios::beg);
			in.clear();//восстановление потока

			int countspace = 0;//кол-во пробелов в строке
			char symbol;
			while (!in.eof()) {//подсчёт пробелов в одной строке
				in.get(symbol);
				if (symbol == ' ') {
					countspace++;
				}
				if (symbol == '\n') {
					break;
				}
			}

			in.seekg(0, ios::beg);
			in.clear();
			row = count / (countspace + 1);
			column = countspace + 1;

			mat = new double*[row];
			for (int i = 0; i < row; i++) {
				mat[i] = new double[column];
			}

			for (int i = 0; i < row; i++) {
				for (int j = 0; j < column; j++) {
					in >> mat[i][j];
				}
			}

		}
		else {
			cout << "File is not open,try again later\n";
		}
		in.close();
	}

	int getrow() { return row; }

	int getcolumn() { return column; }

	double **getmat() { return mat; }

	void setrow(int r) { row = r; }

	void setcolumn(int c) { column = c; }

	void setmat(double **p) {//присваивание внешней матрицы нашему классу
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				mat[i][j] = p[i][j];
			}
		}
	}

	void setmat() {//заполнение матрицы от руки

		mat = new double*[row];
		for (int i = 0; i < row; i++) {
			mat[i] = new double[column];
		}

		for (int i = 0; i < row; i++) {//заполнение массива нулями для красоты
			for (int j = 0; j < column; j++) {
				mat[i][j] = 0;
			}
		}
		string temp;
		for (int i = 0; i<row; i++) {
			for (int j = 0; j < column; j++) {
				cout << "\tPAGE FOR MANUAL ENTRY OF THE MATRIX\n\n";
				showmat();
				cout << "Enter the element with index[" << i << "][" << j << "]: ";
				cin >> temp;
				while (!element(temp)) {
					system("color CE");
					cout << "YOU PUT WRONG ITEM,TRY AGAIN";
					Sleep(1500);
					system("cls");
					system("color 0F");
					cout << "\tPAGE FOR MANUAL ENTRY OF THE MATRIX\n\n";
					showmat();
					cout << "Enter the element with index[" << i << "][" << j << "]: ";
					cin >> temp;
				}
				mat[i][j] = stod(temp);
				std::system("cls");
			}
		}
	}

	void showmat() {//вывод матрицы на экран
		int max_length_of_element = 1;
		string s;//переменная,в которую запишется число
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				ostringstream ost;//объект,в который посимвольно запишем число
				ost << mat[i][j];//непосредственно запись
				s = ost.str();//перенос всё в нашу строку
				if (s.length() > max_length_of_element) {
					max_length_of_element = s.length();
				}
			}
		}

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				cout << setw(max_length_of_element) << mat[i][j] << " ";
			}
			cout << endl;
		}
	}

	void uploadinfo() {//выгрузка для последующей загрузки(отформатированная для программы)
		ofstream out("download.txt");
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				if (j != column - 1) {
					out << mat[i][j] << " ";
				}
				else {
					out << mat[i][j];
				}
			}
			if (i != row - 1) {
				out << "\n";
			}
		}
		out.close();
	}

	void upload() {// выгрузка информации для отчётности
		int max_length_of_element = 1;
		string s;//переменная,в которую запишется число
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				ostringstream ost;//объект,в который посимвольно запишем число
				ost << mat[i][j];//непосредственно запись
				s = ost.str();//перенос всё в нашу строку
				if (s.length() > max_length_of_element) {
					max_length_of_element = s.length();
				}
			}
		}

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				f << setw(max_length_of_element) << mat[i][j] << " ";
			}
			f << endl;
		}
	}

};

class matoperation :public MATRIX {
public:

	matoperation(int r, int c) :MATRIX(r, c) {};//все значения передаются в базовый конструктор

	matoperation(const matoperation& x) :MATRIX(x) {};//конструктор копирования

	matoperation() :MATRIX() {};

	double determinant(double **x, int m) {//вычисление определителя матрицы(матрица и её порядок)
		if (m == 1) {//порядок=1
			return x[0][0];
		}
		else if (m == 2) {//порядок=2
			return (x[0][0] * x[1][1] - x[1][0] * x[0][1]);
		}
		else if (m>2) {//при порядке большем 2
			double **t;
			double det = 0;
			int a, b;//номер строки и столбца во внутренней матрице
			t = new double*[m - 1];
			for (int i = 0; i < m - 1; i++) {
				t[i] = new double[m - 1];
			}
			//вычисление будет происходить методом разложения по 1 строке
			for (int i = 0; i < m; i++) {//проход по элементам 1 строки, которые будут умножаться на свои миноры
				a = 0;
				for (int j = 1; j < m; j++) {//построчный проход во внутренней матрице,начало с единицы,так как раскладываем по 1 строке
					b = 0;
					for (int k = 0; k < m; k++) {//проход по элементам строки во внутренней матрице
						if (k != i) {//проверка на то,чтобы наш элемент не был равен элементу первой строки. При подсчете минора вычеркивается столбец
							t[a][b] = x[j][k];//создание внутренней матрицы
							b++;
						}
					}
					a++;
				}
				det += pow(-1, i + 2)*x[0][i] * determinant(t, m - 1);//знак*элемент строки*минор элемента
			}
			return det;
		}

	}

	matoperation operator~() {//обратная матрица

		if (row != column) {
			cout << "You can get inverse only if you have square matrix" << endl;
			return *this;
		}
		int order = row;
		if (order == 0) {
			cout << "You must using matrix with bigger size than this\n";
			return *this;
		}
		double det = determinant(mat, order);
		if (det == 0) {
			cout << "Determinant=0,searching inverse matrix are impossible\n";
			return *this;
		}
		matoperation ob(row, column);
		int z, detmin;//мнимая единица,определитель минора
		int r = 0, c = 0;//строка и столбец подматрицы
		double **minor;//матрица минора
		minor = new double*[order - 1];
		for (int i = 0; i < order - 1; i++) {
			minor[i] = new double[order - 1];
		}

		for (int i = 0; i < order; i++) {//проход по строкам основной матрицы
			for (int j = 0; j < order; j++) {//проход по столбцам основной матрицы
				r = 0;
				for (int a = 0; a < order; a++) {//проход по строкам подматрицы
					c = 0;
					for (int b = 0; b < order; b++) {//проход по столбцам минора
						if (i == a) {
							if (a == order - 1) {//если мы находимся в последней строке подматрицы
								break;
							}
							a++;
						}
						if (j != b) {
							minor[r][c] = mat[a][b];
							c++;
						}
					}
					r++;
				}
				z = pow(-1, i + j);//вычиление мнимой единицы
				detmin = determinant(minor, order - 1);
				ob.mat[j][i] = z*detmin / det;//элемент результирующей матрицы
			}
		}

		return ob;
	}

	matoperation operator!() {//перегрузка унарной операции для транспонирования
		matoperation temp(column, row);
		for (int i = 0; i < column; i++) {
			for (int j = 0; j < row; j++) {
				temp.mat[i][j] = mat[j][i];
			}
		}
		return temp;
	}

	matoperation operator*(double z) {//перегрузка умножения матрицы на число
		matoperation temp(row, column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				temp.mat[i][j] = 0;
				temp.mat[i][j] = mat[i][j] * z;
			}
		}
		return temp;
	}

	friend matoperation operator*(double, matoperation);//прототип функции для перегрузки умножения числа на матрицу

	friend matoperation operator*(matoperation, matoperation);//прототип функции для перегрузки матрицы на матрицу

	friend matoperation operator+(matoperation, matoperation);//прототип функции для сложения матриц

	friend matoperation operator-(matoperation, matoperation);//прототип функции для вычитания матриц

};

matoperation operator*(double z, matoperation ob) {//перегрузка на перемножение числа на матрицу
	matoperation temp(ob.row, ob.column);
	for (int i = 0; i < ob.row; i++) {
		for (int j = 0; j < ob.column; j++) {
			temp.mat[i][j] = 0;
			temp.mat[i][j] = ob.mat[i][j] * z;
		}
	}
	return temp;
}

matoperation operator*(matoperation x, matoperation y) {//перегрузка на перемножение двух матриц
	matoperation temp(x.row, y.column);
	for (int i = 0; i < x.row; i++) {
		for (int j = 0; j < y.column; j++) {
			temp.mat[i][j] = 0;
			for (int k = 0; k < x.column; k++) {
				temp.mat[i][j] += (x.mat[i][k] * y.mat[k][j]);
			}
		}
	}
	return temp;
}

matoperation operator+(matoperation x, matoperation y) {//перегрузка на сложение матриц
	matoperation temp(x.row, x.column);
	for (int i = 0; i < x.row; i++) {
		for (int j = 0; j < x.column; j++) {
			temp.mat[i][j] = x.mat[i][j] + y.mat[i][j];
		}
	}
	return temp;
}

matoperation operator-(matoperation x, matoperation y) {//перегрузка на вычитание матриц
	matoperation temp(x.row, x.column);
	for (int i = 0; i < x.row; i++) {
		for (int j = 0; j < x.column; j++) {
			temp.mat[i][j] = x.mat[i][j] - y.mat[i][j];
		}
	}
	return temp;
}

//прототипы функций
bool number(string);//проверка на число
matoperation manually();//ручное заполнение матрицы
void show_menu();
void info();
void select_command(int, matoperation&, int*);//меню программы
bool square_matrix(matoperation);//проверка на квадратную матрицу
void determinant_theory();
void transpose_theory();
void inverse_theory();
void addition_theory();
void subtraction_theory();
void multiplication_theory();

int main()
{
	matoperation initial;//исходная матрица
	string com;
	int command, counter = 1;//команда меню
	f << "\t\tFULL REPORT ABOUT YOUR ACTIONS\n\n"
		<< "\tAction number:" << counter
		<< "\n***Download matrix from file***"
		<< "\nYour initial matrix at this moment\n";
	initial.upload();
	f << "______________________________________\n\n";
	while (true)
	{
		show_menu();
		cin >> com;
		while (!number(com)) {
			system("color CE");
			cout << "YOU PUT WRONG ITEM,TRY AGAIN";
			Sleep(1500);
			show_menu();
			cin >> com;
		}
		command = stoi(com);
		select_command(command, initial, &counter);
	}
	std::system("pause");
	return 0;
}

bool number(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

matoperation manually() {//ручное заполнение матрицы
	cout << "\tPAGE ADDITIONS MATRICES";
	bool range = false;//переменная для проверки диапазона количества строк и столбцов
	string row, column;
	int r, c;
	cout << "\n\nEnter numbers of rows:";
	cin >> row;
	while (range == false) {
		while (!number(row)) {
			cout << "Please,put the integer in the range from 2 to 20: ";
			system("color CE");
			Sleep(1000);
			system("color 0F");
			cin >> row;
		}
		r = stoi(row);//перевод из строки в число
		if (r >= 2 && r <= 20) {
			range = true;
		}
		else {
			cout << "Please,put the integer in the range from 2 to 20: ";
			system("color CE");
			Sleep(1000);
			system("color 0F");
			cin >> row;
		}
	}
	range = false;//обнуление переменной,чтобы продолжить проверять на диапозон столбцов
	cout << "Enter numbers of columns:";
	cin >> column;
	while (range == false) {
		while (!number(column)) {
			cout << "Please,put the integer in the range from 2 to 20: ";
			system("color CE");
			Sleep(1000);
			system("color 0F");
			cin >> column;
		}
		c = stoi(column);
		if (c >= 2 && c <= 20) {
			range = true;
		}
		else {
			cout << "Please,put the integer in the range from 2 to 20: ";
			system("color CE");
			Sleep(1000);
			system("color 0F");
			cin >> column;
		}
	}
	matoperation temp(r, c);
	temp.setmat();
	return temp;
}

void show_menu() {//вывод главного меню программы
	system("cls");
	system("color 0E");
	cout << "\t\t***MAIN MENU***\n\n\tBelow is a list with available command\n\n\n1-Download matrix from file\n2-Initialize matrix manually"
		<< "\n\n3-Calculate determinant of matrix\n4-Transpose matrix\n5-Inverse matrix"
		<< "\n\n6-Matrix addition\n7-Matrix subtraction\n8-Matrix multiplication"
		<< "\n\n9-Show initial matrix\n10-Show info\n11-Exit\n--->Select command:";
}

void select_command(int command, matoperation &ob, int* count) {//меню,из которого вызываются подфункции
	system("cls");
	system("color 0F");
	switch (command)
	{
	case 1://инициализация матрицы из файла
	{
		cout << "\tPAGE ADDITIONS MATRICES";
		matoperation temp;
		ob = temp;
		cout << "\n\nCongrate,you add new matrix,now it is initial matrix\n";
		ob.showmat();
		*count = *count + 1;
		f << "\tAction number:" << *count
			<< "\n***Download matrix from file***"
			<< "\nYour initial matrix at this moment\n";
		ob.upload();
		f << "______________________________________\n\n";
		system("pause");
		break;
	}
	case 2://инициализация матрицы с клавиатуры
	{
		ob = manually();
		system("cls");
		cout << "\tPAGE ADDITIONS MATRICES";
		cout << "\n\nCongrate,you add new matrix,now it is initial matrix\n";
		ob.showmat();
		*count = *count + 1;
		f << "\tAction number:" << *count
			<< "\n***Initialize matrix manually***"
			<< "\nYour initial matrix at this moment\n";
		ob.upload();
		f << "______________________________________\n\n";
		system("pause");
		break;
	}
	case 3://вывод определителя матрицы
		determinant_theory();
		ob.showmat();
		if (square_matrix(ob)) {
			cout << "\nDeterminant of this matrix = " << ob.determinant(ob.getmat(), ob.getrow()) << endl;
			cout << "\nYour initial matrix remains unchanged.\n\n";
			*count = *count + 1;
			f << "\tAction number:" << *count
				<< "\n***Search determinant***"
				<< "\nDeterminant of this matrix = " << ob.determinant(ob.getmat(), ob.getrow())
				<< "\nYour initial matrix at this moment\n";
			ob.upload();
			f << "______________________________________\n\n";
		}
		else {
			cout << "\nYou can not get the determinant,because this matrix is not square."
				<< "\nYour initial matrix remains unchanged.\nIf you want to see a determinant you must change matrix in the second menu item.\n\n";;
		}
		system("pause");
		break;
	case 4:
	{
		transpose_theory();
		cout << "\nYour matrix before transposition\n";
		ob.showmat();
		cout << "\nYour matrix after transposition\n";
		ob = !ob;
		ob.showmat();
		cout << "\nYour initial matrix has been changing on last matrix\n\n";
		*count = *count + 1;
		f << "\tAction number:" << *count
			<< "\n***Matrix transpose***"
			<< "\nYour initial matrix at this moment\n";
		ob.upload();
		f << "______________________________________\n\n";
		system("pause");
		break;
	}
	case 5:
	{
		inverse_theory();
		cout << "\nYour initial matrix\n";
		ob.showmat();
		if (square_matrix(ob)) {
			cout << "\nYour inverse matrix\n";
			ob = ~ob;
			ob.showmat();
			cout << "\nYour initial matrix has been changing on last matrix\n\n";
			*count = *count + 1;
			f << "\tAction number:" << *count
				<< "\n***Matrix inverse***"
				<< "\nYour initial matrix at this moment\n";
			ob.upload();
			f << "______________________________________\n\n";
		}
		else {
			cout << "\nYou can not inverse, because you haven't square matrix\n\n";
		}
		system("pause");
		break;
	}
	case 6:
	{
		addition_theory();
		cout << "Your initial matrix below\n";
		ob.showmat();
		cout << "Please,add second matrix\n";
		system("pause");
		matoperation temp = manually();
		if (ob.getrow() != temp.getrow() || ob.getcolumn() != temp.getcolumn())
		{
			system("color CE");
			cout << "YOU CAN NOT ADDITION MATRIX WITH DIFFERENT SIZE";
			Sleep(1500);
		}
		else {
			cout << "Result of addition matrix1\n";
			*count = *count + 1;
			f << "\tAction number:" << *count
				<< "\n***Matrix addition***";
			f << "\nResult of addition matrix1\n";
			ob.upload();
			ob.showmat();
			cout << "\nWith matrix2\n";
			f << "\nWith matrix2\n";
			temp.upload();
			temp.showmat();
			cout << "\nIt is matrix3\n\n";
			f << "\nIt is matrix3(now it's initial matrix)\n\n";
			ob = ob + temp;
			ob.upload();
			ob.showmat();
			cout << "Now it,s initial matrix!\n";
			f << "______________________________________\n\n";
			system("pause");
		}
		break;
	}
	case 7:
	{
		subtraction_theory();
		cout << "Your initial matrix below\n";
		ob.showmat();
		cout << "Please,add second matrix\n";
		system("pause");
		matoperation temp = manually();
		if (ob.getrow() != temp.getrow() || ob.getcolumn() != temp.getcolumn())
		{
			system("color CE");
			cout << "YOU CAN NOT SUBTRACTION MATRIX WITH DIFFERENT SIZE";
			Sleep(1500);
		}
		else {
			cout << "Result of subtraction matrix1\n";
			*count = *count + 1;
			f << "\tAction number:" << *count
				<< "\n***Matrix subtraction***";
			f << "\nResult of subtraction matrix1\n";
			ob.upload();
			ob.showmat();
			cout << "\nWith matrix2\n";
			f << "\nWith matrix2\n";
			temp.upload();
			temp.showmat();
			cout << "\nIt is matrix3\n\n";
			f << "\nIt is matrix3(now it's initial matrix)\n\n";
			ob = ob - temp;
			ob.upload();
			ob.showmat();
			cout << "Now it,s initial matrix!\n";
			f << "______________________________________\n\n";
			system("pause");
		}
		break;
	}
	case 8:
	{
		multiplication_theory();
		cout << "Your initial matrix below\n";
		ob.showmat();
		cout << "Please,add second matrix\n";
		system("pause");
		matoperation temp = manually();
		if (ob.getrow() != temp.getcolumn() || ob.getcolumn() != temp.getrow())
		{
			system("color CE");
			cout << "YOU CAN NOT MULTIPLICATION MATRIX WITH INCORRECT DATA";
			Sleep(1500);
		}
		else {
			cout << "Result of multiplication matrix1\n";
			*count = *count + 1;
			f << "\tAction number:" << *count
				<< "\n***Matrix multiplication***";
			f << "\nResult of multiplication matrix1\n";
			ob.upload();
			ob.showmat();
			cout << "\nWith matrix2\n";
			f << "\nWith matrix2\n";
			temp.upload();
			temp.showmat();
			cout << "\nIt is matrix3\n\n";
			f << "\nIt is matrix3(now it's initial matrix)\n\n";
			ob = ob * temp;
			ob.upload();
			ob.showmat();
			cout << "Now it,s initial matrix!\n";
			f << "______________________________________\n\n";
			system("pause");
		}
		break;
	}
	case 9:
		cout << "\tPAGE FOR DISPLAYING THE INITIAL MATRIX\n\n";
		ob.showmat();
		system("pause");
		break;
	case 10:
		info();
		break;
	case 11:
		ob.uploadinfo();
		cout << "Ok,your matrix was saving. Next time you can using him.";
		Sleep(2000);
		f.close();
		exit(0);
		break;
	default:
		system("color CE");
		cout << "This command does'n exist,please select available command";
		Sleep(1500);
	}
}

bool square_matrix(matoperation temp) {//проверка на квадратную матрицу
	if (temp.getrow() == temp.getcolumn()) {
		return true;
	}
	else {
		return false;
	}
}

void determinant_theory() {
	cout << "\t\tPAGE MATRIX INFO\n\n\t*Short theory about determinant.*"
		<< "\nDeterminant is the main property of matrix.\nIt's similar number that obtained after some mathematics operations\n"
		<< "You can calculate him only if you have square matrix(rows quantity equals columns quantity)\n\n";
}

void transpose_theory() {
	cout << "\t\tPAGE MATRIX INFO\n\n\t*Short theory about transpose.*"
		<< "\nRows elements are changed with columns elements.\nYou can transpose any matrix\n";
}

void inverse_theory() {
	cout << "\t\tPAGE MATRIX INFO\n\n\t*Short theory about inverse matrix.*"
		<< "\nAt first you must search determinant.\nIf he not equal 0 you search matrix of minor."
		<< "\nAfter searching matrix algebraic additions(sign of element)."
		<< "\nThan you transposing and deviding all elements on determinant\n";
}

void addition_theory() {
	cout << "\t\tPAGE FOR MATRIX ADDITION\n\n\t*Short theory about matrix addition.*"
		<< "\n\tResulting matrix is obtained in the result\n of the addition of each element of the source matrix\n"
		<< "\nYou can get addition, if you have only matrix with the equal quantity of rows and columns\n";
}

void subtraction_theory() {
	cout << "\t\tPAGE FOR MATRIX SUBTRACTION\n\n\t*Short theory about matrix subtraction.*"
		<< "\n\tResulting matrix is obtained in the result\n of the subtraction of each element of the source matrix\n"
		<< "\nYou can get subtraction, if you have only matrix with the equal quantity of rows and columns\n";
}

void multiplication_theory() {
	cout << "\t\tPAGE FOR MATRIX MULTIPICATION\n\n\t*Short theory about matrix subtraction.*"
		<< "\n\tThe matrix  multiplication AB consists of all possible combinations"
		<< "\nof scalar multiplication of vector-rows of the matrix A and the vector-columns of the matrix B."
		<< "\nThe matrix Element AB with the indices i, j is the scalar multiplication"
		<< "\nof the i-th vector rows of matrix A and the j-th vector-column of the matrix B."
		<< "\n\nThe operation of multiplying two matrices is possible"
		<< "\nonly if the number of columns in the first factor equals the number of rows in the second\n";
}

void info() {
	system("cls");
	system("color 0E");
	cout << "\t\t***INFORMATION***\n\n\t_____Program info_____\n\nThis program is able to perform various mathematical operations with matrices"
		<< "\n\nName of program-Matrix Complex\n\nIt is a course work in the discipline of object-oriented programming\n\nLecturer-Molchanova S.I."
		<< "\n\n\t_____Author info_____\n\nFull name - Medvedev Kirill\n\nRang - Student\n\nCourse of study-3\n\n";
	system("pause");
}


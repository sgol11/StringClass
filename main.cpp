#include <iostream>
#include <cstring> //если не берет авто strlen

using namespace std;

class myString {
private:
	int len; //размер массива
	char* str; //указатель на дим массив
public:
	myString() {
		len = 0;
		str = nullptr;
	}
	myString(const char* str) {
		len = strlen(str);
		this->str = new char[len + 1];
		for (int i = 0; i < len; i++) {
			this->str[i] = str[i];
		}
		this->str[len] = '\0';
	}
	~myString() {
		delete[] str;
	}

	//перегрузка ввода и вывода
	friend istream& operator >> (istream&, myString&);
	friend ostream& operator << (ostream& out, myString& S);

	//возвращаем длину строки
	int length() { return len; }

	//возвращаем элемент с заданным индексом
	char& operator[] (int index) { return str[index]; }

	//конструктор копирования
	myString(const myString& S);
	//перегрузка оператора +
	myString operator+(const myString &S);
	//перегрузка оператора =
	myString& operator=(const myString& S);
	//перегрузка оператора *
	myString& operator*(int n);
	//перегрузка операторов сравнения
	bool operator==(myString S);
	bool operator!=(myString S);
	bool operator<(myString S);
	bool operator>(myString S);
	bool operator<=(myString S);
	bool operator>=(myString S);
	//смена регистра буквы
	void to_lower();
	void to_upper();
	//добавляение символа в конец
	void push_back(char tmp);
	//вставка символа
	void insert(int index, char tmp);
	//поиск подстроки
	int find(myString t);
};

istream& operator >> (istream& in, myString& S) {
	char buffer[100000];
	in.getline(buffer, 100000);
	//получаем длину входной строки
	S.len = strlen(buffer);
	if (buffer[strlen(buffer) - 1] == '\r' || buffer[strlen(buffer) - 1] == '\n') {
		S.len--;
	}
	//выделяем память под массив
	S.str = new char[S.len + 1];
	//переносим символы из буфера в строку
	for (unsigned int i = 0; i < S.len; i++) {
		S.str[i] = buffer[i];
	}
	//добавляем спецсимвол! \0
	S.str[S.len] = '\0';
	//возвращаем поток
	return in;
}
ostream& operator << (ostream& out, myString& S) {
	out << S.str;
	return out;
}

void myString::push_back(char tmp) {
	this->len++;
	char* new_str = new char[this->len + 1];
	for (int i = 0; i < this->len-1; i++) {
		new_str[i] = this->str[i];
	}
	new_str[this->len-1] = tmp;
	new_str[this->len] = '\0';

	delete[] str;
	str = new_str;
}

void myString::insert(int index, char tmp) {
	this->len++;
	char* new_str = new char[this->len + 1];
	for (int i = 0; i < index; i++) {
		new_str[i] = this->str[i];
	}
	new_str[index] = tmp;
	for (int i = index + 1; i < this->len; i++) {
		new_str[i] = this->str[i - 1];
	}
	new_str[this->len] = '\0';

	delete[] str;
	str = new_str;
}

void myString::to_lower() {
	for (int i = 0; i < len; i++) {
		str[i] = (char)tolower(str[i]);
	}
}
void myString::to_upper() {
	for (int i = 0; i < len; i++) {
		str[i] = (char)toupper(str[i]);
	}
}

myString::myString(const myString& S) {
	len = strlen(S.str);
	this->str = new char[len + 1];

	for (int i = 0; i < len; i++)
		this->str[i] = S.str[i];

	this->str[len] = '\0';
}

myString& myString::operator=(const myString& S) {
	if (this->str != nullptr)
		delete[] this->str;

	len = strlen(S.str);
	this->str = new char[len + 1];

	for (int i = 0; i < len; i++)
		this->str[i] = S.str[i];

	this->str[len] = '\0';
	return *this;
}

myString myString::operator+(const myString &S) {
	myString newString;
	int len1 = this->length();
	int len2 = strlen(S.str);
	newString.str = new char[len1 + len2 + 1];

	int i = 0;
	for (; i < len1; i++) {
		newString[i] = this->str[i];
	}
	for (int j = 0; j < len2; i++, j++) {
		newString[i] = S.str[j];
	}
	newString[len1 + len2] = '\0';
	return newString;
}

myString& myString::operator*(int n) {
	int tmp = this->len;
	this->len*=n;
	char* new_str = new char[this->len + 2];
	for (int i = 0; i < this->len; i++) {
		new_str[i] = this->str[i % tmp];
	}
	new_str[this->len] = '\n';
	new_str[this->len + 1] = '\0';

	delete[] str;
	str = new_str;
	return *this;
}

bool myString::operator==(myString S) {
	if (this->length() != S.length())
		return false;
	else {
		for (int i = 0; i < len; i++) {
			if (str[i] != S[i])
				return false;
		}
	}
	return true;
}
bool myString::operator!=(myString S) {
	return !(*this == S);
}
bool myString::operator<(myString S) {
	int tmp_len;
	if (this->length() < S.length())
		tmp_len = this->length();
	else
		tmp_len = S.length();
	for (int i = 0; i < tmp_len; i++) {
		if ((int)str[i] < (int)S[i])
			return true;
		else
			return false;
	}
	if (this->length() < S.length())
		return true;
	else
		return false;
}
bool myString::operator>(myString S) {
	int tmp_len;
	if (this->length() < S.length())
		tmp_len = this->length();
	else
		tmp_len = S.length();
	for (int i = 0; i < tmp_len; i++) {
		if ((int)str[i] > (int)S[i])
			return true;
		else
			return false;
	}
	if (this->length() > S.length())
		return true;
	else
		return false;
}
bool myString::operator<=(myString S) {
	if (*this < S || *this == S)
		return true;
	else
		return false;
}
bool myString::operator>=(myString S) {
	if (*this > S || *this == S)
		return true;
	else
		return false;
}

int myString::find(myString t) {
	for (int i = 0; i <= this->len - t.len; i++) {
		for (int j = 0; this->str[i + j] == t[j]; j++) {
			if (j == t.len-1)
			    return i;
	    }
	}
	return -1;
}

int main() {
	myString s, t;
	cin >> t >> s;
	cout << s.find(t) << endl;
	return 0;
}

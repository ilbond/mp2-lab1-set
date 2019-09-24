// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField() ////aaaa
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
		if (BitField.GetBit(Elem) == 1)
			return 1;
		else
            return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if ((BitField == s.BitField) && (MaxPower==s.MaxPower))
		return 1;
	else
        throw 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if ((BitField != s.BitField) || (MaxPower != s.MaxPower))
		return 1;
	else
		throw 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int max;
	if (MaxPower > s.MaxPower)
		max = MaxPower;
	else
		max = s.MaxPower;
	TSet res(max);
	res.BitField = (this->BitField) | (s.BitField);
	return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{

	if (Elem > MaxPower)
		throw 1;
	else
	{
		TSet res(*this);
		res.BitField.SetBit(Elem);
		return res;

	}

}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem > MaxPower)
		throw 1;
	else
	{
		TSet res(*this);
		res.BitField.ClrBit(Elem);
		return res;

	}
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	int max;
	if (MaxPower > s.MaxPower)
		max = MaxPower;
	else
		max = s.MaxPower;
	TSet res(max);
	res.BitField = (this->BitField) & (s.BitField);
	return res;
}

TSet TSet::operator~(void) // дополнение
{
	TSet res(*this);
	res.BitField = ~BitField;
	return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	string str;
	vector <int> input;
	int word;
	cout << str;
	for (istringstream is(str); is >> word;)
	{
		input.push_back(word);
	}
	vector<int>::const_iterator it;
	for (it = input.begin(); it != input.end(); it++)
	{
		(s.BitField.SetBit(*it));
	}

	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i = 0; i < s.GetMaxPower(); i++)
	{
		if (s.BitField.GetBit(i) > 0)
			cout << i;
	}
	return ostr;
	
}

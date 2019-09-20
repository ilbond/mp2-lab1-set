// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	MemLen = len;
	BitLen = 32 * MemLen;
	pMem = new TELEM[MemLen];

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n

{
	return (MemLen -1 -n / 32);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{

	return (1<<n%32);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	this->pMem[this->GetMemIndex(n)] | this->GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	this->pMem[this->GetMemIndex(n)] | ~(this->GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{

  return pMem[this->GetMemIndex(n)] & (this->GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	delete[] pMem;
	MemLen = bf.MemLen;
	BitLen = MemLen * 32;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < bf.MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}

int TBitField::operator==(const TBitField &bf) const // сравнение 
{
	if (MemLen != bf.MemLen) {
		return 0;
	}
	for (int i = 0; i < bf.MemLen; i++) {
		if (pMem[i] != bf.pMem[i])
			return 0;
	}
	return 1;

}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (MemLen != bf.MemLen) {
		return 1;
	}
	else
	{
		for (int i = 0; i < bf.MemLen; i++) {
			if (pMem[i] != bf.pMem[i])
				return 1;
		}
	}
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	for (int i = 0; i < bf.MemLen; i++) {
		pMem[i] | bf.pMem[i];
	}

}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	for (int i = 0; i < bf.MemLen; i++) {
		pMem[i] & bf.pMem[i];
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	for (int i = 0; i < MemLen; i++) {
		~(pMem[i]);
	}
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
}

// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
		throw 1;
	MemLen = len/32+1;
	BitLen = len;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = 0;
	}

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n

{
	return (n/32);
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
	if (n < BitLen) {
		if (n < 0)
			throw 1;
			(this->pMem[this->GetMemIndex(n)]) = (this->pMem[this->GetMemIndex(n)]) | (this->GetMemMask(n));
	}
	else
		throw 1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < BitLen) {
		if (n < 0)
			throw 1;
			this->pMem[this->GetMemIndex(n)] = this->pMem[this->GetMemIndex(n)] & ~(this->GetMemMask(n));
	}
	else throw 1;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < BitLen) {
		if (n < 0)
			throw 1;
		else
			if (((pMem[GetMemIndex(n)]) & (GetMemMask(n))) > 0)
				return 1;
			else
				return 0;
	}
	else throw 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	delete [] pMem;
	this->MemLen = bf.MemLen;
	this->BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		this->pMem[i] = bf.pMem[i];
	}
	return *this;
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
	int max;
	if (this->BitLen > bf.BitLen)
		max = this->BitLen;
	else
		max = bf.BitLen;
	TBitField res(max);
	for (int i = 0; i < max/32+1; i++) {
		res.pMem[i]=this->pMem[i] | bf.pMem[i];
	}
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int max;
	if (this->BitLen > bf.BitLen)
		max = this->BitLen;
	else
		max = bf.BitLen;
	TBitField res(max);
	for (int i = 0; i < bf.MemLen; i++) {
		res.pMem[i]=this->pMem[i] & bf.pMem[i];
	}
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(*this);
	for (int i = 0; i < res.MemLen; i++) {
		res.pMem[i]=~(pMem[i]);
		if (i == (res.MemLen - 1))
		{
			int check = res.MemLen * 32 - 1;
			while (check != (res.BitLen - 1))
			{
				res.pMem[MemLen - 1] = res.pMem[MemLen - 1] & (~(1 <<check));
				check--;
			}
		}
	}
	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	return ostr;
}

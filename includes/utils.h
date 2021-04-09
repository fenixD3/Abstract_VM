#pragma once

#include <cassert>
#include <cmath>

#define MaxULPS 32

template <typename TType>
bool IsEqualTwoFloating(TType aFirst, TType aSecond, unsigned aMaxUlps)
{
	// aMaxUlps не должен быть отрицательным и не слишком большим, чтобы
	// NaN не был равен ни одному числу
	assert(aMaxUlps > 0 && aMaxUlps < 4 * 1024 * 1024);
	int aInt = *(int*)&aFirst;
	// Уберем знак в aInt, если есть, чтобы получить правильно упорядоченную последовательность
	if (aInt < 0)
		aInt = 0x80000000 - aInt;
	// Аналогично для bInt
	int bInt = *(int*)&aSecond;
	if (bInt < 0)
		bInt = 0x80000000 - bInt;
	unsigned int intDiff = abs(aInt - bInt);
	if (intDiff <= aMaxUlps)
		return true;
	return false;
}

template <typename TType>
bool IsLessOrEqualFirstFloating(TType aFirst, TType aSecond)
{
	return IsEqualTwoFloating(aFirst, aSecond, MaxULPS) || (!IsEqualTwoFloating(aFirst, aSecond, MaxULPS) && aFirst < aSecond);
}

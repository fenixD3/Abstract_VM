#include "utils.h"
#include <cassert>
#include <cmath>

bool AlmostEqual2sComplement(float A, float B, int maxUlps)
{
    // maxUlps не должен быть отрицательным и не слишком большим, чтобы
    // NaN не был равен ни одному числу
    assert(maxUlps > 0 && maxUlps < 4 * 1024 * 1024);
    int aInt = *(int*)&A;
    // Уберем знак в aInt, если есть, чтобы получить правильно упорядоченную последовательность
    if (aInt < 0)
        aInt = 0x80000000 - aInt;
    // Аналогично для bInt
    int bInt = *(int*)&B;
    if (bInt < 0)
        bInt = 0x80000000 - bInt;
    unsigned int intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;
    return false;
}

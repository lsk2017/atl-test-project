// FastCom.cpp : CFastCom 구현

#include "pch.h"
#include "FastCom.h"


// CFastCom



STDMETHODIMP CFastCom::Sum(LONG a, LONG b, LONG* rst)
{
    // TODO: 여기에 구현 코드를 추가합니다.
    *rst = a + b;

    return S_OK;
}

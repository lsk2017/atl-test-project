#include <Windows.h>
#include <objbase.h>
#include <assert.h>
#include <iostream>
#include "../test_com/testcom_i.h"

int main()
{
	auto hr = CoInitialize(NULL);
	assert(SUCCEEDED(hr));

	IFastCom* pIFastCom{};

	hr = CoCreateInstance(
		CLSID_FastCom,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IFastCom,
		(void**) & pIFastCom
	);
	assert(SUCCEEDED(hr));

	LONG rst{};
	pIFastCom->Sum(1, 1, &rst);
	pIFastCom->Release();

	std::cout << rst << std::endl;

	CoUninitialize();

	return 0;
}
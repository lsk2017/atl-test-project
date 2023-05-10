#include <Windows.h>
#include <objbase.h>
#include <assert.h>
#include <iostream>
#include <functional>
#include "../test_com/testcom_i.h"

namespace
{
	template <typename T>
	std::function<T> LoadFunction(HINSTANCE hDLL, const std::string& funcName)
	{
		// Locate function in DLL.
		FARPROC lpfnGetProcessID = GetProcAddress(hDLL, funcName.c_str());

		// Check if function was located.
		if (!lpfnGetProcessID) {
			return std::function<T>(reinterpret_cast<T*>(nullptr));
		}

		// Create function object from function pointer.
		std::function<T> func(reinterpret_cast<T*>(lpfnGetProcessID));
		return func;
	}
}

int main()
{
	if (false)
	{
		auto hr = CoInitialize(NULL);
		assert(SUCCEEDED(hr));

		IFastCom* pIFastCom{};

		hr = CoCreateInstance(
			CLSID_FastCom,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IFastCom,
			(void**)&pIFastCom
		);
		assert(SUCCEEDED(hr));

		LONG rst{};
		pIFastCom->Sum(1, 1, &rst);
		pIFastCom->Release();

		std::cout << rst << std::endl;

		CoUninitialize();

		int a;
		std::cin >> a;
	}
	else
	{
		HINSTANCE testcomDll = LoadLibrary(TEXT("../x64/debug/test_com.dll"));
		assert(testcomDll != NULL);

		auto fn = LoadFunction<HRESULT(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID* ppv)>(testcomDll, "DllGetClassObject");
		assert(fn);

		// https://stackoverflow.com/questions/18737799/dllgetclassobject-return-no-such-interface-supported-while-cocreateinstance-ca
		IClassFactory* pCF;
		HRESULT hr = fn(CLSID_FastCom, /*IID_IFastCom*/__uuidof(IUnknown), (void**)&pCF);
		if (SUCCEEDED(hr))
		{
			IFastCom* pMyObject;
			hr = pCF->CreateInstance(NULL, IID_IFastCom, (void**)&pMyObject);
			if (SUCCEEDED(hr))
			{
				// Use the COM object
				LONG rst{};
				pMyObject->Sum(10, 10, &rst);
				std::cout << rst << std::endl;
				// ...
				pMyObject->Release();
			}
			pCF->Release();
		}
		else
		{
			assert(false);
		}

	}

	return 0;
}
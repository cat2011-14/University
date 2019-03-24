#include <Windows.h>
#include "..\component\Interfaces.h"
#include <iostream>

using namespace std;


int main()
{
	IUnknown* pUnknown;
	HMODULE hModule = LoadLibrary(L"component.dll");
	if (hModule != NULL)
	{
		CREATEINSTANCEPROC hInstance;
		hInstance = (CREATEINSTANCEPROC)GetProcAddress(hModule, "CreateInstance");
		if (hInstance != 0)
		{
			pUnknown = hInstance();

			ICollection* IC;
			HRESULT res = pUnknown->QueryInterface(IID_ICollection, (void**)&IC);
			if (SUCCEEDED(res))
			{
				Object obj;
				obj.Type = otDouble;
				obj.Value.Double= 5.32;
				IC->Add(obj);
				obj.Type = otDouble;
				obj.Value.Double = 1.121;
				IC->Add(obj);
				obj.Type = otDouble;
				obj.Value.Double = 3.211;
				IC->Add(obj);
			}

			IEnumerator* IE;
			HRESULT res2 = pUnknown->QueryInterface(IID_IEnumerator, (void**)&IE);
			if (SUCCEEDED(res2))
			{
				IE->Reset();
				int result;
				IE->MoveNext(&result);
				Object temp_obj;
				while (result)
				{
					IE->GetCurrent(&temp_obj);
					switch (temp_obj.Type)
					{
					case 0:
					{
						cout << "Object type -  int and value: " << temp_obj.Value.Int << endl;
						break;
					}
					case 1:
					{
						cout << "Object type - double and value: " << temp_obj.Value.Double << endl;
						break;
					}
					case 2:
					{
						cout << "Object type - array and value: " << temp_obj.Value.Array << endl;
						break;
					}
					default:
						break;
					}
					IE->MoveNext(&result);
				}
			}
		}
	
	}
	
	return 0;
}
#include <windows.h>
#include "../Win32Project2/Interfaces.h"
#include "iostream"
using namespace std;
void main()
{
	IUnknown* pUnknown;
	HMODULE hmod;
	hmod = LoadLibrary(L"Win32Project2.dll");
	if (hmod != NULL)
	{
		CREATEINSTANCEPROC hInstance;
		hInstance = (CREATEINSTANCEPROC)GetProcAddress(hmod, "CreateInstance");
		if (hInstance != 0)
		{
			pUnknown = hInstance();
			ICollection* IC;
			HRESULT res = pUnknown->QueryInterface(IID_ICollection, (void**)&IC);
			pUnknown->Release();
			Object obj1;
			obj1.Type = otDouble;
			if (SUCCEEDED(res))
			{
				//добавление элементов
				cout << "elements : " << endl;
				for (int i = 0; i < 8; i++)
				{
					obj1.Value.Double = i;
					cout << obj1.Value.Double << " "<<endl;
					IC->Add(obj1);
				}
				// количество элементов получаем
				unsigned int count;
				IC->GetCount(&count);
				cout << "count :" << count << endl;

				//перевод в массив
				ObjectArray *mass;
				IC->ToArray(&mass);
				
				//удалить элементы
				Object obj2;
				cout << "delete" << endl;
				cin >> obj2.Value.Double;
				obj2.Type = otDouble;
				IC->Remove(obj2);
			}
			IEnumerator *IE=0;
			HRESULT res2 = pUnknown->QueryInterface(IID_IEnumerator, (void**)&IE);
			//HRESULT res2 = IC->QueryInterface(IID_IEnumerator, (void**)&IE);
			if (SUCCEEDED(res2))
			{
				//возврат в исходное положение
				IE->Reset();

				//переход на след положение
				int check;
				Object element;
				IE->MoveNext(&check);
				if (check != 0)
				{
					do
					{
						IE->GetCurrent(&element);
						cout << element.Value.Double<< " ";
						IE->MoveNext(&check);
					} while (check != 0);
				}
				//получить значение
				Object obj3;
				IE->GetCurrent(&obj3);
				int a;
				cin >> a;
			}
			//pUnknown->Release();
		};
	}
}
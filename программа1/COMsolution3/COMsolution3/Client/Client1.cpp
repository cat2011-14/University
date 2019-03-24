#include <Windows.h>
#import "..\Main\Debug\Component.tlb"
#include <iostream>
using namespace MyComLib;

using namespace std;

int main()
{
	
	       HRESULT hr;
	       hr = CoInitialize(NULL);
		   ICollectionPtr  IC;
		   hr = IC = ICollectionPtr(__uuidof(CList));
		   Object obj;
		   obj.Type = otDouble;
		if (SUCCEEDED(hr))
		{
			//cout << "Add:" << endl;
			//����������
			for (int i = 0; i < 5; i++)
			{
				obj.Value.Double = i;
				cout << obj.Value.Double << " "<<endl;
				IC->Add(obj);
			}

			//��������� ���������� ���������
			unsigned int count;
			IC->GetCount(&count);
			cout << "Count: " << count << endl;

			//��������� � ������

			ObjectArray *massiv;
			IC->ToArray(&massiv);

		    //�������� ��������
			Object a;
			cout << "Delete: ";
			cin >> a.Value.Double;
			a.Type = otDouble;
			IC->Remove(a);



		}

		IEnumerator* IE = 0;
	HRESULT hr1 = IC->QueryInterface(__uuidof(IEnumerator), (void**)&IE);
	
		if (SUCCEEDED(hr1))
		{
			//������� � �������� ���������
			IE->Reset();

			//������� �� ���� ���������
			
			int num;
			Object element;
			IE->MoveNext(&num);
			if (num != 0)
			{
				do
				{
					IE->GetCurrent(&element);
					cout << element.Value.Double << " ";
					IE->MoveNext(&num);


				} while (num != 0 );
			}


			//��������� ��������

			Object ob;
			
}
		
		IE = NULL;
		IC = NULL;
		CoUninitialize();
	return 0;
}
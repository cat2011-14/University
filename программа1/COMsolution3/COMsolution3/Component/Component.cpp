#pragma once

#include "Component.h"
#include "Shlwapi.h""


	// Следующие методы вызываются только через указатели на
	// соответствующие интерфейсы, поэтому в компоненте могут быть закрытыми!

	////////////////////////////
	// Методы IUnknown
HRESULT __stdcall CList::QueryInterface(REFIID iid, void** ppv)
{
	if (iid == IID_IUnknown)
	{
		//Клиент запрашивает интерфейс IUnknown
		*ppv = static_cast<ICollection*>(this);
	}
	else if (iid == IID_ICollection)
	{
		//клиент запрашивает интерфейс ICollection 
		*ppv = static_cast<ICollection*>(this);
	}

	else if (iid == IID_IEnumerator)
	{
		//Клиент запрашивает интерфейс IEnumerator
		*ppv = static_cast<IEnumerator*>(this);

	}
	else
	{
		//Мы не поддерживаем запрашиваемый клиентом интерфейс
		//Установить возвращаемый указатель в NULL
		*ppv = NULL;
		return E_NOINTERFACE;

	}
	AddRef();
	return S_OK;
}

ULONG __stdcall CList::AddRef()
{
	return ++m_cRef;
}

ULONG __stdcall CList::Release()
{
	if (--m_cRef == 0)
	{
		delete this;
		return 0;
	}

	return m_cRef;
}

	////////////////////////////
	// Методы ICollection
HRESULT __stdcall CList::Add(Object obj)
{
	Conteiner.emplace_back(obj);
	return S_OK;
}
HRESULT __stdcall CList::Remove(Object obj)
{
	Conteiner.remove(obj);
	return S_OK;
}
HRESULT __stdcall CList::GetCount(unsigned *count)
{
	*count = Conteiner.size();
	return S_OK;
}
HRESULT __stdcall CList::ToArray(ObjectArray **arr)
{
	Object *massiv = new Object[Conteiner.size()];
	int i = 0;
	for each(Object object in Conteiner)
	{
		massiv[i] = object;
		i++;
	}

	ObjectArray *ARRAY = new ObjectArray;
	ARRAY->Data = massiv;
	ARRAY->Count = i;
	*arr = ARRAY;
	return S_OK;
}

	////////////////////////////
	// Методы IEnumerator
HRESULT __stdcall CList::Reset()
{
	this->res_iterator = this->Conteiner.rend();
	return S_OK;
	
}
HRESULT __stdcall CList::MoveNext(int *result)
{

	if (this->Conteiner.size() == 0)
	{
		*result = 0;
	}
	else if (this->res_iterator == this->Conteiner.rbegin())
	{
		*result = 0;
	}
	else
	{
		(--this->res_iterator);
		*result = 1;
	}
	
	return S_OK;
}
HRESULT __stdcall CList::GetCurrent(Object *obj)
{
	*obj = *this->res_iterator;
	return S_OK;
}

IUnknown* CreateInstance()
{
	IUnknown* pI = static_cast<ICollection*>(new CList);
	pI->AddRef();
	return pI;
}

bool operator ==(const Object &o1, const  Object &o2)
{
	if (o1.Type != o2.Type) return false;
	if (o2.Type == otDouble)
	{
		if (abs(o1.Value.Double - o2.Value.Double) < 1e-15) return true;
	}
	if (o2.Type == otArray)
	{
		if (o1.Value.Array == o2.Value.Array) return true;
	}
	if (o2.Type == otInt)
	{
		if (o1.Value.Int == o2.Value.Int) return true;
	}

	else return false;

}

//реализация IClassFactory
//
HRESULT __stdcall CFactory::CreateInstance(
	IUnknown* pUnknownOuter,
	REFIID iid, void** ppv)
{
	CList* pA = new CList;
	if (pA == NULL) return E_OUTOFMEMORY;
	
	pA->AddRef();

	//получить запрошенный интерфейс
	HRESULT hr = pA->QueryInterface(iid, ppv);

	pA->Release();
	return hr;
}

//получить фабрику класса
//
STDAPI DllGetClassObject(REFCLSID clsid, REFIID iid, void** ppv)
{
	//создать фабрику класса
	CFactory* pFactory = new CFactory;
	if (pFactory == NULL) return E_OUTOFMEMORY;
	pFactory->AddRef();
	//получить требуемый интерфейс
	HRESULT hr = pFactory->QueryInterface(iid, ppv);
	pFactory->Release();
	return hr;
}

HRESULT __stdcall CFactory::LockServer(BOOL bLock)
{
	if (bLock) g_cServerLocks++;
	else g_cServerLocks--;
	return S_OK;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD fdwReason, PVOID fImpLoad)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		g_hModule = (HMODULE)hModule;
	}

	return (TRUE);
}
STDAPI DllRegisterServer()
{
	wchar_t KeyPathBuf[512];
	GetModuleFileName(g_hModule, KeyPathBuf, sizeof(KeyPathBuf) / sizeof(char));

	//преобразование в строку
	LPOLESTR str;
	StringFromCLSID(CLSID_CList, &str);

	wstring KeyPath = L"Software\\Classes\\CLSID\\";
	KeyPath += str;
	KeyPath += L"\\InprocServer32";

	//добавление в реестр
	HKEY hkey;

	//создает указанный ключ 

	LONG check1 = RegCreateKey(HKEY_CURRENT_USER, KeyPath.data(), &hkey);

	//устанавливает значение указанному ключу

	LONG check2 = RegSetValue(hkey, NULL, REG_SZ, KeyPathBuf, sizeof(KeyPathBuf) / sizeof(char));
	RegCloseKey(hkey);
	return S_OK;
}


STDAPI DllUnregisterServer()
{
	LPOLESTR str;
	StringFromCLSID(CLSID_CList, &str);
	wstring KeyPath = L"Software\\Classes\\CLSID\\";
	 
	KeyPath += str;
	SHDeleteKey(HKEY_CURRENT_USER, KeyPath.data());
	
	return S_OK;
}

STDAPI DllCanUnloadNow()
{
	if ((g_cComponents == 0) && (g_cServerLocks == 0)) return S_OK;
	else return S_FALSE;
}



HRESULT __stdcall CFactory::QueryInterface(REFIID iid, void** ppv)
{
	if (iid == IID_IUnknown || iid == IID_IClassFactory)
	{
		//Клиент запрашивает интерфейс IUnknown
		*ppv = static_cast<IClassFactory*>(this);
	}
	else
	{
		//Мы не поддерживаем запрашиваемый клиентом интерфейс
		//Установить возвращаемый указатель в NULL
		*ppv = NULL;
		return E_NOINTERFACE;

	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG __stdcall CFactory::AddRef()
{
	return InterlockedIncrement(&m_cRef);
}

ULONG __stdcall CFactory::Release()
{
	if (InterlockedIncrement(&m_cRef) == 0)
	{
		delete this;
		return 0;
	}

	return m_cRef;
}



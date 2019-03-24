#include "Component.h"
#include "Interfaces.h"




bool operator ==(const Object & ob1, const Object & ob2)
{
	if (ob1.Type != ob2.Type)
		return false;
	else if (ob1.Value.Array != ob2.Value.Array)
		return false;
	else if (ob1.Value.Int != ob2.Value.Int)
		return false;
	else if (ob1.Value.Double != ob2.Value.Double)
		return false;
	else
		return true;
}

////////////////////////////
// Методы IUnknown
HRESULT __stdcall CList::QueryInterface(REFIID iid, void** ppv)
{
	if (iid == IID_IUnknown)
	{
		// Клиент запрашивает интерфейс IUnknown
		*ppv = static_cast<ICollection*>(this);
	}
	else if (iid == IID_ICollection)
	{
		// Клиент запрашивает интерфейс ICollection
		*ppv = static_cast<ICollection*>(this);
	}
	else if(iid == IID_IEnumerator)
	{
		// Клиент запрашивает интерфейс IEnumerator
		*ppv = static_cast<IEnumerator*>(this);
	}
	else
	{
		// Мы не поддерживаем запрашиваемый клиентом
		// интерфейс. Установить возвращаемый указатель
		// в NULL
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
	this->lst_obj.push_back(obj);
	return S_OK;
}
HRESULT __stdcall CList::Remove(Object obj)
{
	this->lst_obj.remove(obj);
	return S_OK;
}
HRESULT __stdcall CList::GetCount(unsigned *count)
{
	(*count) = this->lst_obj.size();
	return S_OK;
}
HRESULT __stdcall CList::ToArray(ObjectArray **arr)
{
	Object *temp_arr = new Object[this->lst_obj.size()];
	int i = 0;
	for each(Object it in this->lst_obj)
	{
		temp_arr[i] = it;
		i++;
	}

	ObjectArray * obj_arr = new ObjectArray;
	obj_arr->Data = temp_arr;
	obj_arr->Count = i;
	*arr = obj_arr;

	return S_OK;
}

////////////////////////////
// Методы IEnumerator
HRESULT __stdcall CList::Reset()
{
	this->r_iter = this->lst_obj.rend();
	return S_OK;
}
HRESULT __stdcall CList::MoveNext(int *result)
{
	if (this->lst_obj.size() == 0)
	{
		*result = 0;
	}
	else if (this->r_iter == this->lst_obj.rbegin())
	{
		*result = 0;
	}
	else
	{
		(--this->r_iter);
		*result = 1;
	}
	return S_OK;
}
HRESULT __stdcall CList::GetCurrent(Object *obj)
{
	*obj = *this->r_iter;
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// Экспортируемая функция создания экземпляра компонента
IUnknown* CreateInstance()
{
	IUnknown* pI = static_cast<ICollection*>(new CList);
	pI->AddRef();
	return pI;
}

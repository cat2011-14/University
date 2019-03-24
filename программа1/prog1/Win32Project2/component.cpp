#pragma once
#include "Component.h"
#include "Interfaces.h"

// —ледующие методы вызываютс€ только через указатели на
// соответствующие интерфейсы, поэтому в компоненте могут быть закрытыми!
/*bool operator ==(Object &o1, Object & o2)
{
	if (o1.Type != o2.Type) return false;
	else if (o1.Value.Array == o2.Value.Array) return true;
	else if (o1.Value.Int == o2.Value.Int) return true;
	else if (abs(o1.Value.Double - o2.Value.Double)<1e-15) return true;
}*/
/*bool operator ==(const Object & ob1, const Object & ob2)
{
	if (ob1.Type != ob2.Type)return false;
	else if (ob1.Value.Array != ob2.Value.Array)
		return false;
	else if (ob1.Value.Int != ob2.Value.Int)
		return false;
	else if (abs(ob1.Value.Double - ob2.Value.Double)<1e-15)
		return true;
	else
		return true;
}*/
bool operator ==(const Object & ob1, const Object & ob2)
{
	if (ob1.Type != ob2.Type)return false;
	if (ob1.Type == otArray)
	{
		if (ob1.Value.Array == ob2.Value.Array) return true;
	}
	if (ob1.Type == otDouble)
	{
		if(abs(ob1.Value.Double-ob2.Value.Double)<1e-15) return true;
	}
	if (ob2.Type == otInt)
	{
		if (ob1.Value.Int == ob2.Value.Int) return true;
	}
	else return false;
}
	////////////////////////////
	// ћетоды IUnknown
HRESULT __stdcall CList::QueryInterface(REFIID iid, void** ppv)
{
	if (iid == IID_IUnknown)
	{
		//клиент запрашивает интерфейс IUnknown
		*ppv = static_cast<ICollection*>(this);
	}
	else if (iid == IID_ICollection)
	{
		//клиент запрашивает интерфейс IX
		*ppv = static_cast<ICollection*>(this);
	}
	else if (iid == IID_IEnumerator)
	{
		//клиент запрашивает интерфейс IY
		*ppv = static_cast<IEnumerator*>(this);
	}
	else
	{
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
	// ћетоды ICollection
HRESULT __stdcall CList::Add(Object obj)
{
	this->list_obj.push_back(obj);
	return S_OK;
}
HRESULT __stdcall CList::Remove(Object obj)
{
	this->list_obj.remove(obj);
	return S_OK;
}
HRESULT __stdcall CList::GetCount(unsigned *count)
{
	(*count) = this->list_obj.size();
	return S_OK;
}
HRESULT __stdcall CList::ToArray(ObjectArray **arr)
{
	Object *arr_temp = new Object[this->list_obj.size()];
	int i = 0;
	for each(Object t in this->list_obj)
	{
		arr_temp[i] = t;
		i++;
	}
	ObjectArray *arr_obj = new ObjectArray;
	arr_obj->Data = arr_temp;
	arr_obj->Count = i;
	*arr = arr_obj;
	return S_OK;
}

	////////////////////////////
	// ћетоды IEnumerator
HRESULT __stdcall CList::Reset()
{
	this->revers_iter = this->list_obj.rend();
	return S_OK;
}
HRESULT __stdcall CList::MoveNext(int *result)
{
	if (this->list_obj.size() == 0)
	{
		*result = 0;
	}
	else if (this->revers_iter == this->list_obj.rbegin())
	{
		*result = 0;
	}
	else
	{

		(--this->revers_iter);
		*result = 1;
	}
	return S_OK;
}
HRESULT __stdcall CList::GetCurrent(Object *obj)
{
	*obj = *this->revers_iter;
	return S_OK;
}
///Ёкспортируема€ функци€ создани€ экземпл€ра компонентa
IUnknown* CreateInstance()
{
		IUnknown* pI = static_cast<ICollection*>(new CList);
		pI->AddRef();
		return pI;
}

#pragma once
#include <iostream>
#include "../Main/Interface_h.h"
#include <List>

using namespace std;
long g_cComponents = 0;
long g_cServerLocks = 0;
HMODULE g_hModule;
//////////////////////////////////////////////////////////////////////////
// ����� ������
class CList : public ICollection, public IEnumerator
{
	// ������� ������
	ULONG m_cRef;
	list <Object> Conteiner;
	//std::list<Object> element_list;
	std::list<Object>::reverse_iterator res_iterator;
	// ��������� ������ ���������� ������ ����� ��������� ��
	// ��������������� ����������, ������� � ���������� ����� ���� ���������!
public:
	////////////////////////////
	// ������ IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void** ppv);
	virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();
	
	////////////////////////////
	// ������ ICollection
	virtual HRESULT __stdcall Add(Object obj);
	virtual HRESULT __stdcall Remove(Object obj);
	virtual HRESULT __stdcall GetCount(unsigned *count);
	virtual HRESULT __stdcall ToArray(ObjectArray **arr);
	friend bool operator ==(const Object &o1, const Object &o2);
	////////////////////////////
	// ������ IEnumerator
	virtual HRESULT __stdcall Reset();
	virtual HRESULT __stdcall MoveNext(int *result);
	virtual HRESULT __stdcall GetCurrent(Object *obj);


	// �����������
	CList() : m_cRef(0) 
	{
		g_cComponents++;
	}

	// ����������
	~CList() { std::cout << __FUNCTION__ << std::endl;
	           g_cComponents--;
	          }
};


//������� ������
class CFactory : public IClassFactory
{
	long m_cRef;

    public: 
		//Unknown
		virtual HRESULT __stdcall QueryInterface(REFIID iid, void** ppv);
		virtual ULONG __stdcall AddRef();
		virtual ULONG __stdcall Release();

		//��������� IClassFactory
		virtual HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter, REFIID iid, void** ppv);
		virtual HRESULT __stdcall LockServer(BOOL bLock);

		//�����������
		CFactory() : m_cRef(0) {}

		//����������
		~CFactory() {}
};

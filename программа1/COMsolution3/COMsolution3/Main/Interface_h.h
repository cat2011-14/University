

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Apr 12 13:30:12 2018
 */
/* Compiler settings for Interface.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __Interface_h_h__
#define __Interface_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICollection_FWD_DEFINED__
#define __ICollection_FWD_DEFINED__
typedef interface ICollection ICollection;

#endif 	/* __ICollection_FWD_DEFINED__ */


#ifndef __IEnumerator_FWD_DEFINED__
#define __IEnumerator_FWD_DEFINED__
typedef interface IEnumerator IEnumerator;

#endif 	/* __IEnumerator_FWD_DEFINED__ */


#ifndef __CList_FWD_DEFINED__
#define __CList_FWD_DEFINED__

#ifdef __cplusplus
typedef class CList CList;
#else
typedef struct CList CList;
#endif /* __cplusplus */

#endif 	/* __CList_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_Interface_0000_0000 */
/* [local] */ 


enum ObjectType
    {
        otInt	= 0,
        otDouble	= ( otInt + 1 ) ,
        otArray	= ( otDouble + 1 ) 
    } ;
struct ObjectArray
    {
    struct Object *Data;
    unsigned int Count;
    } ;
struct Object
    {
    enum ObjectType Type;
    /* [switch_is] */ /* [switch_type] */ union 
        {
        /* [case()] */ int Int;
        /* [case()] */ double Double;
        /* [case()] */ struct ObjectArray *Array;
        } 	Value;
    } ;


extern RPC_IF_HANDLE __MIDL_itf_Interface_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_Interface_0000_0000_v0_0_s_ifspec;

#ifndef __ICollection_INTERFACE_DEFINED__
#define __ICollection_INTERFACE_DEFINED__

/* interface ICollection */
/* [uuid][object] */ 


EXTERN_C const IID IID_ICollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("53278EA6-CDFE-43D4-AB4A-08A413613DC5")
    ICollection : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ struct Object obj) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ struct Object obj) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCount( 
            /* [out] */ unsigned int *count) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ToArray( 
            /* [out] */ struct ObjectArray **arr) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *Add )( 
            ICollection * This,
            /* [in] */ struct Object obj);
        
        HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ICollection * This,
            /* [in] */ struct Object obj);
        
        HRESULT ( STDMETHODCALLTYPE *GetCount )( 
            ICollection * This,
            /* [out] */ unsigned int *count);
        
        HRESULT ( STDMETHODCALLTYPE *ToArray )( 
            ICollection * This,
            /* [out] */ struct ObjectArray **arr);
        
        END_INTERFACE
    } ICollectionVtbl;

    interface ICollection
    {
        CONST_VTBL struct ICollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICollection_Add(This,obj)	\
    ( (This)->lpVtbl -> Add(This,obj) ) 

#define ICollection_Remove(This,obj)	\
    ( (This)->lpVtbl -> Remove(This,obj) ) 

#define ICollection_GetCount(This,count)	\
    ( (This)->lpVtbl -> GetCount(This,count) ) 

#define ICollection_ToArray(This,arr)	\
    ( (This)->lpVtbl -> ToArray(This,arr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICollection_INTERFACE_DEFINED__ */


#ifndef __IEnumerator_INTERFACE_DEFINED__
#define __IEnumerator_INTERFACE_DEFINED__

/* interface IEnumerator */
/* [uuid][object] */ 


EXTERN_C const IID IID_IEnumerator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AD1A1128-6675-4607-8A4F-72CA47FFB36F")
    IEnumerator : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveNext( 
            /* [out] */ int *result) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrent( 
            /* [out] */ struct Object *obj) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumeratorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumerator * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumerator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumerator * This);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumerator * This);
        
        HRESULT ( STDMETHODCALLTYPE *MoveNext )( 
            IEnumerator * This,
            /* [out] */ int *result);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrent )( 
            IEnumerator * This,
            /* [out] */ struct Object *obj);
        
        END_INTERFACE
    } IEnumeratorVtbl;

    interface IEnumerator
    {
        CONST_VTBL struct IEnumeratorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumerator_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumerator_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumerator_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumerator_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumerator_MoveNext(This,result)	\
    ( (This)->lpVtbl -> MoveNext(This,result) ) 

#define IEnumerator_GetCurrent(This,obj)	\
    ( (This)->lpVtbl -> GetCurrent(This,obj) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumerator_INTERFACE_DEFINED__ */



#ifndef __MyComLib_LIBRARY_DEFINED__
#define __MyComLib_LIBRARY_DEFINED__

/* library MyComLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MyComLib;

EXTERN_C const CLSID CLSID_CList;

#ifdef __cplusplus

class DECLSPEC_UUID("16979FDD-0103-4884-912A-E252E987EA77")
CList;
#endif
#endif /* __MyComLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif



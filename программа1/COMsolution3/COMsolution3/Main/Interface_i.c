

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_ICollection,0x53278EA6,0xCDFE,0x43D4,0xAB,0x4A,0x08,0xA4,0x13,0x61,0x3D,0xC5);


MIDL_DEFINE_GUID(IID, IID_IEnumerator,0xAD1A1128,0x6675,0x4607,0x8A,0x4F,0x72,0xCA,0x47,0xFF,0xB3,0x6F);


MIDL_DEFINE_GUID(IID, LIBID_MyComLib,0x2D68DD59,0x31AF,0x43E7,0xA9,0x3F,0x0E,0xFD,0x51,0x90,0xAC,0x0A);


MIDL_DEFINE_GUID(CLSID, CLSID_CList,0x16979FDD,0x0103,0x4884,0x91,0x2A,0xE2,0x52,0xE9,0x87,0xEA,0x77);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif






/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 06:14:07 2038
 */
/* Compiler settings for ActiveXCPP2.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



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
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_ActiveXCPP2Lib,0xa57264e2,0x3f07,0x478c,0xbd,0x72,0xfa,0x55,0x96,0x92,0x79,0xf0);


MIDL_DEFINE_GUID(IID, DIID__DActiveXCPP2,0xb1b4b502,0xf06d,0x4d5d,0xbb,0x11,0x7d,0xea,0x2e,0xb3,0x28,0x49);


MIDL_DEFINE_GUID(IID, DIID__DActiveXCPP2Events,0x0e35ce4d,0x9521,0x4c66,0xa5,0x49,0x1e,0x3c,0xd8,0xe4,0x58,0xcd);


MIDL_DEFINE_GUID(CLSID, CLSID_ActiveXCPP2,0x6a7b9efb,0x6141,0x433c,0x90,0x38,0xa5,0xfc,0x9e,0x85,0x9a,0xe6);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif




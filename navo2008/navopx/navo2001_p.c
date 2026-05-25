

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for ..\..\iface\navo2001.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0628 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_)


#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "navopx.h"

#define TYPE_FORMAT_STRING_SIZE   1639                              
#define PROC_FORMAT_STRING_SIZE   6271                              
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   2            

typedef struct _navo2001_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } navo2001_MIDL_TYPE_FORMAT_STRING;

typedef struct _navo2001_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } navo2001_MIDL_PROC_FORMAT_STRING;

typedef struct _navo2001_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } navo2001_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax_2_0 = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};

#if defined(_CONTROL_FLOW_GUARD_XFG)
#define XFG_TRAMPOLINES(ObjectType)\
NDR_SHAREABLE unsigned long ObjectType ## _UserSize_XFG(unsigned long * pFlags, unsigned long Offset, void * pObject)\
{\
return  ObjectType ## _UserSize(pFlags, Offset, (ObjectType *)pObject);\
}\
NDR_SHAREABLE unsigned char * ObjectType ## _UserMarshal_XFG(unsigned long * pFlags, unsigned char * pBuffer, void * pObject)\
{\
return ObjectType ## _UserMarshal(pFlags, pBuffer, (ObjectType *)pObject);\
}\
NDR_SHAREABLE unsigned char * ObjectType ## _UserUnmarshal_XFG(unsigned long * pFlags, unsigned char * pBuffer, void * pObject)\
{\
return ObjectType ## _UserUnmarshal(pFlags, pBuffer, (ObjectType *)pObject);\
}\
NDR_SHAREABLE void ObjectType ## _UserFree_XFG(unsigned long * pFlags, void * pObject)\
{\
ObjectType ## _UserFree(pFlags, (ObjectType *)pObject);\
}
#define XFG_TRAMPOLINES64(ObjectType)\
NDR_SHAREABLE unsigned long ObjectType ## _UserSize64_XFG(unsigned long * pFlags, unsigned long Offset, void * pObject)\
{\
return  ObjectType ## _UserSize64(pFlags, Offset, (ObjectType *)pObject);\
}\
NDR_SHAREABLE unsigned char * ObjectType ## _UserMarshal64_XFG(unsigned long * pFlags, unsigned char * pBuffer, void * pObject)\
{\
return ObjectType ## _UserMarshal64(pFlags, pBuffer, (ObjectType *)pObject);\
}\
NDR_SHAREABLE unsigned char * ObjectType ## _UserUnmarshal64_XFG(unsigned long * pFlags, unsigned char * pBuffer, void * pObject)\
{\
return ObjectType ## _UserUnmarshal64(pFlags, pBuffer, (ObjectType *)pObject);\
}\
NDR_SHAREABLE void ObjectType ## _UserFree64_XFG(unsigned long * pFlags, void * pObject)\
{\
ObjectType ## _UserFree64(pFlags, (ObjectType *)pObject);\
}
#define XFG_BIND_TRAMPOLINES(HandleType, ObjectType)\
static void* ObjectType ## _bind_XFG(HandleType pObject)\
{\
return ObjectType ## _bind((ObjectType) pObject);\
}\
static void ObjectType ## _unbind_XFG(HandleType pObject, handle_t ServerHandle)\
{\
ObjectType ## _unbind((ObjectType) pObject, ServerHandle);\
}
#define XFG_TRAMPOLINE_FPTR(Function) Function ## _XFG
#define XFG_TRAMPOLINE_FPTR_DEPENDENT_SYMBOL(Symbol) Symbol ## _XFG
#else
#define XFG_TRAMPOLINES(ObjectType)
#define XFG_TRAMPOLINES64(ObjectType)
#define XFG_BIND_TRAMPOLINES(HandleType, ObjectType)
#define XFG_TRAMPOLINE_FPTR(Function) Function
#define XFG_TRAMPOLINE_FPTR_DEPENDENT_SYMBOL(Symbol) Symbol
#endif


extern const navo2001_MIDL_TYPE_FORMAT_STRING navo2001__MIDL_TypeFormatString;
extern const navo2001_MIDL_PROC_FORMAT_STRING navo2001__MIDL_ProcFormatString;
extern const navo2001_MIDL_EXPR_FORMAT_STRING navo2001__MIDL_ExprFormatString;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO INavoErrorInfo_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO INavoErrorInfo_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO INotificationManager_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO INotificationManager_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO INotificationSink_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO INotificationSink_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO ISupplyInfo_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISupplyInfo_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO IPingClient_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IPingClient_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO IPingServer_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IPingServer_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO ILockManager_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ILockManager_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO ICntResourceManager_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ICntResourceManager_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO IBackupRestore_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IBackupRestore_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO IBackupRestoreManager_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IBackupRestoreManager_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO IStreamProvider_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IStreamProvider_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO IStreamFilter_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IStreamFilter_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO IStreamSplitter_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IStreamSplitter_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO ISimpleEnumId_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISimpleEnumId_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO IAppDBManager_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IAppDBManager_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO INAVOObjectCollection_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO INAVOObjectCollection_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO IObjectServer_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IObjectServer_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO IObjectServerExtensionHost_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IObjectServerExtensionHost_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO IObjectServerExtension_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IObjectServerExtension_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO IPreprocessedDataCache_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IPreprocessedDataCache_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO IPreprocessor_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IPreprocessor_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO ICachedData_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ICachedData_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO IServerClient_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IServerClient_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO IServerClientFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IServerClientFactory_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO ICrossInfoManager_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ICrossInfoManager_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO IVirtualMachine_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IVirtualMachine_ProxyInfo;

#ifdef __cplusplus
namespace {
#endif

extern const MIDL_STUB_DESC Object_StubDesc;
#ifdef __cplusplus
}
#endif


extern const MIDL_SERVER_INFO IScriptCompiler_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IScriptCompiler_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif
#if !(TARGET_IS_NT60_OR_LATER)
#error You need Windows Vista or later to run this stub because it uses these features:
#error   forced complex structure or array, compiled for Windows Vista.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const navo2001_MIDL_PROC_FORMAT_STRING navo2001__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure RetrieveError */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x24 ),	/* 36 */
/* 14 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 16 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 18 */	NdrFcShort( 0x1 ),	/* 1 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pDataLength */

/* 24 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpBinaryData */

/* 30 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 34 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 36 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 38 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 40 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RetrieveError2 */

/* 42 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 44 */	NdrFcLong( 0x0 ),	/* 0 */
/* 48 */	NdrFcShort( 0x4 ),	/* 4 */
/* 50 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 52 */	NdrFcShort( 0x0 ),	/* 0 */
/* 54 */	NdrFcShort( 0x8 ),	/* 8 */
/* 56 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 58 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 60 */	NdrFcShort( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */
/* 64 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppcErrors */

/* 66 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 68 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 70 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 72 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 74 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 76 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Advise */

/* 78 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 80 */	NdrFcLong( 0x0 ),	/* 0 */
/* 84 */	NdrFcShort( 0x3 ),	/* 3 */
/* 86 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 88 */	NdrFcShort( 0x6 ),	/* 6 */
/* 90 */	NdrFcShort( 0x24 ),	/* 36 */
/* 92 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 94 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 96 */	NdrFcShort( 0x0 ),	/* 0 */
/* 98 */	NdrFcShort( 0x0 ),	/* 0 */
/* 100 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pONSinkUnknown */

/* 102 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 104 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 106 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter pcUserName */

/* 108 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 110 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 112 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pcComputerName */

/* 114 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 116 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 118 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter eNSC */

/* 120 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 122 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 124 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pCookie */

/* 126 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 128 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 130 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 132 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 134 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 136 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetParam */


	/* Procedure UnAdvise */


	/* Procedure UnAdvise */


	/* Procedure UnAdvise */

/* 138 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 140 */	NdrFcLong( 0x0 ),	/* 0 */
/* 144 */	NdrFcShort( 0x4 ),	/* 4 */
/* 146 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 148 */	NdrFcShort( 0x8 ),	/* 8 */
/* 150 */	NdrFcShort( 0x8 ),	/* 8 */
/* 152 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 154 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 156 */	NdrFcShort( 0x0 ),	/* 0 */
/* 158 */	NdrFcShort( 0x0 ),	/* 0 */
/* 160 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nType */


	/* Parameter nCookie */


	/* Parameter nCookie */


	/* Parameter nCookie */

/* 162 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 164 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 166 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 168 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 170 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 172 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure QuerySinks */

/* 174 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 176 */	NdrFcLong( 0x0 ),	/* 0 */
/* 180 */	NdrFcShort( 0x5 ),	/* 5 */
/* 182 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 184 */	NdrFcShort( 0x0 ),	/* 0 */
/* 186 */	NdrFcShort( 0x24 ),	/* 36 */
/* 188 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 190 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 192 */	NdrFcShort( 0x1 ),	/* 1 */
/* 194 */	NdrFcShort( 0x0 ),	/* 0 */
/* 196 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pDataLength */

/* 198 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 200 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 202 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpBinaryData */

/* 204 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 206 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 208 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 210 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 212 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 214 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure NotifySharedVariableChange */

/* 216 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 218 */	NdrFcLong( 0x0 ),	/* 0 */
/* 222 */	NdrFcShort( 0x6 ),	/* 6 */
/* 224 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 226 */	NdrFcShort( 0x10 ),	/* 16 */
/* 228 */	NdrFcShort( 0x8 ),	/* 8 */
/* 230 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 232 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 236 */	NdrFcShort( 0x1 ),	/* 1 */
/* 238 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nOriginatorCookie */

/* 240 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 242 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 244 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lVarNr */

/* 246 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 248 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 250 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nNewValue */

/* 252 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 254 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 256 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 258 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 260 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 262 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure NotifyUser */

/* 264 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 266 */	NdrFcLong( 0x0 ),	/* 0 */
/* 270 */	NdrFcShort( 0x7 ),	/* 7 */
/* 272 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 274 */	NdrFcShort( 0x18 ),	/* 24 */
/* 276 */	NdrFcShort( 0x8 ),	/* 8 */
/* 278 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 280 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 282 */	NdrFcShort( 0x0 ),	/* 0 */
/* 284 */	NdrFcShort( 0x1 ),	/* 1 */
/* 286 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nOriginatorCookie */

/* 288 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 290 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 292 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nDestinatorCookie */

/* 294 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 296 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 298 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lEvenCode */

/* 300 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 302 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 304 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pDataVariant */

/* 306 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 308 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 310 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 312 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 314 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 316 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure NotifyMultipleUsers */

/* 318 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 320 */	NdrFcLong( 0x0 ),	/* 0 */
/* 324 */	NdrFcShort( 0x8 ),	/* 8 */
/* 326 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 328 */	NdrFcShort( 0x18 ),	/* 24 */
/* 330 */	NdrFcShort( 0x8 ),	/* 8 */
/* 332 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 334 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 336 */	NdrFcShort( 0x0 ),	/* 0 */
/* 338 */	NdrFcShort( 0x1 ),	/* 1 */
/* 340 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nOriginatorCookie */

/* 342 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 344 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 346 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nCount */

/* 348 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 350 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 352 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pDestinatorCookies */

/* 354 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 356 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 358 */	NdrFcShort( 0x436 ),	/* Type Offset=1078 */

	/* Parameter lEvenCode */

/* 360 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 362 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 364 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pDataVariant */

/* 366 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 368 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 370 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 372 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 374 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 376 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetProp */

/* 378 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 380 */	NdrFcLong( 0x0 ),	/* 0 */
/* 384 */	NdrFcShort( 0x9 ),	/* 9 */
/* 386 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 388 */	NdrFcShort( 0x10 ),	/* 16 */
/* 390 */	NdrFcShort( 0x8 ),	/* 8 */
/* 392 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 394 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 396 */	NdrFcShort( 0x0 ),	/* 0 */
/* 398 */	NdrFcShort( 0x1 ),	/* 1 */
/* 400 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nCookie */

/* 402 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 404 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 406 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nProp */

/* 408 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 410 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 412 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter vValue */

/* 414 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 416 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 418 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 420 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 422 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 424 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetProp */

/* 426 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 428 */	NdrFcLong( 0x0 ),	/* 0 */
/* 432 */	NdrFcShort( 0xa ),	/* 10 */
/* 434 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 436 */	NdrFcShort( 0x10 ),	/* 16 */
/* 438 */	NdrFcShort( 0x8 ),	/* 8 */
/* 440 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 442 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 444 */	NdrFcShort( 0x1 ),	/* 1 */
/* 446 */	NdrFcShort( 0x0 ),	/* 0 */
/* 448 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nCookie */

/* 450 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 452 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 454 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nProp */

/* 456 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 458 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 460 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pvValue */

/* 462 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 464 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 466 */	NdrFcShort( 0x44a ),	/* Type Offset=1098 */

	/* Return value */

/* 468 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 470 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 472 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Close */

/* 474 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 476 */	NdrFcLong( 0x0 ),	/* 0 */
/* 480 */	NdrFcShort( 0xb ),	/* 11 */
/* 482 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 486 */	NdrFcShort( 0x8 ),	/* 8 */
/* 488 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 490 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 492 */	NdrFcShort( 0x0 ),	/* 0 */
/* 494 */	NdrFcShort( 0x0 ),	/* 0 */
/* 496 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 498 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 500 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 502 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure QuerySinks2 */

/* 504 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 506 */	NdrFcLong( 0x0 ),	/* 0 */
/* 510 */	NdrFcShort( 0xc ),	/* 12 */
/* 512 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 514 */	NdrFcShort( 0x0 ),	/* 0 */
/* 516 */	NdrFcShort( 0x24 ),	/* 36 */
/* 518 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 520 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 522 */	NdrFcShort( 0x1 ),	/* 1 */
/* 524 */	NdrFcShort( 0x0 ),	/* 0 */
/* 526 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pDataLength */

/* 528 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 530 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 532 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpBinaryData */

/* 534 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 536 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 538 */	NdrFcShort( 0x460 ),	/* Type Offset=1120 */

	/* Return value */

/* 540 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 542 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 544 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetProp2 */

/* 546 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 548 */	NdrFcLong( 0x0 ),	/* 0 */
/* 552 */	NdrFcShort( 0xd ),	/* 13 */
/* 554 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 556 */	NdrFcShort( 0x10 ),	/* 16 */
/* 558 */	NdrFcShort( 0x24 ),	/* 36 */
/* 560 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x5,		/* 5 */
/* 562 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 564 */	NdrFcShort( 0x1 ),	/* 1 */
/* 566 */	NdrFcShort( 0x0 ),	/* 0 */
/* 568 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nCookie */

/* 570 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 572 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 574 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nProp */

/* 576 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 578 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 580 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pvValue */

/* 582 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 584 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 586 */	NdrFcShort( 0x44a ),	/* Type Offset=1098 */

	/* Parameter hr */

/* 588 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 590 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 592 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 594 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 596 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 598 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure OnSharedVariableChange */

/* 600 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 602 */	NdrFcLong( 0x0 ),	/* 0 */
/* 606 */	NdrFcShort( 0x3 ),	/* 3 */
/* 608 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 610 */	NdrFcShort( 0x8 ),	/* 8 */
/* 612 */	NdrFcShort( 0x8 ),	/* 8 */
/* 614 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 616 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 618 */	NdrFcShort( 0x0 ),	/* 0 */
/* 620 */	NdrFcShort( 0x1 ),	/* 1 */
/* 622 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lVarNr */

/* 624 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 626 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 628 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nNewValue */

/* 630 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 632 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 634 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 636 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 638 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 640 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure OnNotifyUser */

/* 642 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 644 */	NdrFcLong( 0x0 ),	/* 0 */
/* 648 */	NdrFcShort( 0x4 ),	/* 4 */
/* 650 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 652 */	NdrFcShort( 0x10 ),	/* 16 */
/* 654 */	NdrFcShort( 0x8 ),	/* 8 */
/* 656 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 658 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 660 */	NdrFcShort( 0x0 ),	/* 0 */
/* 662 */	NdrFcShort( 0x1 ),	/* 1 */
/* 664 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nOriginatorCookie */

/* 666 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 668 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 670 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lEvenCode */

/* 672 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 674 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 676 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pDataVariant */

/* 678 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 680 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 682 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 684 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 686 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 688 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure OnProgress */

/* 690 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 692 */	NdrFcLong( 0x0 ),	/* 0 */
/* 696 */	NdrFcShort( 0x5 ),	/* 5 */
/* 698 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 700 */	NdrFcShort( 0x18 ),	/* 24 */
/* 702 */	NdrFcShort( 0x8 ),	/* 8 */
/* 704 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 706 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 708 */	NdrFcShort( 0x0 ),	/* 0 */
/* 710 */	NdrFcShort( 0x0 ),	/* 0 */
/* 712 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nInfoType */

/* 714 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 716 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 718 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lAdvance */

/* 720 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 722 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 724 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lTotal */

/* 726 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 728 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 730 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpDescription */

/* 732 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 734 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 736 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Return value */

/* 738 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 740 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 742 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AskForData */

/* 744 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 746 */	NdrFcLong( 0x0 ),	/* 0 */
/* 750 */	NdrFcShort( 0x3 ),	/* 3 */
/* 752 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 754 */	NdrFcShort( 0x8 ),	/* 8 */
/* 756 */	NdrFcShort( 0x8 ),	/* 8 */
/* 758 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 760 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 762 */	NdrFcShort( 0x1 ),	/* 1 */
/* 764 */	NdrFcShort( 0x1 ),	/* 1 */
/* 766 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nInfoType */

/* 768 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 770 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 772 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpDescription */

/* 774 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 776 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 778 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter varQuestion */

/* 780 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 782 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 784 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter pvarAnswer */

/* 786 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 788 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 790 */	NdrFcShort( 0x44a ),	/* Type Offset=1098 */

	/* Return value */

/* 792 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 794 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 796 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Ping */

/* 798 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 800 */	NdrFcLong( 0x0 ),	/* 0 */
/* 804 */	NdrFcShort( 0x3 ),	/* 3 */
/* 806 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 808 */	NdrFcShort( 0x0 ),	/* 0 */
/* 810 */	NdrFcShort( 0x8 ),	/* 8 */
/* 812 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 814 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 816 */	NdrFcShort( 0x0 ),	/* 0 */
/* 818 */	NdrFcShort( 0x0 ),	/* 0 */
/* 820 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 822 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 824 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 826 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Advise */

/* 828 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 830 */	NdrFcLong( 0x0 ),	/* 0 */
/* 834 */	NdrFcShort( 0x3 ),	/* 3 */
/* 836 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 838 */	NdrFcShort( 0x0 ),	/* 0 */
/* 840 */	NdrFcShort( 0x24 ),	/* 36 */
/* 842 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 844 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 846 */	NdrFcShort( 0x0 ),	/* 0 */
/* 848 */	NdrFcShort( 0x0 ),	/* 0 */
/* 850 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pPingUnknown */

/* 852 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 854 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 856 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter pCookie */

/* 858 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 860 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 862 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 864 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 866 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 868 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Advise */

/* 870 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 872 */	NdrFcLong( 0x0 ),	/* 0 */
/* 876 */	NdrFcShort( 0x3 ),	/* 3 */
/* 878 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 880 */	NdrFcShort( 0x0 ),	/* 0 */
/* 882 */	NdrFcShort( 0x24 ),	/* 36 */
/* 884 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 886 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 888 */	NdrFcShort( 0x0 ),	/* 0 */
/* 890 */	NdrFcShort( 0x0 ),	/* 0 */
/* 892 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pcUserName */

/* 894 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 896 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 898 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pcComputerName */

/* 900 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 902 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 904 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pCookie */

/* 906 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 908 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 910 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 912 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 914 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 916 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Lock */

/* 918 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 920 */	NdrFcLong( 0x0 ),	/* 0 */
/* 924 */	NdrFcShort( 0x5 ),	/* 5 */
/* 926 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 928 */	NdrFcShort( 0x15 ),	/* 21 */
/* 930 */	NdrFcShort( 0x8 ),	/* 8 */
/* 932 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 934 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 936 */	NdrFcShort( 0x0 ),	/* 0 */
/* 938 */	NdrFcShort( 0x1 ),	/* 1 */
/* 940 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nOriginatorCookie */

/* 942 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 944 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 946 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bLock */

/* 948 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 950 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 952 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Parameter nCount */

/* 954 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 956 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 958 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pNavoLock */

/* 960 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 962 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 964 */	NdrFcShort( 0x486 ),	/* Type Offset=1158 */

	/* Return value */

/* 966 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 968 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 970 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Lock_AddItem */

/* 972 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 974 */	NdrFcLong( 0x0 ),	/* 0 */
/* 978 */	NdrFcShort( 0x6 ),	/* 6 */
/* 980 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 982 */	NdrFcShort( 0x30 ),	/* 48 */
/* 984 */	NdrFcShort( 0x8 ),	/* 8 */
/* 986 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x7,		/* 7 */
/* 988 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 990 */	NdrFcShort( 0x0 ),	/* 0 */
/* 992 */	NdrFcShort( 0x0 ),	/* 0 */
/* 994 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter iInx */

/* 996 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 998 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1000 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter iClass */

/* 1002 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1004 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1006 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter iTypeid */

/* 1008 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1010 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1012 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter iIdObj */

/* 1014 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1016 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1018 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter iExtra */

/* 1020 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1022 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1024 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter iLockType */

/* 1026 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1028 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1030 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1032 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1034 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1036 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Lock2 */

/* 1038 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1040 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1044 */	NdrFcShort( 0x7 ),	/* 7 */
/* 1046 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1048 */	NdrFcShort( 0x15 ),	/* 21 */
/* 1050 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1052 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x4,		/* 4 */
/* 1054 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1056 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1058 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1060 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter iOriginatorCookie */

/* 1062 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1064 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1066 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bLock */

/* 1068 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1070 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1072 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Parameter iCount */

/* 1074 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1076 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1078 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1080 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1082 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1084 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateResource */

/* 1086 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1088 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1092 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1094 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1096 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1098 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1100 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1102 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1104 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1106 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1108 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pcResName */

/* 1110 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1112 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1114 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter nMaxUsage */

/* 1116 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1118 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1120 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1122 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1124 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1126 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure DeclareIdent */


	/* Procedure DeleteResource */

/* 1128 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1130 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1134 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1136 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1138 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1140 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1142 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1144 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1146 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1148 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1150 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pcIdentName */


	/* Parameter pcResName */

/* 1152 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1154 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1156 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Return value */


	/* Return value */

/* 1158 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1160 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1162 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UseResource */

/* 1164 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1166 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1170 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1172 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1174 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1176 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1178 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1180 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1182 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1184 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1186 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pcResName */

/* 1188 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1190 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1192 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter nOriginatorCookie */

/* 1194 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1196 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1198 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1200 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1202 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1204 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ReleaseResource */

/* 1206 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1208 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1212 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1214 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1216 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1218 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1220 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1222 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1224 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1226 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1228 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pcResName */

/* 1230 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1232 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1234 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter nOriginatorCookie */

/* 1236 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1238 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1240 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1242 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1244 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1246 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UseResource2 */

/* 1248 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1250 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1254 */	NdrFcShort( 0x7 ),	/* 7 */
/* 1256 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1258 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1260 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1262 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 1264 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1266 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1268 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1270 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pcResName */

/* 1272 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1274 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1276 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter nOriginatorCookie */

/* 1278 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1280 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1282 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter hr */

/* 1284 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1286 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1288 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1290 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1292 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1294 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Begin */

/* 1296 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1298 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1302 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1304 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1306 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1308 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1310 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 1312 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1314 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1316 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1318 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pONSinkUnknown */

/* 1320 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1322 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1324 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter bBackup */

/* 1326 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1328 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1330 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Parameter pParameters */

/* 1332 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1334 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1336 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pSupplyInfo */

/* 1338 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1340 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1342 */	NdrFcShort( 0x49c ),	/* Type Offset=1180 */

	/* Return value */

/* 1344 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1346 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1348 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Init */


	/* Procedure End */

/* 1350 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1352 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1356 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1358 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1360 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1362 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1364 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1366 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1368 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1370 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1372 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */


	/* Return value */

/* 1374 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1376 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1378 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetBackupStream */

/* 1380 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1382 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1386 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1388 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1390 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1392 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1394 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 1396 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1398 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1400 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1402 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppStreamName */

/* 1404 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 1406 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1408 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter ppStreamInfo */

/* 1410 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 1412 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1414 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter ppDataStream */

/* 1416 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1418 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1420 */	NdrFcShort( 0x4ae ),	/* Type Offset=1198 */

	/* Return value */

/* 1422 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1424 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1426 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetRestoreStream */

/* 1428 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1430 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1434 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1436 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1438 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1440 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1442 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 1444 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1446 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1448 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1450 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppStreamName */

/* 1452 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1454 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1456 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter ppStreamInfo */

/* 1458 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 1460 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1462 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter ppDataStream */

/* 1464 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1466 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1468 */	NdrFcShort( 0x4b2 ),	/* Type Offset=1202 */

	/* Parameter i64Length */

/* 1470 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1472 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1474 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 1476 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1478 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1480 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetStat */

/* 1482 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1484 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1488 */	NdrFcShort( 0x7 ),	/* 7 */
/* 1490 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1492 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1494 */	NdrFcShort( 0x40 ),	/* 64 */
/* 1496 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 1498 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1500 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1502 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1504 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pTotalCount */

/* 1506 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1508 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1510 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pTotalSize */

/* 1512 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1514 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1516 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1518 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1520 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1522 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetBackupStream */

/* 1524 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1526 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1530 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1532 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1534 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1536 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1538 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 1540 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1542 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1544 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1546 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppDataStream */

/* 1548 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1550 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1552 */	NdrFcShort( 0x4ae ),	/* Type Offset=1198 */

	/* Parameter ppInfoStream */

/* 1554 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1556 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1558 */	NdrFcShort( 0x4ae ),	/* Type Offset=1198 */

	/* Parameter pONSinkUnknown */

/* 1560 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1562 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1564 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter pISupplyInfo */

/* 1566 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1568 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1570 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Return value */

/* 1572 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1574 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1576 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetRestoreStream */

/* 1578 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1580 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1584 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1586 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1588 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1590 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1592 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 1594 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1596 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1598 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1600 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pDataStream */

/* 1602 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1604 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1606 */	NdrFcShort( 0x4b2 ),	/* Type Offset=1202 */

	/* Parameter pInfoStream */

/* 1608 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1610 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1612 */	NdrFcShort( 0x4b2 ),	/* Type Offset=1202 */

	/* Parameter pONSinkUnknown */

/* 1614 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1616 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1618 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter pISupplyInfo */

/* 1620 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1622 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1624 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Return value */

/* 1626 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1628 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1630 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetProgramObject */


	/* Procedure NewBrSet */

/* 1632 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1634 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1638 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1640 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1642 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1644 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1646 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1648 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1650 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1652 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1654 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppProgramObject */


	/* Parameter ppDispatch */

/* 1656 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1658 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1660 */	NdrFcShort( 0x4c4 ),	/* Type Offset=1220 */

	/* Return value */


	/* Return value */

/* 1662 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1664 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1666 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddBrSet */

/* 1668 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1670 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1674 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1676 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1678 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1680 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1682 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1684 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1686 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1688 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1690 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pDispatch */

/* 1692 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1694 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1696 */	NdrFcShort( 0x186 ),	/* Type Offset=390 */

	/* Return value */

/* 1698 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1700 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1702 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Close */


	/* Procedure RemoveAllBrSets */

/* 1704 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1706 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1710 */	NdrFcShort( 0x7 ),	/* 7 */
/* 1712 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1714 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1716 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1718 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1720 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1722 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1724 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1726 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */


	/* Return value */

/* 1728 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1730 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1732 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure _GetNewEnum */

/* 1734 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1736 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1740 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1742 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1744 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1746 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1748 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1750 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1752 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1754 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1756 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppUnknown */

/* 1758 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1760 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1762 */	NdrFcShort( 0x4c8 ),	/* Type Offset=1224 */

	/* Return value */

/* 1764 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1766 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1768 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetProp */


	/* Procedure SetProp */

/* 1770 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1772 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1776 */	NdrFcShort( 0x9 ),	/* 9 */
/* 1778 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1780 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1782 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1784 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1786 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1788 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1790 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1792 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nProp */


	/* Parameter nProp */

/* 1794 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1796 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1798 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter vValue */


	/* Parameter vValue */

/* 1800 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1802 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1804 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */


	/* Return value */

/* 1806 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1808 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1810 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetProp */

/* 1812 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1814 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1818 */	NdrFcShort( 0xa ),	/* 10 */
/* 1820 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1822 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1824 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1826 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 1828 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1830 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1832 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1834 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nProp */

/* 1836 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1838 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1840 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pvValue */

/* 1842 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 1844 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1846 */	NdrFcShort( 0x44a ),	/* Type Offset=1098 */

	/* Return value */

/* 1848 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1850 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1852 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Get */

/* 1854 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1856 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1860 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1862 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1864 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1866 */	NdrFcShort( 0x41 ),	/* 65 */
/* 1868 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 1870 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1872 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1874 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1876 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter IdFile */

/* 1878 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1880 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1882 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pStream */

/* 1884 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1886 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1888 */	NdrFcShort( 0x4ae ),	/* Type Offset=1198 */

	/* Parameter poNSI */

/* 1890 */	NdrFcShort( 0x2112 ),	/* Flags:  must free, out, simple ref, srv alloc size=8 */
/* 1892 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1894 */	NdrFcShort( 0x4d6 ),	/* Type Offset=1238 */

	/* Return value */

/* 1896 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1898 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1900 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Load */


	/* Procedure AttachInput */

/* 1902 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1904 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1908 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1910 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1912 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1914 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1916 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1918 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1920 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1922 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1924 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pSrcStream */


	/* Parameter pInputStream */

/* 1926 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1928 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1930 */	NdrFcShort( 0x4b2 ),	/* Type Offset=1202 */

	/* Return value */


	/* Return value */

/* 1932 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1934 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1936 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Split */

/* 1938 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1940 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1944 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1946 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1948 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1950 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1952 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1954 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1956 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1958 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1960 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pInputStream */

/* 1962 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1964 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1966 */	NdrFcShort( 0x4b2 ),	/* Type Offset=1202 */

	/* Parameter pSupplyInfo */

/* 1968 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1970 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1972 */	NdrFcShort( 0x49c ),	/* Type Offset=1180 */

	/* Return value */

/* 1974 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1976 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1978 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Join */

/* 1980 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1982 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1986 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1988 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1990 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1992 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1994 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1996 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1998 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2000 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2002 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pSupplyInfo */

/* 2004 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2006 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2008 */	NdrFcShort( 0x49c ),	/* Type Offset=1180 */

	/* Return value */

/* 2010 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2012 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2014 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Next */

/* 2016 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2018 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2022 */	NdrFcShort( 0x3 ),	/* 3 */
/* 2024 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2026 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2028 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2030 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2032 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2034 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2036 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2038 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pFileId */

/* 2040 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2042 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2044 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2046 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2048 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2050 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure NextFull */

/* 2052 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2054 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2058 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2060 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2062 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2064 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2066 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 2068 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2070 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2072 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2074 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pFileId */

/* 2076 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2078 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2080 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter plpValue */

/* 2082 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 2084 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2086 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 2088 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2090 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2092 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetSourceText */


	/* Procedure Init */

/* 2094 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2096 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2100 */	NdrFcShort( 0x3 ),	/* 3 */
/* 2102 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2104 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2106 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2108 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2110 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2112 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2114 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2116 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pcSourceText */


	/* Parameter lpAppName */

/* 2118 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2120 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2122 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Return value */


	/* Return value */

/* 2124 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2126 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2128 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Close */


	/* Procedure Close */

/* 2130 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2132 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2136 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2138 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2140 */	NdrFcShort( 0x5 ),	/* 5 */
/* 2142 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2144 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2146 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2148 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2150 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2152 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bOK */


	/* Parameter bOK */

/* 2154 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2156 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2158 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 2160 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2162 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2164 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure DeleteUser */


	/* Procedure SetOptions */

/* 2166 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2168 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2172 */	NdrFcShort( 0x5 ),	/* 5 */
/* 2174 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2176 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2178 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2180 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2182 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2184 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2186 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2188 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nUserCookie */


	/* Parameter nOptions */

/* 2190 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2192 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2194 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 2196 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2198 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2200 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Upload */

/* 2202 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2204 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2208 */	NdrFcShort( 0x6 ),	/* 6 */
/* 2210 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2212 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2214 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2216 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 2218 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2220 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2222 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2224 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter IdFile */

/* 2226 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2228 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2230 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pStream */

/* 2232 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2234 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2236 */	NdrFcShort( 0x4b2 ),	/* Type Offset=1202 */

	/* Parameter pcExtension */

/* 2238 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2240 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2242 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Return value */

/* 2244 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2246 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2248 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Delete */

/* 2250 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2252 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2256 */	NdrFcShort( 0x7 ),	/* 7 */
/* 2258 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2260 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2262 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2264 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2266 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2268 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2270 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2272 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter IdFile */

/* 2274 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2276 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2278 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2280 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2282 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2284 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateApp */

/* 2286 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2288 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2292 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2294 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2296 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2298 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2300 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 2302 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2304 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2306 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2308 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lpAppName */

/* 2310 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2312 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2314 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter lpLocalRootDirectory */

/* 2316 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2318 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2320 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter lKey */

/* 2322 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2324 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2326 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2328 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2330 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2332 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Purge */


	/* Procedure DropApp */

/* 2334 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2336 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2340 */	NdrFcShort( 0x9 ),	/* 9 */
/* 2342 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2344 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2346 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2348 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2350 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2352 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2354 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2356 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lpFullServerPath */


	/* Parameter lpAppName */

/* 2358 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2360 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2362 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Return value */


	/* Return value */

/* 2364 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2366 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2368 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Pack */

/* 2370 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2372 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2376 */	NdrFcShort( 0xa ),	/* 10 */
/* 2378 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
/* 2380 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2382 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2384 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2386 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2388 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2390 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2392 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter varDestNameOrStream */

/* 2394 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2396 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2398 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter varDestNameOrStreamInfo */

/* 2400 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2402 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2404 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 2406 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2408 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 2410 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Unpack */

/* 2412 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2414 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2418 */	NdrFcShort( 0xb ),	/* 11 */
/* 2420 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
/* 2422 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2424 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2426 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2428 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2430 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2432 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2434 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter varSrcNameOrStream */

/* 2436 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2438 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2440 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Parameter varSrcNameOrStreamInfo */

/* 2442 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2444 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2446 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 2448 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2450 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 2452 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnumFileGroup */

/* 2454 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2456 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2460 */	NdrFcShort( 0xc ),	/* 12 */
/* 2462 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2464 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2466 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2468 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2470 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2472 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2474 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2476 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lpGroupName */

/* 2478 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2480 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2482 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter ppSimpleEnumFileId */

/* 2484 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2486 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2488 */	NdrFcShort( 0x4e0 ),	/* Type Offset=1248 */

	/* Return value */

/* 2490 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2492 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2494 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetItemInfo */

/* 2496 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2498 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2502 */	NdrFcShort( 0xd ),	/* 13 */
/* 2504 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 2506 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2508 */	NdrFcShort( 0x48 ),	/* 72 */
/* 2510 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x6,		/* 6 */
/* 2512 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2514 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2516 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2518 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nInfoType */

/* 2520 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2522 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2524 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter IdFile */

/* 2526 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2528 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2530 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pModifDate */

/* 2532 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2534 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2536 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter pnVarCntr */

/* 2538 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2540 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2542 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppVarNr */

/* 2544 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 2546 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2548 */	NdrFcShort( 0x4fa ),	/* Type Offset=1274 */

	/* Return value */

/* 2550 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2552 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2554 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ChangeMode */

/* 2556 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2558 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2562 */	NdrFcShort( 0xe ),	/* 14 */
/* 2564 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2566 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2568 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2570 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2572 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2574 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2576 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2578 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nNewMode */

/* 2580 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2582 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2584 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2586 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2588 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2590 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetMode */

/* 2592 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2594 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2598 */	NdrFcShort( 0xf ),	/* 15 */
/* 2600 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2602 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2604 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2606 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2608 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2610 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2612 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2614 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pnMode */

/* 2616 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2618 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2620 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2622 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2624 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2626 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetFinalStream */

/* 2628 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2630 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2634 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2636 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2638 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2640 */	NdrFcShort( 0x41 ),	/* 65 */
/* 2642 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 2644 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2646 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2650 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter IdFile */

/* 2652 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2654 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2656 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pcEnvironentStr */

/* 2658 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 2660 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2662 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pStream */

/* 2664 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2666 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2668 */	NdrFcShort( 0x4ae ),	/* Type Offset=1198 */

	/* Parameter poNSI */

/* 2670 */	NdrFcShort( 0x2112 ),	/* Flags:  must free, out, simple ref, srv alloc size=8 */
/* 2672 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2674 */	NdrFcShort( 0x4d6 ),	/* Type Offset=1238 */

	/* Return value */

/* 2676 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2678 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2680 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetItemInfo2 */

/* 2682 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2684 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2688 */	NdrFcShort( 0x11 ),	/* 17 */
/* 2690 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 2692 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2694 */	NdrFcShort( 0x48 ),	/* 72 */
/* 2696 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x6,		/* 6 */
/* 2698 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2700 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2704 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nInfoType */

/* 2706 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2708 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2710 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter IdFile */

/* 2712 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2714 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2716 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pModifDate */

/* 2718 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2720 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2722 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter pnVarCntr */

/* 2724 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2726 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2728 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppVarNr */

/* 2730 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2732 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2734 */	NdrFcShort( 0x460 ),	/* Type Offset=1120 */

	/* Return value */

/* 2736 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2738 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2740 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetAltStreamProvider */

/* 2742 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2744 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2748 */	NdrFcShort( 0x12 ),	/* 18 */
/* 2750 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2752 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2754 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2756 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2758 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2760 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2762 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2764 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pStreamProvider */

/* 2766 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2768 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2770 */	NdrFcShort( 0x50e ),	/* Type Offset=1294 */

	/* Return value */

/* 2772 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2774 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2776 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Fetch */

/* 2778 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2780 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2784 */	NdrFcShort( 0x3 ),	/* 3 */
/* 2786 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 2788 */	NdrFcShort( 0x2a ),	/* 42 */
/* 2790 */	NdrFcShort( 0x40 ),	/* 64 */
/* 2792 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x6,		/* 6 */
/* 2794 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2796 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2798 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2800 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter FetchDirection */

/* 2802 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2804 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2806 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter nCount */

/* 2808 */	NdrFcShort( 0x158 ),	/* Flags:  in, out, base type, simple ref, */
/* 2810 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2812 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pDataLength */

/* 2814 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2816 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2818 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpBinaryData */

/* 2820 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 2822 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2824 */	NdrFcShort( 0x524 ),	/* Type Offset=1316 */

	/* Parameter nAbsolutePosition */

/* 2826 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2828 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2830 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2832 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2834 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2836 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCount */

/* 2838 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2840 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2844 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2846 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2848 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2850 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2852 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2854 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2856 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2858 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2860 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pnCount */

/* 2862 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2864 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2866 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2868 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2870 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2872 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Refresh */

/* 2874 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2876 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2880 */	NdrFcShort( 0x5 ),	/* 5 */
/* 2882 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2884 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2886 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2888 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 2890 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2892 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2894 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2896 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nPositionToKeep */

/* 2898 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2900 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2902 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pnCount */

/* 2904 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2906 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2908 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2910 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2912 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2914 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Fetch2 */

/* 2916 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2918 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2922 */	NdrFcShort( 0x6 ),	/* 6 */
/* 2924 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 2926 */	NdrFcShort( 0x2a ),	/* 42 */
/* 2928 */	NdrFcShort( 0x40 ),	/* 64 */
/* 2930 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x6,		/* 6 */
/* 2932 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 2934 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2936 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2938 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter FetchDirection */

/* 2940 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2942 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2944 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter nCount */

/* 2946 */	NdrFcShort( 0x158 ),	/* Flags:  in, out, base type, simple ref, */
/* 2948 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2950 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pDataLength */

/* 2952 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2954 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2956 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpBinaryData */

/* 2958 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 2960 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2962 */	NdrFcShort( 0x460 ),	/* Type Offset=1120 */

	/* Parameter nAbsolutePosition */

/* 2964 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2966 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2968 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2970 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2972 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2974 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetCoManagers */

/* 2976 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2978 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2982 */	NdrFcShort( 0x3 ),	/* 3 */
/* 2984 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2986 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2988 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2990 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 2992 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2994 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2996 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2998 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pcAppName */

/* 3000 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3002 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3004 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pLockManager */

/* 3006 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 3008 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3010 */	NdrFcShort( 0x538 ),	/* Type Offset=1336 */

	/* Parameter nLockManCookie */

/* 3012 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3014 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3016 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nOptions */

/* 3018 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3020 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3022 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3024 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3026 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3028 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MakeTransaction */

/* 3030 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3032 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3036 */	NdrFcShort( 0x5 ),	/* 5 */
/* 3038 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 3040 */	NdrFcShort( 0x1d ),	/* 29 */
/* 3042 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3044 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x8,		/* 8 */
/* 3046 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3048 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3050 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3052 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nDataLength */

/* 3054 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3056 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3058 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpBinaryData */

/* 3060 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 3062 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3064 */	NdrFcShort( 0x54a ),	/* Type Offset=1354 */

	/* Parameter nBlobInfoCount */

/* 3066 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3068 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3070 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pBlobInfo */

/* 3072 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 3074 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3076 */	NdrFcShort( 0x55a ),	/* Type Offset=1370 */

	/* Parameter nWriteLockCount */

/* 3078 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3080 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3082 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pNavoLock */

/* 3084 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 3086 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3088 */	NdrFcShort( 0x588 ),	/* Type Offset=1416 */

	/* Parameter bCommit */

/* 3090 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3092 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 3094 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 3096 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3098 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 3100 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure FinishTransaction */

/* 3102 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3104 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3108 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3110 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3112 */	NdrFcShort( 0x5 ),	/* 5 */
/* 3114 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3116 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3118 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3120 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3122 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3124 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bSuccess */

/* 3126 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3128 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3130 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 3132 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3134 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3136 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetObjectIfNewer */

/* 3138 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3140 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3144 */	NdrFcShort( 0x7 ),	/* 7 */
/* 3146 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 3148 */	NdrFcShort( 0x1d ),	/* 29 */
/* 3150 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3152 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x7,		/* 7 */
/* 3154 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3156 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3158 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3160 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter TypeId */

/* 3162 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3164 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3166 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter IdObj */

/* 3168 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3170 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3172 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter VersionNoReturn */

/* 3174 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3176 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3178 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bWriteLock */

/* 3180 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3182 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3184 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Parameter pDataLength */

/* 3186 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3188 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3190 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpBinaryData */

/* 3192 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 3194 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3196 */	NdrFcShort( 0x5a2 ),	/* Type Offset=1442 */

	/* Return value */

/* 3198 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3200 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 3202 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetStream */

/* 3204 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3206 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3210 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3212 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 3214 */	NdrFcShort( 0x10 ),	/* 16 */
/* 3216 */	NdrFcShort( 0x79 ),	/* 121 */
/* 3218 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x7,		/* 7 */
/* 3220 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3222 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3224 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3226 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter IdParent */

/* 3228 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3230 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3232 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter IdMapping */

/* 3234 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3236 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3238 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pStream */

/* 3240 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3242 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3244 */	NdrFcShort( 0x4ae ),	/* Type Offset=1198 */

	/* Parameter poNSI */

/* 3246 */	NdrFcShort( 0x2112 ),	/* Flags:  must free, out, simple ref, srv alloc size=8 */
/* 3248 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3250 */	NdrFcShort( 0x4d6 ),	/* Type Offset=1238 */

	/* Parameter pVersion */

/* 3252 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3254 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3256 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pStreamId */

/* 3258 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3260 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3262 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3264 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3266 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 3268 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetUniqueIdent */

/* 3270 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3272 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3276 */	NdrFcShort( 0x9 ),	/* 9 */
/* 3278 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3280 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3282 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3284 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 3286 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3288 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3290 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3292 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter TypeId */

/* 3294 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3296 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3298 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pNewId */

/* 3300 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3302 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3304 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3306 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3308 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3310 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure FindOnField */

/* 3312 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3314 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3318 */	NdrFcShort( 0xa ),	/* 10 */
/* 3320 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3322 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3324 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3326 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 3328 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3330 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3332 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3334 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nTypeId */

/* 3336 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3338 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3340 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpWhereClause */

/* 3342 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3344 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3346 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pFoundId */

/* 3348 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3350 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3352 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3354 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3356 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3358 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure OpenOnStatement */

/* 3360 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3362 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3366 */	NdrFcShort( 0xb ),	/* 11 */
/* 3368 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 3370 */	NdrFcShort( 0x15 ),	/* 21 */
/* 3372 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3374 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x8,		/* 8 */
/* 3376 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3378 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3380 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3382 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter TypeId */

/* 3384 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3386 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3388 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpWhereClause */

/* 3390 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3392 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3394 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter lpOrderByClause */

/* 3396 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3398 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3400 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter lpJoinClause */

/* 3402 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3404 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3406 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter bForwardOnly */

/* 3408 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3410 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3412 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Parameter nTop */

/* 3414 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3416 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3418 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pCollection */

/* 3420 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3422 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 3424 */	NdrFcShort( 0x5b6 ),	/* Type Offset=1462 */

	/* Return value */

/* 3426 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3428 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 3430 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure OpenCollection */

/* 3432 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3434 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3438 */	NdrFcShort( 0xc ),	/* 12 */
/* 3440 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3442 */	NdrFcShort( 0x10 ),	/* 16 */
/* 3444 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3446 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x5,		/* 5 */
/* 3448 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3450 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3452 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3454 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter CollectionId */

/* 3456 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3458 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3460 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter IdParent */

/* 3462 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3464 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3466 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pTotalCount */

/* 3468 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3470 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3472 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pCollection */

/* 3474 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3476 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3478 */	NdrFcShort( 0x5b6 ),	/* Type Offset=1462 */

	/* Return value */

/* 3480 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3482 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3484 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure OpenFTSQuery */

/* 3486 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3488 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3492 */	NdrFcShort( 0xd ),	/* 13 */
/* 3494 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3496 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3498 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3500 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 3502 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3504 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3506 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3508 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter IdMapping */

/* 3510 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3512 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3514 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpQuery */

/* 3516 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3518 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3520 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pCollection */

/* 3522 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3524 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3526 */	NdrFcShort( 0x5b6 ),	/* Type Offset=1462 */

	/* Return value */

/* 3528 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3530 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3532 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure OpenDiscoRecSet */

/* 3534 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3536 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3540 */	NdrFcShort( 0xe ),	/* 14 */
/* 3542 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3544 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3546 */	NdrFcShort( 0x41 ),	/* 65 */
/* 3548 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 3550 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3552 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3556 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lpSQLClause */

/* 3558 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3560 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3562 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pADORecordset */

/* 3564 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3566 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3568 */	NdrFcShort( 0x4ae ),	/* Type Offset=1198 */

	/* Parameter poNSI */

/* 3570 */	NdrFcShort( 0x2112 ),	/* Flags:  must free, out, simple ref, srv alloc size=8 */
/* 3572 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3574 */	NdrFcShort( 0x4d6 ),	/* Type Offset=1238 */

	/* Return value */

/* 3576 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3578 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3580 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CanDelete */

/* 3582 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3584 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3588 */	NdrFcShort( 0xf ),	/* 15 */
/* 3590 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3592 */	NdrFcShort( 0x10 ),	/* 16 */
/* 3594 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3596 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 3598 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3602 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3604 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nTypeId */

/* 3606 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3608 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3610 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter IdObj */

/* 3612 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3614 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3616 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pADORecordset */

/* 3618 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3620 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3622 */	NdrFcShort( 0x4c4 ),	/* Type Offset=1220 */

	/* Return value */

/* 3624 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3626 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3628 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetProp */

/* 3630 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3632 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3636 */	NdrFcShort( 0x10 ),	/* 16 */
/* 3638 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 3640 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3642 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3644 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 3646 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3650 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3652 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nProp */

/* 3654 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3656 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3658 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter vValue */

/* 3660 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3662 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3664 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 3666 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3668 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3670 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetProp */

/* 3672 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3674 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3678 */	NdrFcShort( 0x11 ),	/* 17 */
/* 3680 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3682 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3684 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3686 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 3688 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3690 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3692 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3694 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nProp */

/* 3696 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3698 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3700 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pvValue */

/* 3702 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 3704 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3706 */	NdrFcShort( 0x44a ),	/* Type Offset=1098 */

	/* Return value */

/* 3708 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3710 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3712 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ExecSQL */

/* 3714 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3716 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3720 */	NdrFcShort( 0x12 ),	/* 18 */
/* 3722 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3724 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3726 */	NdrFcShort( 0x24 ),	/* 36 */
/* 3728 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 3730 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3732 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3734 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3736 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lpSQLCommand */

/* 3738 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3740 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3742 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pRecordsAffected */

/* 3744 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3746 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3748 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3750 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3752 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3754 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetSharedVariable */

/* 3756 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3758 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3762 */	NdrFcShort( 0x13 ),	/* 19 */
/* 3764 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 3766 */	NdrFcShort( 0x10 ),	/* 16 */
/* 3768 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3770 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 3772 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3774 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3776 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3778 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nOriginatorCookie */

/* 3780 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3782 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3784 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lVarNr */

/* 3786 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3788 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3790 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nNewValue */

/* 3792 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3794 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3796 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 3798 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3800 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 3802 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetSharedVariable */

/* 3804 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3806 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3810 */	NdrFcShort( 0x14 ),	/* 20 */
/* 3812 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3814 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3816 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3818 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 3820 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3822 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3824 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3826 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lVarNr */

/* 3828 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3830 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3832 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pvValue */

/* 3834 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 3836 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3838 */	NdrFcShort( 0x44a ),	/* Type Offset=1098 */

	/* Return value */

/* 3840 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3842 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3844 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateExtension */

/* 3846 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3848 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3852 */	NdrFcShort( 0x15 ),	/* 21 */
/* 3854 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3856 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3858 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3860 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 3862 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3864 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3866 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3868 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lpExtensionProgId */

/* 3870 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3872 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3874 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pExtensionDisp */

/* 3876 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3878 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3880 */	NdrFcShort( 0x4c4 ),	/* Type Offset=1220 */

	/* Return value */

/* 3882 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3884 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3886 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure WriteToArchive */

/* 3888 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3890 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3894 */	NdrFcShort( 0x16 ),	/* 22 */
/* 3896 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3898 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3900 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3902 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 3904 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3906 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3908 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3910 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lpSAUser */

/* 3912 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3914 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3916 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter lpPwd */

/* 3918 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3920 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3922 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter lpArchivePwd */

/* 3924 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3926 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3928 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pDestStream */

/* 3930 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 3932 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3934 */	NdrFcShort( 0x4b2 ),	/* Type Offset=1202 */

	/* Return value */

/* 3936 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3938 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3940 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ReadFromArchive */

/* 3942 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3944 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3948 */	NdrFcShort( 0x17 ),	/* 23 */
/* 3950 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3952 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3954 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3956 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 3958 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3960 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3962 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3964 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lpSAUser */

/* 3966 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3968 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3970 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter lpPwd */

/* 3972 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3974 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3976 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter lpArchivePwd */

/* 3978 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 3980 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3982 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pSrcStream */

/* 3984 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 3986 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3988 */	NdrFcShort( 0x4b2 ),	/* Type Offset=1202 */

	/* Return value */

/* 3990 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3992 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3994 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MakeTransaction2 */

/* 3996 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3998 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4002 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4004 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 4006 */	NdrFcShort( 0xd ),	/* 13 */
/* 4008 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4010 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 4012 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4014 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4016 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4018 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pBinaryData */

/* 4020 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 4022 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4024 */	NdrFcShort( 0x5d0 ),	/* Type Offset=1488 */

	/* Parameter iLockCount */

/* 4026 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4028 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4030 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bCommit */

/* 4032 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4034 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4036 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Parameter lpExtras */

/* 4038 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 4040 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4042 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter lpResult */

/* 4044 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 4046 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4048 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 4050 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4052 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 4054 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetObjectIfNewer2 */

/* 4056 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4058 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4062 */	NdrFcShort( 0x19 ),	/* 25 */
/* 4064 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 4066 */	NdrFcShort( 0x1d ),	/* 29 */
/* 4068 */	NdrFcShort( 0x40 ),	/* 64 */
/* 4070 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x8,		/* 8 */
/* 4072 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 4074 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4076 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4078 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter TypeId */

/* 4080 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4082 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4084 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter IdObj */

/* 4086 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4088 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4090 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter VersionNoReturn */

/* 4092 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4094 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4096 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bWriteLock */

/* 4098 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4100 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4102 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Parameter pDataLength */

/* 4104 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 4106 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4108 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpBinaryData */

/* 4110 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4112 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 4114 */	NdrFcShort( 0x460 ),	/* Type Offset=1120 */

	/* Parameter hr */

/* 4116 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 4118 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 4120 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 4122 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4124 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 4126 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MakeTransaction_Stream */

/* 4128 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4130 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4134 */	NdrFcShort( 0x1a ),	/* 26 */
/* 4136 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 4138 */	NdrFcShort( 0x35 ),	/* 53 */
/* 4140 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4142 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 4144 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4146 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4148 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4150 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pSrcStream */

/* 4152 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 4154 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4156 */	NdrFcShort( 0x4b2 ),	/* Type Offset=1202 */

	/* Parameter IdParent */

/* 4158 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4160 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4162 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter IdMapping */

/* 4164 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4166 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4168 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter NSI */

/* 4170 */	NdrFcShort( 0x8a ),	/* Flags:  must free, in, by val, */
/* 4172 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4174 */	NdrFcShort( 0x4d6 ),	/* Type Offset=1238 */

	/* Return value */

/* 4176 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4178 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 4180 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure OpenDiscoRecSet2 */

/* 4182 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4184 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4188 */	NdrFcShort( 0x1b ),	/* 27 */
/* 4190 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4192 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4194 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4196 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 4198 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4200 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4202 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4204 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lpSQLClause */

/* 4206 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 4208 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4210 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pADORecordset */

/* 4212 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4214 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4216 */	NdrFcShort( 0x4c8 ),	/* Type Offset=1224 */

	/* Return value */

/* 4218 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4220 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4222 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateADOCommand */

/* 4224 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4226 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4230 */	NdrFcShort( 0x1c ),	/* 28 */
/* 4232 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4236 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4238 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4240 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4242 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4244 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4246 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pADOCommand */

/* 4248 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4250 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4252 */	NdrFcShort( 0x4c8 ),	/* Type Offset=1224 */

	/* Return value */

/* 4254 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4256 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4258 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateADOParameter */

/* 4260 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4262 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4266 */	NdrFcShort( 0x1d ),	/* 29 */
/* 4268 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4270 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4272 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4274 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4276 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4278 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4280 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4282 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pADOParameter */

/* 4284 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4286 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4288 */	NdrFcShort( 0x4c8 ),	/* Type Offset=1224 */

	/* Return value */

/* 4290 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4292 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4294 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Lock_AddItem */

/* 4296 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4298 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4302 */	NdrFcShort( 0x1e ),	/* 30 */
/* 4304 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 4306 */	NdrFcShort( 0x30 ),	/* 48 */
/* 4308 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4310 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x7,		/* 7 */
/* 4312 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4314 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4316 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4318 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter iInx */

/* 4320 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4322 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4324 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter iClass */

/* 4326 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4328 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4330 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter iTypeid */

/* 4332 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4334 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4336 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter iIdObj */

/* 4338 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4340 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4342 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter iExtra */

/* 4344 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4346 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4348 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter iLockType */

/* 4350 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4352 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 4354 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 4356 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4358 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 4360 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PurgeCache */

/* 4362 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4364 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4368 */	NdrFcShort( 0x1f ),	/* 31 */
/* 4370 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4372 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4374 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4376 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 4378 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4380 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4382 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4384 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 4386 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4388 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4390 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetDBConnection */

/* 4392 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4394 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4398 */	NdrFcShort( 0x3 ),	/* 3 */
/* 4400 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4402 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4404 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4406 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4408 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4410 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4412 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4414 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppDBConnection */

/* 4416 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4418 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4420 */	NdrFcShort( 0x4c8 ),	/* Type Offset=1224 */

	/* Return value */

/* 4422 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4424 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4426 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Lock */

/* 4428 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4430 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4434 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4436 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 4438 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4440 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4442 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 4444 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4446 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4448 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4450 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter oNavoLock */

/* 4452 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4454 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4456 */	NdrFcShort( 0x478 ),	/* Type Offset=1144 */

	/* Return value */

/* 4458 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4460 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 4462 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UnLock */

/* 4464 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4466 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4470 */	NdrFcShort( 0x5 ),	/* 5 */
/* 4472 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 4474 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4476 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4478 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 4480 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4482 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4486 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter oNavoLock */

/* 4488 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4490 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4492 */	NdrFcShort( 0x478 ),	/* Type Offset=1144 */

	/* Return value */

/* 4494 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4496 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 4498 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Init */

/* 4500 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4502 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4506 */	NdrFcShort( 0x3 ),	/* 3 */
/* 4508 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4510 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4512 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4514 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 4516 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4518 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4520 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4522 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pHost */

/* 4524 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 4526 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4528 */	NdrFcShort( 0x5da ),	/* Type Offset=1498 */

	/* Return value */

/* 4530 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4532 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4534 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetData */

/* 4536 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4538 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4542 */	NdrFcShort( 0x3 ),	/* 3 */
/* 4544 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4546 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4548 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4550 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 4552 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4556 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4558 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter IdFile */

/* 4560 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4562 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4564 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppDataStream */

/* 4566 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4568 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4570 */	NdrFcShort( 0x4ae ),	/* Type Offset=1198 */

	/* Return value */

/* 4572 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4574 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4576 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PutData */

/* 4578 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4580 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4584 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4586 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4588 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4590 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4592 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 4594 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4596 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4598 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4600 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter IdFile */

/* 4602 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4604 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4606 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pDataStream */

/* 4608 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 4610 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4612 */	NdrFcShort( 0x4b2 ),	/* Type Offset=1202 */

	/* Return value */

/* 4614 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4616 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4618 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Init */

/* 4620 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4622 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4626 */	NdrFcShort( 0x3 ),	/* 3 */
/* 4628 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4630 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4632 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4634 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 4636 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4638 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4640 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4642 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pEnvironmentDisp */

/* 4644 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 4646 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4648 */	NdrFcShort( 0x186 ),	/* Type Offset=390 */

	/* Parameter pStreamProvider */

/* 4650 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 4652 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4654 */	NdrFcShort( 0x50e ),	/* Type Offset=1294 */

	/* Parameter pDataCache */

/* 4656 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 4658 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4660 */	NdrFcShort( 0x5ec ),	/* Type Offset=1516 */

	/* Return value */

/* 4662 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4664 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4666 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PreprocessFile */

/* 4668 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4670 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4674 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4676 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4678 */	NdrFcShort( 0xd ),	/* 13 */
/* 4680 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4682 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 4684 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4686 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4688 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4690 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter IdFile */

/* 4692 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4694 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4696 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bParseMode */

/* 4698 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4700 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4702 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 4704 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4706 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4708 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetVarDependencies */

/* 4710 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4712 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4716 */	NdrFcShort( 0x5 ),	/* 5 */
/* 4718 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4720 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4722 */	NdrFcShort( 0x24 ),	/* 36 */
/* 4724 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 4726 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 4728 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4730 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4732 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pnVarCntr */

/* 4734 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 4736 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4738 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppVarNr */

/* 4740 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 4742 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4744 */	NdrFcShort( 0x5fe ),	/* Type Offset=1534 */

	/* Return value */

/* 4746 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4748 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4750 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetIncludeDependencies */

/* 4752 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4754 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4758 */	NdrFcShort( 0x6 ),	/* 6 */
/* 4760 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4762 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4764 */	NdrFcShort( 0x24 ),	/* 36 */
/* 4766 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 4768 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 4770 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4772 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4774 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pnFileCntr */

/* 4776 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 4778 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4780 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppIdFile */

/* 4782 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 4784 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4786 */	NdrFcShort( 0x5fe ),	/* Type Offset=1534 */

	/* Return value */

/* 4788 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4790 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4792 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Close */

/* 4794 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4796 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4800 */	NdrFcShort( 0x3 ),	/* 3 */
/* 4802 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4804 */	NdrFcShort( 0x5 ),	/* 5 */
/* 4806 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4808 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4810 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4812 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4814 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4816 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bOK */

/* 4818 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4820 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4822 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 4824 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4826 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4828 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetItem */

/* 4830 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4832 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4836 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4838 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 4840 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4842 */	NdrFcShort( 0x41 ),	/* 65 */
/* 4844 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x7,		/* 7 */
/* 4846 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4848 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4850 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4852 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter IdFile */

/* 4854 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4856 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4858 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpFullServerPath */

/* 4860 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 4862 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4864 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter DescriptorLength */

/* 4866 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4868 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4870 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpDescriptor */

/* 4872 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 4874 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4876 */	NdrFcShort( 0x612 ),	/* Type Offset=1554 */

	/* Parameter ppDataStream */

/* 4878 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4880 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4882 */	NdrFcShort( 0x4ae ),	/* Type Offset=1198 */

	/* Parameter poNSI */

/* 4884 */	NdrFcShort( 0x2112 ),	/* Flags:  must free, out, simple ref, srv alloc size=8 */
/* 4886 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 4888 */	NdrFcShort( 0x4d6 ),	/* Type Offset=1238 */

	/* Return value */

/* 4890 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4892 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 4894 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure StoreItem */

/* 4896 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4898 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4902 */	NdrFcShort( 0x5 ),	/* 5 */
/* 4904 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 4906 */	NdrFcShort( 0x51 ),	/* 81 */
/* 4908 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4910 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x8,		/* 8 */
/* 4912 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4914 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4916 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4918 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter IdFile */

/* 4920 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4922 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4924 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpFullServerPath */

/* 4926 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 4928 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4930 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter DescriptorLength */

/* 4932 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4934 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4936 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpDescriptor */

/* 4938 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 4940 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4942 */	NdrFcShort( 0x612 ),	/* Type Offset=1554 */

	/* Parameter TransactionId */

/* 4944 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4946 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4948 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter poNSI */

/* 4950 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 4952 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 4954 */	NdrFcShort( 0x4d6 ),	/* Type Offset=1238 */

	/* Parameter ppDataStream */

/* 4956 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4958 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 4960 */	NdrFcShort( 0x4ae ),	/* Type Offset=1198 */

	/* Return value */

/* 4962 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4964 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 4966 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RemoveItem */

/* 4968 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4970 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4974 */	NdrFcShort( 0x6 ),	/* 6 */
/* 4976 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 4978 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4980 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4982 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 4984 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4986 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4988 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4990 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter IdFile */

/* 4992 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4994 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4996 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpFullServerPath */

/* 4998 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 5000 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5002 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter DescriptorLength */

/* 5004 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5006 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5008 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpDescriptor */

/* 5010 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 5012 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5014 */	NdrFcShort( 0x612 ),	/* Type Offset=1554 */

	/* Parameter TransactionId */

/* 5016 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5018 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 5020 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5022 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5024 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 5026 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure BeginTransaction */

/* 5028 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5030 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5034 */	NdrFcShort( 0x7 ),	/* 7 */
/* 5036 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5038 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5040 */	NdrFcShort( 0x24 ),	/* 36 */
/* 5042 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5044 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5046 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5048 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5050 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pTransacionId */

/* 5052 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 5054 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5056 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5058 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5060 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5062 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure FinishTransaction */

/* 5064 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5066 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5070 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5072 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5074 */	NdrFcShort( 0xd ),	/* 13 */
/* 5076 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5078 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 5080 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5082 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5084 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5086 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter TransactionId */

/* 5088 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5090 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5092 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bSuccess */

/* 5094 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5096 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5098 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 5100 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5102 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5104 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetUniqueIdent */

/* 5106 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5108 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5112 */	NdrFcShort( 0xa ),	/* 10 */
/* 5114 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5116 */	NdrFcShort( 0x1c ),	/* 28 */
/* 5118 */	NdrFcShort( 0x24 ),	/* 36 */
/* 5120 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5122 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5128 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pNewId */

/* 5130 */	NdrFcShort( 0x158 ),	/* Flags:  in, out, base type, simple ref, */
/* 5132 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5134 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5136 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5138 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5140 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCacheInfoGUID */

/* 5142 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5144 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5148 */	NdrFcShort( 0xb ),	/* 11 */
/* 5150 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5152 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5154 */	NdrFcShort( 0x4c ),	/* 76 */
/* 5156 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 5158 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5160 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5164 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lpFullServerPath */

/* 5166 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 5168 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5170 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pGUID */

/* 5172 */	NdrFcShort( 0x4112 ),	/* Flags:  must free, out, simple ref, srv alloc size=16 */
/* 5174 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5176 */	NdrFcShort( 0x2fc ),	/* Type Offset=764 */

	/* Return value */

/* 5178 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5180 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5182 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure FTSQuery */

/* 5184 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5186 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5190 */	NdrFcShort( 0xc ),	/* 12 */
/* 5192 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 5194 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5196 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5198 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 5200 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5202 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5204 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5206 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lpFullServerPath */

/* 5208 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 5210 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5212 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter lpQuery */

/* 5214 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 5216 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5218 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter ppSimpleEnumFileId */

/* 5220 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 5222 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5224 */	NdrFcShort( 0x4e0 ),	/* Type Offset=1248 */

	/* Return value */

/* 5226 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5228 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5230 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetOptions */

/* 5232 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5234 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5238 */	NdrFcShort( 0xd ),	/* 13 */
/* 5240 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5242 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5244 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5246 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5248 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5252 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5254 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nOptions */

/* 5256 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5258 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5260 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5262 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5264 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5266 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure StoreDataObject */

/* 5268 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5270 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5274 */	NdrFcShort( 0xe ),	/* 14 */
/* 5276 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 5278 */	NdrFcShort( 0x20 ),	/* 32 */
/* 5280 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5282 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x7,		/* 7 */
/* 5284 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 5286 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5288 */	NdrFcShort( 0x1 ),	/* 1 */
/* 5290 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lpFullServerPath */

/* 5292 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 5294 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5296 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter nTypeId */

/* 5298 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5300 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5302 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nIdObj */

/* 5304 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5306 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5308 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nVersion */

/* 5310 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5312 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5314 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nDataLength */

/* 5316 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5318 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 5320 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pData */

/* 5322 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 5324 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 5326 */	NdrFcShort( 0x62a ),	/* Type Offset=1578 */

	/* Return value */

/* 5328 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5330 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 5332 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RetrieveDataObject */

/* 5334 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5336 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5340 */	NdrFcShort( 0xf ),	/* 15 */
/* 5342 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 5344 */	NdrFcShort( 0x18 ),	/* 24 */
/* 5346 */	NdrFcShort( 0x24 ),	/* 36 */
/* 5348 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x7,		/* 7 */
/* 5350 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 5352 */	NdrFcShort( 0x1 ),	/* 1 */
/* 5354 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5356 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lpFullServerPath */

/* 5358 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 5360 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5362 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter nTypeId */

/* 5364 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5366 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5368 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nIdObj */

/* 5370 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5372 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5374 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nVersion */

/* 5376 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5378 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5380 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pDataLength */

/* 5382 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 5384 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 5386 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppData */

/* 5388 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 5390 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 5392 */	NdrFcShort( 0x5a2 ),	/* Type Offset=1442 */

	/* Return value */

/* 5394 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5396 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 5398 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure WriteToArchive */

/* 5400 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5402 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5406 */	NdrFcShort( 0x10 ),	/* 16 */
/* 5408 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5410 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5412 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5414 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 5416 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5418 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5420 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5422 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lpFullServerPath */

/* 5424 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 5426 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5428 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pDestStream */

/* 5430 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 5432 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5434 */	NdrFcShort( 0x4b2 ),	/* Type Offset=1202 */

	/* Return value */

/* 5436 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5438 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5440 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ReadFromArchive */

/* 5442 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5444 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5448 */	NdrFcShort( 0x11 ),	/* 17 */
/* 5450 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5452 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5454 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5456 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 5458 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5460 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5462 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5464 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lpFullServerPath */

/* 5466 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 5468 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5470 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pSrcStream */

/* 5472 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 5474 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5476 */	NdrFcShort( 0x4b2 ),	/* Type Offset=1202 */

	/* Return value */

/* 5478 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5480 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5482 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetService */

/* 5484 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5486 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5490 */	NdrFcShort( 0x3 ),	/* 3 */
/* 5492 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5494 */	NdrFcShort( 0x6 ),	/* 6 */
/* 5496 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5498 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 5500 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5502 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5504 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5506 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter eNST */

/* 5508 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5510 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5512 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter ppUnknown */

/* 5514 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 5516 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5518 */	NdrFcShort( 0x4c8 ),	/* Type Offset=1224 */

	/* Return value */

/* 5520 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5522 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5524 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetUpdateVersionIfNewer */

/* 5526 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5528 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5532 */	NdrFcShort( 0x4 ),	/* 4 */
/* 5534 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 5536 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5538 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5540 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 5542 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5544 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5546 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5548 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nUpdateType */

/* 5550 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5552 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5554 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpClientVersion */

/* 5556 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 5558 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5560 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter ppDataStream */

/* 5562 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 5564 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5566 */	NdrFcShort( 0x4ae ),	/* Type Offset=1198 */

	/* Parameter ppInfoStream */

/* 5568 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 5570 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5572 */	NdrFcShort( 0x4ae ),	/* Type Offset=1198 */

	/* Return value */

/* 5574 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5576 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 5578 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AdviseLM */

/* 5580 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5582 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5586 */	NdrFcShort( 0x5 ),	/* 5 */
/* 5588 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 5590 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5592 */	NdrFcShort( 0x24 ),	/* 36 */
/* 5594 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 5596 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5598 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5602 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pcUserName */

/* 5604 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 5606 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5608 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pcComputerName */

/* 5610 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 5612 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5614 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pCookie */

/* 5616 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 5618 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5620 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5622 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5624 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5626 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UnAdviseLM */

/* 5628 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5630 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5634 */	NdrFcShort( 0x6 ),	/* 6 */
/* 5636 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5638 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5640 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5642 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5644 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5646 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5650 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nCookie */

/* 5652 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5654 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5656 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5658 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5660 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5662 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AdviseNM */

/* 5664 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5666 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5670 */	NdrFcShort( 0x7 ),	/* 7 */
/* 5672 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 5674 */	NdrFcShort( 0x6 ),	/* 6 */
/* 5676 */	NdrFcShort( 0x24 ),	/* 36 */
/* 5678 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 5680 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5682 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5684 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5686 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pONSinkUnknown */

/* 5688 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 5690 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5692 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter pcUserName */

/* 5694 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 5696 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5698 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter pcComputerName */

/* 5700 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 5702 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5704 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter eNSC */

/* 5706 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5708 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5710 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pCookie */

/* 5712 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 5714 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 5716 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5718 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5720 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 5722 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UnAdviseNM */

/* 5724 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5726 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5730 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5732 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5734 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5736 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5738 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5740 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5742 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5744 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5746 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nCookie */

/* 5748 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5750 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5752 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5754 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5756 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5758 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetRegistryKeyString */

/* 5760 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5762 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5766 */	NdrFcShort( 0x9 ),	/* 9 */
/* 5768 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 5770 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5772 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5774 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 5776 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5778 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5780 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5782 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hKeyClass */

/* 5784 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5786 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5788 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpSubKey */

/* 5790 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 5792 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5794 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter lpName */

/* 5796 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 5798 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5800 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter plpValue */

/* 5802 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 5804 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5806 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 5808 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5810 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 5812 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetRegistryKeyString */

/* 5814 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5816 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5820 */	NdrFcShort( 0xa ),	/* 10 */
/* 5822 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 5824 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5826 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5828 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 5830 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5832 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5834 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5836 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hKeyClass */

/* 5838 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5840 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5842 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpSubKey */

/* 5844 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 5846 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5848 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter lpName */

/* 5850 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 5852 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5854 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter lpValue */

/* 5856 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 5858 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5860 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Return value */

/* 5862 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5864 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 5866 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnumRegistryKeys */

/* 5868 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5870 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5874 */	NdrFcShort( 0xb ),	/* 11 */
/* 5876 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 5878 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5880 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5882 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 5884 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5886 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5888 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5890 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hKeyClass */

/* 5892 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5894 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5896 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lpSubKey */

/* 5898 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 5900 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5902 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter plpValue */

/* 5904 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 5906 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5908 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 5910 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5912 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5914 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetUniqueId */

/* 5916 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5918 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5922 */	NdrFcShort( 0xc ),	/* 12 */
/* 5924 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5926 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5928 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5930 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 5932 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5934 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5936 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5938 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppUniqueId */

/* 5940 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 5942 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5944 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 5946 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5948 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5950 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Close2 */

/* 5952 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5954 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5958 */	NdrFcShort( 0xd ),	/* 13 */
/* 5960 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5962 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5964 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5966 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 5968 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5970 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5972 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5974 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 5976 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5978 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5980 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetServerClient */

/* 5982 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5984 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5988 */	NdrFcShort( 0x3 ),	/* 3 */
/* 5990 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 5992 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5994 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5996 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 5998 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6000 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6002 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6004 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lpServerName */

/* 6006 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 6008 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6010 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter lpAppID */

/* 6012 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 6014 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6016 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Parameter ppServerClient */

/* 6018 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6020 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6022 */	NdrFcShort( 0x63a ),	/* Type Offset=1594 */

	/* Return value */

/* 6024 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6026 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 6028 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetProp */

/* 6030 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6032 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6036 */	NdrFcShort( 0x3 ),	/* 3 */
/* 6038 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 6040 */	NdrFcShort( 0x24 ),	/* 36 */
/* 6042 */	NdrFcShort( 0x24 ),	/* 36 */
/* 6044 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 6046 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 6048 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6050 */	NdrFcShort( 0x1 ),	/* 1 */
/* 6052 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pnUserCookie */

/* 6054 */	NdrFcShort( 0x158 ),	/* Flags:  in, out, base type, simple ref, */
/* 6056 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6058 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nProp */

/* 6060 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 6062 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6064 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pvValue */

/* 6066 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 6068 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6070 */	NdrFcShort( 0x424 ),	/* Type Offset=1060 */

	/* Return value */

/* 6072 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6074 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 6076 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetProp */

/* 6078 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6080 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6084 */	NdrFcShort( 0x4 ),	/* 4 */
/* 6086 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 6088 */	NdrFcShort( 0x10 ),	/* 16 */
/* 6090 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6092 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 6094 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 6096 */	NdrFcShort( 0x1 ),	/* 1 */
/* 6098 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6100 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nUserCookie */

/* 6102 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 6104 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6106 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nProp */

/* 6108 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 6110 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6112 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pvValue */

/* 6114 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 6116 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6118 */	NdrFcShort( 0x44a ),	/* Type Offset=1098 */

	/* Return value */

/* 6120 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6122 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 6124 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Compile */

/* 6126 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6128 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6132 */	NdrFcShort( 0x5 ),	/* 5 */
/* 6134 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6136 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6138 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6140 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 6142 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6144 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6146 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6148 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 6150 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6152 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6154 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetLine */

/* 6156 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6158 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6162 */	NdrFcShort( 0x6 ),	/* 6 */
/* 6164 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 6166 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6168 */	NdrFcShort( 0x24 ),	/* 36 */
/* 6170 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 6172 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6174 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6176 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6178 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nLineNr */

/* 6180 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 6182 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6184 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pLineBegin */

/* 6186 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 6188 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6190 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 6192 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6194 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6196 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Save */

/* 6198 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6200 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6204 */	NdrFcShort( 0x7 ),	/* 7 */
/* 6206 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6208 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6210 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6212 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 6214 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6216 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6218 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6220 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pDestStream */

/* 6222 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 6224 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6226 */	NdrFcShort( 0x4b2 ),	/* Type Offset=1202 */

	/* Return value */

/* 6228 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6230 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6232 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetVirtualMachine */

/* 6234 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6236 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6240 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6242 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6244 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6246 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6248 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 6250 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6252 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6254 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6256 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppVirtualMachine */

/* 6258 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6260 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6262 */	NdrFcShort( 0x650 ),	/* Type Offset=1616 */

	/* Return value */

/* 6264 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6266 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6268 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const navo2001_MIDL_TYPE_FORMAT_STRING navo2001__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/*  4 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/*  8 */	NdrFcShort( 0x2 ),	/* Offset= 2 (10) */
/* 10 */	
			0x13, 0x20,	/* FC_OP [maybenull_sizeis] */
/* 12 */	NdrFcShort( 0x2 ),	/* Offset= 2 (14) */
/* 14 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 16 */	NdrFcShort( 0x1 ),	/* 1 */
/* 18 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x54,		/* FC_DEREFERENCE */
/* 20 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 22 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 24 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 26 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 28 */	NdrFcShort( 0x2 ),	/* Offset= 2 (30) */
/* 30 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 32 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 34 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 36 */	NdrFcLong( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0x0 ),	/* 0 */
/* 44 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 46 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 48 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 50 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 52 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 54 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 56 */	
			0x12, 0x0,	/* FC_UP */
/* 58 */	NdrFcShort( 0x3d6 ),	/* Offset= 982 (1040) */
/* 60 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 62 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 64 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 66 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 68 */	NdrFcShort( 0x2 ),	/* Offset= 2 (70) */
/* 70 */	NdrFcShort( 0x10 ),	/* 16 */
/* 72 */	NdrFcShort( 0x2f ),	/* 47 */
/* 74 */	NdrFcLong( 0x14 ),	/* 20 */
/* 78 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 80 */	NdrFcLong( 0x3 ),	/* 3 */
/* 84 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 86 */	NdrFcLong( 0x11 ),	/* 17 */
/* 90 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 92 */	NdrFcLong( 0x2 ),	/* 2 */
/* 96 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 98 */	NdrFcLong( 0x4 ),	/* 4 */
/* 102 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 104 */	NdrFcLong( 0x5 ),	/* 5 */
/* 108 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 110 */	NdrFcLong( 0xb ),	/* 11 */
/* 114 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 116 */	NdrFcLong( 0xa ),	/* 10 */
/* 120 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 122 */	NdrFcLong( 0x6 ),	/* 6 */
/* 126 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (358) */
/* 128 */	NdrFcLong( 0x7 ),	/* 7 */
/* 132 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 134 */	NdrFcLong( 0x8 ),	/* 8 */
/* 138 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (364) */
/* 140 */	NdrFcLong( 0xd ),	/* 13 */
/* 144 */	NdrFcShort( 0xff92 ),	/* Offset= -110 (34) */
/* 146 */	NdrFcLong( 0x9 ),	/* 9 */
/* 150 */	NdrFcShort( 0xf0 ),	/* Offset= 240 (390) */
/* 152 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 156 */	NdrFcShort( 0xfc ),	/* Offset= 252 (408) */
/* 158 */	NdrFcLong( 0x24 ),	/* 36 */
/* 162 */	NdrFcShort( 0x324 ),	/* Offset= 804 (966) */
/* 164 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 168 */	NdrFcShort( 0x31e ),	/* Offset= 798 (966) */
/* 170 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 174 */	NdrFcShort( 0x31c ),	/* Offset= 796 (970) */
/* 176 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 180 */	NdrFcShort( 0x31a ),	/* Offset= 794 (974) */
/* 182 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 186 */	NdrFcShort( 0x318 ),	/* Offset= 792 (978) */
/* 188 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 192 */	NdrFcShort( 0x316 ),	/* Offset= 790 (982) */
/* 194 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 198 */	NdrFcShort( 0x314 ),	/* Offset= 788 (986) */
/* 200 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 204 */	NdrFcShort( 0x312 ),	/* Offset= 786 (990) */
/* 206 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 210 */	NdrFcShort( 0x2fc ),	/* Offset= 764 (974) */
/* 212 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 216 */	NdrFcShort( 0x2fa ),	/* Offset= 762 (978) */
/* 218 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 222 */	NdrFcShort( 0x304 ),	/* Offset= 772 (994) */
/* 224 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 228 */	NdrFcShort( 0x2fa ),	/* Offset= 762 (990) */
/* 230 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 234 */	NdrFcShort( 0x2fc ),	/* Offset= 764 (998) */
/* 236 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 240 */	NdrFcShort( 0x2fa ),	/* Offset= 762 (1002) */
/* 242 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 246 */	NdrFcShort( 0x2f8 ),	/* Offset= 760 (1006) */
/* 248 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 252 */	NdrFcShort( 0x2f6 ),	/* Offset= 758 (1010) */
/* 254 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 258 */	NdrFcShort( 0x2f4 ),	/* Offset= 756 (1014) */
/* 260 */	NdrFcLong( 0x10 ),	/* 16 */
/* 264 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 266 */	NdrFcLong( 0x12 ),	/* 18 */
/* 270 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 272 */	NdrFcLong( 0x13 ),	/* 19 */
/* 276 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 278 */	NdrFcLong( 0x15 ),	/* 21 */
/* 282 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 284 */	NdrFcLong( 0x16 ),	/* 22 */
/* 288 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 290 */	NdrFcLong( 0x17 ),	/* 23 */
/* 294 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 296 */	NdrFcLong( 0xe ),	/* 14 */
/* 300 */	NdrFcShort( 0x2d2 ),	/* Offset= 722 (1022) */
/* 302 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 306 */	NdrFcShort( 0x2d6 ),	/* Offset= 726 (1032) */
/* 308 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 312 */	NdrFcShort( 0x2d4 ),	/* Offset= 724 (1036) */
/* 314 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 318 */	NdrFcShort( 0x290 ),	/* Offset= 656 (974) */
/* 320 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 324 */	NdrFcShort( 0x28e ),	/* Offset= 654 (978) */
/* 326 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 330 */	NdrFcShort( 0x28c ),	/* Offset= 652 (982) */
/* 332 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 336 */	NdrFcShort( 0x282 ),	/* Offset= 642 (978) */
/* 338 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 342 */	NdrFcShort( 0x27c ),	/* Offset= 636 (978) */
/* 344 */	NdrFcLong( 0x0 ),	/* 0 */
/* 348 */	NdrFcShort( 0x0 ),	/* Offset= 0 (348) */
/* 350 */	NdrFcLong( 0x1 ),	/* 1 */
/* 354 */	NdrFcShort( 0x0 ),	/* Offset= 0 (354) */
/* 356 */	NdrFcShort( 0xffff ),	/* Offset= -1 (355) */
/* 358 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 360 */	NdrFcShort( 0x8 ),	/* 8 */
/* 362 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 364 */	
			0x12, 0x0,	/* FC_UP */
/* 366 */	NdrFcShort( 0xe ),	/* Offset= 14 (380) */
/* 368 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 370 */	NdrFcShort( 0x2 ),	/* 2 */
/* 372 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 374 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 376 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 378 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 380 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 382 */	NdrFcShort( 0x8 ),	/* 8 */
/* 384 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (368) */
/* 386 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 388 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 390 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 392 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 396 */	NdrFcShort( 0x0 ),	/* 0 */
/* 398 */	NdrFcShort( 0x0 ),	/* 0 */
/* 400 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 402 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 404 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 406 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 408 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 410 */	NdrFcShort( 0x2 ),	/* Offset= 2 (412) */
/* 412 */	
			0x12, 0x0,	/* FC_UP */
/* 414 */	NdrFcShort( 0x216 ),	/* Offset= 534 (948) */
/* 416 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 418 */	NdrFcShort( 0x18 ),	/* 24 */
/* 420 */	NdrFcShort( 0xa ),	/* 10 */
/* 422 */	NdrFcLong( 0x8 ),	/* 8 */
/* 426 */	NdrFcShort( 0x5a ),	/* Offset= 90 (516) */
/* 428 */	NdrFcLong( 0xd ),	/* 13 */
/* 432 */	NdrFcShort( 0x7e ),	/* Offset= 126 (558) */
/* 434 */	NdrFcLong( 0x9 ),	/* 9 */
/* 438 */	NdrFcShort( 0x9e ),	/* Offset= 158 (596) */
/* 440 */	NdrFcLong( 0xc ),	/* 12 */
/* 444 */	NdrFcShort( 0xc8 ),	/* Offset= 200 (644) */
/* 446 */	NdrFcLong( 0x24 ),	/* 36 */
/* 450 */	NdrFcShort( 0x124 ),	/* Offset= 292 (742) */
/* 452 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 456 */	NdrFcShort( 0x140 ),	/* Offset= 320 (776) */
/* 458 */	NdrFcLong( 0x10 ),	/* 16 */
/* 462 */	NdrFcShort( 0x15a ),	/* Offset= 346 (808) */
/* 464 */	NdrFcLong( 0x2 ),	/* 2 */
/* 468 */	NdrFcShort( 0x174 ),	/* Offset= 372 (840) */
/* 470 */	NdrFcLong( 0x3 ),	/* 3 */
/* 474 */	NdrFcShort( 0x18e ),	/* Offset= 398 (872) */
/* 476 */	NdrFcLong( 0x14 ),	/* 20 */
/* 480 */	NdrFcShort( 0x1a8 ),	/* Offset= 424 (904) */
/* 482 */	NdrFcShort( 0xffff ),	/* Offset= -1 (481) */
/* 484 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 486 */	NdrFcShort( 0x4 ),	/* 4 */
/* 488 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 490 */	NdrFcShort( 0x0 ),	/* 0 */
/* 492 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 494 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 496 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 498 */	NdrFcShort( 0x4 ),	/* 4 */
/* 500 */	NdrFcShort( 0x0 ),	/* 0 */
/* 502 */	NdrFcShort( 0x1 ),	/* 1 */
/* 504 */	NdrFcShort( 0x0 ),	/* 0 */
/* 506 */	NdrFcShort( 0x0 ),	/* 0 */
/* 508 */	0x12, 0x0,	/* FC_UP */
/* 510 */	NdrFcShort( 0xff7e ),	/* Offset= -130 (380) */
/* 512 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 514 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 516 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 518 */	NdrFcShort( 0x8 ),	/* 8 */
/* 520 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 522 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 524 */	NdrFcShort( 0x4 ),	/* 4 */
/* 526 */	NdrFcShort( 0x4 ),	/* 4 */
/* 528 */	0x11, 0x0,	/* FC_RP */
/* 530 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (484) */
/* 532 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 534 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 536 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 538 */	NdrFcShort( 0x0 ),	/* 0 */
/* 540 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 542 */	NdrFcShort( 0x0 ),	/* 0 */
/* 544 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 546 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 550 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 552 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 554 */	NdrFcShort( 0xfdf8 ),	/* Offset= -520 (34) */
/* 556 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 558 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 560 */	NdrFcShort( 0x8 ),	/* 8 */
/* 562 */	NdrFcShort( 0x0 ),	/* 0 */
/* 564 */	NdrFcShort( 0x6 ),	/* Offset= 6 (570) */
/* 566 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 568 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 570 */	
			0x11, 0x0,	/* FC_RP */
/* 572 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (536) */
/* 574 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 576 */	NdrFcShort( 0x0 ),	/* 0 */
/* 578 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 580 */	NdrFcShort( 0x0 ),	/* 0 */
/* 582 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 584 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 588 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 590 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 592 */	NdrFcShort( 0xff36 ),	/* Offset= -202 (390) */
/* 594 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 596 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 598 */	NdrFcShort( 0x8 ),	/* 8 */
/* 600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 602 */	NdrFcShort( 0x6 ),	/* Offset= 6 (608) */
/* 604 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 606 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 608 */	
			0x11, 0x0,	/* FC_RP */
/* 610 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (574) */
/* 612 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 614 */	NdrFcShort( 0x4 ),	/* 4 */
/* 616 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 618 */	NdrFcShort( 0x0 ),	/* 0 */
/* 620 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 622 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 624 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 626 */	NdrFcShort( 0x4 ),	/* 4 */
/* 628 */	NdrFcShort( 0x0 ),	/* 0 */
/* 630 */	NdrFcShort( 0x1 ),	/* 1 */
/* 632 */	NdrFcShort( 0x0 ),	/* 0 */
/* 634 */	NdrFcShort( 0x0 ),	/* 0 */
/* 636 */	0x12, 0x0,	/* FC_UP */
/* 638 */	NdrFcShort( 0x192 ),	/* Offset= 402 (1040) */
/* 640 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 642 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 644 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 646 */	NdrFcShort( 0x8 ),	/* 8 */
/* 648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 650 */	NdrFcShort( 0x6 ),	/* Offset= 6 (656) */
/* 652 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 654 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 656 */	
			0x11, 0x0,	/* FC_RP */
/* 658 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (612) */
/* 660 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 662 */	NdrFcLong( 0x2f ),	/* 47 */
/* 666 */	NdrFcShort( 0x0 ),	/* 0 */
/* 668 */	NdrFcShort( 0x0 ),	/* 0 */
/* 670 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 672 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 674 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 676 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 678 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 680 */	NdrFcShort( 0x1 ),	/* 1 */
/* 682 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 684 */	NdrFcShort( 0x4 ),	/* 4 */
/* 686 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 688 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 690 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 692 */	NdrFcShort( 0x10 ),	/* 16 */
/* 694 */	NdrFcShort( 0x0 ),	/* 0 */
/* 696 */	NdrFcShort( 0xa ),	/* Offset= 10 (706) */
/* 698 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 700 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 702 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (660) */
/* 704 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 706 */	
			0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 708 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (678) */
/* 710 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 712 */	NdrFcShort( 0x4 ),	/* 4 */
/* 714 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 716 */	NdrFcShort( 0x0 ),	/* 0 */
/* 718 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 720 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 722 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 724 */	NdrFcShort( 0x4 ),	/* 4 */
/* 726 */	NdrFcShort( 0x0 ),	/* 0 */
/* 728 */	NdrFcShort( 0x1 ),	/* 1 */
/* 730 */	NdrFcShort( 0x0 ),	/* 0 */
/* 732 */	NdrFcShort( 0x0 ),	/* 0 */
/* 734 */	0x12, 0x0,	/* FC_UP */
/* 736 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (690) */
/* 738 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 740 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 742 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 744 */	NdrFcShort( 0x8 ),	/* 8 */
/* 746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 748 */	NdrFcShort( 0x6 ),	/* Offset= 6 (754) */
/* 750 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 752 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 754 */	
			0x11, 0x0,	/* FC_RP */
/* 756 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (710) */
/* 758 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 760 */	NdrFcShort( 0x8 ),	/* 8 */
/* 762 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 764 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 766 */	NdrFcShort( 0x10 ),	/* 16 */
/* 768 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 770 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 772 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (758) */
			0x5b,		/* FC_END */
/* 776 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 778 */	NdrFcShort( 0x18 ),	/* 24 */
/* 780 */	NdrFcShort( 0x0 ),	/* 0 */
/* 782 */	NdrFcShort( 0xa ),	/* Offset= 10 (792) */
/* 784 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 786 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 788 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (764) */
/* 790 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 792 */	
			0x11, 0x0,	/* FC_RP */
/* 794 */	NdrFcShort( 0xfefe ),	/* Offset= -258 (536) */
/* 796 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 798 */	NdrFcShort( 0x1 ),	/* 1 */
/* 800 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 802 */	NdrFcShort( 0x0 ),	/* 0 */
/* 804 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 806 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 808 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 810 */	NdrFcShort( 0x8 ),	/* 8 */
/* 812 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 814 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 816 */	NdrFcShort( 0x4 ),	/* 4 */
/* 818 */	NdrFcShort( 0x4 ),	/* 4 */
/* 820 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 822 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (796) */
/* 824 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 826 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 828 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 830 */	NdrFcShort( 0x2 ),	/* 2 */
/* 832 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 834 */	NdrFcShort( 0x0 ),	/* 0 */
/* 836 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 838 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 840 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 842 */	NdrFcShort( 0x8 ),	/* 8 */
/* 844 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 846 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 848 */	NdrFcShort( 0x4 ),	/* 4 */
/* 850 */	NdrFcShort( 0x4 ),	/* 4 */
/* 852 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 854 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (828) */
/* 856 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 858 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 860 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 862 */	NdrFcShort( 0x4 ),	/* 4 */
/* 864 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 866 */	NdrFcShort( 0x0 ),	/* 0 */
/* 868 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 870 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 872 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 874 */	NdrFcShort( 0x8 ),	/* 8 */
/* 876 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 878 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 880 */	NdrFcShort( 0x4 ),	/* 4 */
/* 882 */	NdrFcShort( 0x4 ),	/* 4 */
/* 884 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 886 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (860) */
/* 888 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 890 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 892 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 894 */	NdrFcShort( 0x8 ),	/* 8 */
/* 896 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 898 */	NdrFcShort( 0x0 ),	/* 0 */
/* 900 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 902 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 904 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 906 */	NdrFcShort( 0x8 ),	/* 8 */
/* 908 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 910 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 912 */	NdrFcShort( 0x4 ),	/* 4 */
/* 914 */	NdrFcShort( 0x4 ),	/* 4 */
/* 916 */	0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 918 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (892) */
/* 920 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 922 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 924 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 926 */	NdrFcShort( 0x8 ),	/* 8 */
/* 928 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 930 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 932 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 934 */	NdrFcShort( 0x8 ),	/* 8 */
/* 936 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 938 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 940 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 942 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 944 */	NdrFcShort( 0xffec ),	/* Offset= -20 (924) */
/* 946 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 948 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 950 */	NdrFcShort( 0x28 ),	/* 40 */
/* 952 */	NdrFcShort( 0xffec ),	/* Offset= -20 (932) */
/* 954 */	NdrFcShort( 0x0 ),	/* Offset= 0 (954) */
/* 956 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 958 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 960 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 962 */	NdrFcShort( 0xfdde ),	/* Offset= -546 (416) */
/* 964 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 966 */	
			0x12, 0x0,	/* FC_UP */
/* 968 */	NdrFcShort( 0xfeea ),	/* Offset= -278 (690) */
/* 970 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 972 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 974 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 976 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 978 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 980 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 982 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 984 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 986 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 988 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 990 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 992 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 994 */	
			0x12, 0x0,	/* FC_UP */
/* 996 */	NdrFcShort( 0xfd82 ),	/* Offset= -638 (358) */
/* 998 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1000 */	NdrFcShort( 0xfd84 ),	/* Offset= -636 (364) */
/* 1002 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1004 */	NdrFcShort( 0xfc36 ),	/* Offset= -970 (34) */
/* 1006 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1008 */	NdrFcShort( 0xfd96 ),	/* Offset= -618 (390) */
/* 1010 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1012 */	NdrFcShort( 0xfda4 ),	/* Offset= -604 (408) */
/* 1014 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1016 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1018) */
/* 1018 */	
			0x12, 0x0,	/* FC_UP */
/* 1020 */	NdrFcShort( 0x14 ),	/* Offset= 20 (1040) */
/* 1022 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 1024 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1026 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 1028 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 1030 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 1032 */	
			0x12, 0x0,	/* FC_UP */
/* 1034 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1022) */
/* 1036 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1038 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 1040 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1042 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1044 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1046 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1046) */
/* 1048 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1050 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1052 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1054 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1056 */	NdrFcShort( 0xfc1c ),	/* Offset= -996 (60) */
/* 1058 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1060 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1062 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1064 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1066 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1068 */	NdrFcShort( 0xfc0c ),	/* Offset= -1012 (56) */
/* 1070 */	
			0x11, 0x0,	/* FC_RP */
/* 1072 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1060) */
/* 1074 */	
			0x11, 0x0,	/* FC_RP */
/* 1076 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1078) */
/* 1078 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 1080 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1082 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 1084 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1086 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1088 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 1090 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1092 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1098) */
/* 1094 */	
			0x13, 0x0,	/* FC_OP */
/* 1096 */	NdrFcShort( 0xffc8 ),	/* Offset= -56 (1040) */
/* 1098 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1100 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1102 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1104 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1106 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1094) */
/* 1108 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1110 */	NdrFcShort( 0xa ),	/* Offset= 10 (1120) */
/* 1112 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1114 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1116) */
/* 1116 */	
			0x13, 0x0,	/* FC_OP */
/* 1118 */	NdrFcShort( 0xff56 ),	/* Offset= -170 (948) */
/* 1120 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1122 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1124 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1128 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (1112) */
/* 1130 */	
			0x11, 0x0,	/* FC_RP */
/* 1132 */	NdrFcShort( 0x1a ),	/* Offset= 26 (1158) */
/* 1134 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 1136 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1138 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1140 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1142 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1144 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1146 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1148 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1150 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1150) */
/* 1152 */	0xd,		/* FC_ENUM16 */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1154 */	0x0,		/* 0 */
			NdrFcShort( 0xffeb ),	/* Offset= -21 (1134) */
			0x5b,		/* FC_END */
/* 1158 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 1160 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1162 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 1164 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1166 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1168 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1172 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 1174 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1176 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (1144) */
/* 1178 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1180 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1182 */	NdrFcLong( 0x188cb168 ),	/* 411873640 */
/* 1186 */	NdrFcShort( 0x82a4 ),	/* -32092 */
/* 1188 */	NdrFcShort( 0x4498 ),	/* 17560 */
/* 1190 */	0x87,		/* 135 */
			0xd0,		/* 208 */
/* 1192 */	0xeb,		/* 235 */
			0xd8,		/* 216 */
/* 1194 */	0xd9,		/* 217 */
			0xa0,		/* 160 */
/* 1196 */	0xf,		/* 15 */
			0xb8,		/* 184 */
/* 1198 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1200 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1202) */
/* 1202 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1204 */	NdrFcLong( 0xc ),	/* 12 */
/* 1208 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1210 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1212 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 1214 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1216 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1218 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 1220 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1222 */	NdrFcShort( 0xfcc0 ),	/* Offset= -832 (390) */
/* 1224 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1226 */	NdrFcShort( 0xfb58 ),	/* Offset= -1192 (34) */
/* 1228 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1230 */	NdrFcShort( 0x8 ),	/* Offset= 8 (1238) */
/* 1232 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 1234 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1236 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 1238 */	
			0x15,		/* FC_STRUCT */
			0x0,		/* 0 */
/* 1240 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1242 */	0x2,		/* FC_CHAR */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1244 */	0x0,		/* 0 */
			NdrFcShort( 0xfff3 ),	/* Offset= -13 (1232) */
			0x5b,		/* FC_END */
/* 1248 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1250 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1252) */
/* 1252 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1254 */	NdrFcLong( 0x188cb169 ),	/* 411873641 */
/* 1258 */	NdrFcShort( 0x82a4 ),	/* -32092 */
/* 1260 */	NdrFcShort( 0x4498 ),	/* 17560 */
/* 1262 */	0x87,		/* 135 */
			0xd0,		/* 208 */
/* 1264 */	0xeb,		/* 235 */
			0xd8,		/* 216 */
/* 1266 */	0xd9,		/* 217 */
			0xa0,		/* 160 */
/* 1268 */	0xf,		/* 15 */
			0xb8,		/* 184 */
/* 1270 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1272 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 1274 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 1276 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1278) */
/* 1278 */	
			0x13, 0x20,	/* FC_OP [maybenull_sizeis] */
/* 1280 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1282) */
/* 1282 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 1284 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1286 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x54,		/* FC_DEREFERENCE */
/* 1288 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1290 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1292 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 1294 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1296 */	NdrFcLong( 0x188cb155 ),	/* 411873621 */
/* 1300 */	NdrFcShort( 0x82a4 ),	/* -32092 */
/* 1302 */	NdrFcShort( 0x4498 ),	/* 17560 */
/* 1304 */	0x87,		/* 135 */
			0xd0,		/* 208 */
/* 1306 */	0xeb,		/* 235 */
			0xd8,		/* 216 */
/* 1308 */	0xd9,		/* 217 */
			0xa0,		/* 160 */
/* 1310 */	0xf,		/* 15 */
			0xb8,		/* 184 */
/* 1312 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 1314 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 1316 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 1318 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1320) */
/* 1320 */	
			0x13, 0x20,	/* FC_OP [maybenull_sizeis] */
/* 1322 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1324) */
/* 1324 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 1326 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1328 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x54,		/* FC_DEREFERENCE */
/* 1330 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1332 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1334 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 1336 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1338 */	NdrFcLong( 0x188cb152 ),	/* 411873618 */
/* 1342 */	NdrFcShort( 0x82a4 ),	/* -32092 */
/* 1344 */	NdrFcShort( 0x4498 ),	/* 17560 */
/* 1346 */	0x87,		/* 135 */
			0xd0,		/* 208 */
/* 1348 */	0xeb,		/* 235 */
			0xd8,		/* 216 */
/* 1350 */	0xd9,		/* 217 */
			0xa0,		/* 160 */
/* 1352 */	0xf,		/* 15 */
			0xb8,		/* 184 */
/* 1354 */	
			0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 1356 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1358) */
/* 1358 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 1360 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1362 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 1364 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1366 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1368 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 1370 */	
			0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 1372 */	NdrFcShort( 0x16 ),	/* Offset= 22 (1394) */
/* 1374 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1376 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1378 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1380 */	NdrFcShort( 0xe ),	/* Offset= 14 (1394) */
/* 1382 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1384 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1386 */	NdrFcShort( 0xff48 ),	/* Offset= -184 (1202) */
/* 1388 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1390 */	NdrFcShort( 0xff68 ),	/* Offset= -152 (1238) */
/* 1392 */	0x3f,		/* FC_STRUCTPAD3 */
			0x5b,		/* FC_END */
/* 1394 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 1396 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1398 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 1400 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1402 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1404 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1408 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 1410 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1412 */	NdrFcShort( 0xffda ),	/* Offset= -38 (1374) */
/* 1414 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1416 */	
			0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 1418 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1420) */
/* 1420 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 1422 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1424 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 1426 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1428 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1430 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1434 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 1436 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1438 */	NdrFcShort( 0xfeda ),	/* Offset= -294 (1144) */
/* 1440 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1442 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 1444 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1446) */
/* 1446 */	
			0x13, 0x20,	/* FC_OP [maybenull_sizeis] */
/* 1448 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1450) */
/* 1450 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 1452 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1454 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x54,		/* FC_DEREFERENCE */
/* 1456 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1458 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1460 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 1462 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1464 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1466) */
/* 1466 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1468 */	NdrFcLong( 0x188cb15f ),	/* 411873631 */
/* 1472 */	NdrFcShort( 0x82a4 ),	/* -32092 */
/* 1474 */	NdrFcShort( 0x4498 ),	/* 17560 */
/* 1476 */	0x87,		/* 135 */
			0xd0,		/* 208 */
/* 1478 */	0xeb,		/* 235 */
			0xd8,		/* 216 */
/* 1480 */	0xd9,		/* 217 */
			0xa0,		/* 160 */
/* 1482 */	0xf,		/* 15 */
			0xb8,		/* 184 */
/* 1484 */	
			0x11, 0x0,	/* FC_RP */
/* 1486 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1488) */
/* 1488 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1490 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1492 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1494 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1496 */	NdrFcShort( 0xfbc0 ),	/* Offset= -1088 (408) */
/* 1498 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1500 */	NdrFcLong( 0x188cb18d ),	/* 411873677 */
/* 1504 */	NdrFcShort( 0x82a4 ),	/* -32092 */
/* 1506 */	NdrFcShort( 0x4498 ),	/* 17560 */
/* 1508 */	0x87,		/* 135 */
			0xd0,		/* 208 */
/* 1510 */	0xeb,		/* 235 */
			0xd8,		/* 216 */
/* 1512 */	0xd9,		/* 217 */
			0xa0,		/* 160 */
/* 1514 */	0xf,		/* 15 */
			0xb8,		/* 184 */
/* 1516 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1518 */	NdrFcLong( 0x188cb188 ),	/* 411873672 */
/* 1522 */	NdrFcShort( 0x82a4 ),	/* -32092 */
/* 1524 */	NdrFcShort( 0x4498 ),	/* 17560 */
/* 1526 */	0x87,		/* 135 */
			0xd0,		/* 208 */
/* 1528 */	0xeb,		/* 235 */
			0xd8,		/* 216 */
/* 1530 */	0xd9,		/* 217 */
			0xa0,		/* 160 */
/* 1532 */	0xf,		/* 15 */
			0xb8,		/* 184 */
/* 1534 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 1536 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1538) */
/* 1538 */	
			0x13, 0x20,	/* FC_OP [maybenull_sizeis] */
/* 1540 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1542) */
/* 1542 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 1544 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1546 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x54,		/* FC_DEREFERENCE */
/* 1548 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1550 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1552 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 1554 */	
			0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 1556 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1558) */
/* 1558 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 1560 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1562 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 1564 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1566 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1568 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 1570 */	
			0x11, 0x0,	/* FC_RP */
/* 1572 */	NdrFcShort( 0xfeb2 ),	/* Offset= -334 (1238) */
/* 1574 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1576 */	NdrFcShort( 0xfcd4 ),	/* Offset= -812 (764) */
/* 1578 */	
			0x12, 0x20,	/* FC_UP [maybenull_sizeis] */
/* 1580 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1582) */
/* 1582 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 1584 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1586 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 1588 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1590 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1592 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 1594 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1596 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1598) */
/* 1598 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1600 */	NdrFcLong( 0x188cb162 ),	/* 411873634 */
/* 1604 */	NdrFcShort( 0x82a4 ),	/* -32092 */
/* 1606 */	NdrFcShort( 0x4498 ),	/* 17560 */
/* 1608 */	0x87,		/* 135 */
			0xd0,		/* 208 */
/* 1610 */	0xeb,		/* 235 */
			0xd8,		/* 216 */
/* 1612 */	0xd9,		/* 217 */
			0xa0,		/* 160 */
/* 1614 */	0xf,		/* 15 */
			0xb8,		/* 184 */
/* 1616 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1618 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1620) */
/* 1620 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1622 */	NdrFcLong( 0x188cb184 ),	/* 411873668 */
/* 1626 */	NdrFcShort( 0x82a4 ),	/* -32092 */
/* 1628 */	NdrFcShort( 0x4498 ),	/* 17560 */
/* 1630 */	0x87,		/* 135 */
			0xd0,		/* 208 */
/* 1632 */	0xeb,		/* 235 */
			0xd8,		/* 216 */
/* 1634 */	0xd9,		/* 217 */
			0xa0,		/* 160 */
/* 1636 */	0xf,		/* 15 */
			0xb8,		/* 184 */

			0x0
        }
    };

XFG_TRAMPOLINES(VARIANT)
XFG_TRAMPOLINES(LPSAFEARRAY)

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            (USER_MARSHAL_SIZING_ROUTINE)XFG_TRAMPOLINE_FPTR(VARIANT_UserSize)
            ,(USER_MARSHAL_MARSHALLING_ROUTINE)XFG_TRAMPOLINE_FPTR(VARIANT_UserMarshal)
            ,(USER_MARSHAL_UNMARSHALLING_ROUTINE)XFG_TRAMPOLINE_FPTR(VARIANT_UserUnmarshal)
            ,(USER_MARSHAL_FREEING_ROUTINE)XFG_TRAMPOLINE_FPTR(VARIANT_UserFree)
            
            }
            ,
            {
            (USER_MARSHAL_SIZING_ROUTINE)XFG_TRAMPOLINE_FPTR(LPSAFEARRAY_UserSize)
            ,(USER_MARSHAL_MARSHALLING_ROUTINE)XFG_TRAMPOLINE_FPTR(LPSAFEARRAY_UserMarshal)
            ,(USER_MARSHAL_UNMARSHALLING_ROUTINE)XFG_TRAMPOLINE_FPTR(LPSAFEARRAY_UserUnmarshal)
            ,(USER_MARSHAL_FREEING_ROUTINE)XFG_TRAMPOLINE_FPTR(LPSAFEARRAY_UserFree)
            
            }
            

        };



/* Standard interface: __MIDL_itf_navo2001_0000_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: INavoErrorInfo, ver. 0.0,
   GUID={0x188cb14d,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short INavoErrorInfo_FormatStringOffsetTable[] =
    {
    0,
    42
    };

static const MIDL_STUBLESS_PROXY_INFO INavoErrorInfo_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &INavoErrorInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO INavoErrorInfo_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &INavoErrorInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _INavoErrorInfoProxyVtbl = 
{
    &INavoErrorInfo_ProxyInfo,
    &IID_INavoErrorInfo,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* INavoErrorInfo::RetrieveError */ ,
    (void *) (INT_PTR) -1 /* INavoErrorInfo::RetrieveError2 */
};

const CInterfaceStubVtbl _INavoErrorInfoStubVtbl =
{
    &IID_INavoErrorInfo,
    &INavoErrorInfo_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Standard interface: __MIDL_itf_navo2001_0000_0001, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: INotificationManager, ver. 0.0,
   GUID={0x188cb14e,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short INotificationManager_FormatStringOffsetTable[] =
    {
    78,
    138,
    174,
    216,
    264,
    318,
    378,
    426,
    474,
    504,
    546
    };

static const MIDL_STUBLESS_PROXY_INFO INotificationManager_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &INotificationManager_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO INotificationManager_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &INotificationManager_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(14) _INotificationManagerProxyVtbl = 
{
    &INotificationManager_ProxyInfo,
    &IID_INotificationManager,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* INotificationManager::Advise */ ,
    (void *) (INT_PTR) -1 /* INotificationManager::UnAdvise */ ,
    (void *) (INT_PTR) -1 /* INotificationManager::QuerySinks */ ,
    (void *) (INT_PTR) -1 /* INotificationManager::NotifySharedVariableChange */ ,
    (void *) (INT_PTR) -1 /* INotificationManager::NotifyUser */ ,
    (void *) (INT_PTR) -1 /* INotificationManager::NotifyMultipleUsers */ ,
    (void *) (INT_PTR) -1 /* INotificationManager::SetProp */ ,
    (void *) (INT_PTR) -1 /* INotificationManager::GetProp */ ,
    (void *) (INT_PTR) -1 /* INotificationManager::Close */ ,
    (void *) (INT_PTR) -1 /* INotificationManager::QuerySinks2 */ ,
    (void *) (INT_PTR) -1 /* INotificationManager::GetProp2 */
};

const CInterfaceStubVtbl _INotificationManagerStubVtbl =
{
    &IID_INotificationManager,
    &INotificationManager_ServerInfo,
    14,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: INotificationSink, ver. 0.0,
   GUID={0x188cb14f,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short INotificationSink_FormatStringOffsetTable[] =
    {
    600,
    642,
    690
    };

static const MIDL_STUBLESS_PROXY_INFO INotificationSink_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &INotificationSink_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO INotificationSink_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &INotificationSink_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(6) _INotificationSinkProxyVtbl = 
{
    &INotificationSink_ProxyInfo,
    &IID_INotificationSink,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* INotificationSink::OnSharedVariableChange */ ,
    (void *) (INT_PTR) -1 /* INotificationSink::OnNotifyUser */ ,
    (void *) (INT_PTR) -1 /* INotificationSink::OnProgress */
};

const CInterfaceStubVtbl _INotificationSinkStubVtbl =
{
    &IID_INotificationSink,
    &INotificationSink_ServerInfo,
    6,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ISupplyInfo, ver. 0.0,
   GUID={0x188cb168,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short ISupplyInfo_FormatStringOffsetTable[] =
    {
    744
    };

static const MIDL_STUBLESS_PROXY_INFO ISupplyInfo_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &ISupplyInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISupplyInfo_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &ISupplyInfo_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _ISupplyInfoProxyVtbl = 
{
    &ISupplyInfo_ProxyInfo,
    &IID_ISupplyInfo,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISupplyInfo::AskForData */
};

const CInterfaceStubVtbl _ISupplyInfoStubVtbl =
{
    &IID_ISupplyInfo,
    &ISupplyInfo_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IPingClient, ver. 0.0,
   GUID={0x188cb16c,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short IPingClient_FormatStringOffsetTable[] =
    {
    798
    };

static const MIDL_STUBLESS_PROXY_INFO IPingClient_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &IPingClient_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IPingClient_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &IPingClient_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _IPingClientProxyVtbl = 
{
    &IPingClient_ProxyInfo,
    &IID_IPingClient,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IPingClient::Ping */
};

const CInterfaceStubVtbl _IPingClientStubVtbl =
{
    &IID_IPingClient,
    &IPingClient_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IPingServer, ver. 0.0,
   GUID={0x188cb16d,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short IPingServer_FormatStringOffsetTable[] =
    {
    828,
    138
    };

static const MIDL_STUBLESS_PROXY_INFO IPingServer_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &IPingServer_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IPingServer_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &IPingServer_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IPingServerProxyVtbl = 
{
    &IPingServer_ProxyInfo,
    &IID_IPingServer,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IPingServer::Advise */ ,
    (void *) (INT_PTR) -1 /* IPingServer::UnAdvise */
};

const CInterfaceStubVtbl _IPingServerStubVtbl =
{
    &IID_IPingServer,
    &IPingServer_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Standard interface: __MIDL_itf_navo2001_0000_0006, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: ILockManager, ver. 0.0,
   GUID={0x188cb152,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short ILockManager_FormatStringOffsetTable[] =
    {
    870,
    138,
    918,
    972,
    1038
    };

static const MIDL_STUBLESS_PROXY_INFO ILockManager_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &ILockManager_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ILockManager_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &ILockManager_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _ILockManagerProxyVtbl = 
{
    &ILockManager_ProxyInfo,
    &IID_ILockManager,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ILockManager::Advise */ ,
    (void *) (INT_PTR) -1 /* ILockManager::UnAdvise */ ,
    (void *) (INT_PTR) -1 /* ILockManager::Lock */ ,
    (void *) (INT_PTR) -1 /* ILockManager::Lock_AddItem */ ,
    (void *) (INT_PTR) -1 /* ILockManager::Lock2 */
};

const CInterfaceStubVtbl _ILockManagerStubVtbl =
{
    &IID_ILockManager,
    &ILockManager_ServerInfo,
    8,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ICntResourceManager, ver. 0.0,
   GUID={0x188cb17d,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short ICntResourceManager_FormatStringOffsetTable[] =
    {
    1086,
    1128,
    1164,
    1206,
    1248
    };

static const MIDL_STUBLESS_PROXY_INFO ICntResourceManager_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &ICntResourceManager_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ICntResourceManager_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &ICntResourceManager_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _ICntResourceManagerProxyVtbl = 
{
    &ICntResourceManager_ProxyInfo,
    &IID_ICntResourceManager,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ICntResourceManager::CreateResource */ ,
    (void *) (INT_PTR) -1 /* ICntResourceManager::DeleteResource */ ,
    (void *) (INT_PTR) -1 /* ICntResourceManager::UseResource */ ,
    (void *) (INT_PTR) -1 /* ICntResourceManager::ReleaseResource */ ,
    (void *) (INT_PTR) -1 /* ICntResourceManager::UseResource2 */
};

const CInterfaceStubVtbl _ICntResourceManagerStubVtbl =
{
    &IID_ICntResourceManager,
    &ICntResourceManager_ServerInfo,
    8,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IBackupRestore, ver. 0.0,
   GUID={0x188cb154,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short IBackupRestore_FormatStringOffsetTable[] =
    {
    1296,
    1350,
    1380,
    1428,
    1482
    };

static const MIDL_STUBLESS_PROXY_INFO IBackupRestore_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &IBackupRestore_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IBackupRestore_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &IBackupRestore_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _IBackupRestoreProxyVtbl = 
{
    &IBackupRestore_ProxyInfo,
    &IID_IBackupRestore,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IBackupRestore::Begin */ ,
    (void *) (INT_PTR) -1 /* IBackupRestore::End */ ,
    (void *) (INT_PTR) -1 /* IBackupRestore::GetBackupStream */ ,
    (void *) (INT_PTR) -1 /* IBackupRestore::SetRestoreStream */ ,
    (void *) (INT_PTR) -1 /* IBackupRestore::GetStat */
};

const CInterfaceStubVtbl _IBackupRestoreStubVtbl =
{
    &IID_IBackupRestore,
    &IBackupRestore_ServerInfo,
    8,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Standard interface: __MIDL_itf_navo2001_0000_0009, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IBackupRestoreManager, ver. 0.0,
   GUID={0x188cb158,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short IBackupRestoreManager_FormatStringOffsetTable[] =
    {
    1524,
    1578,
    1632,
    1668,
    1704,
    1734,
    1770,
    1812
    };

static const MIDL_STUBLESS_PROXY_INFO IBackupRestoreManager_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &IBackupRestoreManager_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IBackupRestoreManager_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &IBackupRestoreManager_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IBackupRestoreManagerProxyVtbl = 
{
    &IBackupRestoreManager_ProxyInfo,
    &IID_IBackupRestoreManager,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IBackupRestoreManager::GetBackupStream */ ,
    (void *) (INT_PTR) -1 /* IBackupRestoreManager::SetRestoreStream */ ,
    (void *) (INT_PTR) -1 /* IBackupRestoreManager::NewBrSet */ ,
    (void *) (INT_PTR) -1 /* IBackupRestoreManager::AddBrSet */ ,
    (void *) (INT_PTR) -1 /* IBackupRestoreManager::RemoveAllBrSets */ ,
    (void *) (INT_PTR) -1 /* IBackupRestoreManager::_GetNewEnum */ ,
    (void *) (INT_PTR) -1 /* IBackupRestoreManager::SetProp */ ,
    (void *) (INT_PTR) -1 /* IBackupRestoreManager::GetProp */
};

const CInterfaceStubVtbl _IBackupRestoreManagerStubVtbl =
{
    &IID_IBackupRestoreManager,
    &IBackupRestoreManager_ServerInfo,
    11,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IStreamProvider, ver. 0.0,
   GUID={0x188cb155,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short IStreamProvider_FormatStringOffsetTable[] =
    {
    1854
    };

static const MIDL_STUBLESS_PROXY_INFO IStreamProvider_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &IStreamProvider_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IStreamProvider_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &IStreamProvider_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _IStreamProviderProxyVtbl = 
{
    &IStreamProvider_ProxyInfo,
    &IID_IStreamProvider,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IStreamProvider::Get */
};

const CInterfaceStubVtbl _IStreamProviderStubVtbl =
{
    &IID_IStreamProvider,
    &IStreamProvider_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Standard interface: __MIDL_itf_navo2001_0000_0011, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IStreamFilter, ver. 0.0,
   GUID={0x188cb16b,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short IStreamFilter_FormatStringOffsetTable[] =
    {
    1902,
    138
    };

static const MIDL_STUBLESS_PROXY_INFO IStreamFilter_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &IStreamFilter_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IStreamFilter_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &IStreamFilter_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IStreamFilterProxyVtbl = 
{
    &IStreamFilter_ProxyInfo,
    &IID_IStreamFilter,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IStreamFilter::AttachInput */ ,
    (void *) (INT_PTR) -1 /* IStreamFilter::SetParam */
};

const CInterfaceStubVtbl _IStreamFilterStubVtbl =
{
    &IID_IStreamFilter,
    &IStreamFilter_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IStreamSplitter, ver. 0.0,
   GUID={0x188cb177,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short IStreamSplitter_FormatStringOffsetTable[] =
    {
    1938,
    1980
    };

static const MIDL_STUBLESS_PROXY_INFO IStreamSplitter_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &IStreamSplitter_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IStreamSplitter_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &IStreamSplitter_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IStreamSplitterProxyVtbl = 
{
    &IStreamSplitter_ProxyInfo,
    &IID_IStreamSplitter,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IStreamSplitter::Split */ ,
    (void *) (INT_PTR) -1 /* IStreamSplitter::Join */
};

const CInterfaceStubVtbl _IStreamSplitterStubVtbl =
{
    &IID_IStreamSplitter,
    &IStreamSplitter_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ISimpleEnumId, ver. 0.0,
   GUID={0x188cb169,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short ISimpleEnumId_FormatStringOffsetTable[] =
    {
    2016,
    2052
    };

static const MIDL_STUBLESS_PROXY_INFO ISimpleEnumId_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &ISimpleEnumId_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISimpleEnumId_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &ISimpleEnumId_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _ISimpleEnumIdProxyVtbl = 
{
    &ISimpleEnumId_ProxyInfo,
    &IID_ISimpleEnumId,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ISimpleEnumId::Next */ ,
    (void *) (INT_PTR) -1 /* ISimpleEnumId::NextFull */
};

const CInterfaceStubVtbl _ISimpleEnumIdStubVtbl =
{
    &IID_ISimpleEnumId,
    &ISimpleEnumId_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Standard interface: __MIDL_itf_navo2001_0000_0014, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IAppDBManager, ver. 0.0,
   GUID={0x188cb156,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short IAppDBManager_FormatStringOffsetTable[] =
    {
    2094,
    2130,
    2166,
    2202,
    2250,
    2286,
    2334,
    2370,
    2412,
    2454,
    2496,
    2556,
    2592,
    2628,
    2682,
    2742
    };

static const MIDL_STUBLESS_PROXY_INFO IAppDBManager_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &IAppDBManager_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IAppDBManager_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &IAppDBManager_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(19) _IAppDBManagerProxyVtbl = 
{
    &IAppDBManager_ProxyInfo,
    &IID_IAppDBManager,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IAppDBManager::Init */ ,
    (void *) (INT_PTR) -1 /* IAppDBManager::Close */ ,
    (void *) (INT_PTR) -1 /* IAppDBManager::SetOptions */ ,
    (void *) (INT_PTR) -1 /* IAppDBManager::Upload */ ,
    (void *) (INT_PTR) -1 /* IAppDBManager::Delete */ ,
    (void *) (INT_PTR) -1 /* IAppDBManager::CreateApp */ ,
    (void *) (INT_PTR) -1 /* IAppDBManager::DropApp */ ,
    (void *) (INT_PTR) -1 /* IAppDBManager::Pack */ ,
    (void *) (INT_PTR) -1 /* IAppDBManager::Unpack */ ,
    (void *) (INT_PTR) -1 /* IAppDBManager::EnumFileGroup */ ,
    (void *) (INT_PTR) -1 /* IAppDBManager::GetItemInfo */ ,
    (void *) (INT_PTR) -1 /* IAppDBManager::ChangeMode */ ,
    (void *) (INT_PTR) -1 /* IAppDBManager::GetMode */ ,
    (void *) (INT_PTR) -1 /* IAppDBManager::GetFinalStream */ ,
    (void *) (INT_PTR) -1 /* IAppDBManager::GetItemInfo2 */ ,
    (void *) (INT_PTR) -1 /* IAppDBManager::SetAltStreamProvider */
};

const CInterfaceStubVtbl _IAppDBManagerStubVtbl =
{
    &IID_IAppDBManager,
    &IAppDBManager_ServerInfo,
    19,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Standard interface: __MIDL_itf_navo2001_0000_0015, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: INAVOObjectCollection, ver. 0.0,
   GUID={0x188cb15f,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short INAVOObjectCollection_FormatStringOffsetTable[] =
    {
    2778,
    2838,
    2874,
    2916
    };

static const MIDL_STUBLESS_PROXY_INFO INAVOObjectCollection_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &INAVOObjectCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO INAVOObjectCollection_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &INAVOObjectCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _INAVOObjectCollectionProxyVtbl = 
{
    &INAVOObjectCollection_ProxyInfo,
    &IID_INAVOObjectCollection,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* INAVOObjectCollection::Fetch */ ,
    (void *) (INT_PTR) -1 /* INAVOObjectCollection::GetCount */ ,
    (void *) (INT_PTR) -1 /* INAVOObjectCollection::Refresh */ ,
    (void *) (INT_PTR) -1 /* INAVOObjectCollection::Fetch2 */
};

const CInterfaceStubVtbl _INAVOObjectCollectionStubVtbl =
{
    &IID_INAVOObjectCollection,
    &INAVOObjectCollection_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Standard interface: __MIDL_itf_navo2001_0000_0016, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IObjectServer, ver. 0.0,
   GUID={0x188cb15e,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short IObjectServer_FormatStringOffsetTable[] =
    {
    2976,
    2130,
    3030,
    3102,
    3138,
    3204,
    3270,
    3312,
    3360,
    3432,
    3486,
    3534,
    3582,
    3630,
    3672,
    3714,
    3756,
    3804,
    3846,
    3888,
    3942,
    3996,
    4056,
    4128,
    4182,
    4224,
    4260,
    4296,
    4362
    };

static const MIDL_STUBLESS_PROXY_INFO IObjectServer_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &IObjectServer_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IObjectServer_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &IObjectServer_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(32) _IObjectServerProxyVtbl = 
{
    &IObjectServer_ProxyInfo,
    &IID_IObjectServer,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IObjectServer::SetCoManagers */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::Close */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::MakeTransaction */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::FinishTransaction */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::GetObjectIfNewer */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::GetStream */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::GetUniqueIdent */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::FindOnField */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::OpenOnStatement */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::OpenCollection */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::OpenFTSQuery */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::OpenDiscoRecSet */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::CanDelete */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::SetProp */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::GetProp */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::ExecSQL */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::SetSharedVariable */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::GetSharedVariable */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::CreateExtension */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::WriteToArchive */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::ReadFromArchive */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::MakeTransaction2 */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::GetObjectIfNewer2 */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::MakeTransaction_Stream */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::OpenDiscoRecSet2 */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::CreateADOCommand */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::CreateADOParameter */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::Lock_AddItem */ ,
    (void *) (INT_PTR) -1 /* IObjectServer::PurgeCache */
};

const CInterfaceStubVtbl _IObjectServerStubVtbl =
{
    &IID_IObjectServer,
    &IObjectServer_ServerInfo,
    32,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IObjectServerExtensionHost, ver. 0.0,
   GUID={0x188cb18d,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short IObjectServerExtensionHost_FormatStringOffsetTable[] =
    {
    4392,
    4428,
    4464
    };

static const MIDL_STUBLESS_PROXY_INFO IObjectServerExtensionHost_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &IObjectServerExtensionHost_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IObjectServerExtensionHost_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &IObjectServerExtensionHost_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(6) _IObjectServerExtensionHostProxyVtbl = 
{
    &IObjectServerExtensionHost_ProxyInfo,
    &IID_IObjectServerExtensionHost,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IObjectServerExtensionHost::GetDBConnection */ ,
    (void *) (INT_PTR) -1 /* IObjectServerExtensionHost::Lock */ ,
    (void *) (INT_PTR) -1 /* IObjectServerExtensionHost::UnLock */
};

const CInterfaceStubVtbl _IObjectServerExtensionHostStubVtbl =
{
    &IID_IObjectServerExtensionHost,
    &IObjectServerExtensionHost_ServerInfo,
    6,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IObjectServerExtension, ver. 0.0,
   GUID={0x188cb18c,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short IObjectServerExtension_FormatStringOffsetTable[] =
    {
    4500
    };

static const MIDL_STUBLESS_PROXY_INFO IObjectServerExtension_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &IObjectServerExtension_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IObjectServerExtension_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &IObjectServerExtension_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _IObjectServerExtensionProxyVtbl = 
{
    &IObjectServerExtension_ProxyInfo,
    &IID_IObjectServerExtension,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IObjectServerExtension::Init */
};

const CInterfaceStubVtbl _IObjectServerExtensionStubVtbl =
{
    &IID_IObjectServerExtension,
    &IObjectServerExtension_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IPreprocessedDataCache, ver. 0.0,
   GUID={0x188cb188,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short IPreprocessedDataCache_FormatStringOffsetTable[] =
    {
    4536,
    4578
    };

static const MIDL_STUBLESS_PROXY_INFO IPreprocessedDataCache_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &IPreprocessedDataCache_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IPreprocessedDataCache_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &IPreprocessedDataCache_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IPreprocessedDataCacheProxyVtbl = 
{
    &IPreprocessedDataCache_ProxyInfo,
    &IID_IPreprocessedDataCache,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IPreprocessedDataCache::GetData */ ,
    (void *) (INT_PTR) -1 /* IPreprocessedDataCache::PutData */
};

const CInterfaceStubVtbl _IPreprocessedDataCacheStubVtbl =
{
    &IID_IPreprocessedDataCache,
    &IPreprocessedDataCache_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IPreprocessor, ver. 0.0,
   GUID={0x188cb165,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short IPreprocessor_FormatStringOffsetTable[] =
    {
    4620,
    4668,
    4710,
    4752,
    1704
    };

static const MIDL_STUBLESS_PROXY_INFO IPreprocessor_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &IPreprocessor_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IPreprocessor_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &IPreprocessor_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _IPreprocessorProxyVtbl = 
{
    &IPreprocessor_ProxyInfo,
    &IID_IPreprocessor,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IPreprocessor::Init */ ,
    (void *) (INT_PTR) -1 /* IPreprocessor::PreprocessFile */ ,
    (void *) (INT_PTR) -1 /* IPreprocessor::GetVarDependencies */ ,
    (void *) (INT_PTR) -1 /* IPreprocessor::GetIncludeDependencies */ ,
    (void *) (INT_PTR) -1 /* IPreprocessor::Close */
};

const CInterfaceStubVtbl _IPreprocessorStubVtbl =
{
    &IID_IPreprocessor,
    &IPreprocessor_ServerInfo,
    8,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ICachedData, ver. 0.0,
   GUID={0x188cb15b,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short ICachedData_FormatStringOffsetTable[] =
    {
    4794,
    4830,
    4896,
    4968,
    5028,
    5064,
    2334,
    5106,
    5142,
    5184,
    5232,
    5268,
    5334,
    5400,
    5442
    };

static const MIDL_STUBLESS_PROXY_INFO ICachedData_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &ICachedData_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ICachedData_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &ICachedData_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(18) _ICachedDataProxyVtbl = 
{
    &ICachedData_ProxyInfo,
    &IID_ICachedData,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ICachedData::Close */ ,
    (void *) (INT_PTR) -1 /* ICachedData::GetItem */ ,
    (void *) (INT_PTR) -1 /* ICachedData::StoreItem */ ,
    (void *) (INT_PTR) -1 /* ICachedData::RemoveItem */ ,
    (void *) (INT_PTR) -1 /* ICachedData::BeginTransaction */ ,
    (void *) (INT_PTR) -1 /* ICachedData::FinishTransaction */ ,
    (void *) (INT_PTR) -1 /* ICachedData::Purge */ ,
    (void *) (INT_PTR) -1 /* ICachedData::GetUniqueIdent */ ,
    (void *) (INT_PTR) -1 /* ICachedData::GetCacheInfoGUID */ ,
    (void *) (INT_PTR) -1 /* ICachedData::FTSQuery */ ,
    (void *) (INT_PTR) -1 /* ICachedData::SetOptions */ ,
    (void *) (INT_PTR) -1 /* ICachedData::StoreDataObject */ ,
    (void *) (INT_PTR) -1 /* ICachedData::RetrieveDataObject */ ,
    (void *) (INT_PTR) -1 /* ICachedData::WriteToArchive */ ,
    (void *) (INT_PTR) -1 /* ICachedData::ReadFromArchive */
};

const CInterfaceStubVtbl _ICachedDataStubVtbl =
{
    &IID_ICachedData,
    &ICachedData_ServerInfo,
    18,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Standard interface: __MIDL_itf_navo2001_0000_0022, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IServerClient, ver. 0.0,
   GUID={0x188cb162,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short IServerClient_FormatStringOffsetTable[] =
    {
    5484,
    5526,
    5580,
    5628,
    5664,
    5724,
    5760,
    5814,
    5868,
    5916,
    5952
    };

static const MIDL_STUBLESS_PROXY_INFO IServerClient_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &IServerClient_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IServerClient_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &IServerClient_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(14) _IServerClientProxyVtbl = 
{
    &IServerClient_ProxyInfo,
    &IID_IServerClient,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IServerClient::GetService */ ,
    (void *) (INT_PTR) -1 /* IServerClient::GetUpdateVersionIfNewer */ ,
    (void *) (INT_PTR) -1 /* IServerClient::AdviseLM */ ,
    (void *) (INT_PTR) -1 /* IServerClient::UnAdviseLM */ ,
    (void *) (INT_PTR) -1 /* IServerClient::AdviseNM */ ,
    (void *) (INT_PTR) -1 /* IServerClient::UnAdviseNM */ ,
    (void *) (INT_PTR) -1 /* IServerClient::GetRegistryKeyString */ ,
    (void *) (INT_PTR) -1 /* IServerClient::SetRegistryKeyString */ ,
    (void *) (INT_PTR) -1 /* IServerClient::EnumRegistryKeys */ ,
    (void *) (INT_PTR) -1 /* IServerClient::GetUniqueId */ ,
    (void *) (INT_PTR) -1 /* IServerClient::Close2 */
};

const CInterfaceStubVtbl _IServerClientStubVtbl =
{
    &IID_IServerClient,
    &IServerClient_ServerInfo,
    14,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IServerClientFactory, ver. 0.0,
   GUID={0x188cb162,0x2012,0x4499,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short IServerClientFactory_FormatStringOffsetTable[] =
    {
    5982
    };

static const MIDL_STUBLESS_PROXY_INFO IServerClientFactory_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &IServerClientFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IServerClientFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &IServerClientFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _IServerClientFactoryProxyVtbl = 
{
    &IServerClientFactory_ProxyInfo,
    &IID_IServerClientFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IServerClientFactory::GetServerClient */
};

const CInterfaceStubVtbl _IServerClientFactoryStubVtbl =
{
    &IID_IServerClientFactory,
    &IServerClientFactory_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ICrossInfoManager, ver. 0.0,
   GUID={0x188cb181,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short ICrossInfoManager_FormatStringOffsetTable[] =
    {
    6030,
    6078,
    2166
    };

static const MIDL_STUBLESS_PROXY_INFO ICrossInfoManager_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &ICrossInfoManager_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ICrossInfoManager_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &ICrossInfoManager_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(6) _ICrossInfoManagerProxyVtbl = 
{
    &ICrossInfoManager_ProxyInfo,
    &IID_ICrossInfoManager,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ICrossInfoManager::SetProp */ ,
    (void *) (INT_PTR) -1 /* ICrossInfoManager::GetProp */ ,
    (void *) (INT_PTR) -1 /* ICrossInfoManager::DeleteUser */
};

const CInterfaceStubVtbl _ICrossInfoManagerStubVtbl =
{
    &IID_ICrossInfoManager,
    &ICrossInfoManager_ServerInfo,
    6,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IVirtualMachine, ver. 0.0,
   GUID={0x188cb184,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short IVirtualMachine_FormatStringOffsetTable[] =
    {
    1902,
    1350,
    1632
    };

static const MIDL_STUBLESS_PROXY_INFO IVirtualMachine_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &IVirtualMachine_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IVirtualMachine_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &IVirtualMachine_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(6) _IVirtualMachineProxyVtbl = 
{
    &IVirtualMachine_ProxyInfo,
    &IID_IVirtualMachine,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IVirtualMachine::Load */ ,
    (void *) (INT_PTR) -1 /* IVirtualMachine::Init */ ,
    (void *) (INT_PTR) -1 /* IVirtualMachine::GetProgramObject */
};

const CInterfaceStubVtbl _IVirtualMachineStubVtbl =
{
    &IID_IVirtualMachine,
    &IVirtualMachine_ServerInfo,
    6,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IScriptCompiler, ver. 0.0,
   GUID={0x188cb182,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#pragma code_seg(".orpc")
static const unsigned short IScriptCompiler_FormatStringOffsetTable[] =
    {
    2094,
    1128,
    6126,
    6156,
    6198,
    6234,
    1770
    };

static const MIDL_STUBLESS_PROXY_INFO IScriptCompiler_ProxyInfo =
    {
    &Object_StubDesc,
    navo2001__MIDL_ProcFormatString.Format,
    &IScriptCompiler_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IScriptCompiler_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    navo2001__MIDL_ProcFormatString.Format,
    &IScriptCompiler_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IScriptCompilerProxyVtbl = 
{
    &IScriptCompiler_ProxyInfo,
    &IID_IScriptCompiler,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IScriptCompiler::SetSourceText */ ,
    (void *) (INT_PTR) -1 /* IScriptCompiler::DeclareIdent */ ,
    (void *) (INT_PTR) -1 /* IScriptCompiler::Compile */ ,
    (void *) (INT_PTR) -1 /* IScriptCompiler::GetLine */ ,
    (void *) (INT_PTR) -1 /* IScriptCompiler::Save */ ,
    (void *) (INT_PTR) -1 /* IScriptCompiler::GetVirtualMachine */ ,
    (void *) (INT_PTR) -1 /* IScriptCompiler::SetProp */
};

const CInterfaceStubVtbl _IScriptCompilerStubVtbl =
{
    &IID_IScriptCompiler,
    &IScriptCompiler_ServerInfo,
    10,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Standard interface: __MIDL_itf_navo2001_0000_0027, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: INEDataObject, ver. 0.0,
   GUID={0x188cb191,0x82a4,0x5000,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */


/* Object interface: INEDataObjectList, ver. 0.0,
   GUID={0x188cb192,0x82a4,0x5000,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */


/* Object interface: INEDataTransaction, ver. 0.0,
   GUID={0x188cb193,0x82a4,0x5000,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */


/* Standard interface: __MIDL_itf_navo2001_0000_0030, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: INUIElement, ver. 0.0,
   GUID={0x188cb1b1,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */


/* Object interface: INUIContainer, ver. 0.0,
   GUID={0x188cb1b2,0x82a4,0x4498,{0x87,0xd0,0xeb,0xd8,0xd9,0xa0,0x0f,0xb8}} */

#ifdef __cplusplus
namespace {
#endif
static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    navo2001__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x60001, /* Ndr library version */
    0,
    0x8010274, /* MIDL Version 8.1.628 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };
#ifdef __cplusplus
}
#endif

const CInterfaceProxyVtbl * const _navo2001_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_INavoErrorInfoProxyVtbl,
    ( CInterfaceProxyVtbl *) &_INotificationManagerProxyVtbl,
    ( CInterfaceProxyVtbl *) &_INotificationSinkProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ILockManagerProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IBackupRestoreProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IStreamProviderProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IAppDBManagerProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IBackupRestoreManagerProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ICachedDataProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IObjectServerProxyVtbl,
    ( CInterfaceProxyVtbl *) &_INAVOObjectCollectionProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IServerClientFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IServerClientProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IPreprocessorProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISupplyInfoProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISimpleEnumIdProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IStreamFilterProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IPingClientProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IPingServerProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IStreamSplitterProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ICntResourceManagerProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ICrossInfoManagerProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IScriptCompilerProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IVirtualMachineProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IPreprocessedDataCacheProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IObjectServerExtensionProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IObjectServerExtensionHostProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _navo2001_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_INavoErrorInfoStubVtbl,
    ( CInterfaceStubVtbl *) &_INotificationManagerStubVtbl,
    ( CInterfaceStubVtbl *) &_INotificationSinkStubVtbl,
    ( CInterfaceStubVtbl *) &_ILockManagerStubVtbl,
    ( CInterfaceStubVtbl *) &_IBackupRestoreStubVtbl,
    ( CInterfaceStubVtbl *) &_IStreamProviderStubVtbl,
    ( CInterfaceStubVtbl *) &_IAppDBManagerStubVtbl,
    ( CInterfaceStubVtbl *) &_IBackupRestoreManagerStubVtbl,
    ( CInterfaceStubVtbl *) &_ICachedDataStubVtbl,
    ( CInterfaceStubVtbl *) &_IObjectServerStubVtbl,
    ( CInterfaceStubVtbl *) &_INAVOObjectCollectionStubVtbl,
    ( CInterfaceStubVtbl *) &_IServerClientFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_IServerClientStubVtbl,
    ( CInterfaceStubVtbl *) &_IPreprocessorStubVtbl,
    ( CInterfaceStubVtbl *) &_ISupplyInfoStubVtbl,
    ( CInterfaceStubVtbl *) &_ISimpleEnumIdStubVtbl,
    ( CInterfaceStubVtbl *) &_IStreamFilterStubVtbl,
    ( CInterfaceStubVtbl *) &_IPingClientStubVtbl,
    ( CInterfaceStubVtbl *) &_IPingServerStubVtbl,
    ( CInterfaceStubVtbl *) &_IStreamSplitterStubVtbl,
    ( CInterfaceStubVtbl *) &_ICntResourceManagerStubVtbl,
    ( CInterfaceStubVtbl *) &_ICrossInfoManagerStubVtbl,
    ( CInterfaceStubVtbl *) &_IScriptCompilerStubVtbl,
    ( CInterfaceStubVtbl *) &_IVirtualMachineStubVtbl,
    ( CInterfaceStubVtbl *) &_IPreprocessedDataCacheStubVtbl,
    ( CInterfaceStubVtbl *) &_IObjectServerExtensionStubVtbl,
    ( CInterfaceStubVtbl *) &_IObjectServerExtensionHostStubVtbl,
    0
};

PCInterfaceName const _navo2001_InterfaceNamesList[] = 
{
    "INavoErrorInfo",
    "INotificationManager",
    "INotificationSink",
    "ILockManager",
    "IBackupRestore",
    "IStreamProvider",
    "IAppDBManager",
    "IBackupRestoreManager",
    "ICachedData",
    "IObjectServer",
    "INAVOObjectCollection",
    "IServerClientFactory",
    "IServerClient",
    "IPreprocessor",
    "ISupplyInfo",
    "ISimpleEnumId",
    "IStreamFilter",
    "IPingClient",
    "IPingServer",
    "IStreamSplitter",
    "ICntResourceManager",
    "ICrossInfoManager",
    "IScriptCompiler",
    "IVirtualMachine",
    "IPreprocessedDataCache",
    "IObjectServerExtension",
    "IObjectServerExtensionHost",
    0
};


#define _navo2001_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _navo2001, pIID, n)

int __stdcall _navo2001_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _navo2001, 27, 16 )
    IID_BS_LOOKUP_NEXT_TEST( _navo2001, 8 )
    IID_BS_LOOKUP_NEXT_TEST( _navo2001, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _navo2001, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _navo2001, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _navo2001, 27, *pIndex )
    
}

EXTERN_C const ExtendedProxyFileInfo navo2001_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _navo2001_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _navo2001_StubVtblList,
    (const PCInterfaceName * ) & _navo2001_InterfaceNamesList,
    0, /* no delegation */
    & _navo2001_IID_Lookup, 
    27,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_) */


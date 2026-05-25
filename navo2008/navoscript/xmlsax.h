
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0279 */
/* at Fri May 05 13:20:37 2000
 */
/* Compiler settings for xmlsax.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __xmlsax_h__
#define __xmlsax_h__

/* Forward Declarations */ 

#ifndef __ISAXXMLReader_FWD_DEFINED__
#define __ISAXXMLReader_FWD_DEFINED__
typedef interface ISAXXMLReader ISAXXMLReader;
#endif 	/* __ISAXXMLReader_FWD_DEFINED__ */


#ifndef __ISAXXMLFilter_FWD_DEFINED__
#define __ISAXXMLFilter_FWD_DEFINED__
typedef interface ISAXXMLFilter ISAXXMLFilter;
#endif 	/* __ISAXXMLFilter_FWD_DEFINED__ */


#ifndef __ISAXLocator_FWD_DEFINED__
#define __ISAXLocator_FWD_DEFINED__
typedef interface ISAXLocator ISAXLocator;
#endif 	/* __ISAXLocator_FWD_DEFINED__ */


#ifndef __ISAXEntityResolver_FWD_DEFINED__
#define __ISAXEntityResolver_FWD_DEFINED__
typedef interface ISAXEntityResolver ISAXEntityResolver;
#endif 	/* __ISAXEntityResolver_FWD_DEFINED__ */


#ifndef __ISAXContentHandler_FWD_DEFINED__
#define __ISAXContentHandler_FWD_DEFINED__
typedef interface ISAXContentHandler ISAXContentHandler;
#endif 	/* __ISAXContentHandler_FWD_DEFINED__ */


#ifndef __ISAXDTDHandler_FWD_DEFINED__
#define __ISAXDTDHandler_FWD_DEFINED__
typedef interface ISAXDTDHandler ISAXDTDHandler;
#endif 	/* __ISAXDTDHandler_FWD_DEFINED__ */


#ifndef __ISAXErrorHandler_FWD_DEFINED__
#define __ISAXErrorHandler_FWD_DEFINED__
typedef interface ISAXErrorHandler ISAXErrorHandler;
#endif 	/* __ISAXErrorHandler_FWD_DEFINED__ */


#ifndef __ISAXAttributes_FWD_DEFINED__
#define __ISAXAttributes_FWD_DEFINED__
typedef interface ISAXAttributes ISAXAttributes;
#endif 	/* __ISAXAttributes_FWD_DEFINED__ */


#ifndef __SAXXMLReader_FWD_DEFINED__
#define __SAXXMLReader_FWD_DEFINED__

#ifdef __cplusplus
typedef class SAXXMLReader SAXXMLReader;
#else
typedef struct SAXXMLReader SAXXMLReader;
#endif /* __cplusplus */

#endif 	/* __SAXXMLReader_FWD_DEFINED__ */


#ifndef __SAXXMLReader30_FWD_DEFINED__
#define __SAXXMLReader30_FWD_DEFINED__

#ifdef __cplusplus
typedef class SAXXMLReader30 SAXXMLReader30;
#else
typedef struct SAXXMLReader30 SAXXMLReader30;
#endif /* __cplusplus */

#endif 	/* __SAXXMLReader30_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "objidl.h"
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_xmlsax_0000 */
/* [local] */ 

//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 2000.
//
//--------------------------------------------------------------------------










extern RPC_IF_HANDLE __MIDL_itf_xmlsax_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_xmlsax_0000_v0_0_s_ifspec;


#ifndef __XMLSAX_LIBRARY_DEFINED__
#define __XMLSAX_LIBRARY_DEFINED__

/* library XMLSAX */
/* [version][lcid][helpstring][uuid] */ 

typedef /* [public][public][public][public] */ 
enum __MIDL___MIDL_itf_xmlsax_0115_0001
    {	SAX_CDATA	= 0,
	SAX_ID	= SAX_CDATA + 1,
	SAX_IDREF	= SAX_ID + 1,
	SAX_IDREFS	= SAX_IDREF + 1,
	SAX_ENTITY	= SAX_IDREFS + 1,
	SAX_ENTITIES	= SAX_ENTITY + 1,
	SAX_NMTOKEN	= SAX_ENTITIES + 1,
	SAX_NMTOKENS	= SAX_NMTOKEN + 1,
	SAX_NOTATION	= SAX_NMTOKENS + 1,
	SAX_ENUMERATION	= SAX_NOTATION + 1,
	SAX_ATTRIBUTE_TYPE_LAST	= SAX_ENUMERATION
    }	SAX_ATTRIBUTE_TYPE;


EXTERN_C const IID LIBID_XMLSAX;

#ifndef __ISAXXMLReader_INTERFACE_DEFINED__
#define __ISAXXMLReader_INTERFACE_DEFINED__

/* interface ISAXXMLReader */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_ISAXXMLReader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a4f96ed0-f829-476e-81c0-cdc7bd2a0802")
    ISAXXMLReader : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetFeature( 
            /* [in] */ const wchar_t __RPC_FAR *pwchName,
            /* [in] */ int cchName,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvfValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PutFeature( 
            /* [in] */ const wchar_t __RPC_FAR *pwchName,
            /* [in] */ int cchName,
            /* [in] */ VARIANT_BOOL vfValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProperty( 
            /* [in] */ const wchar_t __RPC_FAR *pwchName,
            /* [in] */ int cchName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PutProperty( 
            /* [in] */ const wchar_t __RPC_FAR *pwchName,
            /* [in] */ int cchName,
            /* [in] */ VARIANT varValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEntityResolver( 
            /* [retval][out] */ ISAXEntityResolver __RPC_FAR *__RPC_FAR *ppResolver) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PutEntityResolver( 
            /* [in] */ ISAXEntityResolver __RPC_FAR *pResolver) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetContentHandler( 
            /* [retval][out] */ ISAXContentHandler __RPC_FAR *__RPC_FAR *ppHandler) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PutContentHandler( 
            /* [in] */ ISAXContentHandler __RPC_FAR *pHandler) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDTDHandler( 
            /* [retval][out] */ ISAXDTDHandler __RPC_FAR *__RPC_FAR *ppHandler) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PutDTDHandler( 
            /* [in] */ ISAXDTDHandler __RPC_FAR *pHandler) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetErrorHandler( 
            /* [retval][out] */ ISAXErrorHandler __RPC_FAR *__RPC_FAR *ppHandler) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PutErrorHandler( 
            /* [in] */ ISAXErrorHandler __RPC_FAR *pHandler) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBaseURL( 
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchBaseUrl,
            /* [out] */ int __RPC_FAR *pcchBaseUrl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PutBaseURL( 
            /* [in] */ const wchar_t __RPC_FAR *pwchBaseUrl,
            /* [in] */ int cchBaseUrl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSecureBaseURL( 
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchSecureBaseUrl,
            /* [out] */ int __RPC_FAR *pcchSecureBaseUrl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PutSecureBaseURL( 
            /* [in] */ const wchar_t __RPC_FAR *pwchSecureBaseUrl,
            /* [in] */ int cchSecureBaseUrl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Parse( 
            /* [in] */ VARIANT varInput) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ParseURL( 
            /* [in] */ const wchar_t __RPC_FAR *pwchUrl,
            /* [in] */ int cchUrl) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISAXXMLReaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISAXXMLReader __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISAXXMLReader __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISAXXMLReader __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFeature )( 
            ISAXXMLReader __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchName,
            /* [in] */ int cchName,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvfValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutFeature )( 
            ISAXXMLReader __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchName,
            /* [in] */ int cchName,
            /* [in] */ VARIANT_BOOL vfValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProperty )( 
            ISAXXMLReader __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchName,
            /* [in] */ int cchName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutProperty )( 
            ISAXXMLReader __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchName,
            /* [in] */ int cchName,
            /* [in] */ VARIANT varValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEntityResolver )( 
            ISAXXMLReader __RPC_FAR * This,
            /* [retval][out] */ ISAXEntityResolver __RPC_FAR *__RPC_FAR *ppResolver);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEntityResolver )( 
            ISAXXMLReader __RPC_FAR * This,
            /* [in] */ ISAXEntityResolver __RPC_FAR *pResolver);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetContentHandler )( 
            ISAXXMLReader __RPC_FAR * This,
            /* [retval][out] */ ISAXContentHandler __RPC_FAR *__RPC_FAR *ppHandler);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutContentHandler )( 
            ISAXXMLReader __RPC_FAR * This,
            /* [in] */ ISAXContentHandler __RPC_FAR *pHandler);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDTDHandler )( 
            ISAXXMLReader __RPC_FAR * This,
            /* [retval][out] */ ISAXDTDHandler __RPC_FAR *__RPC_FAR *ppHandler);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutDTDHandler )( 
            ISAXXMLReader __RPC_FAR * This,
            /* [in] */ ISAXDTDHandler __RPC_FAR *pHandler);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetErrorHandler )( 
            ISAXXMLReader __RPC_FAR * This,
            /* [retval][out] */ ISAXErrorHandler __RPC_FAR *__RPC_FAR *ppHandler);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutErrorHandler )( 
            ISAXXMLReader __RPC_FAR * This,
            /* [in] */ ISAXErrorHandler __RPC_FAR *pHandler);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBaseURL )( 
            ISAXXMLReader __RPC_FAR * This,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchBaseUrl,
            /* [out] */ int __RPC_FAR *pcchBaseUrl);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutBaseURL )( 
            ISAXXMLReader __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchBaseUrl,
            /* [in] */ int cchBaseUrl);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSecureBaseURL )( 
            ISAXXMLReader __RPC_FAR * This,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchSecureBaseUrl,
            /* [out] */ int __RPC_FAR *pcchSecureBaseUrl);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutSecureBaseURL )( 
            ISAXXMLReader __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchSecureBaseUrl,
            /* [in] */ int cchSecureBaseUrl);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Parse )( 
            ISAXXMLReader __RPC_FAR * This,
            /* [in] */ VARIANT varInput);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ParseURL )( 
            ISAXXMLReader __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchUrl,
            /* [in] */ int cchUrl);
        
        END_INTERFACE
    } ISAXXMLReaderVtbl;

    interface ISAXXMLReader
    {
        CONST_VTBL struct ISAXXMLReaderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISAXXMLReader_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISAXXMLReader_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISAXXMLReader_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISAXXMLReader_GetFeature(This,pwchName,cchName,pvfValue)	\
    (This)->lpVtbl -> GetFeature(This,pwchName,cchName,pvfValue)

#define ISAXXMLReader_PutFeature(This,pwchName,cchName,vfValue)	\
    (This)->lpVtbl -> PutFeature(This,pwchName,cchName,vfValue)

#define ISAXXMLReader_GetProperty(This,pwchName,cchName,pvarValue)	\
    (This)->lpVtbl -> GetProperty(This,pwchName,cchName,pvarValue)

#define ISAXXMLReader_PutProperty(This,pwchName,cchName,varValue)	\
    (This)->lpVtbl -> PutProperty(This,pwchName,cchName,varValue)

#define ISAXXMLReader_GetEntityResolver(This,ppResolver)	\
    (This)->lpVtbl -> GetEntityResolver(This,ppResolver)

#define ISAXXMLReader_PutEntityResolver(This,pResolver)	\
    (This)->lpVtbl -> PutEntityResolver(This,pResolver)

#define ISAXXMLReader_GetContentHandler(This,ppHandler)	\
    (This)->lpVtbl -> GetContentHandler(This,ppHandler)

#define ISAXXMLReader_PutContentHandler(This,pHandler)	\
    (This)->lpVtbl -> PutContentHandler(This,pHandler)

#define ISAXXMLReader_GetDTDHandler(This,ppHandler)	\
    (This)->lpVtbl -> GetDTDHandler(This,ppHandler)

#define ISAXXMLReader_PutDTDHandler(This,pHandler)	\
    (This)->lpVtbl -> PutDTDHandler(This,pHandler)

#define ISAXXMLReader_GetErrorHandler(This,ppHandler)	\
    (This)->lpVtbl -> GetErrorHandler(This,ppHandler)

#define ISAXXMLReader_PutErrorHandler(This,pHandler)	\
    (This)->lpVtbl -> PutErrorHandler(This,pHandler)

#define ISAXXMLReader_GetBaseURL(This,ppwchBaseUrl,pcchBaseUrl)	\
    (This)->lpVtbl -> GetBaseURL(This,ppwchBaseUrl,pcchBaseUrl)

#define ISAXXMLReader_PutBaseURL(This,pwchBaseUrl,cchBaseUrl)	\
    (This)->lpVtbl -> PutBaseURL(This,pwchBaseUrl,cchBaseUrl)

#define ISAXXMLReader_GetSecureBaseURL(This,ppwchSecureBaseUrl,pcchSecureBaseUrl)	\
    (This)->lpVtbl -> GetSecureBaseURL(This,ppwchSecureBaseUrl,pcchSecureBaseUrl)

#define ISAXXMLReader_PutSecureBaseURL(This,pwchSecureBaseUrl,cchSecureBaseUrl)	\
    (This)->lpVtbl -> PutSecureBaseURL(This,pwchSecureBaseUrl,cchSecureBaseUrl)

#define ISAXXMLReader_Parse(This,varInput)	\
    (This)->lpVtbl -> Parse(This,varInput)

#define ISAXXMLReader_ParseURL(This,pwchUrl,cchUrl)	\
    (This)->lpVtbl -> ParseURL(This,pwchUrl,cchUrl)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISAXXMLReader_GetFeature_Proxy( 
    ISAXXMLReader __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchName,
    /* [in] */ int cchName,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvfValue);


void __RPC_STUB ISAXXMLReader_GetFeature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXXMLReader_PutFeature_Proxy( 
    ISAXXMLReader __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchName,
    /* [in] */ int cchName,
    /* [in] */ VARIANT_BOOL vfValue);


void __RPC_STUB ISAXXMLReader_PutFeature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXXMLReader_GetProperty_Proxy( 
    ISAXXMLReader __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchName,
    /* [in] */ int cchName,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarValue);


void __RPC_STUB ISAXXMLReader_GetProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXXMLReader_PutProperty_Proxy( 
    ISAXXMLReader __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchName,
    /* [in] */ int cchName,
    /* [in] */ VARIANT varValue);


void __RPC_STUB ISAXXMLReader_PutProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXXMLReader_GetEntityResolver_Proxy( 
    ISAXXMLReader __RPC_FAR * This,
    /* [retval][out] */ ISAXEntityResolver __RPC_FAR *__RPC_FAR *ppResolver);


void __RPC_STUB ISAXXMLReader_GetEntityResolver_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXXMLReader_PutEntityResolver_Proxy( 
    ISAXXMLReader __RPC_FAR * This,
    /* [in] */ ISAXEntityResolver __RPC_FAR *pResolver);


void __RPC_STUB ISAXXMLReader_PutEntityResolver_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXXMLReader_GetContentHandler_Proxy( 
    ISAXXMLReader __RPC_FAR * This,
    /* [retval][out] */ ISAXContentHandler __RPC_FAR *__RPC_FAR *ppHandler);


void __RPC_STUB ISAXXMLReader_GetContentHandler_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXXMLReader_PutContentHandler_Proxy( 
    ISAXXMLReader __RPC_FAR * This,
    /* [in] */ ISAXContentHandler __RPC_FAR *pHandler);


void __RPC_STUB ISAXXMLReader_PutContentHandler_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXXMLReader_GetDTDHandler_Proxy( 
    ISAXXMLReader __RPC_FAR * This,
    /* [retval][out] */ ISAXDTDHandler __RPC_FAR *__RPC_FAR *ppHandler);


void __RPC_STUB ISAXXMLReader_GetDTDHandler_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXXMLReader_PutDTDHandler_Proxy( 
    ISAXXMLReader __RPC_FAR * This,
    /* [in] */ ISAXDTDHandler __RPC_FAR *pHandler);


void __RPC_STUB ISAXXMLReader_PutDTDHandler_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXXMLReader_GetErrorHandler_Proxy( 
    ISAXXMLReader __RPC_FAR * This,
    /* [retval][out] */ ISAXErrorHandler __RPC_FAR *__RPC_FAR *ppHandler);


void __RPC_STUB ISAXXMLReader_GetErrorHandler_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXXMLReader_PutErrorHandler_Proxy( 
    ISAXXMLReader __RPC_FAR * This,
    /* [in] */ ISAXErrorHandler __RPC_FAR *pHandler);


void __RPC_STUB ISAXXMLReader_PutErrorHandler_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXXMLReader_GetBaseURL_Proxy( 
    ISAXXMLReader __RPC_FAR * This,
    /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchBaseUrl,
    /* [out] */ int __RPC_FAR *pcchBaseUrl);


void __RPC_STUB ISAXXMLReader_GetBaseURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXXMLReader_PutBaseURL_Proxy( 
    ISAXXMLReader __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchBaseUrl,
    /* [in] */ int cchBaseUrl);


void __RPC_STUB ISAXXMLReader_PutBaseURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXXMLReader_GetSecureBaseURL_Proxy( 
    ISAXXMLReader __RPC_FAR * This,
    /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchSecureBaseUrl,
    /* [out] */ int __RPC_FAR *pcchSecureBaseUrl);


void __RPC_STUB ISAXXMLReader_GetSecureBaseURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXXMLReader_PutSecureBaseURL_Proxy( 
    ISAXXMLReader __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchSecureBaseUrl,
    /* [in] */ int cchSecureBaseUrl);


void __RPC_STUB ISAXXMLReader_PutSecureBaseURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXXMLReader_Parse_Proxy( 
    ISAXXMLReader __RPC_FAR * This,
    /* [in] */ VARIANT varInput);


void __RPC_STUB ISAXXMLReader_Parse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXXMLReader_ParseURL_Proxy( 
    ISAXXMLReader __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchUrl,
    /* [in] */ int cchUrl);


void __RPC_STUB ISAXXMLReader_ParseURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISAXXMLReader_INTERFACE_DEFINED__ */


#ifndef __ISAXXMLFilter_INTERFACE_DEFINED__
#define __ISAXXMLFilter_INTERFACE_DEFINED__

/* interface ISAXXMLFilter */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_ISAXXMLFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("70409222-ca09-4475-acb8-40312fe8d145")
    ISAXXMLFilter : public ISAXXMLReader
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetParent( 
            /* [retval][out] */ ISAXXMLReader __RPC_FAR *__RPC_FAR *ppReader) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PutParent( 
            /* [in] */ ISAXXMLReader __RPC_FAR *pReader) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISAXXMLFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISAXXMLFilter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISAXXMLFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFeature )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchName,
            /* [in] */ int cchName,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvfValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutFeature )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchName,
            /* [in] */ int cchName,
            /* [in] */ VARIANT_BOOL vfValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProperty )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchName,
            /* [in] */ int cchName,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutProperty )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchName,
            /* [in] */ int cchName,
            /* [in] */ VARIANT varValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEntityResolver )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [retval][out] */ ISAXEntityResolver __RPC_FAR *__RPC_FAR *ppResolver);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutEntityResolver )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [in] */ ISAXEntityResolver __RPC_FAR *pResolver);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetContentHandler )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [retval][out] */ ISAXContentHandler __RPC_FAR *__RPC_FAR *ppHandler);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutContentHandler )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [in] */ ISAXContentHandler __RPC_FAR *pHandler);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDTDHandler )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [retval][out] */ ISAXDTDHandler __RPC_FAR *__RPC_FAR *ppHandler);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutDTDHandler )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [in] */ ISAXDTDHandler __RPC_FAR *pHandler);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetErrorHandler )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [retval][out] */ ISAXErrorHandler __RPC_FAR *__RPC_FAR *ppHandler);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutErrorHandler )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [in] */ ISAXErrorHandler __RPC_FAR *pHandler);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBaseURL )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchBaseUrl,
            /* [out] */ int __RPC_FAR *pcchBaseUrl);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutBaseURL )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchBaseUrl,
            /* [in] */ int cchBaseUrl);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSecureBaseURL )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchSecureBaseUrl,
            /* [out] */ int __RPC_FAR *pcchSecureBaseUrl);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutSecureBaseURL )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchSecureBaseUrl,
            /* [in] */ int cchSecureBaseUrl);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Parse )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [in] */ VARIANT varInput);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ParseURL )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchUrl,
            /* [in] */ int cchUrl);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParent )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [retval][out] */ ISAXXMLReader __RPC_FAR *__RPC_FAR *ppReader);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutParent )( 
            ISAXXMLFilter __RPC_FAR * This,
            /* [in] */ ISAXXMLReader __RPC_FAR *pReader);
        
        END_INTERFACE
    } ISAXXMLFilterVtbl;

    interface ISAXXMLFilter
    {
        CONST_VTBL struct ISAXXMLFilterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISAXXMLFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISAXXMLFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISAXXMLFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISAXXMLFilter_GetFeature(This,pwchName,cchName,pvfValue)	\
    (This)->lpVtbl -> GetFeature(This,pwchName,cchName,pvfValue)

#define ISAXXMLFilter_PutFeature(This,pwchName,cchName,vfValue)	\
    (This)->lpVtbl -> PutFeature(This,pwchName,cchName,vfValue)

#define ISAXXMLFilter_GetProperty(This,pwchName,cchName,pvarValue)	\
    (This)->lpVtbl -> GetProperty(This,pwchName,cchName,pvarValue)

#define ISAXXMLFilter_PutProperty(This,pwchName,cchName,varValue)	\
    (This)->lpVtbl -> PutProperty(This,pwchName,cchName,varValue)

#define ISAXXMLFilter_GetEntityResolver(This,ppResolver)	\
    (This)->lpVtbl -> GetEntityResolver(This,ppResolver)

#define ISAXXMLFilter_PutEntityResolver(This,pResolver)	\
    (This)->lpVtbl -> PutEntityResolver(This,pResolver)

#define ISAXXMLFilter_GetContentHandler(This,ppHandler)	\
    (This)->lpVtbl -> GetContentHandler(This,ppHandler)

#define ISAXXMLFilter_PutContentHandler(This,pHandler)	\
    (This)->lpVtbl -> PutContentHandler(This,pHandler)

#define ISAXXMLFilter_GetDTDHandler(This,ppHandler)	\
    (This)->lpVtbl -> GetDTDHandler(This,ppHandler)

#define ISAXXMLFilter_PutDTDHandler(This,pHandler)	\
    (This)->lpVtbl -> PutDTDHandler(This,pHandler)

#define ISAXXMLFilter_GetErrorHandler(This,ppHandler)	\
    (This)->lpVtbl -> GetErrorHandler(This,ppHandler)

#define ISAXXMLFilter_PutErrorHandler(This,pHandler)	\
    (This)->lpVtbl -> PutErrorHandler(This,pHandler)

#define ISAXXMLFilter_GetBaseURL(This,ppwchBaseUrl,pcchBaseUrl)	\
    (This)->lpVtbl -> GetBaseURL(This,ppwchBaseUrl,pcchBaseUrl)

#define ISAXXMLFilter_PutBaseURL(This,pwchBaseUrl,cchBaseUrl)	\
    (This)->lpVtbl -> PutBaseURL(This,pwchBaseUrl,cchBaseUrl)

#define ISAXXMLFilter_GetSecureBaseURL(This,ppwchSecureBaseUrl,pcchSecureBaseUrl)	\
    (This)->lpVtbl -> GetSecureBaseURL(This,ppwchSecureBaseUrl,pcchSecureBaseUrl)

#define ISAXXMLFilter_PutSecureBaseURL(This,pwchSecureBaseUrl,cchSecureBaseUrl)	\
    (This)->lpVtbl -> PutSecureBaseURL(This,pwchSecureBaseUrl,cchSecureBaseUrl)

#define ISAXXMLFilter_Parse(This,varInput)	\
    (This)->lpVtbl -> Parse(This,varInput)

#define ISAXXMLFilter_ParseURL(This,pwchUrl,cchUrl)	\
    (This)->lpVtbl -> ParseURL(This,pwchUrl,cchUrl)


#define ISAXXMLFilter_GetParent(This,ppReader)	\
    (This)->lpVtbl -> GetParent(This,ppReader)

#define ISAXXMLFilter_PutParent(This,pReader)	\
    (This)->lpVtbl -> PutParent(This,pReader)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISAXXMLFilter_GetParent_Proxy( 
    ISAXXMLFilter __RPC_FAR * This,
    /* [retval][out] */ ISAXXMLReader __RPC_FAR *__RPC_FAR *ppReader);


void __RPC_STUB ISAXXMLFilter_GetParent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXXMLFilter_PutParent_Proxy( 
    ISAXXMLFilter __RPC_FAR * This,
    /* [in] */ ISAXXMLReader __RPC_FAR *pReader);


void __RPC_STUB ISAXXMLFilter_PutParent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISAXXMLFilter_INTERFACE_DEFINED__ */


#ifndef __ISAXLocator_INTERFACE_DEFINED__
#define __ISAXLocator_INTERFACE_DEFINED__

/* interface ISAXLocator */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_ISAXLocator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9b7e472a-0de4-4640-bff3-84d38a051c31")
    ISAXLocator : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetColumnNumber( 
            /* [retval][out] */ int __RPC_FAR *pnColumn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLineNumber( 
            /* [retval][out] */ int __RPC_FAR *pnLine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPublicId( 
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchPublicId,
            /* [out] */ int __RPC_FAR *pcchPublicId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSystemId( 
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchSystemId,
            /* [out] */ int __RPC_FAR *pcchSystemId) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISAXLocatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISAXLocator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISAXLocator __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISAXLocator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetColumnNumber )( 
            ISAXLocator __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pnColumn);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLineNumber )( 
            ISAXLocator __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pnLine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPublicId )( 
            ISAXLocator __RPC_FAR * This,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchPublicId,
            /* [out] */ int __RPC_FAR *pcchPublicId);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSystemId )( 
            ISAXLocator __RPC_FAR * This,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchSystemId,
            /* [out] */ int __RPC_FAR *pcchSystemId);
        
        END_INTERFACE
    } ISAXLocatorVtbl;

    interface ISAXLocator
    {
        CONST_VTBL struct ISAXLocatorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISAXLocator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISAXLocator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISAXLocator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISAXLocator_GetColumnNumber(This,pnColumn)	\
    (This)->lpVtbl -> GetColumnNumber(This,pnColumn)

#define ISAXLocator_GetLineNumber(This,pnLine)	\
    (This)->lpVtbl -> GetLineNumber(This,pnLine)

#define ISAXLocator_GetPublicId(This,ppwchPublicId,pcchPublicId)	\
    (This)->lpVtbl -> GetPublicId(This,ppwchPublicId,pcchPublicId)

#define ISAXLocator_GetSystemId(This,ppwchSystemId,pcchSystemId)	\
    (This)->lpVtbl -> GetSystemId(This,ppwchSystemId,pcchSystemId)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISAXLocator_GetColumnNumber_Proxy( 
    ISAXLocator __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pnColumn);


void __RPC_STUB ISAXLocator_GetColumnNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXLocator_GetLineNumber_Proxy( 
    ISAXLocator __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pnLine);


void __RPC_STUB ISAXLocator_GetLineNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXLocator_GetPublicId_Proxy( 
    ISAXLocator __RPC_FAR * This,
    /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchPublicId,
    /* [out] */ int __RPC_FAR *pcchPublicId);


void __RPC_STUB ISAXLocator_GetPublicId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXLocator_GetSystemId_Proxy( 
    ISAXLocator __RPC_FAR * This,
    /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchSystemId,
    /* [out] */ int __RPC_FAR *pcchSystemId);


void __RPC_STUB ISAXLocator_GetSystemId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISAXLocator_INTERFACE_DEFINED__ */


#ifndef __ISAXEntityResolver_INTERFACE_DEFINED__
#define __ISAXEntityResolver_INTERFACE_DEFINED__

/* interface ISAXEntityResolver */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_ISAXEntityResolver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("99bca7bd-e8c4-4d5f-a0cf-6d907901ff07")
    ISAXEntityResolver : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResolveEntity( 
            /* [in] */ const wchar_t __RPC_FAR *pwchPublicId,
            /* [in] */ int cchPublicId,
            /* [in] */ const wchar_t __RPC_FAR *pwchSystemId,
            /* [in] */ int cchSystemId,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarInput) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISAXEntityResolverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISAXEntityResolver __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISAXEntityResolver __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISAXEntityResolver __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResolveEntity )( 
            ISAXEntityResolver __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchPublicId,
            /* [in] */ int cchPublicId,
            /* [in] */ const wchar_t __RPC_FAR *pwchSystemId,
            /* [in] */ int cchSystemId,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarInput);
        
        END_INTERFACE
    } ISAXEntityResolverVtbl;

    interface ISAXEntityResolver
    {
        CONST_VTBL struct ISAXEntityResolverVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISAXEntityResolver_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISAXEntityResolver_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISAXEntityResolver_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISAXEntityResolver_ResolveEntity(This,pwchPublicId,cchPublicId,pwchSystemId,cchSystemId,pvarInput)	\
    (This)->lpVtbl -> ResolveEntity(This,pwchPublicId,cchPublicId,pwchSystemId,cchSystemId,pvarInput)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISAXEntityResolver_ResolveEntity_Proxy( 
    ISAXEntityResolver __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchPublicId,
    /* [in] */ int cchPublicId,
    /* [in] */ const wchar_t __RPC_FAR *pwchSystemId,
    /* [in] */ int cchSystemId,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarInput);


void __RPC_STUB ISAXEntityResolver_ResolveEntity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISAXEntityResolver_INTERFACE_DEFINED__ */


#ifndef __ISAXContentHandler_INTERFACE_DEFINED__
#define __ISAXContentHandler_INTERFACE_DEFINED__

/* interface ISAXContentHandler */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_ISAXContentHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1545cdfa-9e4e-4497-a8a4-2bf7d0112c44")
    ISAXContentHandler : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE PutDocumentLocator( 
            /* [in] */ ISAXLocator __RPC_FAR *pLocator) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StartDocument( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EndDocument( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StartPrefixMapping( 
            /* [in] */ const wchar_t __RPC_FAR *pwchPrefix,
            /* [in] */ int cchPrefix,
            /* [in] */ const wchar_t __RPC_FAR *pwchUri,
            /* [in] */ int cchUri) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EndPrefixMapping( 
            /* [in] */ const wchar_t __RPC_FAR *pwchPrefix,
            /* [in] */ int cchPrefix) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StartElement( 
            /* [in] */ const wchar_t __RPC_FAR *pwchNamespaceUri,
            /* [in] */ int cchNamespaceUri,
            /* [in] */ const wchar_t __RPC_FAR *pwchLocalName,
            /* [in] */ int cchLocalName,
            /* [in] */ const wchar_t __RPC_FAR *pwchQName,
            /* [in] */ int cchQName,
            /* [in] */ ISAXAttributes __RPC_FAR *pAttributes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EndElement( 
            /* [in] */ const wchar_t __RPC_FAR *pwchNamespaceUri,
            /* [in] */ int cchNamespaceUri,
            /* [in] */ const wchar_t __RPC_FAR *pwchLocalName,
            /* [in] */ int cchLocalName,
            /* [in] */ const wchar_t __RPC_FAR *pwchQName,
            /* [in] */ int cchQName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Characters( 
            /* [in] */ const wchar_t __RPC_FAR *pwchChars,
            /* [in] */ int cchChars) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IgnorableWhitespace( 
            /* [in] */ const wchar_t __RPC_FAR *pwchChars,
            /* [in] */ int cchChars) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ProcessingInstruction( 
            /* [in] */ const wchar_t __RPC_FAR *pwchTarget,
            /* [in] */ int cchTarget,
            /* [in] */ const wchar_t __RPC_FAR *pwchData,
            /* [in] */ int cchData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SkippedEntity( 
            /* [in] */ const wchar_t __RPC_FAR *pwchName,
            /* [in] */ int cchName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISAXContentHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISAXContentHandler __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISAXContentHandler __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISAXContentHandler __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutDocumentLocator )( 
            ISAXContentHandler __RPC_FAR * This,
            /* [in] */ ISAXLocator __RPC_FAR *pLocator);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartDocument )( 
            ISAXContentHandler __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EndDocument )( 
            ISAXContentHandler __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartPrefixMapping )( 
            ISAXContentHandler __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchPrefix,
            /* [in] */ int cchPrefix,
            /* [in] */ const wchar_t __RPC_FAR *pwchUri,
            /* [in] */ int cchUri);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EndPrefixMapping )( 
            ISAXContentHandler __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchPrefix,
            /* [in] */ int cchPrefix);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartElement )( 
            ISAXContentHandler __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchNamespaceUri,
            /* [in] */ int cchNamespaceUri,
            /* [in] */ const wchar_t __RPC_FAR *pwchLocalName,
            /* [in] */ int cchLocalName,
            /* [in] */ const wchar_t __RPC_FAR *pwchQName,
            /* [in] */ int cchQName,
            /* [in] */ ISAXAttributes __RPC_FAR *pAttributes);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EndElement )( 
            ISAXContentHandler __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchNamespaceUri,
            /* [in] */ int cchNamespaceUri,
            /* [in] */ const wchar_t __RPC_FAR *pwchLocalName,
            /* [in] */ int cchLocalName,
            /* [in] */ const wchar_t __RPC_FAR *pwchQName,
            /* [in] */ int cchQName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Characters )( 
            ISAXContentHandler __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchChars,
            /* [in] */ int cchChars);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IgnorableWhitespace )( 
            ISAXContentHandler __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchChars,
            /* [in] */ int cchChars);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ProcessingInstruction )( 
            ISAXContentHandler __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchTarget,
            /* [in] */ int cchTarget,
            /* [in] */ const wchar_t __RPC_FAR *pwchData,
            /* [in] */ int cchData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SkippedEntity )( 
            ISAXContentHandler __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchName,
            /* [in] */ int cchName);
        
        END_INTERFACE
    } ISAXContentHandlerVtbl;

    interface ISAXContentHandler
    {
        CONST_VTBL struct ISAXContentHandlerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISAXContentHandler_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISAXContentHandler_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISAXContentHandler_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISAXContentHandler_PutDocumentLocator(This,pLocator)	\
    (This)->lpVtbl -> PutDocumentLocator(This,pLocator)

#define ISAXContentHandler_StartDocument(This)	\
    (This)->lpVtbl -> StartDocument(This)

#define ISAXContentHandler_EndDocument(This)	\
    (This)->lpVtbl -> EndDocument(This)

#define ISAXContentHandler_StartPrefixMapping(This,pwchPrefix,cchPrefix,pwchUri,cchUri)	\
    (This)->lpVtbl -> StartPrefixMapping(This,pwchPrefix,cchPrefix,pwchUri,cchUri)

#define ISAXContentHandler_EndPrefixMapping(This,pwchPrefix,cchPrefix)	\
    (This)->lpVtbl -> EndPrefixMapping(This,pwchPrefix,cchPrefix)

#define ISAXContentHandler_StartElement(This,pwchNamespaceUri,cchNamespaceUri,pwchLocalName,cchLocalName,pwchQName,cchQName,pAttributes)	\
    (This)->lpVtbl -> StartElement(This,pwchNamespaceUri,cchNamespaceUri,pwchLocalName,cchLocalName,pwchQName,cchQName,pAttributes)

#define ISAXContentHandler_EndElement(This,pwchNamespaceUri,cchNamespaceUri,pwchLocalName,cchLocalName,pwchQName,cchQName)	\
    (This)->lpVtbl -> EndElement(This,pwchNamespaceUri,cchNamespaceUri,pwchLocalName,cchLocalName,pwchQName,cchQName)

#define ISAXContentHandler_Characters(This,pwchChars,cchChars)	\
    (This)->lpVtbl -> Characters(This,pwchChars,cchChars)

#define ISAXContentHandler_IgnorableWhitespace(This,pwchChars,cchChars)	\
    (This)->lpVtbl -> IgnorableWhitespace(This,pwchChars,cchChars)

#define ISAXContentHandler_ProcessingInstruction(This,pwchTarget,cchTarget,pwchData,cchData)	\
    (This)->lpVtbl -> ProcessingInstruction(This,pwchTarget,cchTarget,pwchData,cchData)

#define ISAXContentHandler_SkippedEntity(This,pwchName,cchName)	\
    (This)->lpVtbl -> SkippedEntity(This,pwchName,cchName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISAXContentHandler_PutDocumentLocator_Proxy( 
    ISAXContentHandler __RPC_FAR * This,
    /* [in] */ ISAXLocator __RPC_FAR *pLocator);


void __RPC_STUB ISAXContentHandler_PutDocumentLocator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXContentHandler_StartDocument_Proxy( 
    ISAXContentHandler __RPC_FAR * This);


void __RPC_STUB ISAXContentHandler_StartDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXContentHandler_EndDocument_Proxy( 
    ISAXContentHandler __RPC_FAR * This);


void __RPC_STUB ISAXContentHandler_EndDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXContentHandler_StartPrefixMapping_Proxy( 
    ISAXContentHandler __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchPrefix,
    /* [in] */ int cchPrefix,
    /* [in] */ const wchar_t __RPC_FAR *pwchUri,
    /* [in] */ int cchUri);


void __RPC_STUB ISAXContentHandler_StartPrefixMapping_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXContentHandler_EndPrefixMapping_Proxy( 
    ISAXContentHandler __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchPrefix,
    /* [in] */ int cchPrefix);


void __RPC_STUB ISAXContentHandler_EndPrefixMapping_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXContentHandler_StartElement_Proxy( 
    ISAXContentHandler __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchNamespaceUri,
    /* [in] */ int cchNamespaceUri,
    /* [in] */ const wchar_t __RPC_FAR *pwchLocalName,
    /* [in] */ int cchLocalName,
    /* [in] */ const wchar_t __RPC_FAR *pwchQName,
    /* [in] */ int cchQName,
    /* [in] */ ISAXAttributes __RPC_FAR *pAttributes);


void __RPC_STUB ISAXContentHandler_StartElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXContentHandler_EndElement_Proxy( 
    ISAXContentHandler __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchNamespaceUri,
    /* [in] */ int cchNamespaceUri,
    /* [in] */ const wchar_t __RPC_FAR *pwchLocalName,
    /* [in] */ int cchLocalName,
    /* [in] */ const wchar_t __RPC_FAR *pwchQName,
    /* [in] */ int cchQName);


void __RPC_STUB ISAXContentHandler_EndElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXContentHandler_Characters_Proxy( 
    ISAXContentHandler __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchChars,
    /* [in] */ int cchChars);


void __RPC_STUB ISAXContentHandler_Characters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXContentHandler_IgnorableWhitespace_Proxy( 
    ISAXContentHandler __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchChars,
    /* [in] */ int cchChars);


void __RPC_STUB ISAXContentHandler_IgnorableWhitespace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXContentHandler_ProcessingInstruction_Proxy( 
    ISAXContentHandler __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchTarget,
    /* [in] */ int cchTarget,
    /* [in] */ const wchar_t __RPC_FAR *pwchData,
    /* [in] */ int cchData);


void __RPC_STUB ISAXContentHandler_ProcessingInstruction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXContentHandler_SkippedEntity_Proxy( 
    ISAXContentHandler __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchName,
    /* [in] */ int cchName);


void __RPC_STUB ISAXContentHandler_SkippedEntity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISAXContentHandler_INTERFACE_DEFINED__ */


#ifndef __ISAXDTDHandler_INTERFACE_DEFINED__
#define __ISAXDTDHandler_INTERFACE_DEFINED__

/* interface ISAXDTDHandler */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_ISAXDTDHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("e15c1baf-afb3-4d60-8c36-19a8c45defed")
    ISAXDTDHandler : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE NotationDecl( 
            /* [in] */ const wchar_t __RPC_FAR *pwchName,
            /* [in] */ int cchName,
            /* [in] */ const wchar_t __RPC_FAR *pwchPublicId,
            /* [in] */ int cchPublicId,
            /* [in] */ const wchar_t __RPC_FAR *pwchSystemId,
            /* [in] */ int cchSystemId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnparsedEntityDecl( 
            /* [in] */ const wchar_t __RPC_FAR *pwchName,
            /* [in] */ int cchName,
            /* [in] */ const wchar_t __RPC_FAR *pwchPublicId,
            /* [in] */ int cchPublicId,
            /* [in] */ const wchar_t __RPC_FAR *pwchSystemId,
            /* [in] */ int cchSystemId,
            /* [in] */ const wchar_t __RPC_FAR *pwchNotationName,
            /* [in] */ int cchNotationName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISAXDTDHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISAXDTDHandler __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISAXDTDHandler __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISAXDTDHandler __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NotationDecl )( 
            ISAXDTDHandler __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchName,
            /* [in] */ int cchName,
            /* [in] */ const wchar_t __RPC_FAR *pwchPublicId,
            /* [in] */ int cchPublicId,
            /* [in] */ const wchar_t __RPC_FAR *pwchSystemId,
            /* [in] */ int cchSystemId);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnparsedEntityDecl )( 
            ISAXDTDHandler __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchName,
            /* [in] */ int cchName,
            /* [in] */ const wchar_t __RPC_FAR *pwchPublicId,
            /* [in] */ int cchPublicId,
            /* [in] */ const wchar_t __RPC_FAR *pwchSystemId,
            /* [in] */ int cchSystemId,
            /* [in] */ const wchar_t __RPC_FAR *pwchNotationName,
            /* [in] */ int cchNotationName);
        
        END_INTERFACE
    } ISAXDTDHandlerVtbl;

    interface ISAXDTDHandler
    {
        CONST_VTBL struct ISAXDTDHandlerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISAXDTDHandler_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISAXDTDHandler_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISAXDTDHandler_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISAXDTDHandler_NotationDecl(This,pwchName,cchName,pwchPublicId,cchPublicId,pwchSystemId,cchSystemId)	\
    (This)->lpVtbl -> NotationDecl(This,pwchName,cchName,pwchPublicId,cchPublicId,pwchSystemId,cchSystemId)

#define ISAXDTDHandler_UnparsedEntityDecl(This,pwchName,cchName,pwchPublicId,cchPublicId,pwchSystemId,cchSystemId,pwchNotationName,cchNotationName)	\
    (This)->lpVtbl -> UnparsedEntityDecl(This,pwchName,cchName,pwchPublicId,cchPublicId,pwchSystemId,cchSystemId,pwchNotationName,cchNotationName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISAXDTDHandler_NotationDecl_Proxy( 
    ISAXDTDHandler __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchName,
    /* [in] */ int cchName,
    /* [in] */ const wchar_t __RPC_FAR *pwchPublicId,
    /* [in] */ int cchPublicId,
    /* [in] */ const wchar_t __RPC_FAR *pwchSystemId,
    /* [in] */ int cchSystemId);


void __RPC_STUB ISAXDTDHandler_NotationDecl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXDTDHandler_UnparsedEntityDecl_Proxy( 
    ISAXDTDHandler __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchName,
    /* [in] */ int cchName,
    /* [in] */ const wchar_t __RPC_FAR *pwchPublicId,
    /* [in] */ int cchPublicId,
    /* [in] */ const wchar_t __RPC_FAR *pwchSystemId,
    /* [in] */ int cchSystemId,
    /* [in] */ const wchar_t __RPC_FAR *pwchNotationName,
    /* [in] */ int cchNotationName);


void __RPC_STUB ISAXDTDHandler_UnparsedEntityDecl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISAXDTDHandler_INTERFACE_DEFINED__ */


#ifndef __ISAXErrorHandler_INTERFACE_DEFINED__
#define __ISAXErrorHandler_INTERFACE_DEFINED__

/* interface ISAXErrorHandler */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_ISAXErrorHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a60511c4-ccf5-479e-98a3-dc8dc545b7d0")
    ISAXErrorHandler : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Error( 
            /* [in] */ ISAXLocator __RPC_FAR *pLocator,
            /* [in] */ IErrorInfo __RPC_FAR *pError) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FatalError( 
            /* [in] */ ISAXLocator __RPC_FAR *pLocator,
            /* [in] */ IErrorInfo __RPC_FAR *pError) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Warning( 
            /* [in] */ ISAXLocator __RPC_FAR *pLocator,
            /* [in] */ IErrorInfo __RPC_FAR *pError) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISAXErrorHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISAXErrorHandler __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISAXErrorHandler __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISAXErrorHandler __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Error )( 
            ISAXErrorHandler __RPC_FAR * This,
            /* [in] */ ISAXLocator __RPC_FAR *pLocator,
            /* [in] */ IErrorInfo __RPC_FAR *pError);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FatalError )( 
            ISAXErrorHandler __RPC_FAR * This,
            /* [in] */ ISAXLocator __RPC_FAR *pLocator,
            /* [in] */ IErrorInfo __RPC_FAR *pError);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Warning )( 
            ISAXErrorHandler __RPC_FAR * This,
            /* [in] */ ISAXLocator __RPC_FAR *pLocator,
            /* [in] */ IErrorInfo __RPC_FAR *pError);
        
        END_INTERFACE
    } ISAXErrorHandlerVtbl;

    interface ISAXErrorHandler
    {
        CONST_VTBL struct ISAXErrorHandlerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISAXErrorHandler_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISAXErrorHandler_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISAXErrorHandler_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISAXErrorHandler_Error(This,pLocator,pError)	\
    (This)->lpVtbl -> Error(This,pLocator,pError)

#define ISAXErrorHandler_FatalError(This,pLocator,pError)	\
    (This)->lpVtbl -> FatalError(This,pLocator,pError)

#define ISAXErrorHandler_Warning(This,pLocator,pError)	\
    (This)->lpVtbl -> Warning(This,pLocator,pError)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISAXErrorHandler_Error_Proxy( 
    ISAXErrorHandler __RPC_FAR * This,
    /* [in] */ ISAXLocator __RPC_FAR *pLocator,
    /* [in] */ IErrorInfo __RPC_FAR *pError);


void __RPC_STUB ISAXErrorHandler_Error_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXErrorHandler_FatalError_Proxy( 
    ISAXErrorHandler __RPC_FAR * This,
    /* [in] */ ISAXLocator __RPC_FAR *pLocator,
    /* [in] */ IErrorInfo __RPC_FAR *pError);


void __RPC_STUB ISAXErrorHandler_FatalError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXErrorHandler_Warning_Proxy( 
    ISAXErrorHandler __RPC_FAR * This,
    /* [in] */ ISAXLocator __RPC_FAR *pLocator,
    /* [in] */ IErrorInfo __RPC_FAR *pError);


void __RPC_STUB ISAXErrorHandler_Warning_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISAXErrorHandler_INTERFACE_DEFINED__ */


#ifndef __ISAXAttributes_INTERFACE_DEFINED__
#define __ISAXAttributes_INTERFACE_DEFINED__

/* interface ISAXAttributes */
/* [unique][helpstring][uuid][local][object] */ 


EXTERN_C const IID IID_ISAXAttributes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f078abe1-45d2-4832-91ea-4466ce2f25c9")
    ISAXAttributes : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetLength( 
            /* [retval][out] */ int __RPC_FAR *pnLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetURI( 
            /* [in] */ int nIndex,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchUri,
            /* [out] */ int __RPC_FAR *pcchUri) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLocalName( 
            /* [in] */ int nIndex,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchLocalName,
            /* [out] */ int __RPC_FAR *pcchLocalName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetQName( 
            /* [in] */ int nIndex,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchQName,
            /* [out] */ int __RPC_FAR *pcchQName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetName( 
            /* [in] */ int nIndex,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchUri,
            /* [out] */ int __RPC_FAR *pcchUri,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchLocalName,
            /* [out] */ int __RPC_FAR *pcchLocalName,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchQName,
            /* [out] */ int __RPC_FAR *pcchQName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIndexFromName( 
            /* [in] */ const wchar_t __RPC_FAR *pwchUri,
            /* [in] */ int cchUri,
            /* [in] */ const wchar_t __RPC_FAR *pwchLocalName,
            /* [in] */ int cchLocalName,
            /* [retval][out] */ int __RPC_FAR *pnIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIndexFromQName( 
            /* [in] */ const wchar_t __RPC_FAR *pwchQName,
            /* [in] */ int cchQName,
            /* [retval][out] */ int __RPC_FAR *pnIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetType( 
            /* [in] */ int nIndex,
            /* [retval][out] */ SAX_ATTRIBUTE_TYPE __RPC_FAR *peType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTypeFromName( 
            /* [in] */ const wchar_t __RPC_FAR *pwchUri,
            /* [in] */ int cchUri,
            /* [in] */ const wchar_t __RPC_FAR *pwchLocalName,
            /* [in] */ int cchLocalName,
            /* [retval][out] */ SAX_ATTRIBUTE_TYPE __RPC_FAR *peType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTypeFromQName( 
            /* [in] */ const wchar_t __RPC_FAR *pwchQName,
            /* [in] */ int cchQName,
            /* [retval][out] */ SAX_ATTRIBUTE_TYPE __RPC_FAR *peType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValue( 
            /* [in] */ int nIndex,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchValue,
            /* [out] */ int __RPC_FAR *pcchValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValueFromName( 
            /* [in] */ const wchar_t __RPC_FAR *pwchUri,
            /* [in] */ int cchUri,
            /* [in] */ const wchar_t __RPC_FAR *pwchLocalName,
            /* [in] */ int cchLocalName,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchValue,
            /* [out] */ int __RPC_FAR *pcchValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValueFromQName( 
            /* [in] */ const wchar_t __RPC_FAR *pwchQName,
            /* [in] */ int cchQName,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchValue,
            /* [out] */ int __RPC_FAR *pcchValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISAXAttributesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISAXAttributes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISAXAttributes __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISAXAttributes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLength )( 
            ISAXAttributes __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pnLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetURI )( 
            ISAXAttributes __RPC_FAR * This,
            /* [in] */ int nIndex,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchUri,
            /* [out] */ int __RPC_FAR *pcchUri);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLocalName )( 
            ISAXAttributes __RPC_FAR * This,
            /* [in] */ int nIndex,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchLocalName,
            /* [out] */ int __RPC_FAR *pcchLocalName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetQName )( 
            ISAXAttributes __RPC_FAR * This,
            /* [in] */ int nIndex,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchQName,
            /* [out] */ int __RPC_FAR *pcchQName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            ISAXAttributes __RPC_FAR * This,
            /* [in] */ int nIndex,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchUri,
            /* [out] */ int __RPC_FAR *pcchUri,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchLocalName,
            /* [out] */ int __RPC_FAR *pcchLocalName,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchQName,
            /* [out] */ int __RPC_FAR *pcchQName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIndexFromName )( 
            ISAXAttributes __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchUri,
            /* [in] */ int cchUri,
            /* [in] */ const wchar_t __RPC_FAR *pwchLocalName,
            /* [in] */ int cchLocalName,
            /* [retval][out] */ int __RPC_FAR *pnIndex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIndexFromQName )( 
            ISAXAttributes __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchQName,
            /* [in] */ int cchQName,
            /* [retval][out] */ int __RPC_FAR *pnIndex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetType )( 
            ISAXAttributes __RPC_FAR * This,
            /* [in] */ int nIndex,
            /* [retval][out] */ SAX_ATTRIBUTE_TYPE __RPC_FAR *peType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeFromName )( 
            ISAXAttributes __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchUri,
            /* [in] */ int cchUri,
            /* [in] */ const wchar_t __RPC_FAR *pwchLocalName,
            /* [in] */ int cchLocalName,
            /* [retval][out] */ SAX_ATTRIBUTE_TYPE __RPC_FAR *peType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeFromQName )( 
            ISAXAttributes __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchQName,
            /* [in] */ int cchQName,
            /* [retval][out] */ SAX_ATTRIBUTE_TYPE __RPC_FAR *peType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetValue )( 
            ISAXAttributes __RPC_FAR * This,
            /* [in] */ int nIndex,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchValue,
            /* [out] */ int __RPC_FAR *pcchValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetValueFromName )( 
            ISAXAttributes __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchUri,
            /* [in] */ int cchUri,
            /* [in] */ const wchar_t __RPC_FAR *pwchLocalName,
            /* [in] */ int cchLocalName,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchValue,
            /* [out] */ int __RPC_FAR *pcchValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetValueFromQName )( 
            ISAXAttributes __RPC_FAR * This,
            /* [in] */ const wchar_t __RPC_FAR *pwchQName,
            /* [in] */ int cchQName,
            /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchValue,
            /* [out] */ int __RPC_FAR *pcchValue);
        
        END_INTERFACE
    } ISAXAttributesVtbl;

    interface ISAXAttributes
    {
        CONST_VTBL struct ISAXAttributesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISAXAttributes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISAXAttributes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISAXAttributes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISAXAttributes_GetLength(This,pnLength)	\
    (This)->lpVtbl -> GetLength(This,pnLength)

#define ISAXAttributes_GetURI(This,nIndex,ppwchUri,pcchUri)	\
    (This)->lpVtbl -> GetURI(This,nIndex,ppwchUri,pcchUri)

#define ISAXAttributes_GetLocalName(This,nIndex,ppwchLocalName,pcchLocalName)	\
    (This)->lpVtbl -> GetLocalName(This,nIndex,ppwchLocalName,pcchLocalName)

#define ISAXAttributes_GetQName(This,nIndex,ppwchQName,pcchQName)	\
    (This)->lpVtbl -> GetQName(This,nIndex,ppwchQName,pcchQName)

#define ISAXAttributes_GetName(This,nIndex,ppwchUri,pcchUri,ppwchLocalName,pcchLocalName,ppwchQName,pcchQName)	\
    (This)->lpVtbl -> GetName(This,nIndex,ppwchUri,pcchUri,ppwchLocalName,pcchLocalName,ppwchQName,pcchQName)

#define ISAXAttributes_GetIndexFromName(This,pwchUri,cchUri,pwchLocalName,cchLocalName,pnIndex)	\
    (This)->lpVtbl -> GetIndexFromName(This,pwchUri,cchUri,pwchLocalName,cchLocalName,pnIndex)

#define ISAXAttributes_GetIndexFromQName(This,pwchQName,cchQName,pnIndex)	\
    (This)->lpVtbl -> GetIndexFromQName(This,pwchQName,cchQName,pnIndex)

#define ISAXAttributes_GetType(This,nIndex,peType)	\
    (This)->lpVtbl -> GetType(This,nIndex,peType)

#define ISAXAttributes_GetTypeFromName(This,pwchUri,cchUri,pwchLocalName,cchLocalName,peType)	\
    (This)->lpVtbl -> GetTypeFromName(This,pwchUri,cchUri,pwchLocalName,cchLocalName,peType)

#define ISAXAttributes_GetTypeFromQName(This,pwchQName,cchQName,peType)	\
    (This)->lpVtbl -> GetTypeFromQName(This,pwchQName,cchQName,peType)

#define ISAXAttributes_GetValue(This,nIndex,ppwchValue,pcchValue)	\
    (This)->lpVtbl -> GetValue(This,nIndex,ppwchValue,pcchValue)

#define ISAXAttributes_GetValueFromName(This,pwchUri,cchUri,pwchLocalName,cchLocalName,ppwchValue,pcchValue)	\
    (This)->lpVtbl -> GetValueFromName(This,pwchUri,cchUri,pwchLocalName,cchLocalName,ppwchValue,pcchValue)

#define ISAXAttributes_GetValueFromQName(This,pwchQName,cchQName,ppwchValue,pcchValue)	\
    (This)->lpVtbl -> GetValueFromQName(This,pwchQName,cchQName,ppwchValue,pcchValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISAXAttributes_GetLength_Proxy( 
    ISAXAttributes __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pnLength);


void __RPC_STUB ISAXAttributes_GetLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXAttributes_GetURI_Proxy( 
    ISAXAttributes __RPC_FAR * This,
    /* [in] */ int nIndex,
    /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchUri,
    /* [out] */ int __RPC_FAR *pcchUri);


void __RPC_STUB ISAXAttributes_GetURI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXAttributes_GetLocalName_Proxy( 
    ISAXAttributes __RPC_FAR * This,
    /* [in] */ int nIndex,
    /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchLocalName,
    /* [out] */ int __RPC_FAR *pcchLocalName);


void __RPC_STUB ISAXAttributes_GetLocalName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXAttributes_GetQName_Proxy( 
    ISAXAttributes __RPC_FAR * This,
    /* [in] */ int nIndex,
    /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchQName,
    /* [out] */ int __RPC_FAR *pcchQName);


void __RPC_STUB ISAXAttributes_GetQName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXAttributes_GetName_Proxy( 
    ISAXAttributes __RPC_FAR * This,
    /* [in] */ int nIndex,
    /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchUri,
    /* [out] */ int __RPC_FAR *pcchUri,
    /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchLocalName,
    /* [out] */ int __RPC_FAR *pcchLocalName,
    /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchQName,
    /* [out] */ int __RPC_FAR *pcchQName);


void __RPC_STUB ISAXAttributes_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXAttributes_GetIndexFromName_Proxy( 
    ISAXAttributes __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchUri,
    /* [in] */ int cchUri,
    /* [in] */ const wchar_t __RPC_FAR *pwchLocalName,
    /* [in] */ int cchLocalName,
    /* [retval][out] */ int __RPC_FAR *pnIndex);


void __RPC_STUB ISAXAttributes_GetIndexFromName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXAttributes_GetIndexFromQName_Proxy( 
    ISAXAttributes __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchQName,
    /* [in] */ int cchQName,
    /* [retval][out] */ int __RPC_FAR *pnIndex);


void __RPC_STUB ISAXAttributes_GetIndexFromQName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXAttributes_GetType_Proxy( 
    ISAXAttributes __RPC_FAR * This,
    /* [in] */ int nIndex,
    /* [retval][out] */ SAX_ATTRIBUTE_TYPE __RPC_FAR *peType);


void __RPC_STUB ISAXAttributes_GetType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXAttributes_GetTypeFromName_Proxy( 
    ISAXAttributes __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchUri,
    /* [in] */ int cchUri,
    /* [in] */ const wchar_t __RPC_FAR *pwchLocalName,
    /* [in] */ int cchLocalName,
    /* [retval][out] */ SAX_ATTRIBUTE_TYPE __RPC_FAR *peType);


void __RPC_STUB ISAXAttributes_GetTypeFromName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXAttributes_GetTypeFromQName_Proxy( 
    ISAXAttributes __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchQName,
    /* [in] */ int cchQName,
    /* [retval][out] */ SAX_ATTRIBUTE_TYPE __RPC_FAR *peType);


void __RPC_STUB ISAXAttributes_GetTypeFromQName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXAttributes_GetValue_Proxy( 
    ISAXAttributes __RPC_FAR * This,
    /* [in] */ int nIndex,
    /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchValue,
    /* [out] */ int __RPC_FAR *pcchValue);


void __RPC_STUB ISAXAttributes_GetValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXAttributes_GetValueFromName_Proxy( 
    ISAXAttributes __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchUri,
    /* [in] */ int cchUri,
    /* [in] */ const wchar_t __RPC_FAR *pwchLocalName,
    /* [in] */ int cchLocalName,
    /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchValue,
    /* [out] */ int __RPC_FAR *pcchValue);


void __RPC_STUB ISAXAttributes_GetValueFromName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISAXAttributes_GetValueFromQName_Proxy( 
    ISAXAttributes __RPC_FAR * This,
    /* [in] */ const wchar_t __RPC_FAR *pwchQName,
    /* [in] */ int cchQName,
    /* [out] */ const wchar_t __RPC_FAR *__RPC_FAR *ppwchValue,
    /* [out] */ int __RPC_FAR *pcchValue);


void __RPC_STUB ISAXAttributes_GetValueFromQName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISAXAttributes_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_SAXXMLReader;

#ifdef __cplusplus

class DECLSPEC_UUID("079aa557-4a18-424a-8eee-e39f0a8d41b9")
SAXXMLReader;
#endif

EXTERN_C const CLSID CLSID_SAXXMLReader30;

#ifdef __cplusplus

class DECLSPEC_UUID("3124c396-fb13-4836-a6ad-1317f1713688")
SAXXMLReader30;
#endif
#endif /* __XMLSAX_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif



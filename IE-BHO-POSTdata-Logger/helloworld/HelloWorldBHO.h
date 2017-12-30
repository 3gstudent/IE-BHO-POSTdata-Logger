// HelloWorldBHO.h : CHelloWorldBHO 的声明

#pragma once
#include "resource.h"       // 主符号
#include <shlguid.h>  
#include <exdispid.h>


#include "helloworld_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;


// CHelloWorldBHO

class ATL_NO_VTABLE CHelloWorldBHO :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CHelloWorldBHO, &CLSID_HelloWorldBHO>,
	public IObjectWithSiteImpl<CHelloWorldBHO>,
	public IDispatchImpl<IHelloWorldBHO, &IID_IHelloWorldBHO, &LIBID_helloworldLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispEventImpl<1, CHelloWorldBHO, &DIID_DWebBrowserEvents2, &LIBID_SHDocVw, 1, 1>  
{
public:
	CHelloWorldBHO()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_HELLOWORLDBHO)

DECLARE_NOT_AGGREGATABLE(CHelloWorldBHO)

BEGIN_COM_MAP(CHelloWorldBHO)
	COM_INTERFACE_ENTRY(IHelloWorldBHO)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IObjectWithSite)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(SetSite)(IUnknown *pUnkSite); 
	BEGIN_SINK_MAP(CHelloWorldBHO)  
    SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE, OnDocumentComplete)  
	END_SINK_MAP()  
  
    // DWebBrowserEvents2  
    void STDMETHODCALLTYPE OnDocumentComplete(IDispatch *pDisp, VARIANT *pvarURL);  
	STDMETHODIMP Invoke(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pvarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);
 
	CComQIPtr<IWebBrowser2, &IID_IWebBrowser2> m_spWebBrowser2;

private:  
  
    CComPtr<IWebBrowser2>  m_spWebBrowser;  
    BOOL m_fAdvised; 

};

OBJECT_ENTRY_AUTO(__uuidof(HelloWorldBHO), CHelloWorldBHO)

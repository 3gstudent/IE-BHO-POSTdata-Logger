// HelloWorldBHO.cpp : CHelloWorldBHO µÄÊµÏÖ

#include "stdafx.h"
#include "HelloWorldBHO.h"
#include <assert.h>
#include <stdio.h>
// CHelloWorldBHO

STDMETHODIMP CHelloWorldBHO::SetSite(IUnknown* pUnkSite)  
{  
    m_spWebBrowser2 = pUnkSite;
	if (pUnkSite != NULL)  
    {  
        // Cache the pointer to IWebBrowser2.  
        HRESULT hr = pUnkSite->QueryInterface(IID_IWebBrowser2, (void **)&m_spWebBrowser);  
        if (SUCCEEDED(hr))  
        {  
            // Register to sink events from DWebBrowserEvents2.  
            hr = DispEventAdvise(m_spWebBrowser);  
            if (SUCCEEDED(hr))  
            {  
                m_fAdvised = TRUE;  
            }  
        }  
    }  
    else  
    {  
        // Unregister event sink.  
        if (m_fAdvised)  
        {  
            DispEventUnadvise(m_spWebBrowser);  
            m_fAdvised = FALSE;  
        }  
  
        // Release cached pointers and other resources here.  
        m_spWebBrowser.Release();  
    }  
  
    // Call base class implementation.  
    return IObjectWithSiteImpl<CHelloWorldBHO>::SetSite(pUnkSite);  
}  
  
void STDMETHODCALLTYPE CHelloWorldBHO::OnDocumentComplete(IDispatch *pDisp, VARIANT *pvarURL)  
{  
    BSTR url = pvarURL->bstrVal;
	CComBSTR u(url);
	
	
	// Retrieve the top-level window from the site.  
    HWND hwnd;  
    HRESULT hr = m_spWebBrowser->get_HWND((LONG_PTR*)&hwnd);  
    if (SUCCEEDED(hr))  
    {  
 //       MessageBox(0, u, L"the url is", MB_OK);
    }  
} 

void Log(char *Buff) {
	char TempPath[1024];
	GetTempPathA(1024,TempPath); 
	sprintf_s(TempPath,1024,"%slog.txt",TempPath);
	FILE *fp;
    fopen_s(&fp,TempPath, "a+");
    fwrite(Buff, strlen(Buff), 1, fp);
    fclose(fp);
}
//This function quotes from: https://github.com/liigo/bho
STDMETHODIMP CHelloWorldBHO::Invoke(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pvarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
	switch(dispidMember)
	{
	case DISPID_BEFORENAVIGATE2:
		{
			assert(pDispParams->cArgs == 7);

			//Arg0: Cancel
			VARIANTARG argCancel = pDispParams->rgvarg[0];
			assert(argCancel.vt == (VT_BYREF|VT_BOOL));

			//Arg1: Headers
			VARIANTARG argHeaders = pDispParams->rgvarg[1];
			assert(argHeaders.vt == (VT_BYREF|VT_VARIANT));
			assert(argHeaders.pvarVal->vt == VT_BSTR);
			BSTR bstrHeaders = argHeaders.pvarVal->bstrVal;
//			MessageBoxW(0, bstrHeaders, L"headers", MB_OK);

			//Arg2: PostData
			VARIANTARG argPostData = pDispParams->rgvarg[2];
			assert(argPostData.vt == (VT_BYREF|VT_VARIANT));
			assert(argPostData.pvarVal->vt == (VT_BYREF|VT_VARIANT));
			if(argPostData.pvarVal->pvarVal->vt != VT_EMPTY)
			{
				assert(argPostData.pvarVal->pvarVal->vt == (VT_ARRAY|VT_UI1));
				SAFEARRAY* pSafeArray = argPostData.pvarVal->pvarVal->parray;
				assert(pSafeArray);
				assert(pSafeArray->cDims == 1 && pSafeArray->cbElements == 1); //array of VT_UI1
				unsigned int nPostDataSize = pSafeArray->rgsabound[0].cElements * pSafeArray->cbElements; //in bytes
				void* pPostData = pSafeArray->pvData;
//				MessageBoxA(0, (char*)pPostData, "post data string", MB_OK);
				Log((char*)pPostData);
			}

			//Arg3: TargetFrameName
			VARIANTARG argTargetFrameName = pDispParams->rgvarg[3];
			assert(argTargetFrameName.vt == (VT_BYREF|VT_VARIANT));
			assert(argTargetFrameName.pvarVal->vt == VT_BSTR);
			BSTR bstrTargetFrameName = argTargetFrameName.pvarVal->bstrVal;
//			MessageBoxW(0, bstrTargetFrameName, L"TargetFrameName", MB_OK);

			//Arg4: Flags
			VARIANTARG argFlags = pDispParams->rgvarg[4];
			assert(argFlags.vt == (VT_BYREF|VT_VARIANT));
			assert(argFlags.pvarVal->vt == VT_I4);
			LONG lFlags = argFlags.pvarVal->lVal;

			//Arg5: Url
			VARIANTARG argUrl = pDispParams->rgvarg[5];
			assert(argUrl.vt == (VT_BYREF|VT_VARIANT));
			assert(argUrl.pvarVal->vt == VT_BSTR);
			BSTR bstrUrl = argUrl.pvarVal->bstrVal;
//			MessageBoxW(0, bstrUrl, L"URL", MB_OK);			
			char Temp[1024] = {0};
			sprintf_s(Temp,1024,"%ws\n",bstrUrl);
			Log(Temp);

			//Arg6: WebBrowser
			VARIANTARG argWebBrowser = pDispParams->rgvarg[6];
			assert(argWebBrowser.vt == VT_DISPATCH);
			IDispatch* pDispWebBrowser = argWebBrowser.pdispVal;

			return S_OK;
		}

	case DISPID_NAVIGATECOMPLETE2: 
		{
			return S_OK;
		}

	case DISPID_DOCUMENTCOMPLETE:
		{
			IDispatch* pDocDisp = NULL;
			if( m_spWebBrowser2->get_Document(&pDocDisp) == S_OK)
			{
				IHTMLDocument2* pDoc = NULL;
				if(pDocDisp->QueryInterface(IID_IHTMLDocument2, (void**)&pDoc) == S_OK)
				{
					BSTR title;
					pDoc->get_title(&title);
//					MessageBox(0, title, NULL, MB_OK);
				}
			}
			return S_OK;
		}

	}

	return S_FALSE;
}

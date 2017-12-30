// dllmain.h : 模块类的声明。

class ChelloworldModule : public ATL::CAtlDllModuleT< ChelloworldModule >
{
public :
	DECLARE_LIBID(LIBID_helloworldLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_HELLOWORLD, "{F600A23F-126F-4A5A-A28B-9D38013C2570}")
};

extern class ChelloworldModule _AtlModule;

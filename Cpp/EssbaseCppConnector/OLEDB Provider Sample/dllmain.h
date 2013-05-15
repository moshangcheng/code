// dllmain.h : Declaration of module class.

class COLEDBProviderSampleModule : public ATL::CAtlDllModuleT< COLEDBProviderSampleModule >
{
public :
	DECLARE_LIBID(LIBID_OLEDBProviderSampleLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_OLEDBPROVIDERSAMPLE, "{4D5917FE-6EF6-4A33-9947-85890EC81DBC}")
};

extern class COLEDBProviderSampleModule _AtlModule;

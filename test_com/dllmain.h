// dllmain.h : 모듈 클래스의 선언입니다.

class CtestcomModule : public ATL::CAtlDllModuleT< CtestcomModule >
{
public :
	DECLARE_LIBID(LIBID_testcomLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TESTCOM, "{834a4ffd-2cd7-4138-b8a8-6f16e49f9972}")
};

extern class CtestcomModule _AtlModule;

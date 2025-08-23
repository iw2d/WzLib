#pragma once
#include <windows.h>
#include "zcomdef.h"

inline FARPROC _g_apfnPCOMAPIs[5] = {};
inline HMODULE _g_hPCOMModule = nullptr;
inline LONG _g_nPCOMModuleRef = 0;

inline BOOL LoadProc(HMODULE hModule) {
    _g_apfnPCOMAPIs[0] = GetProcAddress(hModule, "PcCreateObject");
    _g_apfnPCOMAPIs[1] = GetProcAddress(hModule, "PcFreeUnusedLibraries");
    _g_apfnPCOMAPIs[2] = GetProcAddress(hModule, "PcSerializeObject");
    _g_apfnPCOMAPIs[3] = GetProcAddress(hModule, "PcSerializeString");
    _g_apfnPCOMAPIs[4] = GetProcAddress(hModule, "PcRootNameSpace");
    for (size_t i = 0; i < 5; ++i) {
        if (!_g_apfnPCOMAPIs[i]) {
            return FALSE;
        }
    }
    return TRUE;
}

inline HRESULT PcInitialize(const wchar_t* sPCOMModule) {
    HMODULE hModule = LoadLibraryW(sPCOMModule ? sPCOMModule : L"PCOM.DLL");
    if (!hModule) {
        return CO_E_DLLNOTFOUND;
    }
    if (!LoadProc(hModule)) {
        return CO_E_ERRORINDLL;
    }
    FARPROC PcInitModule = GetProcAddress(hModule, "PcInitModule");
    if (!PcInitModule) {
        FreeLibrary(hModule);
        return CO_E_ERRORINDLL;
    }
    HRESULT hr = PcInitModule();
    if (FAILED(hr)) {
        FreeLibrary(hModule);
        return hr;
    }
    InterlockedIncrement(&_g_nPCOMModuleRef);
    _g_hPCOMModule = hModule;
    return S_OK;
}

inline void PcUninitialize() {
    if (!InterlockedDecrement(&_g_nPCOMModuleRef)) {
        FARPROC PcTermModule = GetProcAddress(_g_hPCOMModule, "PcTermModule");
        if (PcTermModule) {
            PcTermModule();
        }
        FreeLibrary(_g_hPCOMModule);
        _g_hPCOMModule = nullptr;
    }
}

template <typename T>
void PcCreateObject(const wchar_t* sUOL, T& pObj, IUnknown* pUnkOuter) {
    pObj = nullptr;
    if (!_g_apfnPCOMAPIs[0]) {
        _com_issue_error(CO_E_NOTINITIALIZED);
    }
    _com_util::CheckError(reinterpret_cast<HRESULT(__cdecl*)(const wchar_t*, const GUID*, T&, void*)>(_g_apfnPCOMAPIs[0])(sUOL, &__uuidof(T), pObj, pUnkOuter));
}

inline void PcSetRootNameSpace(IUnknown* pNameSpace) {
    if (!_g_apfnPCOMAPIs[4]) {
        _com_issue_error(CO_E_NOTINITIALIZED);
    }
    _com_util::CheckError(reinterpret_cast<HRESULT(__cdecl*)(IUnknown**, int)>(_g_apfnPCOMAPIs[4])(&pNameSpace, 1));
}
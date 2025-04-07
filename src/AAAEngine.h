#pragma once

#ifdef _WIN32
    #ifdef BUILDING_DLL
        #define EXPORT __declspec(dllexport)
    #else
        #define EXPORT __declspec(dllimport)
    #endif
#else
    #define EXPORT
#endif

#define REGISTER_SCRIPT(CLASSNAME)                   \
extern "C" EXPORT Script* CreateScript() {           \
    return new CLASSNAME();                          \
}

class EXPORT Script
{
public:
    virtual ~Script() = default;
    virtual void Start(){}
    virtual void Update(){}
};

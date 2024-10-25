#ifndef SHAREDLIB_H
#define SHAREDLIB_H

#include "SharedLib_global.h"

class SHAREDLIB_EXPORT CSharedLib
{
public:
    CSharedLib();

    template<class T>
    static T Add(T _X, T _Y)
    {
        return _X + _Y;
    }
};

#endif // SHAREDLIB_H

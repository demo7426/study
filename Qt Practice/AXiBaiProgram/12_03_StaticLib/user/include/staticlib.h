#ifndef STATICLIB_H
#define STATICLIB_H

class CStaticlib
{
public:
    CStaticlib();

    template<class T>
    static T Add(T _X, T _Y)
    {
        return _X + _Y;
    }
};

#endif // STATICLIB_H

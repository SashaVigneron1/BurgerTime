#pragma once
#include <cassert>


// I came to this idea after discussing it with Gillian Assi & Senne De Vocht
template <typename T>
class SingleInstance
{
public:

    virtual ~SingleInstance() { isInstantiated = false; };

    SingleInstance(const SingleInstance& other) = delete;
    SingleInstance(SingleInstance&& other) = delete;
    SingleInstance& operator=(const SingleInstance& other) = delete;
    SingleInstance& operator=(SingleInstance&& other) = delete;

protected:
    SingleInstance()
    {
        assert(!isInstantiated && "Error: Trying to create a second instance of a SingleInstance class");
        isInstantiated = true;
    };

private:
    static bool isInstantiated;
};

template <typename T>
bool SingleInstance<T>::isInstantiated = false;
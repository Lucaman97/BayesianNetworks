#ifndef BAYESIANNETWORKS_COWBASE_H
#define BAYESIANNETWORKS_COWBASE_H
#pragma once

template<class T>
class COWBase
{
public:

    // function to get the internal raw ptr
    T* raw()
    {
        return m_ptr.get();
    }

    //function to get the value of the shared_ptr
    T value() const {return *m_ptr;}


    // returns count of the shared_ptr instance
    long use_count() const
    {
        return m_ptr.use_count();
    }

protected:
    std::shared_ptr<T> m_ptr;
};

#endif //BAYESIANNETWORKS_COWBASE_H

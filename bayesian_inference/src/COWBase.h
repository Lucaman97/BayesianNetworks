//
// Created by lmann on 21/12/2021.
//

#ifndef BAYESIANNETWORKS_COWBASE_H
#define BAYESIANNETWORKS_COWBASE_H
#pragma once

template<typename T>
class COWBase
{
public:
    // call this function in derived constructor
    void construct()
    {
        m_ptr = std::make_shared<T>();
    }
    // call this function in derived's setter before other code
    void clone_if_needed()
    {
        if (m_ptr.use_count() > 1)
        {
            std::shared_ptr<T> old = m_ptr;
            construct();
            *m_ptr = *old; // copy the old contents to new ptr.
        }
    }
    // function to get the internal raw ptr
    const T* ptr() const
    {
        return m_ptr.get();
    }
    // function to get the internal raw ptr
    std::shared_ptr<T> ptr()
    {
        return m_ptr;
    }
    // returns count of the shared_ptr instance
    long use_count() const
    {
        return m_ptr.use_count();
    }
private:
    std::shared_ptr<T> m_ptr;
};

#endif //BAYESIANNETWORKS_COWBASE_H

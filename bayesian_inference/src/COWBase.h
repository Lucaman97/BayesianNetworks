//
// Created by lmann on 21/12/2021.
//

#ifndef BAYESIANNETWORKS_COWBASE_H
#define BAYESIANNETWORKS_COWBASE_H
#pragma once

template<class T>
class COWBase
{
public:
    void copy_ptr(std::shared_ptr<T> other) {
        probabilities = other;
    }
    // function to get the internal raw ptr
    const T* ptr() const
    {
        return probabilities.get();
    }


    // returns count of the shared_ptr instance
    long use_count() const
    {
        return probabilities.use_count();
    }
protected:
    std::shared_ptr<T> probabilities;
};

#endif //BAYESIANNETWORKS_COWBASE_H

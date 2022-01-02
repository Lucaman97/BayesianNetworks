#ifndef BAYESIANNETWORKS_COWBASE_H
#define BAYESIANNETWORKS_COWBASE_H
#pragma once

template<class T>
class COWBase
{
public:

    // function to get the internal raw ptr
    std::shared_ptr<T> prob()
    {
        return probabilities;
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

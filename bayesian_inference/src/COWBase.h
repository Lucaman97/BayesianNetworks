#pragma once

template<typename T>
class COWBase
{
protected:
	// call this function in derived constructor
	void construct()
	{
        ptr_probs = std::make_shared<T>();
	}
	// call this function in derived's setter before other code
	void clone_if_needed()
	{
        //se
		if (ptr_probs.use_count() > 1)
		{
			std::shared_ptr<T> old = ptr_probs;
			construct();
			*ptr_probs = *old; // copy the old contents to new ptr.
		}
	}
	// function to get the internal raw ptr
	const T* ptr() const
	{
		return ptr_probs.get();
	}
	// function to get the internal raw ptr
	T* ptr()
	{
		return ptr_probs.get();
	}
	// returns count of the shared_ptr instance
	long use_count() const
	{
		return ptr_probs.use_count();
	}
private:
	std::shared_ptr<T> ptr_probs;
};

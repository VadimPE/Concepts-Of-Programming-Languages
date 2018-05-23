#pragma once
#include "Сontainer.h"

template <class T>
class Future {
public:
    Future(std::mutex& mutex, std::condition_variable& cv, Container<T>& container)
      : mutex_(mutex),
        set_value_cv_(cv),
        container_(container) {
    }
    
    T Get() {
        std::unique_lock<std::mutex> lock(this->mutex_);
        while(!container_.IsSet()) {
            set_value_cv_.wait(lock);
        }
        if (container_.IsException()) {
            throw container_.GetException();
        }
        return this->Get();
    }
    
    bool TryGet(T& value) {
        std::unique_lock<std::mutex> lock(this->mutex_);
        if (container_.IsSet()) {
            if (container_.IsException()) {
                throw container_.GetException();
            }
            value = container_.Get();
            return true;
        }
        return false;
    }
    
private:
    std::mutex& mutex_;
    std::condition_variable& set_value_cv_;
    Container<T>& container_;
};

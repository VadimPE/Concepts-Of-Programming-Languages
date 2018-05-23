#pragma once

template <class T>
class Promise {
public:
    
    Promise(std::mutex& mutex, std::condition_variable& cv, Container<T>& container)
      : mutex_(mutex),
        set_value_cv_(cv),
        container_(container) {
    }
    
    void SetValue(T value) {
        std::unique_lock<std::mutex> lock(this->mutex_);
        if (this->container_.IsSet()) {
            throw "Value has already been";
        }
        this->container_.Set(value);
        this->set_value_cv_.notify_one();
    }
    
    void SetException(std::exception exception) {
        std::unique_lock<std::mutex> lock(this->mutex_);
        if (this->container_.IsException()) {
            throw "Exception has already been";
        }
        this->container_->Catch(exception);
        this->conditionVariable->notify_one( );
    }
    
private:
    std::mutex& mutex_;
    std::condition_variable& set_value_cv_;
    Container<T>& container_;
};

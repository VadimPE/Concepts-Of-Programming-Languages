#pragma once

template<class T>
class Container {
public:
    Container()
      : finished_(false),
        exception_catched_(false) {
    }
    
    void Set(T value) {
        finished_ = true;
        value_ = value;
    }
    
    T Get() {
        return this->value_;
    }
    
    bool IsException() {
        return this->exception_catched_;
    }
    
    bool IsSet() {
        return this->finished_;
    }
    
    bool Catch(std::exception exception) {
        this->finished_ = true;
        this->exception_catched_ = true;
        this->exception_ = exception;
    }
    
    std::exception GetException() {
        return this->exception_;
    }
private:
    bool finished_;
    bool exception_catched_;
    T value_;
    std::exception exception_;
};

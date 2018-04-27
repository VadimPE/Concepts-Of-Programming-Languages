#pragma once

#include <iostream>
#include <vector>
#include <setjmp.h>

class BaseObj;
class MyException;

std::vector<jmp_buf*> jmps;
std::vector<BaseObj*> objs;
std::vector<int> offsets;
MyException* exception;
bool catch_block = false;
int jmp_value;
jmp_buf* jmpb;

class BaseObj {
public:
    BaseObj() {
        objs.push_back(this);
    }
    
    virtual ~BaseObj() {
        std::cout << "DEL OBJ " << objs.size() << std::endl;
        objs.pop_back();
    }
};

class MyException {
public:
    MyException() {};
    virtual ~MyException() {};
};

#define TRY(CODE)                                                                       \
    offsets.push_back(objs.size());                                                     \
    jmpb = new jmp_buf[1];                                                              \
    jmp_value = setjmp(*jmpb);                                                          \
    if (jmp_value == 0) {                                                               \
        jmps.push_back(jmpb);                                                           \
        CODE                                                                            \
    }\
    delete[] jmps.back();                                                               \
    jmps.pop_back();\

#define CATCH(TYPE, ERROR, CODE)                                                        \
    TYPE* ERROR = dynamic_cast<TYPE*>(exception);                                       \
    if (jmp_value != 0 && ERROR != nullptr) {                                           \
        CODE                                                                            \
        delete exception;\
    }                                                                                   \
    if (ERROR == nullptr) {                                                             \
    }                                                                                   \

#define THROW(EXCEPTION)                                                                \
    if (EXCEPTION == nullptr || jmps.size() == 0) {                                     \
        exit(1);                                                                        \
    }                                                                                   \
    for (int i = objs.size() - 1; i >= offsets.back(); --i) {                           \
        objs[i]->~BaseObj();                                                            \
    }                                                                                   \
    exception = EXCEPTION;                                                              \
    longjmp(*(jmps.back()), 1);                                                         \

#define END_CATCH \
if (exception != nullptr) { \
    THROW(exception); \
} \

#pragma once
#include <unordered_map>
#include <vector>

#define VIRTUAL_CLASS(class_name) struct class_name {                                   \
    std::unordered_map<std::string, std::function<void(void*)>> v_table_;               \

#define BASE_CONSTRUCTOR(class_name, CODE) class_name() { CODE };                       \

#define ADD_FOO(class_name, foo_name)                                                   \
    this->v_table_.emplace(#foo_name, std::function<void(void*)>(this->foo_name));      \

#define START_DECLARE_METHOD(class_name, foo_name)                                      \
    static void foo_name(void* obj_ptr) {                                               \
        class_name* this_ = (class_name*)obj_ptr;                                       \
        std::cout << #class_name << "::" << #foo_name << " ";                           \

#define END_DECLARE_METHOD std::cout << std::endl; };

#define END(class_name) };                                                              \

#define VIRTUAL_CALL(obj_ptr, foo_name)                                                 \
(obj_ptr->v_table_[#foo_name])(obj_ptr);                                                \

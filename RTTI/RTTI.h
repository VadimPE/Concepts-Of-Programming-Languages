#pragma once

#include <iostream>
#include <unordered_set>
#include <unordered_map>

#define CLASSES std::unordered_map<std::string, std::set<std::string>> classes;

size_t GetHash(std::string class_name) {
    std::hash<std::string> hash_foo;
    return hash_foo(class_name);
}

template <typename to_class_ptr, typename from_class_ptr>
to_class_ptr CastForced(from_class_ptr obj_ptr) {
    from_class_ptr* new_obj_ptr = reinterpret_cast<from_class_ptr>(obj_ptr);
    new_obj_ptr->name = obj_ptr->name;
    return new_obj_ptr;
}

struct type_info {
    type_info(std::string name): name_(name), hash_(GetHash(name)) {};
    
    std::string name_;
    size_t hash_;
};

#define TYPEID(obj_ptr) obj_ptr->type_info

#define BASE_CLASS(class_name) class class_name { \
  public: \
    class_name() {\
        classes.emplace(#class_name, class_name::parents_); \
    }; \
std::string GetInfo() { \
    return class_name::type_info_; \
} \
  private: \
    static std::unordered_set<std::string> parents_; \
    static type_info type_info; \
    static std::string name_; \
}; \

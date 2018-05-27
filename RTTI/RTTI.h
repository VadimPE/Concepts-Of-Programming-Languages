#pragma once

#include <iostream>
#include <unordered_set>
#include <unordered_map>

std::unordered_map<std::string, std::unordered_set<std::string>> classes;

size_t GetHash(std::string class_name) {
    std::hash<std::string> hash_foo;
    return hash_foo(class_name);
};

template <typename from_class_ptr, typename to_class_ptr>
to_class_ptr Cast(from_class_ptr obj_ptr) {
    to_class_ptr new_obj_ptr = reinterpret_cast<from_class_ptr>(obj_ptr);
    new_obj_ptr->name_ = obj_ptr->name_;
    return new_obj_ptr;
};

std::unordered_set<std::string> Split(std::string str, char chr) {
    std::unordered_set<std::string> ans;
    std::string new_class_name = "";
    for (auto i = 0; i < str.length(); ++i) {
        if (str[i] == ' ') {
            new_class_name = "";
        } else if (str[i] == chr) {
            ans.insert(new_class_name);
            new_class_name = "";
        } else {
            new_class_name += str[i];
        }
    }
    ans.insert(new_class_name);
    return ans;
};

struct type_info {
    type_info(std::string name): name_(name), hash_(GetHash(name)) {};
    
    std::string name_;
    size_t hash_;
};

bool IsParent(std::string from_class, std::string to_class) {
    if (from_class == to_class) {
        return true;
    }
    for (auto i = classes[from_class].begin(); i != classes[from_class].end(); ++i) {
        if (IsParent(*i, to_class)) {
            return true;
        }
    }
    return false;
};

#define TYPEID(obj_ptr) obj_ptr->type_info

#define BASE_CLASS(class_name) class class_name { \
  public: \
    class_name(): name_(#class_name) {\
    }; \
    static void DECLARE() { \
        classes.emplace(#class_name, class_name::parents_); \
    } \
type_info GetInfo() { \
    return class_name::type_info_; \
} \
    std::string name_; \
  private: \
    static std::unordered_set<std::string> parents_; \
    static type_info type_info_; \
  public: \

#define DERIVED_CLASS(class_name, ...) class class_name: __VA_ARGS__ { \
  public: \
    class_name(): name_(#class_name) {\
    }; \
    static void DECLARE() { \
        class_name::parents_ = Split(#__VA_ARGS__, ','); \
        classes.emplace(#class_name, class_name::parents_); \
    } \
    type_info GetInfo() { \
        return class_name::type_info_; \
    } \
    std::string name_; \
  private: \
    static std::unordered_set<std::string> parents_; \
    static type_info type_info_; \
  public: \

#define END_CLASS(class_name) };\
std::unordered_set<std::string> class_name::parents_; \
type_info class_name::type_info_ = type_info(#class_name); \

#define DYNAMIC_CAST(from_class_ptr, to_class_ptr, obj_ptr) (IsParent(#from_class_ptr, #to_class_ptr)) ? (Cast<from_class_ptr*, to_class_ptr*>(obj_ptr)) : nullptr


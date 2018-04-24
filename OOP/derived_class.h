#pragma once
#include <unordered_map>

#define VIRTUAL_CLASS_DERIVED(base_class_name, derived_class_name) struct derived_class_name {          \
    std::unordered_map<std::string, std::function<void(derived_class_name*)>> v_table_;                 \

#define DERIVED_CONSTRUCTOR(base_class_name, derived_class_name, CODE) derived_class_name() {           \
    CODE                                                                                                \
    base_class_name base_class;                                                                         \
    for (auto i = base_class.v_table_.begin(); i != base_class.v_table_.end(); ++i) {                   \
        if (this->v_table_.count(i->first) == 0) {                                                      \
            this->v_table_.emplace(i->first, std::function<void(derived_class_name*)>(i->second));      \
        }                                                                                               \
    }                                                                                                   \
};                                                                                                      \

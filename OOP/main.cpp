#include <iostream>
#include "base_class.h"
#include "derived_class.h"

// базовый класс
VIRTUAL_CLASS(Base)

int a = 5;

// методы
START_DECLARE_METHOD(Base, Both)
    std::cout << this_->a;
END_DECLARE_METHOD

START_DECLARE_METHOD(Base, OnlyBase)
END_DECLARE_METHOD

BASE_CONSTRUCTOR(Base,
            ADD_FOO(Base, Both)
            ADD_FOO(Base, OnlyBase)
            )
END(Base)

// класс-наследник
VIRTUAL_CLASS_DERIVED(Base, Derived)

int b = 10;

// методы
START_DECLARE_METHOD(Derived, Both)
    std::cout << this_->b;
END_DECLARE_METHOD

START_DECLARE_METHOD(Derived, OnlyDerived)
END_DECLARE_METHOD

DERIVED_CONSTRUCTOR(Base, Derived,
                    ADD_FOO(Derived, Both)
                    ADD_FOO(Derived, OnlyDerived)
                    )
END(Derived)

int main() {
    Base base;
    Derived derived;
    Base* reallyDerived = reinterpret_cast<Base*>(&derived);
    
    VIRTUAL_CALL((&base), Both);
    VIRTUAL_CALL(reallyDerived, Both);
    VIRTUAL_CALL(reallyDerived, OnlyBase);
    VIRTUAL_CALL(reallyDerived, OnlyDerived);
    return 0;
}

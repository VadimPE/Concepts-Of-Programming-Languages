#include "RTTI.h"

BASE_CLASS(A)
int a = 5;
void foo() {
    std::cout << a;
};
END_CLASS(A)

BASE_CLASS(C)
int b = 10;
void foo1() {
    std::cout << b;
};
END_CLASS(C)

DERIVED_CLASS(B, public A, public C)
END_CLASS(B)

int main() {
    B::DECLARE();
    B a;
    std::cout << a.b;
    return 0;
}

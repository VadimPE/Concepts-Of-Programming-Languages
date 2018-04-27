//
//  main.cpp
//  MyException
//
//  Created by Вадик on 04.04.2018.
//  Copyright © 2018 Вадик. All rights reserved.
//

#include <iostream>
#include "Exception.h"

class ObjNum: public BaseObj {
public:
    int a = 6;
};

class ExceptionStr: public MyException {
public:
    ExceptionStr(std::string txt) : text(txt) {}
    std::string text;
};

class ExceptionNum: public MyException {
public:
    ExceptionNum(int num)
    : num(num) {}
    int num;
};

// Тест на поимку простого исключения
void TEST1() {
    TRY(
        std::cout << "TRY" << std::endl;
        THROW(new ExceptionStr("STR EXCEPTION"));
        std::cout << "END TRY";
        )
    CATCH(ExceptionStr, excep, std::cout << excep->text << std::endl;)
}

// Пролет исключений наверх
void TEST2() {
    TRY(
        std::cout << "TRY1" << std::endl;
        TRY(
            std::cout << "TRY2" << std::endl;
            THROW(new ExceptionStr("STR EXCEPTION"));
        )
        CATCH(ExceptionNum, excep1, std::cout << excep1->num << std::endl;)
    )
    CATCH(ExceptionStr, excep, std::cout << excep->text << std::endl;)
}

// Удаление объектов при пролете исключения
void TEST3() {
    TRY(
        std::cout << "TRY1" << std::endl;
        ObjNum a;
        ObjNum b;
        TRY(
            ObjNum c;
            ObjNum d;
            std::cout << "TRY2" << std::endl;
            THROW(new ExceptionStr("STR EXCEPTION"));
            )
        CATCH(ExceptionNum, excep1, std::cout << excep1->num << std::endl;)
        )
    CATCH(ExceptionStr, excep, std::cout << excep->text << std::endl;)
}

// Что будет если не поймать исключение
void TEST4() {
    TRY(
        std::cout << "TRY" << std::endl;
        ObjNum a;
        THROW(new ExceptionStr("STR EXCEPTION"));
        std::cout << "END TRY";
        )
    CATCH(ExceptionNum, excep, std::cout << excep->num << std::endl;)
}

void TEST5() {
    TRY(
        ObjNum c;
        ObjNum d;
        std::cout << "TRY2" << std::endl;
        THROW(new ExceptionStr("STR EXCEPTION"));
        )
    CATCH(ExceptionNum, excep1, std::cout << excep1->num << std::endl;)
    CATCH(ExceptionStr, excep, std::cout << excep->text << std::endl;)
    END_CATCH;
}

int main() {
    TEST3();
    return 0;
}

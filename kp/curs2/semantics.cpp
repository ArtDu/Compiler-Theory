/* $mlisp19 */
#include "semantics.h"
#include "semempty.cpp"

using namespace std;

void tSM::init() {
    globals.clear();
    locals.clear();
    params.clear();
    scope = 0; // вне процедуры
//константы:
    globals["e"] =
//          properties
            tgName(VAR | DEFINED | BUILT);
    globals["pi"] =
            tgName(VAR | DEFINED | BUILT);
//
// элементарные процедуры:
    globals["remainder"] =
//          properties       arity
            tgName(PROC | DEFINED | BUILT, 2);
    globals["abs"] =
            tgName(PROC | DEFINED | BUILT, 1);
    globals["eq?"] =
            tgName(PROC | DEFINED | BUILT, 2);
// ...
// только те процедуры, которые использованы
// в СВОИХ контрольных задачах
    return;
}

        int tSM::p01() { //       S -> PROG
    bool error = false;
    ferror_message = "";
    string name;
    tgName elem;
    for (tGlobal::iterator it = globals.begin();
         it != globals.end();
         ++it) {
        // Просмотреть таблицу глобальных имен
        // и в сообщении об ошибках указать имена
        // ВСЕХ вызванных, но не определенных процедур,
        // а также использованных, но не определенных
        // глобальных переменных. Сообщения отметить [!].
        // Кроме того, ПРЕДУПРЕДИТЬ обо ВСЕХ определенных,
        // но не использованных процедурах и переменных,
        // за исключением встроенных. Сообщения отметить [?].
        //   it->first   имя
        //   it->second  учетная запись
        // ...
        name = it->first;
        elem = it->second;
        if (elem.test(USED) && !elem.test(DEFINED)) {
            error = true;
            if (elem.test(PROC))
                ferror_message += "[!]Procedure application:"
                                  "  '" + name +
                                  "' was used and not defined\n";
            else
                ferror_message += "[!]Variable application:"
                                  "  '" + name +
                                  "' was used and not defined\n";
        }
        if (!elem.test(USED) && elem.test(DEFINED) && !elem.test(BUILT)) {
            if (elem.test(PROC))
                ferror_message += "[?]Procedure application:"
                                  "  '" + name +
                                  "' was defined and not used\n";
            else
                ferror_message += "[?]Variable application:"
                                  "  '" + name +
                                  "' was defined and not used\n";
        }

    }//for...
    if (error) return 1;
    return 0;
}

int tSM::p11() { //       E -> $id
    string name = S1->name;
    if (scope == 2) {// локальная область (let ...)
        if (locals.count(name)) {// локальное имя
            //okay
            return 0;
        }

    }
    if (scope >= 1) {// область параметров
        if (params.count(name)) {// имя параметра
            //okay
            return 0;
        }
    }

    //найти имя в глобальной таблице
    tgName &ref = globals[name];
    //имя найдено
    if (ref.test(PROC)) {//процедура
        //процедуру нельзя использовать
        //только VAR или константу или параметр

        ferror_message = "[!]Procedure application:"
                         "  '" + name +
                         "' is a procedure and can not be used as a variable";
        return 1;
    }
    if (ref.empty()) {
        //ранее имя не встречалось
        //отметить использование
        ref.set(USED);
        ref.set(VAR);
        //процедуру нельзя использовать так
        //только VAR
        return 0;
    }
    if (!ref.test(USED))
        //встречалось и не использовалось
        ref.set(USED);

    return 0;
}

int tSM::p45() { //   CPROC -> HCPROC )
    string name = S1->name;
    int count = S1->count;
    if (scope > 1) {// внури тела let
        if (locals.count(name)) {// локальное имя
            //p45-1.ss
            ferror_message = "[!]Procedure application:"
                             " local variable '" + name +
                             "' shadows the procedure!";
            return 1;
        } // if locals ...
    } // if scope ...
    if (scope > 0) {// внутри процедуры
        if (params.count(name)) {// имя параметра
            //p45-2.ss
            ferror_message = "[!]Procedure application:"
                             " parameter '" + name +
                             "' shadows the procedure!";
            return 1;
        }// if params...
    }// if scope...
    do {
        //  найти имя в глобальной таблице
        tgName &ref = globals[name];
        if (ref.empty()) {//неизвестное имя
            //  создать новую учетную запись
            ref = tgName(PROC | USED, count);
            break;
        }

        // имя найдено
        if (!ref.test(PROC)) {//не процедура
            //p45-3.ss
            ferror_message = "[!]Procedure application:"
                             "  '" + name +
                             "' is not a procedure!";
            return 1;
        }

        if (ref.arity != count) {//число аргументов
            //                не равно числу параметров
            std::ostringstream buf;
            buf << "[!]Procedure application: '" << name << "' "
                //p45-4.ss
                << (ref.test(DEFINED) ? "expects " // процедура
                    //                                      уже определена
                    //p45-5.ss

                    // процедура еще не определена, но уже вызывалась ранее
                                      : "has been called already\n\t with "
                )
                << ref.arity << " argument"
                << (ref.arity != 1 ? "s" : "")
                << ", given: " << count << " !";
            ferror_message = buf.str();
            return 1;
        }


// ошибок нет
        ref.set(USED);//имя использовано
    } while (false);
    return 0;
}

int tSM::p46() { //  HCPROC -> ( $id
    //валидация процедуры $id проводиться в р45
    S1->name = S2->name;
    S1->count = 0;
    return 0;
}

int tSM::p47() { //  HCPROC -> HCPROC E
    //валидация E была проведена
    ++S1->count;
    return 0;
}

int tSM::p49() { //    BOOL -> $idq

    string name = S1->name;
    if (scope == 2) {// локальная область (let ...)
        if (locals.count(name)) {// локальное имя
            //okay
            return 0;
        }
    }
    if (scope >= 1) {// область параметров
        if (params.count(name)) {// имя параметра
            //okay
            return 0;
        }
    }

    //переменую типа BOOL обьявить нельзя
    //и как следствие использовать
    ferror_message = "[!]BOOL var:"
                     "  '" + name +
                     "' boolean variable can not exist";
    return 1;

}

int tSM::p55() { //   CPRED -> HCPRED )
    //валидация вызова предиката
    //как для композиции в p45
    //с дополнительным просмотром типов параметров
    string name = S1->name;
    int count = S1->count;
    int types = S1->types;
    if (scope > 1) {// внури тела let
        if (locals.count(name)) {// локальное имя
            ferror_message = "[!]Predicate application:"
                             " local variable '" + name +
                             "' shadows the predicate!";
            return 1;
        } // if locals ...
    } // if scope ...
    if (scope > 0) {// внутри процедуры
        if (params.count(name)) {// имя параметра
            ferror_message = "[!]Predicate application:"
                             " parameter '" + name +
                             "' shadows the predicate!";
            return 1;
        }// if params...
    }// if scope...
    do {
        //  найти имя в глобальной таблице
        tgName &ref = globals[name];
        if (ref.empty()) {//неизвестное имя
            //        создать новую учетную запись
            ref = tgName(PROC | USED, count, types);
            break;
        }

        // имя найдено
        if (!ref.test(PROC)) {//не процедура
            ferror_message = "[!]Predicate application:"
                             "  '" + name +
                             "' is not a predicate!";
            return 1;
        }

        if (ref.arity != count) {//число аргументов
            //                не равно числу параметров
            std::ostringstream buf;
            buf << "[!]Predicate application: '" << name << "' "
                << (ref.test(DEFINED) ? "expects " // процедура
                    //                                      уже определена
                    // процедура еще не определена, но уже вызывалась ранее
                                      : "has been called already\n\t with "
                )
                << ref.arity << " argument"
                << (ref.arity != 1 ? "s" : "")
                << ", given: " << count << " !";
            ferror_message = buf.str();
            return 1;
        }

        if (ref.types != types && ref.types != (ID | IDQ) ) {//типы ожидаемых параметров
            //не равен введенным
            std::ostringstream buf;
            buf << "[!]Predicate application: '" << name << "' ";
            buf << "expects ";
            if ((ref.types & ID) == ID) {
                buf << "id ";
            }
            if ((ref.types & IDQ) == IDQ) {
                buf << "idq";
            }

            buf << ", given: ";
            if ((types & ID) == ID) {
                buf << "id ";
            }
            if ((types & IDQ) == IDQ) {
                buf << "idq";
            }
            buf << " !";

            ferror_message = buf.str();
            return 1;
        }
        // ошибок нет
        if (!ref.test(USED))
            ref.set(USED);//имя использовано
    } while (false);

    return 0;
}

int tSM::p56() { //  HCPRED -> ( $idq
    //вызов предиката
    //валидация будет проведена в p55
    S1->name = S2->name;
    S1->count = 0;
    return 0;
}

int tSM::p57() { //  HCPRED -> HCPRED ARG
    ++S1->count;
    S1->types = S2->types;
    return 0;
}

int tSM::p58() { //     ARG -> E
    S1->types |= ID;
    return 0;
}

int tSM::p59() { //     ARG -> BOOL
    S1->types |= IDQ;
    return 0;
}

int tSM::p74() { //     SET -> ( set! $id E )

    string name = S3->name;
    if(scope == 2) {
        if (!params.count(name) && !locals.count(name)) {
            ferror_message = "[!]Assignment disallowed;:"
                             "  '" + name +
                             "' cannot set variable";
            return 1;
        }
        else {
            //OK
            return 0;
        }
    }

    if (scope == 1) {
        if (!params.count(name)) {
            ferror_message = "[!]Assignment disallowed;:"
                             "  '" + name +
                             "' cannot set variable, missing in parameters";
            return 1;
        }
        else {
            //OK
            return 0;
        }
    }

    //найти имя в глобальной таблице
    tgName &ref = globals[name];
    //имя найдено
    if (ref.test(PROC)) {//процедура
        //процедуру нельзя использовать
        ferror_message = "[!]Set application:"
                         "  '" + name +
                         "' is a procedure and can not be redefined";
        return 1;
    }
    if (ref.empty()) {
        //ранее имя не встречалось
        //нельзя изменить переменную, которая не существует
        ferror_message = "[!]Assignment disallowed;:"
                         "  '" + name +
                         "' cannot set variable before its definition";
        return 1;
    }

    return 0;
}

int tSM::p87() { //    PRED -> HPRED BOOL )

    string name = S1->name;
    int count = S1->count;
    int types = S1->types;
    tgName &ref = globals[name];
    if (ref.empty()) {
        //не было упоминаний
        ref = tgName(PROC | DEFINED, count, types);
    } else if (ref.test(VAR)) {
        ferror_message = "[!]Procedure initialization:"
                         " '" + name +
                         "' was already initialized as variable";
        return 1;
    } else if (ref.test(DEFINED)) {
        ferror_message = "[!]Procedure initialization:"
                         " '" + name +
                         "' was already initialized";
        return 1;
    } else {
        if (ref.arity != count) {
            std::ostringstream buf;
            buf << "[!]Procedure application: '" << name << "' "
                << (ref.test(DEFINED) ? "expects "
                                      : "has been called already\n\t with "
                )
                << ref.arity << " argument"
                << (ref.arity != 1 ? "s" : "")
                << ", given: " << count << " !";
            ferror_message = buf.str();
            return 1;
        } else if (ref.types != types && types != (ID | IDQ) ) {
            //тип ожидаемых параметров
            //не равен введенным
            std::ostringstream buf;
            buf << "[!]Procedure application: '" << name << "' ";
            buf << "given: ";
            if ((ref.types & ID) == ID) {
                buf << "id ";
            }
            if ((ref.types & IDQ) == IDQ) {
                buf << "idq";
            }

            buf << ", expects: ";
            if ((types & ID) == ID) {
                buf << "id ";
            }
            if ((types & IDQ) == IDQ) {
                buf << "idq";
            }
            buf << " !";

            ferror_message = buf.str();
            return 1;
        } else {
            ref.set(DEFINED);
        }
    }
    params.clear();
    scope = 0;
    return 0;
}

int tSM::p88() { //   HPRED -> PDPAR )
    scope = 1;
    return 0;
}

int tSM::p89() { //   PDPAR -> ( define ( $idq
    //определение предиката
    //валиадация имени произойдет в p87
    S1->name = S4->name;
    S1->count = 0;
    return 0;
}

int tSM::p90() { //   PDPAR -> PDPAR $idq
    if (params.count(S2->name)) {
        ferror_message =
                "[!]Predicate definition: in '"
                + S1->name +
                "' duplicate parameter identifier '"
                + S2->name + "'!";
        return 1;
    }
    params.insert(S2->name);
    ++S1->count;
    S1->types |= IDQ;
    return 0;
}

int tSM::p91() { //   PDPAR -> PDPAR $id
    if (params.count(S2->name)) {
        ferror_message =
                "[!]Predicate definition: in '"
                + S1->name +
                "' duplicate parameter identifier '"
                + S2->name + "'!";
        return 1;
    }
    params.insert(S2->name);
    ++S1->count;
    S1->types |= ID;
    return 0;
}

int tSM::p92() { //     VAR -> ( define $id CONST )
    //определение глобальной переменной
    string name = S3->name;
    tgName &ref = globals[name];
    if (ref.empty()) {//неизвестное имя
        //создать новую учетную запись
        ref.set(VAR);
        ref.set(DEFINED);
        return 0;
    } else if (ref.test(VAR)) {
        if (ref.test(DEFINED)) {
            ferror_message = "[!]Global variable initialization:"
                             " Trying to reinitialize '" + name +
                             "'";
            return 1;
        } else {
            ref.set(DEFINED);
            return 0;
        }
    } else {
        ferror_message = "[!]Global variable initialization:"
                         " '" + name +
                         "' was already used not as variable";
        return 1;
    }
    return 0;
}

int tSM::p93() { //    PROC -> HPROC LET )
    string name = S1->name;
    int count = S1->count;
    tgName &ref = globals[name];
    if (ref.empty()) {
        //не было упоминаний
        ref = tgName(PROC | DEFINED, count);
    } else if (ref.test(VAR)) {
        ferror_message = "[!]Procedure initialization:"
                         " '" + name +
                         "' was already initialized as variable";
        return 1;
    } else if (ref.test(DEFINED)) {
        ferror_message = "[!]Procedure initialization:"
                         " '" + name +
                         "' was already initialized";
        return 1;
    } else {
        if (ref.arity != count) {
            std::ostringstream buf;
            buf << "[!]Procedure application: '" << name << "' "
                << (ref.test(DEFINED) ? "expects "
                                      : "has been called already\n\t with "
                )
                << ref.arity << " argument"
                << (ref.arity != 1 ? "s" : "")
                << ", given: " << count << " !";
            ferror_message = buf.str();
            return 1;
        } else {
            ref.set(DEFINED);
        }
    }
    params.clear();
    scope = 0;
    return 0;
}

int tSM::p94() { //    PROC -> HPROC E )
    string name = S1->name;
    int count = S1->count;
    tgName &ref = globals[name];
    if (ref.empty()) {
        //не было упоминаний
        ref = tgName(PROC | DEFINED, count);
    } else if (ref.test(VAR)) {
        ferror_message = "[!]Procedure initialization:"
                         " '" + name +
                         "' was already initialized as variable";
        return 1;
    } else if (ref.test(DEFINED)) {
        ferror_message = "[!]Procedure initialization:"
                         " '" + name +
                         "' was already initialized";
        return 1;
    } else {
        if (ref.arity != count) {
            std::ostringstream buf;
            buf << "[!]Procedure application: '" << name << "' "
                << (ref.test(DEFINED) ? "expects "
                                      : "has been called already\n\t with "
                )
                << ref.arity << " argument"
                << (ref.arity != 1 ? "s" : "")
                << ", given: " << count << " !";
            ferror_message = buf.str();
            return 1;
        } else {
            ref.set(DEFINED);
        }
    }
    params.clear();
    scope = 0;
    return 0;
}

int tSM::p95() { //   HPROC -> PCPAR )
    scope = 1;
    return 0;
}

int tSM::p97() { //   PCPAR -> ( define ( $id
    S1->name = S4->name;
    S1->count = 0;
    return 0;
}

int tSM::p98() { //   PCPAR -> PCPAR $id
    if (params.count(S2->name)) {
        //p98-1.ss
        ferror_message =
                "[!]Procedure definition: in '"
                + S1->name +
                "' duplicate parameter identifier '"
                + S2->name + "'!";
        return 1;
    }
    params.insert(S2->name);
    ++S1->count;
    return 0;
}

int tSM::p99() { //     LET -> HLET E )

    locals.clear();
    return 0;
}

int tSM::p100() { //    HLET -> LETLOC )
    scope = 2;
    return 0;
}

int tSM::p102() { //  LETLOC -> ( let (
    return 0;
}

int tSM::p104() { //  LETVAR -> ( $id E )
    if (locals.count(S2->name)) {
        ferror_message =
                "[!]Local variables definition: '"
                "' duplicate variable initialization'"
                + S2->name + "'!";
        return 1;
    }
    locals.insert(S2->name);
    ++S1->count;
    return 0;
}
//_____________________

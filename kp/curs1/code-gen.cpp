/* $a07 */
#include "code-gen.h"

using namespace std;

int tCG::p01() { // S -> PROG
    string header = "/*  " + lex.Authentication() + "   */\n";
    header += "#include \"mlisp.h\"\n";
    header += declarations;
    header += "//________________ \n";
    S1->obj = header + S1->obj;
    return 0;
}

int tCG::p02() { //   PROG -> CALCS
    S1->obj = "int main(){\n" + S1->obj
              + " std::cin.get();\n return 0;\n}\n";
    return 0;
}

int tCG::p03() { //   PROG -> DEFS
    S1->obj += "int main(){\n"
               "\tdisplay(\"No calculations!\");newline();\n"
               "\tstd::cin.get();\n\treturn 0;\n}\n";
    return 0;
}

int tCG::p04() { //   PROG -> DEFS CALCS
    S1->obj += "int main(){\n";
    S1->obj += S2->obj;
    S1->obj += "\n\tstd::cin.get();\n\treturn 0;\n}\n";
    return 0;
}

int tCG::p05() { //  CALCS -> CALC
    return 0;
}

int tCG::p06() { //  CALCS -> CALCS CALC
    S1->obj += S2->obj;
    return 0;
}

int tCG::p07() { //   CALC -> E
    /*if (S1->obj[S1->obj.size()-1] == ';') {
        S1->obj = S1->obj.substr(0,S3->obj.size()-1);
    }*/
    S1->obj = "\tdisplay(" + S1->obj + "); newline();\n";
    return 0;
}

int tCG::p08() { //   CALC -> BOOL
    /*if (S1->obj[S1->obj.size()-1] == ';') {
        S1->obj = S1->obj.substr(0,S1->obj.size()-1);
    }*/
    S1->obj = "\tdisplay(" + S1->obj + "); newline();\n";
    return 0;
}

int tCG::p09() { //   CALC -> STR
    /*if (S1->obj[S1->obj.size()-1] == ';') {
        S1->obj = S1->obj.substr(0,S1->obj.size()-1);
    }*/
    S1->obj = "\tdisplay(" + S1->obj + "); newline();\n";
    return 0;
}

int tCG::p10() { //   CALC -> DISPSET
    S1->obj = S1->obj + "\n";
    return 0;
}

int tCG::p11() { //      E -> $id
    S1->obj = decor(S1->name);
    return 0;
}

int tCG::p12() { //      E -> $zero
    S1->obj = decor(S1->name);
    return 0;
}

int tCG::p13() { //      E -> ADD
    S1->obj = "( " + S1->obj + " )";
    return 0;
}

int tCG::p14() { //      E -> SUB
    S1->obj = "( " + S1->obj + " )";
    return 0;
}

int tCG::p15() { //      E -> DIV
    S1->obj = "( " + S1->obj + " )";
    return 0;
}

int tCG::p16() { //      E -> MUL
    S1->obj = "( " + S1->obj + " )";
    return 0;
}

int tCG::p17() { //      E -> COND
    return 0;
}

int tCG::p18() { //      E -> IF
    return 0;
}

int tCG::p19() { //      E -> CPROC
    /*if (S1->obj[S1->obj.size()-1] == ';') {
        S1->obj = S1->obj.substr(0,S1->obj.size()-1);
    }*/
    return 0;
}

int tCG::p20() { //    ADD -> HADD E )
    if (S1->count == 0) //один операнд
        S1->obj = S2->obj;
    else            //более одного операнда
        S1->obj += S2->obj;
    S1->count = 0;
    return 0;
}

int tCG::p21() { //   HADD -> ( +
    return 0;
}

int tCG::p22() { //   HADD -> HADD E
    S1->obj += S2->obj + " + ";
    ++S1->count;
    return 0;
}

int tCG::p23() { //    SUB -> HSUB E )
    if (S1->count == 0) //один операнд
        S1->obj = S2->obj;
    else            //более одного операнда
        S1->obj += S2->obj;
    S1->count = 0;
    return 0;
}

int tCG::p24() { //   HSUB -> ( -
    return 0;
}

int tCG::p25() { //   HSUB -> HSUB E
    S1->obj += S2->obj + " - ";
    ++S1->count;
    return 0;
}

int tCG::p26() { //    DIV -> HDIV E )
    if (S1->count == 0) //один операнд
        S1->obj = S2->obj;
    else            //более одного операнда
        S1->obj += S2->obj;
    S1->count = 0;
    return 0;
}

int tCG::p27() { //   HDIV -> ( /
    return 0;
}

int tCG::p28() { //   HDIV -> HDIV E
    S1->obj += S2->obj + " / ";
    ++S1->count;
    return 0;
}

int tCG::p29() { //    MUL -> HMUL E )
    if (S1->count == 0) //один операнд
        S1->obj = S2->obj;
    else            //более одного операнда
        S1->obj += S2->obj;
    S1->count = 0;
    return 0;
}

int tCG::p30() { //   HMUL -> ( *
    return 0;
}

int tCG::p31() { //   HMUL -> HMUL E
    S1->obj += S2->obj + " * ";
    ++S1->count;
    return 0;
}

// COND = (cond CLAUS ELSE) = (CLAUS CLAUS ELSE);
int tCG::p32() { //   COND -> HCOND ELSE )
    if (S2->obj[S2->obj.size()-1] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-1);
    }
    else if (S2->obj[S2->obj.size()-1] == '\n' && S2->obj[S2->obj.size()-2] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-2);
    }
    S1->obj = S1->obj + S2->obj + " ); ";
    return 0;
}

// COND = (cond CLAUS CLAUS) = (CLAUS CLAUS _infinity);
int tCG::p33() { //   COND -> HCOND CLAUS )
    if (S2->obj[S2->obj.size()-1] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-1);
    }
    else if (S2->obj[S2->obj.size()-1] == '\n' && S2->obj[S2->obj.size()-2] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-2);
    }

    S1->obj = S1->obj + S2->obj + " _infinity); ";
    return 0;
}

int tCG::p34() { //  HCOND -> ( cond
    if(S1)
    S1->obj = " ( ";
    return 0;
}

int tCG::p35() { //  HCOND -> HCOND CLAUS
    S1->obj = S1->obj + S2->obj;
    return 0;
}

// CLAUS = (BOOL E) = BOOL ? E :
int tCG::p36() { //  CLAUS -> HCLAUS E )

    if (S2->obj[S2->obj.size()-1] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-1);
    }
    else if (S2->obj[S2->obj.size()-1] == '\n' && S2->obj[S2->obj.size()-2] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-2);
    }
    else if (S2->obj[S2->obj.size()-1] == ' ' && S2->obj[S2->obj.size()-2] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-2);
    }


    if(S1->count)
        S1->obj += ", " + S2->obj + ") : ";
    else
        S1->obj += S2->obj + ") : ";
    S1->count = 0;


    return 0;
}

int tCG::p37() { // HCLAUS -> ( BOOL
    S1->obj = S2->obj + " ? (";
    return 0;
}

int tCG::p38() { // HCLAUS -> HCLAUS INTER
    if (S2->obj[S2->obj.size()-1] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-1);
    }
    else if (S2->obj[S2->obj.size()-1] == '\n' && S2->obj[S2->obj.size()-2] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-2);
    }

    if(S1->count)
        S1->obj += ", " + S2->obj;
    else
        S1->obj += S2->obj;
    S1->count++;
    return 0;
}

// ELSE = (else E) = (E)
int tCG::p39() { //   ELSE -> HELSE E )
    if (S2->obj[S2->obj.size()-1] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-1);
    }
    else if (S2->obj[S2->obj.size()-1] == '\n' && S2->obj[S2->obj.size()-2] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-2);
    }


    if(S1->count)
        S1->obj += ", " + S2->obj + ")";
    else
        S1->obj += S2->obj + ")";
    S1->count = 0;
    return 0;
}

int tCG::p40() { //  HELSE -> ( else
    S1->obj = "( ";
    return 0;
}

int tCG::p41() { //  HELSE -> HELSE INTER
    if (S2->obj[S2->obj.size()-1] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-1);
    }
    else if (S2->obj[S2->obj.size()-1] == '\n' && S2->obj[S2->obj.size()-2] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-2);
    }
    if(S1->count)
        S1->obj += ", " + S2->obj;
    else
        S1->obj += S2->obj;
    S1->count++;
    return 0;
}

// IF = (if BOOl E E) = (BOOL ? E : E)
int tCG::p42() { //     IF -> ( if BOOL E E );
    S1->obj = "( " + S3->obj + " ? " + S4->obj + " : " + S5->obj + " );";
    return 0;
}

int tCG::p43() { //  CPROC -> HCPROC )
    S1->obj = S1->obj + ")";
    return 0;
}

int tCG::p44() { // HCPROC -> ( $id
    S1->obj = decor(S2->name) + "( ";
    S1->count = 0;
    return 0;
}

int tCG::p45() { // HCPROC -> HCPROC E
    if (S1->count)
        S1->obj += ", ";// не первый параметр
    S1->obj += S2->obj;
    ++(S1->count);
    return 0;
}

int tCG::p46() { //   BOOL -> $bool
    S1->obj += (S1->name == "#t" ? "true" : "false");
    return 0;
}

int tCG::p47() { //   BOOL -> $idq
    S1->obj = decor(S1->name);
    return 0;
}

int tCG::p48() { //   BOOL -> CPRED
    return 0;
}

int tCG::p49() { //   BOOL -> REL
    return 0;
}

int tCG::p50() { //   BOOL -> ( not BOOL )
    S1->obj += "(!" + S3->obj + ")";
    return 0;
}

int tCG::p51() { //  CPRED -> HCPRED )
    S1->obj = S1->obj + ")";
    return 0;
}

int tCG::p52() { // HCPRED -> ( $idq
    S1->obj = decor(S2->name) + "( ";
    return 0;
}

int tCG::p53() { // HCPRED -> HCPRED ARG
    if (S1->count)
        S1->obj += ", ";// не первый параметр
    S1->obj += S2->obj;
    ++(S1->count);
    return 0;
}

int tCG::p54() { //    ARG -> E
    return 0;
}

int tCG::p55() { //    ARG -> BOOL
    return 0;
}

int tCG::p56() { //    REL -> ( < E E )
    S1->obj = "( " + S3->obj + " < " + S4->obj + " )";
    return 0;
}

int tCG::p57() { //    REL -> ( = E E )
    if (S3->obj[S3->obj.size()-1] == ';') {
        S3->obj = S3->obj.substr(0,S3->obj.size()-1);
    }
    else if (S3->obj[S3->obj.size()-1] == '\n' && S3->obj[S3->obj.size()-2] == ';') {
        S3->obj = S3->obj.substr(0,S3->obj.size()-2);
    }
    else if (S3->obj[S3->obj.size()-1] == ' ' && S3->obj[S3->obj.size()-2] == ';') {
        S3->obj = S3->obj.substr(0,S3->obj.size()-2);
    }

    if (S4->obj[S4->obj.size()-1] == ';') {
        S4->obj = S4->obj.substr(0,S4->obj.size()-1);
    }
    else if (S4->obj[S4->obj.size()-1] == '\n' && S4->obj[S4->obj.size()-2] == ';') {
        S4->obj = S4->obj.substr(0,S4->obj.size()-2);
    }
    else if (S4->obj[S4->obj.size()-1] == ' ' && S4->obj[S4->obj.size()-2] == ';') {
        S4->obj = S4->obj.substr(0,S4->obj.size()-2);
    }

    S1->obj = "( " + S3->obj + " == " + S4->obj + " )";
    return 0;
}

int tCG::p58() { //    STR -> $str
    S1->obj = S1->name;
    return 0;
}

int tCG::p59() { //    SET -> ( set! $id E )
    if (S4->obj[S4->obj.size()-1] == ';') {
        S4->obj = S4->obj.substr(0,S4->obj.size()-1);
    }
    else if (S4->obj[S4->obj.size()-1] == '\n' && S4->obj[S4->obj.size()-2] == ';') {
        S4->obj = S4->obj.substr(0,S4->obj.size()-2);
    }
    else if (S4->obj[S4->obj.size()-1] == ' ' && S4->obj[S4->obj.size()-2] == ';') {
        S4->obj = S4->obj.substr(0,S4->obj.size()-2);
    }
    S1->obj = decor(S3->name) + " = " + S4->obj + ";\n";
    return 0;
}

int tCG::p60() { //DISPSET -> ( display E )
    if (S3->obj[S3->obj.size()-1] == ';') {
        S3->obj = S3->obj.substr(0,S3->obj.size()-1);
    }
    S1->obj = "\tdisplay( " + S3->obj + ");\n";
    return 0;
}

int tCG::p61() { //DISPSET -> ( display BOOL )
    if (S3->obj[S3->obj.size()-1] == ';') {
        S3->obj = S3->obj.substr(0,S3->obj.size()-1);
    }
    S1->obj = "\tdisplay( " + S3->obj + ");\n";
    return 0;
}

int tCG::p62() { //DISPSET -> ( display STR )
    if (S3->obj[S3->obj.size()-1] == ';') {
        S3->obj = S3->obj.substr(0,S3->obj.size()-1);
    }
    S1->obj = "\tdisplay( " + S3->obj + ");";
    return 0;
}

int tCG::p63() { //DISPSET -> ( newline )
    S1->obj = "\tnewline();\n";
    return 0;
}

int tCG::p64() { //DISPSET -> SET
    return 0;
}

int tCG::p65() { //  INTER -> DISPSET
    return 0;
}

int tCG::p66() { //  INTER -> E
    S1->obj = S1->obj;
    return 0;
}

int tCG::p67() { //   DEFS -> DEF
    return 0;
}

int tCG::p68() { //   DEFS -> DEFS DEF
    S1->obj+=S2->obj;
    return 0;
}

int tCG::p69() { //    DEF -> PRED
    return 0;
}

int tCG::p70() { //    DEF -> VAR
    return 0;
}

int tCG::p71() { //    DEF -> PROC
    return 0;
}

//
int tCG::p72() { //   PRED -> HPRED BOOL )
    S1->obj += S2->obj + ";\n}\n";
    return 0;
}

int tCG::p73() { //  HPRED -> PDPAR )
    S1->obj += ")";
    declarations += S1->obj + ";\n"; //!!!
    S1->obj += "{\n\treturn ";
    S1->count = 0;
    return 0;
}

int tCG::p74() { //  PDPAR -> ( define ( $idq
    S1->obj = "\tbool " + decor(S4->name) + "(";
    S1->count = 0;
    return 0;
}

int tCG::p75() { //  PDPAR -> PDPAR $idq
    if (S1->count)S1->obj += ", ";// не первый параметр
    S1->obj += "\tdouble " + decor(S2->name);
    ++(S1->count);
    return 0;
}

int tCG::p76() { //  PDPAR -> PDPAR $id
    if (S1->count)S1->obj += ", ";// не первый параметр
    S1->obj += "\tdouble " + decor(S2->name);
    ++(S1->count);
    return 0;
}

int tCG::p77() { //  CONST -> $zero
    S1->obj = decor(S1->name);
    return 0;
}

int tCG::p78() { //  CONST -> $dec
    S1->obj = decor(S1->name);
    return 0;
}

int tCG::p79() { //    VAR -> ( define $id CONST )
    S1->obj = "\tdouble " + decor(S3->name) + " = " + S4->obj + ";\n";
    return 0;
}

int tCG::p80() { //   PROC -> HPROC LET )
    if (S2->obj[S2->obj.size()-1] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-1);
    }
    else if (S2->obj[S2->obj.size()-1] == '\n' && S2->obj[S2->obj.size()-2] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-2);
    }
    else if (S2->obj[S2->obj.size()-1] == ' ' && S2->obj[S2->obj.size()-2] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-2);
    }


    S1->obj = S1->obj + S2->obj + ";\n}\n";
    return 0;
}

int tCG::p81() { //   PROC -> HPROC E )

    if (S2->obj[S2->obj.size()-1] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-1);
    }
    else if (S2->obj[S2->obj.size()-1] == '\n' && S2->obj[S2->obj.size()-2] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-2);
    }
    else if (S2->obj[S2->obj.size()-1] == ' ' && S2->obj[S2->obj.size()-2] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-2);
    }

    S1->obj = S1->obj + "\treturn " + S2->obj + ";\n}\n";
    return 0;
}

int tCG::p82() { //  HPROC -> PCPAR )
    S1->obj += ")";
    declarations += S1->obj + ";\n"; //!!!
    S1->obj += " {\n  ";
    S1->count = 0;
    return 0;
}

int tCG::p83() { //  HPROC -> HPROC INTER
    S1->obj+=S2->obj;
    return 0;
}

int tCG::p84() { //  PCPAR -> ( define ( $id
    S1->obj = "\tdouble " + decor(S4->name) + "(";
    S1->count = 0;
    return 0;
}

int tCG::p85() { //  PCPAR -> PCPAR $id
    if (S1->count)
        S1->obj += ", ";// не первый параметр
    S1->obj += "\tdouble " + decor(S2->name);
    ++(S1->count);
    return 0;
}

// LET = ( let (LETVAR) INTER ) = LETVAR\n INTER
int tCG::p86() { //    LET -> HLET E )
    S1->obj+= "return " + S2->obj;
    return 0;
}

int tCG::p87() { //   HLET -> LETLOC )
    return 0;
}

int tCG::p88() { //   HLET -> HLET INTER
    if (S2->obj[S2->obj.size()-1] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-1);
    }
    else if (S2->obj[S2->obj.size()-1] == '\n' && S2->obj[S2->obj.size()-2] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-2);
    }
    else if (S2->obj[S2->obj.size()-1] == ' ' && S2->obj[S2->obj.size()-2] == ';') {
        S2->obj = S2->obj.substr(0,S2->obj.size()-2);
    }
    S1->obj+=  S2->obj + ";\n";
    return 0;
}

int tCG::p89() { // LETLOC -> ( let (
    return 0;
}

int tCG::p90() { // LETLOC -> LETLOC LETVAR
    S1->obj+=S2->obj + "\n";
    return 0;
}

// double $id = E;
int tCG::p91() { // LETVAR -> ( $id E )
    S1->obj = "\tdouble " + decor(S2->name) + " = " + S3->obj + ";";
    return 0;
}

//_____________________
int tCG::p92() { return 0; }

int tCG::p93() { return 0; }

int tCG::p94() { return 0; }

int tCG::p95() { return 0; }

int tCG::p96() { return 0; }

int tCG::p97() { return 0; }

int tCG::p98() { return 0; }

int tCG::p99() { return 0; }

int tCG::p100() { return 0; }

int tCG::p101() { return 0; }

int tCG::p102() { return 0; }

int tCG::p103() { return 0; }

int tCG::p104() { return 0; }

int tCG::p105() { return 0; }

int tCG::p106() { return 0; }

int tCG::p107() { return 0; }

int tCG::p108() { return 0; }

int tCG::p109() { return 0; }

int tCG::p110() { return 0; }


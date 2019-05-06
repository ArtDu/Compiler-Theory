/* $a07 */
#include "code-gen.h"
using namespace std;
int tCG::p01(){ // S -> PROG
  string header ="/*  " + lex.Authentication()+"   */\n";
  header += "#include \"mlisp.h\"\n";
  header += declarations;
  header += "//________________ \n";
  S1->obj = header + S1->obj;
	return 0;}
int tCG::p02(){ //   PROG -> CALCS
	return 0;}
int tCG::p03(){ //   PROG -> DEFS
	return 0;}
int tCG::p04(){ //   PROG -> DEFS CALCS
	return 0;}
int tCG::p05(){ //  CALCS -> CALC
	return 0;}
int tCG::p06(){ //  CALCS -> CALCS CALC
	return 0;}
int tCG::p07(){ //   CALC -> E
	return 0;}
int tCG::p08(){ //   CALC -> BOOL
	return 0;}
int tCG::p09(){ //   CALC -> STR
	return 0;}
int tCG::p10(){ //   CALC -> DISPSET
	return 0;}
int tCG::p11(){ //      E -> $id
	return 0;}
int tCG::p12(){ //      E -> $zero
	return 0;}
int tCG::p13(){ //      E -> ADD
	return 0;}
int tCG::p14(){ //      E -> SUB
	return 0;}
int tCG::p15(){ //      E -> DIV
	return 0;}
int tCG::p16(){ //      E -> MUL
	return 0;}
int tCG::p17(){ //      E -> COND
	return 0;}
int tCG::p18(){ //      E -> IF
	return 0;}
int tCG::p19(){ //      E -> CPROC
	return 0;}
int tCG::p20(){ //    ADD -> HADD E )
	return 0;}
int tCG::p21(){ //   HADD -> ( +
	return 0;}
int tCG::p22(){ //   HADD -> HADD E
	return 0;}
int tCG::p23(){ //    SUB -> HSUB E )
	return 0;}
int tCG::p24(){ //   HSUB -> ( -
	return 0;}
int tCG::p25(){ //   HSUB -> HSUB E
	return 0;}
int tCG::p26(){ //    DIV -> HDIV E )
	return 0;}
int tCG::p27(){ //   HDIV -> ( /
	return 0;}
int tCG::p28(){ //   HDIV -> HDIV E
	return 0;}
int tCG::p29(){ //    MUL -> HMUL E )
	return 0;}
int tCG::p30(){ //   HMUL -> ( *
	return 0;}
int tCG::p31(){ //   HMUL -> HMUL E
	return 0;}
int tCG::p32(){ //   COND -> HCOND ELSE )
	return 0;}
int tCG::p33(){ //   COND -> HCOND CLAUS )
	return 0;}
int tCG::p34(){ //  HCOND -> ( cond
	return 0;}
int tCG::p35(){ //  HCOND -> HCOND CLAUS
	return 0;}
int tCG::p36(){ //  CLAUS -> HCLAUS E )
	return 0;}
int tCG::p37(){ // HCLAUS -> ( BOOL
	return 0;}
int tCG::p38(){ // HCLAUS -> HCLAUS INTER
	return 0;}
int tCG::p39(){ //   ELSE -> HELSE E )
	return 0;}
int tCG::p40(){ //  HELSE -> ( else
	return 0;}
int tCG::p41(){ //  HELSE -> HELSE INTER
	return 0;}
int tCG::p42(){ //     IF -> ( if BOOL E E )
	return 0;}
int tCG::p43(){ //  CPROC -> HCPROC )
	return 0;}
int tCG::p44(){ // HCPROC -> ( $id
	return 0;}
int tCG::p45(){ // HCPROC -> HCPROC E
	return 0;}
int tCG::p46(){ //   BOOL -> $bool
	return 0;}
int tCG::p47(){ //   BOOL -> $idq
	return 0;}
int tCG::p48(){ //   BOOL -> CPRED
	return 0;}
int tCG::p49(){ //   BOOL -> REL
	return 0;}
int tCG::p50(){ //   BOOL -> ( not BOOL )
	return 0;}
int tCG::p51(){ //  CPRED -> HCPRED )
	return 0;}
int tCG::p52(){ // HCPRED -> ( $idq
	return 0;}
int tCG::p53(){ // HCPRED -> HCPRED ARG
	return 0;}
int tCG::p54(){ //    ARG -> E
	return 0;}
int tCG::p55(){ //    ARG -> BOOL
	return 0;}
int tCG::p56(){ //    REL -> ( < E E )
	return 0;}
int tCG::p57(){ //    REL -> ( = E E )
	return 0;}
int tCG::p58(){ //    STR -> $str
	return 0;}
int tCG::p59(){ //    SET -> ( set! $id E )
	return 0;}
int tCG::p60(){ //DISPSET -> ( display E )
	return 0;}
int tCG::p61(){ //DISPSET -> ( display BOOL )
	return 0;}
int tCG::p62(){ //DISPSET -> ( display STR )
	return 0;}
int tCG::p63(){ //DISPSET -> ( newline )
	return 0;}
int tCG::p64(){ //DISPSET -> SET
	return 0;}
int tCG::p65(){ //  INTER -> DISPSET
	return 0;}
int tCG::p66(){ //  INTER -> E
	return 0;}
int tCG::p67(){ //   DEFS -> DEF
	return 0;}
int tCG::p68(){ //   DEFS -> DEFS DEF
	return 0;}
int tCG::p69(){ //    DEF -> PRED
	return 0;}
int tCG::p70(){ //    DEF -> VAR
	return 0;}
int tCG::p71(){ //    DEF -> PROC
	return 0;}
int tCG::p72(){ //   PRED -> HPRED BOOL )
	return 0;}
int tCG::p73(){ //  HPRED -> PDPAR )
	return 0;}
int tCG::p74(){ //  PDPAR -> ( define ( $idq
	return 0;}
int tCG::p75(){ //  PDPAR -> PDPAR $idq
	return 0;}
int tCG::p76(){ //  PDPAR -> PDPAR $id
	return 0;}
int tCG::p77(){ //  CONST -> $zero
	return 0;}
int tCG::p78(){ //  CONST -> $dec
	return 0;}
int tCG::p79(){ //    VAR -> ( define $id CONST )
	return 0;}
int tCG::p80(){ //   PROC -> HPROC LET )
	return 0;}
int tCG::p81(){ //   PROC -> HPROC E )
	return 0;}
int tCG::p82(){ //  HPROC -> PCPAR )
	return 0;}
int tCG::p83(){ //  HPROC -> HPROC INTER
	return 0;}
int tCG::p84(){ //  PCPAR -> ( define ( $id
	return 0;}
int tCG::p85(){ //  PCPAR -> PCPAR $id
	return 0;}
int tCG::p86(){ //    LET -> HLET E )
	return 0;}
int tCG::p87(){ //   HLET -> LETLOC )
	return 0;}
int tCG::p88(){ //   HLET -> HLET INTER
	return 0;}
int tCG::p89(){ // LETLOC -> ( let (
	return 0;}
int tCG::p90(){ // LETLOC -> LETLOC LETVAR
	return 0;}
int tCG::p91(){ // LETVAR -> ( $id E )
	return 0;}
//_____________________
int tCG::p92(){return 0;} int tCG::p93(){return 0;} 
int tCG::p94(){return 0;} int tCG::p95(){return 0;} 
int tCG::p96(){return 0;} int tCG::p97(){return 0;} 
int tCG::p98(){return 0;} int tCG::p99(){return 0;} 
int tCG::p100(){return 0;} int tCG::p101(){return 0;} 
int tCG::p102(){return 0;} int tCG::p103(){return 0;} 
int tCG::p104(){return 0;} int tCG::p105(){return 0;} 
int tCG::p106(){return 0;} int tCG::p107(){return 0;} 
int tCG::p108(){return 0;} int tCG::p109(){return 0;} 
int tCG::p110(){return 0;} 


/* $mlisp19 */
#include "code-gen.h"
using namespace std;
int tCG::p01(){ // S -> PROG
  string header ="/*  " + lex.Authentication()+"   */\n";
  header += "#include \"mlisp.h\"\n";
  header += declarations;
  header += "//________________ \n";
  S1->obj = header + S1->obj;
	return 0;}
int tCG::p02(){ //    PROG -> CALCS
	return 0;}
int tCG::p03(){ //    PROG -> DEFS
	return 0;}
int tCG::p04(){ //    PROG -> DEFS CALCS
	return 0;}
int tCG::p05(){ //   CALCS -> CALC
	return 0;}
int tCG::p06(){ //   CALCS -> CALCS CALC
	return 0;}
int tCG::p07(){ //    CALC -> E
	return 0;}
int tCG::p08(){ //    CALC -> BOOL
	return 0;}
int tCG::p09(){ //    CALC -> STR
	return 0;}
int tCG::p10(){ //    CALC -> DISPSET
	return 0;}
int tCG::p11(){ //       E -> $id
	return 0;}
int tCG::p12(){ //       E -> CONST
	return 0;}
int tCG::p13(){ //       E -> ADD
	return 0;}
int tCG::p14(){ //       E -> SUB
	return 0;}
int tCG::p15(){ //       E -> DIV
	return 0;}
int tCG::p16(){ //       E -> MUL
	return 0;}
int tCG::p17(){ //       E -> COND
	return 0;}
int tCG::p18(){ //       E -> IF
	return 0;}
int tCG::p19(){ //       E -> CPROC
	return 0;}
int tCG::p20(){ //   CONST -> $zero
	return 0;}
int tCG::p21(){ //   CONST -> $dec
	return 0;}
int tCG::p22(){ //     ADD -> HADD E )
	return 0;}
int tCG::p23(){ //    HADD -> ( +
	return 0;}
int tCG::p24(){ //    HADD -> HADD E
	return 0;}
int tCG::p25(){ //     SUB -> HSUB E )
	return 0;}
int tCG::p26(){ //    HSUB -> ( -
	return 0;}
int tCG::p27(){ //    HSUB -> HSUB E
	return 0;}
int tCG::p28(){ //     DIV -> HDIV E )
	return 0;}
int tCG::p29(){ //    HDIV -> ( /
	return 0;}
int tCG::p30(){ //    HDIV -> HDIV E
	return 0;}
int tCG::p31(){ //     MUL -> HMUL E )
	return 0;}
int tCG::p32(){ //    HMUL -> ( *
	return 0;}
int tCG::p33(){ //    HMUL -> HMUL E
	return 0;}
int tCG::p34(){ //    COND -> HCOND ELSE )
	return 0;}
int tCG::p35(){ //    COND -> HCOND CLAUS )
	return 0;}
int tCG::p36(){ //   HCOND -> ( cond
	return 0;}
int tCG::p37(){ //   HCOND -> HCOND CLAUS
	return 0;}
int tCG::p38(){ //   CLAUS -> HCLAUS E )
	return 0;}
int tCG::p39(){ //  HCLAUS -> ( BOOL
	return 0;}
int tCG::p40(){ //  HCLAUS -> HCLAUS INTER
	return 0;}
int tCG::p41(){ //    ELSE -> HELSE E )
	return 0;}
int tCG::p42(){ //   HELSE -> ( else
	return 0;}
int tCG::p43(){ //   HELSE -> HELSE INTER
	return 0;}
int tCG::p44(){ //      IF -> ( if BOOL E E )
	return 0;}
int tCG::p45(){ //   CPROC -> HCPROC )
	return 0;}
int tCG::p46(){ //  HCPROC -> ( $id
	return 0;}
int tCG::p47(){ //  HCPROC -> HCPROC E
	return 0;}
int tCG::p48(){ //    BOOL -> $bool
	return 0;}
int tCG::p49(){ //    BOOL -> $idq
	return 0;}
int tCG::p50(){ //    BOOL -> CPRED
	return 0;}
int tCG::p51(){ //    BOOL -> REL
	return 0;}
int tCG::p52(){ //    BOOL -> OR
	return 0;}
int tCG::p53(){ //    BOOL -> AND
	return 0;}
int tCG::p54(){ //    BOOL -> ( not BOOL )
	return 0;}
int tCG::p55(){ //   CPRED -> HCPRED )
	return 0;}
int tCG::p56(){ //  HCPRED -> ( $idq
	return 0;}
int tCG::p57(){ //  HCPRED -> HCPRED ARG
	return 0;}
int tCG::p58(){ //     ARG -> E
	return 0;}
int tCG::p59(){ //     ARG -> BOOL
	return 0;}
int tCG::p60(){ //     REL -> ( < E E )
	return 0;}
int tCG::p61(){ //     REL -> ( = E E )
	return 0;}
int tCG::p62(){ //     REL -> ( > E E )
	return 0;}
int tCG::p63(){ //     REL -> ( >= E E )
	return 0;}
int tCG::p64(){ //     REL -> ( <= E E )
	return 0;}
int tCG::p65(){ //      OR -> HOR BOOL )
	return 0;}
int tCG::p66(){ //     HOR -> ( or
	return 0;}
int tCG::p67(){ //     HOR -> HOR BOOL
	return 0;}
int tCG::p68(){ //     AND -> HAND BOOL )
	return 0;}
int tCG::p69(){ //    HAND -> ( and
	return 0;}
int tCG::p70(){ //    HAND -> HAND BOOL
	return 0;}
int tCG::p71(){ //     STR -> $str
	return 0;}
int tCG::p72(){ //     STR -> SIF
	return 0;}
int tCG::p73(){ //     SIF -> ( if BOOL STR STR )
	return 0;}
int tCG::p74(){ //     SET -> ( set! $id E )
	return 0;}
int tCG::p75(){ // DISPSET -> ( display E )
	return 0;}
int tCG::p76(){ // DISPSET -> ( display BOOL )
	return 0;}
int tCG::p77(){ // DISPSET -> ( display STR )
	return 0;}
int tCG::p78(){ // DISPSET -> ( newline )
	return 0;}
int tCG::p79(){ // DISPSET -> SET
	return 0;}
int tCG::p80(){ //   INTER -> DISPSET
	return 0;}
int tCG::p81(){ //   INTER -> E
	return 0;}
int tCG::p82(){ //    DEFS -> DEF
	return 0;}
int tCG::p83(){ //    DEFS -> DEFS DEF
	return 0;}
int tCG::p84(){ //     DEF -> PRED
	return 0;}
int tCG::p85(){ //     DEF -> VAR
	return 0;}
int tCG::p86(){ //     DEF -> PROC
	return 0;}
int tCG::p87(){ //    PRED -> HPRED BOOL )
	return 0;}
int tCG::p88(){ //   HPRED -> PDPAR )
	return 0;}
int tCG::p89(){ //   PDPAR -> ( define ( $idq
	return 0;}
int tCG::p90(){ //   PDPAR -> PDPAR $idq
	return 0;}
int tCG::p91(){ //   PDPAR -> PDPAR $id
	return 0;}
int tCG::p92(){ //     VAR -> ( define $id CONST )
	return 0;}
int tCG::p93(){ //    PROC -> HPROC LET )
	return 0;}
int tCG::p94(){ //    PROC -> HPROC E )
	return 0;}
int tCG::p95(){ //   HPROC -> PCPAR )
	return 0;}
int tCG::p96(){ //   HPROC -> HPROC INTER
	return 0;}
int tCG::p97(){ //   PCPAR -> ( define ( $id
	return 0;}
int tCG::p98(){ //   PCPAR -> PCPAR $id
	return 0;}
int tCG::p99(){ //     LET -> HLET E )
	return 0;}
int tCG::p100(){ //    HLET -> LETLOC )
	return 0;}
int tCG::p101(){ //    HLET -> HLET INTER
	return 0;}
int tCG::p102(){ //  LETLOC -> ( let (
	return 0;}
int tCG::p103(){ //  LETLOC -> LETLOC LETVAR
	return 0;}
int tCG::p104(){ //  LETVAR -> ( $id E )
	return 0;}
//_____________________
int tCG::p105(){return 0;} int tCG::p106(){return 0;} 
int tCG::p107(){return 0;} int tCG::p108(){return 0;} 
int tCG::p109(){return 0;} int tCG::p110(){return 0;} 



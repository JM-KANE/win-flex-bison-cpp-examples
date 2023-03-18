#pragma once

#ifndef __FLEX_LEXER_H
#undef yyFlexLexer
#define yyFlexLexer myFlexLexer
#include <FlexLexer.h>
#endif

#define YY_DECL int Scanner::lex()

class Scanner
    :public myFlexLexer
{
public:
    Scanner(std::istream& arg_yyin, std::ostream& arg_yyout = std::cerr);
    int lex();
};

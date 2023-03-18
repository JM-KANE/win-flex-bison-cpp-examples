#pragma once

#ifndef __FLEX_LEXER_H
#include <FlexLexer.h>
#endif

#include "parser.hpp"
#define YY_DECL yy::parser::symbol_type yy::scanner::lex(driver& drv)

namespace yy
{
    class scanner
        :public yyFlexLexer
    {
    public:
        scanner(std::istream& arg_yyin, std::ostream& arg_yyout = std::cerr);
        yy::parser::symbol_type lex(driver& drv);
    };
}

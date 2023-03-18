﻿#pragma once

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
        static yy::parser::symbol_type make_NUMBER(const std::string& s, const yy::parser::location_type& loc);
    public:
        scanner(std::istream& arg_yyin, std::ostream& arg_yyout = std::cerr);
        yy::parser::symbol_type lex(driver& drv);
    };
}

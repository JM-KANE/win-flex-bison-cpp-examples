%{
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include "driver.hpp"
%}
%{
#define YY_USER_ACTION loc.columns(yyleng);
yy::parser::symbol_type make_NUMBER(const std::string &s, const yy::parser::location_type& loc);
%}

%option c++
%option noyywrap nounput noinput batch debug
%option outfile="scanner.cpp"
%option yyclass="scanner"

id      [a-zA-Z][a-zA-Z_0-9]*
int     [0-9]+
real1   [0-9]+[.][0-9]*
real2   [.][0-9]+
num     {int}|{real1}|{real2}
blank   [ \t\r]

%%
%{
    // A handy shortcut to the location held by the driver.
    yy::location& loc = drv.location;
    // Code run each time yylex is called.
    loc.step();
%}

{blank}+    { loc.step(); }
\n+         { loc.lines(yyleng); loc.step(); }

"-"         { return yy::parser::make_MINUS(loc); }
"+"         { return yy::parser::make_PLUS(loc); }
"*"         { return yy::parser::make_STAR(loc); }
"/"         { return yy::parser::make_SLASH(loc); }
"("         { return yy::parser::make_LPAREN(loc); }
")"         { return yy::parser::make_RPAREN(loc); }
":="        { return yy::parser::make_ASSIGN(loc); }
"="         { return yy::parser::make_INITIAL(loc); }
"^"         { return yy::parser::make_TRI(loc); }
"def"       { return yy::parser::make_DEF(loc); }
";"         { return yy::parser::make_SCOLON(loc); }

{num}       { return make_NUMBER(yytext, loc); }
{id}        { return yy::parser::make_IDENTIFIER(yytext, loc); }

.           {}
<<EOF>>     { return yy::parser::make_YYEOF(loc); }

%%

yy::parser::symbol_type make_NUMBER(const std::string &s, const yy::parser::location_type& loc)
{
    auto n = std::stod(s);
    return yy::parser::make_NUMBER(n, loc);
}

yy::scanner::scanner(std::istream& arg_yyin, std::ostream& arg_yyout) :yyFlexLexer(arg_yyin, arg_yyout)
{
}

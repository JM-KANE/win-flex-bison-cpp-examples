%skeleton "lalr1.cc"
%require "3.8.1"

%header "parser.hpp"
%output "parser.cpp"

%locations
%define api.location.file "location.hpp"

%define api.token.raw
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define parse.trace
%define parse.error detailed
%define parse.lac full

%parse-param { driver& drv }
%lex-param { driver& drv } 

%code requires 
{
#include <string>
class driver;
class Node;
}

%code
{
#include "driver.hpp"
}

%define api.token.prefix {TOK_}
%token
ASSIGN 99 ":=" 
MINUS "-"
PLUS "+"
STAR "*"
SLASH "/"
LPAREN "("
RPAREN ")"
;
%token <std::string> IDENTIFIER "identifier"
%token <Node*> NUMBER "number"
%nterm <Node*> exp

%printer { yyo << $$; } <*>;

%start unit;
%left "+" "-";
%left "*" "/";
%%
unit: assignments exp { drv.result = $2; };

assignments:
    %empty
|   assignments assignment
;

assignment:
    "identifier" ":=" exp { drv.variables[$1] = driver::VariableInfo{ @1,$3 }; }

exp:
    "number"        { $$ = $1; }
|   "identifier"    { $$ = drv.variables[$1].value->Copy(); }
|   exp "+" exp     { $$ = $1; $$->value += $3->value; delete $3; }
|   exp "-" exp     { $$ = $1; $$->value -= $3->value; delete $3; }
|   exp "*" exp     { $$ = $1; $$->value *= $3->value; delete $3; }
|   exp "/" exp     { $$ = $1; $$->value /= $3->value; delete $3; }
|   "(" exp ")"     { $$ = $2; }
;

%%
void yy::parser::error (const location_type& l, const std::string& m)
{
    std::cerr << l << ": " << m << '\n';
    for (size_t i = 0; i < yystack_.size() - 1; ++i)
    {
        auto yykind = yystack_[i].kind();
        switch (yykind)
        {
        case symbol_kind::S_NUMBER:
        case symbol_kind::S_exp:
        {
            delete yystack_[i].value.template as<Node*>();
        }
        break;
        default:
            break;
        }
    }
}

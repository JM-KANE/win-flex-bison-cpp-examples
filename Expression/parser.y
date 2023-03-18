%skeleton "lalr1.cc"
%require "3.8.1"

%header "parser.hpp"
%output "parser.cpp"

%locations
%define api.location.file "location.hpp"

%define api.token.raw
%define api.token.constructor
%define api.value.type variant
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
class expression;
class variable;
class statement;
}

%code
{
#include "driver.hpp"
#undef yylex
#define yylex drv.lexer->lex
}

%define api.token.prefix {TOK_}
%token
ASSIGN ":=" 
INITIAL "="
MINUS "-"
PLUS "+"
STAR "*"
SLASH "/"
TRI "^"
LPAREN "("
RPAREN ")"
SCOLON ";"
DEF "def"
;
%token <std::string> IDENTIFIER "identifier"
%token <double> NUMBER "number"
%nterm <expression*> exp add_sub signed multi_div pow atom
%nterm <variable*> declaration
%nterm <statement*> assignment

%%
unit: statements exp        { drv.result = $2; };

statements:
    %empty
|   statements statement ";"
;

statement:
    assignment              { drv.add_stmt($1); }
|   declaration             { 
                                if (!drv.add_variable($1))
                                {
                                    auto strVar = $1->name();
                                    throw yy::parser::syntax_error(@1, "redefined identifier: " + strVar); 
                                }
                            }
;

assignment:
    "identifier" ":=" exp   { 
                                auto var = drv.lookup($1);
                                if (var)
                                {
                                    $$ = new statement(var, $3);
                                }
                                else
                                {
                                    throw yy::parser::syntax_error(@1, "undefined identifier: " + $1); 
                                }
                            }

declaration:
    DEF IDENTIFIER          { $$ = new variable(std::move($2)); }
|   DEF IDENTIFIER "=" exp  { $$ = new variable(std::move($2), $4); }
;

exp: add_sub;

add_sub:
    add_sub "+" signed      { $$ = new add_expr($1, $3); }
|   add_sub "-" signed      { $$ = new sub_expr($1, $3); }
|   signed
;

signed:
    "+" multi_div           { $$ = $2; }
|   "-" multi_div           { $$ = new neg_expr($2); }
|   multi_div
;

multi_div:
    multi_div "*" pow       { $$ = new multi_expr($1, $3); }
|   multi_div "/" pow       { $$ = new div_expr($1, $3); }
|   pow
;

pow:
    atom "^" atom           { $$ = new pow_expr($1, $3); }
|   atom
;

atom:
    "number"                { $$ = new real_literal_expr($1); }
|   "(" exp ")"             { $$ = $2; }
|   "identifier"            { 
                                auto var = drv.lookup($1);
                                if (var)
                                {
                                    $$ = new variable_expr(var);
                                }
                                else
                                {
                                    throw yy::parser::syntax_error(@1, "undefined identifier: " + $1); 
                                }
                            }
;

%%
void yy::parser::error (const location_type& l, const std::string& m)
{
    std::cerr << l << ": " << m << '\n';

    // TODO 在parser的pop操作中清理, 而不是在这里
    for (size_t i = 0; i < yystack_.size() - 1; ++i)
    {
        auto yykind = yystack_[i].kind();
        if (symbol_kind::S_assignment <= yykind && symbol_kind::S_atom >= yykind)
        {
            delete yystack_[i].value.template as<object*>();
        }
    }
}

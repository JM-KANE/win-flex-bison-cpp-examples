%require "3.2"
%language "c++"
%skeleton "lalr1.cc"

%define api.value.type variant
%define api.token.constructor
%define api.namespace {simple}
%define api.parser.class {Parser}

%header "simple.hpp"
%output "simple.cpp"

%code
{
    // %locations
    // %parse-param
    // %destructor
}

%code
{
    namespace simple
    {
        // Return the next token.
        auto yylex () -> Parser::symbol_type
        {
            static int count = 0;
            switch (int stage = count++)
            {
            case 0:
                return Parser::make_TEXT ("I have three numbers for you.");
            case 1: case 2: case 3:
                return Parser::make_NUMBER (new auto(stage));
            case 4:
                return Parser::make_TEXT ("And that's all!");
            default:
                return Parser::make_YYEOF ();
            }
        }
    }
}

%token <std::string> TEXT;
%token <int*> NUMBER;
%nterm <std::vector<std::string>> list;
%nterm <std::string> item;

%destructor { delete $$; } NUMBER

%%

result:
    list    {
                for (auto& str : $1)
                {
                    std::cout << str << ' ';
                }
                std::cout << '\n';
            }
;

list:
    %empty     {}
|   list <std::size_t>{ $$ = $1.size(); } item { $$ = $1; $$.emplace_back (std::move($3)); }
;

item:
    TEXT    { $$ = std::move($1); }
|   NUMBER  { $$ = std::to_string (*$1); }

%%

namespace simple
{
    void Parser::error (const std::string& msg)
    {
        std::cerr << msg << '\n';
    }
}

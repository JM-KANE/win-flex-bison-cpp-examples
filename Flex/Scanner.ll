%{
    #include "Scanner.hpp"
    int mylineno{};     
%}

%option noyywrap c++ batch
%option prefix="my"
%option yyclass="Scanner"
%option outfile="Scanner.cpp"

str     \"[^\n]+\"
ws      [ \t]+
alpha   [A-Za-z]
dig     [0-9]
name    ({alpha}|{dig}|\$)({alpha}|{dig}|[_.\-/$])*
num1    [-+]?{dig}+\.?([eE][-+]?{dig}+)?
num2    [-+]?{dig}*\.{dig}+([eE][-+]?{dig}+)?
number  {num1}|{num2}

%%
{ws}  
"/*"    {
            int c;
            while ((c = yyinput()) != 0)
            {
                if (c == '\n')
                {
                    ++mylineno;
                }
                else if (c == '*')
                {
                    if ((c = yyinput()) == '/')
                        break;
                    else
                        unput(c);
                }
            }
            if (!c)
            {
                yyout << "error" << '\n';
            }
        }

{number}    { yyout << "number " << YYText() << '\n'; }    
\n          { mylineno++; }
{name}      { yyout << "name " << YYText() << '\n'; }
{str}       { yyout << "string " << YYText() << '\n'; }
%%


Scanner::Scanner(std::istream& arg_yyin, std::ostream& arg_yyout) :yyFlexLexer(arg_yyin, arg_yyout)
{
}

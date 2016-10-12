%{

#include <algorithm>
#include <string>
#include <iostream>
#include "frontend/scanner.hpp"

typedef FrontEnd::Parser::token token;
bool term = false;

#define T_STRING( s ) ( new std::string(s) )
#define STRIP_QUOTES( s ) ( s->erase(remove(s->begin(), s->end(), '\"'), s->end()) )
#define yyterminate() return (term = !term)?Parser::token::PRGEND : YY_NULL
#define YY_NO_UNISTD_H

%}

%option debug
%option nodefault
%option yyclass="FrontEnd::Scanner"
%option noyywrap
%option c++

digit ([0-9])
integer ({digit}+)
float_num ({digit}+\.{digit}+)

%%

[\ \t]+
\"[^"]*\"           {
                      yylval->sval = T_STRING(yytext);
                      yylval->sval->erase(remove(yylval->sval->begin(), yylval->sval->end(), '\"' ), yylval->sval->end());
                      return(token::STRING);
                    }

%%

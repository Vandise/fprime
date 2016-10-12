%x  incl
%{

#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include "frontend/scanner.hpp"

typedef FrontEnd::Parser::token token;
bool term = false;

#define T_STRING( s ) ( new std::string(s) )
#define STRIP_QUOTES( s ) ( s->erase(remove(s->begin(), s->end(), '\"'), s->end()) )
#define yyterminate() return (term = !term)?Parser::token::PRGEND : YY_NULL
#define YY_NO_UNISTD_H
#define MAX_INCLUDE_DEPTH 10
YY_BUFFER_STATE include_stack[MAX_INCLUDE_DEPTH];

std::ifstream *file = new std::ifstream;

%}

%option debug
%option nodefault
%option yyclass="FrontEnd::Scanner"
%option noyywrap
%option c++
%option yylineno

digit ([0-9])
integer ({digit}+)
float_num ({digit}+\.{digit}+)

%%

import              BEGIN(incl);

\n                  { 
                      return( token::NEWLINE );   
                    }
[\ \t]+
\"[^"]*\"           {
                      yylval->sval = T_STRING(yytext);
                      yylval->sval->erase(remove(yylval->sval->begin(), yylval->sval->end(), '\"' ), yylval->sval->end());
                      return(token::STRING);
                    }

<incl>[ \t]* /* skip whitespace */
<incl>[^ \t\n]+     {
                      file->open(yytext);
                      yyin = file;
                      if (!yyin || !file->is_open())
                      {
                        std::cout << "Error: Unable to import file " << yytext << std::endl;
                        exit(1);
                      }
                      yypush_buffer_state(yy_create_buffer( yyin, YY_BUF_SIZE ));
                      BEGIN(INITIAL);
                    }
<<EOF>>             {
     			            yypop_buffer_state();
     
                      if ( !YY_CURRENT_BUFFER )
                      {
                        file->close();
                        delete file;
                        yyterminate();
                      }
                     }
%%

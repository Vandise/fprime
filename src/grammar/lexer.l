%x  incl
%{

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include "frontend/scanner.hpp"

#undef  YY_DECL
#define YY_DECL int FrontEnd::Scanner::yylex( FrontEnd::Parser::semantic_type * const lval, FrontEnd::Parser::location_type *loc ) 

using token = FrontEnd::Parser::token;

#define T_STRING( s ) ( new std::string(s) )
#define YY_NO_UNISTD_H
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);                 \
        if (current_file->previous != nullptr) {                          \
          current_file->column += yyleng;                                 \
        }                                                                 \
        else                                                              \
        {                                                                 \
          current_file->column += yyleng;                                 \
        }                                                                 \
        loc->begin.line = loc->end.line = current_file->line;

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

%{
  yylval = lval;
%}

import              BEGIN(incl);

\n                  {
                      current_file->line += 1;
                      return( token::T_NEWLINE );   
                    }
[\ \t]+             
\"[^"]*\"           {
                      yylval->build< std::string >( yytext );
                      return(token::T_STRING);
                    }
{integer}           {
                      yylval->build< int >( atoi(yytext) );
                      return( token::T_INTEGER );
                    }
.                   { }

<incl>[ \t]*        /* skip whitespace */
<incl>[^ \t\n]+     {
                      file->open(yytext);
                      yyin = file;
                      if (!yyin || !file->is_open())
                      {
                        std::cout << "Error: Unable to import file " << yytext << std::endl;
                        exit(1);
                      }

                      current_file->next = new file_map();
                      current_file->next->previous = current_file;
                      current_file->next->filename = std::string(yytext);
                      current_file = current_file->next;
                      current_file->line   = 1;
                      current_file->column = 1;

                      *loc->begin.filename = current_file->filename;

                      yypush_buffer_state(yy_create_buffer( yyin, YY_BUF_SIZE ));
                      BEGIN(INITIAL);
                    }
<<EOF>>             {
     			            yypop_buffer_state();

     			            if (current_file->next != nullptr) delete current_file->next;
     			            if (current_file->previous != nullptr) {
                        current_file = current_file->previous;
                        delete current_file->next;
                      }

                      *loc->begin.filename = current_file->filename;
                      if ( !YY_CURRENT_BUFFER )
                      {
                        file->close();
                        delete file;
                        yyterminate();
                      }
                     }

%%

%x  incl
%{

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include "common/fprime.hpp"
#include "frontend/headers/scanner.hpp"
#include "util/debug_new/debug_new.h"

#undef  YY_DECL
#define YY_DECL int FrontEnd::Scanner::yylex( FrontEnd::Parser::semantic_type * const lval, FrontEnd::Parser::location_type *loc ) 

using token = FrontEnd::Parser::token;

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

int_32              {
                      yylval->datatype = INT_32;
                      return( token::T_TYPE_INT_32 );
                    }
[_a-zA-Z\\?\\!]+    {
                      yylval->sval = new std::string(yytext);
                      yylval->sval->erase(remove(yylval->sval->begin(), yylval->sval->end(), '\"' ), yylval->sval->end());
                      return( token::T_IDENTIFIER );
                    }
"="                 {
                      return( token::T_ASSIGN );
                    }
{integer}           {
                      yylval->ival = (atoi(yytext));
                      return( token::T_INTEGER );
                    }
\"[^"]*\"           {
                      yylval->sval = new std::string(yytext);
                      yylval->sval->erase(remove(yylval->sval->begin(), yylval->sval->end(), '\"' ), yylval->sval->end());
                      return( token::T_STRING );
                    }
.                   { }

<incl>[ \t]*        /* skip whitespace */
<incl>[^ \t\n]+     {

                      current_file->next = new file_map();
                      current_file->next->previous = current_file;
                      current_file->next->filename = std::string(yytext);

                      current_file = current_file->next;
                      current_file->line   = 1;
                      current_file->column = 1;
                      current_file->fp = new std::ifstream();

                      current_file->fp->open(yytext);
                      yyin = current_file->fp;

                      if (!yyin || !current_file->fp->is_open())
                      {
                        yylval->sval = new std::string("Unable to import file " + current_file->filename);
                        return( token::T_FATAL_ERROR );
                      }

                      *loc->begin.filename = current_file->filename;

                      yypush_buffer_state(yy_create_buffer( yyin, YY_BUF_SIZE ));
                      BEGIN(INITIAL);
                    }
<<EOF>>             {
                      yypop_buffer_state();

                      if (current_file->next != nullptr) {
                        delete current_file->next;
                        current_file->next = nullptr;
                      }
                      if (current_file->fp != nullptr) {
                        current_file->fp->close();
                        delete current_file->fp;
                        current_file->fp = nullptr;
                      }
                      if (current_file->previous != nullptr) {
                        current_file = current_file->previous;
                        delete current_file->next;
                        current_file->next = nullptr;
                      }

                      *loc->begin.filename = current_file->filename;
                      if ( !YY_CURRENT_BUFFER )
                      {
                        yyterminate();
                      }
                     }

%%

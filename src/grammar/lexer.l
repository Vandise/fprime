%x  incl
%{

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include "frontend/scanner.hpp"
#include "util/debug_new/debug_new.h"

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

"byte"              {  yylval->build< int >( BYTE );    return( token::T_TYPE_BYTE );    }
"bool"              {  yylval->build< int >( BOOLEAN ); return( token::T_TYPE_BOOLEAN ); }
"int_8"             {  yylval->build< int >( INT_8 );   return( token::T_TYPE_INT_8 );   }
"int_16"            {  yylval->build< int >( INT_16 );  return( token::T_TYPE_INT_16 );  }
"int_32"            {  yylval->build< int >( INT_32 );  return( token::T_TYPE_INT_32 );  }
"int_64"            {  yylval->build< int >( INT_64 );  return( token::T_TYPE_INT_64 );  }
"int"               {  yylval->build< int >( INTEGER ); return( token::T_TYPE_INTEGER ); }
"float"             {  yylval->build< int >( FLOAT );   return( token::T_TYPE_FLOAT );   }
"decimal"           {  yylval->build< int >( DOUBLE );  return( token::T_TYPE_DOUBLE );  }
"string"            {  yylval->build< int >( STRING );  return( token::T_TYPE_STRING );  }

"struct"            { return ( token::T_STRUCT );        }
"*"                 { return ( token::T_ASTERISK );      }
"["                 { return ( token::T_OPEN_BRACKET );  }
"]"                 { return ( token::T_CLOSE_BRACKET ); }
"{"                 { return ( token::T_OPEN_BRACE );    }
"}"                 { return ( token::T_CLOSE_BRACE );   }

[_a-zA-Z\\?\\!]+    {
                      yylval->build< std::string >( yytext );
                      return( token::T_IDENTIFIER );
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
                        yylval->build< std::string >( "Unable to import file " + std::string(yytext) );
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

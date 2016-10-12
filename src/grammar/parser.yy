%skeleton "lalr1.cc"
%require  "3.0"
%defines 
%define api.namespace {FrontEnd}
%define parser_class_name {Parser}
%define parse.trace

%code requires {
  namespace FrontEnd {
    class Scanner;
    class Driver;
  }
}

%parse-param { Scanner  &scanner  }
%parse-param { Driver  &driver  }

%code {

  #include <iostream>
  #include <cstdlib>
  #include "frontend/headers/driver.hpp"

  #undef yylex
  #define yylex scanner.yylex
}

%token    <sval>  STRING
%token            NEWLINE 
%token            PRGEND 0     "end of file"

%destructor { if ($$)  { delete ($$); ($$) = nullptr; } } <sval>

%left  DOT
%right "!"
%left  MULT DIV
%left  PLUS MINUS
%left  GT GE LT LE
%left  EQ "!="
%left  "&&"
%left  "||"
%left  COMMA

%union {
  std::string                        *sval;
}

%%

Expressions:
  Expression                          {}
  | Expressions Terminator Expression {}
  |                                   {}
  | Expressions Terminator            {}
  ;

Expression:
  Literal
  ;

Literal:
  STRING      { std::cout << "Found String " << *$1 << std::endl; }
  ;

Terminator:
  NEWLINE
  ;
%%

void
FrontEnd::Parser::error(const std::string &err_message )
{
  std::cerr << "Error: " << err_message << std::endl;
}

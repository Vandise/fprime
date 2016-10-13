%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines
%error-verbose
%define api.namespace {FrontEnd}
%define parser_class_name {Parser}

%code requires {
  namespace FrontEnd {
    class Driver;
    class Scanner;
  }
}

%parse-param { Scanner  &scanner  }
%parse-param { Driver  &driver  }

%code {

#include <iostream>
#include <cstdlib>
#include <fstream>

#include "frontend/headers/driver.hpp"

#undef yylex
#define yylex scanner.yylex

}

%define parse.assert
%define api.value.type variant

%token    <std::string>  T_STRING
%token    <int>          T_INTEGER
%token                   T_NEWLINE 
%token                   PRGEND 0     "end of file"


%locations
%initial-action {
    @$.begin.filename = @$.end.filename = &driver.file;
};

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
  T_STRING { std::cout << "Found String: " << $1 << std::endl; }
  ;

Terminator:
  T_NEWLINE
  ;
%%

void
FrontEnd::Parser::error(const location_type& l, const std::string& m )
{
  std::ifstream error_file (*l.begin.filename);
  std::string line;
  int line_number = 1;
  int chars_read = 0;

  if (error_file) {
    std::cout << std::endl << "-- ERROR -------------------------------------- " << std::endl << std::endl;
    std::cout << *l.begin.filename << std::endl;

    while(getline(error_file, line)) {

      chars_read += line.length();
      if (line_number >= l.begin.line - 5 || line_number <= l.begin.line + 5) {

        std::cout << "    " << line_number << ": " << line << std::endl;

        if (line_number == l.begin.line) {

          std::cout << " >> " << m << std::endl << std::endl;
        }

      }
      line_number++;
    }

  }

}


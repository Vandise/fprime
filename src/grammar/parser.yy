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

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <fstream>

#include "util/debug_new/debug_new.h"
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

    std::cout << std::endl << "-- ERROR " << std::endl;
    std::cout << std::endl << " " << m << " on line " << l.begin.line << " in file: " << *l.begin.filename << std::endl << std::endl;
    std::cout << "-- SOURCE " << std::endl << std::endl;

    //
    // Source Tracking
    //

    while(getline(error_file, line)) {

      if (line_number >= l.begin.line - 5 || line_number <= l.begin.line + 5) {
        std::cout << "    " << line_number << ": " << line << std::endl;

        if (line_number == l.begin.line) {
/*
          int position = scanner.current_file->column - ((line_number - 1) * 2 + chars_read);
          std::string colptr = "";
          colptr.assign(std::to_string(line_number).length() + 6 + (position), ' ');
          colptr += "^";
          std::cout << colptr << std::endl;
*/
          std::string colptr = "";
          colptr.assign(std::to_string(line_number).length() + 6, ' ');
          int i = 0;
          while (i <= line.length()) {
            colptr += "~";
            i++;
          }
          std::cout << colptr << std::endl;
      }

      }
      line_number++;
      chars_read += line.length();
    }

    error_file.close();


    //
    // File Trace
    //

    std::cout << std::endl << "-- TRACE " << std::endl << std::endl;

    while(scanner.current_file->previous != nullptr) {
      scanner.current_file = scanner.current_file->previous;
    }

    int j = 1;

    while(scanner.current_file != nullptr) {
      std::string trace = "";
      trace.assign(j*2, ' ');
      trace += ">> ";
      if (scanner.current_file->filename == *l.begin.filename) {
        trace += "Error in ";
      } else {
        trace += "Included in ";
      }
      trace += scanner.current_file->filename + " on line " + std::to_string(scanner.current_file->line);
      std::cout << trace << std::endl;

      int k = 1;
      std::ifstream trace_file (scanner.current_file->filename);
      while(getline(trace_file, line)) {
        std::string bktrace = "";
        bktrace.assign(j*2, ' ');
        bktrace += "   | " + std::to_string(k) + ": ";
        if (k >= scanner.current_file->line - 2 || k <= scanner.current_file->line + 2) {
          bktrace += line;
          std::cout << bktrace << std::endl;
        }
        k++;
      }

      scanner.current_file = scanner.current_file->next;
      j++;
    }

    std::cout << std::endl << "-- END TRACE" << std::endl << std::endl;
  }

}


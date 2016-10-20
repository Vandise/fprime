%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%error-verbose
%define api.namespace {FrontEnd}
%define parser_class_name {Parser}

%code requires {

#include "common/fprime.h"

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

/* def */
%token    <std::string>  T_IDENTIFIER

/* literals */
%token    <std::string>  T_STRING
%token    <int>          T_INTEGER

/* types */
%token    <int>          T_TYPE_BYTE
%token    <int>          T_TYPE_BOOLEAN
%token    <int>          T_TYPE_INT_8
%token    <int>          T_TYPE_INT_16
%token    <int>          T_TYPE_INT_32
%token    <int>          T_TYPE_INT_64
%token    <int>          T_TYPE_INTEGER
%token    <int>          T_TYPE_FLOAT
%token    <int>          T_TYPE_DOUBLE
%token    <int>          T_TYPE_STRING
%token    <int>          T_TYPE_ARRAY
%token    <int>          T_TYPE_VOID

%token                   T_FUNCTION
%token                   T_END

/* misc */
%token                   T_OPEN_PAREN
%token                   T_CLOSE_PAREN
%token                   T_OPEN_BRACKET
%token                   T_CLOSE_BRACKET
%token                   T_OPEN_BRACE
%token                   T_CLOSE_BRACE
%token                   T_ASTERISK
%token                   T_STRUCT
%token                   T_EQUAL
%token    <std::string>  T_FATAL_ERROR
%token                   T_NEWLINE
%token                   PRGEND 0     "end of file"


%locations
%initial-action {
    @$.begin.filename = @$.end.filename = &driver.file;
};

%type <int>         DataTypes
%type <std::string> Errors

%%

Expressions:
  Expression                          {}
  | Expressions Terminator Expression {}
  |                                   {}
  | Expressions Terminator            {}
  ;

Expression:
    Literal
  | Initialize
  | Assignment
  | Struct
  | Function
  | Errors
  ;

Literal:
    T_STRING  { std::cout << "Found String: "  << $1 << std::endl; }
  | T_INTEGER { std::cout << "Found Integer: " << $1 << std::endl; }
  ;

Initialize:
    DataTypes T_IDENTIFIER
      { std::cout << "Setting Identifier: " << $2 << " with type: " << $1 << std::endl; }
  | DataTypes T_ASTERISK T_IDENTIFIER
      { std::cout << "Setting Identifier: " << $3 << " pointer: " << POINTER << " type: " << $1 << std::endl; }
  | DataTypes T_OPEN_BRACKET T_CLOSE_BRACKET T_IDENTIFIER
      { std::cout << "Setting Identifier: " << $4 << " with type: " << ARRAY << " Only: " << $1 << std::endl; }
  | DataTypes T_OPEN_BRACKET T_INTEGER T_CLOSE_BRACKET T_IDENTIFIER
      { std::cout << "Setting Identifier: " << $5 << " with type: " << ARRAY << " Only: " << $1 << " Fixed Size: " << $3 << std::endl; }
  ;

Assignment:
    Initialize T_EQUAL Expression { std::cout << "Assigning variable with a type" << std::endl; }
  ;

Errors:
    T_FATAL_ERROR { error(yyla.location, $1); YYABORT; }
  ;

DataTypes:
    T_TYPE_BYTE      { $$ = $1; }
  | T_TYPE_BOOLEAN   { $$ = $1; }
  | T_TYPE_INT_8     { $$ = $1; }
  | T_TYPE_INT_16    { $$ = $1; }
  | T_TYPE_INT_32    { $$ = $1; }
  | T_TYPE_INT_64    { $$ = $1; }
  | T_TYPE_INTEGER   { $$ = $1; }
  | T_TYPE_FLOAT     { $$ = $1; }
  | T_TYPE_DOUBLE    { $$ = $1; }
  | T_TYPE_STRING    { $$ = $1; }
  | T_TYPE_VOID      { $$ = $1; }
  ;

Struct:
    T_STRUCT T_IDENTIFIER T_OPEN_BRACE
      StructInitializers
    T_CLOSE_BRACE
                  { std::cout << "Structure definition: " << $2 << std::endl; }
  ;

StructInitializers:
    Initialize                                {}
  | StructInitializers Terminator Initialize  {}
  |                                           { /* error(yyla.location, "Struct cannot have empty body definition"); YYABORT; */ }
  | StructInitializers Terminator             {}
  ;

Function:
    DataTypes T_IDENTIFIER T_OPEN_PAREN T_CLOSE_PAREN
      Expressions
    T_END
          { std::cout << "Creating function: " << $2 << std::endl; }
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


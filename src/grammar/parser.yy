%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%error-verbose
%define api.namespace {FrontEnd}
%define parser_class_name {Parser}

%code requires {

  #include "common/fprime.hpp"

  namespace FrontEnd {
    class Driver;
    class Scanner;
  }

  namespace AST {
    class Stack;
    class AbstractNode;
    class LiteralNode;
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
#include "ast/headers/ast.hpp"

#undef yylex
#define yylex scanner.yylex

}

/*
%destructor { if ($$)  { delete ($$); ($$) = nullptr; } } <sval> <abstract_node> <stack>
*/

%locations
%initial-action {
    @$.begin.filename = @$.end.filename = &driver.file;
};

%token       <sval>      T_STRING
%token       <ival>      T_INTEGER

%token       <datatype>  T_TYPE_INT_32
%token       <sval>      T_IDENTIFIER
%token                   T_ASSIGN

%token       <sval>      T_FATAL_ERROR
%token                   T_NEWLINE
%token                   PRGEND 0     "end of file"

%union {
  int ival;
  FPTYPE datatype;
  std::string *sval;
  AST::AbstractNode   *abstract_node;
  AST::Stack          *stack;
}

%type <stack>         Expressions
%type <abstract_node> Expression Literal Assignment
%type <datatype>      DataTypes

%%

root:
   Expressions { driver.stack = $1; }
  ;

Expressions:
    Expression                        {
                                        std::vector<AST::AbstractNode *> nodes;
                                        nodes.push_back($1);
                                        $$ = new AST::Stack(nodes);
                                      }
  | Expressions Terminator Expression {
                                        $1->push_node($3);
                                        $$ = $1;
                                      }
  |                                   {}
  | Expressions Terminator            { $$ = $1; }
  ;

Expression:
    Literal
  | Assignment
  | Errors
  ;

Literal:
    T_STRING  { std::cout << "Found String: "  << *$1 << std::endl; $$ = fp_string_node($1); delete($1); }
  | T_INTEGER { std::cout << "Found Integer: " << $1 << std::endl;  $$ = fp_int32_node($1); }
  ;

DataTypes: T_TYPE_INT_32 { $$ = $1; }

Assignment:
    DataTypes T_IDENTIFIER T_ASSIGN Expression { $$ = fp_assignment_node($1, $2, $4); delete($2); }
  ;

Errors:
    T_FATAL_ERROR { error(yyla.location, *$1); delete($1); YYABORT; }
  ;

Terminator:
  T_NEWLINE
  ;

%%

void
FrontEnd::Parser::error(const location_type& l, const std::string& m )
{
  std::ifstream error_file ( *l.begin.filename );
  std::string line;
  int line_number = 1;
  int chars_read = 0;

  std::cout << "Errored" << std::endl;

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

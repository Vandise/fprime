#ifndef __SCANNER_HPP__
#define __SCANNER_HPP__ 1

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "parser.tab.hpp"
#include "location.hh"

typedef struct file_map {
  file_map *previous;
  file_map *next;
  std::string filename;
  int line;
  int column;
  int leng;
} file_map;

namespace FrontEnd {
  class Scanner : public yyFlexLexer {
    public:

      file_map                        *current_file = nullptr;

      Scanner(std::istream *in, std::string filename) : yyFlexLexer(in)
      {
        loc = new FrontEnd::Parser::location_type();
        fmap = { nullptr, nullptr, filename, 1, 1, 1 };
        current_file = &fmap;
      };

      virtual ~Scanner() {
        delete loc;
      };

      using FlexLexer::yylex;
      virtual int yylex( FrontEnd::Parser::semantic_type * const lval, FrontEnd::Parser::location_type *location );

    private:
      FrontEnd::Parser::semantic_type *yylval = nullptr;
      FrontEnd::Parser::location_type *loc    = nullptr;
      file_map                         fmap;
  };
}

#endif
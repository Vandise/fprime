#ifndef __SCANNER_HPP__
#define __SCANNER_HPP__ 1

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#include <fstream>
#endif

#include "parser.tab.hpp"
#include "location.hh"
#include "util/debug_new/debug_new.h"

typedef struct file_map {
  file_map *previous;
  file_map *next;
  std::ifstream *fp;
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
        fmap = new file_map();
        fmap->previous = nullptr; fmap->next = nullptr; fmap->fp = nullptr;
        fmap->filename = filename; fmap->line = 1; fmap->column = 1; fmap->leng = 1;
        current_file = fmap;
      };

      virtual ~Scanner() {
        current_file = fmap;
        while(1) {
          if(current_file->fp != nullptr) {
            current_file->fp->close();
            delete current_file->fp;
          }
          if(current_file->previous != nullptr) {
            delete current_file->previous;
          }
          if(current_file->next == nullptr) {
            break;
          }
          current_file = current_file->next;
        }
        delete current_file;
        delete loc;
      };

      using FlexLexer::yylex;
      virtual int yylex( FrontEnd::Parser::semantic_type * const lval, FrontEnd::Parser::location_type *location );

    private:
      FrontEnd::Parser::semantic_type *yylval = nullptr;
      FrontEnd::Parser::location_type *loc    = nullptr;
      file_map                        *fmap;
  };
}

#endif
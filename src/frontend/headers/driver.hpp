#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__ 1

#include <vector>
#include "frontend/scanner.hpp"
#include "frontend/parser.tab.hpp"
#include "ast/headers/stack.hpp"
#include "ast/headers/abstractnode.hpp"

namespace FrontEnd {
  class Driver {
    public:
      Driver() = default;
      virtual ~Driver();
      int parse( const char *filename );
      void push_stack( std::vector<AST::AbstractNode*> stack);
      void push_node( AST::AbstractNode *node);
      std::string file;
    private:
      FrontEnd::Parser  *parser  = nullptr;
      FrontEnd::Scanner *scanner = nullptr;
  };
}

#endif

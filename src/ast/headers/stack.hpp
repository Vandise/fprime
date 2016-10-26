#ifndef __AST_STACK_HPP
#define __AST_STACK_HPP 1

#include <vector>

namespace AST {
  class AbstractNode;
  class Stack
  {
    public:
      static std::vector<AST::AbstractNode*> nodes;
  };
}

#endif

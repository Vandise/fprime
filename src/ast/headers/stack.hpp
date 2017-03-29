#pragma once

#ifndef __AST_STACK
#define __AST_STACK 1

#include <vector>
#include "abstractnode.hpp"

namespace AST {
  class AbstractNode;
  class Stack : public AbstractNode
  {
    public:
      Stack(std::vector<AST::AbstractNode*> nodes);
      virtual ~Stack();
      virtual void compile();
      int stack_size();
      void push_node(AST::AbstractNode *node);
      void push_nodes(std::vector<AST::AbstractNode*> nodes);
    private:
      std::vector<AST::AbstractNode*> nodes;
  };
}

#endif
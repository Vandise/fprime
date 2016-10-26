#pragma once

#ifndef __AST_LITERALNODE
#define __AST_LITERALNODE 1

#include "abstractnode.hpp"
#include <string>

namespace AST {
  class AbstractNode;
  class LiteralNode : public AbstractNode {
    public:
      LiteralNode();
      LiteralNode(int value);
      LiteralNode(std::string value);
      virtual ~LiteralNode();
      virtual void compile();
    private:
      int         int_value;
      std::string string_value;
  };
}

#endif
#pragma once

#ifndef __AST_LITERALNODE
#define __AST_LITERALNODE 1

#include <string>
#include "abstractnode.hpp"
#include "common/fprime.hpp"

namespace AST {
  class AbstractNode;
  class LiteralNode : public AbstractNode {
    public:
      LiteralNode();
      LiteralNode(int value, FPTYPE type);
      LiteralNode(std::string value, FPTYPE type);
      virtual ~LiteralNode();
      virtual void compile();
    private:
      FPTYPE      data_type;
      int         int_value;
      std::string string_value;
  };
}

#endif
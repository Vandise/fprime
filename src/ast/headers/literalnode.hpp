#pragma once
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

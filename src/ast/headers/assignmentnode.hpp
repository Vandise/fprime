#pragma once

#ifndef __AST_ASSIGNMENTNODE
#define __AST_ASSIGNMENTNODE 1

#include <string>
#include "abstractnode.hpp"
#include "common/fprime.hpp"

namespace AST {
  class AbstractNode;
  class AssignmentNode : public AbstractNode {
    public:
      AssignmentNode(FPTYPE type, std::string identifier, AST::AbstractNode *expression);
      virtual ~AssignmentNode();
      virtual void compile(Generator::CodeGenerator *cg);
    private:
      FPTYPE      data_type;
      std::string identifier;
      AST::AbstractNode *expression;
  };
}

#endif

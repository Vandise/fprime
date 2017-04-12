#include "headers/assignmentnode.hpp"
#include "util/debug_new/debug_new.h"

#include <iostream>

AST::AssignmentNode::AssignmentNode(FPTYPE type, std::string identifier, AST::AbstractNode *expression)
{
  this->data_type = type;
  this->identifier = identifier;
  this->expression = expression;
}

AST::AssignmentNode::~AssignmentNode()
{
  std::cout << "Destructor - Assignment Node" << std::endl;
  delete(this->expression);
}

void
AST::AssignmentNode::compile(Generator::CodeGenerator *cg)
{
  std::cout << "Assigning " << this->identifier << " type " << this->data_type << std::endl;
}

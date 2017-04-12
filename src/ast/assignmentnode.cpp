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
  this->expression->compile(cg);
  cg->context_manager->get_current_frame()->set_literal_value(
    this->identifier,
    cg->context_manager->get_current_frame()->pop_stack()
  );
  std::cout << "The assigned value is: " << cg->context_manager->get_current_frame()->get_literal_value(this->identifier) << std::endl;
  std::cout << "Assigning " << this->identifier << " type " << this->data_type << std::endl;
}

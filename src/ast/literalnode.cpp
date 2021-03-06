#include "headers/literalnode.hpp"
#include "util/debug_new/debug_new.h"

#include <iostream>

AST::LiteralNode::LiteralNode()
{

}

AST::LiteralNode::LiteralNode(int value, FPTYPE type)
{
  data_type = type;
  int_value = value;
}

AST::LiteralNode::LiteralNode(std::string value, FPTYPE type)
{
  data_type = type;
  string_value = value;
}

AST::LiteralNode::~LiteralNode()
{
  std::cout << "Destructor - Literal Node" << std::endl;
}

void
AST::LiteralNode::compile(Generator::CodeGenerator *cg)
{
  std::string frame_label = cg->context_manager->get_current_frame()->get_label();
  switch(data_type) {
    case INT_32:
      std::cout << "Compiling Type: " << data_type << " with value: " << int_value << " in frame " << frame_label << std::endl;
      cg->context_manager->get_current_frame()->push_stack(int_value);
      break;
    case INT_64:
      break;
    case STRING:
      std::cout << "Compiling Type: " << data_type << " with value: " << string_value  << " in frame " << frame_label << std::endl;
      break;
    default:
      std::cout << "Compiling node" << std::endl;
      break;
  }
}

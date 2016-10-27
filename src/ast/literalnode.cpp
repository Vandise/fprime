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
AST::LiteralNode::compile()
{
  switch(data_type) {
    case INT_32:
      std::cout << "Compiling Type: " << data_type << " with value: " << int_value << std::endl;
      break;
    case INT_64:
      break;
    default:
      std::cout << "Compiling node" << std::endl;
      break;
  }
}
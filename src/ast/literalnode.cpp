#include "headers/literalnode.hpp"
#include "util/debug_new/debug_new.h"

AST::LiteralNode::LiteralNode()
{

}

AST::LiteralNode::LiteralNode(int value)
{
  int_value = value;
}

AST::LiteralNode::LiteralNode(std::string value)
{
  string_value = value;
}



AST::LiteralNode::~LiteralNode()
{

}

void
AST::LiteralNode::compile()
{
  
}

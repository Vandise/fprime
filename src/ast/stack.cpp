#include "headers/stack.hpp"
#include "util/debug_new/debug_new.h"

AST::Stack::Stack(std::vector<AST::AbstractNode*> nodes)
{
  this->nodes = nodes;
}

AST::Stack::~Stack()
{
  for (auto &n : nodes)
  {
    delete(n);
  }
}

void
AST::Stack::compile()
{
  for (auto &n : nodes)
  {
    n->compile();
  }
}

void
AST::Stack::push_node(AST::AbstractNode *node)
{
  nodes.push_back(node);
}

void
AST::Stack::push_nodes(std::vector<AST::AbstractNode*> nodes)
{
  for (auto &n : nodes)
  {
    nodes.push_back(n);
  }
}
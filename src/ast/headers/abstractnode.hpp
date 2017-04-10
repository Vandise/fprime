#pragma once
#ifndef __AST_ABSTRACTNODE_HPP
#define __AST_ABSTRACTNODE_HPP 1

#include <iostream>
#include "generator/headers/contextManager.hpp"

namespace AST {
  class AbstractNode
  {
    public:
      virtual void compile(Generator::ContextManager *context) = 0;
      virtual ~AbstractNode(){ std::cout << "Desctrutor - AbstractNode" << std::endl; };
  };
}

#endif
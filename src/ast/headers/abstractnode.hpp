#pragma once
#ifndef __AST_ABSTRACTNODE_HPP
#define __AST_ABSTRACTNODE_HPP 1

namespace AST {
  class AbstractNode
  {
    public:
      virtual void compile() = 0;
  };
}

#endif

#ifndef __CODE_GENERATOR_HPP__
#define __CODE_GENERATOR_HPP__ 1

#include "generator/headers/contextManager.hpp"

namespace Generator
{
  class CodeGenerator
  {
    public:
      Generator::ContextManager *context_manager;

    public:
      CodeGenerator();
      virtual ~CodeGenerator();
  };
}

#endif
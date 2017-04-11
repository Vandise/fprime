#ifndef __CODE_GENERATOR_HPP__
#define __CODE_GENERATOR_HPP__ 1

#include "generator/headers/contextManager.hpp"
#include "generator/headers/sectionManager.hpp"

namespace Generator
{
  class CodeGenerator
  {
    public:
      Generator::ContextManager *context_manager;
      Generator::SectionManager *section_manager;

    public:
      CodeGenerator();
      virtual ~CodeGenerator();
  };
}

#endif
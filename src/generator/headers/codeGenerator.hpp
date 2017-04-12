#ifndef __CODE_GENERATOR_HPP__
#define __CODE_GENERATOR_HPP__ 1

#include <string>

#include "generator/headers/contextManager.hpp"
#include "generator/headers/sectionManager.hpp"

namespace Generator
{
  class CodeGenerator
  {
    private:
      std::string line_buffer = "";

    public:
      Generator::ContextManager *context_manager;
      Generator::SectionManager *section_manager;

    public:
      CodeGenerator();
      virtual ~CodeGenerator();
  };
}

#endif
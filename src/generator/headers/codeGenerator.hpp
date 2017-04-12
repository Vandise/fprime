#ifndef __CODE_GENERATOR_HPP__
#define __CODE_GENERATOR_HPP__ 1

#define INSTRUCTION_PADDING = 10

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
      void emit_instruction();
      void emit_dword_indirect(
        std::string base_reg = "",
        std::string index = "",
        int scale = -1,
        int disp = -1,
        bool add_base_reg = true,
        bool add_displacement = true);
  };
}

#endif
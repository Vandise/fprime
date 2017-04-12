#ifndef __CODE_GENERATOR_HPP__
#define __CODE_GENERATOR_HPP__ 1

#define INSTRUCTION_PADDING = 10

#include <string>

#include "common/fprime.hpp"
#include "generator/headers/contextManager.hpp"
#include "generator/headers/sectionManager.hpp"

namespace Generator
{
  class CodeGenerator
  {
    public:
      std::string asm_registers[64] = {
        "rax", "rbx", "rcx", "rdx", "rbp", "rsp", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15",
        "eax", "ebx", "ecx", "edx", "epb", "esp", "esi", "edi", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d",
        "ax", "bx", "cx", "dx", "si", "di", "bp", "sp", "r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w",
        "al", "bl", "cl", "dl", "sil", "dil", "bpl", "spl", "r8b", "r9b", "r10b", "r11b", "r12b", "r13b", "r14b", "r15b"
      };
      std::string instructions[1] = {
        "mov"
      };

    private:
      std::string line_buffer = "";

    public:
      Generator::ContextManager *context_manager;
      Generator::SectionManager *section_manager;

    public:
      CodeGenerator();
      virtual ~CodeGenerator();
      void push_buffer(std::string b);
      void push_line();
      std::string reg(FP_REGISTERS r);
      std::string instruction(FP_INSTRUCTIONS i);
      std::string dword_indirect(
        std::string base_reg = "",
        std::string index = "",
        int scale = -1,
        int disp = -1,
        bool add_base_reg = true,
        bool add_displacement = true);
  };
}

#endif
#include "headers/codeGenerator.hpp"


#include <iostream>
#include <string>

Generator::CodeGenerator::~CodeGenerator()
{
  delete(this->context_manager);
  delete(this->section_manager);
}

Generator::CodeGenerator::CodeGenerator()
{
  this->context_manager = new Generator::ContextManager();
  this->section_manager = new Generator::SectionManager();
}

void
Generator::CodeGenerator::emit_instruction()
{
  /* TODO */
}

void
Generator::CodeGenerator::emit_dword_indirect(std::string base_reg, std::string index, int scale, int disp, bool add_base_reg, bool add_displacement)
{
  std::string line = "";
  line += "dword";
  line += " [";
    if (base_reg != "") {
      line += base_reg;
      if(add_base_reg) {
        line += "+";
      } else {
        line += "-";
      }
    }
    if(index != "") {
      line += index;
    }
    if(scale != -1) {
      line += "*" + std::to_string(scale);
    }
    if(disp != -1) {
      if(add_displacement) {
        line += "+";
      } else {
        line += "-";
      }
      line += std::to_string(disp);
    }
  line += "]";
  std::cout << line << std::endl;
}
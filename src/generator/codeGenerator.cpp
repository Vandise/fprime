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

  this->start_frame("main");
}


void
Generator::CodeGenerator::start_frame(std::string label)
{
  this->context_manager->next_frame(label);
  EMIT_FRAME_START(this);
}

void
Generator::CodeGenerator::exit_frame()
{
  this->context_manager->exit_frame();
  EMIT_FRAME_EXIT(this);
}


void
Generator::CodeGenerator::push_buffer(std::string b)
{
  this->line_buffer += b;
}

void
Generator::CodeGenerator::push_line()
{
  this->line_buffer += "\n";
  std::cout << this->line_buffer << std::endl;
}

std::string
Generator::CodeGenerator::reg(FP_REGISTERS r)
{
  return this->asm_registers[r];
}

std::string
Generator::CodeGenerator::instruction(FP_INSTRUCTIONS i)
{
  int padding = 8;
  std::string instruction = this->instructions[i];
  instruction.insert(instruction.size(), padding - instruction.size(), '\0');
  return instruction;
}

std::string
Generator::CodeGenerator::dword_indirect(std::string base_reg, std::string index, int scale, int disp, bool add_base_reg, bool add_displacement)
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
      if(index != "") {
        line += "*" + std::to_string(scale);
      } else {
        line += std::to_string(scale) + "*";
      }
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

  return line;
}
#include "headers/codeGenerator.hpp"

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
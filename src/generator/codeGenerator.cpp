#include "headers/codeGenerator.hpp"

Generator::CodeGenerator::~CodeGenerator()
{
  delete(this->context_manager);
}

Generator::CodeGenerator::CodeGenerator()
{
  this->context_manager = new Generator::ContextManager();
}
#include "headers/frame.hpp"

Generator::Frame::~Frame()
{

}

Generator::Frame::Frame(std::string label)
{
  this->label = label;
}

std::string
Generator::Frame::get_label()
{
  return label;
}

int
Generator::Frame::get_literal_value(std::string literal)
{
  if (this->literal_reference.count(literal)) {
    return this->literal_reference.at(literal);
  }
  return 0;
}

void
Generator::Frame::set_literal_value(std::string literal_name, int value)
{
  this->literal_values.push_back(value);
  this->literal_reference[literal_name] = this->literal_values.back();
}

std::vector<int>
Generator::Frame::get_literal_values()
{
  return this->literal_values;
}

std::map<std::string, int>
Generator::Frame::get_literal_references()
{
  return this->literal_reference;
}

void
Generator::Frame::push_instruction(std::string instruction)
{
  this->instructions.push_back(instruction);
}

std::vector<std::string>
Generator::Frame::get_instructions()
{
  return this->instructions;
}
#include "headers/frame.hpp"

#include <iostream>
#include <string>

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
Generator::Frame::get_literal_value(std::string identifier)
{
  if (this->literal_reference.count(identifier)) {
    int offset = this->literal_reference[identifier];
    return this->literal_values[offset];
  }
  return 0;
}

/*
  Stores the offset of the identifier value in literal_values
*/
void
Generator::Frame::set_literal_value(std::string literal_name, int value)
{
  this->literal_values.push_back(value);
  this->literal_reference[literal_name] = (this->literal_values.size() - 1);
}

int
Generator::Frame::get_literal_offset(std::string identifier)
{
  if (this->literal_reference.find(identifier) != this->literal_reference.end()) {
    return this->literal_reference.at(identifier);
  }
  return -1;
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

/* TODO: struct will be used for each datatype */
void
Generator::Frame::push_stack(int value)
{
  this->stack.push_back(value);
}

int
Generator::Frame::pop_stack()
{
  int value = this->stack.back();
  this->stack.pop_back();
  return value;
}
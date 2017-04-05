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
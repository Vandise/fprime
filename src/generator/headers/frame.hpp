#ifndef __FRAME_HPP__
#define __FRAME_HPP__ 1

#include <map>
#include <vector>
#include <string>
#include <stack>

/*
  Frame Container
    TODO: literal values vector will be a class yet to be defined
*/
namespace Generator
{
  class Frame
  {
    private:
      std::vector<int> literal_values;
      std::map<std::string, int> literal_reference;
      std::vector<std::string> instructions;
      std::string label;
      std::stack<int> stack;

    public:
      Frame(std::string label);
      virtual ~Frame();
      std::string get_label();
      std::vector<int> get_literal_values();
      std::map<std::string, int> get_literal_references();
      int get_literal_offset(std::string identifier);
      int get_literal_value(std::string literal);
      void set_literal_value(std::string literal_name, int value);
      void push_instruction(std::string instruction);
      std::vector<std::string> get_instructions();
      void push_stack(int value);
      int  pop_stack();
  };
}

#endif
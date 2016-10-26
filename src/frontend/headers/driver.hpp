#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__ 1

#include <string>
#include <cstdint>
#include <vector>
#include "frontend/headers/scanner.hpp"
#include "frontend/parser.tab.hpp"

namespace FrontEnd
{

  class Driver
  {
    public:
       std::string file;
       Driver() = default;
       virtual ~Driver();
       void parse( const char *filename );
       void push_stack();
       void push_node();

    private:
       FrontEnd::Parser  *parser  = nullptr;
       FrontEnd::Scanner *scanner = nullptr;
  };

}
#endif
#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__ 1

#include "frontend/scanner.hpp"
#include "frontend/parser.tab.hpp"

namespace FrontEnd {

  class Driver {
    public:
      Driver() = default;
      virtual ~Driver();
      void parse( const char *filename );
    private:
      FrontEnd::Parser  *parser  = nullptr;
      FrontEnd::Scanner *scanner = nullptr;
  };

}

#endif

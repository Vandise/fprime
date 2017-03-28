#include <iostream>
#include <cstdlib>
#include "frontend/headers/driver.hpp"
#include "util/debug_new/debug_new.h"

int
main( const int argc, const char **argv )
{
  int parse_result;
  if(argc != 2)
    return ( EXIT_FAILURE );

  FrontEnd::Driver driver;
  parse_result = driver.parse( argv[1] );
  if (parse_result == 0) {
    driver.stack->compile();
  }
  return 1;
}
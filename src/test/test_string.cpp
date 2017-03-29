#include "headers/common.hpp"

SCENARIO("Compiling Strings", "[stack]")
{

  FrontEnd::Driver driver;
  const char *filename = "test/string/primitive.src";

  WHEN("A string is parsed")
  {
    driver.parse(filename);
    THEN("It should be pushed onto the node-stack tree")
    {
      REQUIRE(driver.stack->stack_size() == 1);
    }
  }
}
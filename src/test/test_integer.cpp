#include "headers/common.hpp"

SCENARIO("Compiling Integers", "[stack]")
{

  FrontEnd::Driver driver;
  const char *filename = "test/integer/primitive.src";

  WHEN("An integer is parsed")
  {
    driver.parse(filename);
    THEN("It should be pushed onto the node-stack tree")
    {
      REQUIRE(driver.stack->stack_size() == 1);
    }
  }
}
#include "headers/common.hpp"

SCENARIO("Compiling Imports", "[stack]")
{

  FrontEnd::Driver driver;
  const char *filename = "test/imports/main.src";

  WHEN("An include is parsed")
  {
    driver.parse(filename);
    THEN("The main and imported file nodes are pushed onto the node-stack tree")
    {
      REQUIRE(driver.stack->stack_size() == 2);
    }
  }
}
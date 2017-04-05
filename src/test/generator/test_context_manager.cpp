#include "../headers/common.hpp"

SCENARIO("Context Manager", "[Generator::ContextManager]")
{
  Generator::ContextManager cm = Generator::ContextManager();
  WHEN("The manager is initialized")
  {
    THEN("It should push a frame labeled 'main' onto the heap")
    {
      REQUIRE(cm.get_current_frame()->get_label() == "main");
    }
  }

}
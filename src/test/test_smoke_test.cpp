#include "headers/common.hpp"

SCENARIO("CATCH", "[null]")
{

  WHEN("A test is run")
  {
    THEN("It should pass")
    {
      REQUIRE(2== 2);
    }
  }

}
#include "../headers/common.hpp"

SCENARIO("Frame", "[Generator::Frame]")
{

  std::string label = std::string("main");
  Generator::Frame f = Generator::Frame(label);

  WHEN("The frame is initialized")
  {
    THEN("It should set the frame label")
    {
      REQUIRE(f.get_label() == label);
    }
  }

  WHEN("A literal value is set")
  {
    THEN("It should map the value to the literals vector")
    {
      int value = 10;
      std::string decade = "decade";
      f.set_literal_value(decade, value);
      REQUIRE(f.get_literal_value(decade) == value);
    }
    THEN("It should push the value to the literal_values vector")
    {
      int value = 10;
      f.set_literal_value("decade", value);
      REQUIRE(f.get_literal_values().back() == value);
    }
  }
}
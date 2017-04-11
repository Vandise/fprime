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

  WHEN("A frame instruction is pushed")
  {
    THEN("It should be pushed to the instructions vector")
    {
      std::string instruction = "mov 10, rax";
      f.push_instruction(instruction);
      REQUIRE(f.get_instructions().size() == 1);
      REQUIRE(f.get_instructions().back() == instruction);
    }
  }
}
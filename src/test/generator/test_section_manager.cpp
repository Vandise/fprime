#include "../headers/common.hpp"

SCENARIO("Section Manager", "[Generator::SectionManager]")
{
  WHEN("The manager is initialized")
  {
    Generator::SectionManager sm = Generator::SectionManager();
    THEN("It should initialize a text, bss, and data section")
    {
      REQUIRE(sm.get_sections().count("text") == 1);
      REQUIRE(sm.get_sections().count("bss") == 1);
      REQUIRE(sm.get_sections().count("data") == 1);
    }
  }
  WHEN("Pushing a line to a specified section")
  {
    Generator::SectionManager sm = Generator::SectionManager();
    THEN("The line should exist in the section")
    {
      std::string line = "msg: db \"hello world\",10";
      sm.push_section("data", line);
      REQUIRE(sm.get_sections()["data"].back() == line);
    }
  }
}
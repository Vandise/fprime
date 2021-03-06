#include "../headers/common.hpp"

SCENARIO("Context Manager", "[Generator::ContextManager]")
{
  WHEN("The manager is initialized")
  {
    Generator::ContextManager cm = Generator::ContextManager();
    THEN("The frame heap should be empty")
    {
      REQUIRE(cm.frame_heap_size() == 0);
    }
  }
  GIVEN("The frame heap is not full")
  {
    Generator::ContextManager cm = Generator::ContextManager();
    WHEN("Shifting to the next frame")
    {
      THEN("The new frame is pushed onto the heap")
      {
        int result = cm.next_frame(std::string("main"));
        result = cm.next_frame(std::string("my_function_scope"));
        REQUIRE(result == 1);
        REQUIRE(cm.frame_heap_size() == 2);
        REQUIRE(cm.get_current_frame()->get_label() == "my_function_scope");
      }
    }
  }
  GIVEN("The frame heap is full")
  {
    Generator::ContextManager cm = Generator::ContextManager();
    for (int i = 0; i <= HEAP_FRAME_SIZE; i++)
    {
      cm.next_frame(std::to_string(i));
    }
    WHEN("Shifting to the next frame")
    {
      THEN("It should fail to push the frame onto the stack")
      {
        int result = cm.next_frame(std::string("my_function_scope"));
        REQUIRE(result == 0);
        REQUIRE(cm.frame_heap_size() == HEAP_FRAME_SIZE);
      }
    }
  }
  GIVEN("On the main frame")
  {
    Generator::ContextManager cm = Generator::ContextManager();
    WHEN("Exiting the current frame")
    {
      THEN("It should return a truthy value")
      {
        cm.next_frame(std::string("main"));
        int result = cm.exit_frame();
        REQUIRE(result == 1);
      }
    }
  }
  GIVEN("There is no current frame")
  {
    Generator::ContextManager cm = Generator::ContextManager();
    WHEN("Exiting the current frame")
    {
      THEN("It should return 0")
      {
        cm.exit_frame(); // exit main
        int result = cm.exit_frame();
        REQUIRE(result == 0);
      }
    }
  }
}
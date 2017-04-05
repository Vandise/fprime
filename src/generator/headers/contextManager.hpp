#ifndef __CONTEXTMANAGER_HPP__
#define __CONTEXTMANAGER_HPP__ 1

#define HEAP_FRAME_SIZE 50

#include <string>
#include <vector>
#include "frame.hpp"

/*
  Context Manager (frames)
*/
namespace Generator
{
  class ContextManager
  {
    private:
      std::vector<Frame*> frame_heap;

    public:
      ContextManager();
      virtual ~ContextManager();
      int frame_heap_size();
      int exit_frame();
      int next_frame(std::string label);
      Generator::Frame* get_current_frame();
  };
}

#endif
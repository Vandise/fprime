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
      Generator::Frame* get_current_frame();
  };
}

#endif
#ifndef __CONTEXTMANAGER_HPP__
#define __CONTEXTMANAGER_HPP__ 1

#define HEAP_FRAME_SIZE 50
#define INITIAL_FRAME    0

#include <string>
#include <vector>

/*
  Context Manager (frames)
*/
namespace Generator
{
  class Frame;

  class ContextManager
  {
    private:
      std::vector<Frame*> frame_heap;

    public:
      ContextManager();
      virtual ~ContextManager();
  };
}

#endif
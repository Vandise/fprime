#include "headers/contextManager.hpp"

Generator::ContextManager::~ContextManager()
{
  for (std::vector<Frame*>::iterator frame = frame_heap.begin() ; frame != frame_heap.end(); ++frame)
  {
    delete (*frame);
  }
  frame_heap.clear();
}

Generator::ContextManager::ContextManager()
{
  // frame_heap.push_back(new Frame(std::string("main")));
}

int
Generator::ContextManager::frame_heap_size()
{
  return frame_heap.size();
}

int
Generator::ContextManager::next_frame(std::string label)
{
  if (frame_heap_size() + 1 > HEAP_FRAME_SIZE) {
    // scope level too deep
    return 0;
  }
  frame_heap.push_back(new Frame(label));
  return 1;
}

int
Generator::ContextManager::exit_frame()
{
  if (frame_heap.empty()) {
    // exiting main scope
    return 0;
  }
  delete (frame_heap.back());
  frame_heap.pop_back();
  return 1;
}

Generator::Frame*
Generator::ContextManager::get_current_frame()
{
  return frame_heap.back();
}
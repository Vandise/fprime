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
  frame_heap.push_back(new Frame(std::string("main")));
}

Generator::Frame*
Generator::ContextManager::get_current_frame()
{
  return frame_heap.back();
}
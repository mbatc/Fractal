#include "flInterface.h"

using namespace flEngine;

Interface::Interface()
  : m_refCount(1) // Default to 1 for the creator
{}

Interface::~Interface() {}

void Interface::DecRef()
{
  if (this != nullptr && --m_refCount == 0)
    Destroy();
}

void Interface::Destroy()
{
  flDelete this;
}

void flEngine::Interface::IncRef()
{
  if (this != nullptr)
    ++m_refCount;
}

int64_t Interface::GetReferenceCount() const
{
  return this != nullptr ? m_refCount : 0;
}

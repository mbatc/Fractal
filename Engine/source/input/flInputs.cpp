#include "input/flInputs.h"

using namespace flEngine;
using namespace flEngine::Input;

void Inputs::Update()
{
  int64_t deviceCount = InputDevice::GetRegisteredDeviceCount();
  for (int64_t i = 0; i < deviceCount; ++i)
    InputDevice::GetRegisteredDevice(i)->Update();
}

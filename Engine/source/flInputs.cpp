#include "flInputs.h"

namespace Fractal
{
  void Inputs::Update()
  {
    int64_t deviceCount = InputDevice::GetRegisteredDeviceCount();
    for (int64_t i = 0; i < deviceCount; ++i)
      InputDevice::GetRegisteredDevice(i)->Update();
  }
}
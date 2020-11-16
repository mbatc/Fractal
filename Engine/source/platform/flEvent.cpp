#include "platform/flEvent.h"
#include <string.h>

using namespace flEngine::Platform;

void flCCONV flEngine::Platform::Event_Create(flOUT Event *pEvent, flIN void *pData, void (*DestroyFunc)(Event*))
{
  memset(pEvent, 0, sizeof(Event));
  pEvent->userEvent.pData = pData;
  pEvent->userEvent.DestroyFunc = DestroyFunc;
}

void flCCONV flEngine::Platform::Event_Destroy(flIN flOUT Event *pEvent)
{
  // Destroy built-in event types
  switch (pEvent->id)
  {
  case E_Wnd_Create:
    pEvent->wndCreate.name; // delete this
    break;
  }

  // If this is a user event and it has a destroy function, call that
  if (pEvent->type == E_Type_User && pEvent->userEvent.DestroyFunc)
    pEvent->userEvent.DestroyFunc(pEvent);

  memset(pEvent, 0, sizeof(Event));
}

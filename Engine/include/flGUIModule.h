#pragma once

#include "flInterface.h"
#include "flModule.h"

namespace Fractal
{
  class Panel;

  class Impl_GUIModule;

  class flEXPORT GUIModule : public Module
  {
    flPIMPL_DEF(GUIModule);

  public:
    typedef void (*MenuCommandFunc)();

    GUIModule();

    /**
     * @brief Open a new panel in the GUI.
     *
     * T must be a subclass of Panel, and it's constructor must take a GUISystem* as the first parameter.
     *
     * Arguments passed to this function are forwarded to T's constructor following the GUISystem*.
     */
    template<typename T, typename... Args>
    void Open(Args&& ... args)
    {
      Open(MakeRef(flNew(flAllocT(T, 1)) T(this, std::forward<Args>(args)...), false).Get());
    }

    /**
     * @brief Add a command to the menu bar.
     *
     * @param [in] name The command path.
     * @param [in] func The command function to call.
     */
    void AddMenuItem(flIN char const* name, flIN MenuCommandFunc func);

    virtual void OnUpdate() override;
    virtual void OnRender() override;

    virtual bool OnStartup() override;
    virtual void OnShutdown() override;

    virtual void OnPreUpdate() override;
    virtual void OnPreRender() override;

    virtual void OnPostUpdate() override;
    virtual void OnPostRender() override;

    virtual bool OnKeyState(Event* pEvent) override;
    virtual bool OnMouseState(Event* pEvent) override;
    virtual bool OnMouseScroll(Event* pEvent) override;

  protected:
    void Open(Panel* pPanel);
  };
}

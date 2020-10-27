# Fractal

Game engine project

## Engine Programming Guide

### Public API

This section describes the prefered practices when adding components to the public API of the engine.

Public interfaces should be designed in such a way to maintain a stable Application Binary Interface. This is neccessary to improve compatibility between different C++ compilers. This is a driving factor for the design desicions detailed below.

The public API should also attempt to hide the internal implementation details as best as possible by minimising the number of external includes.

#### Functions

Public global functions should be exported using the `flEXPORT` define.

However, where appropriate inlining functions should be prefered (for example single line functions) to reduce overhead when calling them. Implementations should be placed in an `.inl` file with the same name as the header.

#### Classes

Wherever possible, components should follow the OOP Factory design pattern. This should be done using a pure virtual base class to define the interface in the public API, and a derived class which implements that interface.

A factory function should also be declared in the interface for the implementation do implement. Both the interface, and the factor function should be exported using the `flEXPORT` define.

For example,
```
// flUtil_Example.h (Public interface header)

namespace flEngine
{ // Namespaces should be used so the global namespace is not polluted
  namespace Util
  {
    class flEXPORT Example // Notice the interface is exported in the DLL
    {
    public:
      virtual void MemberA() = 0;
      virtual void MemberB() = 0;
    };
  };
};

...

// Example_Impl.h (Implementation class header)

#include "flUtil_Example.h"

namespace flEngine
{
  namespace Util
  {
    // Implementations of interfaces are prefixed with Impl_
    class Impl_Example : public Example // Notice the implementation is not exported so can be implemented using any available tools/libs
    {
    public:
      virtual void MemberA() override;
      virtual void MemberB() override;
    };
  }
}

...

// Example_Impl.cpp (Implementation source file) 

#include "flUtil_Example_Impl.h"

using namespace flEngine::Util; // Using statement for readability

void Impl_Example::MemberA() { printf("Hello from MemberA()\n"); }
void Impl_Example::MemberB() { printf("Hello from MemberA()\n"); } 
      
```

#### Templated APIs

Public template class and functions are not 

#### Performance Critical Components

Components in which performance is a key consideration should be implemented using C style opaque pointers.

#### Documentation

Doxygen is used to generate the documentation for the project. As a result, all functions exposed in the public API should be commented using Javadoc comments.

### Cross-Platform

Public API components should be platform independent. Platform specifics can be exposed, but the API's should work without needing these to be used.

Platform specific code should always be wrapped in `#ifdef flUSING(platform) ... #endif`, where `platform` is the appropriate `flPLATFORM_*` define (e.g. flPLATFORM_WINDOWS).

#### Member Function Implementations

When an interface implementation requires platform specific code, the implementations should generally be placed in separate files. These files should have the platform as a suffix. Shared code in an implementation can be placed in a single file. For example, a cross platform implementation of a Platorm::Window class may have the files,

* flPlatform_Window.h              (public API header)
* flPlatform_Window_Impl.h         (internal implementation)
* flPlatform_Window_Impl.cpp       (implementation of functions shared by all platforms)
* flPlatform_Window_Impl_Win32.cpp (implementation of Windows specific code)
* flPlatform_Window_Impl_Linux.cpp (implementation of Linux specific code)

Although there are plenty of files, this will help to keep implementation details for each platform well separated and easier to follow.

However, if only a small section of the implementation is platform specific (e.g. a single function), it can be placed in the same file in a function.

#### Member Variables and Nested Structs/Classes

Platform specific member variables and nested structs or classes should be declared in the internal implementation header within the appropriate `#ifdef`. If different members are required for multiple platforms, this should be do using `#ifdef flUSING(pltfm1) ... #elif flUSING(pltfm2) ... #endif`. All platform specific members should be group together within the same protection level (`public`, `protected` or `private`) where possible.

#### Example

```
// flPlatform_SomeSpecifics.h

namespace flEngine
{
  namespace Platform
  {
    class SomeSpecifics : public Interface
    {
    public:
      virtual void Foo();
      virtual void Bar();
    }
  }
}

...

// flPlatform_SomeSpecifics_Impl.h

#include "flPlatform_SomeSpecifics.h"

namespace flEngine
{
  namespace Platform
  {
    class Impl_SomeSpecifics : public SomeSpecifics
    {
    public:
      virtual void Foo();
      virtual void Bar();
      virtual void Shared();

    protected:
      #if flUSING(flPLATFORM_WINDOWS)

      // Windows specific protected members

      #elif flUSING(flPLATFORM_LINUX)

      // Linux specific protected members

      #endif
      
    private:
      #if flUSING(flPLATFORM_WINDOWS)

      // Windows specific private members

      #elif flUSING(flPLATFORM_LINUX)

      // Linux specific private members

      #endif
    }
  }
}

...

// flPlatform_SomeSpecifics_Impl.cpp (Shared implementation of SomeSpecifics)

#if flUSING(flPLATFORM_WINDOWS)

#include "flPlatform_SomeSpecifics_Impl.h"

using namespace flEngine::Platform;

SomeSpecifics* SomeSpecifics::Create() { return flNew Impl_SomeSpecifics; }

void Impl_SomeSpecifics::Shared() { /*Shared implementation*/ }

#endif

...

// flPlatform_SomeSpecifics_Impl_Win32.cpp (Windows implementation of SomeSpecifics)

#if flUSING(flPLATFORM_WINDOWS)

#include "flPlatform_SomeSpecifics_Impl.h"

using namespace flEngine::Platform;

void Impl_SomeSpecifics::Foo() { /*Some Windows code*/ }
void Impl_SomeSpecifics::Bar() { /*Some more Windows code*/ }

#endif
...

// flPlatform_SomeSpecifics_Impl_Linux.cpp (Linux implementation of SomeSpecifics)

#if flUSING(flPLATFORM_LINUX)

#include "flPlatform_SomeSpecifics_Impl.h"

using namespace flEngine::Platform;

void Impl_SomeSpecifics::Foo() { /*Some Linux code*/ }
void Impl_SomeSpecifics::Bar() { /*Some more Linux code*/ }

#endif

```
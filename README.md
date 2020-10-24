# Fractal

Game engine project

## Engine Programming Guide

### Public Interfaces

Public interfaces should be designed in such a way to maintain the Application Binary Interface. This is neccessary to improve compatibility between C++ compilers. This section describes the prefered practices for this

#### General

Wherever possible, components should follow the OOP Factory design pattern. This should be done using a pure virtual base class to define the interface in the public API, and a derived class which implements that interface.

A factory function should also be declared in the interface for the implementation do implement. Both the interface, and the factor function should be exported using the `flEXPORT` define.

For example,
```
// Example.h (Public interface header)

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

#include "Example.h"

namespace flEngine
{
  namespace Util
  {
    namespace Impl
    {
      class Example // Notice the implementation is not exported - can be implemented using any available tools/libs
      {
      public:
        virtual void MemberA() override;
        virtual void MemberB() override;
      };
    }
  }
}

...

// Example_Impl.cpp (Implementation source file) 

using namespace flEngine::Util::Impl; // Using statement for readability

void Example::MemberA() { printf("Hello from MemberA()\n"); }
void Example::MemberB() { printf("Hello from MemberA()\n"); } 
      
```

#### Templated APIs

Public template class and functions are not 

#### Performance Critical Components

Components in which performance is a key consideration should be implemented using C style opaque pointers.

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

#### Documentation

Doxygen is used to generate the documentation for the project. As a result, all functions exposed in the public API should be commented using Javadoc comments.
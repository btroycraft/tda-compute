#include <cstlib>
#include <cstdint>

#include "VecCompr.hpp"

// Destructor for the VecCompr class

VecCompr::~VecCompr()
{
  std::free(init_);
}

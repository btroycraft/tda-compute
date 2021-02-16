#include <cstlib>
#include <cstdint>

#include "VecCompr.hpp"
#include "_Index.hpp"

// Constructor for the _Index proxy

VecCompr::_Index::_Index(uint_vec_compr_t *init, Index index)
  : init_(init), index(index)
{}

#ifndef _INDEX_HPP
#define _INDEX_HPP

#include "VecCompr.hpp"

// Define the proxy _Index object

class VecCompr::_Index{
  uint_vec_compr_t *init_;
  Index index_;
  operator=(uint_vec_compr_t);
};

#endif

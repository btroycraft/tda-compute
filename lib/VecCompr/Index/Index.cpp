#include <cstlib>
#include <cstdint>

#include "VecCompr.hpp"

// Constructor for the Index object referencing a given array element within a VecCompr compressed vector

VecCompr::Index::Index()
  : ind_(0), off_(0), offComp_(UINT_VEC_COMPR_BIT), widthComp_(UINT_VEC_COMPR_BIT - width_)
{}

VecCompr::Index::Index(std::size_t ind)
  : widthComp_(UINT_VEC_COMPR_BIT - width_)
{
  std::size_t q1 = ind / UINT_VEC_COMPR_BIT;
  std::size_t r1 = ind - UINT_VEC_COMPR_BIT*q;

  std::size_t v = width_*r1;
  std::size_t q2 = v / UINT_VEC_COMPR_BIT;
  std::size_t r2 = v - UINT_VEC_COMPR_BIT*q2;

  ind_ = width_*q1 + q2;
  off_ = r2;
  offComp_ = UINT_VEC_COMPR_BIT - off_;
}

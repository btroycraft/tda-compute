#ifndef VECCOMPR_HPP
#define VECCOMPR_HPP

#include <cstdint>
#include <climits>

#ifndef UINT_VEC_COMPR_MAX
#define UINT_VEC_COMPR_MAX UINT_FAST32_MAX
#endif

#ifndef UINT_VEC_COMPR_BIT
#define UINT_VEC_COMPR_BIT (CHAR_BIT*sizeof(std::uint_fast32_t))
#endif

#ifndef SIZE_INIT_VEC_COMPR
#define SIZE_INIT_VEC_COMPR 16
#endif

#ifndef SIZE_MULT_VEC_COMPR
#define SIZE_MULT_VEC_COMPR 1.5
#endif

typedef uint_vec_compr_t std::uint_fast32_t;

class VecCompr{

  public:

    class Index;

    VecCompr(std::size_t, void*);
    ~VecCompr();

    uint_vec_compr_t operator[](Index) &&;
    _Index operator[](Index) &;
    _Index operator[](std::size_t) &;

  private:

    class Index_;

    std::size_t width_;
    Index end_;
    std::size_t size_;
    void *add_;
};

class VecCompr::Index{

  public:

    Index();
    Index(std::size_t);

    Index& operator--();
    Index operator--(int);

    Index& operator++();
    Index operator++(int);

  private:

    std::size_t ind_;
    std::size_t off_;
    std::size_t offComp_;
    std::size_t widthComp_;
};

#endif

// Copyright 2015-2016 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef _BOOST_HISTOGRAM_DETAIL_WEIGHT_HPP_
#define _BOOST_HISTOGRAM_DETAIL_WEIGHT_HPP_

#include <boost/cstdint.hpp>
#include <type_traits>
#include <ostream>

namespace boost {
namespace histogram {
namespace detail {

/// Used by nstore to hold a sum of weighted counts and a variance estimate
struct weight_t {
  double w, w2;
  weight_t() = default;
  weight_t(const weight_t&) = default;
  weight_t(weight_t&&) = default;
  weight_t& operator=(const weight_t&) = default;
  weight_t& operator=(weight_t&&) = default;
  weight_t(double v) : w(v), w2(v) {}
  weight_t& add_weight(double v)
  { w += v; w2 += v*v; return *this; }
  template <typename T>
  weight_t& add_count(T v)
  { w += v; w2 += v; return *this; }
  weight_t& operator+=(const weight_t& o)
  { w += o.w; w2 += o.w2; return *this; }
  weight_t& operator++()
  { ++w; ++w2; return *this; }
  bool operator==(double v) const
  { return w == v && w2 == v; }
  bool operator!=(double v) const
  { return w != v || w2 != v; }
  bool operator==(const weight_t& o) const
  { return w == o.w && w2 == o.w2; }
  bool operator!=(const weight_t& o) const
  { return w != o.w || w2 != o.w2; }
};

// inline
// std::ostream& operator<<(std::ostream& os, const weight_t& w)
// {
//   os << '(' << w.w << ',' << w.w2 << ')';
//   return os;
// }

}
}
}

#endif

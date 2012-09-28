//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   Triplet.hh
 * \brief  Triplet class definition
 * \author Jeremy Roberts
 * \date   Sep 26, 2012
 */
//---------------------------------------------------------------------------//

#ifndef callow_TRIPLET_HH_
#define callow_TRIPLET_HH_

namespace callow
{

/// Structure for storing COO matrix
struct triplet
{
  int i;
  int j;
  double v;
  // i, j initialized to -1 to ensure they get sorted out
  triplet(int ii=-1, int jj=-1, double vv=0.0)
    : i(ii), j(jj), v(vv)
  {}
};

inline bool compare_triplet(const triplet &x, const triplet &y)
{
  // leave -1's on the right
  if (x.j == -1) return false;
  if (y.j == -1) return true;
  // otherwise, order from low to high j
  return x.j < y.j;
}

inline std::ostream& operator<< (std::ostream &out, triplet s)
{
  out << "(i = " << s.i << ", j = " << s.j << ", v = " << s.v << ")";
  return out;
}

} // end namespace detran

#endif // callow_TRIPLET_HH_

//---------------------------------------------------------------------------//
//              end of file Triplet.hh
//---------------------------------------------------------------------------//
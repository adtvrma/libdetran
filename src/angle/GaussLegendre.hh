//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   GaussLegendre.hh
 *  @author Jeremy Roberts
 *  @date   Mar 23, 2012
 *  @brief  GaussLegendre class definition.
 */
//---------------------------------------------------------------------------//

#ifndef detran_angle_GAUSSLEGENDRE_HH_
#define detran_angle_GAUSSLEGENDRE_HH_

#include "Quadrature.hh"

namespace detran_angle
{

class GaussLegendre: public Quadrature
{

public:

  //-------------------------------------------------------------------------//
  // PUBLIC INTERFACE
  //-------------------------------------------------------------------------//

  /**
   *  @brief Constructor
   *  @param    order       Quadrature order.
   */
  GaussLegendre(size_t order);

  /// SP constructor
  static SP_quadrature Create(size_t order)
  {
    SP_quadrature p(new GaussLegendre(order));
    return p;
  }

};

} // end namespace detran_angle

#endif /* detran_angle_GAUSSLEGENDRE_HH_ */

//---------------------------------------------------------------------------//
//              end of GaussLegendre.hh
//---------------------------------------------------------------------------//

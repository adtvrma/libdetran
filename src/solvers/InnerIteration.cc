//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   InnerIteration.cc
 * \author robertsj
 * \date   Apr 4, 2012
 * \brief  InnerIteration class definition.
 * \note   Copyright (C) 2012 Jeremy Roberts. 
 */
//---------------------------------------------------------------------------//

// Detran
#include "InnerIteration.hh"

namespace detran
{

template <class D>
InnerIteration<D>::InnerIteration(SP_input          input,
				  SP_state          state,
			          SP_mesh      	    mesh,
			          SP_material       material,
			          SP_quadrature     quadrature,
			          SP_MtoD           MtoD,
			          SP_boundary       boundary,
			          SP_externalsource q_e,
			          SP_fissionsource  q_f)
  :  d_input(input)
  ,  d_state(state)
  ,  d_mesh(mesh)
  ,  d_material(material)
  ,  d_quadrature(quadrature)
  ,  d_boundary(boundary)
{

}

} // end namespace detran

//---------------------------------------------------------------------------//
//              end of InnerIteration.cc
//---------------------------------------------------------------------------//
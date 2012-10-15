//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   detran_materials.i
 * \author Jeremy Roberts
 * \brief  Python interface for detran materials.
 */
//---------------------------------------------------------------------------//
   
%include "utilities/detran_utilities.i"

%include "Material.hh"

%template(MaterialSP) detran_utilities::SP<detran_material::Material>;

//---------------------------------------------------------------------------//
//              end of detran_material.i
//---------------------------------------------------------------------------//
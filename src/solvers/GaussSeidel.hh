//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   GaussSeidel.hh
 * \author robertsj
 * \date   Apr 9, 2012
 * \brief  GaussSeidel class definition.
 * \note   Copyright (C) 2012 Jeremy Roberts. 
 */
//---------------------------------------------------------------------------//

#ifndef GAUSSSEIDEL_HH_
#define GAUSSSEIDEL_HH_

// Detran
#include "InnerIteration.hh"

// Utilities
#include "DBC.hh"
#include "InputDB.hh"
#include "SP.hh"


namespace detran
{

//===========================================================================//
/*!
 * \class GaussSeidel
 * \brief Solves the multigroup transport equation via Gauss-Seidel.
 */
//===========================================================================//
template <class D>
class GaussSeidel: public Object
{

public:

  typedef SP<GaussSeidel<D> >                   SP_solver;
  typedef InnerIteration<D>                     SP_inner;
  // basic objects
  typedef InputDB::SP_input                     SP_input;
  typedef State::SP_state                       SP_state;
  typedef Mesh::SP_mesh                         SP_mesh;
  typedef Material::SP_material                 SP_material;
  typedef Quadrature::SP_quadrature             SP_quadrature;
  typedef typename Boundary<D>::SP_boundary     SP_boundary;
  // source typedefs
  typedef ExternalSource::SP_source             SP_externalsource;
  typedef FissionSource::SP_source              SP_fissionsource;

  /*!
   *  \brief Constructor
   *
   *  \param input             Input database.
   *  \param state             State vectors, etc.
   *  \param mesh              Problem mesh.
   *  \param mat               Material definitions.
   *  \param quadrature        Angular mesh.
   *  \param boundary          Boundary fluxes.
   *  \param external_source   User-defined external source.
   *  \param fission_source    Fission source.
   */
  GaussSeidel(SP_input           input,
              SP_state           state,
              SP_mesh            mesh,
              SP_material        material,
              SP_quadrature      quadrature,
              SP_boundary        boundary,
              SP_externalsource  q_e,
              SP_fissionsource   q_f);

  /*!
   *  \brief SP Constructor.
   */
  static SP<GaussSeidel<D> >
  Create(SP<detran::InputDB>         input,
         SP<detran::State>           state,
         SP<detran::Mesh>            mesh,
         SP<detran::Material>        material,
         SP<detran::Quadrature>      quadrature,
         SP<detran::Boundary<D> >    boundary,
         SP<detran::ExternalSource>  q_e,
         SP<detran::FissionSource>   q_f)
  {
    SP_solver p;
    p = new GaussSeidel(input, state, mesh, material,
                        quadrature, boundary, q_e, q_f);
    return p;
  }

  /// Solve the multigroup equations.
  void solve();

  /// Unimplemented DBC function.
  bool is_valid() const
  {return true;}

};

} // namespace detran

//---------------------------------------------------------------------------//
// INLINE FUNCTIONS
//---------------------------------------------------------------------------//

#include "SourceIteration.i.hh"


#endif /* GAUSSSEIDEL_HH_ */
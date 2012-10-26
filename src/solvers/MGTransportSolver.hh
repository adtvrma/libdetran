//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   MGTransportSolver.hh
 *  @author robertsj
 *  @date   Oct 24, 2012
 *  @brief  TransportMGSolver class definition.
 */
//---------------------------------------------------------------------------//

#ifndef detran_MGTRANSPORTSOLVER_HH_
#define detran_MGTRANSPORTSOLVER_HH_

#include "WGSolver.hh"
#include "MGSolver.hh"
#include "angle/Quadrature.hh"

namespace detran
{

//---------------------------------------------------------------------------//
/**
 *  \class MGTransportSolver
 *  \brief Base class for multigroup transport solvers.
 *
 */
//---------------------------------------------------------------------------//

template <class D>
class MGTransportSolver: public MGSolver<D>
{

public:

  //-------------------------------------------------------------------------//
  // TYPEDEFS
  //-------------------------------------------------------------------------//

  // From base
  typedef MGSolver<D>                               Base;
  typedef typename Base::SP_solver                  SP_solver;
  typedef typename Base::SP_input                   SP_input;
  typedef typename Base::SP_state                   SP_state;
  typedef typename Base::SP_mesh                    SP_mesh;
  typedef typename Base::SP_material                SP_material;
  typedef typename Base::SP_boundary                SP_boundary;
  typedef typename Base::SP_externalsource          SP_externalsource;
  typedef typename Base::vec_externalsource         vec_externalsource;
  typedef typename Base::SP_fissionsource           SP_fissionsource;
  // transport-specific
  typedef detran_angle::Quadrature::SP_quadrature   SP_quadrature;
  typedef typename WGSolver<D>::SP_solver           SP_wg_solver;

  //-------------------------------------------------------------------------//
  // CONSTRUCTOR & DESTRUCTOR
  //-------------------------------------------------------------------------//

  /**
   *  @brief Constructor
   *  @param state             State vectors, etc.
   *  @param material          Material definitions.
   *  @param boundary          Boundary fluxes.
   *  @param external_source   User-defined external source.
   *  @param fission_source    Fission source.
   *  @param multiply          Flag for multiplying fixed source problem
   */
  MGTransportSolver(SP_state                  state,
                    SP_material               material,
                    SP_boundary               boundary,
                    const vec_externalsource &q_e,
                    SP_fissionsource          q_f,
                    bool                      multiply);

  /// Virtual destructor
  virtual ~MGTransportSolver(){};

  //-------------------------------------------------------------------------//
  // ABSTRACT INTERFACE -- ALL MULTIGROUP SOLVERS MUST IMPLEMENT
  //-------------------------------------------------------------------------//

  /// Solve the multigroup equations.
  virtual void solve(const double keff = 1.0) = 0;

protected:

  //-------------------------------------------------------------------------//
  // DATA
  //-------------------------------------------------------------------------//

  /// Expose base members
  using Base::d_input;
  using Base::d_state;
  using Base::d_mesh;
  using Base::d_material;
  using Base::d_boundary;
  using Base::d_externalsources;
  using Base::d_fissionsource;
  using Base::d_downscatter;
  using Base::d_number_groups;
  using Base::d_maximum_iterations;
  using Base::d_tolerance;
  using Base::d_print_level;
  using Base::d_print_interval;
  using Base::d_adjoint;
  using Base::d_multiply;

  /// Angular mesh
  SP_quadrature d_quadrature;

  /// Inner solver
  SP_wg_solver d_wg_solver;

};

} // namespace detran

//---------------------------------------------------------------------------//
// INLINE FUNCTIONS
//---------------------------------------------------------------------------//

//#include "MGTransportSolver.i.hh"

#endif /* detran_MGTRANSPORTSOLVER_HH_ */

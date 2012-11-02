//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   Sweeper1D.hh
 * \author Jeremy Roberts
 * @date   Mar 24, 2012
 * \brief  Sweeper1D class definition.
 */
//---------------------------------------------------------------------------//

#ifndef SWEEPER1D_HH_
#define SWEEPER1D_HH_

#include "Sweeper.hh"
#include "boundary/BoundarySN.hh"

namespace detran
{

//---------------------------------------------------------------------------//
/*!
 *  \class Sweeper1D
 *  \brief Sweeper for 1D discrete ordinates problems.
 */
//---------------------------------------------------------------------------//
template <class EQ>
class Sweeper1D: public Sweeper<_1D>
{

public:

  //-------------------------------------------------------------------------//
  // TYPEDEFS
  //-------------------------------------------------------------------------//

  typedef detran_utilities::SP<Sweeper1D>           SP_sweeper;
  typedef Sweeper<_1D>                              Base;
  typedef typename Base::SP_state                   SP_state;
  typedef typename Base::SP_input                   SP_input;
  typedef typename Base::SP_material                SP_material;
  typedef typename Base::Mesh                       Mesh;
  typedef typename Base::SP_mesh                    SP_mesh;
  typedef typename Base::SP_quadrature              SP_quadrature;
  typedef typename Base::SP_sweepsource             SP_sweepsource;
  typedef typename Base::moments_type               moments_type;
  typedef typename Base::angular_flux_type          angular_flux_type;
  typedef typename Base::SP_tally                   SP_currenttally;
  typedef typename Base::vec_int                    vec_int;
  typedef typename Base::vec2_int                   vec2_int;
  typedef typename Base::vec3_int                   vec3_int;
  typedef typename Base::size_t                     size_t;
  typedef EQ                                        Equation_T;
  typedef BoundarySN<_1D>                           Boundary_T;
  typedef typename Boundary_T::SP_boundary          SP_boundary;
  typedef typename BoundaryTraits<_1D>::value_type  boundary_flux_type;

  //-------------------------------------------------------------------------//
  // CONSTRUCTOR & DESTRUCTOR
  //-------------------------------------------------------------------------//

  /*!
   *  \brief Constructor.
   *
   *  @param    input       User input database.
   *  @param    mesh        Cartesian mesh.
   *  @param    material    Material database.
   *  @param    quadrature  Angular quadrature.
   *  @param    state       State vectors.
   *  @param    boundary    Boundary based on mesh.
   *  @param    sweepsource Sweep source constructor.
   */
  Sweeper1D(SP_input input,
            SP_mesh mesh,
            SP_material material,
            SP_quadrature quadrature,
            SP_state state,
            SP_boundary boundary,
            SP_sweepsource sweepsource)
  : Base(input,mesh,material,quadrature,
         state,sweepsource)
  , d_boundary(boundary)
  , d_ordered_octants(2, 0)
  {
    Require(boundary);

    // Order the octants
    d_ordered_octants[0] = 0;
    d_ordered_octants[1] = 1;
    if (d_boundary->is_reflective(0) and d_boundary->is_reflective(1))
    {
      d_ordered_octants[0] = 1;
      d_ordered_octants[1] = 0;
    }

  }

  /// Virtual destructor
  virtual ~Sweeper1D(){}

  /// SP Constructor
  static SP_sweeper
  Create(detran_utilities::InputDB::SP_input        input,
         detran_geometry::Mesh::SP_mesh             mesh,
         detran_material::Material::SP_material     material,
         detran_angle::Quadrature::SP_quadrature    quadrature,
         State::SP_state                            state,
         BoundaryBase<_1D>::SP_boundary             boundary,
         SweepSource<_1D>::SP_sweepsource           sweepsource)
  {
    SP_sweeper p(new Sweeper1D(input, mesh, material, quadrature,
                               state, boundary, sweepsource));
    return p;
  }

  //-------------------------------------------------------------------------//
  // ABSTRACT INTERFACE -- ALL SWEEPERS MUST IMPLEMENT THESE
  //-------------------------------------------------------------------------//

  /// Sweep.
  inline void sweep(State::moments_type &phi);

  /// Setup the equations for the group
  void setup_group(const detran_utilities::size_t g)
  {
    d_g = g;
  }

private:

  //-------------------------------------------------------------------------//
  // DATA
  //-------------------------------------------------------------------------//

  SP_boundary d_boundary;
  vec_int d_ordered_octants;

};

} // end namespace detran

//---------------------------------------------------------------------------//
// INLINE MEMBER DEFINITIONS
//---------------------------------------------------------------------------//

#include "Sweeper1D.i.hh"

#endif /* SWEEPER1D_HH_ */

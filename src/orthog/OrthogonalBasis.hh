//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   OrthogonalBasis.hh
 *  @brief  OrthogonalBasis
 *  @author Jeremy Roberts
 *  @date   Jan 8, 2013
 */
//---------------------------------------------------------------------------//

#ifndef detran_orthog_ORTHOGONALBASIS_HH_
#define detran_orthog_ORTHOGONALBASIS_HH_

#include "orthog/orthog_export.hh"
#include "callow/vector/Vector.hh"
#include "callow/matrix/MatrixDense.hh"
#include "callow/utils/CallowDefinitions.hh"
#include "utilities/Definitions.hh"
#include "utilities/SP.hh"

/**
 *  @namespace detran_ortho
 *  @brief Contains basic utilities for performing orthogonal expansions
 */
namespace detran_orthog
{

/**
 *  @class OrthogonalBasis
 *  @brief Base orthogonal basis class
 *
 *  Consider a one dimensional function (or a vector) @f$ f(x) @f$.
 *  We seek to expand
 *  @f$ f @f$ either completely or approximately in some orthogonal
 *  basis consisting of functions
 *  @f[
 *      P_l(x) \, , l = 0, 1, \ldots \, ,
 *  @f]
 *  subject to the normalization
 *  @f[
 *      \Braket{ w P_l, P_k } = a_l \delta_{lk} \, ,
 *  @f]
 *  where @f$ w @f$ is a weighting function.
 *  An orthonormal basis (with respect to the weights)
 *  has @f$ a_l = 1 @f$.
 *
 *  Suppose @f$ f \in R^{n} @f$ and
 *  @f$ \mathbf{P} \in R^{n\times n} = [P_0 P_1 \ldots]^T @f$.
 *  The transform into the basis is represented as
 *  @f[
 *      \tilde{f} =  \mathbf{P} \mathbf{W} f \, ,
 *  @f]
 *  where @f$ \mathbf{W} @f$ represents the diagonal weight
 *  operator.
 *  The vector @f$ \tilde{f} @f$ contains the expansion
 *  coefficients.  Note, were @f$ \mathbf{P} \in R^{m \times n} @f$,
 *  for @f$ m < n @f$, then  @f$ \tilde{f} \in R^{m} @f$ is a
 *  truncated expansion.
 *
 *  To get back our initial vector (or its approximation),
 *  we perform the inverse transform
 *  @f[
 *      f =   \mathbf{P}^{T} \mathbf{A}^{-1} \tilde{f} \, ,
 *  @f]
 *  where @f$ \mathbf{A} @f$ represents the diagonal operator
 *  of the   @f$ a_l @f$ coefficients.
 *
 */
class ORTHOG_EXPORT OrthogonalBasis
{

public:

  //-------------------------------------------------------------------------//
  // TYPEDEFS
  //-------------------------------------------------------------------------//

  typedef detran_utilities::SP<OrthogonalBasis> SP_basis;
  typedef callow::Vector                        Vector;
  typedef callow::Vector::SP_vector             SP_vector;
  typedef callow::MatrixDense::SP_matrix        SP_matrix;
  typedef detran_utilities::size_t              size_t;
  typedef detran_utilities::vec_dbl             vec_dbl;

  //-------------------------------------------------------------------------//
  // CONSTRUCTOR & DESTRUCTOR
  //-------------------------------------------------------------------------//

  /**
   *   @brief Constructor.
   *   @param   order       Order of the expansion
   *   @param   size        Size of the basis vectors
   *   @param   orthonormal Flag to indicate the basis should be orthonormal
   */
  OrthogonalBasis(const size_t order,
                  const size_t size,
                  const bool orthonormal = false);

  /// Pure virtual destructor
  virtual ~OrthogonalBasis() = 0;

  //-------------------------------------------------------------------------//
  // PUBLIC FUNCTIONS
  //-------------------------------------------------------------------------//

  /**
   *  @brief Fold a vector with one row of the basis.
   *
   *  Performs the operation
   *  @f[
   *      \tilde{f}_l =  \mathbf{P}_{l,:} \mathbf{W} f \, ,
   *  @f]
   *
   *  @param  row   Row index of the basis operator
   *  @param  V     Vector to fold
   */
  virtual double fold(const size_t row, const Vector &V);
  /// Interface for SP vectors
  double fold(const size_t row, SP_vector V);
  /// Interface for std vector
  double fold(const size_t row, const vec_dbl &V);

  /**
   *  @brief (Un)fold a vector with one column of the basis
   *
   *  Performs the operation
   *  @f[
   *      f_l =  \mathbf{P}^T_{:, l} \mathbf{A}^{-1} \tilde{f} \, ,
   *  @f]
   *
   *  @param  column  Column index of the basis operator
   *  @param  V       Vector to fold
   */
  virtual double unfold(const size_t column, const Vector &V);
  /// Interface for SP vectors
  double unfold(const size_t column, SP_vector V);
  /// Interface for std vector
  double unfold(const size_t column, const vec_dbl &V);


  /**
   *  @brief Perform a transform
   *
   *  Performs the operation
   *  @f[
   *      \tilde{f} =  \mathbf{P} \mathbf{W} f \, ,
   *  @f]
   *
   *  @param  f       Vector to transform
   *  @param  ftilde  Transformed vector
   */
  virtual void transform(const Vector &f, Vector &ftilde);
  /// Interface for SP vectors
  void transform(SP_vector f, SP_vector ftilde);
  /// Interface for std vector
  void transform(const vec_dbl &f, vec_dbl &ftilde);

  /**
   *  @brief Perform an inverse transform
   *
   *  Performs the operation
   *  @f[
   *      f_l =  \mathbf{P}^T \mathbf{A}^{-1} \tilde{f} \, ,
   *  @f]
   *
   *  @param  ftilde  Vector to inverse transform
   *  @param  f       Transformed vector
   */
  virtual void inverse(const Vector &ftilde, Vector &f);
  /// Interface for SP vectors
  void inverse(SP_vector f, SP_vector ftilde);
  /// Interface for std vector
  void inverse(const vec_dbl &f, vec_dbl &ftilde);

  /// Access to transform operator PW
  virtual double operator()(const size_t i, const size_t j) const;

  /// Return the basis matrix
  SP_matrix basis() {return d_basis;}

  /// Return the weights
  SP_vector weights() {return d_w;}

  /// Return the coefficients
  SP_vector coefficients() {return d_a;}

  /// Return the basis order.
  size_t order() const {return d_order;}

protected:

  //-------------------------------------------------------------------------//
  // DATA
  //-------------------------------------------------------------------------//

  /// Order of the basis (i.e. the highest degree polynomial stored)
  size_t d_order;
  /// Size of the basis (i.e. the length of the functions expanded)
  size_t d_size;
  /// Dense matrix representation of basis
  SP_matrix d_basis;
  /// Vector of weights
  SP_vector d_w;
  /// Vector of the inverse normalization coefficients
  SP_vector d_a;
  /// Orthonormal flag
  bool d_orthonormal;

  //-------------------------------------------------------------------------//
  // IMPLEMENTATION
  //-------------------------------------------------------------------------//

  /// Compute the normalization coefficients directly
  void compute_a();

};

ORTHOG_TEMPLATE_EXPORT(detran_utilities::SP<OrthogonalBasis>)

} // end namespace detran_orthog

#include "OrthogonalBasis.i.hh"

#endif // detran_orthog_ORTHOGONALBASIS_HH_

//---------------------------------------------------------------------------//
//              end of file OrthogonalBasis.hh
//---------------------------------------------------------------------------//

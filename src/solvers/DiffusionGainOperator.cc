//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   DiffusionGainOperator.cc
 * \brief  DiffusionGainOperator 
 * \author Jeremy Roberts
 * \date   Sep 10, 2012
 */
//---------------------------------------------------------------------------//

#include "DiffusionGainOperator.hh"

namespace detran
{

DiffusionGainOperator::DiffusionGainOperator(SP_input      input,
                                             SP_material   material,
                                             SP_mesh       mesh)
  : OperatorMatrix(material->number_groups()*mesh->number_cells(),
                   material->number_groups()*mesh->number_cells())
  , d_input(input)
  , d_material(material)
  , d_mesh(mesh)
{

  // Nonzeros.  We have up to the number of groups in a row
  // due to fission.
  vec_int nnz(d_number_rows, d_number_groups);

  // Preallocate the matrix.  Note, PETSc documentation suggests getting
  // this right is extremely important.
  preallocate(nnz);

  // Build the matrix with the initial keff guess.
  build();
}

//---------------------------------------------------------------------------//
// IMPLEMENTATION
//---------------------------------------------------------------------------//

void DiffusionGainOperator::build()
{
  using std::cout;
  using std::endl;

  // Get the material map.
  vec_int mat_map = d_mesh->mesh_map("MATERIAL");

  for (int g = 0; g < d_number_groups; g++)
  {

    // Loop over all cells.
    for (int cell = 0; cell < d_group_size; cell++)
    {

      // Compute row index.
      int row = cell + g * d_group_size;

      // Define the data for this cell.
      int m = mat_map[cell];

      // Get the directional indices.
      int i = d_mesh->cell_to_i(cell);
      int j = d_mesh->cell_to_j(cell);
      int k = d_mesh->cell_to_k(cell);

      // Loop through source group.
      for (int gp = 0; gp < d_number_groups; gp++)
      {
        // Compute column index.
        int col = cell + gp * d_group_size;

        // Fold the fission density with the spectrum.
        double val = d_material->nu_sigma_f(m, gp) *
                     d_material->chi(m, g);

        // Set the value.
        insert_values(1, &row, 1, &col, &val, INSERT_VALUES);
      }

    } // row loop

  } // group loop

  assemble();

}

} // end namespace detran

//---------------------------------------------------------------------------//
//              end of file DiffusionGainOperator.cc
//---------------------------------------------------------------------------//
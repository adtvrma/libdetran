#------------------------------------------------------------------------------#
# src/callow/test/CMakeLists.txt
#------------------------------------------------------------------------------#

# Vector
ADD_EXECUTABLE(test_Vector              test_Vector.cc)
TARGET_LINK_LIBRARIES(test_Vector       callow )
ADD_TEST(test_Vector                    test_Vector 0)

# Matrix
ADD_EXECUTABLE(test_Matrix              test_Matrix.cc)
TARGET_LINK_LIBRARIES(test_Matrix       callow )
ADD_TEST(test_Matrix                    test_Matrix 0)
#
ADD_EXECUTABLE(test_MatrixShell         test_MatrixShell.cc)
TARGET_LINK_LIBRARIES(test_MatrixShell  callow )
ADD_TEST(test_MatrixShell               test_MatrixShell 0)
#
ADD_EXECUTABLE(test_MatrixDense         test_MatrixDense.cc)
TARGET_LINK_LIBRARIES(test_MatrixDense  callow )
ADD_TEST(test_MatrixDense               test_MatrixDense 0)

# Linear Solvers
ADD_EXECUTABLE(test_LinearSolver        test_LinearSolver.cc)
TARGET_LINK_LIBRARIES(test_LinearSolver callow )
ADD_TEST(test_Richardson                test_LinearSolver 0)
ADD_TEST(test_Jacobi                    test_LinearSolver 1)
ADD_TEST(test_GaussSeidel               test_LinearSolver 2)
ADD_TEST(test_SOR                       test_LinearSolver 3)
ADD_TEST(test_GMRES                     test_LinearSolver 4)

# Eigenvalue Solvers
ADD_EXECUTABLE(test_EigenSolver         test_EigenSolver.cc)
TARGET_LINK_LIBRARIES(test_EigenSolver  callow )
ADD_TEST(test_PowerIteration            test_EigenSolver 0)



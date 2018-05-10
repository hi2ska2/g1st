////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// numericalsolvers.h

#ifndef numericalsolversH
#define numericalsolversH

//#include <complex>
#include <iostream>
#include <fstream>
#include <vector>
#include "Sparse.h"

//#include "Etc.h"

//
// LAPACK
//

extern "C" {
   void dgesv_(
      int *n, 
      int *nrhs,
      double *a,
      int *lda,
      int *ipiv,
      double *b,
      int *ldb,
      int *info
      );
}

extern "C" {
  void zgesv_
  (
   int *n, int *nrhs, double *a, int *lda, int *ipiv, double *b, int *ldb, int *info
   );
}

extern "C" {
  void zgeev_
  (
   char *jobvl, char *jobvr,
   int *n, double *a, int *lda, double *w, double *vl, int *ldvl, double *vr,
   int *ldvr, double *work, int *lwork, double *rwork, int *info
   );
}

extern "C" {
  void dggev_
  (
   char *jobvl, char *jobvr,	       
   int *n, double *a, int *lda, double *b, int *ldb, 
   double *alphar, double* alphai, double *beta,
   double *vl, int *ldvl, double *vr, int *ldvr, double *work, int *lwork, int *info
   );
}

extern "C" {
  void zggev_
  (
   char *jobvl, char *jobvr,	       
   int *n, double *a, int *lda, double *b, int *ldb, double *alpha, double *beta,
   double *vl, int *ldvl, double *vr, int *ldvr, double *work, int *lwork, double *rwork,
   int *info
   );
}

//
// LAPACK warper
//

void myDGGEV(int n, double *a, double *b, double *w, double *vr);

void myZGESV(int n, double *a, double *b);   // ax=b, b=x
void myZGEEV(int n, double *a, double *w, double *vr);
//void myZGGEV(int n, double *a, double *b, double *w, double *vr);

//class Sparse;
inline void solveEigenValue(Sparse<double>& a,Sparse<double>& b) {
  // ARPACK implementation is desirable.
  // For test, LAPACK implementation is here.

  //myZGEEV();

  //a.show();
  //b.show();  
  int n = a.getSize();

  //std::cout << "Size of the matrix is " << n << "\n";

  double* pa = new double[n*n];
  double* pb = new double[n*n];
  double* pw = new double[n];
  double* pvr = new double[n*n]; 
  a.getFullColumnMajor(pa);
  b.getFullColumnMajor(pb);

  myDGGEV(n,pa,pb,pw,pvr);

  //for (int ii=0; ii<n; ++ii) std::cout << pw[ii] << "\n";

  delete[] pa;
  delete[] pb;
  delete[] pw;
  delete[] pvr;
}

void solveEigenValue(Sparse<double>& a,Sparse<double>& b,
		     std::vector<double>& eigenvalues,
		     std::vector<double>& eigenvectors,
		     int nEigen);

#endif

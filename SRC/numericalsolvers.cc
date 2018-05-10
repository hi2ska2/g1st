////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// numericalsolvers.cc

#include "numericalsolvers.h"

void myDGGEV(int n, double *a, double *b, double *w, double *vr)
{
  double *vl = new double[n*n];
  for (int ii=0; ii<n; ++ii) w[ii] = 0.0;
  for (int ii=0; ii<n; ++ii) vl[ii] = 0.0;
  for (int ii=0; ii<n*n; ++ii) vr[ii] = 0.0; 
  
  char c4='N';
  char c5='V';
  int lda = n;
  int ldb = n;
  int ldvl = n;
  int ldvr = n;
  int info;
  
  int lwork = 8*n;
  double work[2*lwork];
  double alphar[n], alphai[n], beta[n];		
  
  dggev_(&c4,&c5,&n,a,&lda,b,&ldb,alphar,alphai,beta,vl,&ldvl,vr,&ldvr,work,&lwork,&info);	
  
  for (int ener=0; ener<n; ener++) w[ener] = (alphar[ener]/beta[ener]);
  
  delete[] vl;	
}

void solveEigenValue(Sparse<double>& a,Sparse<double>& b,
		     std::vector<double>& eigenvalues,
		     std::vector<double>& eigenvectors,
		     int nEigen)
{ 
  int n = a.getSize();

  double* pa = new double[n*n];
  double* pb = new double[n*n];
  double* pw = new double[n];
  double* pvr = new double[n*n]; 
  a.getFullColumnMajor(pa);
  b.getFullColumnMajor(pb);

  myDGGEV(n,pa,pb,pw,pvr);  

  eigenvalues.resize(nEigen,0.0);
  eigenvectors.resize(nEigen*n,0.0);

  std::multimap<double,int> sortedEigenvalues;
  for (int ii=0; ii<n; ++ii) {
    sortedEigenvalues.insert( std::pair<double,int>(pw[ii],ii) );
  }

  int ii=0;
  for (std::multimap<double,int>::iterator it=sortedEigenvalues.begin();
       it!=sortedEigenvalues.end(); ++it) {
    if (it->first > 1e10) {
      eigenvalues[ii] = it->first;
      std::cout << eigenvalues[ii] << " " << nEigen << " " << ii << "\n";
      int jj = it->second;
      for (int kk=0; kk<n; ++kk) {
	eigenvectors[n*ii+kk] = pvr[n*jj+kk]; // Column-major order
      }
      ++ii;
    }
    if (ii>=nEigen) break;
  }

  delete[] pa;
  delete[] pb;
  delete[] pw;
  delete[] pvr;  
}

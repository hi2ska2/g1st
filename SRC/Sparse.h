////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// Sparse.h

// A square matrix is understood.

// Since there can be many different forms of a sparse matrix,
// the class Sparse has derived classes.

#ifndef SparseH
#define SparseH

#include "ParseTree.h"
#include "utilities.h"
#include <iostream>
#include <fstream>
#include <map>
#include <math.h>

template<class T>
class Sparse {
 public:
  Sparse<T>() : _n(0) { }
  virtual void show() { std::cout << "Sparse::show()\n"; }
  virtual T& operator()(int ii, int ij) = 0;
  virtual void clearRow(int ii) = 0;
  int getSize() { return _n; }
  virtual void getFullColumnMajor(double* p) = 0;
  virtual void moveRow(int ii,int jj) = 0;
  //virtual void solve(std::vector<T> theVector,std::vector<T> theSolution) = 0;

  protected:
  int _n;
};

template<class T> 
class Triplet : public Sparse<T> {
 public:
  Triplet<T>() : Sparse<T>() { _contents.clear(); }
  virtual void show() { 
    std::cout << "Triplet::show()\n"; 
    typename std::map<std::pair<int,int>,T>::iterator it;
    for (it=_contents.begin(); it!=_contents.end(); ++it)
      if (it->second!=0.0) {
	std::cout << (it->first).first << " " << (it->first).second << " " << it->second << "\n";
      }
  }

  virtual T& operator()(int ii, int ij) { 
    if (ii>=this->_n) this->_n = (ii+1);
    if (ij>=this->_n) this->_n = (ij+1);

    typename std::map<std::pair<int,int>,T>::iterator it;
    it = _contents.find(std::pair<int,int>(ii,ij));
    if (it == _contents.end()) it = _contents.insert(it,std::pair<std::pair<int,int>,T>(std::pair<int,int>(ii,ij),0.0));

    return it->second;
  }

  virtual void clear() {
    _contents.clear();
    this->_n = 0;
  }

  // Implemented on April 4, 2016
  virtual void clearRow(int ii) {
    //std::cout << "Triplet::clearRow(ii)\n";
    typename std::map<std::pair<int,int>,T>::iterator it;
    for (it=_contents.begin(); it!=_contents.end(); ++it) {
      if ((it->first).first==ii) it->second = 0.0;
    }    
  }

  virtual void getFullColumnMajor(double* p) {
    int n = this->_n;
    for (int ii=0; ii<n*n; ++ii) p[ii] = 0.0;

    typename std::map<std::pair<int,int>,T>::iterator it;
    for (it=_contents.begin(); it!=_contents.end(); ++it) {
      int ii = (it->first).first;
      int ij = (it->first).second;
      double val = it->second;
      p[n*ij+ii] = val; // Column-major order
    }
  }

  virtual void moveRow(int ii,int jj) { // from ii to jj
    std::vector<int>    col; col.clear();
    std::vector<double> val; val.clear();
    typename std::map<std::pair<int,int>,T>::iterator it;
    for (it=_contents.begin(); it!=_contents.end(); ++it) {
      if ((it->first).first==ii) {	
	col.push_back((it->first).second);
	val.push_back(it->second);
	it->second = 0.0;
      }
    }
    for (int kk=0; kk<col.size(); ++kk) {
      operator()(jj,col[kk]) += val[kk];
    }
  }

  virtual void solve(std::vector<T>& theVector,std::vector<T>& theSolution) {
    myReportError("Triplet::solve(theVector,theSolution)");
  }

 protected:
  std::map<std::pair<int,int>,T> _contents;
};
 
class RealTriplet : public Triplet<double> {
 public:
  void get_csr_format_1based(int* &prow, int* &icol, double* &ax, int& nz);

  void get_csc_format(int* &pcol, int* &irow, double* &ax, int* &map) {
    // Empty implementation
  }

  void get_triplet_format(std::vector<int>& ti,std::vector<int>& tj,std::vector<double>& tx,int& nz)
  {
    typename std::map<std::pair<int,int>,double>::iterator it;
    for (it=_contents.begin(); it!=_contents.end(); ++it) {
      if (it->second!=0.0) {
	ti.push_back((it->first).first );
	tj.push_back((it->first).second);
	tx.push_back( it->second       );
	nz++;
      }
    }
  }

  void printMATLAB(std::string fileName,
		   std::vector<double>& theResidue,
		   std::vector<double>& theSolution)
  {
    printMATLAB(fileName);

    //
    std::string resFileName = fileName + ".res";
    std::ofstream resFile(resFileName.c_str());
    resFile.precision(17);

    for (int ii=0; ii<theResidue.size(); ++ii) {
      resFile << theResidue[ii] << "\n";
    }

    resFile.close();

    //
    std::string solFileName = fileName + ".sol";
    std::ofstream solFile(solFileName.c_str());
    solFile.precision(17);

    for (int ii=0; ii<theSolution.size(); ++ii) {
      solFile << theSolution[ii] << "\n";
    }

    solFile.close();
  }

  void printMATLAB(std::string fileName)
  {
    // ti, tj, tx, nz 
    std::vector<int>    ti;
    std::vector<int>    tj;
    std::vector<double> tx;
    int nz = 0;

    get_triplet_format(ti,tj,tx,nz);

    std::ofstream outputFile(fileName.c_str());
    outputFile.precision(17);

    for (int ii=0; ii<nz; ++ii) {
      outputFile << ti[ii]+1 << " " << tj[ii]+1 << " " << tx[ii] << "\n";
    }

    outputFile.close();
  }

  void solve(std::vector<double>& theVector,std::vector<double>& theSolution);
  void solve(std::vector<double>& theVector,std::vector<double>& theSolution,
	     ArgList* solverArgList);
};

#endif

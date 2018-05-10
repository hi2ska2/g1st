////////////////////////////////////////////////
// G-1st                                      //
//                                            //
// Copyright 2018 Sung-Min Hong               //
//                                            //
// Please see LICENSE for license information //
////////////////////////////////////////////////

// Balance.h

#ifndef BalanceH
#define BalanceH

#include <cmath>
#include <math.h>
#include <limits>

class Grad {
 public:
  Grad() { _contents.clear(); }
  Grad(int col,double grad) { 
    _contents.clear(); 
    _contents.insert(std::pair<int,double>(col,grad)); 
  }
  
  void clear() { _contents.clear(); }
  const std::map<int,double>& getContents() const { return _contents; };
  std::map<int,double>& getContents()             { return _contents; }; 
  const double& getValue(int col) const { myReportError("Grad::getValue(col) const"); };
  double&       getValue(int col)       { 
    std::map<int,double>::iterator it = _contents.find(col);
    if (it==_contents.end()) myReportError("Grad::getValue(col)"); 
    else                     return it->second;    
  };
  bool isnan() {
    std::map<int,double>::iterator it;
    for (it=_contents.begin(); it!=_contents.end(); ++it) {
      int col = it->first;
      if (std::isnan(it->second)) return true;
    }
    return false;
  }    
  void set(int col,double grad) {
    _contents.clear();
    _contents.insert(std::pair<int,double>(col,grad));
  }
  void show() {
    std::map<int,double>::iterator it;
    for (it=_contents.begin(); it!=_contents.end(); ++it) {
      int col = it->first;
      myReport("col = " + myIntToString(col) + ", grad = " + myDoubleToString(it->second));
    }
  }
  void show() const {
    std::map<int,double>::const_iterator it;
    for (it=_contents.begin(); it!=_contents.end(); ++it) {
      int col = it->first;
      myReport("col = " + myIntToString(col) + ", grad = " + myDoubleToString(it->second));
    }
  }  

  // operator+=
  Grad& operator+=(const Grad& grad) { 
    std::map<int,double>::const_iterator it;
    std::map<int,double>::iterator       jt;
    for (it=(grad._contents).begin(); it!=(grad._contents).end(); ++it) {
      jt = _contents.find(it->first);
      if (jt==_contents.end()) _contents.insert(std::pair<int,double>(it->first,it->second));
      else                     (jt->second) += (it->second);
    } 
  }

  // operator-=
  Grad& operator-=(const Grad& grad) { 
    std::map<int,double>::const_iterator it;
    std::map<int,double>::iterator       jt;
    for (it=(grad._contents).begin(); it!=(grad._contents).end(); ++it) {
      jt = _contents.find(it->first);
      if (jt==_contents.end()) _contents.insert(std::pair<int,double>(it->first,-(it->second)));
      else                     (jt->second) -= (it->second);
    }  
  }

  // operator*=
  Grad& operator*=(const double& val) { 
    std::map<int,double>::iterator it;
    for (it=(_contents).begin(); it!=(_contents).end(); ++it) {
      (it->second) *= val;
    } 
  }

  // operator/=
  Grad& operator/=(const double& val) { 
    std::map<int,double>::iterator it;
    for (it=(_contents).begin(); it!=(_contents).end(); ++it) {
      (it->second) /= val;
    } 
  }

  private:
  std::map<int,double> _contents;
};

class Balance {
 public:
 Balance(const double value=0.0) : _value(value) { _grad.clear(); }
 Balance(const double value,const int col,double grad=1.0) : _value(value) {      
    _grad.set(col,grad);
  }
  
  void addGrad(const int col,double grad=1.0) { _grad += Grad(col,grad); }
  Grad& getGrad() { return _grad; }
  double  getGradValue(const int col) const { return _grad.getValue(col); }
  double& getGradValue(const int col)       { return _grad.getValue(col); }
  double  getValue() const { return _value; }
  double& getValue()       { return _value; }
  bool isnan() {
    return ( std::isnan(_value) || _grad.isnan() );
  }
  void setValue(const double& value) { _value = value; }
  
  void show() {
    myReport("Balance.show()");
    myReport("value = " + myDoubleToString( _value));
    _grad.show();
  }
  void show() const {
    myReport("Balance.show()");
    myReport("value = " + myDoubleToString( _value));
    _grad.show();
  }  

  Balance& operator=(double value) {
    _grad.clear();
    _value = value;
    return *this;
  }

  Balance operator-() const {
    Balance tmp(*this); 
    return (tmp*=(-1.0));
  }  

  // operator+=
  Balance& operator+=(const double value) { _value += value;                          return *this; }
  Balance& operator+=(const Balance& bal) { 
    _value += bal._value; 
    _grad += bal._grad; 
    //std::cout << "_value = " << _value <<"\n";
    //_grad.show();
    return *this; 
  }

  // operator-=
  Balance& operator-=(const double value) { _value -= value;                          return *this; }
  Balance& operator-=(const Balance& bal) { _value -= bal._value; _grad -= bal._grad; return *this; }

  // operator*=
  Balance& operator*=(const double value) {     
    _value *= value;
    _grad *= value;;
    return *this; 
  }
  Balance& operator*=(const Balance& bal) {     
    _grad *= bal._value;  //myReport("Intermediately, _grad="); _grad.show();
    Balance tmp(bal);     //myReport("Originally, tmp._grad="); tmp._grad.show();
    tmp._grad *= _value;  //myReport("Intermediately, tmp._grad="); tmp._grad.show();
    _grad += tmp._grad;   //myReport("Finally, _grad="); _grad.show();
    _value *= bal._value; //myReport("_value=" + myDoubleToString(_value));
    return *this; 
  }

  // operator/=
  Balance& operator/=(const Balance& bal) {     
    _grad /= bal._value;  
    Balance tmp(bal);     
    tmp._grad *= (_value/bal._value/bal._value);  
    _grad -= tmp._grad;   
    _value /= bal._value; 
    return *this; 
  }

  // operator+
  friend Balance operator+(const Balance& lhs,const Balance& rhs) { Balance tmp = lhs; return tmp += rhs; }
  friend Balance operator+(const Balance& lhs,const double& rhs)  { Balance tmp = lhs; return tmp += rhs; }
  friend Balance operator+(const double& lhs,const Balance& rhs)  { Balance tmp(lhs);  return tmp += rhs; } 

  // operator-
  friend Balance operator-(const Balance& lhs,const Balance& rhs) { Balance tmp = lhs; return tmp -= rhs; }
  friend Balance operator-(const Balance& lhs,const double& rhs)  { Balance tmp = lhs; return tmp -= rhs; }
  friend Balance operator-(const double& lhs,const Balance& rhs)  { Balance tmp(lhs);  return tmp -= rhs; }  
  
  // operator*
  friend Balance operator*(const Balance& lhs,const Balance& rhs) { Balance tmp = lhs; return tmp *= rhs; }

  // operator/
  friend Balance operator/(const Balance& lhs,const Balance& rhs) { Balance tmp = lhs; return tmp /= rhs; }
  friend Balance operator/(const Balance& lhs,const double& rhs)  { Balance tmp = lhs; return tmp /= rhs; }

  // operator<
  friend bool operator<(const Balance& lhs, const Balance& rhs) { return lhs._value < rhs._value; } // Bug fixed on January 4, 2017
  friend bool operator<(const Balance& lhs, const double&  rhs) { return lhs._value < rhs;        } // Bug fixed on January 4, 2017
  friend bool operator<(const double&  lhs, const Balance& rhs) { return lhs        < rhs._value; } // Bug fixed on January 4, 2017

  // operator>
  friend bool operator>(const Balance& lhs, const Balance& rhs) { return lhs._value > rhs._value; } // Bug fixed on January 4, 2017
  friend bool operator>(const Balance& lhs, const double&  rhs) { return lhs._value > rhs;        } // Bug fixed on January 4, 2017
  friend bool operator>(const double&  lhs, const Balance& rhs) { return lhs        > rhs._value; } // Bug fixed on January 4, 2017

  // exp
  friend Balance exp(const Balance& exponent) { 
    Balance tmp(exponent);
    tmp._value = 1.0;
    return tmp *= exp(exponent._value); 
  }

  // log
  friend Balance log(const Balance& x) { 
    Balance tmp(x);
    tmp._value = log(x._value);
    tmp._grad /= x._value; // It is assumed that x._value is non-zero.
    return tmp;
  } 

  // pow
  // It calcultates base^exponent.
  friend Balance pow(const Balance& base, const Balance& exponent) { 
    if (base._value==0.0) return Balance(0.0);
    else                  return exp( exponent*log(base) );
  }
  friend Balance pow(const Balance& base, const double&  exponent) { 
    if (base._value==0.0) return Balance(0.0);
    else                  return exp( exponent*log(base) );
  }
  friend Balance pow(const double&  base, const Balance& exponent) { 
    if (base==0.0) return Balance(0.0);
    else           return exp( exponent*log(base) );
  }

  // fabs
  friend Balance fabs(const Balance& x)
  {
    //std::cout << "Balance::fabs(x)\n";
    Balance tmp(x); //std::cout << "tmp =\n"; tmp.show();
    if (x._value < 0.0) { 
      //std::cout << "negative value\n"; 
      //std::cout << "tmp's address = " << &tmp <<"\n";
      tmp = -x; //std::cout << "tmp's address = " << &tmp <<"\n";
      //tmp.show();
    }
    return tmp;
  }

  // Bernoulli
  friend Balance Bernoulli(const Balance& x)
  {
    Balance b, sx;
    Balance c = fabs(x); // std::cout << "x = " << x.getValue() << ", c = " << c.getValue() << "\n";;
    
    // New implementation, introduced on 2018-02-04.
    if(c < 2.502000000000000e-02) {
      sx=x*x;      
      b=1.0-x/2.0+sx/12.0*(1.0-sx/60.0*(1.0-sx/42.0));
    } else if(c < 1.500000000000000e-01) {
      sx=x*x;      
      b=1.0-x/2.0+sx/12.0*(1.0-sx/60.0*(1.0-sx/42.0*(1.0-sx/40.0*(1.0-0.02525252525252525252525*sx))));
    } else if (x > 150.01) { // (x > 709.0) {
      b = x*exp(-x); 
    } else {
      b=x/(exp(x)-1.0);
    }    

    // Previous implementation
    /*
    if(c < 2.502000000000000e-02) {
      sx=x*x;      
      b=1.0-x/2.0+sx/12.0*(1.0-sx/60.0*(1.0-sx/42.0));
    } else if(c < 1.500000000000000e-01) {
      sx=x*x;      
      b=1.0-x/2.0+sx/12.0*(1.0-sx/60.0*(1.0-sx/42.0*(1.0-sx/40.0*(1.0-0.02525252525252525252525*sx))));
    } else if(c > 710.0) {
      b=0.0;
    } else {
      b=x/(exp(x)-1.0);
    }
    */
    
    //if (std::isnan(b.getValue())) myReportError("Beroulli(x), isnan");
    /*
    if (b.isnan()) {
      x.show();
      b.show();
      (exp(x)-1.0).show();
      myReportError("Bernoulli(x), b.isnan()");
    }
    */
    return b;     
  }

 private:
  double _value;
  Grad _grad;
};

/*
class Grad {
 public:
  Grad() { _contents.clear(); }
  
  void clear() { _contents.clear(); }
  const std::map<Place,double>& getContents() const { return _contents; };
  std::map<Place,double>& getContents()             { return _contents; };  
  void set(Place place,double grad) {
    _contents.clear();
    _contents.insert(std::pair<Place,double>(place,grad));
  }
  void show() {
    std::map<Place,double>::iterator it;
    for (it=_contents.begin(); it!=_contents.end(); ++it) {
      Place place = it->first;
      VertexId vertexId = place.getVertexId();
      VariableId variableId = place.getVariableId();
      myReport("vertex = " + myIntToString(vertexId.getId()) + ", region = " + place.getRegionName() + ", variableId = " + myIntToString(variableId.getId()) + ", grad = " + myDoubleToString(it->second));
    }
  }

  // operator+=
  Grad& operator+=(const Grad& grad) { 
    std::map<Place,double>::const_iterator it;
    std::map<Place,double>::iterator       jt;
    for (it=(grad._contents).begin(); it!=(grad._contents).end(); ++it) {
      jt = _contents.find(it->first);
      if (jt==_contents.end()) _contents.insert(std::pair<Place,double>(it->first,it->second));
      else                     (jt->second) += (it->second);
    } 
  }

  // operator-=
  Grad& operator-=(const Grad& grad) { 
    std::map<Place,double>::const_iterator it;
    std::map<Place,double>::iterator       jt;
    for (it=(grad._contents).begin(); it!=(grad._contents).end(); ++it) {
      jt = _contents.find(it->first);
      if (jt==_contents.end()) _contents.insert(std::pair<Place,double>(it->first,-(it->second)));
      else                     (jt->second) -= (it->second);
    }  
  }

  private:
  std::map<Place,double> _contents;
};

class Balance {
 public:
 Balance(const double value=0.0) : _value(value) { _grad.clear(); }
 Balance(const double value,const Place place,double grad=1.0) : _value(value) {      
    _grad.set(place,grad);
  }
  
  Grad& getGrad() { return _grad; }
  double& getValue() { return _value; }

  void show() {
    myReport("Balance.show()");
    myReport("value = " + myDoubleToString( _value));
    _grad.show();
  }

  Balance& operator=(double value) {
    _grad.clear();
    _value = value;
    return *this;
  }

  // operator+=
  Balance& operator+=(const double value) { _value += value;                          return *this; }
  Balance& operator+=(const Balance& bal) { _value += bal._value; _grad += bal._grad; return *this; }

  // operator-=
  Balance& operator-=(const double value) { _value -= value;                          return *this; }
  Balance& operator-=(const Balance& bal) { _value -= bal._value; _grad -= bal._grad; return *this; }

  // operator-
  friend Balance operator-(const Balance& lhs,const Balance& rhs) { Balance tmp = lhs; return tmp -= rhs; }
  friend Balance operator-(const Balance& lhs,const double& rhs)  { Balance tmp = lhs; return tmp -= rhs; }
  friend Balance operator-(const double& lhs,const Balance& rhs)  { Balance tmp(lhs);  return tmp -= rhs; }  
  
 private:
  double _value;
  Grad _grad;
};
*/

#endif

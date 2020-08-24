#ifndef MCL_MATHEMATICS_H
#define MCL_MATHEMATICS_H

#include <vector>


namespace mcl
{
  typedef bool Boolean;
  typedef unsigned long long int Natural;
  typedef long long int Integer;
  typedef double Real;
  typedef std::vector<Boolean> BooleanSet;
  typedef std::vector<Natural> NaturalSet;
  typedef std::vector<Integer> IntegerSet;
  typedef std::vector<Real> RealSet;
  
  template <typename T>
  struct TypeMap { typedef void type; };
  
  #include "Math/TypeMap.h"
  
  template <typename T>
  using map_t = typename TypeMap<T>::type;
  
  
  template <typename T>
  map_t<T> Cast(T a) { return a; }
  
  
  
  const Real PI =     3.14159265358979323846;
  const Real TAU =    6.28318530717958647692;
  const Real EulerE = 2.71828182845904523536; 
  
  
  
  
  enum MathErr {
    undefined
  };
  
  
  
  
  
  template <class T> Boolean pow(Boolean, T);

  Natural pow(Natural, Boolean); //DEFINED
  Natural pow(Natural, Natural); //DEFINED
  Real pow(Natural, Integer); //DEFINED
  Real pow(Natural, Real);
  //Complex pow(Natural, Complex);

  Integer pow(Integer, Boolean);
  Integer pow(Integer, Natural);
  Real pow(Integer, Integer);
  
  
  Real exp(Real);
  
  
  
  
  
  Integer flog2(Real); //= floor(log_2(|a|))
  
  
  Boolean abs(Boolean a) { return a; }
  Natural abs(Natural a) { return a; }
  Natural abs(Integer a)
  {
    if (a < 0)
      return -a;
    return a;
  }
  Real abs(Real a)
  {
    if (a < 0)
      return -a;
    return a;
  }
  
  Integer sgn(Integer);
  
  
  
  
  
  NaturalSet   fact(Natural);
  NaturalSet  pfact(Natural);
  NaturalSet upfact(Natural);
  
  
  
  
  template <typename T, T id = 1>
  T product(std::vector<T>);
  
  
  
  
  
    //=================//
   //===DEFINITIONS===//
  //=================//
  template <class T> Boolean pow(Boolean a, T) { return a; }

  Natural pow(Natural a, Boolean b)
  {
    if (b)
      return a;
    if (a)
      return 1;
    throw(undefined);
  }
  Natural pow(Natural a, Natural b)
  {
    if (a || b)
    {
      Natural o = 1;
      for ( ; b; b >>= 1)
      {
        if (b & 1)
          o *= a;
        a *= a;
      }
      return o;
    }
    throw(undefined);
  }
  Real pow(Natural a, Integer b) { return b < 0 ? 1.0 / pow(a, (Natural)(-b)) : pow(a, (Natural)b); }

  Integer pow(Integer a, Boolean b)
  {
    if (b)
      return a;
    if (a)
      return 1;
    throw(undefined);
  }
  Integer pow(Integer a, Natural b)
  {
    Integer o = 1;
    for ( ; b; b >>= 1)
    {
      if (b & 1)
        o *= a;
      a *= a;
    }
    return o;
  }
  Real pow(Integer a, Integer b) { return b < 0 ? 1.0 / pow(a, (Natural)(-b)) : pow(a, (Natural)b); }
  
  Real exp(Real a)
  {
    //Compress into accuracy range by dividing by a power of two
    Integer Exponent = flog2(a); //Extract floating point exponent
    *((short int*)(&a + 1) - 1) -= (Exponent << 4); //"Divide" by 2^Exponent
    
    
    Real Sum = 1;
    
    Real Term = 1;
    for (Natural k = 1; k < 20/*Arbitrary*/; k++)
      Sum += (Term *= a/k);
      
    //Compute Sum^(2^Exponent)
    for ( ; Exponent; Exponent--)
      Sum *= Sum;
    return Sum;
  }
  
  
  
  
  
  Integer flog2(Real a)
  {
    Integer ret = *((short int*)(&a + 1) - 1);
    ret >>= 4;
    ret &= 0x07FF;
    ret -= 0x3FF;
    return ret;
  }
  
  
  
  
  
  
  
  
  Integer sgn(Integer a)
  {
    if (a > 0)
      return 1;
    if (a < 0)
      return -1;
    return 0;
  }
  
  
  
  NaturalSet fact(Natural a)
  {
    NaturalSet Factors;
    Natural f = 1;
    for ( ; f * f <= a; f++)
    {
      if (a % f == 0)
        Factors.push_back(f);
    }
    
    int i = Factors.size() - (f*f == a);
    
    while(i)
      Factors.push_back(a / Factors[--i]);
      
    return Factors;
  }
  NaturalSet pfact(Natural a)
  {
    if (a)
    {
      NaturalSet Factors;
      while ((a & 1) == 0)
      {
        Factors.push_back(2);
        a >>= 1;
      }
      
      for (Natural p = 3; p*p <= a; p += 2)
      {
        while (a % p == 0)
        {
          Factors.push_back(p);
          a /= p;
        }
      }
      
      if (a != 1)
        Factors.push_back(a);
        
      return Factors;
    }
    return {};
  }
  NaturalSet upfact(Natural a)
  {
    NaturalSet Factors;
    if ((a & 1) == 0)
    {
      Factors.push_back(2);
      a >>= 1;
      while ((a & 1) == 0)
        a >>= 1;
    }
    
    for (Natural p = 3; p*p <= a; p += 2)
    {
      if (a % p == 0)
      {
        Factors.push_back(p);
        a /= p;
        while (a % p == 0)
          a /= p;
      }
    }
    
    if (a != 1)
      Factors.push_back(a);
      
    return Factors;
  }
  
  
  
  template <typename T, T id>
  T product(std::vector<T> v)
  {
    T prod = id;
    for (T e : v)
      prod *= e;
    return prod;
  }
}


#endif
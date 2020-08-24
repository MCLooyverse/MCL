#ifndef MCL_LINEAR_ALGEBRA_H
#define MCL_LINEAR_ALGEBRA_H

#include <MCL/StrManip.h>
#include <initializer_list>
#include <type_traits>

#define RTYPE(a,o,b) decltype(std::declval<a>() o std::declval<b>())

namespace mcl
{
  template <typename T>
  using init_list = std::initializer_list<T>;
  /* Bruh
  template <bool B>
  using enable_if_t = typename std::enable_if<B>::type;
  */
  
  enum lialError {
    SizeDataMismatch
  };
  
  
  template <size_t L, typename T>
  class Vector;
  
  
  template <size_t H, size_t W, typename T>
  class Matrix
  {
    T m_arr[H*W];
    
  public:
    static constexpr size_t m_sz = H*W;
    
    
    //===CONSTRUCTORS===//
    Matrix(T init = T()); //DEFINED
    Matrix(T* arr, size_t sz);
    Matrix(init_list<init_list<T>> arr); //DEFINED
    
    
    //===OPERATORS===//
    template <typename U>
    Matrix<H,W,RTYPE(T,+,U)> operator+(const Matrix<H,W,U>&) const;
    template <typename U>
    Matrix<H,W,RTYPE(T,-,U)> operator-(const Matrix<H,W,U>&) const;
    template <size_t P, typename U>
    Matrix<H,P,RTYPE(T,*,U)> operator*(const Matrix<W,P,U>&) const;
    template <typename U>
    Matrix<H,W,RTYPE(T,*,U)> operator*(const U&) const;
    template <typename U>
    Matrix<H,W,RTYPE(T,/,U)> operator/(const U&) const;
    
    T& operator()(int, int = 0); //DEFINED
    T operator()(int, int = 0) const; //DEFINED
    
    
    ///===ASSIGNS===///
    template <typename U>
    Matrix<H,W,T>& operator+=(const Matrix<H,W,U>&);
    template <typename U>
    Matrix<H,W,T>& operator-=(const Matrix<H,W,U>&);
    template <typename U>
    Matrix<H,W,T>& operator*=(const Matrix<W,W,U>&);
    template <typename U>
    Matrix<H,W,T>& operator*=(const U&);
    template <typename U>
    Matrix<H,W,T>& operator/=(const U&);
    
    
    ///===CASTS===///
    template <typename U>
    operator Matrix<H,W,U>() const;
    
    
    //===METHODS===//
    T& at(int,int = 0); //DEFINED
    T at(int,int = 0) const; //DEFINED
    
    Vector<W,T> row(int) const;
    Vector<H,T> col(int) const;
    
    Matrix<W,H,T> transpose() const;
    //template <typename std::enable_if<H == W, int>::type = 0>
    Matrix<H,W,T> inverse() const = delete;
    //template <typename std::enable_if<H == W, int>::type = 0>
    T determinate() const = delete;
    
    template <typename U>
    Matrix<H,W,U> apply(U (*)(T)) const; //DEFINED
    template <typename U>
    Matrix<H,W,U> apply(U (*)(T,int,int)) const;
    template <typename U, typename... Args>
    Matrix<H,W,U> apply(U (*)(T,int,int,Args...), Args...) const;
    
    template <typename U>
    U reduce(U (*)(U,T), U) const;
    template <typename U>
    U reduce(U (*)(U,T,int,int), U) const;
    template <typename U, typename... Args>
    U reduce(U (*)(U,T,int,int,Args...), U, Args...) const;
    
    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;
    
    std::string toPrettyString() const; //DEFINED
    
    
    //===FRIENDS===//
    template <typename U>
    friend RTYPE(T,*,U) innerProduct(const Matrix<H,W,T>&, const Matrix<H,W,T>&);
    
    template <typename U>
    friend Matrix<H,W,RTYPE(U,*,T)> operator*(const U&, const Matrix<H,W,T>&);
  };
  
  
  
  
  
  template <size_t L, typename T>
  class Vector : public Matrix<L,1,T>
  {
    using Parent = Matrix<L,1,T>;
  public:
    //===CONSTRUCTORS===//
    Vector(T init = T()); //DEFINED
    Vector(init_list<T>);
    
    
    //===OPERATORS===//
    T& operator[](int); //DEFINED
    T operator[](int) const; //DEFINED
    
    
    //===METHODS===//
    T norm() const;
    
    
    //===FRIENDS===//
    friend Vector<L, T> crossProduct(const Vector<L,T>&, const Vector<L,T>&);
  };
  
  
  
  
  
    //=================//
   //===DEFINITIONS===//
  //=================//
  template <size_t H, size_t W, typename T>
  Matrix<H,W,T>::Matrix(T init) : m_arr{}
  {
    for (auto& e : m_arr)
      e = init;
  }
  template <size_t H, size_t W, typename T>
  Matrix<H,W,T>::Matrix(init_list<init_list<T>> arr) : m_arr{}
  {
    if (arr.size() != H)
      throw(SizeDataMismatch);
      
    int i = 0;
    for (auto r : arr)
    {
      if (r.size() != W)
        throw(SizeDataMismatch);
        
      for (auto e : r)
        m_arr[i++] = e;
    }
  }
  
  
  
  
  
  template <size_t H, size_t W, typename T>
  T& Matrix<H,W,T>::operator()(int i, int j) { return m_arr[i * W + j]; }
  template <size_t H, size_t W, typename T>
  T Matrix<H,W,T>::operator()(int i, int j) const { return m_arr[i * W + j]; }
  
  
  
  
  
  
  template <size_t H, size_t W, typename T>
  T& Matrix<H,W,T>::at(int i, int j) { return m_arr[i * W + j]; }
  template <size_t H, size_t W, typename T>
  T Matrix<H,W,T>::at(int i, int j) const { return m_arr[i * W + j]; }
  
  template <size_t H, size_t W, typename T>
  template <typename U>
  Matrix<H,W,U> Matrix<H,W,T>::apply(U (*func)(T)) const
  {
    Matrix<H,W,U> ret;
    for (int i = 0; i < H; i++)
    for (int j = 0; j < W; j++)
      ret(i,j) = func(at(i,j));
    return ret;
  }
  
  
  
  
  
  template <size_t H, size_t W, typename T>
  std::string Matrix<H,W,T>::toPrettyString() const
  {
    if (H == 1)
    {
      std::ostringstream Out("[ ");
      for (auto e : *this)
        Out << e << " ";
      Out << "]";
      return Out.str();
    }
    
    
    
    Matrix<H,W,std::string> Strings = this->apply<std::string>(
      [](T e) -> std::string {
        std::ostringstream s;
        s << e;
        return s.str();
      }
    );
    
    
    Vector<W, size_t> Widths(0);
    for (int i = 0; i < H; i++)
    for (int j = 0; j < W; j++)
    {
      if (Strings(i,j).length() > Widths[j])
        Widths[j] = Strings(i,j).length();
    }
    
    
    std::string Out("/ ");
    for (int j = 0; j < W; j++)
      Out += Pad(Strings(0,j), Widths[j], 2) + " ";
    Out += "\\\n";
    
    
    for (int i = 1; i < H-1; i++)
    {
      Out += "| ";
      for (int j = 0; j < W; j++)
        Out += Pad(Strings(i,j), Widths[j], 2) + " ";
      Out += "|\n";
    }
    
    Out += "\\ ";
    for (int j = 0; j < W; j++)
      Out += Pad(Strings(H-1,j), Widths[j], 2) + " ";
    Out += "/";
    
    return Out;
  }
  /* Too convinent to work
  template <size_t W, typename T>
  std::string Matrix<1,W,T>::toPrettyString() const
  {
    std::ostringstream Out("[ ");
    for (auto e : *this)
      Out << e << " ";
    return (Out << "]").str();
  }
  */
  
  
  
  
  
  template <size_t L, typename T>
  Vector<L,T>::Vector(T init) : Parent(init) { }
  
  
  template <size_t L, typename T>
  T& Vector<L,T>::operator[](int i) { return Parent::at(i); }
  template <size_t L, typename T>
  T Vector<L,T>::operator[](int i) const { return Parent::at(i); }
}


#endif
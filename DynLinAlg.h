#ifndef MCL_DYNAMIC_LINEAR_ALGEBRA_H
#define MCL_DYNAMIC_LINEAR_ALGEBRA_H

#include <MCL/StrManip.h>
#include <initializer_list>

//#define RTYPE(a,o,b) decltype(std::declval<a>() o std::declval<b>())


namespace mcl
{
  template <typename T>
  using init_list = std::initializer_list<T>;
  
  
  enum lialError {
    SizeMismatch,
    InconsistantWidth
  };
  
  
  template <typename T>
  class Vector
  {
    size_t m_l = 0;
    T* m_arr = 0;
    
  public:
    //===CONSTRUCTORS===//
    Vector();
    Vector(const Vector<T>&); //DEFINED
    Vector(size_t l, T init = T()); //DEFINED
    Vector(T* arr, size_t sz); //DEFINED
    Vector(init_list<T> arr); //DEFINED
    
    
    //===DESTRUCTOR===//
    ~Vector();
    
    
    //===OPERATORS===//
    template <typename U>
    Vector<T/*RTYPE(T,+,U) bruh*/> operator+(const Vector<U>&) const; //DEFINED
    template <typename U>
    Vector<T/*RTYPE(T,-,U) bruh*/> operator-(const Vector<U>&) const; //DEFINED
    template <typename U>
    T/*RTYPE(T,*,U) bruh*/ operator*(const Vector<U>&) const; //dot product //DEFINED
    template <typename U>
    Vector<T/*RTYPE(T,*,U) bruh*/> operator*(const U&) const; //DEFINED
    template <typename U>
    Vector<T/*RTYPE(T,/,U) bruh*/> operator/(const U&) const; //DEFINED
    
    T& operator[](int); //DEFINED
    T operator[](int) const; //DEFINED
    
    
    ///===ASSIGNS===///
    template <typename U>
    Vector<T>& operator+=(const Vector<U>&);
    template <typename U>
    Vector<T>& operator-=(const Vector<U>&);
    template <typename U>
    Vector<T>& operator*=(U);
    template <typename U>
    Vector<T>& operator/=(U);
    
    Vector<T>& operator=(const Vector<T>&); //DEFINED
    
    
    ///===CASTS===///
    template <typename U>
    operator Vector<U>() const; //DEFINED
    
    
    //===METHODS===//
    T norm() const;
    
    template <typename U>
    Vector<U> apply(U (*)(T)) const;
    template <typename U>
    Vector<U> apply(U (*)(T,int)) const;
    template <typename U, typename... Args>
    Vector<U> apply(U (*)(T,int,Args...), Args...) const;
    
    template <typename U>
    U reduce(U (*)(U,T), U) const;
    template <typename U>
    U reduce(U (*)(U,T,int), U) const;
    template <typename U, typename... Args>
    U reduce(U (*)(U,T,int,Args...), U, Args...) const;
    
    T* begin(); //DEFINED
    T* end(); //DEFINED
    const T* begin() const; //DEFINED
    const T* end() const; //DEFINED
    
    size_t size() const; //DEFINED
    
    
    //===FRIENDS===//
    template <typename U>
    friend T/*RTYPE(T,*,U) bruh*/ innerProduct(const Vector<T>&, const Vector<U>&);
    template <typename U>
    friend Vector<T/*RTYPE(T,*,U) bruh*/> crossProduct(const Vector<T>&, const Vector<U>&);
  };
  
  template <typename T, typename U>
  Vector<T> operator*(const T&, const Vector<U>&);
  template <typename T>
  std::ostream& operator<<(std::ostream&, const Vector<T>&);
  
  
  
  template <typename T>
  class Matrix
  {
    size_t m_h = 0, m_w = 0, m_sz = 0;
    Vector<T>* m_arr = 0;
    
  public:
    //===CONSTRUCTORS===//
    Matrix(size_t h, size_t w, T init = T()); //DEFINED
    Matrix(size_t h, size_t w, T* arr, size_t sz); //DEFINED
    Matrix(init_list<init_list<T>> arr); //DEFINED
    
    
    //===DESTRUCTOR===//
    ~Matrix();
    
    
    //===OPERATORS===//
    template <typename U>
    Matrix<T/*RTYPE(T,+,U) bruh*/> operator+(const Matrix<U>&) const;
    template <typename U>
    Matrix<T/*RTYPE(T,-,U) bruh*/> operator-(const Matrix<U>&) const;
    template <typename U>
    Matrix<T/*RTYPE(T,*,U) bruh*/> operator*(const Matrix<U>&) const;
    template <typename U>
    Matrix<T/*RTYPE(T,*,U) bruh*/> operator*(const U&) const;
    template <typename U>
    Matrix<T/*RTYPE(T,/,U) bruh*/> operator/(const U&) const;
    
    T& operator()(int, int = 0);
    T operator()(int, int = 0) const;
    
    
    ///===ASSIGNS===///
    template <typename U>
    Matrix<T>& operator+=(const Matrix<U>&);
    template <typename U>
    Matrix<T>& operator-=(const Matrix<U>&);
    template <typename U>
    Matrix<T>& operator*=(const Matrix<U>&);
    template <typename U>
    Matrix<T>& operator*=(const U&);
    template <typename U>
    Matrix<T>& operator/=(const U&);
    
    
    ///===CASTS===///
    template <typename U>
    operator Matrix<U>() const;
    
    
    //===METHODS===//
    T& at(int,int = 0);
    T at(int,int = 0) const;
    
    Vector<T>& row(int);
    Vector<T> row(int) const;
    Vector<T> col(int) const;
    
    Matrix<T> transpose() const;
    Matrix<T> inverse() const;
    T determinate() const;
    
    template <typename U>
    Matrix<U> apply(U (*)(T)) const; //DEFINED
    template <typename U>
    Matrix<U> apply(U (*)(T,int,int)) const; //DEFINED
    template <typename U, typename... Args>
    Matrix<U> apply(U (*)(T,int,int,Args...), Args...) const; //DEFINED
    
    template <typename U>
    U reduce(U (*)(U,T), U) const; //DEFINED
    template <typename U>
    U reduce(U (*)(U,T,int,int), U) const; //DEFINED
    template <typename U, typename... Args>
    U reduce(U (*)(U,T,int,int,Args...), U, Args...) const; //DEFINED
    
    /*
    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;
    */
    
    std::string toPrettyString(bool Sq = 0) const;
    
    
    size_t width() const;
    size_t height() const;
    size_t size() const;
    
    
    //===FRIENDS===//
    template <typename U>
    friend T/*RTYPE(T,*,U) bruh*/ innerProduct(const Matrix<T>&, const Matrix<T>&);
    
    template <typename U>
    friend Matrix<T/*RTYPE(U,*,T) bruh*/> operator*(const U&, const Matrix<T>&);
  };
  
  
  
  
  template <typename T>
  Vector<T>::Vector() : m_l(0), m_arr(0) { }
  template <typename T>
  Vector<T>::Vector(const Vector<T>& vec) : m_l(vec.m_l), m_arr(new T[m_l])
  {
    for (int i = 0; i < m_l; i++)
      m_arr[i] = vec[i];
  }
  template <typename T>
  Vector<T>::Vector(size_t l, T init) : m_l(l), m_arr(new T[m_l])
  {
    for (int i = 0; i < m_l; i++)
      m_arr[i] = init;
  }
  template <typename T>
  Vector<T>::Vector(T* arr, size_t sz) : m_l(sz), m_arr(new T[m_l])
  {
    for (int i = 0; i < m_l; i++)
      m_arr[i] = arr[i];
  }
  template <typename T>
  Vector<T>::Vector(init_list<T> arr) : m_l(arr.size()), m_arr(new T[m_l])
  {
    int i = 0;
    for (auto e : arr)
      m_arr[i++] = e;
  }
  
  
  template <typename T>
  Vector<T>::~Vector()
  {
    if (m_arr)
      delete[] m_arr;
  }
  
  
  
  template <typename T>
  template <typename U>
  Vector<T/*RTYPE(T,+,U) bruh*/> Vector<T>::operator+(const Vector<U>& a) const
  {
    auto ret = *this;
    ret += a;
    return ret;
  }
  template <typename T>
  template <typename U>
  Vector<T/*RTYPE(T,-,U) bruh*/> Vector<T>::operator-(const Vector<U>& a) const
  {
    auto ret = *this;
    ret -= a;
    return ret;
  }
  template <typename T>
  template <typename U>
  T/*RTYPE(T,*,U) bruh*/ Vector<T>::operator*(const Vector<U>& a) const
  {
    T Sum = 0;
    if (m_l != a.size())
      throw(SizeMismatch);
      
    for (int i = 0; i < m_l; i++)
      Sum += m_arr[i] * a[i];
    return Sum;
  }
  template <typename T>
  template <typename U>
  Vector<T/*RTYPE(T,*,U) bruh*/> Vector<T>::operator*(const U& a) const
  {
    auto ret = *this;
    ret *= a;
    return ret;
  }
  template <typename T>
  template <typename U>
  Vector<T/*RTYPE(T,/,U) bruh*/> Vector<T>::operator/(const U& a) const
  {
    auto ret = *this;
    ret /= a;
    return ret;
  }
  
  
  
  template <typename T>
  T& Vector<T>::operator[](int i) { return m_arr[i]; }
  template <typename T>
  T Vector<T>::operator[](int i) const { return m_arr[i]; }
  
  
  
  template <typename T>
  template <typename U>
  Vector<T>& Vector<T>::operator+=(const Vector<U>& b)
  {
    if (b.size() != m_l)
      throw(SizeMismatch);
      
    for (int i = 0; i < m_l; i++)
      m_arr[i] += b[i];
      
    return *this;
  }
  template <typename T>
  template <typename U>
  Vector<T>& Vector<T>::operator-=(const Vector<U>& b)
  {
    if (b.size() != m_l)
      throw(SizeMismatch);
      
    for (int i = 0; i < m_l; i++)
      m_arr[i] -= b[i];
      
    return *this;
  }
  template <typename T>
  template <typename U>
  Vector<T>& Vector<T>::operator*=(U b)
  {
    for (int i = 0; i < m_l; i++)
      m_arr[i] *= b;
    return *this;
  }
  template <typename T>
  template <typename U>
  Vector<T>& Vector<T>::operator/=(U b)
  {
    for (int i = 0; i < m_l; i++)
      m_arr[i] /= b;
    return *this;
  }
  
  
  
  template <typename T>
  Vector<T>& Vector<T>::operator=(const Vector<T>& vec)
  {
    if (m_l != vec.m_l)
    {
      if (m_arr)
        delete[] m_arr;
        
      m_l = vec.m_l;
      m_arr = new T[m_l];
    }
    
    for (int i = 0; i < m_l; i++)
      m_arr[i] = vec[i];
      
    return *this;
  }
  
  
  template <typename T> template <typename U>
  Vector<T>::operator Vector<U>() const
  {
    Vector<U> ret(m_l);
    for (int i = 0; i < m_l; i++)
      ret[i] = m_arr[i];
    return ret;
  }
  
  
  template <typename T>
  T* Vector<T>::begin() { return m_arr; }
  template <typename T>
  T* Vector<T>::end() { return m_arr + m_l; }
  template <typename T>
  const T* Vector<T>::begin() const { return m_arr; }
  template <typename T>
  const T* Vector<T>::end() const { return m_arr + m_l; }
  
  template <typename T>
  size_t Vector<T>::size() const { return m_l; }
  
  
  
  
  
  
  
  
  
  
  
  
  template <typename T>
  Matrix<T>::Matrix(size_t h, size_t w, T init) : m_h(h), m_w(w), m_sz(h*w), m_arr(new Vector<T>[h])
  {
    for (int i = 0; i < h; i++)
      new(m_arr + i) Vector<T>(w, init);
  }
  template <typename T>
  Matrix<T>::Matrix(size_t h, size_t w, T* arr, size_t sz) : m_h(h), m_w(w), m_sz(h*w), m_arr(new Vector<T>[h])
  {
    if (m_sz != sz)
      throw(SizeMismatch);
      
    for (int i = 0; i < h; i++)
      new(m_arr + i) Vector<T>(arr + i*w, w);
  }
  template <typename T>
  Matrix<T>::Matrix(init_list<init_list<T>> arr) : m_h(arr.size())
  {
    if (m_h)
    {
      m_w = arr.begin()->size();
      m_sz = m_h * m_w;
      m_arr = new Vector<T>[m_h];
      
      int i = 0;
      for (auto r : arr)
      {
        if (r.size() != m_w)
          throw(InconsistantWidth);
          
        new(m_arr + i++) Vector<T>(r);
      }
    }
  }
  
  
  template <typename T>
  Matrix<T>::~Matrix()
  {
    if (m_arr)
      delete[] m_arr;
  }
  
  
  
  template <typename T>
  T& Matrix<T>::operator()(int i, int j) { return m_arr[i][j]; }
  template <typename T>
  T Matrix<T>::operator()(int i, int j) const { return m_arr[i][j]; }
  
  
  
  
  template <typename T>
  T& Matrix<T>::at(int i, int j) { return m_arr[i][j]; }
  template <typename T>
  T Matrix<T>::at(int i, int j) const { return m_arr[i][j]; }
  
  
  template <typename T>
  Vector<T>& Matrix<T>::row(int i)
  {
    return m_arr[i];
  }
  template <typename T>
  Vector<T> Matrix<T>::row(int i) const
  {
    return m_arr[i];
  }
  template <typename T>
  Vector<T> Matrix<T>::col(int j) const
  {
    Vector<T> ret(m_h);
    for (int i = 0; i < m_h; i++)
      ret[i] = m_arr[i][j];
    return ret;
  }
  
  
  template <typename T>
  template <typename U>
  Matrix<U> Matrix<T>::apply(U (*func)(T)) const
  {
    Matrix<U> ret(m_h,m_w);
    for (int i = 0; i < m_h; i++)
    for (int j = 0; j < m_w; j++)
    {
      U DEBUGIntern = func(at(i,j));
      ret(i,j) = func(at(i,j));
    }
    return ret;
  }
  template <typename T>
  template <typename U>
  Matrix<U> Matrix<T>::apply(U (*func)(T,int,int)) const
  {
    Matrix<U> ret(m_h,m_w);
    for (int i = 0; i < m_h; i++)
    for (int j = 0; j < m_w; j++)
      ret(i,j) = func(at(i,j), i,j);
    return ret;
  }
  template <typename T>
  template <typename U, typename... Args>
  Matrix<U> Matrix<T>::apply(U (*func)(T,int,int,Args...), Args... args) const
  {
    Matrix<U> ret(m_h,m_w);
    for (int i = 0; i < m_h; i++)
    for (int j = 0; j < m_w; j++)
      ret(i,j) = func(at(i,j), i,j, args...);
    return ret;
  }
  
  template <typename T>
  template <typename U>
  U Matrix<T>::reduce(U (*func)(U,T), U init) const
  {
    for (int i = 0; i < m_h; i++)
    for (int j = 0; j < m_w; j++)
      init = func(init, at(i,j));
    return init;
  }
  template <typename T>
  template <typename U>
  U Matrix<T>::reduce(U (*)(U,T,int,int), U init) const
  {
    for (int i = 0; i < m_h; i++)
    for (int j = 0; j < m_w; j++)
      init = func(init, at(i,j), i,j);
    return init;
  }
  template <typename T>
  template <typename U, typename... Args>
  U Matrix<T>::reduce(U (*)(U,T,int,int,Args...), U init, Args... args) const
  {
    for (int i = 0; i < m_h; i++)
    for (int j = 0; j < m_w; j++)
      init = func(init, at(i,j), i,j, args...);
    return init;
  }
  
  
  template <typename T>
  std::string Matrix<T>::toPrettyString(bool Sq) const
  {
    if (m_h == 1)
    {
      std::ostringstream ret;
      ret << "[ ";
      for (auto e : *m_arr)
        ret << e << " ";
      return ret.str() + "]";
    }
    
    
    Matrix<std::string> Strings = this->apply<std::string>(
      [](T e) -> std::string {
        std::ostringstream s;
        s << e;
        return s.str();
      }
    );
    
    
    Vector<size_t> Widths(m_w, 0);
    for (int i = 0; i < m_h; i++)
    for (int j = 0; j < m_w; j++)
    {
      if (Strings(i,j).length() > Widths[j])
      {
        Widths[j] = Strings(i,j).length();
      }
    }
    
    
    std::string ret("");
    if (Sq)
    {
      for (int i = 0; i < m_h; i++)
      {
        ret += "[ ";
        for (int j = 0; j < m_w; j++)
          ret += Pad(Strings(i,j), Widths[j], 2) + " ";
        ret += "]\n";
      }
    }
    else
    {
      ret += "/ ";
      int i = 0;
      for (int j = 0; j < m_w; j++)
        ret += Pad(Strings(i,j), Widths[j], 2) + " ";
      ret += "\\\n";
      
      for (++i; i < m_h-1; i++)
      {
        ret += "| ";
        for (int j = 0; j < m_w; j++)
          ret += Pad(Strings(i,j), Widths[j], 2) + " ";
        ret += "|\n";
      }
      ret += "\\ ";
      for (int j = 0; j < m_w; j++)
        ret += Pad(Strings(i,j), Widths[j], 2) + " ";
      ret += "/";
    }
    
    return ret;
  }
  
  
  template <typename T>
  size_t Matrix<T>::width() const { return m_w; }
  template <typename T>
  size_t Matrix<T>::height() const { return m_h; }
  template <typename T>
  size_t Matrix<T>::size() const { return m_sz; }
  
  
  
  
  
  
  
  
  
  
  
  
  template <typename T, typename U>
  Vector<T/*RTYPE(T,*,U) bruh*/> operator*(const T& s, const Vector<U>& v)
  {
    Vector<T> ret(v.size());
    for (int i = 0; i < v.size(); i++)
      ret[i] = s * v[i];
    return ret;
  }
  
  
  
  template <typename T>
  std::ostream& operator<<(std::ostream& s, const Vector<T>& v)
  {
    s << "(";
    for (int i = 0; i < v.size()-1; i++)
      s << v[i] << ", ";
    s << v[v.size()-1] << ")";
    return s;
  }
}


#endif
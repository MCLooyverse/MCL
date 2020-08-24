#ifndef MCL_STRING_MANIPULATION_H
#define MCL_STRING_MANIPULATION_H

#include <string>
#include <sstream>
#include <vector>


namespace mcl
{
  using usint = unsigned short int;
  using uint = unsigned int;
  
  const std::string Digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  const std::string WhiteSpace = " \r\n\t";
  
  
  //0:  Success;  1:  Invalid string;  //2:  Value too large
  template <typename N> bool StoN(const std::string& s, N& n, usint b = 10);
  template <typename I> bool StoI(const std::string& s, I& i, usint b = 10);
  template <typename R> bool StoR(const std::string& s, R& r, usint b = 10);
  template <typename C> bool StoC(const std::string& s, C& c, usint b = 10);
  
  
  
  //opt:  0 -> just left;  1 -> just center, bias left;  2 -> just center, bias right;  3 -> just right
  std::string Pad(const std::string& in, size_t w, usint opt = 3, char pad = ' '); //DEFINED
  
  
  
  
  
  
  
  template <class T> std::string VtoS(const std::vector<T>& v, const std::string& s = ", ", const std::string& b = "{  }");
  template <class T> std::string VtoS(const T* v, uint len, const std::string& s = ", ", const std::string& b = "{  }");

  
  
  
  
  
  //Returns pos, where s[pos] = c, or s.length() if c is not in s
  uint InStr(char c, const std::string& s);
  
  bool IsWS(char c);
  bool IsAlpha(char c);
  bool IsLower(char c);
  bool IsUpper(char c);
  bool IsNum(char c);
  bool IsHex(char c);
  bool IgnoreWS(std::string::iterator& i, const std::string::iterator& e);
  
  
    //=================//
   //===DEFINITIONS===//
  //=================//
  template <typename N> bool StoN(const std::string& s, N& n, usint b)
  {
    n = 0;
    for (char c : s)
    {
      if (c == ' ' || c == ',')
        continue;
        
      uint pos = InStr(c, Digits.substr(0, b));
      if (pos == b)
        return 1;
        
      (n *= b) += pos;
    }
    
    return 0;
  }
  //template <typename I> usint StoI(const std::string& s, I& i, usint b = 10);
  //template <typename R> usint StoR(const std::string& s, R& r, usint b = 10);
  //template <typename C> usint StoC(const std::string& s, C& c, usint b = 10);
  std::string Pad(const std::string& in, size_t w, usint opt, char pad)
  {
    if (in.length() >= w)
      return in;
      
    const size_t dif = w - in.length();
    switch (opt)
    {
    case 0:
      return in + std::string(dif, pad);
    case 1:
      return std::string(dif/2, pad) + in + std::string(dif - dif/2, pad);
    case 2:
      return std::string(dif - dif/2, pad) + in + std::string(dif/2, pad);
    case 3:
    default:
      return std::string(dif, pad) + in;
    }
  }
  
  
  
  template <class T> std::string VtoS(const std::vector<T>& v, const std::string& s, const std::string& b)
  {
    if (v.size())
    {
      //std::cout << "[BOI: " << b.substr(0, b.length()/2) << "]";
      std::ostringstream os;//(b.substr(0, b.length()/2)); WHAT the FUCK
      os << b.substr(0, b.length()/2);
      for (int i = 0; i < v.size() - 1; i++)
        os << v[i] << s;
      os << v.back() << b.substr(b.length()/2);
      return os.str();
    }
    return b;
  }
  
  
  uint InStr(char c, const std::string& s)
  {
    for (int i = 0; i < s.length(); i++)
    {
      if (s[i] == c)
        return i;
    }
    return s.length();
  }
  
  bool IsWS(char c)
  {
    return InStr(c, WhiteSpace) != WhiteSpace.length();
  }
  bool IsLower(char c)
  {
    return 'a' <= c && c <= 'z';
  }
  bool IsUpper(char c)
  {
    return 'A' <= c && c <= 'A';
  }
  bool IsAlpha(char c)
  {
    return IsLower(c) || IsUpper(c);
  }
  bool IsNum(char c)
  {
    return '0' <= c && c <= '9';
  }
  bool IsHex(char c)
  {
    return '0' <= c && c <= '9' || 'A' <= c && c <= 'F' || 'a' <= c && c <= 'f';
  }
  bool IgnoreWS(std::string::iterator& i, const std::string::iterator& e)
  {
    while (i != e && IsWS(*i)) ++i;
    if (i == e)
      return 1;
    return 0;
  }
}


#endif
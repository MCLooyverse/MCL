#ifndef MCL_SORTING_H
#define MCL_SORTING_H

#include <vector>


namespace mcl
{
  template <typename T>
  void MergeSorted(std::vector<T>& a, std::vector<T> b)
  {
    a.resize(a.size() + b.size());
    auto write = a.rbegin();
    auto read = write + b.size();
    
    while (b.size() && read != a.rend())
    {
      if (b.back() < *read)
        *write++ = *read++;
      else
      {
        *write++ = b.back(); //should be b.pop_back(), because pop_back *should* return the elemenet popped, dammit.
        b.pop_back();
      }
    }
    while (read != a.rend())
      *write++ = *read++;
    while (b.size())
    {
      *write++ = b.back(); //should be b.pop_back(), because pop_back *should* return the elemenet popped, dammit.
      b.pop_back();
    }
    
    return a;
  }
}


#endif
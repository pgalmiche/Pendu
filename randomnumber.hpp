#ifndef RANDOMNUMBER_H
#define RANDOMNUMBER_H 1

#include <random>

template<typename T, typename Generator = std::mt19937>
class RandomNumber
{
  using dist_type = typename std::conditional< std::is_integral<T>::value,
                                               std::uniform_int_distribution<T>,
                                               std::uniform_real_distribution<T>
                                               >::type;
public :
  RandomNumber( T min, T max )
    :
    M_rd(),
    M_gen( M_rd() ),
    M_dist( min, max )
  {}

  T operator()() { return M_dist(M_gen); }
private :
  std::random_device M_rd;
  Generator M_gen;
  dist_type M_dist;
};

template<typename T, typename Generator = std::mt19937>
class RandomNumberNormal
{
  using dist_type = std::normal_distribution<T>;

public :
  RandomNumberNormal( T mean, T sigma )
    :
    M_rd(),
    M_gen( M_rd() ),
    M_dist( mean, sigma )
  {}

  T operator()() { return M_dist(M_gen); }
private :
  std::random_device M_rd;
  Generator M_gen;
  dist_type M_dist;
};

#endif

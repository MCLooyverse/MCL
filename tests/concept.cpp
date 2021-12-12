#include <iostream>
#include <string>



template <typename T, typename... Us>
struct sOneOf
{
	static const bool value = false;
};

template <typename T, typename... Us>
struct sOneOf<T, T, Us...>
{
	static const bool value = true;
};
template <typename T, typename U, typename... Us>
struct sOneOf<T, U, Us...>
{
	static const bool value = sOneOf<T, Us...>::value;
};



template <typename T, typename... Ts>
concept OneOf = sOneOf<T, Ts...>::value;



template <OneOf<unsigned int, int, float, double> T>
T f(T t)
{
	return 2 * t;
}


int main()
{
	std::cout << f(3) << " = " << f((short)3) << "\n";
}

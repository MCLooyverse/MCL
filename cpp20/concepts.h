#if __cplusplus < 202002L
	#error "Included version of mcl/concepts.h meant for at least C++20.  Do not directly include mcl/cpp20/concepts.h; use mcl/concepts.h instead."
#endif

#ifndef MCL_CONCEPTS_H
#define MCL_CONCEPTS_H

#include <concepts>
#include <ranges>


namespace mcl
{
	template <typename T, typename U>
	concept Addable = requires (T t, U u) { t + u; };

	template <typename T>
	concept ClosedAddition = requires (T a, T b) { { a + b } -> std::same_as<T>; };

	template <typename T>
	concept Truthy = std::convertable_to<T, bool>;

	template <typename T>
	concept Eq = requires (T a, T b) { { a == b } -> Truthy; { a != b } -> Truthy; };

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

	template <typename T, typename... Us>
	concept OneOf = sOneOf<T, Us...>::value;


	template <typename I, typename T>
	concept InputIterTo = std::input_iterator<I> &&
		requires (I i) { { *i } -> std::convertible_to<const T&>; };

	template <typename R, typename T>
	concept RangeOf = std::ranges::range<R> &&
		std::same_as<std::ranges::range_value_t<R>, T>;

	template <typename T, typename U>
	concept CanConstruct<T, U> = std::constructible_from<U, T>;
}


#endif


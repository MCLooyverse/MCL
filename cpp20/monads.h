#ifndef MCL_MONADS_H
#define MCL_MONADS_H

#include <functional>


namespace mcl
{
	template <template <typename> M>
	concept Monad = requires (T a, T b)
	{

	}

	template <typename T>
	class Maybe
	{
		T* p;

	public:
		Maybe();    //Nothing
		Maybe(T t); //Just t

		template <typename U>
		friend Maybe<U> operator>>=(const Maybe<T>&, const std::function<Maybe<U>(T)>&);
		template <typename U>
		friend Maybe<U> operator>>(const Maybe<T>&, const Maybe<U>&);
	};
}


#endif


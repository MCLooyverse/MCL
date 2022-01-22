#include "../typedefs.h"
#include "../concepts.h"
#include <array>
#include <algorithm>


namespace mcl {
	constexpr bool hostIsLE()
	{
		int a = 1;
		return *(byte*)&a;
	}

	enum class Endianness {
		native, little, big
	};

	constexpr bool isNative(Endianness e)
	{
		switch (e)
		{
		case Endianness::native: return true;
		case Endianness::little: return hostIsLE();
		case Endianness::big: return !hostIsLE();
		}
		return false; //That is, shut up.
	}


	template <std::integral T, size_t N = sizeof(T)>
		requires (N <= sizeof(T))
	std::array<byte, N> toBytes(T t, Endianness end = Endianness::native)
	{
		std::array<byte, N> out;
		byte* p = (byte*)&t;
		if (isNative(end))
			std::ranges::copy(p, p+N, out.begin());
		else
			std::ranges::copy_backward(p, p+N, out.begin());

		return out;
	}

	template <std::integral T, InputIterTo<byte> I, std::sentinel_for<I> S>
	T fromBytes(I i, S e, Endianness end = Endianness::native)
	{
		T t = 0;
		auto p = (byte*)&t;
		if (isNative(end))
			for (auto j = p; j != p + sizeof(T) && i != e; )
				*j++ = *i++;
		else
			for (auto j = p + sizeof(T) - 1; j != p && i != e; )
				*j-- = *i++;


		return t;
	}

	template <std::integral T, RangeOf<byte> R>
	T fromBytes(R r, Endianness end = Endianness::native)
	{
		return fromBytes<T>(std::begin(r), std::end(r), end);
	}
}


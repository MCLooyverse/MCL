#include "../typedefs.h"
#include <ranges>



namespace mcl
{
	template <typename T>
	concept Showable = requires (const T& t) { show<T>(t); };

	template <typename T>
	struct ShowConfig;


	template<std::integral T>
	struct ShowConfig<T>
	{
		//TODO: Create constructor that checks correctness.
		usint base = 6;
		bool rtl = 0;
		bool leftsign = 0;
		bool forcesign = 0;
		size_t minwidth = 0;
		enum PadWay {
			left, centerl, centerr, right,
			zeroes
		} padway = left;
	};


	template <std::integral T>
	std::string show(T n,
			const ShowConfig<T>& cf = ShowConfig<T>{})
	{
		using Cf = ShowConfig<T>;

		constexpr char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		constexpr char signs[] = "+-";
		std::string out;

		bool neg = n < 0;
		if (neg)
			n = -n;

		if (cf.rtl)
		{
			T place = 1;
			while (place * cf.base <= n)
				place *= cf.base;
			while (place)
			{
				out += digits[n / place];
				n %= place;
				place /= cf.base;
			}
		}
		else while (n)
		{
			out += digits[n % cf.base];
			n /= cf.base;
		}

		if (out.size() + (neg || cf.forcesign) < cf.minwidth)
		{
			size_t diff = cf.minwidth - out.size() - (neg || cf.forcesign);
			if (cf.padway == Cf::zeroes)
				out.insert(cf.rtl ? out.end() : out.begin(), diff, '0');

			if (neg || cf.forcesign)
				out.insert(cf.leftsign ? out.begin() : out.end(),
						1, signs[neg]);

			switch (cf.padway)
			{
			case Cf::left:
				out.insert(out.begin(), diff, ' ');
				break;
			case Cf::centerl:
				out.insert(out.end(), diff >> 1, ' ');
				out.insert(out.begin(), diff - (diff >> 1), ' ');
				break;
			case Cf::centerr:
				out.insert(out.begin(), diff >> 1, ' ');
				out.insert(out.end(), diff - (diff >> 1), ' ');
				break;
			case Cf::right:
				out.insert(out.begin(), diff, ' ');
				break;
			default: break;
			}
		}
		else if (neg || cf.forcesign)
			out.insert(cf.leftsign ? out.begin() : out.end(),
					1, signs[neg]);


		return out;
	}


	template<std::ranges::range C>
	struct ShowConfig<C>
	{
		using ItemT = std::ranges::range_value_t<C>;

		std::string_view sep = ", ";
		bool keeplast = 0;
		const ShowConfig<ItemT>& itemcf
			= ShowConfig<ItemT>{};
	};

	template <std::ranges::range C>
		requires Showable<std::ranges::range_value_t<C>>
	std::string show(const C& c,
			const ShowConfig<C>& cf = ShowConfig<C>{})
	{
		if (std::ranges::empty(c))
			return "";

		std::string out;
		for (const auto& e : c)
			(out += show(e, cf.itemcf)) += cf.sep;
		if (!cf.keeplast)
			out.erase(out.size() - cf.sep.size());

		return out;
	}
}


#ifndef MCL_PREFIX_TREE_CLASS_H
#define MCL_PREFIX_TREE_CLASS_H


#include <map>
#include <vector>
#include "../concepts.h"


namespace mcl
{
	auto to_pair(const auto& p)
	{
		const auto& [f, s] = p;
		return std::make_pair(f, s);
	}
	auto to_pair(auto&& p)
	{
		auto&& [f, s] = p;
		return std::make_pair(f, s);
	}

	template <typename K, typename T>
	class PrefixTree
	{
		std::map<K, PrefixTree> children;
		T* val;

	public:
		PrefixTree() : children{}, val{0}
		{ }
		PrefixTree(PrefixTree<K, T>&& p)
			: children{p.children}, val{p.val ? new T{*p.val} : 0}
		{ }
		PrefixTree(const PrefixTree<K, T>& p)
			: children{p.children}, val{p.val ? new T{*p.val} : 0}
		{ }

		PrefixTree(T&& t) : children{}, val{new T{t}}
		{ }
		PrefixTree(K&& k, T&& t) : children{{k, {t}}}, val{0}
		{ }

		/*
		template <InputIterTo<K> I,
						 std::sentinel_for<I> S>
		PrefixTree(I i, const S& e, T&& t) : children{}, val{0}
		{
			if (i == e)
				val = new T{t};
			else
				children.emplace(*i, { ++i, e, t });
		}

		template <RangeOf<K> R>
		PrefixTree(R&& r, T&& t) : PrefixTree(std::begin(r), std::end(r), t)
		{ }
		template <RangeOf<K> R>
		PrefixTree(const R& r, T&& t) : PrefixTree(std::begin(r), std::end(r), t)
		{ }


		template <std::input_iterator I,
						 std::sentinel_for<I> S>
			requires requires (const std::iter_value_t<I>& p) {
				{ p.first  } -> RangeOf<K>;
				{ p.second } -> std::same_as<T>;
			}
		PrefixTree(I i, const S& e) : children{}, val{0}
		{
			while (i != e)
			{
				(*this)[i->first] = i->second;
				++i;
			}
		}
		template <std::ranges::range R>
			requires requires (const std::ranges::range_value_t<R>& p) {
				{ p.first  } -> RangeOf<K>;
				{ p.second } -> std::same_as<T>;
			}
		PrefixTree(R&& r)
		{
			for (const auto& [k, v] : r)
			{
				auto tr = this;
				for (const auto& e : k)
					tr = &tr->children[e];
				tr->val = v;
			}
		}
		template <std::ranges::range R>
			requires requires (const std::ranges::range_value_t<R>& p) {
				{ p.first  } -> RangeOf<K>;
				{ p.second } -> std::same_as<T>;
			}
		PrefixTree(const R& r)
		{
			for (const auto& [k, v] : r)
			{
				auto tr = this;
				for (const auto& e : k)
					tr = &tr->children[e];
				tr->val = v;
			}
		}
		*/

		template <RangeOf<K> KS>
		PrefixTree(const std::map<KS, T>& r) : children{}, val{0}
		{
			for (const auto& [k, v] : r)
			{
				auto tr = this;
				for (const auto& e : k)
					tr = &tr->children[e];
				if (tr->val)
					*(tr->val) = v;
				else
					tr->val = new T{v};
			}
		}
		template <RangeOf<K> KS>
		PrefixTree(const std::initializer_list<std::pair<KS, T>>& r)
			: children{}, val{0}
		{
			for (const auto& [k, v] : r)
			{
				auto tr = this;
				for (const auto& e : k)
					tr = &tr->children[e];
				if (tr->val)
					*(tr->val) = v;
				else
					tr->val = new T{v};
			}
		}


		~PrefixTree()
		{
			if (val)
				delete val;
		}



		PrefixTree<K, T>* travel(const K& k)
		{
			try {
				return &children.at(k);
			} catch (std::out_of_range e) {
				return 0;
			}
		}

		std::vector<K> nexts() const
		{
			std::vector<K> out;
			for (const auto& [k, v] : children)
				out.push_back(k);
			return out;
		}

		bool has(const K& k) const
		{
			return children.count(k);
		}

		bool hasValue() const
		{
			return val;
		}

		T& value()
		{
			if (val)
				return *val;
			else
				throw std::logic_error("TODO");
		}

		const T& value() const
		{
			if (val)
				return *val;
			else
				throw std::logic_error("TODO");
		}


		//Fetch child at least depth with value.
		//Return 0 if multiple exist at equal least depth.
		PrefixTree<K, T>* nearestValued(size_t* found = 0)
		{
			size_t& mindepth = found ? *found : *new size_t;
			mindepth = 0;

			if (val)
			{
				if (!found)
					delete &mindepth;
				return val;
			}

			PrefixTree<K, T>* match = 0;
			for (auto& [k, tr] : children)
			{
				size_t depth;
				auto x = tr.nearestValued(&depth);
				if (x)
				{
					++depth;
					if (depth == mindepth)
					{
						if (!found)
							delete &mindepth;
						return 0;
					}
					if (depth < mindepth)
					{
						mindepth = depth;
						match = x;
					}
				}
			}

			if (!found)
				delete &mindepth;
			return match;
		}

		const PrefixTree<K, T>* nearestValued(size_t* found = 0) const
		{
			size_t& mindepth = found ? *found : *new size_t;
			mindepth = 0;

			if (val)
			{
				if (!found)
					delete &mindepth;
				return val;
			}

			const PrefixTree<K, T>* match = 0;
			for (auto& [k, tr] : children)
			{
				size_t depth;
				auto x = tr.nearestValued(&depth);
				if (x)
				{
					++depth;
					if (depth == mindepth)
					{
						if (!found)
							delete &mindepth;
						return 0;
					}
					if (depth < mindepth)
					{
						mindepth = depth;
						match = x;
					}
				}
			}

			if (!found)
				delete &mindepth;
			return match;
		}
	};
}


#endif


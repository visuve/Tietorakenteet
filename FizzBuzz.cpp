#include <cstdio>
#include <iterator>

constexpr size_t digits(size_t x)
{
	return 1ull
		+ (x >= 10ull)
		+ (x >= 100ull)
		+ (x >= 1000ull)
		+ (x >= 10000ull)
		+ (x >= 100000ull)
		+ (x >= 1000000ull)
		+ (x >= 10000000ull)
		+ (x >= 100000000ull)
		+ (x >= 1000000000ull)
		+ (x >= 10000000000ull)
		+ (x >= 100000000000ull)
		+ (x >= 1000000000000ull)
		+ (x >= 10000000000000ull)
		+ (x >= 100000000000000ull)
		+ (x >= 1000000000000000ull)
		+ (x >= 10000000000000000ull)
		+ (x >= 100000000000000000ull)
		+ (x >= 1000000000000000000ull)
		+ (x >= 10000000000000000000ull);
}

template<size_t N>
class to_string_t
{
public:
	constexpr to_string_t() noexcept
	{
		char* ptr = _buffer + sizeof(_buffer) - 1;

		for (size_t n = N; n; n /= 10)
		{
			*--ptr = "0123456789"[n % 10];
		}
	}

	constexpr operator const char* () const
	{
		return _buffer;
	}

private:
	char _buffer[digits(N) + 1] = {};
};

template<size_t N>
to_string_t<N> to_string;

template <size_t X> concept is_fizz = X % 3 == 0;
template <size_t X> concept is_buzz = X % 5 == 0;

template <size_t N>
class fizz_buzz {
public:
	constexpr fizz_buzz()
	{
		fill<N>();
	}

	auto begin() const
	{
		return std::begin(_data);
	}

	auto end() const
	{
		return std::end(_data);
	}

private:
	template <size_t X> requires (X > 0)
	constexpr void fill() {
		_data[X - 1] = value<X>();
		fill<X - 1>();
	}

	template <size_t X> requires (X <= 0)
	constexpr void fill()
	{
	};

	template<size_t X> requires is_fizz<X>
	constexpr const char* value()
	{
		return "Fizz";
	}

	template<size_t X> requires is_buzz<X>
	constexpr const char* value()
	{
		return "Buzz";
	}

	template<size_t X> requires (is_fizz<X>&& is_buzz<X>)
		constexpr const char* value()
	{
		return "FizzBuzz";
	}

	template<size_t X> requires (!is_fizz<X> && !is_buzz<X>)
	constexpr const char* value()
	{
		return to_string<X>;
	}

	const char* _data[N] = {};
};

int main()
{
	constexpr fizz_buzz<50> fb;

	for (const char* x : fb)
	{
		puts(x);
	}

	return 0;
}
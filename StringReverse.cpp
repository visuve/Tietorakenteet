#include <iostream>

template <typename T, typename size_t N>
constexpr void reverse_any(T* data)
{
	for (size_t i = 0; i < N / 2; ++i)
	{
		std::swap(data[i], data[N - i - 1]);
	}
}

template <typename T, typename size_t N>
constexpr void reverse_array(T(&data)[N])
{
	reverse_any<T, N>(data);
}

template<typename T>
concept Character = 
	std::is_same_v<char, T> ||
	std::is_same_v<wchar_t, T> ||
	std::is_same_v<char8_t, T> ||
	std::is_same_v<char16_t, T> ||
	std::is_same_v<char32_t, T>;

template <typename T, typename size_t N>
constexpr void reverse_string(T(&data)[N]) requires Character<T>
{
	reverse_any<T, N - 1>(data);
}

int main()
{
	{
		char test[] = "foo bar";
		reverse_string(test);
		puts(test);
	}
	{
		int test[] = { 1, 2, 3, 4, 5, 6 };
		reverse_array(test);

		std::copy(
			std::begin(test),
			std::end(test),
			std::ostream_iterator<int>(std::cout, "\n"));
	}


	return 0;
}
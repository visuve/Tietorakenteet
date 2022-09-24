#include <algorithm>
#include <cassert>
#include <exception>
#include <iostream>

// TODO: add some kind of "EOF"
template <class T>
class ring_buffer
{
public:
	ring_buffer(size_t capacity) :
		_data(new T[capacity]),
		_capacity(capacity)
	{
	}

	// TODO: implement these?
	ring_buffer(ring_buffer&) = delete;
	ring_buffer(ring_buffer&&) = delete;
	ring_buffer& operator = (ring_buffer&) = delete;
	ring_buffer& operator = (ring_buffer&&) = delete;

	~ring_buffer()
	{
		delete[] _data;
	}

	ring_buffer& operator << (const T& x)
	{
		_data[_index] = x;
		++_index %= _capacity;

		_count = std::clamp(++_count, size_t(0), _capacity);
		return *this;
	}

	ring_buffer& operator >> (T& x)
	{
		if (!_count)
		{
			throw std::out_of_range("no data");
			//return *this;
		}

		if (_index > 0)
		{
			--_index;
		}
		else
		{
			_index = _capacity - 1;
		}

		x = _data[_index];

		_count = std::clamp(--_count, size_t(0), _capacity);
		return *this;
	}

	T& operator[] (size_t i)
	{
		if (i >= _count)
		{
			throw std::out_of_range("accessed uninitialized value");
		}

		return _data[i];
	}

	operator bool() const
	{
		return _count && _count <= _capacity;
	}

	auto begin()
	{
		return _data;
	}

	auto end()
	{
		return _data + _count;
	}

private:
	T* _data;
	const size_t _capacity;
	size_t _index = 0;
	size_t _count = 0;
};

int main()
{
	{
		ring_buffer<int> rb(5);

		rb << 1;
		rb << 2;
		rb << 3;
		rb << 4;

		for (int x : rb)
		{
			std::cout << x << std::endl;
		}

		rb << 5;
		rb << 6;
		rb << 7;

		std::cout << "\nAfter inserting 3 new elements\n" << std::endl;

		for (int x : rb)
		{
			std::cout << x << std::endl;
		}

		int x;
		rb >> x;
		assert(x == 7);

		rb >> x;
		assert(x == 6);

		rb >> x;
		assert(x == 5);

		rb >> x;
		assert(x == 4);

		rb >> x;
		assert(x == 3);

		bool threw_exception = false;

		try
		{
			rb >> x; // no data
		}
		catch (const std::out_of_range&)
		{
			threw_exception = true;
		}

		assert(threw_exception);
		threw_exception = false;

		try
		{
			std::cout << rb[5];
		}
		catch (const std::out_of_range&)
		{
			threw_exception = true;
		}

		assert(threw_exception);
	}
	{
 		ring_buffer<int> rb(5);

		rb << 1;
		rb << 2;
		rb << 3;
		rb << 4;
		rb << 5;

		std::cout << "\nExtracting all from a new ring buffer\n" << std::endl;

		int x;
		int count = 0;

		while (rb) // TODO: I would like to call "while (rb >> x)" and "extract" all
		{
			rb >> x;
			std::cout << x << std::endl;
			++count;
		}

		assert(count == 5);
	}

	return 0;
}
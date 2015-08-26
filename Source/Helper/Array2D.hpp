#ifndef LP_ARRAY2D_HPP
#define LP_ARRAY2D_HPP

#include <vector>
#include <cassert>

namespace lp
{

template<typename T>
class Array2D
{
    public:
        Array2D();
		Array2D(std::size_t width, std::size_t height);

		std::size_t width() const;
		std::size_t height() const;

		void resize(std::size_t width, std::size_t height);

		template<typename T>
		void set(std::size_t x, std::size_t y, T const& value);

		template<typename T>
		const T& get(std::size_t x, std::size_t y) const;

	protected:
		std::vector<std::vector<T>> mArray;
};

template <typename T>
Array2D<T>::Array2D()
{
}

template <typename T>
Array2D<T>::Array2D(std::size_t width, std::size_t height)
{
    resize(width, height);
}

template <typename T>
std::size_t Array2D<T>::width() const;
{
	return mArray.size();
}

template <typename T>
std::size_t Array2D<T>::height() const
{
	if (width() >= 1)
	{
		return mArray[0].size();
	}
	else
	{
		return 0;
	}
}

template <typename T>
void Array2D<T>::resize(std::size_t width, std::size_t height)
{
	mArray.clear();
	mArray.resize(width);
	for (std::size_t i = 0; i < width; i++)
	{
		mArray[i].resize(height);
	}
}

template<typename T>
void Array2D<T>::set(std::size_t x, std::size_t y, T const& value)
{
	if (x >= 0 && x < width() && y >= 0 && y < height())
	{
		mArray[x][y] = value;
	}
}

template<typename T>
const T& Array2D<T>::get(std::size_t x, std::size_t y)
{
	assert(x >= 0 && x < width() && y >= 0 && y < height());
	return mArray[x][y];
}

} // namespace lp

#endif // LP_ARRAY2D_HPP

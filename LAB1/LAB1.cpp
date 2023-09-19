#include <iostream>
#include <random>

using std::unique_ptr;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::cout;
using std::endl;

class IntArray
{
public:
	IntArray(size_t size) : m_array(new int[size]), m_array_length(size) {};
	IntArray() : m_array(nullptr), m_array_length(0) {};

	int get(size_t index)
	{
		return m_array[index];
	};

	void set(size_t index, int value)
	{
		m_array[index] = value;
	};

	int length()
	{
		return m_array_length;
	};

	static void random_fill(IntArray& array, uniform_int_distribution <int>& distribution, mt19937& generator)
	{
		for (int i = 0; i < array.length(); ++i)
		{
			array.set(i, distribution(generator));
		}
	};

	friend std::ostream& operator<< (std::ostream& os, IntArray& array)
	{
		for (int i = 0; i < array.length(); ++i)
		{
			os << array.get(i) << " ";
		}
		return os;
	}

private:
	unique_ptr <int[]>m_array;
	size_t m_array_length;
};

class IntArray2D
{
public:
	IntArray2D(size_t rows, size_t columns) : m_ammount_rows(rows), m_ammount_columns(columns)
	{
		m_array = new IntArray[rows];
		for (int i = 0; i < rows; ++i)
		{
			m_array[i] = IntArray(columns);
		};
	};

	int columns()
	{
		return m_ammount_columns;
	};

	int rows()
	{
		return m_ammount_rows;
	};

	int get(size_t row, size_t col)
	{
		return m_array[row].get(col);
	};

	void set(size_t row, size_t col, int value)
	{
		m_array[row].set(col, value);
	};

	static void random_fill(IntArray2D& array, uniform_int_distribution<int>& distribution, mt19937& generator)
	{
		for (int i = 0; i < array.rows(); ++i)
		{
			for (int j = 0; j < array.columns(); ++j)
			{
				array.set(i, j, distribution(generator));
			}
		}
	};

	friend std::ostream& operator<< (std::ostream& os, IntArray2D& array)
	{
		for (int i = 0; i < array.rows(); ++i)
		{
			os << array.m_array[i] << " " << endl;
		}
		return os;
	};

private:
	IntArray* m_array;
	size_t m_ammount_rows;
	size_t m_ammount_columns;
};

int main()
{
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<int> distribution(0, 9);

	IntArray array(10);
	IntArray::random_fill(array, distribution, generator);

	cout << array << endl << endl;

	IntArray2D array2d(10, 5);
	IntArray2D::random_fill(array2d, distribution, generator);

	cout << array2d << endl;

	return 0;
}

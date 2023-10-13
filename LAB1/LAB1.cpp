#include <iostream>
#include <random>

using std::unique_ptr;
using std::cout;

class CIntArray
{
public:
	// Конструкторы
	CIntArray();
	CIntArray(size_t size);

	// Геттеры
	int getElement(size_t element)
	{
		return m_array[element];
	}

	size_t getLength()
	{
		return m_array_length;
	};

	// Сеттер
	void setElement(size_t element, int value)
	{
		m_array[element] = value;
	};

	// Заполнитель
	static void fillRandom(CIntArray& array, std::uniform_int_distribution <int>& distribution, std::mt19937& generator)
	{
		for (int i = 0; i < array.getLength(); ++i)
		{
			array.setElement(i, distribution(generator));
		}
	};

	// Перегрузка
	friend std::ostream& operator<< (std::ostream& os, CIntArray& array)
	{
		for (int i = 0; i < array.getLength(); ++i)
		{
			os << array.getElement(i) << " ";
		}
		return os;
	}

private:
	unique_ptr <int[]>m_array;
	size_t m_array_length;
};

CIntArray::CIntArray() : m_array(nullptr), m_array_length(0) {}
CIntArray::CIntArray(size_t size) : m_array(new int[size]), m_array_length(size) {}

class CIntArray2D
{
public:
	// Конструктор
	CIntArray2D(size_t rows, size_t columns);

	// Геттеры
	size_t getColumns()
	{
		return m_array_columns;
	};

	size_t getRows()
	{
		return m_array_rows;
	};

	int getElement(size_t row, size_t column)
	{
		return m_array[row].getElement(column);
	};

	// Сеттер
	void setElement(size_t row, size_t column, int value)
	{
		m_array[row].setElement(column, value);
	};

	// Заполнитель
	static void fillRandom(CIntArray2D& array, std::uniform_int_distribution<int>& distribution, std::mt19937& generator)
	{
		for (int i = 0; i < array.getRows(); ++i)
		{
			for (int j = 0; j < array.getColumns(); ++j)
			{
				array.setElement(i, j, distribution(generator));
			}
		}
	};

	// Перегрузка
	friend std::ostream& operator<< (std::ostream& os, CIntArray2D& array)
	{
		for (int i = 0; i < array.getRows(); ++i)
		{
			os << array.m_array[i] << "\n";
		}
		return os;
	};

private:
	CIntArray* m_array;
	size_t m_array_rows;
	size_t m_array_columns;
};

CIntArray2D::CIntArray2D(size_t rows, size_t columns) : m_array_rows(rows), m_array_columns(columns)
{
	m_array = new CIntArray[rows];
	for (int i = 0; i < rows; ++i)
	{
		m_array[i] = CIntArray(columns);
	};
}

int main()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(0, 9);

	CIntArray array(10);
	CIntArray::fillRandom(array, distribution, generator);

	cout << array << "\n\n";

	CIntArray2D array2d(5, 5);
	CIntArray2D::fillRandom(array2d, distribution, generator);

	cout << array2d;

	return 0;
}

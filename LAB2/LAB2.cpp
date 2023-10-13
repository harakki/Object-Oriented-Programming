#include <iostream>
#include <random>

using std::cout;
using std::endl;
using std::mt19937;
using std::random_device;
using std::uniform_int_distribution;
using std::unique_ptr;

class CIntArray
{
  public:
    // Конструкторы
    CIntArray();
    CIntArray(size_t size);

    // Геттеры, сеттеры и заполнители
    int getElement(size_t element)
    {
        return m_array[element];
    }

    size_t getLength()
    {
        return m_array_length;
    };

    void setElement(size_t element, int value)
    {
        m_array[element] = value;
    };

    static void fillRandom(CIntArray &array, uniform_int_distribution<int> &distribution, mt19937 &generator)
    {
        for (int i = 0; i < array.getLength(); ++i)
        {
            array.setElement(i, distribution(generator));
        }
    };

    friend std::ostream &operator<<(std::ostream &os, CIntArray &array)
    {
        for (int i = 0; i < array.getLength(); ++i)
        {
            os << array.getElement(i) << " ";
        }
        return os;
    }

  private:
    unique_ptr<int[]> m_array;
    size_t m_array_length;
};

CIntArray::CIntArray() : m_array(nullptr), m_array_length(0)
{
}
CIntArray::CIntArray(size_t size) : m_array(new int[size]), m_array_length(size)
{
}

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
    static void fillRandom(CIntArray2D &array, std::uniform_int_distribution<int> &distribution,
                           std::mt19937 &generator)
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
    friend std::ostream &operator<<(std::ostream &os, CIntArray2D &array)
    {
        return array.to_stream(os);
    };

  private:
    CIntArray *m_array;
    size_t m_array_rows;
    size_t m_array_columns;

    virtual std::ostream &to_stream(std::ostream &os) = 0;
};

CIntArray2D::CIntArray2D(size_t rows, size_t columns) : m_array_rows(rows), m_array_columns(columns)
{
    m_array = new CIntArray[rows];
    for (int i = 0; i < rows; ++i)
    {
        m_array[i] = CIntArray(columns);
    };
}

class CRightDiagonalArray2D : public CIntArray2D
{
  private:
    std::ostream &to_stream(std::ostream &os) override
    {
        int n = (int)getRows();
        int m = (int)getColumns();

        for (int k = 0; k < n + m - 1; ++k)
        {
            int i_start = std::max(0, k - m + 1);
            int i_end = std::min(k, n - 1);

            for (int i = i_start; i <= i_end; ++i)
            {
                int j = k - i;
                os << getElement(i, j) << " ";
            }
            os << "\n";
        }

        return os;
    }
};

class CLeftDiagonalArray2D : public CIntArray2D
{
  public:
    CLeftDiagonalArray2D(size_t rows, size_t columns) : CIntArray2D(rows, columns)
    {
    }

  private:
    std::ostream &to_stream(std::ostream &os) override
    {
        int n = (int)getRows();
        int m = (int)getColumns();

        for (int k = 0; k < n + m - 1; ++k)
        {
            int j_start = std::max(0, k - n + 1);
            int j_end = std::min(k, m - 1);

            for (int j = j_start; j <= j_end; ++j)
            {
                int i = k - j;
                os << getElement(i, j) << " ";
            }
            os << "\n";
        }

        return os;
    }
};

int main()
{
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, 9);

    CIntArray array(10);
    CIntArray::fillRandom(array, distribution, generator);

    cout << array << "\n\n";

    CIntArray2D *array2d = new CLeftDiagonalArray2D(5, 5);
    CIntArray2D::fillRandom(*array2d, distribution, generator);

    cout << *array2d;

    return 0;
}
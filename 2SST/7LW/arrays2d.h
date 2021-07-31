#ifndef ARRAYS_2D
#define ARRAYS_2D

namespace array2d
{

    template <class T>
    void delete_(T **array, unsigned rows)
    {
        for (unsigned row = 0; row < rows; row++)
        {
            if (array[row] != nullptr)
            {
                delete[] array[row];
            }
        }
        delete[] array;
    }

    template <class T>
    T **init(const unsigned rows, const unsigned collumns, T value = 0)
    {
        if (rows == 0 or collumns == 0)
            return nullptr;
        else
        {
            T **array = new T *[rows];
            if (value == 0)
            {
                for (unsigned i = 0; i < rows; i++)
                {
                    array[i] = new T[collumns]();
                }
            }
            else
            {
                for (unsigned i = 0; i < rows; i++)
                {
                    array[i] = new T[collumns]{value};
                }
            }

            return array;
        }
    }

} // namespace array2d

#endif
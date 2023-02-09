using System;

class Matrix<T> where T : IComparable, IFormattable
{
    protected T[,] array;

    public Matrix(int width, int height)
    {
        array = new T[width, height];
    }

    public Matrix(T[,] array)
    {
        this.array = array;
    }

    public T GetItem(int x, int y)
    {
        if (array.Length >= x || array.GetLength(1) >= y)
        {
            throw new Exception("index out of range");
        }

        return array[x, y];
    }

    public static Matrix<T> operator -(Matrix<T> m)
    {
        var result = new Matrix<T>(m.array.GetLength(0), m.array.GetLength(1));
        for (int i = 0; i < m.array.GetLength(0); ++i)
        {
            for (int j = 0; j < m.array.GetLength(1); ++j)
            {
                dynamic temp = m.array[i,j];
                result.array[i,j] = -temp;
            }
        }
        return result;
    }

    public static Matrix<T> operator -(Matrix<T> m1, Matrix<T> m2)
    {
        return m1 + (-m2);
    }

    public static Matrix<T> operator +(Matrix<T> m1, Matrix<T> m2)
    {
        if (m1.array.GetLength(0) != m2.array.GetLength(0) || m1.array.GetLength(1) != m2.array.GetLength(1))
        {
            throw new Exception("operation cannot be done");
        }

        var result = new Matrix<T>(m1.array.GetLength(0), m1.array.GetLength(1));
        for (int i = 0; i < m1.array.GetLength(0); ++i)
        {
            for (int j = 0; j < m1.array.GetLength(1); ++j)
            {
                dynamic a = m1.array[i, j];
                dynamic b = m2.array[i, j];
                result.array[i, j] = a + b;
            }
        }

        return result;
    }

    public static Matrix<T> operator *(Matrix<T> m1, Matrix<T> m2)
    {
        if (m1.array.GetLength(1) != m2.array.GetLength(0))
        {
            throw new Exception("operation cannot be done");
        }

        var result = new Matrix<T>(m1.array.GetLength(0), m2.array.GetLength(1));

        for (int i = 0; i < m1.array.GetLength(0); ++i)
        {
            for (int j = 0; j < m2.array.GetLength(1); ++j)
            {
                dynamic s = Activator.CreateInstance<T>();
                for (int k = 0; k < m1.array.GetLength(1); ++k)
                {
                    dynamic a = m1.array[i, k];
                    dynamic b = m2.array[k, j];
                    s += a * b;
                }
                result.array[i, j] = s;
            }
        }

        return result;
    }

    public void Print()
    {
        for (int i = 0; i < array.GetLength(0); ++i)
        {
            for (int j = 0; j < array.GetLength(1); ++j)
            {
                Console.Write($"{array[i, j]}  ");
            }
            Console.Write("\n");
        }
    }
}

class MatrixSquare<T> : Matrix<T> where T : IComparable, IFormattable
{
    public MatrixSquare(T[,] array) : base(array)
    {
        if (array.GetLength(0) != array.GetLength(1))
        {
            throw new Exception("this is not a square array");
        }
    }

    public bool IsDiagonal()
    {
        for (int i = 0; i < array.GetLength(0); ++i)
        {
            for (int j = 0; j < array.GetLength(1); ++j)
            {
                if (i != j)
                {
                    dynamic temp = array[i, j];
                    if (temp != 0)
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }
}

// vim: fdl=1

#include <iostream>
//the structure of Sparse Matrix
struct SparseMat
{
    int t_rows, t_cols; //total rows,total columns
    int **array; //array to store non zero value and position in sparse matrix
};

SparseMat createSparseMatrix(int rows, int cols)
{
    SparseMat matrix;
    matrix.t_rows = rows;
    matrix.t_cols = cols;

    matrix.array = new int *[rows];
    int i = 0;
    while (i < rows)
    {
        matrix.array[i] = new int[3](); //init a array of lengtth 3 for row,column and value
        i++;
    }
    return matrix;
}

void addNum(SparseMat &matrix, int row, int col, int number)
{
    for (int i = 0; i < matrix.t_rows; i++)
    {
        if (matrix.array[i][0] == -1)
        { //store row col and value  of the number in sparse matrix
            matrix.array[i][0] = row;
            matrix.array[i][1] = col;
            matrix.array[i][2] = number; 
            break;
        }
    }
}

int main()
{
    int rows, cols, nonZero;
    std::cout << "enter number of rows: ";
    std::cin >> rows;
    std::cout << "enter number of columns: ";
    std::cin >> cols;
    std::cout << "enter number of Non zero elements: ";
    std::cin >> nonZero;

    SparseMat matrix = createSparseMatrix(nonZero, 3);

    for (int i = 0; i < matrix.t_rows; i++)
    {
        matrix.array[i][0] = -1;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int value;
            std::cout << "Enter value for element at row " << i << " and column " << j << ": ";
            std::cin >> value;
            if (value != 0)
            {
                addNum(matrix, i, j, value);
            }
        }
    }

    std::cout << "Matrix:" << std::endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int value=0; //default value 0
            for (int k = 0; k < nonZero; k++)
            {
                // row and column are matched
                if (matrix.array[k][0] == i && matrix.array[k][1] == j)
                {
                    value=matrix.array[k][2];
                }
            }
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}

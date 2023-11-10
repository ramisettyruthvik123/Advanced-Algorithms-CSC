#include <iostream>
#include <stdexcept>

//class Node represents sparse matrix element
class ElementNode {
public:
    int value;
    int total_rows;
    int total_cols;
    ElementNode* next;

    ElementNode(int val, int r, int c) {
        value = val;
        total_rows = r;
        total_cols = c;
        next = nullptr;
    } 
};

class Sparse {
public:
    int rows;
    int cols;
    ElementNode** heads;

    Sparse(int r, int c) {
        rows = r;
        cols =  c;
        heads = new ElementNode*[rows]();
    }

    void insertElement( int row, int col,int value) {
        if (row < 0  || col >= cols || row >= rows || col < 0) {
            throw std::out_of_range("Index out of bounds");
        }

        ElementNode* new_node = new ElementNode(value, row, col);
        if (!heads[row]) {
            heads[row] = new_node;
        } else {
            ElementNode* current = heads[row];
            while (current->next) {
                current = current->next;
            }
            current->next = new_node;
        }
    }
};

int main() {
    
    std::cout << "Enter number of rows: ";
    int cols, rows;
    std::cin >> rows;
    std::cout << "Enter number of columns: ";
    std::cin >> cols;

    Sparse matrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int value;
            std::cout << "Enter a value for row " << i << " and column " << j << ": ";
            std::cin >> value;
            matrix.insertElement(i, j,value);
        }
    }

    std::cout << "**********Sparse Matrix:**********\n";
            for (int row = 0; row < rows; ++row) {
            ElementNode* current = matrix.heads[row];
            int row_values[cols] = {0};
            while (current) {
                row_values[current->total_cols] = current->value;
                current = current->next;
            }
            for (int col = 0; col < cols; ++col) {
                std::cout << row_values[col] << " ";
            }
            std::cout << std::endl;
        }

    return 0;
}

#include <iostream>
#include <stdexcept>

class Node {
public:
    int value;
    int row;
    int col;
    Node* next;

    Node(int val, int r, int c) : value(val), row(r), col(c), next(nullptr) {}
};

class SparseMatrix {
private:
    int rows;
    int cols;
    Node** heads;

public:
    SparseMatrix(int r, int c) : rows(r), cols(c) {
        heads = new Node*[rows]();
    }

    void insert(int value, int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Row or column index out of bounds");
        }

        Node* new_node = new Node(value, row, col);
        if (!heads[row]) {
            heads[row] = new_node;
        } else {
            Node* current = heads[row];
            while (current->next) {
                current = current->next;
            }
            current->next = new_node;
        }
    }

    int get(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Row or column index out of bounds");
        }

        Node* current = heads[row];
        while (current) {
            if (current->col == col) {
                return current->value;
            }
            current = current->next;
        }
        return 0;  // Return 0 for elements not explicitly set
    }

    void display() {
        for (int row = 0; row < rows; ++row) {
            Node* current = heads[row];
            int row_values[cols] = {0};
            while (current) {
                row_values[current->col] = current->value;
                current = current->next;
            }
            for (int col = 0; col < cols; ++col) {
                std::cout << row_values[col] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    int rows, cols;
    std::cout << "Enter the number of rows: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns: ";
    std::cin >> cols;

    SparseMatrix matrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int value;
            std::cout << "Enter value at row " << i << " and column " << j << ": ";
            std::cin >> value;
            matrix.insert(value, i, j);
        }
    }

    std::cout << "Sparse Matrix:\n";
    matrix.display();

    int search_row, search_col;
    std::cout << "Enter the row and column to retrieve a value: ";
    std::cin >> search_row >> search_col;
    int result = matrix.get(search_row, search_col);
    std::cout << "Value at (" << search_row << ", " << search_col << ") is " << result << std::endl;

    return 0;
}

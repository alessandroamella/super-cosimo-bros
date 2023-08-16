#ifndef _LIST2D_HPP_
#define _LIST2D_HPP_

#include "list.hpp"

template <typename T>
class List2D {
   private:
    List<List<T>> list;
    int rows;
    int cols;

   public:
    List2D(int rows, int cols);
    T at(int row, int col);
    void set(int row, int col, T data);
    size_t length();
    void print();
};

template <typename T>
List2D<T>::List2D(int rows, int cols) : rows(rows), cols(cols) {
    for (int i = 0; i < rows; i++) {
        List<T> row;
        for (int j = 0; j < cols; j++) {
            row.push(T());
        }
        list.push(row);
    }
}

template <typename T>
T List2D<T>::at(int row, int col) {
    return list.at(row).at(col);
}

template <typename T>
void List2D<T>::set(int row, int col, T data) {
    list.at(row).pop(col);
    list.at(row).push(data);
}

template <typename T>
size_t List2D<T>::length() {
    return (size_t)(rows * cols);
}

template <typename T>
void List2D<T>::print() {
    std::cout << "[";
    std::cout << std::endl;
    for (size_t i = 0; i < rows; i++) {
        std::cout << "    ";
        list.at(i).print();
        std::cout << std::endl;
    }
    std::cout << "]" << std::endl;
}

#endif  // _LIST2D_HPP_

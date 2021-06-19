// column-submit.h

#ifndef COLUMN_SUBMIT_H_
#define COLUMN_SUBMIT_H_

#include <string>
#include <iostream>

/// TODO: Add the definitions of inline global functions below

template <>
inline std::string Column<int>::as_string_at(int index) const {
    return std::to_string((*this)[index]); // negative index
}

template <>
inline std::string Column<bool>::as_string_at(int index) const {
    if ((*this)[index] == 1) return "true";
    else return "false";
}

template <>
inline std::string Column<std::string>::as_string_at(int index) const {
    return (*this)[index];
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Column<T>& column) {
    return column.operator<<(os);
}

/// TODO: Add the missing function definitions of the Column template below

template <typename T>
void Column<T>::reserve_capacity(int new_capacity) {
    if (new_capacity > capacity_){
        capacity_ = new_capacity;
        T* newdata_ = new T[capacity_];
        for (int i = 0; i < size_; i++){
            newdata_[i] = data_[i];
        }
        delete[] data_;
        data_ = newdata_;
    }
    return;
}

template <typename T>
void Column<T>::expand_size(int new_size) {
    if (new_size > size_ && new_size <= capacity_){
        for(int i = size_; i < new_size; i++){
            data_[i] = default_value_;
        }
        size_ = new_size;
    }
    else if (new_size > capacity_){
        reserve_capacity(new_size);
        for(int i = size_; i < new_size; i++){
            data_[i] = default_value_;
        }
        size_ = new_size;
    }
    return;
}

template <typename T>
void Column<T>::append(const Column<T>& other) {
    if (size_ + other.size_ <= capacity_){
        for (int i = size_; i < size_ + other.size_; i++){
            data_[i] = other[i - size_];
        }
    }
    else{
        reserve_capacity(size_ + other.size_);
        for (int i = size_; i < capacity_; i++){
            data_[i] = other[i - size_];
        }
    }
    size_ += other.size_;
    return;
}

template <typename T>
const Column<T>& Column<T>::operator=(const Column<T>& other) {
    default_value_ = other.default_value_;
    name_ = other.name_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    T* newdata_ = new T[capacity_];
    for (int i = 0; i < size_; i++){
        newdata_[i] = other.data_[i];
    }
    delete[] data_;
    data_ = newdata_;
    return *this;
}

template <typename T>
Column<T> Column<T>::operator+(const Column<T>& other) const {
    Column<T> newColumn(default_value_, size_, size_, "NULL");
    for (int i = 0; i < newColumn.size_; i++){
        newColumn.data_[i] = data_[i] + other.data_[i];
    }
    return newColumn;
}

template <typename T>
const Column<T>& Column<T>::operator+=(const Column<T>& other) {
    for (int i = 0; i < size_; i++){
        data_[i] += other.data_[i];
    }
    return *this;
}

template <typename T>
Column<bool> Column<T>::operator==(const Column<T>& other) const {
    Column<bool> newColumn(false, size_, size_, "NULL");
    for (int i = 0; i < size_; i++){
        if (data_[i] == other.data_[i]) newColumn[i] = true;
        else newColumn[i] = false;
    }
    return newColumn;
}

template <typename T>
Column<bool> Column<T>::operator<(const Column<T>& other) const {
    Column<bool> newColumn(false, size_, size_, "NULL");
    for (int i = 0; i < size_; i++){
        if (data_[i] < other.data_[i]) newColumn[i] = true;
        else newColumn[i] = false;
    }
    return newColumn;
}

template <typename T>
Column<bool> Column<T>::operator==(const T& other) const {
    Column<bool> newColumn(false, size_, size_, "NULL");
    for (int i = 0; i < size_; i++){
        if (data_[i] == other) newColumn[i] = true;
        else newColumn[i] = false;
    }
    return newColumn;
}

template <typename T>
Column<bool> Column<T>::operator<(const T& other) const {
    Column<bool> newColumn(false, size_, size_, "NULL");
    for (int i = 0; i < size_; i++){
        if (data_[i] < other) newColumn[i] = true;
        else newColumn[i] = false;
    }
    return newColumn;
}

template <typename T>
Column<bool> Column<T>::operator!() const {
    Column<bool> newColumn(false, size_, size_, "NULL");
    for (int i = 0; i < size_; i++){
        newColumn[i] = !(data_[i]);
    }
    return newColumn;
}

template <typename T>
Column<bool> Column<T>::operator&&(const Column<T>& other) const {
    Column<bool> newColumn(false, size_, size_, "NULL");
    for (int i = 0; i < size_; i++){
        if (data_[i] && other.data_[i]) newColumn[i] = true;
        else newColumn[i] = false;
    }
    return newColumn;
}


template <typename T>
T Column<T>::operator[](int index) const {
    if (index >= 0) return data_[index];
    else return data_[size_ + index]; // negative index
}

template <typename T>
T& Column<T>::operator[](int index) {
    if (index >= 0) return data_[index];
    else return data_[size_ + index]; // negative index
}

/*template <typename T>
Column<T>::Column(const Column<T>& other, const Column<bool>& selector) {  
}*/

template <typename T>
Column<T> Column<T>::operator[](const Column<bool>& selector) const {
    int newColumnsize = 0;
    for (int i = 0; i < selector.get_size(); i++){
        if (selector[i] == true) newColumnsize++;
    }
    Column<T> newColumn(default_value_, newColumnsize, newColumnsize, "NULL");
    for (int i = 0, j = 0; i < selector.get_size(); i++){
        if (selector[i] == true) newColumn.data_[j++] = data_[i];
    }
    return newColumn;
}

#endif  // COLUMN_SUBMIT_H_
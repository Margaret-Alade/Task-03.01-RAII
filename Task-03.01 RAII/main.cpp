//
//  main.cpp
//  Task-03.01 RAII
//
//  Created by Маргарет  on 22.01.2024.
//

#include <iostream>

class WrongIndex : public std::exception {
public:
const char* what() const noexcept override { return "Вы ввели несуществующий индекс";}
};
    


class SmartArray {
private:
    int*arr_ = NULL;
    int size_;
    int capacity_;
public:
    SmartArray() {
        capacity_ = 1;
        size_ = 0;
        arr_ = new int[capacity_];
    }
    
    SmartArray(int capacity) {
        this->capacity_ = capacity;
        arr_ = new int[capacity_];
        size_ = 0;
    }
    
    void growArray() {
        
        int* temp = new int[capacity_ * 2];
        capacity_ = capacity_ * 2;
        for (int i = 0; i < size_; i++) {
            temp[i] = arr_[i];
        }
        delete[] arr_;
        arr_ = temp;
    }
    
    void add_element(int value) {
        if (size_ == capacity_) {
            growArray();
        }
        arr_[size_] = value;
        size_++;
            
    }
    
    int get_element(int index) {
        if (index < capacity_) {
            return arr_[index];
        } else {
            throw WrongIndex();
        }
    }
    ~SmartArray() {
        delete[] arr_;
    }
        
    
};

int main(int argc, const char * argv[]) {
    try {
        SmartArray arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        arr.add_element(14);
        arr.add_element(15);
        std::cout << arr.get_element(7) << std::endl;
    }
    catch (const WrongIndex& e) {
        std::cout << e.what() << "\n";
    }
   
    return 0;
}

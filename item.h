//
// Created by myx on 2023/2/18.
//

#pragma once

#include <iostream>
#include <cmath>


template<typename DataType>
class Item {
    DataType data;
public:
    explicit Item(DataType d) : data(d) {
    };

    Item() {}

    Item(const Item &item) {
        this->data = item.data;
    }

    bool operator<(const Item &rhs) const {
        return data < rhs.data;
    }

    Item operator%(const Item<DataType> t) const {
        return Item(fmod(this->data, t.data));

    }

    Item operator+(const Item<DataType> item) const {
        return Item(this->data + item.data);
    }

    DataType operator-(const Item<DataType> &it) {
        return ::fabs(this->data - it.data);
    }

    DataType getData() const {
        return data;
    }

    friend std::ostream &operator<<(std::ostream &os, const Item &item) {
        os << "data: " << item.data;
        return os;
    }

};



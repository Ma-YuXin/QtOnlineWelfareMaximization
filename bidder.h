//
// Created by myx on 2023/2/18.
//
#pragma once

#include "submodularFunction.h"
#include <string>
#include "item.h"
#include "myException.h"
#include <iostream>
#include <set>


template<template<class> class Container, typename DataType, typename Result>
class Bidder {
public:
    typedef Container<Item<DataType>> ContainerType;
private:
    typedef SubmodularFunction<ContainerType, DataType, Result> Function;
    Function *f;
    ContainerType c;
    Result totalValue;
public:
    Bidder(Function *f1) :
            f(f1),
            totalValue(0) {
    }

    Bidder() : f(nullptr), totalValue(0) {
    }

    ContainerType getContainer() {
        return c;
    }

    int getSize() {
        return c.size();
    }

    Result getTotal() {
        return totalValue;
    }

    void update(const Item<DataType> &e);

    Result marginalValuation(const Item<DataType> &it);

    Function getF() {
        return f;
    }

    FuncType getFuncType() const {
        return f->getType();
    }

    void setF(Function *f) {
        this->f = f;
    }
};

template<template<class> class Container, typename DataType, typename Result>
void Bidder<Container, DataType, Result>::update(const Item<DataType> &e) {
    c.push_back(e);
    totalValue = f->calculate(c);
}

template<template<class> class Container, typename DataType, typename Result>
Result Bidder<Container, DataType, Result>::marginalValuation(const Item<DataType> &it) {
    Result val;
    if (f == nullptr)throw FunctionPointerIsNull();
    c.push_back(it);
    try {
        val = f->calculate(c);
    } catch (SizeOutOfRangeException &e) {
        std::cout << e.what() << std::endl;
    }
    c.pop_back();
    return val - totalValue;
}


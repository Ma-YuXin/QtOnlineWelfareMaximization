//
// Created by myx on 2023/2/18.
//

#pragma once

#include "submodularFunction.h"

template<class Container, class DataType, class Result>
class SubmodularFunctionFactory {
private:
    typedef SubmodularFunction<Container, DataType, Result> FunctionType;
    typedef SubmodularFunctionFactory<Container, DataType, Result> FunctionFactoryType;

    SubmodularFunctionFactory() = default;

public:
    SubmodularFunctionFactory(const SubmodularFunctionFactory &submodularFunction) = delete;

    FunctionType *getSubmodularFunction(int key) const {
        switch (key) {
            case 0:
                return LinearFunction<Container, DataType, Result>::getInstance();
            case 1:
                return CoverFunction<Container, DataType, Result>::getInstance();
            default:
                return nullptr;
        }
    }

    int getTotalFunctionNum() {
        return 2;
    }

    static FunctionFactoryType *getInstance() {
        static FunctionFactoryType instance;
        return &instance;
    };
};

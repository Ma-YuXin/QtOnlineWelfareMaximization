//
// Created by myx on 2023/2/18.
//

#pragma once

#include <string>
#include <numeric>
#include "myException.h"
#include <algorithm>
#include "item.h"
#include "funcType.h"

template<class Container, class DataType, class Result>
class SubmodularFunction {

public:
    SubmodularFunction() = default;

    SubmodularFunction(SubmodularFunction &function) = default;

    virtual FuncType getType() const = 0;

    virtual Result calculate(const Container &c) const = 0;

    [[maybe_unused]]   virtual std::string getDescription() const = 0;

    virtual ~SubmodularFunction() = default;
};

template<class Container, class DataType, class Result>
class CoverFunction : public SubmodularFunction<Container, DataType, Result> {
    static double coverFactor;
    static double totalLength;


    CoverFunction(double coverFactor = 20, double tLength = 100) {
        this->coverFactor = coverFactor, this->totalLength = tLength;
    }

public:
    CoverFunction(const CoverFunction<Container, DataType, Result> &) = delete;

    static FuncType getFuncType() {
        return FuncType::CoFunction;
    }

    FuncType getType() const override {
        return FuncType::CoFunction;
    }

    Result calculate(const Container &c) const override {
        Container tmp(c.size());
        std::transform(c.begin(), c.end(), tmp.begin(),
                       bind(std::modulus<Item<DataType>>(), std::placeholders::_1, Item<DataType>(totalLength)));
        std::sort(tmp.begin(), tmp.end(), std::less<Item<DataType>>());
        if (c.size() == 0)return 0;
        Result sum = 0;
        if (c.front().getData() - coverFactor / 2 < 0) {
            sum += c.front().getData();
        } else {
            sum += coverFactor / 2;
        }
        if (c.back().getData() + coverFactor / 2 > totalLength) {
            sum += (totalLength - c.back().getData());
        } else {
            sum += coverFactor / 2;
        }
        for (int i = 0; i < tmp.size() - 1; ++i) {
            Result dif = fabs(tmp[i].getData() - tmp[i + 1].getData());
            if (dif > coverFactor)sum += (coverFactor);
            else sum += dif;
        }
        return sum;
    }

    static SubmodularFunction<Container, DataType, Result> *getInstance() {
        static CoverFunction<Container, DataType, Result> cf;
        return &cf;
    }

    static std::pair<double, double> getValue() {
        return std::make_pair(coverFactor, totalLength);
    }

    std::string getDescription() const override {
        return "每个元素可以在坐标轴上覆盖以它为中心的" + std::to_string(coverFactor) +
               "单位，函数返回集合覆盖的总范围";
    }

};

template<class Container, class DataType, class Result>
double CoverFunction<Container, DataType, Result>::coverFactor = 20;
template<class Container, class DataType, class Result>
double CoverFunction<Container, DataType, Result>::totalLength = 100;

template<class Container, class DataType, class Result>
class LinearFunction : public SubmodularFunction<Container, DataType, Result> {
    static double k, b;

    explicit LinearFunction(double k = -2, double b = 20) {
        this->k = k;
        this->b = b;
    }

public:
    LinearFunction(const LinearFunction<Container, DataType, Result> &) = delete;

    FuncType getType() const override {
        return FuncType::LiFunction;
    }

    static FuncType getFuncType() {
        return FuncType::LiFunction;
    }

    Result calculate(const Container &c) const {
        if (k * c.size() + b < 0)throw SizeOutOfRangeException();
        Result sum = 0;
        for (int i = 0; i < c.size(); ++i) {
            sum += (k * i + b);
        }
        return sum;
    }

    static SubmodularFunction<Container, DataType, Result> *getInstance() {
        static LinearFunction<Container, DataType, Result> lf;
        return &lf;
    }

    static std::pair<double, double> getValue() {
        return std::make_pair(k, b);
    }

    std::string getDescription() const override {
        return "一次函数：k=" + std::to_string(k) + ",b=" + std::to_string(b) + "。";
    }

};

template<class Container, class DataType, class Result>
double LinearFunction<Container, DataType, Result>::k = -2;
template<class Container, class DataType, class Result>
double LinearFunction<Container, DataType, Result>::b = 20;

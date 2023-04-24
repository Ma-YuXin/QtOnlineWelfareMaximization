//
// Created by myx on 2023/2/18.
//

#pragma once

#include <exception>

class SizeOutOfRangeException : public std::exception {
public:
    const char *what() const

    _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
    override {
        return "集合大小超过了函数所能适用的范围";
    }

    SizeOutOfRangeException() = default;
};

class ItemValueToLarge : public std::exception {
public:
    const char *what() const

    _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
    override {
        return "元素的值过大，超过了覆盖函数的适用范围";
    }

    ItemValueToLarge() = default;

};

class FunctionPointerIsNull : public std::exception {
public:
    const char *what() const

    _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
    override {
        return "代理人的次模函数指针为空";
    }

    FunctionPointerIsNull() = default;
};

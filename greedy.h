//
// Created by myx on 2023/2/18.
//
#pragma once

#include "bidder.h"
#include "item.h"
#include <set>
#include <vector>
#include <algorithm>
#include "submodularFunctionFactory.h"
#include <iterator>

template<typename DataType, typename Result>
class Greedy {
public:
    template<class T>
    using SetInBidder = std::vector <T, std::allocator<T>>;
private:
    typedef Bidder<SetInBidder, DataType, Result> TypeOfBidder;
    typedef std::vector <TypeOfBidder> BiddersCollection;
    typedef Item<DataType> ItemType;
    int m, n;
    BiddersCollection *bidders;
    std::vector <Result> *marginValue;

public:

    Greedy(int n1) : m(0), n(n1) {
        bidders = new BiddersCollection(n);
        marginValue = new std::vector<Result>(n);
    }

    std::vector <Item<DataType>> getAllocation(int i) {
        return (*bidders)[i].getContainer();
    }

    void initialization(std::vector<int> &functions);

    int fit(const ItemType &element);

    int getSize(int i) {
        return (*bidders)[i].getSize();
    }

    FuncType getFuncType(int i) const {
        return (*bidders)[i].getFuncType();
    }

    int getN() const {
        return n;
    }

    int getM() const {
        return m;
    }

    Result getTotal(int i) {
        return (*bidders)[i].getTotal();
    }

    Result getMargin(int i) const {
        return (*marginValue)[i];
    }

    ~Greedy() {
        delete marginValue;
        delete bidders;
    }
};

template<typename DataType, typename Result>
void Greedy<DataType, Result>::initialization(std::vector<int> &functions) {
    int i = 0;
    SubmodularFunctionFactory<SetInBidder<ItemType>, DataType, Result> *factory = SubmodularFunctionFactory<SetInBidder<ItemType>, DataType, Result>::getInstance();
    for (const auto &item: functions) {
        (*bidders)[i++].setF(factory->getSubmodularFunction(item));
    }
}

template<typename DataType, typename Result>
int Greedy<DataType, Result>::fit(const ItemType &element) {
    m++;
    std::transform(bidders->begin(), bidders->end(), marginValue->begin(), [&element](TypeOfBidder &bidder) -> Result {
        return bidder.marginalValuation(element);
    });
    auto pos = std::max_element(marginValue->begin(), marginValue->end(), std::less<Result>());
    (*bidders)[pos - marginValue->begin()].update(element);
    return pos - marginValue->begin();
}

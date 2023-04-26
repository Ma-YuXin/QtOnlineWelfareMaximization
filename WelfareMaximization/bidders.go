package main

import (
	"sort"
	"welfareMaximization/function"
)

type Bidder struct {
	totalValue float64
	allocate   sort.Float64Slice
	funcType   int
}

func (b *Bidder) init(f int) {
	b.allocate = make(sort.Float64Slice, 0, 10)
	b.funcType = f
}
func (b *Bidder) Update(v float64) {
	if b.allocate == nil {
		b.allocate = make(sort.Float64Slice, 0, 10)
	}
	b.allocate = append(b.allocate, v)
	b.totalValue = b.Calculate()

}
func (b *Bidder) Calculate() float64 {
	if b.allocate == nil {
		return -1
	}
	switch b.funcType {
	case 1:
		return function.CoverCalculate(&b.allocate)
	case 2:
		return function.LinearCalculate(&b.allocate)
	}
	return -1
}
func (b *Bidder) Margin(v float64) float64 {
	if b.allocate == nil {
		return -1
	}
	b.allocate = append(b.allocate, v)
	var mar float64
	tmp := b.allocate[:len(b.allocate)-1]
	switch b.funcType {
	case 1:
		mar = function.CoverCalculate(&b.allocate) - function.CoverCalculate(&tmp)
	case 2:
		mar = function.LinearCalculate(&b.allocate) - function.LinearCalculate(&tmp)
	}
	b.allocate = tmp
	return mar
}

package main

import (
	"fmt"
	"sort"
)

type Greedy struct {
	total     float64
	bidderNum int64
	itemNum   int64
	bidders   []Bidder
}
func (g*Greedy)init(f sort.IntSlice){
	for i:=0;i<len(g.bidders);i++{
		g.bidders[i].init(f[i])
	}
}
func (g *Greedy) getBidder(pos int) *Bidder {
	return &(g.bidders[pos])
}
func (g *Greedy) fit(v float64) int64 {
	// fmt.Println("flalajl")
	if len(g.bidders) == 0 {
		return -1
	}
	margin := make(sort.Float64Slice, len(g.bidders))
	for i := 0; i < len(g.bidders); i++ {
		margin[i] = g.bidders[i].Margin(v)
	}
	tmp := margin[0]
	pos := 0
	for i := 1; i < len(margin); i++ {
		if margin[i] > tmp {
			tmp = margin[i]
			pos = i
		}
	}
	g.bidders[pos].Update(v)
	g.total+=margin[pos]
	fmt.Println(margin)
	return int64(pos)
}
func (g *Greedy) getTotal()float64{
	return g.total
}
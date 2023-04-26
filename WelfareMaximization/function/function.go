package function

import (
	"math"
	"sort"
)
type Func struct{
	typeId int
}
type CoverFunc struct{
	Func
}
type LinearFunc struct{
	Func
}
var (
	coverFactor float64 = 20
	totalLenth  float64 = 100
	k           float64 = -4
	b           float64 = 20
)

func CoverCalculate(c *sort.Float64Slice) (sum float64) {
	cantain := make(sort.Float64Slice, 0, len(*c))
	for i := 0; i < len(*c); i++ {
		cantain = append(cantain, math.Mod((*c)[i], totalLenth))
	}
	sort.Sort(cantain)
	if len(cantain) > 0 {
		if cantain[0] > coverFactor/2 {
			sum += coverFactor / 2
		} else {
			sum += cantain[0]
		}
		if totalLenth-cantain[len(cantain)-1] > coverFactor/2 {
			sum += coverFactor / 2
		} else {
			sum += cantain[0]
		}
	}
	for i := 1; i < len(cantain); i++ {
		if cantain[i]-cantain[i-1] > coverFactor {
			sum += coverFactor
		} else {
			sum += cantain[i] - cantain[i-1]
		}
	}
	return
}
func LinearCalculate(c *sort.Float64Slice) (sum float64) {
	for i := 0; i < len(*c); i++ {
		sum += float64(i)*k + b
	}
	return
}

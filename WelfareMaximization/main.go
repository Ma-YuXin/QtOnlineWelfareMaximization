package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"sort"
	"strconv"
	"strings"
)

var ans sort.Float64Slice

func main() {
	num, value, funct := getData()
	greed := Greedy{
		0,
		num,
		int64(len(value)),
		make([]Bidder, num),
	}
	fmt.Println(funct)
	greed.init(funct)
	// for _, v := range value {
	// 	// fmt.Println("flalajl")
	// 	greed.fit(v)
	// }
	ans = make(sort.Float64Slice, 0)
	recur(0, value, &greed)
	var maximum float64
	for _, v := range ans {
		if v > maximum {
			maximum = v
		}
	}
	fmt.Println(maximum)
	fmt.Println(len(ans))
}
func recur(pos int, value sort.Float64Slice, gre *Greedy) {
	if pos == len(value) {
		ans = append(ans, gre.getTotal())
		// fmt.Println(pos, len(value), ans)
		return
	}

	for i := 0; i < int(gre.bidderNum); i++ {
		gre.Alloc(i, value[pos])
		recur(pos+1, value, gre)
		gre.PopBack(i)
	}
}
func getData() (int64, sort.Float64Slice, sort.IntSlice) {
	defer func() {
		err := recover()
		if err != nil {
			fmt.Println(err)
		}
	}()
	var content []byte
	var val string
	var bidderNum int64
	var tmp float64
	var t1 int64
	file, err := os.Open("./input.txt")
	if err != nil {
		panic("文件打开失败")
	}
	defer file.Close()
	re := bufio.NewReader(file)
	content, _, err = re.ReadLine()
	if err != nil {
		panic("文件为空")
	}
	t := strings.Trim(string(content), " ")
	bidderNum, err = strconv.ParseInt(t, 10, 64)
	if err != nil {
		panic("转换买家数量失败")
	}
	content, _, err = re.ReadLine()
	if err != nil {
		panic("买家函数设置为空")
	}
	t = strings.Trim(string(content), " ")
	value := strings.Split(t, " ")
	funct := make(sort.IntSlice, 0, bidderNum)
	for i := 0; i < len(value); i++ {
		t1, err = strconv.ParseInt(value[i], 10, 64)
		if err != nil {
			continue
		}
		funct = append(funct, int(t1))
	}
	if err != nil {
		panic("转换买家数量失败")
	}
	for {
		content, _, err = re.ReadLine()
		if err == io.EOF {
			break
		}
		val += " "
		val += string(content)
	}
	value = strings.Split(val, " ")
	ans := make(sort.Float64Slice, 0, len(value))
	for i := 0; i < len(value); i++ {
		tmp, err = strconv.ParseFloat(value[i], 64)
		if err != nil {
			continue
		}
		ans = append(ans, tmp)
	}
	return bidderNum, ans, funct
}

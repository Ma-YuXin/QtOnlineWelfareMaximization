package vector

import (
	"errors"
)

type vector struct {
	data     []interface{}
	capacity int
	size     int
}
func GetVector(capacity int) *vector{
	vec:=&vector{}
	vec.data=make([]interface{},capacity)
	vec.capacity=capacity
	return vec
}
func (v *vector) Size() int {
	return v.size
}
func (v *vector) Capacity() int {
	return v.capacity
}
func (v *vector) IsEmpty() bool {
	return v.size == 0
}
func (v *vector) Push_back(value interface{}) error {
	if v.size == v.capacity {
		v.capacity *= 2
		v.data = make([]interface{}, v.capacity)
	}
	v.data[v.size] = value
	v.size++
	return nil
}
func (v *vector) Pop_back() error {
	if v.Size() > 0 {
		v.size--
		return nil
	} else {
		return errors.New("数组为空，不能继续删除元素")
	}
}
func (v *vector) Back() (interface{}, error) {
	if v.size == 0 {
		return 0, errors.New("数组大小为空")
	}
	return v.data[v.size-1], nil
}
func (v *vector) Front() (interface{}, error) {
	if v.size == 0 {
		return 0, errors.New("数组大小为空")
	}
	return v.data[0], nil
}

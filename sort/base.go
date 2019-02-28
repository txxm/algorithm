package main

import (
	"fmt"
)

/* 适用于区间范围较小的数组排序 */
func base(array []int, l, r int) {
	if array == nil {
		return
	}

	var temp [10]int
	for i := 0; i <= r; i++ {
		temp[array[i]] = array[i]
	}

	fmt.Println(temp)
}

func main() {
	array := []int {3, 5, 1, 6, 9 ,0, 4, 7, 2, 8}
	base(array, 0, len(array)-1)
}

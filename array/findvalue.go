package main

import (
	"fmt"
)

func main() {
	var a = []int{1,4,9,1,4,5,1,1,1,7,1,1,6}
	fmt.Println(FindValue(a, len(a)))
}


/*
 *在一个数组中，有一个数的个数超过数组长度的1/2，找出这个数
 *互相抵消法:两个数不同时互相抵消，相同时个数加1
 */
func FindValue(a []int, length int) int {
	target := a[0]
	number := 1

	for i := 1; i < length; i++ {
		if a[i] != target {
			if number == 0 {
				target = a[i]
				number = 1
			}
		} else {
			number++
		}
	}

	return target
}

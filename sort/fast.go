package main

import (
	"fmt"
)

func position(array []int, l int, r int) int {
	if array == nil {
		return -1
	}

	i := l-1
	val := array[r]
	for j := l; j <= r-1; j++ {
		if array[j] <= val {
			i = i+1
			array[i], array[j] = array[j], array[i]
		}
	}

	array[i+1], array[r] = array[r], array[i+1]
	return i+1
}

func quicksort(array []int, l int, r int) {
	var pos int
	if array == nil {
		return
	}

	if l < r {
		pos = position(array, l, r)
		quicksort(array, l, pos-1)
		quicksort(array, pos+1, r)
	}
}

func main() {
	var array = []int{4, 6, 2, 8, 0, 3, 5, 7, 1, 9}

	quicksort(array, 0, len(array)-1)
	fmt.Println(array)
}

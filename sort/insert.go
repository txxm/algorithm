package main

import (
	"fmt"
)

func InsertSort(array []int, l int, r int) {
	if array == nil {
		return
	}

	for i := 1; i < r; i++ {
		for j := 0; j < i; j++ {
			if array[i] < array[j] {
				array[i], array[j] = array[j], array[i]
			}
		}
	}
	fmt.Println(array)
}

func main() {
	array := []int {3, 6, 1, 5, 0, 7, 4, 2, 8, 9}

	InsertSort(array, 0, len(array)-1)
}

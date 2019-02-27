package main

import (
	"fmt"
)

func bubble(array []int, l int, r int) {
	if array == nil {
		return
	}

	for i := 0; i < r-1; i++ {
		for j := 0; j < r-i; j++ {
			if array[j] > array[j+1] {
				array[j], array[j+1] = array[j+1], array[j]
			}
		}
	}

	fmt.Println(array)
}

func main() {
	array := []int {3, 5, 1, 7, 0, 6, 4, 9, 8, 2}

	bubble(array, 0, len(array)-1)
}

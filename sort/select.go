package main

import (
	"fmt"
)

func selecting(array []int, l int, r int) {
	if array == nil {
		return
	}

	for i := 0; i < r; i++ {
		for j := i+1; j <= r; j++ {
			if array[i] > array[j] {
				array[i], array[j] = array[j], array[i]
			}
		}
	}

	fmt.Println(array)
}

func main() {
	array := []int {3, 5, 1, 7, 0, 6, 4, 9, 8, 2}

	selecting(array, 0, 9)
}

package main

import (
	"fmt"
)

func main() {
	array := []int{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}

	low := 0
	high := len(array)-1
	for ; low <= high; {
		mid := low + (high-low)/2
		if array[mid] < 6 {
			low = mid+1
		} else if array[mid] > 6 {
			high = mid-1
		} else {
			fmt.Println("6")
			return
		}
	}
}

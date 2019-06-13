package main

import (
	"fmt"
	"math/rand"
)

func partition(array []int, left int, right int) int {
	if array == nil {
		return -1
	}

	i := left-1
	val := array[right]
	for j := left; j <= right-1; j++ {
		if array[j] <= val {
			i = i+1
			array[i], array[j] = array[j], array[i]
		}
	}

	array[i+1], array[right] = array[right], array[i+1]
	return i+1
}

func random_partition(array []int, left int, right int) int {
	var i, temp int

	i = rand.Intn(100)%(right-left+1)+left
	temp = array[right]
	array[right] = array[i]
	array[i] = temp

	temp = partition(array, left, right)
	return temp
}

func quicksort(array []int, left int, right int) {
	var pos int
	if array == nil {
		return
	}

	if left < right {
		pos = random_partition(array, left, right)
		quicksort(array, left, pos-1)
		quicksort(array, pos+1, right)
	}
}

func main() {
	var array = []int{4, 6, 2, 8, 0, 3, 5, 7, 1, 9}

	quicksort(array, 0, len(array)-1)
	fmt.Println(array)
}

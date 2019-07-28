package main

import (
	"fmt"
)

func MaxHeapify(a []int, i int, heapsize int) {
	var largest int
	left := 2*i
	right := 2*i+1

	if left < heapsize && a[left] > a[i] {
		largest = left
	} else {
		largest = i
	}

	if right < heapsize && a[right] > a[largest] {
		largest = right
	}

	if right >= heapsize-1 {
		return
	}
	if largest != i {
		a[largest], a[i] = a[i], a[largest]
		MaxHeapify(a, largest, heapsize)
	}
}

func BuildHeap(a []int, left, right int) {
	for i := len(a)/2; i > 0; i-- {
		MaxHeapify(a, i, len(a))
	}
}

func SortHeap(a []int, left, right int) {
	heapsize := len(a)
	fmt.Println(a[0])
	for i := len(a)-1; i > 0; i-- {
		a[0], a[i] = a[i], a[0]
		MaxHeapify(a, 0, heapsize)
		heapsize--
		fmt.Println(a[0])
	}
}

func main() {
	var a = []int{16,14,10,8,7,9,3,2,4,1}

	BuildHeap(a, 0, 9)
	SortHeap(a, 0, 9)
}

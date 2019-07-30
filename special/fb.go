package main

import (
	"fmt"
)

func main() {
	n := 7
	value := 13
	fmt.Println(FibonacciFindValue_1(n))
	fmt.Println(FibonacciFindN(value))
}

/*
 * 找出第n个斐波那契数？
 */
func FibonacciFindValue_1(n int) int {
	f1 := 1
	f2 := 1
	for i := 0; i < (n-2)/2; i++ {
		f1 = f1 + f2
		f2 = f2 + f1
	}
	if n%2 == 0 {
		return f2
	} else {
		return (f1+f2)
	}
}


/*
 * 给定一个斐波那契数，求是第几个？
 */
func FibonacciFindN(value int) int {
	f1 := 1
	f2 := 1

	i := 2
	for {
		if value == f1 {
			return i-1
		} else if value == f2 {
			return i
		}
		f1 = f1 + f2
		f2 = f2 + f1
		i += 2
	}
}

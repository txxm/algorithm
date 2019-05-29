package main

import (
	"fmt"
)

func isPalindrome(x int) bool {
	if x < 0 || (x%10==0 && x != 0) {
		return false
	}

	var temp int
	for x > temp {
		temp = temp * 10 + x % 10
		x /= 10
	}

	return x == 0 || x == temp/10
}

func main() {
	var x int
	fmt.Scanf("%d", &x)
	if ok := isPalindrome(x); ok {
		fmt.Println("x是回文数.")
	} else {
		fmt.Println("x不是回文数.")
	}
}

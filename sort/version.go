package main

import (
	"errors"
	"strings"
)

func compare(v1, v2 string) (res string) {
	str1 := strings.Split(v1, ".")
	str2 := strings.Split(v2, ".")

	if len(str1) == 0 && len(str2) == 0 {
		return errors.New("invalid version").Error()
	}

	var n int
	if len(str1) <= len(str2) {
		n = len(str1)
	} else if len(str1) > len(str2) {
		n = len(str2)
	}

	for k := 0; k < n; k++ {
		if len(str1[k]) < len(str2[k]) {
			return v1+" < "+v2
		} else if len(str1[k]) > len(str2[k]) {
			return v1+" > "+v2
		} else {
			for i := 0; i < len(str1[k]); i++ {
				if str1[k][i] > str2[k][i] {
					return v1+" > "+v2
				} else if str1[k][i] < str2[k][i] {
					return v1+" < "+v2
				} else {
					continue
				}
			}
		}
	}
	if len(str1) < len(str2) {
		res = v1+" < "+v2
	} else if len(str1) > len(str2) {
		res = v1+" > "+v2
	} else {
		res = v1+" = "+v2
	}
	return res
}

func main() {
	println(compare("0.0.11", "0.0.11"))

	println(compare("1.0", "0.1"))
	println(compare("0.1", "0.0.1"))
	println(compare("1.1", "1.1.3"))
	println(compare("0.11.0", "0.12.0"))

	println(compare("1.3.4a", "0.2.4b"))
	println(compare("0.3.4a", "1.2.4b"))

	println(compare("1.3.4a", "1.2.4b"))
	println(compare("1.2.4b", "1.3.4a"))

	println(compare("1.2.3b", "1.2.4b"))
	println(compare("1.2.3a", "1.2.2d"))

	println(compare("1.2.3b", "1.12.4b"))
	println(compare("1.12.3", "1.12.4b"))

	println(compare("1.10.3", "1.2.3b"))

	println(compare("v2.10.3", "v1.2.3b"))
	println(compare("v.10.3", "v1.2.3b"))
}

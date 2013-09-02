package main

import "fmt"

func main() {
	m := map[string]int{
		"a": 0,
		"b": 1,
		"c": 2, //note that there is a comma
	}

	v := m["a"]
	fmt.Println(v)

	//distinguish a missing entry from zero value
	v1, ok1 := m["d"]
	fmt.Println(v1, ok1)

	m["d"] = 3
	//use blak indentifier test for presence in a map
	_, ok2 := m["d"]
	fmt.Println(ok2)

	//delete a entry
	delete(m, "d")
	fmt.Println(m)
}

package main

import (
	"fmt"
	"math/cmplx"
)
// bool
// string
// int int8 int16 int32 int64
// uint uint8 uint16 uint32 uint64 uintptr
// byte
// rune
// float32 float64
// complex64 complex128

var (
	ToBe bool = false
	MaxInt uint64 = 1 << 64 -1
	z complex128 = cmplx.Sqrt(-5 + 12i)
)

func main() {
	const f = "%T(%v)\n"
	fmt.Printf(f, f, f)
	fmt.Printf(f, ToBe, ToBe)
	fmt.Printf(f, MaxInt, MaxInt)
	fmt.Printf(f, z, z)
}

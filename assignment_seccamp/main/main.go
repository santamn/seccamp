package main

import "fmt"

func main() {
	// t := 0x4142434445464748
	// fmt.Printf("%c\n", byte(t))

	// seccamp2021 := []byte("SECCAMP2021")
	// resource := []byte{0x9d, 0xcb, 0x1e, 0xa7, 0x65, 0xed, 0x5f, 0x4d, 0x01, 0xd6, 0x49, 0x4a, 0x55, 0xbd, 0xd7, 0x83, 0x52, 0x07, 0x30, 0x40}

	// fmt.Print("元のリソースデータ:")
	// dump(resource)
	// fmt.Println()

	// decode(resource, seccamp2021, 0x89192712)

	fmt.Printf("%d\n", int8(0xc0^0x73+0x73+0xee))
}

func decode(resource []byte, key []byte, data int64) {
	temp := data

	for i, v := range resource {
		fmt.Printf("%d文字目\n", i)

		if v > 0xa1 {
			resource[i]--
		}

		value := temp*5 + 0x2365f703
		// debug
		dump(resource)

		resource[i] ^= byte(value)

		// debug
		dump(resource)

		// debug
		fmt.Println("前")
		fmt.Println("temp:", int8(temp))
		temp = (value >> 2) - 0x1ca9
		fmt.Println("後")
		fmt.Println("temp:", int8(temp))

		keyByte := int8(key[i%len(key)])
		resource[i] = byte(int8(resource[i]) ^ keyByte + keyByte + int8(temp))

		// debug
		dump(resource)
		fmt.Println()
	}

	fmt.Printf("decoded text: %s\n", resource)
	dump(resource)
}

func dump(t []byte) {
	fmt.Printf("[")
	for i, v := range t {
		x := int8(v)
		fmt.Printf("%d", x)
		if i != len(t)-1 {
			fmt.Printf(", ")
		}
	}
	fmt.Printf("]\n")
}

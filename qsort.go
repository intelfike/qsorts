package main

import (
	"fmt"
	"math/rand"
	"time"
)

//int型スライスに対してソート
func Qsort(data []int) {
	L, R := qset(data[:])
	if len(L) > 1 {
		Qsort(L)
	}
	if len(R) > 1 {
		Qsort(R)
	}
}

//基準(最初と最後の要素の平均)をもとにスライス左右に振り分ける、クイックソートの最小単位の処理
func qset(data []int) ([]int, []int) {
	start, end := 0, len(data)-1
	center := (data[start]+data[end])>>1 + 1

	for {
		for data[start] < center {
			start++
		}
		for data[end] > center {
			end--
		}
		if start >= end {
			break
		}
		data[start], data[end] = data[end], data[start]
		if data[start] == center {
			start++
		}
		if data[end] == center {
			end--
		}
	}
	return data[:start], data[start:]
}

func main() {
	data := arr3(200000)
	fmt.Println(data[:10])

	//fmt.Println(data[:10], data[len(data)-10:])

	s := time.Now()
	Qsort(data) //ソートの実行
	e := time.Now()

	for n, v := range data {
		if n != 0 && data[n-1] > v {
			fmt.Println("Error!! n =", n, data[n:n+2])
			break
		}
	}

	fmt.Println(e.Sub(s)) //時間の表示
	fmt.Println(data[:10])
}

// ランダムなスライスを生成(一意)
func arr1(size int) []int {
	rand.Seed(2)
	return rand.Perm(size) //ランダムスライス生成
}

// 整列済みスライスを生成
func arr2(size int) []int {
	data := make([]int, size)
	for n, _ := range data {
		data[n] = n
	}
	return data[:]
}

// 逆V字型のスライスを生成
func arr3(size int) []int {
	data := make([]int, size)
	for n, _ := range data {
		data[n] = n
		if n > len(data)/2 {
			data[n] = len(data) - n
		}
	}
	return data[:]
}

import Glibc
var data:[Int] = []
let length = 200000
for n in 0...length{
	data.append(random()%length)	
}
print(data[0...10])

func gettime() -> Double{
	var tv:timeval = timeval(tv_sec: 0, tv_usec: 0)
	gettimeofday(&tv, nil)
	return Double(tv.tv_sec) + Double(tv.tv_usec) * 1e-6
}

func qsort(data: [Int]) -> ([Int]){
	let result = qset(data:data)
	var L = result.0, R = result.1
	if L.count > 1{
		L = qsort(data:L)
	}
	if R.count > 1{
		R = qsort(data:R)
	}
	return L + R
}

func qset(data: [Int]) -> ([Int], [Int]){
	var data = data
	var start = 0, end = data.count - 1
	let center = (data[start] + data[end]) >> 1
outer:
	while true {
		while data[start] <= center{
			if start >= end {
				break outer
			}
			start += 1
		}
		while data[end] > center{
			if start >= end{
				break outer
			}
			end -= 1
		}
		if data[start] != data[end] {
			let work = data[start]
			data[start] = data[end]
			data[end] = work
		}
	}
	//print(data)
	let ss = Array<Int>(data[0...start-1])
	let es = Array<Int>(data[end...data.count-1])
	return (ss, es)
}

let s = gettime()
// start
data = qsort(data:data)
// end
print((gettime() - s) * 1000, "ms")
print(data[0...10])
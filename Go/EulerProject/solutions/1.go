package solutions 

type P1 struct {}

func (p P1) Run() int {
    var sum int
    for i := 0; i < 1000; i++ {
        if i%3 == 0 || i%5 == 0 {
            sum += i
        }
    }
    return sum
}

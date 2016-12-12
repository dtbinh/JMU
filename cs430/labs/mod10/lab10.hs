--Author: Conner Turnbull
--Date: 2 March 2016

sumOfFirstN::Integer -> Integer
sumOfFirstN n = n * (n+1) `div` 2

--points::Int -> Int
--points 1 = 10
--points 2 = 8
--points 3 = 6
--points 4 = 5
--points 5 = 4
--points 6 = 3
--points 7 = 2
--points 8 = 1
--points _ = 0

points n
 | (9<n) || (n<1) = 0
 | (n<=3) = 12 - 2*n
 | otherwise = 9-n

myHead::[a]->a
myHead (x:xs) = x

factorial::Integer -> Integer
factorial 0 = 1
factorial n = n * factorial (n-1)

myLength::[a]->Int
myLength a = length a

myConcat::[a]->[a]->[a]
myConcat a b = a ++ b

fib::Integer -> Integer
fib 0 = 1
fib 1 = 1
fib n = fib(n-1) + fib(n-2)

ffib n = fibAccum 1 1 n
fibAccum e0 e1 k
 | (k==0) = e0
 | (k==1) = e1
 | otherwise = fibAccum e1 (e0+e1)(k-1)

indexOf Eq a => a -> [a] -> Int
indexOf a b = indexHelper a b 0
indexHelper a1 b1 k
 | (k==(length b1) = -1
 | (b!!k == a) = k
 | otherwise = indexHelper a1 b1 (k+1)

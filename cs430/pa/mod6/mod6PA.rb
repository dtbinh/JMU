# Author: Conner Turnbull

# factors(n)—must return an Array of all the factors of n, in order and without
# duplicates. The result must be [] if n < 1. For examples, factors(1) == [1]
# and factors(12) == [1, 2, 3, 4, 6, 12].
def factors(n)
  result = []

  if n < 1
    return result 
  end

  (1..n).each do |i|
    if n % i == 0
      result.push(i)
    end
  end

  return result
end

# primes(n)—must return an Array of all prime numbers less than or equal to n,
# in order and without duplicates. primes must return [] if n < 2. For examples,
# primes(10) == [2, 3, 5, 7].
def primes(n)
  result = []

  if n < 2
    return result
  end

  (2..n).each do |i|
    result.push(i) if is_prime(i)
  end

  return result
end

# countChars(str)-must return a Hash whose keys are characters (that is,
# strings consisting of a single character), and whose values are the number of
# occurrences of the characters in str. For example,
# countChars(hello) == {"h"=>1, "e"=>1, "l"=>2, "o"=>1}
def countChars(str)
  result = Hash.new

  str.split("").each do |ch|
    if result[ch] == nil
      result[ch] = 1
    else
      result[ch] += 1
    end
  end

  return result
end

# toCountsArray(counts)—given a Hash counting characters (like the one produced
# by countChar()), this method must return an Array of two-element Arrays where
# each inner arrays hold a character and its count. The result must be sorted by
# key values with no duplicates. For example,
# toCountsArray(countChars(“hello”)) ==
# [ [“e”, 1], [“h”, 1], [“l”, 2], [“o”, 1] ].
def toCountsArray(counts)
  result = []
  counts.keys.sort.each do |ch|
    result.push(Array[ch, counts[ch]])
  end

  return result
end

# encode(str, encoding)—must return a string in which each character of str is
# replaced with a string indicated in the Hash encoding, whose keys are
# characters and whose values are strings. You may assume that characters
# missing from encoding are mapped to the empty string and so must not be
# represented in the result. For examples, if
# encoding == { “0” => “zero ”, “1” => “one ”, … “9” => “nine ” },
# then encode(“4#2”, encoding) == “four two ”.
def encode(str, encoding)
  result = str
  str.split("").each do |ch|
    result[ch] = encoding[ch]
  end
  return result
end

# is_prime(num)-determines if a number is a prime number. Returns true if prime
# and false otherwise
def is_prime(num)
  return false if num <= 1
  Math.sqrt(num).to_i.downto(2).each {|i| return false if num % i == 0}
  return true
end

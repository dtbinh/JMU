listOf4 :: a -> a -> a-> a-> [a]
listOf4 a b c d = a:b:c:d:[]

double :: Integer -> Integer
double = (2*)

doubleList :: [Integer] -> [Integer]
doubleList [] = []
doubleList (n:ns) = (double n):doubleList ns

applyToList :: (a -> a) -> [a] -> [a]
applyToList _ [] = []
applyToList f (n:ns) = (f n):(applyToList f ns)

findMaxString :: [[Char]] -> [Char]
findMaxString =
  let
    maxString s t
     | (length s) < (length t) = t
     | otherwise = s
  in foldl maxString ""

findMaxString' :: [[Char]] -> [Char]
findMaxString' = foldl maxString ""
 where
  maxString s t
   | (length s) < (length t) = t
   | otherwise = s

data Color = Blue
           | Green
           | Yellow
           | Orange
           | Red

data Shape = Square Float
           | Circle Float
           | Rectangle Float Float
           | Triangle Float Float deriving Show

extractCircles :: [Shape] -> [Shape]
extractCircles [] = []
extractCircles (c@(Circle _):cs) = c:(extractCircles cs)
extractCircles (n:ns) = (extractCircles ns)

area :: Shape -> Float
area (Circle r) = 0.5 * pi * r * r

safeHead :: [a] -> Maybe a
safeHead [] = Nothing
safeHead (n:ns) = Just n

safeTail :: [a] -> Maybe [a]
safeTail [] = Nothing
safeTail (n:ns) = Just ns

addMaybe :: [a] -> a

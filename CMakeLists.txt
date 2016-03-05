project("codeeval" CXX)
cmake_minimum_required(VERSION 3.0)

function   (add_challenge val)
    add_executable(challenge-${val} challenge-${val}.cpp)
endfunction(add_challenge)

add_executable(echo echo.cpp)

add_challenge(0001) #Fizzbuzz
add_challenge(0002) #Longest Lines
add_challenge(0008) #Reverse Words

add_challenge(0012) #First Non-Repeated Character
add_challenge(0015) #Endianness
add_challenge(0019) #Bit Positions

add_challenge(0020) #Lowercase
add_challenge(0022) #Fibonacci Series
add_challenge(0023) #Multiplication Tables
add_challenge(0025) #Odd Numbers

add_challenge(0031) #Rightmost Char
add_challenge(0039) #Happy Numbers

add_challenge(0041) #Array Absurdity
add_challenge(0048) #Discount Offers

add_challenge(0051) #Closest Pair

add_challenge(0064) #Climbing Stairs

add_challenge(0076) #String Rotation

add_challenge(0108) #Computer Terminal

add_challenge(0192) #Compare Points

add_challenge(0207) #Which Way is Faster?
add_challenge(0227) #Real Fake

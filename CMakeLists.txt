project("codeeval" CXX)
cmake_minimum_required(VERSION 3.0)

function   (add_challenge val)
    add_executable(challenge-${val} challenge-${val}.cpp)
endfunction(add_challenge)

add_executable(echo echo.cpp)

add_challenge(0001) #Fizzbuzz
add_challenge(0008) #Reverse Words

add_challenge(0012) #First Non-Repeated Character

add_challenge(0031) #Rightmost Char

add_challenge(0041) #Array Absurdity
add_challenge(0048) #Discount Offers

add_challenge(0051) #Closest Pair

add_challenge(0076) #String Rotation

add_challenge(0108) #Computer Terminal

add_challenge(0192) #Compare Points

add_challenge(0227) #Real Fake

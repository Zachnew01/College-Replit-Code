# Zachary Newman - Thursday September 9th, 2021

# Data types: string, floating-point number, integer
# Complex data types: list, tuples, dictionary
# If():, Else:, Elif():
# 1 KB = 1024 bytes (2^10)
# 1 MB = 1048576 bytes (2^20)
# 1 GB = 1073741824 bytes (2^30)
# logic ops: not(), and, or (in order of occurrence)
# assert() - if true, continue; if false, error
# x,y,z = function(x,y,z) (function(x,y,z) has return x, y, z)

import math
zz = 1
'''
def testFunc():
  global zz
  zz += 1
  testVal = 0
  testVal = float(input("Please input a number: "))
  if (testVal > 0):
    print("Your number is positive!")
    print(format(testVal,'.2f'))
  elif (testVal < 0):
    print("Your number is negative!")
    print(format(testVal,'.2e'))
  else:
    print("Your number is either invalid or zero.")

contVal = 0
while(contVal == 0):
  if(int(input("Input 0 if you would like to use \"testFunc\": ")) == 0):
    testFunc()
  contVal = int(input("Input 0 to continue or any non-zero number to stop: "))
'''
print(str(zz))

print(math.log(math.e))
print(math.log10(100))

myList = [1,3,2,5,4,7,6,9,8,10]
for num in myList:
  print(num,end=' ')
print()
myList.sort()
print(myList)

file = open("array.txt", "w")

for i in range (256):
    file.write("/*   ")
    str_ = bin(i)
    str = str_[2:]

    strZero = '00000000'

    numSimbols = 8 - len(str)

    newStr = strZero[:numSimbols] + str

    str = newStr
    
    file.write(str[:2])

    file.write(' ')

    file.write(str[2:5])

    file.write(' ')
    
    file.write(str[5:])
    file.write("   */ 0,\n")

file.close()

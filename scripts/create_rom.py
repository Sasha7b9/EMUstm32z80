import struct

file = open("..\\EMUstm32z80\\ROM\\48.ROM", "br")
fileOut = open("ROM.c", "w")

fileOut.write("uint8 RAM48[65536] =\n")
fileOut.write("{\n")

for i in range (16384 // 16):
    fileOut.write("   ")
    for j in range (16):
        value = struct.unpack('@B', file.read(1))
        fileOut.write("  " + str(hex(value[0])) + ",")
    fileOut.write("\n")

fileOut.write("};\n")
    
file.close()
fileOut.close()


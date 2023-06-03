import sys

def xor(input):
    output = bytearray(len(input))
    for i in range(len(input)):
        output[i] = input[i] ^ 0xff
    return output

def main():
    with open(sys.argv[1], 'rb') as filein:
        filedata = bytearray(filein.read())

    fileout = open(sys.argv[2], 'wb')
    fileout.write(xor(filedata))
    fileout.close()

if __name__ == '__main__':
    main()

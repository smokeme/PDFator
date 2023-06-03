# PDFator

PDFator is an InfoSec project that consists of a Python script and a C application to generate an executable payload. The payload includes functionality to write and execute a PDF file and execute shellcode. Both the PDF file and shellcode are encrypted using XOR and decrypted at runtime.

## Requirements

To run this project, you need the following:

- Python 3.x
- MinGW (Minimalist GNU for Windows)

---

MinGW can be downloaded from here http://musl.cc/

## Usage

1. Clone the repository:
  ```bash
  git clone https://github.com/smokeme/PDFator.git
  ```
2. Change into the project directory:
  ```bash
  cd PDFator
  ```
3. Prepare the payload by running the Python script:
  ```bash
  python generate.py <raw_shellcode> <pdf_file>
  ```
Replace `<raw_shellcode>` with the path to your shellcode file, and `<pdf_file>` with the path to your PDF file.
The generated payload can be found in the project root directory with the name `payload.exe`.


## License

This project is licensed under the MIT License.

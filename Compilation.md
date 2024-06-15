# Compilation Guide

This guide provides instructions for compiling the socket server program using the following command:

g++ Socket/BindingSocket.cpp Socket/ListeningSocket.cpp Socket/Create_socket.cpp Server/TestServer.cpp Server/Simpleserver.cpp Server/test.cpp -o test.exe

## Prerequisites

Before compiling the program, ensure that you have the following prerequisites installed on your system:

- C++ compiler (e.g., g++ for GCC)

## Step-by-Step Compilation

Follow these steps to compile the socket server program:

1. Open a terminal or command prompt.

2. Navigate to the directory containing the `Socket` and `Server` directories, as well as the C++ source files.

3. Run the following command:

g++ Socket/BindingSocket.cpp Socket/ListeningSocket.cpp Socket/Create_socket.cpp Server/TestServer.cpp Server/Simpleserver.cpp Server/test.cpp -o test.exe

This command compiles the specified C++ source files (`BindingSocket.cpp`, `ListeningSocket.cpp`, `Create_socket.cpp`, `TestServer.cpp`, `Simpleserver.cpp`, and `test.cpp`) and links them into a single executable named `test.exe`.

4. If the compilation is successful, you should see no errors or warnings. The compiled executable `test.exe` will be created in the same directory.

## Running the Executable

After successful compilation, you can run the `test.exe` executable by entering the following command in the terminal or command prompt:

./test.exe

This will start the socket server program, and it will begin listening for incoming client connections on the specified port (configured within the source code).

## Troubleshooting

If you encounter any issues during compilation, ensure that:

- The file paths and names in the compilation command are correct and match the locations of your source files.
- You have the necessary permissions to execute the compiler and create the output executable file.
- Your C++ compiler is installed and configured correctly on your system.

If the issues persist, you may need to consult the documentation for your specific C++ compiler or seek further assistance.





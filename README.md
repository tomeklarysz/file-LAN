# C++ HTTP File Server

A lightweight, multi-threaded HTTP file server written in C++ that enables easy file sharing over a network.

## Features

- 🚀 Multi-threaded client handling
- 📂 Simple RESTful API for file operations
- 🔄 Cross-platform compatibility (Windows/Unix)
- 📡 Binary file streaming
- 🔒 URL-safe file handling

## Prerequisites

- C++ compiler with C++17 support
- CMake (minimum version 3.10)
- Windows: Visual Studio or MinGW with g++
- Unix: GCC or Clang

## Building
Clone the repository
 ```bash
git clone https://github.com/tomeklarysz/file-LAN.git
cd file-LAN
```
Create and enter build directory
```bash
mkdir build
cd build
```

Generate build files and build the project
```bash
cmake ..
cmake --build .
```

## Running
On Unix-like systems
```bash
./server
```
On Windows
```bash
.\server.exe
```

The server will start on port 3490 and create a `shared_files` directory in the same folder as the executable if it doesn't exist.

## Usage

### Setting Up

1. Start the server as shown above
2. Place files you want to share in the `shared_files` directory
3. Server will be accessible at `http://localhost:3490`

### API Endpoints

#### List Available Files
```bash
GET http://localhost:3490/files
```

Returns a list of all files available for download.

#### Download a File
```bash
GET http://localhost:3490/files/filename.txt
```

Downloads the specified file. The filename should be URL-encoded if it contains special characters.

### Example Using cURL
List files
```bash
curl http://localhost:3490/files
```

Download a file
```bash
curl -O http://localhost:3490/files/download/example.txt
```

## Configuration

- Default port: 3490 (defined in `headers/start_server.h`)
- Default shared directory: `./shared_files`

## Technical Details

- Uses standard C++ networking libraries
- Implements proper HTTP/1.1 response handling
- Supports binary file transfers
- Includes URL decoding for safe file handling
- Cross-platform socket cleanup
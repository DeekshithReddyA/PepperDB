# 🌶️ PepperDB

A lightweight, high-performance in-memory key-value database written in C++. PepperDB provides a simple and fast way to store and retrieve string-based key-value pairs with a Redis-like command interface.

## 🚀 Quick Start

### Using Docker (Recommended)

```bash
docker run -it deekshithreddya/pepperdb:latest
```

### Building from Source

```bash
# Clone the repository
git clone https://github.com/yourusername/pepperdb.git
cd pepperdb

# Build the project
mkdir build
cd build
cmake ..
make

# Run PepperDB
./pepperdb
```

## 📖 Features

- **In-Memory Storage**: Lightning-fast key-value operations
- **Simple Command Interface**: Redis-like syntax for ease of use
- **Lightweight**: Minimal dependencies and resource footprint
- **Interactive REPL**: Built-in command-line interface
- **Active/Passive cleanup**: Efficient expiration management for keys

## 🔧 Commands

PepperDB supports the following commands:

| Command | Description | Example |
|---------|-------------|---------|
| `SET key value` | Set a key to hold a string value | `SET name John` |
| `SET key value EX seconds` | Set a key with an expiration time in seconds | `SET session token abc123 EX 60` |
| `TTL key` | Get the time-to-live for a key | `TTL session` |
| `PERSIST key` | Remove the expiration from a key | `PERSIST session` |
| `EXPIRE key seconds` | Set a key to expire after a certain number of seconds | `EXPIRE session 120` |
| `GET key` | Get the value of a key | `GET name` |
| `DEL key` | Delete a key | `DEL name` |
| `EXISTS key` | Check if a key exists | `EXISTS name` |
| `KEYS` | List all keys | `KEYS` |
| `COUNT` | Get the number of keys | `COUNT` |
| `CLEAR` | Remove all keys | `CLEAR` |
| `EXIT` / `QUIT` | Exit PepperDB | `EXIT` |

## 💻 Usage Example

```bash
PepperDB booted
Type 'exit' or 'quit' to leave.
pepperdb> SET greeting "Hello, World!"
OK
pepperdb> GET greeting
Hello, World!
pepperdb> EXISTS greeting
(integer) 1
pepperdb> COUNT
(integer) 1
pepperdb> KEYS
greeting
pepperdb> DEL greeting
(integer) 1
pepperdb> GET greeting
(nil)
pepperdb> SET session_token abc123 EX 100
OK
pepperdb> TTL session_token
(integer) 100
pepperdb> PERSIST session_token
(integer) 1
pepperdb> EXPIRE session_token 120
(integer) 1
pepperdb> TTL greeting
(integer) -2
pepperdb> EXIT
PepperDB shutdown
```

## 🛠️ Requirements

- C++17 or higher
- CMake 3.10 or higher
- Docker (for containerized deployment)

## 📁 Project Structure

```
pepperdb/
├── src/
│   ├── main.cpp        # Entry point
│   ├── repl.cpp        # REPL implementation
│   ├── parser.cpp      # Command parser
│   ├── executer.cpp    # Command executor
│   └── database.cpp    # Core database logic
├── include/
│   └── pepperdb/
│       └── core/       # Core headers
├── CMakeLists.txt      # Build configuration
└── Dockerfile          # Docker configuration
```

## 🤝 Contributing

Contributions are welcome! Feel free to submit issues or pull requests.


## 🔮 Future Plans

- Persistence support
- Multi-threaded operations
- Additional data types (lists, sets, hashes)
- Network protocol support
- Backup and restore functionality

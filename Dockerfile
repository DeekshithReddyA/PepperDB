# Build stage
FROM ubuntu:22.04 AS builder

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++ \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy source files
COPY CMakeLists.txt ./
COPY src/ ./src/
COPY include/ ./include/

# Build the project
RUN mkdir build && cd build && \
    cmake .. && \
    make

# Runtime stage
FROM ubuntu:22.04

# Install runtime dependencies (if any)
RUN apt-get update && apt-get install -y \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy built binary from builder stage
COPY --from=builder /app/build/pepperdb .

# Set the entrypoint
ENTRYPOINT ["./pepperdb"]

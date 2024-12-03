FROM alpine:latest

# Install necessary tools and libraries
RUN apk add --no-cache \
    build-base \
    cmake \
    g++ \
    opencv-dev \
    git \
    python3 \
    boost-dev \
    zlib-dev \
    openssl-dev \
    asio-dev

# Install Google Test
RUN git clone https://github.com/google/googletest.git /tmp/googletest \
    && cd /tmp/googletest \
    && cmake -S . -B build \
    && cmake --build build \
    && cmake --install build \
    && rm -rf /tmp/googletest

# Install Crow web framework
RUN git clone https://github.com/CrowCpp/Crow.git /tmp/crow \
    && cd /tmp/crow \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make install \
    && rm -rf /tmp/crow

# Set working directory
WORKDIR /app

# Copy project files into the container
COPY . .

# Build the project
RUN mkdir build && cd build && cmake .. && make

# Expose the server port
EXPOSE 18080

# Set the default command to run the server
CMD ["./build/api_service"]

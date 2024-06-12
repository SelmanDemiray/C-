# Use the official GCC image from the Docker Hub
FROM gcc:latest

# Install additional dependencies (e.g., Boost, CMake)
RUN apt-get update && apt-get install -y \
    libboost-all-dev \
    libopencv-dev \
    cmake \
    git \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory in the container
WORKDIR /usr/src/app

# Clone the GitHub repository
RUN git clone https://github.com/yourusername/yourrepo.git .

# Build the application
RUN g++ -o main main.cpp -lboost_system -lboost_filesystem -lboost_regex -lopencv_core -lopencv_highgui -lopencv_imgcodecs

# Expose port 8080 for web access
EXPOSE 8080

# Run the application
CMD ["./main"]

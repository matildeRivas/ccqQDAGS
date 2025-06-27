# Stage 1: Build stage
FROM ubuntu:latest AS build

RUN apt-get update && apt-get install -y build-essential cmake 

# Set the working directory
WORKDIR /app

COPY src/ ./src/
COPY includes/ ./includes/
COPY queries/ ./queries/
COPY external/ ./external/
COPY runqueries/runqueries.sh .
RUN chmod +x runqueries.sh
COPY CMakeLists.txt .

RUN cmake -S . -B ./build && \
    cmake --build ./build

# run all queries
ENTRYPOINT ["/bin/bash", "./runqueries.sh"]

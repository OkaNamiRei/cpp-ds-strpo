FROM ubuntu:22.04

RUN apt-get update && apt-get install -y g++ && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY ascii_cat.cpp .
RUN g++ -std=c++17 -O2 ascii_cat.cpp -o ascii_cat

CMD ["./ascii_cat"]

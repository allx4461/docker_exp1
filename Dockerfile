FROM gcc:11 AS builder

WORKDIR /app

COPY *.cpp .
COPY *.h .

RUN g++ -std=c++14 -pthread -O2 -o app main.cpp actor.cpp bubble.cpp canvas.cpp entity.cpp fishes.cpp world.cpp

FROM ubuntu:22.04

WORKDIR /app

COPY --from=builder /app/app .

RUN apt-get update && apt-get install -y --no-install-recommends \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

CMD ["./app"]

FROM gcc:11
WORKDIR /app
COPY *.cpp .
COPY *.h .
RUN g++ -std=c++14 -pthread -o app main.cpp actor.cpp bubble.cpp canvas.cpp entity.cpp fishes.cpp world.cpp

CMD ["./app"]

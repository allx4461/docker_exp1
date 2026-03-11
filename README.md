# uuuugh

<img width="748" height="78" alt="image" src="https://github.com/user-attachments/assets/d62ddae8-232a-47ef-941e-6cfc476b76e0" />
я сделала две версии докерфайла, вторая сильно легче за счет того что в ней только бинарь

почему все работает? 

### первая версия
```dockerfile 
FROM gcc:11 #все что нужно для сборки
WORKDIR /app #бахнули рабочую директорию
COPY *.cpp . #скопировали из папки все спп
COPY *.h . #и все хедеры
RUN g++ -std=c++14 -pthread -o app main.cpp actor.cpp bubble.cpp canvas.cpp entity.cpp fishes.cpp world.cpp #довели до объектного файла 

CMD ["./app"] #при старте контейнера запускается приложение
```
и вроде все хорошо но тяжело

### вторая версия, вдохновленная сегодняшней парой
```dockerfile
FROM gcc:11 AS builder
WORKDIR /app
COPY *.cpp .
COPY *.h .
RUN g++ -std=c++14 -pthread -O2 -o app main.cpp actor.cpp bubble.cpp canvas.cpp entity.cpp fishes.cpp world.cpp #-o2 флаг для оптимизации 2 уровня. 
FROM ubuntu:22.04 #можно было поставить альпин но я испугалась
WORKDIR /app
COPY --from=builder /app/app . #во второй стадии нам нужен 
RUN apt-get update && apt-get install -y --no-install-recommends \ #флаги для сильных и независимых. сами решаем что ставить
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/* #почистили кешу 

CMD ["./app"]
```

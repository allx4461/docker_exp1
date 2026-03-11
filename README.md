# uuuugh

<img width="838" height="128" alt="image" src="https://github.com/user-attachments/assets/d32fe0e6-c984-4a3d-8b11-05ce4534a9a1" />

я сделала две версии докерфайла, вторая сильно легче за счет того что в ней только бинарь
upd: я сделала три версии. , третья самая отчаянная, хоть и пришлось немного покопаться тк контейнер не хотел билдиться
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
RUN g++ -std=c++14 -pthread -O2 -o app main.cpp actor.cpp bubble.cpp canvas.cpp entity.cpp fishes.cpp world.cpp #-o2 флаг для оптимизации 2 
FROM ubuntu:22.04 #можно было поставить альпин но я испугалась
WORKDIR /app
COPY --from=builder /app/app . #во второй стадии нам нужен 
RUN apt-get update && apt-get install -y --no-install-recommends \ #флаги для сильных и независимых. сами решаем что ставить
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/* #почистили кешу 

CMD ["./app"]
```
### третья версия, вдохновленная отчаянием
```dockerfile 
FROM alpine:3.18 AS builder #на основе альпина
RUN apk add --no-cache g++ make # тут вместо чистки флажок 
WORKDIR /app
COPY *.cpp .
COPY *.h .
RUN g++ -std=c++11 -pthread -static -O3 -o app \#без флага статик ничего не работало. + оптимизация 3 
    main.cpp actor.cpp bubble.cpp canvas.cpp entity.cpp fishes.cpp world.cpp
FROM alpine:3.18
WORKDIR /app
COPY --from=builder /app/app .

CMD ["./app"]
```
я не знаю на каком святом духе это работает но было очень интересно. осталось сделать ридми на английском потому что так круче. 

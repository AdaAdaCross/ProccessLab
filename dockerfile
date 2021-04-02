FROM alpine
COPY bee.cpp .
COPY bear.cpp .
RUN apk add gcc g++
RUN g++ -o bee bee.cpp
RUN g++ -o bear bear.cpp
CMD ./bear 1 5 10

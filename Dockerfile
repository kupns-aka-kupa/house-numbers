FROM gcc:latest as build

RUN apt-get update
RUN apt-get install cmake -y

COPY . /app

WORKDIR /app
RUN cmake -E make_directory build
RUN cmake -B build -S . -DCMAKE_BUILD_TYPE=Release

WORKDIR /app/build
RUN cmake --build .

FROM ubuntu:latest

WORKDIR /app

COPY --from=build /app/build/house-numbers .
COPY --from=build /app/build/_deps/pytorch-src/lib/* /usr/local/lib/

RUN ldconfig -v

ENTRYPOINT [ "./house-numbers" ]


FROM rikorose/gcc-cmake:gcc-9 as build

COPY . /app

WORKDIR /app
RUN cmake -E make_directory build
RUN cmake -B build -S . -DCMAKE_BUILD_TYPE=Release

WORKDIR /app/build
RUN cmake --build .

FROM ubuntu:latest

WORKDIR /app

COPY --from=build /app/build/mnist /usr/local/bin

COPY pytorch.conf /etc/ld.so.conf.d/

ENTRYPOINT [ "mnist" ]

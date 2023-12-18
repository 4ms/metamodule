LABEL org.opencontainers.image.source=https://github.com/4ms/metamodule
FROM ubuntu:22.04

ARG flatbuffer_version=v23.5.26

RUN apt update && apt upgrade -y && apt clean
RUN apt update && apt install git ninja-build build-essential bsdmainutils xxd python3 -y && apt clean
RUN apt update && apt install -y cmake && git clone --depth 1 https://github.com/google/flatbuffers -b $flatbuffer_version && cd flatbuffers && cmake -S . -B build -G Ninja && cmake --build build --target install && cd .. && rm -rf flatbuffers && apt remove cmake -y && apt clean

RUN flatc --version


# Build stage
# FROM ubuntu:18.04
FROM debian:10.13
ARG USER=vscode
RUN useradd -m -s /bin/bash $USER
RUN echo ========== Install dependencies ========== \
  && apt-get update && apt-get install -y \
    clang \
    ffmpeg \
    libavformat-dev \
    libavcodec-dev \
    libavutil-dev \
    gdb \
    git \
    libavahi-compat-libdnssd-dev \
    libssl-dev \
    make \
    openssh-server \
    perl \
    unzip \
    wget \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*
USER vscode
WORKDIR /build

# Build stage
# FROM ubuntu:18.04
FROM debian:10.13
ARG USER=vscode
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
    sudo \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*
RUN useradd -m -s /bin/bash $USER \
    && echo $USER ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USER \
    && chmod 0440 /etc/sudoers.d/$USER
USER vscode
WORKDIR /build

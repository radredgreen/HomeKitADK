# Build stage
FROM ubuntu:18.04
ARG USER=vscode
RUN echo ========== Install dependencies ========== \
  && apt-get update && apt-get install -y \
    clang \
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
    libturbojpeg0-dev \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*
RUN useradd -m -s /bin/bash $USER \
    && echo $USER ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USER \
    && chmod 0440 /etc/sudoers.d/$USER
USER vscode
WORKDIR /build

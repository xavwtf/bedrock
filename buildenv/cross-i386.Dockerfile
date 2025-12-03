FROM techiekeith/gcc-cross-i686-elf

# build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    make \
    grub-pc-bin \
    xorriso \
    mtools \
    qemu-system-x86 \
    git \
    curl \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /bedrock

CMD ["/bin/bash"]
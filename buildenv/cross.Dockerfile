FROM techiekeith/gcc-cross-i686-elf

# build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    make \
    grub-pc-bin \
    grub-efi-amd64-bin \
    xorriso \
    mtools \
    qemu-system-x86 \
    nasm \
    git \
    curl \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /bedrock

CMD ["/bin/bash"]
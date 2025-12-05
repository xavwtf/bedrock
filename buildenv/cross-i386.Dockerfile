FROM techiekeith/gcc-cross-i686-elf

# build tools
# note: it isn't required to install libmpc, libmpfr or libgmp when building natively
# but in some strange cases they're required?? especially when building via github actions workflow
RUN apt-get update && apt-get install -y --no-install-recommends \
    libmpc3 libmpfr6 libgmp10 \
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
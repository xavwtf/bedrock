# Bedrock - a small (useless) operating system

Bedrock is a small, largely non-functional operating system. It's a hobbyist implementation and, as such, is not the primary object of anyone's time. It is built from the ground up, featuring its own kernel, userspace and standard library. Eventually.

## Building Bedrock

As of now, Bedrock does not possess the capability to be compiled under itself, so the optimal method to build Bedrock is by using a cross-compiler.

Bedrock currently targets the following architectures:
- i386 (IA32)

If you have any issues with script execution, try **running chmod +x** on all build scripts in the repo. You can run this simple command to perform this task on every build script automatically:

```bash
find . -name "*.sh" -exec chmod +x {} \;
```

### Build instructions - Bedrock

...yeah, I wish.

### Build instructions - Docker
We provide Dockerfiles designed for cross-compiling Bedrock in `buildenv`. It includes the cross-compiler relevant for your chosen target, and any packages required, as well as some useful utilities. This is the recommended platform to build Bedrock on as it provides a standardised environment and as such limits the amount of errors that can occur simply from environmental issues, as well as overall being an easier and faster setup (full GCC toolchains can take upwards of an hour to compile! Downloading binaries is *much* nicer)

To build Bedrock using Docker, first run the following command (ensure `git` is installed)

```bash
git clone https://github.com/xavvvvxd/bedrock
```

Next, build your chosen Dockerfile (depending on what architecture you would like to cross-compile for)

```bash
docker build -f buildenv/cross-i386.Dockerfile -t bedrock-kernel-i386 .
```

> Note: You'll only need to build this image once. For future builds, just make sure you're in the project root and run one of the run commands below.

Once it's built, make sure you're in the root project directory and run:

Linux:
```bash
docker run --rm -it -v $(pwd):/bedrock bedrock-kernel-i386
```

Windows (CMD):
```bat
docker run --rm -it -v %cd%:/bedrock bedrock-kernel-i386
```

Windows (PowerShell):
```ps1
docker run --rm -it -v ${pwd}:/bedrock bedrock-kernel-i386
```

You can then proceed to build Bedrock by either running `build.sh` or `iso.sh`.

> Note: Using QEMU with graphics enabled from within the Docker container will not work on WSL-based containers (at least) due to environment issues. Please `exit` the container and run the script from your host operating system.

### Build instructions - Linux

You will need to build a cross-compiler for your target architecture. Specifically, you will require the `-elf` variant of the toolchain.

A guide to easily building an i686-elf toolchain can be found [here](https://github.com/lordmilko/i686-elf-tools).

> Note: I am not responsible for the guide/tools linked. Please take any precautions, naturally.

Once the cross-compiler is installed, you must install the build dependencies.

Bedrock requires the following build dependencies:
- make
- grub
- xorriso
- mtools
- git (for cloning the repository)

and optionally:

- qemu (to emulate Bedrock, good for quick testing)

On Debian-based systems:

```bash
sudo apt update && sudo apt install -y make grub-pc-bin xorriso mtools qemu-system-x86 git
```

For Arch users (btw):
```bash
sudo pacman -Syu --needed make grub libisoburn mtools qemu-system-x86 git
```

Fedora:
```bash
sudo dnf install make grub2-tools-extra xorriso mtools qemu-system-x86 git --refresh
```

> On Fedora-based systems, `grub-mkrescue` is called `grub2-mkrescue`. This is handled in the build script, but it's good to be aware of that.

Once all build dependencies are installed, `git clone` this repository to anywhere you prefer:

```bash
git clone https://github.com/xavvvvxd/bedrock
```

`cd` into the newly created directory and run `iso.sh`:

```bash
cd bedrock && ./iso.sh
```

(or run.sh, both build the operating system)


### Build instructions - Windows (WSL)

While building on Windows is not explicitly supported, you could use the Windows Subsystem for Linux (WSL) tool or Docker to provide a Linux-like environment you can use to build Bedrock.

> Note: Docker Desktop for Windows has a dependency on WSL to begin with, so you should follow the WSL installation part of this guide if you plan to use Docker. After that, install Docker Desktop and follow the Docker installation guide.

First, we need to install WSL. Run PowerShell as Administrator then run:

```ps1
wsl --install
```

This will install the WSL2 system and a default Linux distribution (Ubuntu)

Start WSL using:

```ps1
wsl
```

Once inside WSL, you may be prompted to setup a user. Follow any setup it asks you to do.

Once setup, you are effectively in a Linux environment. You're free to follow the Linux section of this build guide - everything should work the same.

### Build instructions - macOS

> Note: building on a macOS host is not entirely supported. It might work, but if you encounter any issues we can't help you unfortunately. None of this guide is tested. Additionally, this won't build an ISO, only a kernel binary that isn't usable on its own. I'd highly recommend just using Docker for this task, but if you insist...

Ensure you have the `brew` package manager installed.

First, update Homebrew using this command:

```bash
brew update
```

You can then install the i686-elf toolchain using the following command:

```bash
brew install i686-elf-gcc
```

Once that's installed, install the other build dependencies:

```bash
brew install make git
```

Download the repository locally:

```bash
git clone https://github.com/xavvvvxd/bedrock
```

`cd` into it and run:

```bash
./build.sh
```
# mikron

Microkernel for ARM devices. Currently targetting `qemu-system-arm`'s `virt` board. 

## Building

1. Install CMake (version 3.16 or above), build-essential and arm-none-eabi toolchain:

```sh
sudo apt install cmake build-essential gcc-arm-none-eabi libnewlib-arm-none-eabi
```

2. Recursively clone this repository:

```sh
git clone --recursive https://github.com/s95rob/mikron
```

3. Change directory and configure with CMake, then build all targets with Make:

```sh
cd mikron
cmake -S . -B build
cd build
make all
```

## Running

Mikron is currently only designed to run on qemu. 

1. Install `qemu-system-arm`

```sh
sudo apt install qemu-system-arm
```

2. Run the generated `boot.bin` image*:

```sh
qemu-system-arm -machine virt -m 512M -bios boot/boot.bin
```

<sub>* Assuming current directory is still `../mikron/build` from the [Building](#building) section.</sub>
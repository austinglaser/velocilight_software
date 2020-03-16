# Velocilight Software

This repository contains code from several embedded-systems art projects. I am
the primary author, but some portions of the code were written by other
developers, or are third-party libraries. They've been left to provide context
for the software projects as a whole.

Here is a brief overview of the content:

- `chibios`: An open-source RTOS and hardware abstraction layer (third-party)
- `chibios-contrib`: Extra community contributions to ChibiOS (third-party)
- `common`: Software components shared between multiple projects
    - `common/arm_math`: Code for math acceleration on Cortex-M MCUs
        (third-party)
    - `common/fft`: Simple wrappers around FFTs (Written by another developer)
    - `common/generated`: Lookup tables too tedious to write by hand
    - `common/perlin`: An implementation of [Ken Perlin's psuedorandom noise
        generator](https://mrl.nyu.edu/~perlin/noise/)
- `modules`: More reusable software components (collaboration of many
    developers)
- `nrf5-sdk`: An old version of Nordic Semiconductor's SDK (third-party)
- `soundpuddle_fpga`: Several applications meant to run on the FPGA half of an
    interactive art project
- `soundpuddle_mcu`: Firmware for the MCU half (an STM32H7) of the same
    interactive art project
- `velomicro`: A small motion-reactive LED control application

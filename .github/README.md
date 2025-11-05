<h1 align="center">
  YutsuOS - EPITECH PROJECT 2025<br>
  <img src="https://raw.githubusercontent.com/catppuccin/catppuccin/main/assets/palette/macchiato.png" width="600px"/>
  <br>
</h1>

<div align="center">
  <p></p>
  <div align="center">
     <a href="https://github.com/Leorevoir/YutsuOS/stargazers">
        <img src="https://img.shields.io/github/stars/Leorevoir/YutsuOS?color=F5BDE6&labelColor=303446&style=for-the-badge&logo=starship&logoColor=F5BDE6">
     </a>
     <a href="https://github.com/Leorevoir/YutsuOS/">
        <img src="https://img.shields.io/github/repo-size/Leorevoir/YutsuOS?color=C6A0F6&labelColor=303446&style=for-the-badge&logo=github&logoColor=C6A0F6">
     </a>
     <a href="https://github.com/Leorevoir/YutsuOS/blob/main/LICENSE">
        <img src="https://img.shields.io/static/v1.svg?style=for-the-badge&label=License&message=GPL-3.0&colorA=313244&colorB=F5A97F&logo=unlicense&logoColor=F5A97F&"/>
     </a>
  </div>
  <br>
</div>

<p align="center">
  YutsuOS<br>
  a working x86-32 Kernel from Scratch
</p>

---

## Description

YutsuOS was a project I made during my 3rd year at EPITECH. The goal was to discover the **real** kernel-level programming.

![**showcase**](./assets/showcase.png)

## Installation

Ensure you have the right dependencies:

```bash
cmake
gcc
ninja
nasm
qemu-system-x86
grub-pc-bin
grub-common
```

Build the project:

```bash
./build.sh
```

Run the OS in a Virtual Machine:

```bash
./build.sh --run
```

## Tested on

- EndeavourOS
- Arch Linux
- Ubuntu

---

## Documentation

See [**DOCUMENTATION**](../docs/README.md)

## License

Project developed as part of the G-PRO-500 module at EPITECH.
See [**LICENSE**](./LICENSE).

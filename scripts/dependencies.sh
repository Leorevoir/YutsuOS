#!/usr/bin/env bash

set -e

function install_dependencies()
{
    local packages="cmake gcc ninja-build nasm make qemu-system-x86 qemu-utils grub-pc-bin grub-common grub2-common xorriso"

    apt update && sudo apt upgrade -y
    apt install -y $packages
}

install_dependencies "$@"

#!/usr/bin/env bash

#
# CI/CD script to install dependencies on Ubuntu for the gitaction workflow
#

set -e

function install_dependencies()
{
    local packages="cmake gcc ninja-build nasm make qemu-system-x86 qemu-utils grub-pc-bin grub-common grub2-common xorriso"

    sudo apt update
    sudo apt install -y $packages
}

install_dependencies "$@"

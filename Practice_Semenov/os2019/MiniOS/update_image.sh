#!/bin/bash
echo "Creating empty image file...";
# для работы fdisk'а
dd if=/dev/zero of=./hdd.img bs=512 count=16065
echo "Attaching block device file using first found loop device..."
# рассмотрим файл как device, чтобы работать с fdisk'ком
device=`sudo losetup --find --show  ./hdd.img`
echo "Creating partition table and bootable partition..."
# o - create table, w - save and exit
(echo o; echo w;) |                                      \
#
sudo fdisk $device
(echo n; echo p; echo 1; echo ; echo ; echo a; echo w;) |\
sudo fdisk $device
echo "Reattaching device and newly created partitions..."
sudo losetup -d $device
device=`sudo losetup --find --show  --partscan ./hdd.img`
partition="$device""p1"
echo "Formatting partition to ext4 filesystem..."
sudo mkfs.ext4 $partition
echo "Mounting partition to first found loop device..."
sudo mkdir -p drive
sudo mount $partition drive
echo "Installing grub to bootable partition..."
sudo grub-install                 \
		--recheck                     \
		--boot-directory=drive/boot/  \
		--target=i386-pc              \
		--uefi-secure-boot            \
		$device
echo "Creating grub menu config file..."
sudo cat >> grub.cfg << EOF
set timeout=30
set default=0
menuentry "Mini OS" {
	multiboot /boot/MiniOS.bin
	boot
}
EOF
echo "Removing temporary files and resources..."
sudo mv grub.cfg drive/boot/grub/
sudo cp ./src/MiniOS.bin drive/boot/MiniOS.bin
sudo umount drive
sudo rm  -r drive
sudo losetup -d $device
echo "Done!"

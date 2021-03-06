#! /bin/sh
#automating script for making CD games

DIR=$PWD
PROJECT_NAME="GLDC_tests"

# go to  build directory
# make clean
make

#elf transform??
sh-elf-objcopy -R .stack -O binary main.elf output.bin

#scraming process
/home/lerabot/Dreamcast/kos/utils/scramble/scramble output.bin 1ST_READ.bin

#creating iso -> -o outputname.cdi / build files path
mkisofs -C 0,11702 -V DC_GAME -G IP.BIN -r -J -l -o ../$PROJECT_NAME.iso $DIR
#mkisofs -C 0,45000 -V DC_GAME -G IP.BIN -r -J -l -o ../$PROJECT_NAME.iso $DIR
#mkisofs -C 0,0 -V DC_GAME -G IP.BIN -r -J -l -o ../$PROJECT_NAME.iso $DIR

#transform iso into a CDI
/home/lerabot/Dreamcast/kos/utils/cdi4cd/cdi4dc ../$PROJECT_NAME.iso ../$PROJECT_NAME.cdi -d > cdi4dc.log

sudo arp -s 192.168.0.99 00:d0:f1:03:14:02

#start the game
#sudo ../dc-tool-ip -t dreamcast -i ../phenix_data.iso -x main.elf
#sudo ../dc-tool-ip -t dreamcast -c ./ -x main.elf
#lxdream --audio=null main.elf
#lxdream main.elf
lxdream --audio=null ../$PROJECT_NAME.iso
#reicast ../$PROJECT_NAME.cdi
#../redream ../$PROJECT_NAME.cdi

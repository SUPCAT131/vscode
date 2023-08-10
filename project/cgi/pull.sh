sudo arm-linux-gnueabihf-gcc ../include/cgic.c $1.c -o $1.cgi
sudo cp $1.cgi ~/rootfs/www/cgi-bin/
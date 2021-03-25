# RetroFW 2048

![](https://telegra.ph/file/1552f2722123d084e61eb.jpg) ![](https://telegra.ph/file/fd6647ac20d8ffb6d9115.jpg)

RetroFW 2048 is a port of the puzzle game 2048 for all RetroFW-compatible devices, with 3x3 and 4x4 boards support and some animations.

Inspired by Gabriele Cirulli's original [game](https://github.com/gabrielecirulli/2048).

## Make-ing

### For Linux

Simply run `make`.  
You'll need `SDL` development libraries, and the C compiler `gcc`.  
You will get an executable called `2048.dge`, run it and enjoy your 2048 experience!  

### For RetroFW

Run `make -f Makefile.RS97`  
You'll need a [working buildroot installation](https://github.com/retrofw/retrofw.github.io/wiki/Configuring-a-Toolchain), that includes the SDL development libraries, and `gcc`. Since RetroFW runs on MIPSel devices, instead of the compiler `gcc`, the Makefile will use `mipsel-linux-gcc`, make sure it is a working command on your machine, if it isn't, make sure that the folder where the `mipsel-linux-gcc` binary is stored is in `$PATH`.
You will get a file called `build.ipk` that you can [install](https://github.com/retrofw/retrofw.github.io/wiki/Emulators-and-Apps#install-ipk) on RetroFW devices.

### For Windows

I have no idea. Just get Linux :P 

## Contributing

Contributions are always welcome! You can contribute by opening a pull request or an issue.  
You can also report me stuff via email if you don't want to sign up to whichever Git server I choose to host this project.  
My mail is hello@massivebox.eu.org.


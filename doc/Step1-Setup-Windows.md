# Setup Instruction for Windows

## Getting Started
Here are the tools you will need. You will find download links below in each section
 - A computer running Windows
 - AVR Toolchain for windows
 - GnuMake for Windows
 - A Linux-ish shell. I use Git Bash.

## Install Git Bash
I personally use Git Bash, but any shell should work (PowerShell or Command Prompt will **NOT** work). You can download Git Bash [here](https://gitforwindows.org/). After you install it. You should be able to right click in the file explorer and open Git Bash by clicking "Git Bash Here"

## Install AVR Toolchain
Download [AVR Toolchain for windows](https://www.microchip.com/mplab/avr-support/avr-and-arm-toolchains-c-compilers). Make sure you download the AVR toolchain, not the ARM. You will need to register on their website in order to download. 

Once the download is complete, extract the archive and copy the folder to `C:\Program Files` (so you don't accidentally delete them). Locate the `bin` folder inside (mine is `C:\Program Files\avr8-gnu-toolchain-win32_x86\bin`). You need to add this to the `PATH` environment variable. If you don't know how, [this article](https://www.architectryan.com/2018/03/17/add-to-the-path-on-windows-10/) will help.

Once you are done, open the shell in the root directory of the repo and type `avr-gcc`. You should see some error message indicating no input files to compiler.

## Install GNU Make
Download [GNU Make Setup](http://gnuwin32.sourceforge.net/packages/make.htm) and install it. Again, locate the `bin` folder (mine is `C:\Program Files (x86)\GnuWin32\bin`) and add it to the `PATH` environment variable.

If you open the shell in the root directory of the repo and type 'make', you should be able to build the project.

## Next Step
Please refer to the next section in [README](../README.md)
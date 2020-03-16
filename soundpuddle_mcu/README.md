SoundPuddle
===========

Software for SoundPuddle

# Setup

## Subtree

To clone and build, you don't need to do any configuration. However, if any
development touches anything under `chibios/` or `modules/`, or if you want to
update the trees underneath these directories, you will need to do some
configuration.

### Remotes

Run these three commands to add the necessary remotes:

    $ git remote add -f bes-chibios-remote git@git.boulderes.com:bes-internal/bes-chibios.git
    $ git remote add -f modules-remote git@git.boulderes.com:bes-internal/modules.git

This isn't strictly necessary, but its more convenient (and assumed) for the
following commands.

Note that the ChibiOS subtree is actually from a bes-internal "fork" of ChibiOS
GitHub repository. All upstream changes from ChibiOS are pulled in from the
bes-internal ChibiOS repository.

### Pushing to subtree repositories

To push changes to any of the subtrees, add and push changes to this repository
first (`$ git push origin master`) and then push to the appropriate subtree:

    $ git subtree push --prefix=chibios bes-chibios-remote <branch_name>
    $ git subtree push --prefix=modules modules-remote <branch_name>

### Pulling from subtree repositories

To pull changes from one of the subtree repositories, run the appropriate
command below. Note that the commands squash commits -- to keep our commit
history relatively clean you MUST always do this.

    $ git subtree pull --prefix=chibios bes-chibios-remote master --squash
    $ git subtree pull --prefix=modules modules-remote master --squash

Remember to push changes to this repository (`$ git push origin master`), after
this merge.

### Other useful commands

To do a fetch (but not merge) with all remotes, run:

    $ git remote update

## Installing ARM GCC

On Linux:

    $ sudo add-apt-repository ppa:terry.guo/gcc-arm-embedded
    $ sudo apt-get update
    $ sudo apt-get install gcc-arm-none-eabi

Otherwise:

Go to https://launchpad.net/gcc-arm-embedded, and download the appropriate
package for your platform.

## Install Dependencies

    $ sudo apt-get install python
    $ sudo apt-get install ruby
    $ sudo apt-get -y install python-pip
    $ pip install pyyaml
    $ gem install --remote rake

## Configuring the MCU platform

The following files will need to be added/updated for the target MCU:

File                                  | Description                                                                                       |
--------------------------------------|---------------------------------------------------------------------------------------------------|
`system/boards/project_vxx/boards.mk` | Makefile (Update BOARD MCU OPTIONS, Startup Files, Platform include file and BOARD LINKER SCRIPT) |
`system/app/inc/chconf.h`             | ChibiOS Kernel config                                                                             |
`system/app/inc/mcuconf.h`            | MCU Peripheral config                                                                             |
`system/app/inc/halconf.h`            | HAL Driver config                                                                                 |


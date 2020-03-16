# BES Modules

[![build status](https://git.boulderes.com/bes-internal/modules/badges/master/build.svg)](https://git.boulderes.com/bes-internal/modules/commits/master)


Internal BES modules which have no specific hardware or OS dependency.

Adding to this modules will require the following files and directories to be added at the root directory of this folder. 
For instance, if the module is *example*:

Subdirectory    | Description
----------------|-------------
`example/example.mk` | Module makefile (defines the directory paths for the top-level makefile)
`example/common/inc`| Module directory for header file(s) common to all implementations (*.h)
`example/common/src`| Module firectory for source file(s) common to all implementations (*.c)
`example/common/test/test_example.c` | Module test directory and test file with test case(s) common to all implementations
`example/common/test/support` | Module support directory and support files for testing(optional) 
`example/chibios/*`| Header, source, etc (see above) files for a specific implementation (in this case ChibiOS)


[modules.mk](modules.mk) need to be edited, to integrate the module into the build:

    $(call module, module_dir, module_name)

`module_dir` is the containing directory where the module is to be found, and
`module_name` is what it's actually called. The `module` function looks for a
makefile at `module_dir/module_name/module_name.mk`. It assumes the presence of
variables named `MODULE_NAME_INC`, `MODULE_NAME_SRC`, etc. (see [log.mk](log/log.mk) for
a module makefile example).

Refer to existing modules for the content of the module makefile and the module
test file. For a list of assertions when using the Unity test framework refer to
the [documentation](https://github.com/ThrowTheSwitch/Unity/blob/master/README.md).

For mock generation and test build management respectively, we use CMock and
Ceedling. Their documentation can be found
[here](https://github.com/ThrowTheSwitch/Ceedling/blob/master/docs/CeedlingPacket.md)
and
[here](https://github.com/ThrowTheSwitch/CMock/blob/master/docs/CMock_Summary.md).

## Install Dependencies
    $ sudo apt-get install python
    $ sudo apt-get install ruby
    $ sudo apt-get -y install python-pip
    $ pip install pyyaml
    $ gem install --remote rake




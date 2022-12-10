How to use?
- Refer to simulator.sh and demo.sh for examples on how to run the simulator.


Who did what?

Henry:
- airbags.c and functionality
- engine_toggle.c and functionality
- engine.c ground work
- interprocess communication handling in engine.c
- indicator functionality in engine as well as emergency lights functionality

Danna:
- throttle.c client and its corresponding functionality in engine.c
- brakes.c client and its corresponding functionality in engine.c
- indicators.c client 
- steering.c client and corresponding functionality in engine.c

Siddharth:
- Helped setup group member's environments for QNX development
- Setup virtual machine with mkqnximage
- Setup python3 to run on QNX
- Tried to run PySimpleGUI on QNX
- Built tkinter from source
- Tried to run Remi on QNX
- Built setuptools from source
- Tried to run easy_install on QNX 
- Tried to run PySimpleGUIWeb on QNX
- Wrote scripts to run a python based web server
- Wrote a HTML page to check whether we could use it as a frontend
- Attempted to run PHP and Javascript on QNX
- Wrote simulator.sh and demo.sh
- Reviewed all PR's and suggested changes
- Compiled and tested all code in a mkqnximage generated virtual machine
    

Note: 
- Built and tested on MacOS 13 only (which is not officially supported. Must build qemu from source and tweak mkqnximage files to bring back MacOS support). 
- Everything should work on Linux as well. 
- Windows support is not guaranteed without tweaking the appropriate scripts.
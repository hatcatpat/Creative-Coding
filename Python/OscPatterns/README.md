A project for sending OSC data for livecoding musical performance.

To install:
  I have no idea. At least need to install Python3, with pip. Then install "python-osc" via pip. Also maybe need to install "importlib" from pip.

To use:
  Run "main.py". Edit the "commands" and "variables" functions of "user_commands.py", and then send an OSC message to "/update_commands" of localhost:5005 in order to update the commands. Personally I set a keybinding in Vim to save the file and trigger an OSC message. The "command" function is called often, with "t" for "time" as an argument, this is where you trigger the notes. The "variables" function is called every time you update the file, this is where you set up the variables you want to use in "commands". The OSC messages are not sent immediately, instead the script adds the messages to a bundle, and then sends that out.

To add:
  A whole lot! I'm thinking a config file to store the out-addresses for OSC messages. Plus a ton of pattern generation stuff (toggles, euclidean, cycles, speed changes).

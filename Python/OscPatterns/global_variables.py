from importlib import reload
from osc_manager import OSCManager


def init():
    global first_command, osc, t, mod, quit, printStrings, speed, current_synth
    first_command = True
    osc = OSCManager()
    t = 0
    speed = 0.125
    mod = 16
    quit = False
    current_synth = 0

    printStrings = []

    for i in range(3):
        printStrings.append("")


def update_commands(*args):
    print("read commands")
    global user_commands, first_command, onces

    onces = []

    if first_command:
        import user_commands
        first_command = False
    else:
        reload(user_commands)

    user_commands.variables()

import global_variables

from random import *
from math import *

#SNIPPETS###############
tab = []
res = 64
for i in range(res):
    tab.append(0.0)
#CLASSES################


#UTILS##################
def tab(res, func):
    t = []
    for i in range(res):
        t.append(func(i))
    waveform(t)


def sinwave(res=64, angle=2):
    tab(res, lambda i: sin(i * angle * pi / res))


def sawwave(res=64, angle=2):
    tab(res, lambda i: -1.0 + (i * 2 / res))


def randwave(res=64, discrete=False):
    if discrete:
        discrete_randwave(res)
    else:
        tab(res, lambda i: -1.0 + 2.0 * random())


def discrete_randwave(res=64):
    tab(res, lambda i: pchoose(-1.0, 0.0, 1.0))


def speed(sp):
    global_variables.speed = sp


def chance(prob):
    return random() < prob


def prange(lo, hi):
    return random() * (hi - lo) + lo


def prandsplit(*args):
    if len(args) > 0:
        x = randint(0, len(args) - 1)
        args[x]()


def pchoose(*args):
    return choice(args)


def cycle(*args):
    return args[global_variables.t % len(args)]


def mod(*args):
    output = False

    for x in args:
        output = output or (global_variables.t % x == 0)

    return output


def t_mod(m):
    global_variables.mod = m


def once(index, *args):
    found = False
    to_remove = []

    for once_index in global_variables.onces:
        if once_index == -index:
            to_remove.append(once_index)

            break

        if once_index == index:
            found = True

            break

    for r in to_remove:
        global_variables.onces.remove(r)

    if not found:
        global_variables.onces.append(index)

        for func in args:
            tup = tuple()

            for x in func[1]:
                tup += ((x, ))

            func[0](*tup)


#OSC####################
def message(clientIndex, address, *args):
    global_variables.osc.send_osc_to_client(clientIndex, "/" + address, args)


def delay(*args):  #toggle, time, level, pan
    global_variables.osc.send_osc_message("/delay", args)


def waveform(table):
    global_variables.osc.send_osc_message("/waveform", table)


def reverb(width=0.2, room=0.2, mix=1.0):
    wet = 1.0 - mix
    dry = mix
    global_variables.osc.send_osc_message("/reverb",
                                          tuple((
                                              width,
                                              room,
                                              wet,
                                              dry,
                                          )))


def lpf(cutoff=10000.0, res=0.0, drive=1.0):
    global_variables.osc.send_osc_message("/lpf", tuple((cutoff, res, drive)))


def hpf(cutoff=0.0, res=0.0, drive=1.0):
    global_variables.osc.send_osc_message("/hpf", tuple((cutoff, res, drive)))


def reset():
    global_variables.osc.send_osc_message("/reset", 0)


def trig(*args):
    print(args)
    global_variables.osc.send_osc_message("/trig", args)


def note_off(*args):
    global_variables.osc.send_osc_message("/note_off", args)


def synth(index):
    global_variables.current_synth = index
    global_variables.osc.send_osc_message("/current_synth", index)


def mute(*args):
    global_variables.osc.send_osc_message("/mute", args)


def solo(*args):
    global_variables.osc.send_osc_message("/solo", args)


def unsolo():
    global_variables.osc.send_osc_message("/unsolo", 0)


def unmuteAll():
    global_variables.osc.send_osc_message("/unmuteAll", 0)


#ADSR
def adsr(*args):
    global_variables.osc.send_osc_message("/adsr", args)


def atk(value):
    global_variables.osc.send_osc_message(
        "/atk", [global_variables.current_synth, value])


def dec(*args):
    global_variables.osc.send_osc_message("/dec", args)


def sus(value):
    global_variables.osc.send_osc_message(
        "/sus", [global_variables.current_synth, value])


def rel(value):
    global_variables.osc.send_osc_message(
        "/rel", [global_variables.current_synth, value])


def pan(value):
    global_variables.osc.send_osc_message(
        "/pan", [global_variables.current_synth, value])


#TOGGLES
def waveToggle(*args):
    global_variables.osc.send_osc_message("/waveTog", args)


def sinTog(b):
    waveToggle(0, b)


def sawTog(b):
    waveToggle(1, b)


def sqrTog(b):
    waveToggle(2, b)


def triTog(b):
    waveToggle(3, b)


def multiTog(sin, saw, sqr, tri):
    sinTog(sin)
    sawTog(saw)
    sqrTog(sqr)
    triTog(tri)


#WAVEVOLS
def waveVol(*args):
    global_variables.osc.send_osc_message("/waveVol", args)


def sinVol(v):
    waveVol(0, v)


def sawVol(v):
    waveVol(0, v)


def sqrVol(v):
    waveVol(0, v)


def triVol(v):
    waveVol(0, v)


def multiVol(sin, saw, sqr, tri):
    sinVol(sin)
    sawVol(saw)
    sqrVol(sqr)
    triVol(tri)

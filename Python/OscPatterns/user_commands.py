from funcs import *


def variables(*args):
    global X, Y, Z, A, B, C, D, E, F, G
    speed(0.125 / 2)
    t_mod(16 * 2)
    message(0, "speed", global_variables.speed * 2)
    X = 0

    for i in range(8):
        synth(i)
        sus(1.0)
        pan(0.5)

    synth(3)
    pan(0.4)
    sus(1.25)

    synth(2)
    sus(2.0)

    synth(5)
    sus(2.0)

    synth(6)
    rel(0.2)
    pan(0.7)
    sus(0.5)

    synth(7)
    sus(0.4)
    rel(0.5)


def random_rel():
    synth(pchoose(0, 1, 2, 3))
    rel(prange(0.0, 1.0))


def random_atk():
    synth(pchoose(0, 1, 2, 3))
    atk(prange(0.0, 1.0))


def command(t):
    global X, Y, Z, A, B, C, D, E, F, G

    if mod(2, 3) or chance(0.01):
        synth(0)
        atk(prange(0.1, 1.0))
        rel(prange(0.1, 1.0))
        if chance(0.2):
            synth(1)
            pan(prange(0.0, 1.0))
            trig(1)
        else:
            trig(0)

        if mod(4, 5) or chance(0.01):
            synth(2)
            pan(prange(0.25, 0.75))
            rel(prange(0.05, 0.3))
            trig(2)

        if mod(8):
            trig(3)

        if mod(10):
            trig(7)  # to 4/7
            message(0, "blue_mode", t, 1)  # to 1/0

        if chance(0.5):
            synth(5)
            atk(1.0)
            rel(prange(0.2, 1.0))
            trig(5)

        if chance(0.1):
            trig(6)

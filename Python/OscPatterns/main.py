import sys
import threading
import time
import global_variables


def thread_func():
    while True:

        if global_variables.quit:
            break

        print(chr(27) + "[2J")
        global_variables.user_commands.command(global_variables.t)
        global_variables.osc.send_full_bundle()
        global_variables.printStrings[2] = global_variables.t

        global_variables.t += 1
        global_variables.t %= global_variables.mod

        for s in global_variables.printStrings:
            print(f"{s}")

        time_after = time.time()

        time.sleep(global_variables.speed -
                   (time.time() % global_variables.speed))


def main():
    global_variables.init()
    global_variables.osc.reset_bundle()
    global_variables.update_commands()

    try:
        thread = threading.Thread(target=thread_func, daemon=False)
        thread.start()

        global_variables.osc.serve_server()

        while True:
            time.sleep(1000)
    except (KeyboardInterrupt, SystemExit):
        print("leaving")
        global_variables.quit = True


if __name__ == "__main__":
    main()

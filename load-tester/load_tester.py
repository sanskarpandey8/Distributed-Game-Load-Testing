import argparse
import json
import os
import random
import socket
import threading
import time

from colorama import Fore, init
from report import save_report

init(autoreset=True)

HOST = "127.0.0.1"
PORT = 8080

success = 0
failed = 0
latencies = []

lock = threading.Lock()


def load_scenario(name):
    path = os.path.join("scenarios", f"{name}.json")

    if not os.path.exists(path):
        raise FileNotFoundError(f"Scenario '{name}' not found.")

    with open(path, "r") as file:
        return json.load(file)


def virtual_player(player_id, min_actions, max_actions):
    global success
    global failed

    commands = [f"LOGIN Player{player_id}"]

    moves = [
        "MOVE UP",
        "MOVE DOWN",
        "MOVE LEFT",
        "MOVE RIGHT"
    ]

    chats = [
        "CHAT Hello",
        "CHAT Need Backup",
        "CHAT Enemy Ahead",
        "CHAT GG",
        "CHAT Follow Me"
    ]

    attacks = [
        "ATTACK Enemy",
        "ATTACK Dragon",
        "ATTACK Boss"
    ]

    total_actions = random.randint(min_actions, max_actions)

    for _ in range(total_actions):

        action = random.randint(1, 3)

        if action == 1:
            commands.append(random.choice(moves))
        elif action == 2:
            commands.append(random.choice(chats))
        else:
            commands.append(random.choice(attacks))

    try:

        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((HOST, PORT))

        for command in commands:

            start = time.perf_counter()

            sock.sendall((command + "\n").encode())

            response = sock.recv(1024).decode()

            latency = (time.perf_counter() - start) * 1000

            with lock:
                latencies.append(latency)

        sock.close()

        with lock:
            success += 1

    except Exception as e:

        print(Fore.RED + f"Player {player_id}: {e}")

        with lock:
            failed += 1


def main():

    parser = argparse.ArgumentParser(
        description="GameBench Load Tester"
    )

    parser.add_argument(
        "--clients",
        type=int,
        help="Number of virtual players"
    )

    parser.add_argument(
        "--scenario",
        type=str,
        help="Scenario name (smoke/load/stress/spike)"
    )

    parser.add_argument(
        "--ramp",
        type=float,
        default=0,
        help="Ramp-up time in seconds"
    )

    args = parser.parse_args()

    if args.scenario:

        scenario = load_scenario(args.scenario)

        num_clients = scenario["clients"]
        min_actions = scenario["min_actions"]
        max_actions = scenario["max_actions"]

    else:

        num_clients = args.clients if args.clients else 50
        min_actions = 10
        max_actions = 20

    print(Fore.CYAN + f"\nStarting {num_clients} virtual players...\n")

    start = time.perf_counter()

    threads = []

    delay = 0

    if args.ramp > 0:
        delay = args.ramp / num_clients

    for i in range(num_clients):

        thread = threading.Thread(
            target=virtual_player,
            args=(i, min_actions, max_actions)
        )

        thread.start()

        threads.append(thread)

        if delay > 0:
            time.sleep(delay)

    for thread in threads:
        thread.join()

    total_time = time.perf_counter() - start

    avg_latency = sum(latencies) / len(latencies) if latencies else 0
    max_latency = max(latencies) if latencies else 0

    success_rate = (success / num_clients) * 100 if num_clients else 0
    failure_rate = (failed / num_clients) * 100 if num_clients else 0

    requests_per_second = (
        len(latencies) / total_time if total_time > 0 else 0
    )

    print("\n========== REPORT ==========")
    print(f"Clients              : {num_clients}")
    print(f"Successful Clients   : {success}")
    print(f"Failed Clients       : {failed}")
    print(f"Success Rate         : {success_rate:.2f}%")
    print(f"Failure Rate         : {failure_rate:.2f}%")
    print(f"Total Requests       : {len(latencies)}")
    print(f"Requests / Second    : {requests_per_second:.2f}")
    print(f"Average Latency      : {avg_latency:.2f} ms")
    print(f"Maximum Latency      : {max_latency:.2f} ms")
    print(f"Execution Time       : {total_time:.2f} sec")

    save_report(
        num_clients,
        success,
        failed,
        len(latencies),
        avg_latency,
        max_latency,
        total_time
    )


if __name__ == "__main__":
    main()
import argparse
import logging
import os
import sys
import time

import numpy as np
import pandas

from BTinterface import BTInterface
from maze import Action, Maze
from score import Scoreboard, ScoreboardFake

logging.basicConfig(
    format="%(asctime)s - %(name)s - %(levelname)s - %(message)s", level=logging.INFO
)

log = logging.getLogger(__name__)

# TODO : Fill in the following information
TEAM_NAME = "YOUR_TEAM_NAME"
SERVER_URL = "http://140.112.175.18:5000/"
MAZE_FILE = "data/big_maze.csv"
BT_PORT = "COM3"

# python main.py --maze-file="data/small_maze.csv" --bt-port="21"`` --team-name="HELLO" --server-url="http://140.112.175.18:5000/" 1
# python main.py 1

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("mode", help="0: treasure-hunting, 1: self-testing", type=str)
    parser.add_argument("--maze-file", default=MAZE_FILE, help="Maze file", type=str)
    parser.add_argument("--bt-port", default=BT_PORT, help="Bluetooth port", type=str)
    parser.add_argument(
        "--team-name", default=TEAM_NAME, help="Your team name", type=str
    )
    parser.add_argument("--server-url", default=SERVER_URL, help="Server URL", type=str)

    return parser.parse_args()


def main(mode: int, bt_port: str, team_name: str, server_url: str, maze_file: str):
<<<<<<< HEAD
    #comment!!!
    #maze = Maze(maze_file)
    point = Scoreboard(team_name, server_url)
    # point = ScoreboardFake("your team name", "data/fakeUID.csv") # for local testing
=======
    maze = Maze(maze_file)
    #point = Scoreboard(team_name, server_url)
    point = ScoreboardFake("your team name", "data/fakeUID.csv") # for local testing
>>>>>>> 6f6f2fb7a5fd5ce6b3903540d191270afe12a3d1
    interface = BTInterface(port=bt_port)
    # TODO : Initialize necessary variables

    if mode == "0":
        log.info("Mode 0: For treasure-hunting")
        # TODO : for treasure-hunting, which encourages you to hunt as many scores as possible

    elif mode == "1":
        log.info("Mode 1: Self-testing mode.")
        # TODO: You can write your code to test specific function.
        start = maze.get_node_dict()[1]
        goal = maze.BFS(start)
        path = maze.BFS_2(start, goal)
        cmd = maze.actions_to_str(maze.getActions(path))
        for i in range(0, len(cmd)):
            interface.send_action(cmd[i])
        while True:
            s = interface.receive_message()
            if len(s) >= 8:
                point.add_UID(s)
                start = goal
                goal = maze.BFS(start)
                path = maze.BFS_2(start, goal)
                cmd = maze.actions_to_str(maze.getActions(path))
                interface.send_action('b')
                for i in range(1, len(cmd)):
                    interface.send_action(cmd[i])
        
        for i in range(1, 12):
            start = goal
            goal = maze.BFS(start)
            path = maze.BFS_2(start, goal)
            cmd = maze.actions_to_str(maze.getActions(path))
        

    else:
        log.error("Invalid mode")
        sys.exit(1)


if __name__ == "__main__":
    args = parse_args()
    main(**vars(args))

import csv
import logging
import math
from enum import IntEnum
from typing import List

import numpy as np
import pandas

from node import Direction, Node

log = logging.getLogger(__name__)


class Action(IntEnum):
    ADVANCE = 1
    U_TURN = 2
    TURN_RIGHT = 3
    TURN_LEFT = 4
    HALT = 5


class Maze:
    def __init__(self, filepath: str):
        # TODO : read file and implement a data structure you like
        # For example, when parsing raw_data, you may create several Node objects.
        # Then you can store these objects into self.nodes.
        # Finally, add to nd_dict by {key(index): value(corresponding node)}
        self.raw_data = pandas.read_csv(filepath).values
        self.nodes = [] # range from 0 to N-1
        self.traveled = [] # root nodes that are already traveled
        self.node_dict = dict()  # key: index, value: the correspond node
        for i in range(len(self.raw_data)):
            self.nodes.append(Node(int(self.raw_data[i][0])))
        for i in range(len(self.raw_data)):
            for j in range(1, 5):
                if not math.isnan(self.raw_data[i][j]):
                    self.nodes[i].set_successor(self.nodes[int(self.raw_data[i][j]) - 1], j)
            self.node_dict[i + 1] = self.nodes[i]

    def get_start_point(self):
        if len(self.node_dict) < 2:
            log.error("Error: the start point is not included.")
            return 0
        return self.node_dict[1]

    def get_node_dict(self):
        return self.node_dict

    def in_list(self, node: Node):
        for i in self.traveled:
            if node == i: return True
        return False

    def BFS(self, node: Node):
        # TODO : design your data structure here for your algorithm
        # Tips : return a sequence of nodes from the node to the nearest unexplored deadend
        self.traveled.append(node)
        Q = [node]
        D = [0 for i in range(0, len(self.nodes))]
        P = [0 for i in range(0, len(self.nodes))]
        for succ in Q[0].get_successors():
            if(D[int(succ[0].get_index()) - 1] == 0):
                Q.append(succ[0])
                D[int(succ[0].get_index()) - 1] = D[int(Q[0].get_index()) - 1] + 1
                P[int(succ[0].get_index()) - 1] = Q[0]
            Q.remove(Q[0])
        while len(Q) != 0:
            if(len(Q[0].get_successors()) == 1):
                break
            else:
                for succ in Q[0].get_successors():
                    if D[int(succ[0].get_index()) - 1] == 0 and not self.in_list(succ[0]):
                        Q.append(succ[0])
                        D[int(succ[0].get_index()) - 1] = D[int(Q[0].get_index()) - 1] + 1
                        P[int(succ[0].get_index()) - 1] = Q[0]
                Q.remove(Q[0])
        return Q[0]

    def BFS_2(self, node_from: Node, node_to: Node):
        # TODO : similar to BFS but with fixed start point and end point
        # Tips : return a sequence of nodes of the shortest path
        Q = [node_from]
        D = [0 for i in range(0, len(self.nodes))]
        P = [0 for i in range(0, len(self.nodes))]
        while len(Q) != 0:
            for succ in Q[0].get_successors():
                if(D[int(succ[0].get_index()) - 1] == 0):
                    Q.append(succ[0])
                    D[int(succ[0].get_index()) - 1] = D[int(Q[0].get_index()) - 1] + 1
                    P[int(succ[0].get_index()) - 1] = Q[0]
            Q.remove(Q[0]) 
        sequ = [node_to]
        while sequ[0] != node_from:
            sequ.insert(0, P[int(sequ[0].get_index()) - 1])
        return sequ

    def getAction(self, car_dir, node_from: Node, node_to: Node):
        # TODO : get the car action
        # Tips : return an action and the next direction of the car if the node_to is the Successor of node_to
        # If not, print error message and return 0
        goal_dir = node_from.get_direction(node_to)
        if goal_dir == 1: #NORTH
            if car_dir == 1: return Action.ADVANCE
            elif car_dir == 2: return Action.U_TURN
            elif car_dir == 3: return Action.TURN_RIGHT
            elif car_dir == 4: return Action.TURN_LEFT
        elif goal_dir == 2: #SOUTH
            if car_dir == 1: return Action.U_TURN
            elif car_dir == 2: return Action.ADVANCE
            elif car_dir == 3: return Action.TURN_LEFT
            elif car_dir == 4: return Action.TURN_RIGHT
        elif goal_dir == 3: #WEST
            if car_dir == 1: return Action.TURN_LEFT
            elif car_dir == 2: return Action.TURN_RIGHT
            elif car_dir == 3: return Action.ADVANCE
            elif car_dir == 4: return Action.U_TURN
        elif goal_dir == 4: #EAST
            if car_dir == 1: return Action.TURN_RIGHT
            elif car_dir == 2: return Action.TURN_LEFT
            elif car_dir == 3: return Action.U_TURN
            elif car_dir == 4: return Action.ADVANCE
        else: return 0

    def getActions(self, nodes: List[Node]):
        # TODO : given a sequence of nodes, return the corresponding action sequence
        # Tips : iterate through the nodes and use getAction() in each iteration
        car_dir = nodes[0].get_direction(nodes[1])
        action = [Action.ADVANCE]
        for i in range(2, len(nodes)):
            if(self.getAction(car_dir, nodes[i - 1], nodes[i]) != 0):
                action.append(self.getAction(car_dir, nodes[i - 1], nodes[i]))
                car_dir = nodes[i - 1].get_direction(nodes[i])
        return action

    def actions_to_str(self, actions):
        # cmds should be a string sequence like "fbrl....", use it as the input of BFS checklist #1
        cmd = "fbrls"
        cmds = ""
        for action in actions:
            cmds += cmd[action - 1]
        log.info(cmds)
        return cmds

    """
    def strategy(self, node: Node):
        return self.BFS(node)

    def strategy_2(self, node_from: Node, node_to: Node):
        return self.BFS_2(node_from, node_to)
    """

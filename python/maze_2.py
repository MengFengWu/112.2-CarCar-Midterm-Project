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
    def __init__(self, filepath: str, start = 6, width = 8, height = 6):
        # TODO : read file and implement a data structure you like
        # For example, when parsing raw_data, you may create several Node objects.
        # Then you can store these objects into self.nodes.
        # Finally, add to nd_dict by {key(index): value(corresponding node)}
        self.raw_data = pandas.read_csv(filepath).values
        self.nodes = [] # range from 0 to N-1
        self.traveled = [] # root nodes that are already traveled
        self.start = start
        self.width = width
        self.height = height
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
    
    def calcScore(self, goal: int):
        return int(abs(goal - self.start) / self.height) + abs(goal - self.start) % self.height

    def BFS(self, node: Node):
        # TODO : design your data structure here for your algorithm
        # Tips : return a sequence of nodes from the node to the nearest unexplored deadend
        return self.strategy(node)

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
        else: return Action.ADVANCE

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

    def strategy(self, node: Node):
        Q = [node]
        D = [0 for i in range(0, len(self.nodes))]
        P = [0 for i in range(0, len(self.nodes))]
        F = [0 for i in range(0, len(self.nodes))] #simulated car direction
        S = [len(self.node_dict[i + 1].get_successors()) for i in range(0, len(self.nodes))] #secessors
        Root = []
        weight = [1, 2, 2, 4, 16384]

        self.traveled.append(node)
        while len(Q) != 0:
            if S[int(Q[0].get_index()) - 1] > 0:
                #print("now testing: " + str(Q[0].index))
                S[int(Q[0].get_index()) - 1] -= 1
                for succ in Q[0].get_successors():
                    if len(succ[0].get_successors()) == 1 and D[int(succ[0].get_index()) - 1] == 0 and not self.in_list(succ[0]):
                        Root.append(succ[0])
                    Q.append(succ[0])
                    testDir = Q[0].get_direction(succ[0])
                    if D[int(Q[0].get_index()) - 1] + weight[int(self.getAction(testDir, Q[0], succ[0]))] < D[int(succ[0].get_index()) - 1] or D[int(succ[0].get_index()) - 1] == 0:
                        F[int(succ[0].get_index()) - 1] = testDir
                        D[int(succ[0].get_index()) - 1] = D[int(Q[0].get_index()) - 1] + weight[self.getAction(testDir, Q[0], succ[0])]
                    P[int(succ[0].get_index()) - 1] = Q[0]
            Q.remove(Q[0])
        if len(Root) != 0: 
            bestRoot = Root[0]
            bestDist = self.calcScore(Root[0].get_index()) / D[int(Root[0].get_index()) - 1]
            #print("add " + str(Root[0].get_index()) + " with profit: " + str(self.calcScore(Root[0].get_index()) / D[int(Root[0].get_index()) - 1]))
            if len(Root) > 1:
                for i in range(1, len(Root)):
                    if(self.calcScore(Root[i].get_index()) / D[int(Root[i].get_index()) - 1] > bestDist):
                        bestRoot = Root[i]
                        bestDist = Root[i].get_index() / D[int(Root[i].get_index()) - 1]
                    #print("add " + str(Root[i].get_index()) + " with profit: " + str(self.calcScore(Root[i].get_index()) / D[int(Root[i].get_index()) - 1]))
            #print("final choose " + str(bestRoot.index) + " with profit: " + str(bestDist))
            return bestRoot
        else: return node

    """
    def strategy_2(self, node_from: Node, node_to: Node):
        return self.BFS_2(node_from, node_to)
    """

# import the things you need here
import enum
import math
from typing import Literal, Tuple


class CommandType(enum.Enum):
    FIRE = "fire"
    SHIELD = "shield"
    MOVE = "move"


type Command = Tuple[Literal["fire"] | Literal["shield"] | Literal["move"], int]
type Position = Tuple[int, int]


class Tank_AI(object):
    def __init__(self):
        # required attributes
        self.name = "jeedus"  # your bot name here
        self.house = "Yost"  # your house. Use "Hudson", "Yost", "Witherell", "Lynn",
        # "Skaggs", or "Unaffiliated"
        # optional attributes: your class variables can go here
        self.my_angle = 0
        self.fire_countdown = 0

    def make_move(self, location, tank_list, bullet_list):
        # pick a new angle every so often
        # self.my_angle = random.choice([90, 180, 270, 0])
        # choose command to return
        command = ("move", self.my_angle)

        if self.fire_countdown == 0:
            target_x = tank_list[0][2]
            target_y = -tank_list[0][3]

            target_x -= location[0]
            target_y += location[1]

            angle = math.atan2(target_y, target_x)

            if angle < 0:
                angle += math.pi * 2

            command = ("fire", math.degrees(angle))

        return command

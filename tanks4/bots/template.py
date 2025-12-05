# import the things you need here
import random


class Tank_AI(object):
    def __init__(self):
        # required attributes
        self.name = "HAL9000"  # your bot name here
        self.house = "Yost"  # your house. Use "Hudson", "Yost", "Witherell", "Lynn",
        # "Skaggs", or "Unaffiliated"
        # optional attributes: your class variables can go here
        self.my_angle = 0
        self.fire_countdown = 0

    def make_move(self, your_location, tank_list, bullet_list):
        command = ("move", self.my_angle)

        # pick a new angle every so often
        if random.randint(0, 100) == 0:
            self.my_angle = random.choice([90, 180, 270, 0])
            # choose command to return
            if random.randint(0, 10) == 0:
                command = ("fire", random.randint(0, 359))

        return command

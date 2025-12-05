# import the things you need here
import math
import random
import sys
from pprint import pp
from typing import Literal, NamedTuple, Tuple

type CommandType = Literal["fire"] | Literal["shield"] | Literal["move"]


type Command = Tuple[CommandType, float] | None
type Position = Tuple[int, int]
# type Tank = Tuple[str, str, int, int, int, int]


class Point(NamedTuple):
    x: float
    y: float

    @staticmethod
    def get_dist_sq(a, b) -> float:
        return (a.x - b.x) ** 2 + (a.y - b.y) ** 2

    def __add__(self, b):
        return Point(self.x + b.x, self.y + b.y)

    def __sub__(self, b):
        return Point(self.x - b.x, self.y - b.y)

    def __neg__(self):
        return Point(-self.x, -self.y)

    def __pos__(self):
        return Point(+self.x, +self.y)


class Line(NamedTuple):
    """A line in parametric form.
    If this is a line segment, pos should be a starting point, and dir should be the difference
    between the end and start points
    """

    pos: Point
    """Position"""

    dir: Point
    """Direction"""

    @staticmethod
    def from_points(point1: Point, point2: Point):
        return Line(point1, point2 - point1)

    def intersects_with(self, line2) -> bool:
        determinant = line2.dir.x * self.dir.y - self.dir.x * line2.dir.y

        if math.isclose(determinant, 0):
            return False

        s = (1 / determinant) * (
            (self.pos.x - line2.pos.x) * self.dir.y
            - (self.pos.y - line2.pos.y) * self.dir.x
        )
        t = (1 / determinant) * (
            (self.pos.x - line2.pos.x) * line2.dir.y
            - (self.pos.y - line2.pos.y) * line2.dir.x
        )

        if 0 <= s <= 1 and 0 <= t <= 1:
            return True

        return False


BARRIERS: Tuple[Tuple[Point, Point], ...] = (
    (
        Point(200, 300),
        Point(230, 700),
    ),
    (
        Point(800, 300),
        Point(770, 700),
    ),
    (
        Point(400, 200),
        Point(600, 225),
    ),
    (
        Point(400, 775),
        Point(600, 800),
    ),
)


def rect_to_lines(corner1: Point, corner2: Point):
    """
    Convert a rect described by two corners into two lines
    """
    corner3 = Point(corner1.x, corner2.y)
    corner4 = Point(corner2.x, corner1.y)
    line1 = Line.from_points(corner1, corner2)
    line2 = Line.from_points(corner3, corner4)

    return (line1, line2)


BARRIERS_LINED: Tuple[Tuple[Line, Line], ...] = tuple(
    [rect_to_lines(*barrier) for barrier in BARRIERS]
)

pp(BARRIERS)
print()
pp(BARRIERS_LINED)


class Tank(NamedTuple):
    name: str
    house: str
    pos: Point
    health: int
    score: int

    @staticmethod
    def from_flat(
        name: str,
        house: str,
        pos_x: float,
        pos_y: float,
        health: int,
        score: int,
    ):
        return Tank(name, house, Point(pos_x, pos_y), health, score)


class Tank_AI(object):
    name: str = "ohmyjeed"  # your bot name here
    house: str = "Yost"  # your house. Use "Hudson", "Yost", "Witherell", "Lynn",
    my_angle: float
    fire_countdown: int

    def __init__(self):
        self.my_angle = 0
        self.fire_countdown = 0

    def select_target_tank(
        self, location: Point, tank_list: Tuple[Tank, ...]
    ) -> Tank | None:
        # search for target
        target = None

        min_dist = sys.maxsize
        for tank in tank_list:
            # skip self
            if tank.name == self.name:
                continue

            # skip dead tanks
            if tank.health == 0:
                continue

            line_to = Line.from_points(location, tank.pos)
            intersects = False
            for barrier in BARRIERS_LINED:
                for line in barrier:
                    intersects = intersects or line.intersects_with(line_to)

            print(f"{tank.name} {intersects} {line_to}")
            if intersects:
                continue

            dist = Point.get_dist_sq(tank.pos, location)
            if dist < min_dist:
                min_dist = dist
                target = tank

        return target

    def make_move(self, location, tank_list, bullet_list: Tuple[Position]) -> Command:
        # just making these proper...
        location = Point._make(location)
        tank_list = tuple([Tank.from_flat(*tank) for tank in tank_list])

        self.fire_countdown = max(self.fire_countdown - 1, 0)

        # pick a new angle every so often
        if random.randint(0, 100) == 0:
            # self.my_angle = random.randint(0, 359)
            self.my_angle = random.choice([90, 180, 270, 0])

        # choose command to return
        command: Command = ("move", self.my_angle)

        target = self.select_target_tank(location, tank_list)
        if target is None:
            return command

        if self.fire_countdown <= 0:
            self.fire_countdown = 15
            target_x = target.pos.x
            target_y = -target.pos.y

            target_x -= location.x
            target_y += location.y

            angle = math.atan2(target_y, target_x)

            if angle < 0:
                angle += math.pi * 2

            command = ("fire", math.degrees(angle))

        return command

# Building
Run `make` to build.

# Usage
Run with `make run` or run executable (in build/).

Board is generated randomly with 300 live cells, 'X' is live cell, '-' is dead.
The board is shown and you will be prompted for a command. Enter 'help' or '?' for a list of
commands. Commands are detected by first letter, 'help', 'how', and 'hello?' all print the help, for
example. There is a limit to how long a command may be, see `help` for the number.

## Commands
| Command   | Parameters      | Result                                                                            |
|-----------|-----------------|-----------------------------------------------------------------------------------|
| [h]elp    | None            | Print the help page.                                                              |
| Enter     | None            | Show next generation.                                                             |
| r         | `Generations`   | Run `Generations` generations.                                                    |
| l         | `Path`          | Load board from file at `Path` (see example boards)                               |
| s         | `Seed`, `Cells` | Set the random seed to `Seed` and reinitialize the board with `Cells` live cells. |
| [d]isplay | None            | Show current generation.                                                          |
| [q]uit    | None            | Exit the game.                                                                    |

# Disclosure
Examples taken from https://conwaylife.com/wiki

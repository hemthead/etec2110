# What is this?

Well, in my ETEC2110 Systems Programming class, I can get bonus points on the final exam by making a
'Tanks 4' AI. 'Tanks 4' is a seemingly in-house game, so I can't exactly give away the source, but
it's written in python, and if you have it you'll have the `tanks_final.cpython-3XX.pyc` files. Bit
of a problem, though, whoever made the game only ever intended for it to be ran on windows (and I
use Linux!); as such, there's an issue where it expects paths to use `\` rather than `/`. This issue
manifests on linux as an import error (`Import error: tank=bots/<bot_name> error:No module named
'bots/<bot_name>'`, where `<bot_name>` is the bot's name), and the game fails to load any AI.

# Solution!

With an issue as simple as this, you'd think we could do a very naive substitution of `\` with `/`
somewhere... and you'd be right! If you disassemble the bytecode (with a tool like
[pycdas](https://github.com/zrax/pycdc)) and look around, you'll find that our bot's path is loaded
into a variable called `bot_file`, and then `replace` is called with the values `'\\'` and `.`, and
the result is put into `import_path` (i.e. the source would've said `import_path =
bot_file.replace('\\', '.')`). So, if we change that `'\\'` to `'/'` it'll work on linux!

If you look further into the disassembly, you'll find that there are a couple other constants nearby
(in particular, I saw a `'.py'`) that we can use to find where the `'\\'` constant is in the `.pyc`
file (ex. it's at 109:355 in the 310 file) (and, interestingly, it seems that python likes to
preinterpret the `\\` to `\`, which is extremely lucky for us) and replace it with the value for
`'/'`. Do that for all three versions and you've got everything you need to make some patches!

# Patching

Patches (`.delta` files) were generated with [rdiff](https://librsync.github.io/page_rdiff.html).
You can do things manually by running `$ rdiff <.pyc file> <.pyc.delta file> <output file>` for each
file you want to patch. If you prefer automation (and I do!):

- unzip this `.zip` into your 'Tanks 4' directory (the provided `.pyc.delta` files should end up in
  the same directory as your `.pyc` files)
- run `$ make` or `$ make patch` to generate patched versions of the files (`.pyc.linux`), as well
  as a launcher for linux (`tank_launcher_linux.py`)

For convenience, you can run `$ make run` to run the `tank_launcher_linux.py` script.

# Security

You should probably give the makefile a once-over before you run anything, it _is_ a random script
from the internet, after all. You might also consider running `$ diff -a <.pyc file> <.pyc.linux
file>` to verify that I only changed what I said I would.

You shouldn't be worried about your losing original `.pyc` files, or anything unrelated. rdiff
doesn't overwrite anything, and neither do I. After patching, you'll be left with everything you
already had, as well as the (now patched) `.pyc.linux` files, and a `tank_launcher_linux.py` script.

# Author, License, Credit

Author: <ReallyJohnReed@Gmail.com> (John Reed) @hemthead
License: MIT, go crazy

Notice: Tanks is not my creation, not sure who made it.

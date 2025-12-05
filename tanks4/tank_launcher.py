import subprocess
import sys

version = sys.version.strip()[0:4]

print(f"Tanks4 - Launching version: {version}")
if version == "3.10":
    subprocess.run(["python", "tanks_final.cpython-310.pyc"])
elif version == "3.13":
    subprocess.run(["python", "tanks_final.cpython-313.pyc"])
elif version == "3.14":
    subprocess.run(["python", "tanks_final.cpython-314.pyc"])
input("Tanks 2025 Done - Enter to Exit.")

import os


def display():
    for _, _, files in os.walk("../gapbs/benchmark/out"):
        for file in files:
            print(file)
            with open(os.path.join("../gapbs/benchmark/out", file)) as f:
                print(f.readlines()[-1].strip())


cmd = [
    "LOGV=1",
    "/usr/bin/numactl -m 1",
    "../cmake-build-debug/CXLMemSim",
    "-t",
    "../gapbs/run.sh",
    "-i",
    "100",
]
cmd = " ".join(cmd)
print(cmd)
os.system(cmd)
display()

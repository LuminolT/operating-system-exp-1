from collections import Counter
from random import randint

m = Counter()

initial_status = [True, False, False, False, False, False]

def step(stats: list[bool], episode: list(int)) -> int:
    nexts = []
    if episode[-1] == 0:
        stats[0] = False
        ch = [1, 3][randint(0, 1)]
        stats[ch] = True
    if episode[-1] == 1:
        ...

def sample(stats: list[bool]) -> list[int]:
    episode = [0]
    res = []
    for i in range(5):
        tmp = step(stats, episode)
        if tmp in [1,2,3]:
            res.append(tmp)
        episode.append(tmp)
    return res
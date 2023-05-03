import random

N = 10000001
acertos = 0

for i in range(N):
    x = random.uniform(0.0, 1.0)
    y = random.uniform(0.0, 1.0)

    if x**2 + y**2 <= 1.0:
        acertos+=1

print(4*acertos/N)



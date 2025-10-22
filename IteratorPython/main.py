import numpy as np;

data = list(np.random.normal(15, 4.5, 1_000_000))

step1 = filter(lambda t: t >= 25, data)
step2 = map(lambda t: t * 0.95, step1)
print(step2) # lazy object

# consommation
for t, _ in zip(step2, range(100)):
    print(t)
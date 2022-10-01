from matplotlib import pyplot as plt

N = 500-1

p1 = []
n1 = []
for i in range(N):
    temp_n, temp_p = input().split()
    p1.append(float(temp_p))
    n1.append(int(temp_n))

p2 = []
n2 = []
for i in range(N):
    temp_n, temp_p = input().split()
    p2.append(float(temp_p))
    n2.append(int(temp_n))

p_th = []
for i in range(N):
    p_th.append(10/101)

plt.plot(n1, p1)
plt.plot(n2, p2)
plt.plot(n1, p_th)
plt.legend(['set', 'segment', 'theory'])

plt. show()

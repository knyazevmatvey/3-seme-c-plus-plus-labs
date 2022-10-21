from matplotlib import pyplot as plt

N = 4000-1
 
p1 = []
n1 = []
for i in range(N):
    temp_n, temp_p = input().split()
    p1.append(float(temp_p))
    n1.append(int(temp_n))

p_th = []
for i in range(N):
    p_th.append(10/158)

plt.plot(n1, p1)
plt.plot(n1, p_th)
plt.legend(['set', 'segment', 'theory'])

plt. show()

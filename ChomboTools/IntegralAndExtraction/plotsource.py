# A simple python script to plot the GW
# signals over time, for a chosen mode

import numpy as np;
import matplotlib.pyplot as plt;

# output data from running merger
M = 1.0
mu = 0.5
v = 0.1
r = 100
symmetry = 4
data1 = np.loadtxt("IntegralData.dat")
data2 = np.loadtxt("IntegralData100.dat")

# make the plot
fig = plt.figure()

labelstring = "r=100"
timedata = data1[:,0]
Fdata = symmetry * data1[:,1] * 0.1 * 0.1
plt.plot(timedata, Fdata, '-', lw = 1.0, label=labelstring)

dina = np.ones_like(timedata)*1.2
plt.plot(timedata, dina, '--', lw = 1.0, label=labelstring)

# make the plot look nice
plt.xlabel("time")
plt.ylabel("Force")
#plt.xlim(0, 1000)
#plt.ylim(1e-1, 1e2)
plt.legend()

# save as png image
filename = "FvsT" + "_mu" + str(mu) + ".png"
plt.savefig(filename)
# A simple python script to plot the GW
# signals over time, for a chosen mode

import numpy as np;
import matplotlib.pyplot as plt;

# output data from running merger
M = 1.0
mu = 0.5
v = 0.1
r = 500
symmetry = 4

# make the plot
fig = plt.figure()

data = np.loadtxt("Run3/IntegralData.dat")
labelstring = "r_max = 500, v=0.3"
timedata = data[:,0]
Fdata = symmetry * data[:,1]
plt.plot(timedata, Fdata, '-', lw = 1.0, label=labelstring)

#data = np.loadtxt("Run4/IntegralData.dat")
#labelstring = "r_max = 500, v=0.4"
#timedata = data[:,0]
#Fdata = symmetry * data[:,1]
#plt.plot(timedata, Fdata, '-', lw = 1.0, label=labelstring)

#data = np.loadtxt("Run5/IntegralData.dat")
#labelstring = "r_max = 500, v=0.5"
#timedata = data[:,0]
#Fdata = symmetry * data[:,1]
#plt.plot(timedata, Fdata, '-', lw = 1.0, label=labelstring)

data = np.loadtxt("Run6/IntegralData.dat")
labelstring = "r_max = 500, v=0.6"
timedata = data[:,0]
Fdata = symmetry * data[:,1]
plt.plot(timedata, Fdata, '-', lw = 1.0, label=labelstring)

# make the plot look nice
plt.xlabel("time")
plt.ylabel("Force")
#plt.xlim(0, 1000)
#plt.ylim(1e-1, 1e2)
plt.legend(loc=4)
plt.grid()

# save as png image
filename = "FvsT" + "_mu" + str(mu) + ".png"
plt.savefig(filename)
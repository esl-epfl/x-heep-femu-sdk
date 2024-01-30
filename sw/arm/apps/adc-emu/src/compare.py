#!/usr/bin/env python3

import io, os, sys
import numpy as np
import matplotlib.pyplot as plt

from processes import *

BITS_N = 16
BITS_LC = 8

processes = []
initial_samples = -1

def add_step(series, alpha=1):
    global initial_samples
    initial_samples = len(series.time) if initial_samples == -1 else initial_samples
    print(f'Samples \t {len(series.time):0.1e} \t {len(series.time)*100/initial_samples:2.0f}% \t {series}')
    ax.plot(series.time, series.data, alpha = alpha )
    processes.append(series)
    series.dump()



filename, time_s = '../in/Epiphone', 2

EXTENSION = '.txt'
figure, ax = plt.subplots(figsize=(10, 8))


y = []

with open(filename+EXTENSION) as f:
    y = f.readlines()

data = np.asarray([int(np.round(float(f))) for f in y])

s_n = len(data)
T_s = time_s/s_n
f_Hz = s_n/time_s
time = np.arange(0,time_s,T_s)

'''```````````````````````````````````````
        TAKE ONLY A WINDOW

```````````````````````````````````````'''

if 1:
    FROM_S  = 1.84
    TO_S    = 2

    start   = int(FROM_S*f_Hz)
    end     = int(TO_S*f_Hz)
    time_s  = TO_S-FROM_S
    data    = data[start:end]
    time    = time[start:end]

'''```````````````````````````````````````
        DOWNSAMPLE

```````````````````````````````````````'''

print(f"Initial sampling frequency:\t{f_Hz:.0f} Hz")

if 0:
    f_Hz_new    = 200
    skip        = int( f_Hz/ f_Hz_new )
    f_Hz_new    = f_Hz/skip
    data        = data[::skip]
    time        = time[::skip]

    print(f"New samping frequency:\t{f_Hz_new:.0f} Hz (/{skip})")
    f_Hz = f_Hz_new


'''```````````````````````````````````````
        RAW SIGNAL

```````````````````````````````````````'''

''' The raw signal '''
raw = Timeseries('Raw')
raw.data    = data
raw.time    = time
raw.f_Hz    = f_Hz
# add_step(raw, 0.3)

''' Normalize the data '''
raw = norm(raw, BITS_N)
# add_step(raw, 0.3)

'''```````````````````````````````````````
        MEAN SUBTRACTION

```````````````````````````````````````'''
''' Subtract the mean with average function '''
meand = mean_sub(raw, 100)
# add_step(meand, 0.3)

''' Normalize the data '''
meand = norm(meand, BITS_N)
# add_step(meand, 0)

filtered = meand


''' Normalize the data '''
filtered = bpf_butter(raw, 100, 1500, order=4)
filtered = norm(filtered, BITS_N)
add_step(filtered, 1)


'''```````````````````````````````````````
        ANALOG LEVEL CROSSING

```````````````````````````````````````'''

if 1:
    ''' Oversample to simulate analog signal '''
    analog = filtered
    analog = oversample(filtered, 50)
    add_step(analog, 0.5)



    sdr_lc = []

    for lvl_width in 2**np.asarray([ 8, 9, 10, 11, 12 ]):

        lvls = lvls_unif(lvl_width, BITS_N)
        for method in [ lcadc_naive ]:

            lc = method( analog, lvls )

            lcrt = lcadc_reconstruct_time(lc, height=lvl_width/2)
            # add_step(lcrt,0.5)

            offset = 2 if method == lcadc_fil else 0
            lcr = lcadc_reconstruct(lc, lvls, offset=offset)
            add_step(lcr, 0)

            sdr = compute_sdr( analog.data, lcr.data, interpolate=True )
            sdr_lc.append(sdr)

'''```````````````````````````````````````
        Fixed Rate ADC

```````````````````````````````````````'''

''' Quantize the data '''

if 1:
    sdr_fr = []

    for bits in list(range(6,17)):
        qnt = quant(analog, bits)
        # add_step(qnt, 0.3)

        sdr_fr_b = []

        for freq_Hz in list(range(200, 6000, 200)):

            initial_f = qnt.f_Hz
            # print(f"Initial sampling frequency:\t{initial_f:.0f} Hz")

            skip        = int( initial_f/ freq_Hz )
            freq_Hz    = initial_f/skip
            # print(f"New samping frequency:\t{freq_Hz} Hz (/{skip})")

            fradc = Timeseries( qnt.name + f" frADC({freq_Hz:1.0f})" )

            fradc.data = qnt.data[::skip]

            fradc.time = qnt.time[::skip]
            fradc.f_Hz = freq_Hz

            add_step(fradc, 1)

            sdr = compute_sdr( analog.data, fradc.data, interpolate=True )
            sdr_fr_b.append(sdr)
        sdr_fr.append(sdr_fr_b)









    # print(sdr_lc)
    # for s in sdr_fr:
    #     a = [f"{r:0.2f}" for r in s]
    #     print(a)



# ax.set_yticks(lvls)
plt.legend(processes, loc='lower left')
plt.xlabel("Time (s)")
plt.ylabel("Amplitude (arbitrary units)")
plt.title(f"Signal from {filename}")
# [ plt.axhline(l, color='k', linestyle=':', alpha=0.2 ) for l in lvls ]


plt.show()




# COMPARE TO THE SDR OF A HPF SIGNAL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# Check Silvios paper on LC
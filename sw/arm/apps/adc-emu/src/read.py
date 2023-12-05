#!/usr/bin/env python3

import io, os, sys
import numpy as np
import matplotlib.pyplot as plt

from processes import *

BITS_N = 8
BITS_LC = 8

# plt.ion()
# plt.show()

processes = []


EPIPHONE    = '../in/Epiphone'
BIOPAC      = '../in/Biopac'
JACKSON     = '../in/Jackson'


def add_step(series, alpha=1):
    print(f'Samples \t {len(series.time)} \t {series}')
    ax.plot(series.time, series.data, alpha = alpha )
    processes.append(series)
    series.dump()


if len(sys.argv) == 1:
    # No pts was provided. Run a demo
    demo = 1
    pts = 0
else:
    demo = 0
    pts = 1


if demo:
    filename, time_s = JACKSON, 2
    filename, time_s = EPIPHONE, 60
    filename, time_s = BIOPAC, 60

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

    if 0:
        FROM_S  = 57
        TO_S    = 60

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
    # add_step(raw, 0.3) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    ''' Normalize the data '''
    raw = norm(raw, BITS_N)
    add_step(raw, 0.3) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    '''```````````````````````````````````````
            MEAN SUBTRACTION

    ```````````````````````````````````````'''

    ''' Subtract the mean with average function '''
    meand = mean_sub(raw, 100)
    # add_step(meand, 0.3) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    ''' Subtract pseudo mean 2-steps '''
    if filename == EPIPHONE:    win = 6
    if filename == BIOPAC:      win = 6
    if filename == JACKSON:     win = 8

    meand = pseudo_mean(raw, win)
    meand.data = [ d - m for d, m in zip(raw.data,meand.data)]
    meand.name = meand.name + ".sub"
    # add_step(meand, 0.3) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    ''' Normalize the data '''
    meand = norm(meand, BITS_N)
    add_step(meand, 0.3) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    '''```````````````````````````````````````
            FILTERING

    ```````````````````````````````````````'''

    ''' LPF by pMean '''
    if filename == EPIPHONE:    win = 6
    if filename == BIOPAC:      win = 6
    if filename == JACKSON:     win = 3

    lpfd = pseudo_mean(meand, win)
    lpfd.name = meand.name + ".LPF" + f".{win}"
    # add_step(lpfd, 1) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    if filename == JACKSON:     win += 1
    if filename == EPIPHONE:    win += 1
    if filename == BIOPAC:      win += 1

    base = pseudo_mean(lpfd, win)
    base.name = base.name + f".{win}"
    # add_step(base, 1) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    lpfd.data = [ f - d for f,d in zip(lpfd.data, base.data) ]
    # add_step(lpfd, 1) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    ''' Through a DIGITAL LPF '''
    # lpfd = lpf_butter(pm2s, 100, 2 )
    # lpfd = pm2s
    # add_step(lpfd, 0.3) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    '''```````````````````````````````````````
            SUBSAMPLING

    ```````````````````````````````````````'''

    ''' Normalize the data for level crossing'''
    lpfd = norm(lpfd, BITS_LC)
    # add_step(lpfd, 0.3) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    ''' Oversample to simulate analog signal '''
    analog = lpfd
    analog = oversample(lpfd, 20)
    # add_step(analog, 1) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    ''' Level-crosing with debouncing'''
    if filename == EPIPHONE :lvls = lvls_pwr2()
    if filename == BIOPAC :lvls = lvls_pwr2()
    if filename == JACKSON : lvls = lvls_uniform()

    lc = lcadc_fil( analog, lvls )
    lcrt = lcadc_reconstruct_time(lc)
    add_step(lcrt,1)    #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    lcr = lcadc_reconstruct(lc, lvls)
    # add_step(lcr, 0.7) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    ''' Through the PAS sub-sampler '''
    e = 1e3 # Biopac works better with 1e4
    pasd = pas(analog, e)
    # add_step(pasd, 1) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    ''' Mean the LC '''
    lcr = pseudo_mean(lcr, 2)
    # add_step(lcr, 1) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    ''' PAS the LCd '''
    if filename == BIOPAC:      e = 1000
    if filename == EPIPHONE:    e = 5
    if filename == JACKSON:     e = 100
    pasd = pas(lcr, e)
    # add_step(pasd, 1) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    '''```````````````````````````````````````
            SPIKE ENHANCEMENT

    ```````````````````````````````````````'''
    slope = 50e-3

    ''' AS2O on PAS'd '''
    if filename == JACKSON:     win = 4
    if filename == EPIPHONE:    win = 1
    if filename == BIOPAC:      win = 1

    as2od = as2o(pasd, win)
    as2o_nd = norm(as2od, BITS_N)
    # add_step(as2o_nd, 1) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    as2od = needle(pasd, win)
    as2o_nd = norm(as2od, BITS_N)
    # add_step(as2o_nd, 1) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    print(f"COMPRESSION: {len(as2od.data)*100/len(raw.data):.1f}%")

    '''```````````````````````````````````````
            ENTIRE SPIKING ACTIVITY

    ```````````````````````````````````````'''

    ''' Density of LC samples '''
    # esa = get_density(lc, 0.1)
    # esa = norm(esa, BITS_LC)
    # add_step(esa) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    ''' ASO on LC samples '''
    # lcaso = lc_aso(lc, lvls)
    # lcaso = norm(lcaso, BITS_LC)
    # add_step(lcaso) #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    '''```````````````````````````````````````
            SPIKE DETECTION

    ```````````````````````````````````````'''
    counts = []
    if 1:
        try:
            ''' Ground truth '''
            SUFIX = '_spk'
            spike_file = filename + SUFIX + EXTENSION

            with open(spike_file) as f:
                g_truth = f.readlines()

            g_truth = [float(f) for f in g_truth]
            [ plt.axvline(l, color='g', linestyle=':', alpha=0.5, linewidth=2  ) for l in g_truth ]


            if 1:
                ''' Detection thorugh thresholding'''
                lvl_offset = 1
                mid = first_level(lvls)
                th = lvls[mid+lvl_offset]

                spk = spike_det_dt( as2o_nd, th )
                [ plt.axvline(l, color='r', linestyle=':', alpha=0.5  ) for l in spk.time ]


                ''' Detection through LC counts'''

                dt_is = []
                senss_d = []
                senss = []
                specs_d = []
                specs = []
                foms_d = []
                foms = []

                # These were the best results for one experiment
                counts = [5]
                dt_is = [300e-6]
                # counts = np.arange( 2,20, 1)
                # dt_is = np.arange( 10e-6, 50e-6, 5e-6)

                for count in counts:
                    senss_d = []
                    specs_d = []
                    foms_d = []
                    for dt_i in dt_is:

                        spk = spike_det_lc( lcrt, dt_i, count )
                        sens = 0
                        spec = 0
                        if len(spk.time) != 0:
                            '''comparison'''
                            det = 0
                            for gt in g_truth:
                                for ds in spk.time:
                                    if np.abs(ds-gt) < dt_i*count*20:
                                        det += 1
                                        break

                            total = len(g_truth)
                            sens = det/total

                            det = 0
                            for ds in spk.time:
                                for gt in g_truth:
                                    if np.abs(ds-gt) < dt_i*count*20:
                                        det += 1
                                        break
                            fa = len(spk.time) - det
                            spec = 1- fa/len(spk.time)
                            fom = sens*spec
                        senss_d.append(sens)
                        specs_d.append(spec)
                        foms_d.append(fom)
                        print(f"{count}\tchanges in {dt_i*1e6:.2f}us\t=> SENSITIVITY: {sens:.2f}\t||\tSPECIFICITY: {spec:.2f}\t||\t FOM: {fom:.2f}")
                    senss.append(senss_d)
                    specs.append(specs_d)
                    foms.append(foms_d)

                senss = np.asarray(senss)
                specs = np.asarray(specs)
                foms = np.asarray(foms)

                [ plt.axvline(l, color='r', linestyle=':', alpha=0.5  ) for l in spk.time ]

        except FileNotFoundError:
            pass

    '''```````````````````````````````````````
            PLOTTING

    ```````````````````````````````````````'''

    if 0:
        if filename == BIOPAC:
            ax.set_xlim(50, 60)
        if filename == EPIPHONE:
            ax.set_xlim(57, 59)
        if filename == JACKSON:
            ax.set_xlim(0.75,0.775)
            # ax.set_xlim(0, 0.001)

    ax.set_yticks(lvls)
    # ax.set_ylim(-32,32)
    # ax.set_ylim(min(lvls), max(lvls))
    plt.legend(processes)
    plt.xlabel("Time (s)")
    plt.ylabel("Amplitude (God knows)")
    plt.title(f"Signal from {filename}")
    [ plt.axhline(l, color='k', linestyle=':', alpha=0.2 ) for l in lvls ]

    if len( counts )  > 1:
        import plotly.graph_objects as go
        from plotly.subplots import make_subplots
        from typing import Tuple, Iterable

        X, Y = np.meshgrid(dt_is, counts)
        fig = make_subplots(rows=1, cols=1, specs=[[{'type': 'surface'}]])
        surface = go.Surface(x=X, y=Y, z=np.asarray(senss), colorscale='Reds', showscale=False)
        fig.add_trace(surface, row=1, col=1)
        surface = go.Surface(x=X, y=Y, z=np.asarray(specs), colorscale='Greens', showscale=False)
        fig.add_trace(surface, row=1, col=1)
        surface = go.Surface(x=X, y=Y, z=np.asarray(foms), colorscale='Blues', showscale=False)
        fig.add_trace(surface, row=1, col=1)
        fig.show()

    plt.show()






# breakpoint()
'''
if pts:
    # to run GUI event loop
    # plt.ion()
    x = np.linspace(0, 2, 100)
    y = np.sin(x)


    # here we are creating sub plots
    figure, ax = plt.subplots(figsize=(10, 8))
    ax.set_ylim(0,255)
    ax.autoscale(enable=None, axis="x", tight=True)
    line1, = ax.plot(x, y)



    tty = io.TextIOWrapper(
            io.FileIO(
                os.open(
                    "/dev/pts/" + f'{sys.argv[1]}',
                    os.O_NOCTTY | os.O_RDWR),
                "r+"))

    values = []
    for line in iter(tty.readline, None):
        val = line.strip()
        try:
            val = int(val)
            values.append(int(val))
            x = range(len(values))
            ax.set_xlim(0, max(x))
            # Edited from https://www.geeksforgeeks.org/how-to-update-a-plot-on-same-figure-during-the-loop/
            line1.set_xdata(x)
            line1.set_ydata(values)
            figure.canvas.draw()
            figure.canvas.flush_events()
        except:
            print(val)
'''
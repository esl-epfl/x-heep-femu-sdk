from scipy.signal import butter,filtfilt
from scipy import interpolate
import numpy as np
from timeseries import Timeseries

def pas(series, e):
    '''
    Implement a PAS
    '''
    data = series.data
    time = series.time
    dx  = 1 # Time differential
    i   = 1 # Sample index
    f   = 0 # Cost function
    x   = 0 # Time sample
    y   = 0 # Value sample
    t_  = 0 # Time of the previous fiducial point
    p   = 0 # Time of a peak
    l   = 0 # Length
    o = Timeseries(series.name + " PAS") # Output array
    for i in range(1,len(time)):
        dy = data[i] - data[i-1]
        x += dx
        y += dy
        f = f + x*dx + y*dy
        displ = abs(y) + x
        if displ < l and p == 0:
            p += i - 1
        l = displ
        if abs(f) > e: # ToDo: Maybe adjust e to reach a certain level of compression?
            if p == 0:
                t = i -1
            else:
                t= p
            o.data.append( data[t] )
            o.dx = t - t_# This is the value that would be saved
            o.time.append( time[t] )
            f = 0
            p = 0
            x = (i-t)*dx
            y = data[i] - data[t]
            t_ = t
            l = abs(y) + x
    return o

def neo(series, win):
    o = Timeseries(series.name + " NEO")
    o.f_Hz = series.f_Hz
    t_diff = int(o.f_Hz*win)
    for i in range(t_diff,len(series.data)):
        dx = series.time[i] - series.time[i-t_diff]
        dy = series.data[i] - series.data[i-t_diff]
        dydx = dy/dx
        o.data.append( dydx**2 - series.data[i]*dydx )
        o.time.append( series.time[i] )
    return o

def aso(series, win):
    o = Timeseries(series.name + " ASO")
    o.f_Hz = series.f_Hz
    t_diff = int(o.f_Hz*win)
    for i in range(1,len(series.data)):
        dx = series.time[i] - series.time[i-t_diff]
        dy = series.data[i] - series.data[i-t_diff]
        dydx = dy/dx
        o.data.append( series.data[i]*dydx )
        o.time.append( series.time[i] )
    return o

def as2o(series, win):
    o = Timeseries(series.name + " AS2O")
    o.f_Hz = series.f_Hz
    t_diff = int(o.f_Hz*win) if o.f_Hz != 0 else win
    for i in range(t_diff,len(series.data)):
        dx = series.time[i] - series.time[i-t_diff]
        dy = series.data[i] - series.data[i-t_diff]
        dydx = dy/dx
        o.data.append( series.data[i]*dydx**2 )
        o.time.append( series.time[i] )
    return o

def needle(series, win):
    o = Timeseries(series.name + " needle'd")
    o.f_Hz = series.f_Hz
    t_diff = int(o.f_Hz*win) if o.f_Hz != 0 else win
    k = Timeseries("inflections")
    d = []
    d.append(0)
    o.data.append(1)
    o.time.append(0)
    for j in range(1,len(series.data)):
        d.append( 1 if series.data[j] - series.data[j-t_diff] > 0 else -1 )
        if d[j]*d[j-1] < 0:
            k.data.append( j-1 )
    for i in range(1,len(k.data)):
        dx = series.time[k.data[i]] - series.time[k.data[i-1]]
        dy = series.data[ k.data[i] ] - series.data[ k.data[i-1] ]
        o.data.append( (dy**2)/dx )
        o.time.append( series.time[k.data[i]] )
    return o



def mean_sub(series, window):
    o = Timeseries(series.name + " Mean")
    o.f_Hz = series.f_Hz
    for i in range(window,len(series.time)):
        ### print('',end='\r')
        m = np.average(series.data[i-window:i])
        o.data.append( series.data[i] - m )
        o.time.append( series.time[i] )
        ### print(i, end='')
    ### print('',end='\r')
    return o

def pseudo_mean(series, bits):
    o = Timeseries(series.name + " pMean")
    o.f_Hz = series.f_Hz
    m = int(series.data[0])
    mb = int(series.data[0]) << bits
    for i in range(len(series.time)):
        mb = int(mb - m + series.data[i]) # m[i]xb = m[i-1]xb - m[i-1] + s[i]]
        m = mb >> bits  # m[i] = m[i]xb /b
        o.data.append( m )
        o.time.append( series.time[i] )
        ### print('\r',i, end='')
    ### print('',end='\r')
    return o

def lpf_butter(series, cutoff, order):
    o = Timeseries(series.name + " LPF")
    o.f_Hz = series.f_Hz
    normal_cutoff = 2/cutoff
    b, a = butter(order, normal_cutoff, btype='low', analog=False)
    o.data = filtfilt(b, a, series.data)
    o.time = series.time
    return o

def norm(series):
    o = Timeseries(series.name + " Norm")
    o.time = series.time
    o.f_Hz = series.f_Hz
    sorted = np.abs(series.data)
    sorted.sort()
    maxs = sorted[-10:]
    maxd = np.average(maxs)
    for s in series.data:
        d = 127*s/maxd
        if d > 127:
            d = 127
        elif d < -127:
            d = -127
        o.data.append(d)
    return o

def first_level(lvls):
    return int( np.floor( len(lvls)/2 ) )

UP = 1
NO = 0
DN = -1
CHANGE = -1

def lcadc(series, lvls, save_last=True):
    o = Timeseries(series.name + " LCADC")
    first = first_level(lvls)
    o.f_Hz = 0
    now = first
    last_l = first
    nxt = 0
    dir = 0
    last_t = 0

    def save(i, last_t, dir, last_l):
        if save_last and last_l >= 0: #also save last time\
            last_t, last_l = save( last_l, last_t, NO, CHANGE )
        dt = series.time[i] - last_t
        o.time.append(dt)
        o.data.append(dir)
        return series.time[i], last_l

    def switch( i, nxt, dir, last_l):
        last_l = i
        dir *= CHANGE
        poss =  nxt + 2*dir
        if poss > 0 and poss < len(lvls):
            nxt = poss
        return dir, nxt, last_l

    def next(nxt, dir, last_l):
        last_l = CHANGE
        now = nxt
        nxt += dir
        return now, nxt, last_l


    start = 0
    while True:
        if series.data[start+1] > series.data[start]:
            # We started going up
            dir = UP
        elif series.data[start+1] < series.data[start]:
            dir = DN
        else:
            start += 1
            continue
        nxt = now + dir
        break

    o.time.append(0)
    o.data.append(dir)
    last_t = series.time[start]

    for i in range(start+1,len(series.data)):
        s = series.data[i]
        if dir == UP:
            if s > lvls[nxt]:
                last_t, last_l = save(i, last_t, dir, last_l)
                now, nxt, last_l = next(nxt, dir, last_l)
            elif s < lvls[now]:
                dir, nxt, last_l = switch(i, nxt,dir, last_l)
        elif dir == DN:
            if s < lvls[nxt]:
                last_t, last_l = save(i, last_t, dir, last_l)
                now, nxt, last_l = next(nxt, dir, last_l)
            elif s > lvls[now]:
                dir, nxt, last_l = switch(i,nxt,dir, last_l)
    return o


CMP_H = DIR_U = NEXT = 1
CMP_L = DIR_D = SWTC = -1
CMP_N = 0

class Comparator:
    def __init__( self ):
        self.high   = 0
        self.low    = 0
        self.ptr    = 0
        self.dir    = DIR_U
        self.cmp    = CMP_N
        self.lvls_n = 0
        self.buf    = Timeseries("All level crossings")
        self.prund  = Timeseries("debounced")
        self.diffd  = Timeseries("Differences between points")


    def set_comparators(self, lvls):
        self.lvls_n = len(lvls)
        if self.dir == DIR_U:
            self.high   = min(self.lvls_n-1,self.ptr + 1)
            self.low    = self.ptr
        elif self.dir == DIR_D:
            self.high   = self.ptr
            self.low    = max(0,self.ptr - 1)

    def compare(self, s, lvls ):
        if      s >= lvls[self.high]:   self.cmp = CMP_H
        elif    s <= lvls[self.low]:    self.cmp = CMP_L
        else:                           self.cmp = CMP_N

    def check_cross(self):
        case = self.cmp * self.dir
        if case == NEXT: self.next()
        if case == SWTC: self.switch()
        return case

    def next(self):
        self.ptr = max(0, min( self.ptr + self.dir, self.lvls_n ))

    def switch(self):
        self.dir *= -1

    def save(self, t):
        self.buf.data.append(self.ptr)
        self.buf.time.append(t)

    def debounce(self):
        for i in range(2, len(self.buf.data)):
            if      self.buf.data[i] == self.buf.data[i-1]: continue # It's the same level! keep the first one only
            elif    self.buf.data[i] == self.buf.data[i-2]: continue # We are going back and forth, ignore this one
            else:
                self.prund.data.append( self.buf.data[i] )
                self.prund.time.append( self.buf.time[i] )

    def differentiate(self, series ):
        # ### print(series.time[0], series.data[0])
        self.diffd.data.append( series.time[0] )
        self.diffd.time.append( series.time[0] )
        for i in range(1,len(series.data) ):
            dl = series.data[i] - series.data[i-1] # This should be either -1, 0 or 1
            dt = series.time[i] - series.time[i-1]
            # ### print(f"{series.time[i]}/{series.data[i]:.1f} = {dt}/{dl}")
            self.diffd.data.append( dl )
            self.diffd.time.append( dt )



def lcadc_fil(series, lvls):
    o = Timeseries(series.name + " LC2")
    first =  first_level(lvls)
    c = Comparator()
    c.ptr = first
    c.buf.data.append(first)
    c.buf.time.append(series.time[0])

    for i in range( 1, len(series.data) ):
        s = series.data[i]
        t = series.time[i]
        c.set_comparators(lvls)
        c.compare(s, lvls)
        case = c.check_cross()
        if case == NEXT:
            c.save(t)
    c.debounce()
    c.differentiate(c.buf)
    o.data = c.diffd.data
    o.time = c.diffd.time
    return o


def lcadc_reconstruct(series, lvls):
    o = Timeseries(series.name + " LCrec")
    first = first_level(lvls)
    lvl = first
    o.time.append(series.time[0])
    o.data.append(lvls[lvl])
    for i in range(1, len(series.data)):
        o.time.append( o.time[i-1] + series.time[i] )
        lvl = min( max(0, lvl + series.data[i] ), len(lvls) -1 )
        o.data.append( lvls[lvl] )
    return o

def lcadc_reconstruct_time(series):
    o = Timeseries(series.name + " LCrecTime")
    o.time.append(series.time[0])
    o.time.append(series.time[0])
    o.time.append(series.time[0])
    o.data.append(0)
    o.data.append(0)
    o.data.append(0)
    dt = 0.00001
    i = 3
    for x in range(1, len(series.data)):
        t = o.time[i-2] + series.time[x]
        o.time.append( t -dt )
        o.time.append( t )
        o.time.append( t +dt )
        o.data.append( 0 )
        o.data.append( 16 if series.data[x] == 1 else -16 )
        o.data.append( 0 )
        i += 3
    return o

def lvls_shifted():
    lvls_a = [ 2, 4, 8, 16, 32, 64, 128 ]
    lvls_b = [3 + l for l in lvls_a ]
    lvls_c = lvls_a + lvls_b
    lvls_c.sort()
    lvls_d = [0]+lvls_c
    lvls_c.reverse()
    lvls_c = [-l for l in lvls_c]
    lvls_d = lvls_c+lvls_d
    return lvls_d

def lvls_pwr2():
    return [ -128, -96, -64, -48, -32, -24, -16, -12, -8, -6, -4, 0,
            4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128]

def lvls_centered():
    return [-128, -95, -63, -47, -39, -32, -27, -23, -15, 0, 15, 23, 27, 32, 39, 47, 63, 95, 128]

def lvls_pwr2_high():
    return [ -128, -96, -64, -48, -32, -24, -16, -12, -8, 8, 12, 16, 24, 32, 48, 64, 96, 128]

def lvls_uniform():
    return list(range(-128,129,16))

def lvls_uniform_dense():
    return list(range(-128,129,8))

def get_density(series, win):
    o = Timeseries("LCdens")
    abst = 0
    lstt = 0
    buf = []
    for t in series.time:
        abst += t
        if abst - lstt > win:
            o.time.append(abst)
            o.data.append(len(buf))
            lstt = abst
            buf = []
        else:
            buf.append(t)
    return o


def spike_det_dt(series, threshold):
    o = Timeseries("sDet")
    for s,t in zip(series.data, series.time):
        if s > threshold or s < -threshold:
            o.time.append(t)
    return o


def spike_det_lc(series, dt, count):
    o = Timeseries("sDETlc")
    i = count

    print(">>", series.data[:10])

    data = [d for d in series.data if d != 0]
    time = [t for t,d in zip(series.time, series.data) if d != 0]
    for i in range(count, len(data)):
        if all(d == data[i] for d in data[i-count+1:i+1]): # A burst
            if time[i] - time[i-count] < dt: # fast
                o.time.append(time[i])
    return o


def lc_aso(series, lvls):
    o = Timeseries("LCASO")
    lvl = first_level(lvls)
    t =  series.time[0]
    for i in range(1, len(series.data) ):
        dt = series.time[i]
        t += dt
        dir = series.data[i]
        lvl += dir
        y = lvls[lvl]
        dy = y - lvls[ lvl- dir ]
        slope = dy/dt
        aso = y*slope
        o.time.append(t)
        o.data.append(aso)
    return o


def oversample(series, order):
    o = Timeseries(f"Overs.{order}")
    o.f_Hz = series.f_Hz*order
    f = interpolate.interp1d(series.time, series.data)
    o.time = np.arange( series.time[0], series.time[-1], 1/o.f_Hz )
    o.data = f(o.time)
    return o

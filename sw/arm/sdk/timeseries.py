import numpy as np
import pickle

class Timeseries:
    def __init__(self, name):
        self.name = name
        self.data = []
        self.time = []
        self.dx = []
        self.f_Hz = 0

    def __str__(self):
        return self.name

    def export(self, path="../out/", name="" ):
        if name == "": name = self.name.replace(" ", "_")
        with open( path+name+".timeseries", 'w+') as f:
            for t, d in zip(self.time, self.data): f.write(f"{t}, {d}\n")

    def export_bin(self, path="../out/", name=""):
        '''
        This will onlywork with synchronous timeseries, as it will discard time information.
        '''
        if name == "": name = self.name.replace(" ", "_")
        # Save the array to a binary file
        d_32 = np.array(self.data).astype(np.int32)
        with  open( path+name+".bin", 'wb+') as f:
            d_32.byteswap(True).tofile(f)

    def dump(self, path="../out/", name=""):
        if name == "": name = self.name.replace(" ", "_")
        cop = self
        cop.data = np.asarray(cop.data)
        with open( path + name + ".pkl", 'wb') as f:
            pickle.dump( cop, f )

    @classmethod
    def load(cls, filename ):
        with open( filename, 'rb' ) as f:
            return pickle.load(f)

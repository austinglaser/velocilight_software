#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8

import numpy as np
import numpy.fft as fft
import matplotlib.pyplot as plt
import sys

fs = 27439

audio_time = np.fromfile(sys.argv[1], dtype="i2")
times = np.array([t / fs for t in range(len(audio_time))])

audio_freq  = np.absolute(fft.rfft(audio_time))
freqs = np.array([b * fs / len(audio_time) for b in range(len(audio_freq))])

fig, axs = plt.subplots(nrows=2, ncols=1)

axs[0].plot(freqs[1:], audio_freq[1:])
axs[1].plot(times, audio_time)
plt.show()

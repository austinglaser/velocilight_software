#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8

import numpy as np
import numpy.fft as fft
import math
import matplotlib.pyplot as plt
import sys

fs = 27439

#audio_freqc = np.fromfile(sys.argv[1], dtype="f4")
#
#audio_freq = []
#for i in range(len(audio_freqc) // 2):
#    audio_freq.append(math.sqrt(audio_freqc[2*i]**2
#                                + audio_freqc[2*i + 1]**2))
#audio_freq = np.array(audio_freq)

audio_freq = np.fromfile(sys.argv[1], dtype="u2")

freqs = np.array([b * fs / (len(audio_freq)*2) for b in range(len(audio_freq))])

plt.plot(freqs[1:], audio_freq[1:])
plt.show()

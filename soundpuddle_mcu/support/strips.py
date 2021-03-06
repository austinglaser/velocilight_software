#! /usr/bin/env python3
# -*- coding: utf-8 -*-
# vim:fenc=utf-8

import numpy as np
import sys

if len(sys.argv) != 3:
    print("Usage: strips.py <file_basename> <len>")
    sys.exit(1)

fs        = 27439
strips    = 72
octaves   = 9
base_freq = 13.75

logical_strips = strips*octaves

fft_size = int(sys.argv[2])
basename = sys.argv[1] + "_len" + str(fft_size)

bin_freqs = np.array([b * fs / fft_size / 2 for b in range(fft_size)])

center_freqs = np.array([base_freq * (2**(tone/strips))
                         for tone in range(octaves*strips)])

if center_freqs[-1] > fs/2:
    print("Requesting frequencies over nyquist")
    sys.exit(1)

# Map bins to center frequencies
bin_centers = []
for bin_idx in range(2048):
    bin_freq = bin_freqs[bin_idx]
    best_center = 0
    for center in range(len(center_freqs)):
        best_error = abs(center_freqs[best_center] - bin_freq)
        this_error = abs(center_freqs[center] - bin_freq)
        if (this_error < best_error):
            best_center = center
    bin_centers.append(best_center)

# Hacky way to exclude zero from any set
bin_centers[0] = -1

bin_centers = np.array(bin_centers)

strip_bins = []
longest = 0
for strip in range(strips):
    strip_bins.append([])
    strip_freq_idxs = range(strip,len(center_freqs),strips)
    for strip_freq_idx in strip_freq_idxs:
        strip_freq = center_freqs[strip_freq_idx]
        center_idxs = np.where(bin_centers == strip_freq_idx)
        for center_idx in center_idxs:
            strip_bins[strip].extend(center_idx)
    if len(strip_bins[strip]) > longest:
        longest = len(strip_bins[strip])

header_filename = basename + ".h"
source_filename = basename + ".c"

variable_template = "const uint16_t {n}[{s}][{l}]"
variable_name = variable_template.format(n=basename,l=longest,s=strips)
with open(header_filename, "w") as header_file:
    header_file.write("#pragma once\n\n");
    header_file.write("/* This is an autogenerated file -- DO NOT EDIT */\n\n");
    header_file.write('#include <stdint.h>\n\n');
    header_file.write("extern " + variable_name + ";\n")

with open(source_filename, "w") as source_file:
    source_file.write("/* This is an autogenerated file -- DO NOT EDIT */\n\n");
    source_file.write('#include "' + header_filename + '"\n\n');
    source_file.write('#include <stdint.h>\n\n');
    source_file.write(variable_name + " = {\n")
    for strip in strip_bins:
        source_file.write("    {\n")
        for b in strip:
            source_file.write("        {b},\n".format(b=b))
        source_file.write("    },\n")
    source_file.write("};\n")

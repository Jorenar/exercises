#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# Tasks: https://is.gd/dlcmvI

import numpy as np
import matplotlib.pyplot as pl
import scipy.stats as st
from sklearn import cluster, datasets


# Wykonaj kenrlową estymację gęstości 2D
# (dobierz odpowiednią szerokość okna)
def ex():
    # data {{{
    n_samples = 100
    data, data_y = datasets.make_circles(n_samples=n_samples, factor=0.5, noise=0.05)
    # }}}

    X, Y = np.mgrid[-2:2:100j, -2:2:100j]

    kernel = st.gaussian_kde(data.T, bw_method=0.2)
    pos = np.vstack([X.ravel(), Y.ravel()])
    Z = np.reshape(kernel(pos).T, X.shape)

    fig, ax = pl.subplots()
    cs = ax.contour(X, Y, Z)
    ax.clabel(cs, cs.levels, inline=True, fmt="%.3f", fontsize=10)
    pl.show()

ex()

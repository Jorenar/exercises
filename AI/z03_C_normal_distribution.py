#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# Tasks: https://is.gd/mUTxCH

import matplotlib.pylab as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.mlab as mlab
from matplotlib import cm
from scipy.stats import multivariate_normal


# Narysujmy gęstość dwuwymiarowego rozkładu Normalnego
def ex():
    def draw(n, cov):
        x = np.linspace(-10, 10, 100)
        y = np.linspace(-10, 10, 100)
        X, Y = np.meshgrid(x, y)
        pos = np.empty(X.shape + (2,))
        pos[:, :, 0] = X
        pos[:, :, 1] = Y
        rv = multivariate_normal(n, cov)

        fig = plt.figure()
        ax = fig.gca(projection='3d')
        ax.plot_surface(X, Y, rv.pdf(pos), cmap='viridis', linewidth=0)
        plt.show()

    draw([0, 0], [[1, 0], [0, 1]])
    draw([0, 0], [[2, 0], [0, 1]])
    draw([0, 0], [[1, 0], [0, 2]])


# Narysujmy kontury gęstości dwuwymiarowego rozkładu Normalnego
def ex():
    def draw(n, cov):
        x = np.linspace(-10, 10, 100)
        y = np.linspace(-10, 10, 100)
        X, Y = np.meshgrid(x, y)
        pos = np.empty(X.shape + (2,))
        pos[:, :, 0] = X
        pos[:, :, 1] = Y
        rv = multivariate_normal(n, cov)

        Z = rv.pdf(pos)
        fig = plt.figure()
        plt.xlabel("X")
        plt.ylabel("Y")
        contours = plt.contour(X, Y, Z, 100)

        plt.show()

    draw([0, 0], [[1, 0], [0, 1]])
    draw([0, 0], [[2, 0], [0, 1]])
    draw([0, 0], [[1, 0], [0, 2]])


# Wylosujmy próbkę z dwuwymiarowego rozkładu normalnego i narysuj odpowiedni wykres
def ex():  # HW
    def draw(n, cov):
        X_rv = multivariate_normal(n, cov)
        X = X_rv.rvs(1000)
        fig, ax = plt.subplots(nrows=1, ncols=1, figsize=(5, 5))
        ax.scatter(X[:, 0], X[:, 1])
        ax.set_xlim([-6,6])
        ax.set_ylim([-6,6])
        plt.show()

    draw([0, 0], [[1, 0], [0, 1]])
    draw([0, 0], [[2, 0], [0, 1]])
    draw([0, 0], [[1, 0], [0, 2]])

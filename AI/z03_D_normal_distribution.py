#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# Tasks: https://is.gd/jrjGka

import matplotlib.pyplot as plt
import numpy as np
import numpy.random as rnd
import scipy.stats as stats
from scipy.stats import multivariate_normal
from sklearn import datasets

from pprint import pprint

# Proszę zdefiniować zmienną losową o razkładzie zadanym na podstawie
# empirycznej średniej i kowariancji oraz narysować na jednym wykresie
# próbkę oraz poziomice rozkładu normalnego.
def ex():
    mean = np.array([0, 0])
    cov = np.array([[4.40, -2.75], [-2.75, 5.50]])
    X2_rv = multivariate_normal(mean, cov)
    X = X2_rv.rvs(1000)
    x = np.linspace(-10, 10, 100)
    y = np.linspace(-10, 10, 100)
    X2, Y2 = np.meshgrid(x, y)
    pos = np.empty(X2.shape + (2,))
    pos[:, :, 0] = X2
    pos[:, :, 1] = Y2
    plt.figure(figsize=(7, 7))
    plt.contour(X2, Y2, X2_rv.pdf(pos), colors="red")
    plt.scatter(X[:, 0], X[:, 1])
    plt.show()


# Policz wektory i wartości własne macierzy kowariancji.
# Narysuj na jednym wykresie:
#   próbkę
#   poziomice rozkładu normalnego
#   wektory własne macierzy kowariancji
def ex(): # HW
    mean = np.array([0, 0])
    cov = np.array([[4.40, -2.75], [-2.75,  5.50]])
    X1_rv = multivariate_normal(mean, cov)
    sample = X1_rv.rvs(1000)
    means = sample.mean(axis=0)
    cov = np.cov(sample.T)
    X2_rv = multivariate_normal(means, cov)

    eigVals, eigVecs = np.linalg.eig(cov)

    print("# means\n", means, "\n")
    print("# eigVecs\n", eigVecs, "\n")

    plt.scatter(sample[:,0], sample[:,1])

    soa = np.array([[means[0], means[1],
                     2 * np.sqrt(eigVals[1]) * eigVecs[0, 1],
                     2 * np.sqrt(eigVals[1]) * eigVecs[1, 1]],
                    [means[0], means[1],
                     2 * np.sqrt(eigVals[0]) * eigVecs[0, 0],
                     2 * np.sqrt(eigVals[0]) * eigVecs[1, 0]]])
    print("# soa")
    print(soa)
    X, Y, U, V = zip(*soa)
    plt.quiver(X, Y, U, V, angles="xy", scale_units="xy", scale=1)

    linSpc = lambda: np.linspace(-10, 10, 100)
    x, y = np.meshgrid(linSpc(), linSpc())

    pos = np.empty(x.shape + (2,))
    pos[:, :, 0] = x
    pos[:, :, 1] = y
    plt.contour(x, y, X2_rv.pdf(pos), colors="red")

    plt.show()


# Proszę wygenerować próbkę na kwadracie [0,1]x[0,1]
# Następnie proszę policzyć średnią oraz macierz kowariancji próbki.
# Narysuj na jednym wykresie:
#   próbkę
#   poziomice rozkładu normalnego
#   wektory własne macierzy kowariancji
def ex(): # HW
    n = 5000
    sample = np.random.uniform(0, 1, size=(n,2))

    means = sample.mean(axis=0)
    cov = np.cov(sample.T)
    X2_rv = multivariate_normal(means, cov)

    eigVals, eigVecs = np.linalg.eig(cov)

    print("# means\n", means, "\n")
    print("# eigVecs\n", eigVecs, "\n")

    plt.scatter(sample[:,0], sample[:,1])

    soa = np.array([[means[0], means[1],
                     2 * np.sqrt(eigVals[1]) * eigVecs[0, 1],
                     2 * np.sqrt(eigVals[1]) * eigVecs[1, 1]],
                    [means[0], means[1],
                     2 * np.sqrt(eigVals[0]) * eigVecs[0, 0],
                     2 * np.sqrt(eigVals[0]) * eigVecs[1, 0]]])
    print("# soa")
    print(soa)
    X, Y, U, V = zip(*soa)
    plt.quiver(X, Y, U, V, angles="xy", scale_units="xy", scale=1)

    linSpc = lambda: np.linspace(-0.2, 1.2, n) # <-
    x, y = np.meshgrid(linSpc(), linSpc())

    pos = np.empty(x.shape + (2,))
    pos[:, :, 0] = x
    pos[:, :, 1] = y
    plt.contour(x, y, X2_rv.pdf(pos), colors="red")

    plt.show()

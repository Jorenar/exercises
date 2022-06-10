#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# Tasks: https://is.gd/5MrNPc

import seaborn as sns
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import scipy.stats as stats
from scipy.stats import multivariate_normal

# Wygeneruj dane 10D tak by
#   1, 3 i 5 współrzedna były skorelowane ze sobą dodatnio
#   7 i 8 współrzedna były skorelowane ze sobą ujemnie
#   pozostałe były nieskorelowane
def ex():
    n = 1000
    x0 = stats.norm(0, 1).rvs(n)
    x1 = stats.norm(0, 1).rvs(n)
    x3 = stats.norm(0, 1).rvs(n)
    x5 = stats.norm(0, 1).rvs(n)
    x6 = stats.norm(0, 1).rvs(n)
    x8 = stats.norm(0, 1).rvs(n)
    x9 = stats.norm(0, 1).rvs(n)
    X = np.stack((x0, x1, 2 * x0, x3, 3 * x0, x5, x6, -1 * x6, x8, x9), 1)

    df = pd.DataFrame(X)
    sns.pairplot(df)
    plt.show()

    sns.set(style="darkgrid")

    corr = df.corr()

    # Generate a mask for the upper triangle
    mask = np.zeros_like(corr, dtype=np.bool)
    mask[np.triu_indices_from(mask)] = True

    # Set up the matplotlib figure
    f, ax = plt.subplots(figsize=(11, 9))

    # Generate a custom diverging colormap
    cmap = sns.diverging_palette(220, 10, as_cmap=True)

    # Draw the heatmap with the mask and correct aspect ratio
    sns.heatmap(corr, mask=mask, cmap=cmap, vmin=-1, vmax=1,
                square=True, xticklabels=5, yticklabels=5,
                linewidths=.5, cbar_kws={"shrink": .5}, ax=ax)
    plt.show()
    print(corr)


# Dodaj kilka współrzednych tak by były skorelowanie nieliniowo np. x^2
# (czy widać jakiś efekt na heat map?)                  // Nie widać... chyba
def ex():  # HW
    n = 1000
    x0 = stats.norm(0, 1).rvs(n)
    x1 = stats.norm(0, 1).rvs(n)
    x3 = stats.norm(0, 1).rvs(n)
    x5 = stats.norm(0, 1).rvs(n)
    x6 = stats.norm(0, 1).rvs(n)
    x8 = stats.norm(0, 1).rvs(n)
    x9 = stats.norm(0, 1).rvs(n)
    X = np.stack((x0, x1, 2 * x0, x3, 3 * x0, x5, x6, -1 * x6, x8, x9,
                  x0**2, 1/x3, x8**5), 1)

    df = pd.DataFrame(X)
    corr = df.corr()

    # PAIRPLOT {{{1
    sns.pairplot(df)
    plt.show()

    # HEATMAP {{{1
    sns.set(style="darkgrid")

    # Generate a mask for the upper triangle
    mask = np.zeros_like(corr, dtype=np.bool_)
    mask[np.triu_indices_from(mask)] = True

    # Set up the matplotlib figure
    f, ax = plt.subplots(figsize=(11, 9))

    # Generate a custom diverging colormap
    cmap = sns.diverging_palette(220, 10, as_cmap=True)

    # Draw the heatmap with the mask and correct aspect ratio
    sns.heatmap(corr, mask=mask, cmap=cmap, vmin=-1, vmax=1,
                square=True, xticklabels=5, yticklabels=5,
                linewidths=.5, cbar_kws={"shrink": .5}, ax=ax)
    plt.show()
    # }}}1

    print(corr)


# Wykonaj wykresy `sns.pairplot` oraz `sns.heatmap` dla poniższego zbioru danych
def ex():  # HW
    # data {{{
    from sklearn import datasets
    boston = datasets.load_boston()
    data = boston.data
    # }}}

    df = pd.DataFrame(data)
    corr = df.corr()

    # PAIRPLOT {{{1
    sns.pairplot(df)
    plt.show()

    # HEATMAP {{{1
    sns.set(style="darkgrid")

    # Generate a mask for the upper triangle
    mask = np.zeros_like(corr, dtype=np.bool)
    mask[np.triu_indices_from(mask)] = True

    # Set up the matplotlib figure
    f, ax = plt.subplots(figsize=(11, 9))

    # Generate a custom diverging colormap
    cmap = sns.diverging_palette(220, 10, as_cmap=True)

    # Draw the heatmap with the mask and correct aspect ratio
    sns.heatmap(corr, mask=mask, cmap=cmap, vmin=-1, vmax=1,
                square=True, xticklabels=5, yticklabels=5,
                linewidths=.5, cbar_kws={"shrink": .5}, ax=ax)

    # }}}1

    plt.show()

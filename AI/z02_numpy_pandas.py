#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# Tasks: https://is.gd/pvgbkv

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from scipy.integrate import simps
from scipy import stats


def ex1():
    a = np.random.rand(100, 10)
    dist = ((a - a.reshape(a.shape[0], 1, a.shape[1]))**2).sum(axis=-1)
    print(dist)


def ex2():  # HW TODO
    print(np.random.multivariate_normal(5, 100))


def ex3():
    tab = np.random.random_integers(5, 15, size=100)
    b = np.bincount(tab)
    a = np.argmax(b)


def ex4():  # HW TODO
    pass


def ex5():
    df = pd.read_csv("data/airports.csv", header=None)
    # Column:
    #  1 = airport name
    #  2 = city
    #  3 = country
    #  8 = elevation

    # Wybierz nazwy państw ostatnich 12 lotnisk w tabeli
    print(df[3].tail(12).unique().tolist())

    # Wybierz wiersz o indeksie 1 korzystając z indeksera .loc oraz .iloc
    #  (porównaj otrzymane wyniki)
    x = df.loc[df[0] == 1]
    y = df.iloc[1]
    print(x)
    print(y)
    print(x == y)

    # Wybierz wszystkie lotniska w Polsce
    print(df.loc[df[3] == "Poland"])

    # Wybierz wszystkie lotniska, których nazwa różni się od nazwy miasta, w którym się znajdują
    print(df.loc[df[1] != df[2]])

    # Przelicz wartości wysokości na metry i zapisz zmodyfikowaną kolumnę w miejsce starej
    #   (w naszej tabeli wysokość jest podana w kolumnie 8 w stopach nad poziomem morza;
    #    jedna stopa angielska równa się 30,48 cm)
    df[8] = df[8].apply(lambda x: x * 0.3048)
    print(df[[1, 8]])

    # Znajdź wszystkie państwa, w których znajduje się wyłącznie 1 lotnisko
    one = df[3].drop_duplicates(keep=False)
    print("\n".join(one.tolist()))


def ex6():
    df = pd.read_csv("data/titanic.csv")
    df.drop(columns=["PassengerId", "Name", "Ticket"])


def ex7():
    df = pd.read_csv("data/titanic.csv")
    df.assign(HasCabin=df["Cabin"].notnull().astype(int))[["HasCabin", "Cabin"]]


def ex8():
    df = pd.read_csv("data/titanic.csv")
    df.dropna()


def ex_():  # HW TODO
    pass


def ex9():  # HW
    mu = 0
    sigma = 1

    x = np.linspace(mu - 4*sigma, mu + 4*sigma, 100)
    y = stats.norm.pdf(x, mu, sigma)

    area1 = np.linspace(mu - sigma, mu +sigma, 100)
    val1 = stats.norm.pdf(area1, mu, sigma)
    area2 = np.linspace(mu - 2*sigma, mu + 2*sigma, 100)
    val2 = stats.norm.pdf(area2, mu, sigma)
    area3 = np.linspace(mu - 3*sigma, mu + 3* sigma, 100)
    val3 = stats.norm.pdf(area3, mu, sigma)

    int1 = simps(val1,area1, 100)
    int2 = simps(val2,area2, 100)
    int3 = simps(val3,area3, 100)

    rand_x = np.random.normal(mu, sigma, 1000000)

    p1 = np.sum((rand_x > mu-sigma) & (rand_x<mu+sigma))/1000000
    p2 = np.sum((rand_x > mu-2*sigma) & (rand_x<mu+2*sigma))/1000000
    p3 = np.sum((rand_x > mu-3*sigma) & (rand_x<mu+3*sigma))/1000000

    fig, (ax1, ax2, ax3) = plt.subplots(1, 3, sharey=True, figsize=(10, 3))
    ax1.fill_between(x,y,0,where = (x > mu-sigma) & (x<mu+sigma),color='grey')
    ax1.plot(x, y)
    ax2.fill_between(x,y,0,where = (x > mu-2*sigma) & (x<mu+2*sigma),color='grey')
    ax2.plot(x, y)
    ax3.fill_between(x,y,0,where = (x > mu-3*sigma) & (x<mu+3*sigma),color='grey')
    ax3.plot(x, y)
    ax1.text(0.5, 0.5, '{:.3f}'.format(int1), horizontalalignment='center', verticalalignment='center', transform=ax1.transAxes)
    ax2.text(0.5, 0.5,'{:.3f}'.format(int2), horizontalalignment='center', verticalalignment='center', transform=ax2.transAxes)
    ax3.text(1.7, 0.5, '{:.3f}'.format(int3), horizontalalignment='center', verticalalignment='center', transform=ax2.transAxes)
    plt.show()

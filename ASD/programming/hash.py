#!/usr/bin/env python
# -*- coding: UTF-8 -*-


# Task: find all subarrays which's elements sum up to k


tests = [
        {
            "arr": [ 1, -2, 3 ],
            "k": 2,
            "out": 1,
            },
        {
            "arr": [ 1 ],
            "k": 1,
            "out": 1,
            },
        {
            "arr": [ 1, 3 ],
            "k": 2,
            "out": 0,
            },
        {
            "arr": [ 1, 1, 1 ],
            "k": 2,
            "out": 2,
            },
        ]

def find(arr, k):
    K = 0
    sum = 0

    foo = { 0: 1 }

    for a in arr:
        sum += a;
        if foo.has_key(sum - k):
            K += foo[sum - k];
        foo[sum] = 1 if not foo.has_key(sum) else foo[sum] + 1

    return K

for test in tests:
    print(test)
    print(find(test["arr"], test["k"]))

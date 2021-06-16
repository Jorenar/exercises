-- Top three prices in Products | using the solution from ex. 24
SELECT MAX(A.UnitPrice),
       MAX(B.UnitPrice),
       MAX(C.UnitPrice)
FROM Products AS A,
     Products AS B,
     Products AS C
WHERE (A.UnitPrice > B.UnitPrice) AND (B.UnitPrice > C.UnitPrice);

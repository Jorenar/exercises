-- Top three prices in Products | using the solution from ex. 28
SELECT DISTINCT COUNT(*), A.UnitPrice
FROM Products AS A, Products AS B
WHERE (A.UnitPrice <= B.UnitPrice)
GROUP BY A.UnitPrice
HAVING COUNT(*) <= 3;

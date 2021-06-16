-- Max and min prices by category of products with prices over 30
SELECT CategoryID,
       MAX(UnitPrice) AS [Max],
       MIN(UnitPrice) AS [Min]
FROM Products
WHERE UnitPrice > 30
GROUP BY CategoryID;

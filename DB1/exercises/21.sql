-- Max and min prices in each category (together with products)
SELECT temp.CategoryID, MaxPrice AS Price, ProductID, ProductName
FROM (SELECT CategoryID, MAX(UnitPrice) AS MaxPrice FROM Products
      GROUP BY CategoryID) AS temp
JOIN Products ON temp.CategoryID = Products.CategoryID
                 AND
                 temp.MaxPrice = Products.UnitPrice

UNION

SELECT temp.CategoryID, MinPrice AS Price, ProductID, ProductName
FROM (SELECT CategoryID, MIN(UnitPrice) AS MinPrice FROM Products
      GROUP BY CategoryID) AS temp
JOIN Products ON temp.CategoryID = Products.CategoryID
                 AND
                 temp.MinPrice = Products.UnitPrice;

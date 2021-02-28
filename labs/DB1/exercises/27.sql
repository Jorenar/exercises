-- Top three prices in Products | using the solution from ex. 26
SELECT DISTINCT UnitPrice FROM Products
WHERE UnitPrice >=
    (SELECT MAX(UnitPrice) FROM Products
     WHERE UnitPrice < (SELECT MAX(UnitPrice) FROM Products
                        WHERE UnitPrice < (SELECT MAX(UnitPrice) FROM Products)));

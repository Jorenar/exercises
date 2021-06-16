-- Beverages of price between 20 and 30
SELECT * FROM Products
WHERE (CategoryID IN (SELECT CategoryID FROM Categories
                      WHERE CategoryName = 'Beverages'))
      AND
      (UnitPrice BETWEEN 20 AND 30)

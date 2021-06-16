-- IDs of clients who placed orders for the largest total amount
SELECT CustomerID FROM
    (SELECT OrderID, SUM(UnitPrice * Quantity) as total FROM [Order Details]
     GROUP BY OrderID) AS temp
JOIN Orders ON Orders.OrderID = temp.OrderID
WHERE total =
    (SELECT TOP 1 total FROM
        (SELECT OrderID, SUM(UnitPrice * Quantity) as total FROM [Order Details]
		 GROUP BY OrderID) AS foo
     ORDER BY total DESC);

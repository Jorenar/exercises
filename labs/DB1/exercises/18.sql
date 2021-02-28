-- Sum of amounts on all orders on a given day by product
SELECT OrderDate, ProductID, SUM(UnitPrice * Quantity) FROM Orders
JOIN [Order Details] AS details ON Orders.OrderID = details.OrderID
GROUP BY OrderDate, ProductID
ORDER BY OrderDate, ProductID;

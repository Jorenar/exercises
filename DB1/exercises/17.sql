-- Sum of amounts on all orders on a given day
SELECT Orders.OrderDate, SUM(UnitPrice * Quantity) FROM Orders
JOIN [Order Details] AS details ON Orders.OrderID = details.OrderID
GROUP BY OrderDate
ORDER BY OrderDate;

-- Amount of orders by category
SELECT CategoryID, COUNT(CategoryID) AS Amount FROM Orders
LEFT JOIN [Order Details] AS details ON details.OrderID = Orders.OrderID
LEFT JOIN Products ON details.ProductID = Products.ProductID
GROUP BY CategoryID
ORDER BY CategoryID;

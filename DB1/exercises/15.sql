-- Amount of orders for product by clients
SELECT details.ProductID, COUNT(DISTINCT CustomerID) AS Amount FROM [Order Details] AS details
LEFT JOIN Products ON details.ProductID = Products.ProductID
LEFT JOIN Orders ON details.OrderID = Orders.OrderID
GROUP BY details.ProductID;

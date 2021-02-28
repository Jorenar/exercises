-- Clients without orders yet | using `LEFT JOIN` and `WHERE`
SELECT Customers.* FROM Customers
LEFT JOIN Orders ON Orders.CustomerID = Customers.CustomerID
WHERE OrderID IS NULL;

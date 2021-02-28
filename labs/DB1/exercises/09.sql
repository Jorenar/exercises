-- Clients without orders yet | using `NOT` and `IN`
SELECT * FROM Customers
WHERE CustomerID NOT IN (SELECT CustomerID FROM Orders);

-- Clients without orders yet | using `NOT` and `EXISTS`
SELECT * FROM Customers
WHERE NOT EXISTS (SELECT NULL FROM Orders
                  WHERE Orders.CustomerID = Customers.CustomerID);

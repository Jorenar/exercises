-- Amount of orders by day
SELECT OrderDate, COUNT(*) AS Amount FROM Orders
GROUP BY OrderDate;

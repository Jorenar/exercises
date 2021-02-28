-- Amount of clients from Poland and from Germany
SELECT Country           AS Kraj,
       COUNT(CustomerID) AS [Liczba klientów]
FROM Customers
WHERE Country = 'Poland' OR Country = 'Germany'
GROUP BY Country;

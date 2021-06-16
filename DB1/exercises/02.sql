-- Clients whose names start with 'C' or 'N'
SELECT * FROM Customers
WHERE CompanyName LIKE 'C%' OR CompanyName LIKE 'N%';
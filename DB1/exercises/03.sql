-- Products starting with letter 'C'
SELECT Products.* FROM Products
JOIN Categories ON Categories.CategoryID = Categories.CategoryID
WHERE CategoryName LIKE 'C%';
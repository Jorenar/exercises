-- Select given columns
SELECT orders.OrderID,
       OrderDate,
       products.ProductID,
       ProductName,
       details.UnitPrice,
       Quantity,
       CategoryName,
       customers.CustomerID,
       CompanyName
FROM      Orders          AS orders
LEFT JOIN Customers       AS customers  ON orders.CustomerID   = customers.CustomerID
LEFT JOIN [Order Details] AS details    ON orders.OrderID      = details.OrderID
LEFT JOIN Products        AS products   ON details.ProductID   = products.ProductID
LEFT JOIN Categories      AS categories ON products.CategoryID = categories.CategoryID;

-- How many rows has this dataset?
--    2155 rows

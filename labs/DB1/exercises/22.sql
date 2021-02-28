-- Top three prices in Products | using `TOP 3`
SELECT TOP 3 UnitPrice FROM Products
ORDER BY UnitPrice DESC;

-- What's the difference between `TOP 3` and `TOP 3 WITH TIES`?
--    Suppose we have N rows in the table and out of that half rows have same value
--    in column which is used in ORDER BY. `TOP k` rows, it will return only 'k' rows,
--    but `TOP K WITH TIES` will return all the rows that have same value as that of
--    the last record of top k - which means a total of N/2 records.

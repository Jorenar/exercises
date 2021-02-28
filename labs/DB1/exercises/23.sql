-- Top three prices in Products | not using `TOP 3`, but `UNION`
WITH temp AS (SELECT MAX(UnitPrice) AS TopPrices FROM Products)
SELECT TopPrices FROM (
    SELECT * FROM temp

    UNION

    SELECT MAX(UnitPrice) FROM Products
	WHERE UnitPrice != (SELECT * FROM temp)

	UNION

    SELECT MAX(UnitPrice) FROM Products
	WHERE
        UnitPrice != (SELECT * FROM temp)
        AND
        UnitPrice != (SELECT MAX(UnitPrice) FROM Products
					  WHERE UnitPrice != (SELECT * FROM temp))

    ) AS foo
ORDER BY TopPrices DESC;

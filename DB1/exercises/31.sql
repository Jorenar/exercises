-- Sort Customers by Region, so that `NULL` will be at the end, but the rest
-- of rows will be in ascending order | using `CASE`

SELECT CompanyName, Region FROM Customers
ORDER BY
    CASE
        WHEN Region IS NULL THEN 2
        ELSE 1
    END, Region

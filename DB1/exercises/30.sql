-- Who is whose boss
SELECT E1.LastName  AS NazwiskoSzefa,
       E1.FirstName AS ImięSzefa,
       'jestem szefem pracownika' AS ZaleznośćSłużbowa,
       E2.LastName  AS NazwiskoPodwładnego,
       E2.FirstName AS ImięPodwładnego
FROM Employees AS E1
JOIN Employees AS E2 ON E2.ReportsTo = E1.EmployeeID;

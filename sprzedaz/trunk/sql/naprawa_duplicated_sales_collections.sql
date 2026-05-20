USE globtechnic
GO

-- sieroty - 3 rodzaje

delete from collections where idcollection=10129013 and IdParent in (
select collections.idparent from collections left outer join n5sprzedaz on collections.idparent=n5sprzedaz.idobj where idcollection=10129013 and n5sprzedaz.idobj is null)
go

delete from collections where idcollection=10129013 and idobj in 
(select collections.idobj from collections left outer join n5pozsprzedaz on collections.idobj=n5pozsprzedaz.idobj where idcollection=10129013 and (n5pozsprzedaz.idobj is null))
go

delete from n5pozsprzedaz where n5pozsprzedaz.idobj not in (select collections.idobj from collections where collections.idcollection=10129013)
go


SELECT coll.IdObj
	,coll.IdParent
	,coll.LP
	,'product' = (
		SELECT strIndeks
		FROM n5produkt
		WHERE IdObj = (
				SELECT pProdukt
				FROM n5pozsprzedaz
				WHERE idobj = coll.IdObj
				)
		)
	,'nr_dok' = (
		SELECT strNrDok
		FROM n5sprzedaz
		WHERE IdObj = coll.IdParent
		)
INTO sales_duplicates
FROM Collections coll
WHERE IdCollection = 10129013
	AND idobj IN (
		SELECT idobj
		FROM Collections
		WHERE IdCollection = 10129013
		GROUP BY IdObj
		HAVING count(*) > 1
		)
GO

--STOP
select * from sales_duplicates
go

SELECT idobj
	,'min_idparent' = min(idparent)
	,'max_idparent' = max(idparent)
INTO sales_duplicate_candidates
FROM sales_duplicates
GROUP BY idobj
GO

SELECT *
FROM Collections c1
INNER JOIN sales_duplicate_candidates sdc ON c1.idobj = sdc.idobj
	AND c1.IdParent = sdc.min_idparent
WHERE IdCollection = 10129013
GO

select c1.* 
into _backup_deleted_sales_duplicate_candidates
FROM Collections c1
INNER JOIN sales_duplicate_candidates sdc ON c1.idobj = sdc.idobj
	AND c1.IdParent = sdc.min_idparent
WHERE IdCollection = 10129013
GO

DELETE Collections
FROM Collections c1
INNER JOIN sales_duplicate_candidates sdc ON c1.idobj = sdc.idobj
	AND c1.IdParent = sdc.min_idparent
WHERE IdCollection = 10129013
GO

DROP TABLE sales_duplicates
GO

DROP TABLE sales_duplicate_candidates
GO


USE globtechnic
GO

-- sieroty - 3 rodzaje
delete from collections 
where idcollection=10176012 and IdParent in (
select collections.idparent from collections left outer join n5zakup on collections.idparent=n5zakup.idobj where idcollection=10176012 and n5zakup.idobj is null)
go

delete from Collections where idcollection=10176012 and IdObj in (
select collections.idobj from collections left outer join n5pozzakup on collections.idobj=n5pozzakup.idobj where idcollection=10176012 and (n5pozzakup.idobj is null))
go

delete from n5pozzakup where n5pozzakup.idobj not in (select collections.idobj from collections where collections.idcollection=10176012)
go

SELECT coll.IdObj
	,coll.IdParent
	,coll.LP
	,'product' = (
		SELECT strIndeks
		FROM n5produkt
		WHERE IdObj = (
				SELECT pProdukt
				FROM n5pozzakup
				WHERE idobj = coll.IdObj
				)
		)
	,'nr_dok' = (
		SELECT strNrDok
		FROM n5zakup
		WHERE IdObj = coll.IdParent
		)
INTO purchase_duplicates
FROM Collections coll
WHERE IdCollection = 10176012
	AND idobj IN (
		SELECT idobj
		FROM Collections
		WHERE IdCollection = 10176012
		GROUP BY IdObj
		HAVING count(*) > 1
		)
GO

-- stop
select * from purchase_duplicates
GO

SELECT idobj,
	'bad_idparent' = idparent
INTO purchase_duplicate_candidates
FROM purchase_duplicates
WHERE nr_dok is null or nr_dok like 'FZK%' or nr_dok like 'ZK%'
GO

SELECT *
FROM Collections c1
INNER JOIN purchase_duplicate_candidates sdc ON c1.idobj = sdc.idobj
	AND c1.IdParent = sdc.bad_idparent
WHERE IdCollection = 10176012
GO

select c1.* 
into _backup_deleted_purchase_duplicate_candidates
FROM Collections c1
INNER JOIN purchase_duplicate_candidates sdc ON c1.idobj = sdc.idobj
	AND c1.IdParent = sdc.bad_idparent
WHERE IdCollection = 10176012
GO

DELETE Collections
FROM Collections c1
INNER JOIN purchase_duplicate_candidates sdc ON c1.idobj = sdc.idobj
	AND c1.IdParent = sdc.bad_idparent
WHERE IdCollection = 10176012
GO

DROP TABLE purchase_duplicates
GO

DROP TABLE purchase_duplicate_candidates
GO


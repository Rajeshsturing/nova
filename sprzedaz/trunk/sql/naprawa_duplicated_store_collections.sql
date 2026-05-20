
USE globtechnic
GO

-- sieroty - 3 rodzaje

delete from collections where idcollection=10162011 and IdParent in (
select collections.idparent from collections left outer join n5dokmag on collections.idparent=n5dokmag.idobj where idcollection=10162011 and n5dokmag.idobj is null)							
go

delete from collections where idcollection=10162011 and idobj in 
(select collections.idobj from collections left outer join n5pozdokmag on collections.idobj=n5pozdokmag.idobj where idcollection=10162011 and (n5pozdokmag.idobj is null))
go

delete from n5pozdokmag where n5pozdokmag.idobj not in (select collections.idobj from collections where collections.idcollection=10162011)
go

---
select * from n5gmop

where

gmo_nNumOp not in (select nnumoper from n5dokmag) and

gmo_nNumOp not in (select nnumoper from n5realprod)

order by gmo_nNumOp,gmo_nLP, IdObj
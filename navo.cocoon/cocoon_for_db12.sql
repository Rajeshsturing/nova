/*
NAVO Cocoon add-ons to EuroBusiness 5.0 DB12 database
*/
 declare  @bExistsCoccon1 int
 select @bExistsCoccon1 = (select 1 where exists(select * from sysobjects where name='cocoon_current_stock'))
 
if @bExistsCoccon1 is null
begin
declare @sqlstring1 nvarchar(4000)
set @sqlstring1 = 
 'create view cocoon_current_stock as
 select 
 [product_id] =vl.p_idobj,
 [subproduct_id]=vl.c_idobj, 
 [subproduct_lp]=max(vl.coll_lp),
 [store_id] = m.idobj,
 [quantity] = isnull((select sum(gms.gms_curIlosc) 
	from n5gmstan gms 
	where gms.gms_pProd=vl.p_idobj and gms.gms_pOpak = vl.c_idobj and gms.gms_pMag=m.idobj),0)
 from vlist_n5produkt_listOpakowania vl, n5magazyn m
 group by vl.p_idobj,vl.c_idobj, m.idobj'
 
exec (@sqlstring1)
end
go
-----------------
 declare  @bExistsCoccon2 int
select @bExistsCoccon2 = (select 1 where exists(select * from sysobjects where name='cocoon_product_group_subtree'))
if @bExistsCoccon2 is null
begin
declare @sqlstring2 nvarchar(4000)
set @sqlstring2 =
'create function cocoon_product_group_subtree(@root int)
returns table as
return
with group_(parent_id, id, text_)
as
(
select @root, IdObj, strNazwa from n5grupaproduktow where pGrupaNadrzedna = @root
union all 
select pGrupaNadrzedna, IdObj, strNazwa from n5grupaproduktow 
inner join group_ on pGrupaNadrzedna = id
)
select parent_id, id, text_ from group_
union all select 0, IdObj, strNazwa from n5grupaproduktow where IdObj=@root'
 
exec (@sqlstring2)
end
go

--all products in subtree under group with idobj=33
--i.e. select * from n5produkt where pGrupaProd in (select id from dbo.cocoon_product_group_subtree(33))

-----------------
exec n2001_makegrants 'navo2002user'
go
-----------------

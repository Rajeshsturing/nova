drop view view_zap_zas
go
-- zapotrzebowanie na zasoby
create view view_zap_zas as 
select 
'idzlecprod'=vzp.p_idobj,
'idtypzasprod'=tzp.idobj,
'zapzas_m'=sum(vzp.c_curIloscOpakPoz / vrw.c_curIloscOpak * vrz.c_prz_curilosc),
'dostzas_m'=(select sum(zsp_curDostepnosc) from n5zasobprod where zsp_pTypZasobu = tzp.idobj)
from vlist_n5zlecprod_listPozycje as vzp
inner join vlist_n5recepta_listWyrob as vrw on vzp.c_pRecepta = vrw.p_idobj
inner join vlist_n5recepta_rcpt_listZasob as vrz on vrz.p_idobj = vrw.p_idobj
inner join n5typzasobprod tzp on vrz.c_prz_ptypzasobu = tzp.idobj
where vzp.c_curIloscOpakPoz <>0
group by tzp.idobj,vzp.p_idobj

-- 

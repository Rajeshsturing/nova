SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO


create   PROCEDURE [dbo].[RAND_FVAT_WZ_KLIOB] @obiekt_klienta int
 AS

BEGIN

select * from 
(
select
10129 as dokument_type,
p_strnrdok as dokument_numer
,p_idobj as dokument_idobj
,p_ddatawyst as dokument_data
,n5produkt.strNazwa as towar_nazwa 
,n5produkt.idobj as towar_idobj 
,n5jednostka.nDokladnosc as towar_dokladnosc
,n5jednostka.strSkrot as towar_jm
,c_curiloscopak as pozycja_ilosc
,c_curwartbrutto as pozycja_wartosc
from vlist_n5sprzedaz_listPozycje
inner join n5produkt on (n5produkt.idobj = vlist_n5sprzedaz_listPozycje.c_pprodukt )
inner join dbo.n5jednostka on (n5jednostka.idobj = n5produkt.pJednostkaEwid)
where vlist_n5sprzedaz_listPozycje.c_psprzed_pklob = @obiekt_klienta and 
p_idobj not in (select pPopSprzed from n5sprzedaz)

union

select 
10162 as dokument_type,
max(dokument_numer),
max(dokument_idobj),
max(dokument_data),
max(towar_nazwa),
max(towar_idobj),
max(towar_dokladnosc),
max(towar_jm),
sum(pozycja_ilosc),
-1 * sum(pozycja_ilosc) * max(pozycja_cena)
from
(
select 
case p_pdokmag when 0 then p_strnrdok else '' end as dokument_numer  ,
case p_pdokmag when 0 then p_idobj else p_pdokmag end as dokument_idobj ,
p_ddatawyst as dokument_data,
n5produkt.strNazwa as towar_nazwa ,
n5produkt.idobj as towar_idobj ,
n5jednostka.nDokladnosc as towar_dokladnosc ,
n5jednostka.strSkrot as towar_jm ,
case p_pdokmag when 0 then c_curiloscopak else -1*c_curiloscopak end as  pozycja_ilosc,
c_curcenamag as pozycja_cena
from dbo.vlist_n5dokmag_listPozycje
inner join n5produkt on (n5produkt.idobj = vlist_n5dokmag_listPozycje.c_pprodukt )
inner join dbo.n5jednostka on (n5jednostka.idobj = n5produkt.pJednostkaEwid)
where vlist_n5dokmag_listPozycje.c_pdm_pobiektklienta = @obiekt_klienta
) tmp
group by dokument_idobj
) tmp2
order by dokument_data desc

END








GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO


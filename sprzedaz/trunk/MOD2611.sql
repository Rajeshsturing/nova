------------------------------------------------------------
-- skrypt do uruchomienia dla potrzeb modyfikacji MOD2611
------------------------------------------------------------

use navo2002
go

if exists(select * from sys.views where name = 'iow_mod2611')
	drop view iow_mod2611
go

 create view iow_mod2611 as
 select 'typ'=1, 'idtran' = idobj, 'idwaluta'=pWaluta,
 'kwota_dok'=case when pWaluta = 4 
 then curWnEwid
 else
 curWn
 end,
 'kwota_zapl'=case when pWaluta = 4 
 then curWnEwid - CurMaEwid
 else
 curWn - curMa
 end,
 'kurs_dok'=trn_curKurs,
 'kurs_zapl'= 0.0,
 'data_dok' = dDataRozp,
 'data_op' = dDataRozp
 from n5transakcja
 union all
 select 'typ'=2, 'idtrans'=n5transakcja.IdObj, 'idwaluta'=pWaluta, 
 'kwota_dok'=case when pWaluta = 4 
 then curWnEwid
 else
 curWn
 end,
 'kwota_zapl'= trop_curMa,
 'kurs_dok'=n5transakcja.trn_curKurs,
 'kurs_zapl'= trop_curKursOp,
 'data_dok' = n5transakcja.dDataRozp,
 'data_op' = trop_dDataOp
 from n5transakcja_operacja trop
 join n5transakcja on trop_ptransakcja = n5transakcja.idobj
 where trop_wrefDokument_wrt=10121
go

execute [dbo].[n2001_makegrants] 'navo2002user'
go
------------------------------------------------------------

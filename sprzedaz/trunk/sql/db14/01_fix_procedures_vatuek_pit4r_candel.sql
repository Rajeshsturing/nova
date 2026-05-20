---------------------------------------------------------------------------------
-- patch 01 after DB14 (included in upg-db13-db14 2018.07.09.00)
---------------------------------------------------------------------------------
use %DBNAME%
go

if exists (select * from sysobjects where name='n5transakcja_candel')
	drop procedure n5transakcja_candel
go
create procedure n5transakcja_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10214 as integer),idobj from n5poznotaods where pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10143 as integer),idobj from n5vatue where vtue_pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10177 as integer),idobj from n5rozlvat where vat7_pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10137 as integer),idobj from n5pit5l where pt5l_pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pTransakcjaImport=@idobj_par
union
select TOP 5 'typeid'=cast(10227 as integer),idobj from n5istat where istt_pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10156 as integer),idobj from n5pozrata where prat_pTransakcja=@idobj_par
union
--select TOP 5 'typeid'=cast(10241 as integer),idobj from n5vatuek where vtue_pTransakcja=@idobj_par
--union
select TOP 5 'typeid'=cast(10136 as integer),idobj from n5pit5 where pt5_pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10252 as integer),idobj from n5transakcja_operacja where trop_pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10147 as integer),idobj from n5dekret where pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10215 as integer),idobj from n5notaods where pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where plnal_pTransakcjaUS=@idobj_par
union
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where plnal_pTransakcjaZUS51=@idobj_par
union
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where plnal_pTransakcjaZUS52=@idobj_par
union
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where plnal_pTransakcjaZUS53=@idobj_par
union
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where plnal_pTransakcjaInne=@idobj_par
union
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where plnal_pTransakcjaInne2=@idobj_par
union
select TOP 5 'typeid'=cast(10121 as integer),idobj from n5pozplatnosc where pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10138 as integer),idobj from n5pit11 where pt11_pTransakcja=@idobj_par
--union
--select TOP 5 'typeid'=cast(10240 as integer),idobj from n5pit4r where pit4r_pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10135 as integer),idobj from n5pit4 where pt4_pTransakcja=@idobj_par
union
select TOP 5 'typeid'=cast(10203 as integer),idobj from n5rozlcit where pTransakcja=@idobj_par
go
if exists (select * from sysobjects where name='n5dowodksieg_candel')
	drop procedure n5dowodksieg_candel
go
create procedure n5dowodksieg_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10143 as integer),idobj from n5vatue where vtue_pDowKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10177 as integer),idobj from n5rozlvat where vat7_pDowKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10194 as integer),idobj from n5pllistaplac where lppl_pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10137 as integer),idobj from n5pit5l where pt5l_pDowKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10216 as integer),idobj from n5opsrtrw where pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10227 as integer),idobj from n5istat where istt_pDowKsieg=@idobj_par
union
--select TOP 5 'typeid'=cast(10241 as integer),idobj from n5vatuek where vtue_pDowKsieg=@idobj_par
--union
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where wrefSzczegoly=@idobj_par and wrefSzczegoly_wrt=10148
union
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where pDowKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10136 as integer),idobj from n5pit5 where pt5_pDowKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10187 as integer),idobj from n5zlecprod where pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10150 as integer),idobj from n5platnosc where pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10215 as integer),idobj from n5notaods where pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10158 as integer),idobj from n5rapkas where raka_pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10138 as integer),idobj from n5pit11 where pt11_pDowKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10172 as integer),idobj from n5zamowienie where pDowodKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10206 as integer),idobj from n5realprod where pDowodKsieg=@idobj_par
union
--select TOP 5 'typeid'=cast(10240 as integer),idobj from n5pit4r where pit4r_pDowKsieg=@idobj_par
--union
select TOP 5 'typeid'=cast(10135 as integer),idobj from n5pit4 where pt4_pDowKsieg=@idobj_par
union
select TOP 5 'typeid'=cast(10203 as integer),idobj from n5rozlcit where pDowKsieg=@idobj_par
go
if exists (select * from sysobjects where name='n5instytucja_candel')
	drop procedure n5instytucja_candel
go
create procedure n5instytucja_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10146 as integer),idobj from n5konto where wrefPodmiotRozrach=@idobj_par and wrefPodmiotRozrach_wrt=10105
union
select TOP 5 'typeid'=cast(10109 as integer),idobj from n5pracownik where pUrzadSkarbowy=@idobj_par
union
select TOP 5 'typeid'=cast(10143 as integer),idobj from n5vatue where vtue_pUrzadSkarbowy=@idobj_par
union
select TOP 5 'typeid'=cast(10177 as integer),idobj from n5rozlvat where vat7_pUrzadSkarbowy=@idobj_par
union
select TOP 5 'typeid'=cast(10137 as integer),idobj from n5pit5l where pt5l_pUrzadSkarbowy=@idobj_par
union
select TOP 5 'typeid'=cast(10154 as integer),idobj from n5transakcja where wrefPodmiot=@idobj_par and wrefPodmiot_wrt=10105
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pUrzadCelny=@idobj_par
union
select TOP 5 'typeid'=cast(10227 as integer),idobj from n5istat where istt_pUrzadSkarbowy=@idobj_par
union
--select TOP 5 'typeid'=cast(10241 as integer),idobj from n5vatuek where vtue_pUrzadSkarbowy=@idobj_par
--union
select TOP 5 'typeid'=cast(10136 as integer),idobj from n5pit5 where pt5_pUrzadSkarbowy=@idobj_par
union
select TOP 5 'typeid'=cast(10150 as integer),idobj from n5platnosc where wrefPodmiot=@idobj_par and wrefPodmiot_wrt=10105
union
select TOP 5 'typeid'=cast(10110 as integer),idobj from n5firma where pUrzadSkarbowyVAT=@idobj_par
union
select TOP 5 'typeid'=cast(10110 as integer),idobj from n5firma where pUrzadSkarbowyPD=@idobj_par
union
select TOP 5 'typeid'=cast(10110 as integer),idobj from n5firma where pZUS=@idobj_par
union
select TOP 5 'typeid'=cast(10138 as integer),idobj from n5pit11 where pt11_pUrzadSkarbowy=@idobj_par
union
--select TOP 5 'typeid'=cast(10240 as integer),idobj from n5pit4r where pit4r_pUrzadSkarbowy=@idobj_par
--union
select TOP 5 'typeid'=cast(10135 as integer),idobj from n5pit4 where pt4_pUrzadSkarbowy=@idobj_par
union
select TOP 5 'typeid'=cast(10203 as integer),idobj from n5rozlcit where pUrzadSkarbowy=@idobj_par
go

if exists (select * from sysobjects where name='n5zadanie_candel')
	drop procedure n5zadanie_candel
go
create procedure n5zadanie_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10132 as integer),idobj from n5pozsprzedaz where psprzed_pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10143 as integer),idobj from n5vatue where vtue_pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10177 as integer),idobj from n5rozlvat where vat7_pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10137 as integer),idobj from n5pit5l where pt5l_pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10148 as integer),idobj from n5dowodksieg where wrefDokZrod=@idobj_par and wrefDokZrod_wrt=10119
union
select TOP 5 'typeid'=cast(10125 as integer),idobj from n5zadaniezal where wrefZal=@idobj_par and wrefZal_wrt=10119
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10227 as integer),idobj from n5istat where istt_pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10173 as integer),idobj from n5pozzamowienie where pzam_pZadanie=@idobj_par
union
--select TOP 5 'typeid'=cast(10241 as integer),idobj from n5vatuek where vtue_pZadanie=@idobj_par
--union
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where pNadZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where pPopZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10136 as integer),idobj from n5pit5 where pt5_pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10187 as integer),idobj from n5zlecprod where pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10150 as integer),idobj from n5platnosc where pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10235 as integer),idobj from n5plrcp where rcp_pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10175 as integer),idobj from n5pozzakup where pzak_pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10138 as integer),idobj from n5pit11 where pt11_pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10172 as integer),idobj from n5zamowienie where pZadanie=@idobj_par
union
--select TOP 5 'typeid'=cast(10240 as integer),idobj from n5pit4r where pit4r_pZadanie=@idobj_par
--union
select TOP 5 'typeid'=cast(10135 as integer),idobj from n5pit4 where pt4_pZadanie=@idobj_par
union
select TOP 5 'typeid'=cast(10203 as integer),idobj from n5rozlcit where pZadanie=@idobj_par
go

if exists (select * from sysobjects where name='n5uzytkownik_candel')
	drop procedure n5uzytkownik_candel
go
create procedure n5uzytkownik_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10013 as integer),idobj from n5userfile where pUzytkownik=@idobj_par
union
select TOP 5 'typeid'=cast(10166 as integer),idobj from n5doketyk where doet_pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10166 as integer),idobj from n5doketyk where doet_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where sprzed_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10143 as integer),idobj from n5vatue where vtue_pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10143 as integer),idobj from n5vatue where vtue_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10177 as integer),idobj from n5rozlvat where vat7_pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10177 as integer),idobj from n5rozlvat where vat7_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10211 as integer),idobj from n5bwinfo where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10211 as integer),idobj from n5bwinfo where bwi_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10137 as integer),idobj from n5pit5l where pt5l_pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10137 as integer),idobj from n5pit5l where pt5l_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10188 as integer),idobj from n5eventlog where pUser=@idobj_par
union
select TOP 5 'typeid'=cast(10117 as integer),idobj from n5dokument where pUzytkWypoz=@idobj_par
union
select TOP 5 'typeid'=cast(10117 as integer),idobj from n5dokument where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10117 as integer),idobj from n5dokument where dok_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10202 as integer),idobj from n5plnieob where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10202 as integer),idobj from n5plnieob where pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10148 as integer),idobj from n5dowodksieg where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10148 as integer),idobj from n5dowodksieg where dk_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10199 as integer),idobj from n5plumowa where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10199 as integer),idobj from n5plumowa where pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10216 as integer),idobj from n5opsrtrw where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10216 as integer),idobj from n5opsrtrw where opsrtrw_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where dm_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10006 as integer),idobj from n5securityobj where pUser=@idobj_par
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where zak_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10227 as integer),idobj from n5istat where istt_pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10227 as integer),idobj from n5istat where istt_pUzytModyf=@idobj_par
union
--select TOP 5 'typeid'=cast(10241 as integer),idobj from n5vatuek where vtue_pUzytRej=@idobj_par
--union
--select TOP 5 'typeid'=cast(10241 as integer),idobj from n5vatuek where vtue_pUzytModyf=@idobj_par
--union
select TOP 5 'typeid'=cast(10136 as integer),idobj from n5pit5 where pt5_pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10136 as integer),idobj from n5pit5 where pt5_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10187 as integer),idobj from n5zlecprod where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10187 as integer),idobj from n5zlecprod where zlp_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10221 as integer),idobj from n5plpozostale where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10221 as integer),idobj from n5plpozostale where pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10150 as integer),idobj from n5platnosc where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10150 as integer),idobj from n5platnosc where plat_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10201 as integer),idobj from n5plchoroba where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10201 as integer),idobj from n5plchoroba where pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10235 as integer),idobj from n5plrcp where rcp_pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10252 as integer),idobj from n5transakcja_operacja where trop_pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10252 as integer),idobj from n5transakcja_operacja where trop_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10286 as integer),idobj from n5ankieta_toral where ank_pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10011 as integer),idobj from n5userprof where pn5user=@idobj_par
union
select TOP 5 'typeid'=cast(10215 as integer),idobj from n5notaods where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10215 as integer),idobj from n5notaods where nos_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10283 as integer),idobj from n5polecenie_wyjazdu where pws_pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10158 as integer),idobj from n5rapkas where raka_pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10158 as integer),idobj from n5rapkas where raka_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10138 as integer),idobj from n5pit11 where pt11_pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10138 as integer),idobj from n5pit11 where pt11_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10172 as integer),idobj from n5zamowienie where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10172 as integer),idobj from n5zamowienie where zam_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10206 as integer),idobj from n5realprod where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10206 as integer),idobj from n5realprod where realprod_pUzytModyf=@idobj_par
union
--select TOP 5 'typeid'=cast(10240 as integer),idobj from n5pit4r where pit4r_pUzytRej=@idobj_par
--union
--select TOP 5 'typeid'=cast(10240 as integer),idobj from n5pit4r where pit4r_pUzytModyf=@idobj_par
--union
select TOP 5 'typeid'=cast(10135 as integer),idobj from n5pit4 where pt4_pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10135 as integer),idobj from n5pit4 where pt4_pUzytModyf=@idobj_par
union
select TOP 5 'typeid'=cast(10203 as integer),idobj from n5rozlcit where pUzytRej=@idobj_par
union
select TOP 5 'typeid'=cast(10203 as integer),idobj from n5rozlcit where cit2_pUzytModyf=@idobj_par
go
if exists (select * from sysobjects where name='n5schematdekr_candel')
	drop procedure n5schematdekr_candel
go
create procedure n5schematdekr_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10129 as integer),idobj from n5sprzedaz where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10143 as integer),idobj from n5vatue where vtue_pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10177 as integer),idobj from n5rozlvat where vat7_pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10194 as integer),idobj from n5pllistaplac where lppl_pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10137 as integer),idobj from n5pit5l where pt5l_pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10216 as integer),idobj from n5opsrtrw where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10145 as integer),idobj from n5rejestrdok where pDefSchematdekr=@idobj_par
union
select TOP 5 'typeid'=cast(10145 as integer),idobj from n5rejestrdok where rejdok_pDefSchematdekr2=@idobj_par
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10176 as integer),idobj from n5zakup where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10227 as integer),idobj from n5istat where istt_pSchematDekr=@idobj_par
union
--select TOP 5 'typeid'=cast(10241 as integer),idobj from n5vatuek where vtue_pSchematDekr=@idobj_par
--union
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where pSchematDekretacji=@idobj_par
union
select TOP 5 'typeid'=cast(10136 as integer),idobj from n5pit5 where pt5_pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10187 as integer),idobj from n5zlecprod where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10150 as integer),idobj from n5platnosc where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10215 as integer),idobj from n5notaods where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10158 as integer),idobj from n5rapkas where raka_pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10192 as integer),idobj from n5plnaliczenie where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10138 as integer),idobj from n5pit11 where pt11_pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10172 as integer),idobj from n5zamowienie where pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10206 as integer),idobj from n5realprod where pSchematDekr=@idobj_par
union
--select TOP 5 'typeid'=cast(10240 as integer),idobj from n5pit4r where pit4r_pSchematDekr=@idobj_par
--union
select TOP 5 'typeid'=cast(10135 as integer),idobj from n5pit4 where pt4_pSchematDekr=@idobj_par
union
select TOP 5 'typeid'=cast(10203 as integer),idobj from n5rozlcit where pSchematDekr=@idobj_par
go

n2001_makegrants 'navo2002user'
go

---------------------------------------------------------------------------------
---------------------------------------------------------------------------------

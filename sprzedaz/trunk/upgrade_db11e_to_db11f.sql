-- NAVO Enterprise SQL script (drop) --
-- generated: 2013-07-29

--================================================================================================

if exists (select * from sysobjects where name='FK_n5dokmag_n5uzytkownik_10')
	alter table n5dokmag drop constraint FK_n5dokmag_n5uzytkownik_10
go
if exists (select * from sysobjects where name='FK_n5dokmag_n5rejestrdok_13')
	alter table n5dokmag drop constraint FK_n5dokmag_n5rejestrdok_13
go
if exists (select * from sysobjects where name='WRT_n5dokmag_wrefDokHandl_21')
	alter table n5dokmag drop constraint WRT_n5dokmag_wrefDokHandl_21
go
if exists (select * from sysobjects where name='FK_n5dokmag_n5uzytkownik_34')
	alter table n5dokmag drop constraint FK_n5dokmag_n5uzytkownik_34
go

if exists (select * from sysobjects where name='PK_n5dokmag_IdObj')
	alter table n5dokmag drop constraint PK_n5dokmag_IdObj
go
-- table: n5dokmag
if exists (select * from sysobjects where name='n5dokmag_select')
	drop procedure n5dokmag_select
go
if exists (select * from sysobjects where name='n5dokmag_insert')
	drop procedure n5dokmag_insert
go
if exists (select * from sysobjects where name='n5dokmag_update')
	drop procedure n5dokmag_update
go
if exists (select * from sysobjects where name='n5dokmag_delete')
	drop procedure n5dokmag_delete
go
if exists (select * from sysobjects where name='n5dokmag_maxid')
	drop procedure n5dokmag_maxid
go
if exists (select * from sysobjects where name='n5dokmag_candel')
	drop procedure n5dokmag_candel
go
if exists (select * from sysobjects where name='vlist_n5dokmag_listPozycje')
	drop view vlist_n5dokmag_listPozycje
go
if exists (select * from sysobjects where name='vlist_n5dokmag_dm_listEgzemplarze')
	drop view vlist_n5dokmag_dm_listEgzemplarze
go
if exists (select * from sysobjects where name='vlist_n5dokmag_zak_listZalacznik')
	drop view vlist_n5dokmag_zak_listZalacznik
go
-- alter table n5dokmag
sp_rename 'n5dokmag','upg___n5dokmag','OBJECT'
go

CREATE TABLE [dbo].[n5dokmag](
	[IdObj] [int] NOT NULL,
	[VersionId] [int] NOT NULL,
	[strNrDok] [varchar](32) NOT NULL,
	[pKlient] [int] NOT NULL,
	[pKlient_JO] [int] NOT NULL,
	[pKlientPracownik] [int] NOT NULL,
	[pDokMag] [int] NOT NULL,
	[nNumOper] [int] NOT NULL,
	[nTypDok] [int] NOT NULL,
	[dDataWyst] [datetime] NOT NULL,
	[pUzytRej] [int] NOT NULL,
	[strUwagi] [varchar](512) NOT NULL,
	[pRejestrDok] [int] NOT NULL,
	[pDowodKsieg] [int] NOT NULL,
	[pSchematDekr] [int] NOT NULL,
	[curSumaMag] [decimal](12, 2) NOT NULL,
	[curSumaEwid] [decimal](12, 2) NOT NULL,
	[pMagZrod] [int] NOT NULL,
	[pMagDocel] [int] NOT NULL,
	[cAutoCalc] [varchar](1) NOT NULL,
	[wrefDokHandl] [int] NOT NULL,
	[wrefDokHandl_wrt] [int] NOT NULL,
	[strExtra1] [varchar](32) NOT NULL,
	[strExtra2] [varchar](128) NOT NULL,
	[dExtra3] [datetime] NOT NULL,
	[curExtra4] [decimal](12, 2) NOT NULL,
	[curExtra5] [decimal](12, 2) NOT NULL,
	[pKwalifikatorEx] [int] NOT NULL,
	[dDataRezerw] [datetime] NOT NULL,
	[tCzasRezerw] [int] NOT NULL,
	[dm_pSposobDostawy] [int] NOT NULL,
	[dm_strNrDokObcy] [varchar](32) NOT NULL,
	[dm_pUzytModyf] [int] NOT NULL,
	[dm_strNrPartii] [varchar](64) NOT NULL,
	[pDokStatus] [int] NOT NULL,
	pPracownik integer not null,
	pObiektKlienta integer not null

 CONSTRAINT [PK_n5dokmag_IdObj] PRIMARY KEY CLUSTERED 
(
	[IdObj] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

create procedure upd_n5dokmag as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5dokmag(
	IdObj,VersionId,strNrDok,pKlient,pKlient_JO,pKlientPracownik,pDokMag,nNumOper,nTypDok,dDataWyst
	,pUzytRej,strUwagi,pRejestrDok,pDowodKsieg,pSchematDekr,curSumaMag,curSumaEwid
	,pMagZrod,pMagDocel,cAutoCalc,wrefDokHandl,strExtra1,strExtra2,dExtra3
	,curExtra4,curExtra5,pKwalifikatorEx,dDataRezerw,tCzasRezerw,wrefDokHandl_wrt,dm_pSposobDostawy
	,dm_strNrDokObcy,dm_pUzytModyf,dm_strNrPartii,pDokStatus,pPracownik,pObiektKlienta)
select
	IdObj,VersionId,strNrDok,pKlient,pKlient_JO,pKlientPracownik,pDokMag,nNumOper,nTypDok,dDataWyst
	,pUzytRej,strUwagi,pRejestrDok,pDowodKsieg,pSchematDekr,curSumaMag,curSumaEwid
	,pMagZrod,pMagDocel,cAutoCalc,wrefDokHandl,strExtra1,strExtra2,dExtra3
	,curExtra4,curExtra5,pKwalifikatorEx,dDataRezerw,tCzasRezerw,wrefDokHandl_wrt,dm_pSposobDostawy
	,dm_strNrDokObcy,dm_pUzytModyf,dm_strNrPartii,pDokStatus,0,0
from upg___n5dokmag

go
exec upd_n5dokmag
go
drop procedure upd_n5dokmag
go
drop table upg___n5dokmag
go

create view vlist_n5dokmag_listPozycje as select 
'coll_lp'=collections.lp,'p_versionid'=p.VersionId,'p_idobj'=p.IdObj
,'p_strnrdok'=p.strNrDok
,'p_pklient'=p.pKlient
,'p_pklient_jo'=p.pKlient_JO
,'p_pklientpracownik'=p.pKlientPracownik
,'p_pdokmag'=p.pDokMag
,'p_nnumoper'=p.nNumOper
,'p_ntypdok'=p.nTypDok
,'p_ddatawyst'=p.dDataWyst
,'p_puzytrej'=p.pUzytRej
,'p_struwagi'=p.strUwagi
,'p_prejestrdok'=p.pRejestrDok
,'p_pdowodksieg'=p.pDowodKsieg
,'p_pschematdekr'=p.pSchematDekr
,'p_cursumamag'=p.curSumaMag
,'p_cursumaewid'=p.curSumaEwid
,'p_pmagzrod'=p.pMagZrod
,'p_pmagdocel'=p.pMagDocel
,'p_cautocalc'=p.cAutoCalc
,'p_wrefdokhandl'=p.wrefDokHandl
,'p_wrefdokhandl_wrt'=p.wrefDokHandl_wrt
,'p_strextra1'=p.strExtra1
,'p_strextra2'=p.strExtra2
,'p_dextra3'=p.dExtra3
,'p_curextra4'=p.curExtra4
,'p_curextra5'=p.curExtra5
,'p_pkwalifikatorex'=p.pKwalifikatorEx
,'p_ddatarezerw'=p.dDataRezerw
,'p_tczasrezerw'=p.tCzasRezerw
,'p_dm_psposobdostawy'=p.dm_pSposobDostawy
,'p_dm_strnrdokobcy'=p.dm_strNrDokObcy
,'p_dm_puzytmodyf'=p.dm_pUzytModyf
,'p_dm_strnrpartii'=p.dm_strNrPartii
,'p_pdokstatus'=p.pDokStatus
,'p_ppracownik'=p.pPracownik
,'p_pobiektklienta'=p.pObiektKlienta
,'c_versionid'=c.VersionId,'c_idobj'=c.IdObj
,'c_pprodukt'=c.pProdukt
,'c_popak'=c.pOpak
,'c_ntypdok'=c.nTypDok
,'c_pmagzrod'=c.pMagZrod
,'c_pmagdocel'=c.pMagDocel
,'c_pjednopak'=c.pJednOpak
,'c_curiloscopak'=c.curIloscOpak
,'c_pjednewid'=c.pJednEwid
,'c_curiloscewid'=c.curIloscEwid
,'c_curcenamag'=c.curCenaMag
,'c_curcenaewid'=c.curCenaEwid
,'c_curwartmag'=c.curWartMag
,'c_curwartewid'=c.curWartEwid
,'c_nnumopmagdost'=c.nNumOpMagDost
,'c_nlpdost'=c.nLpDost
,'c_struwagi'=c.strUwagi
,'c_strextra1'=c.strExtra1
,'c_strextra2'=c.strExtra2
,'c_dextra3'=c.dExtra3
,'c_curextra4'=c.curExtra4
,'c_curextra5'=c.curExtra5
,'c_pkwalifikatorex'=c.pKwalifikatorEx
,'c_ddatawazn'=c.dDataWazn
,'c_pdm_pobiektklienta'=c.pdm_pObiektKlienta
,'c_pdm_strnrpartii'=c.pdm_strNrPartii
 from n5dokmag as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10162011
 join n5pozdokmag as c on c.idobj = collections.idobj 
 go

create view vlist_n5dokmag_dm_listEgzemplarze as select 
'coll_lp'=collections.lp,'p_versionid'=p.VersionId,'p_idobj'=p.IdObj
,'p_strnrdok'=p.strNrDok
,'p_pklient'=p.pKlient
,'p_pklient_jo'=p.pKlient_JO
,'p_pklientpracownik'=p.pKlientPracownik
,'p_pdokmag'=p.pDokMag
,'p_nnumoper'=p.nNumOper
,'p_ntypdok'=p.nTypDok
,'p_ddatawyst'=p.dDataWyst
,'p_puzytrej'=p.pUzytRej
,'p_struwagi'=p.strUwagi
,'p_prejestrdok'=p.pRejestrDok
,'p_pdowodksieg'=p.pDowodKsieg
,'p_pschematdekr'=p.pSchematDekr
,'p_cursumamag'=p.curSumaMag
,'p_cursumaewid'=p.curSumaEwid
,'p_pmagzrod'=p.pMagZrod
,'p_pmagdocel'=p.pMagDocel
,'p_cautocalc'=p.cAutoCalc
,'p_wrefdokhandl'=p.wrefDokHandl
,'p_wrefdokhandl_wrt'=p.wrefDokHandl_wrt
,'p_strextra1'=p.strExtra1
,'p_strextra2'=p.strExtra2
,'p_dextra3'=p.dExtra3
,'p_curextra4'=p.curExtra4
,'p_curextra5'=p.curExtra5
,'p_pkwalifikatorex'=p.pKwalifikatorEx
,'p_ddatarezerw'=p.dDataRezerw
,'p_tczasrezerw'=p.tCzasRezerw
,'p_dm_psposobdostawy'=p.dm_pSposobDostawy
,'p_dm_strnrdokobcy'=p.dm_strNrDokObcy
,'p_dm_puzytmodyf'=p.dm_pUzytModyf
,'p_dm_strnrpartii'=p.dm_strNrPartii
,'p_pdokstatus'=p.pDokStatus
,'p_ppracownik'=p.pPracownik
,'p_pobiektklienta'=p.pObiektKlienta
,'c_versionid'=c.VersionId,'c_idobj'=c.IdObj
,'c_pdmeg_pegz'=c.pdmeg_pEgz
 from n5dokmag as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10162030
 join n5pozdokmag_egz as c on c.idobj = collections.idobj 
 go

create view vlist_n5dokmag_zak_listZalacznik as select 
'coll_lp'=collections.lp,'p_versionid'=p.VersionId,'p_idobj'=p.IdObj
,'p_strnrdok'=p.strNrDok
,'p_pklient'=p.pKlient
,'p_pklient_jo'=p.pKlient_JO
,'p_pklientpracownik'=p.pKlientPracownik
,'p_pdokmag'=p.pDokMag
,'p_nnumoper'=p.nNumOper
,'p_ntypdok'=p.nTypDok
,'p_ddatawyst'=p.dDataWyst
,'p_puzytrej'=p.pUzytRej
,'p_struwagi'=p.strUwagi
,'p_prejestrdok'=p.pRejestrDok
,'p_pdowodksieg'=p.pDowodKsieg
,'p_pschematdekr'=p.pSchematDekr
,'p_cursumamag'=p.curSumaMag
,'p_cursumaewid'=p.curSumaEwid
,'p_pmagzrod'=p.pMagZrod
,'p_pmagdocel'=p.pMagDocel
,'p_cautocalc'=p.cAutoCalc
,'p_wrefdokhandl'=p.wrefDokHandl
,'p_wrefdokhandl_wrt'=p.wrefDokHandl_wrt
,'p_strextra1'=p.strExtra1
,'p_strextra2'=p.strExtra2
,'p_dextra3'=p.dExtra3
,'p_curextra4'=p.curExtra4
,'p_curextra5'=p.curExtra5
,'p_pkwalifikatorex'=p.pKwalifikatorEx
,'p_ddatarezerw'=p.dDataRezerw
,'p_tczasrezerw'=p.tCzasRezerw
,'p_dm_psposobdostawy'=p.dm_pSposobDostawy
,'p_dm_strnrdokobcy'=p.dm_strNrDokObcy
,'p_dm_puzytmodyf'=p.dm_pUzytModyf
,'p_dm_strnrpartii'=p.dm_strNrPartii
,'p_pdokstatus'=p.pDokStatus
,'p_ppracownik'=p.pPracownik
,'p_pobiektklienta'=p.pObiektKlienta
,'c_versionid'=c.VersionId,'c_idobj'=c.IdObj
,'c_pdza_pdokument'=c.pdza_pDokument
 from n5dokmag as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10162035
 join n5pozdok_zalacznik as c on c.idobj = collections.idobj 
 go

-- table: n5dokmag
create procedure n5dokmag_select(@idobj_par integer,@versionid_par integer output,
	@strNrDok_par varchar(32) output,
	@pKlient_par integer output,
	@pKlient_JO_par integer output,
	@pKlientPracownik_par integer output,
	@pDokMag_par integer output,
	@nNumOper_par integer output,
	@nTypDok_par integer output,
	@dDataWyst_par datetime output,
	@pUzytRej_par integer output,
	@strUwagi_par varchar(512) output,
	@pRejestrDok_par integer output,
	@pDowodKsieg_par integer output,
	@pSchematDekr_par integer output,
	@curSumaMag_par decimal(12,2) output,
	@curSumaEwid_par decimal(12,2) output,
	@pMagZrod_par integer output,
	@pMagDocel_par integer output,
	@cAutoCalc_par varchar(1) output,
	@wrefDokHandl_par integer output,
	@wrefDokHandl_wrt_par integer output,
	@strExtra1_par varchar(32) output,
	@strExtra2_par varchar(128) output,
	@dExtra3_par datetime output,
	@curExtra4_par decimal(12,2) output,
	@curExtra5_par decimal(12,2) output,
	@pKwalifikatorEx_par integer output,
	@dDataRezerw_par datetime output,
	@tCzasRezerw_par integer output,
	@dm_pSposobDostawy_par integer output,
	@dm_strNrDokObcy_par varchar(32) output,
	@dm_pUzytModyf_par integer output,
	@dm_strNrPartii_par varchar(64) output,
	@pDokStatus_par integer output,
	@pPracownik_par integer output,
	@pObiektKlienta_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNrDok_par=strNrDok,
	@pKlient_par=pKlient,
	@pKlient_JO_par=pKlient_JO,
	@pKlientPracownik_par=pKlientPracownik,
	@pDokMag_par=pDokMag,
	@nNumOper_par=nNumOper,
	@nTypDok_par=nTypDok,
	@dDataWyst_par=dDataWyst,
	@pUzytRej_par=pUzytRej,
	@strUwagi_par=strUwagi,
	@pRejestrDok_par=pRejestrDok,
	@pDowodKsieg_par=pDowodKsieg,
	@pSchematDekr_par=pSchematDekr,
	@curSumaMag_par=curSumaMag,
	@curSumaEwid_par=curSumaEwid,
	@pMagZrod_par=pMagZrod,
	@pMagDocel_par=pMagDocel,
	@cAutoCalc_par=cAutoCalc,
	@wrefDokHandl_par=wrefDokHandl,
	@wrefDokHandl_wrt_par=wrefDokHandl_wrt,
	@strExtra1_par=strExtra1,
	@strExtra2_par=strExtra2,
	@dExtra3_par=dExtra3,
	@curExtra4_par=curExtra4,
	@curExtra5_par=curExtra5,
	@pKwalifikatorEx_par=pKwalifikatorEx,
	@dDataRezerw_par=dDataRezerw,
	@tCzasRezerw_par=tCzasRezerw,
	@dm_pSposobDostawy_par=dm_pSposobDostawy,
	@dm_strNrDokObcy_par=dm_strNrDokObcy,
	@dm_pUzytModyf_par=dm_pUzytModyf,
	@dm_strNrPartii_par=dm_strNrPartii,
	@pDokStatus_par=pDokStatus,
	@pPracownik_par=pPracownik,
	@pObiektKlienta_par=pObiektKlienta from n5dokmag where IdObj=@idobj_par
return @@rowcount
go

create procedure n5dokmag_insert(@idobj_par integer,@versionid_par integer,
	@strNrDok_par varchar(32),
	@pKlient_par integer,
	@pKlient_JO_par integer,
	@pKlientPracownik_par integer,
	@pDokMag_par integer,
	@nNumOper_par integer,
	@nTypDok_par integer,
	@dDataWyst_par datetime,
	@pUzytRej_par integer,
	@strUwagi_par varchar(512),
	@pRejestrDok_par integer,
	@pDowodKsieg_par integer,
	@pSchematDekr_par integer,
	@curSumaMag_par decimal(12,2),
	@curSumaEwid_par decimal(12,2),
	@pMagZrod_par integer,
	@pMagDocel_par integer,
	@cAutoCalc_par varchar(1),
	@wrefDokHandl_par integer,
	@wrefDokHandl_wrt_par integer,
	@strExtra1_par varchar(32),
	@strExtra2_par varchar(128),
	@dExtra3_par datetime,
	@curExtra4_par decimal(12,2),
	@curExtra5_par decimal(12,2),
	@pKwalifikatorEx_par integer,
	@dDataRezerw_par datetime,
	@tCzasRezerw_par integer,
	@dm_pSposobDostawy_par integer,
	@dm_strNrDokObcy_par varchar(32),
	@dm_pUzytModyf_par integer,
	@dm_strNrPartii_par varchar(64),
	@pDokStatus_par integer,
	@pPracownik_par integer,
	@pObiektKlienta_par integer) with encryption as 
	insert into n5dokmag values(@idobj_par,@versionid_par,
	@strNrDok_par,
	@pKlient_par,
	@pKlient_JO_par,
	@pKlientPracownik_par,
	@pDokMag_par,
	@nNumOper_par,
	@nTypDok_par,
	@dDataWyst_par,
	@pUzytRej_par,
	@strUwagi_par,
	@pRejestrDok_par,
	@pDowodKsieg_par,
	@pSchematDekr_par,
	@curSumaMag_par,
	@curSumaEwid_par,
	@pMagZrod_par,
	@pMagDocel_par,
	@cAutoCalc_par,
	@wrefDokHandl_par,
	@wrefDokHandl_wrt_par,
	@strExtra1_par,
	@strExtra2_par,
	@dExtra3_par,
	@curExtra4_par,
	@curExtra5_par,
	@pKwalifikatorEx_par,
	@dDataRezerw_par,
	@tCzasRezerw_par,
	@dm_pSposobDostawy_par,
	@dm_strNrDokObcy_par,
	@dm_pUzytModyf_par,
	@dm_strNrPartii_par,
	@pDokStatus_par,
	@pPracownik_par,
	@pObiektKlienta_par)
return @@rowcount
go

create procedure n5dokmag_update(@idobj_par integer,@versionid_par integer,
	@strNrDok_par varchar(32),
	@pKlient_par integer,
	@pKlient_JO_par integer,
	@pKlientPracownik_par integer,
	@pDokMag_par integer,
	@nNumOper_par integer,
	@nTypDok_par integer,
	@dDataWyst_par datetime,
	@pUzytRej_par integer,
	@strUwagi_par varchar(512),
	@pRejestrDok_par integer,
	@pDowodKsieg_par integer,
	@pSchematDekr_par integer,
	@curSumaMag_par decimal(12,2),
	@curSumaEwid_par decimal(12,2),
	@pMagZrod_par integer,
	@pMagDocel_par integer,
	@cAutoCalc_par varchar(1),
	@wrefDokHandl_par integer,
	@wrefDokHandl_wrt_par integer,
	@strExtra1_par varchar(32),
	@strExtra2_par varchar(128),
	@dExtra3_par datetime,
	@curExtra4_par decimal(12,2),
	@curExtra5_par decimal(12,2),
	@pKwalifikatorEx_par integer,
	@dDataRezerw_par datetime,
	@tCzasRezerw_par integer,
	@dm_pSposobDostawy_par integer,
	@dm_strNrDokObcy_par varchar(32),
	@dm_pUzytModyf_par integer,
	@dm_strNrPartii_par varchar(64),
	@pDokStatus_par integer,
	@pPracownik_par integer,
	@pObiektKlienta_par integer) with encryption as 
	update n5dokmag set VersionId=@versionid_par,
	strNrDok=@strNrDok_par,
	pKlient=@pKlient_par,
	pKlient_JO=@pKlient_JO_par,
	pKlientPracownik=@pKlientPracownik_par,
	pDokMag=@pDokMag_par,
	nNumOper=@nNumOper_par,
	nTypDok=@nTypDok_par,
	dDataWyst=@dDataWyst_par,
	pUzytRej=@pUzytRej_par,
	strUwagi=@strUwagi_par,
	pRejestrDok=@pRejestrDok_par,
	pDowodKsieg=@pDowodKsieg_par,
	pSchematDekr=@pSchematDekr_par,
	curSumaMag=@curSumaMag_par,
	curSumaEwid=@curSumaEwid_par,
	pMagZrod=@pMagZrod_par,
	pMagDocel=@pMagDocel_par,
	cAutoCalc=@cAutoCalc_par,
	wrefDokHandl=@wrefDokHandl_par,
	wrefDokHandl_wrt=@wrefDokHandl_wrt_par,
	strExtra1=@strExtra1_par,
	strExtra2=@strExtra2_par,
	dExtra3=@dExtra3_par,
	curExtra4=@curExtra4_par,
	curExtra5=@curExtra5_par,
	pKwalifikatorEx=@pKwalifikatorEx_par,
	dDataRezerw=@dDataRezerw_par,
	tCzasRezerw=@tCzasRezerw_par,
	dm_pSposobDostawy=@dm_pSposobDostawy_par,
	dm_strNrDokObcy=@dm_strNrDokObcy_par,
	dm_pUzytModyf=@dm_pUzytModyf_par,
	dm_strNrPartii=@dm_strNrPartii_par,
	pDokStatus=@pDokStatus_par,
	pPracownik=@pPracownik_par,
	pObiektKlienta=@pObiektKlienta_par
	where idobj=@idobj_par
return @@rowcount
go

create procedure n5dokmag_delete(@idobj_par integer) with encryption as 
	delete from n5dokmag where idobj=@idobj_par
return @@rowcount
go

create procedure n5dokmag_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5dokmag
go

create procedure n5dokmag_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10166 as integer),idobj from n5doketyk where doet_pDokMag=@idobj_par
union
select TOP 5 'typeid'=cast(10148 as integer),idobj from n5dowodksieg where wrefDokZrod=@idobj_par and wrefDokZrod_wrt=10162
union
select TOP 5 'typeid'=cast(10162 as integer),idobj from n5dokmag where pDokMag=@idobj_par
union
select TOP 5 'typeid'=cast(10119 as integer),idobj from n5zadanie where wrefSzczegoly=@idobj_par and wrefSzczegoly_wrt=10162
union
select TOP 5 'typeid'=cast(10289 as integer),idobj from n5inwmag where im_pIR=@idobj_par
union
select TOP 5 'typeid'=cast(10289 as integer),idobj from n5inwmag where im_pIP=@idobj_par
union
select TOP 5 'typeid'=cast(10274 as integer),idobj from n5prop where prop_pDokMag=@idobj_par
union
select TOP 5 'typeid'=cast(10169 as integer),idobj from n5proglojal where proloj_pDokMag=@idobj_par
go

alter table n5dokmag add constraint FK_n5dokmag_n5uzytkownik_10 foreign key (pUzytRej ) references n5uzytkownik ( IdObj )
go
alter table n5dokmag add constraint FK_n5dokmag_n5rejestrdok_13 foreign key (pRejestrDok ) references n5rejestrdok ( IdObj )
go
alter table n5dokmag add constraint WRT_n5dokmag_wrefDokHandl_21 check (
	wrefDokHandl_wrt=0 or 
	wrefDokHandl_wrt=10129 or 
	wrefDokHandl_wrt=10172 or 
	wrefDokHandl_wrt=10176 or 
	wrefDokHandl_wrt=10187
)
go
alter table n5dokmag add constraint FK_n5dokmag_n5uzytkownik_34 foreign key (dm_pUzytModyf ) references n5uzytkownik ( IdObj )
go
--================================================================================================
--================================================================================================
if exists (select * from sysobjects where name='FK_n5pozprojekt_abas_n5produkt_2')
	alter table n5pozprojekt_abas drop constraint FK_n5pozprojekt_abas_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5egzemplarz_n5produkt_2')
	alter table n5egzemplarz drop constraint FK_n5egzemplarz_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5ptstan_n5produkt_2')
	alter table n5ptstan drop constraint FK_n5ptstan_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5gmop_n5produkt_8')
	alter table n5gmop drop constraint FK_n5gmop_n5produkt_8
go
if exists (select * from sysobjects where name='FK_n5klient_produkt_n5produkt_3')
	alter table n5klient_produkt drop constraint FK_n5klient_produkt_n5produkt_3
go
if exists (select * from sysobjects where name='FK_n5ptop_n5produkt_8')
	alter table n5ptop drop constraint FK_n5ptop_n5produkt_8
go
if exists (select * from sysobjects where name='FK_n5pozdokprod_n5produkt_2')
	alter table n5pozdokprod drop constraint FK_n5pozdokprod_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5pozdoketyk_n5produkt_3')
	alter table n5pozdoketyk drop constraint FK_n5pozdoketyk_n5produkt_3
go
if exists (select * from sysobjects where name='FK_n5gmstan_n5produkt_2')
	alter table n5gmstan drop constraint FK_n5gmstan_n5produkt_2
go

if exists (select * from sysobjects where name='FK_n5pozzakup_n5produkt_2')
	alter table n5pozzakup drop constraint FK_n5pozzakup_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5pozdokmag_n5produkt_2')
	alter table n5pozdokmag drop constraint FK_n5pozdokmag_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5pozsprzedaz_n5produkt_2')
	alter table n5pozsprzedaz drop constraint FK_n5pozsprzedaz_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5pozrealprod_n5produkt_2')
	alter table n5pozrealprod drop constraint FK_n5pozrealprod_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5pozzamowienie_n5produkt_2')
	alter table n5pozzamowienie drop constraint FK_n5pozzamowienie_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5pozrecepta_n5produkt_2')
	alter table n5pozrecepta drop constraint FK_n5pozrecepta_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5pozzlecprod_n5produkt_2')
	alter table n5pozzlecprod drop constraint FK_n5pozzlecprod_n5produkt_2
go
if exists (select * from sysobjects where name='FK_n5produkt_n5jednostka_11')
	alter table n5produkt drop constraint FK_n5produkt_n5jednostka_11
go
if exists (select * from sysobjects where name='ENUM_n5produkt_eAktywny_12')
	alter table n5produkt drop constraint ENUM_n5produkt_eAktywny_12
go
if exists (select * from sysobjects where name='FK_n5produkt_n5grupaproduktow_14')
	alter table n5produkt drop constraint FK_n5produkt_n5grupaproduktow_14
go

if exists (select * from sysobjects where name='ENUM_n5produkt_eRodzaj_19')
	alter table n5produkt drop constraint ENUM_n5produkt_eRodzaj_19
go
if exists (select * from sysobjects where name='PK_n5produkt_IdObj')
	alter table n5produkt drop constraint PK_n5produkt_IdObj
go
if exists (select * from sysobjects where name='ENUM_n5produkt_eVAT_7')
	alter table n5produkt drop constraint ENUM_n5produkt_eVAT_7
go
-- table: n5produkt
if exists (select * from sysobjects where name='n5produkt_select')
	drop procedure n5produkt_select
go
if exists (select * from sysobjects where name='n5produkt_insert')
	drop procedure n5produkt_insert
go
if exists (select * from sysobjects where name='n5produkt_update')
	drop procedure n5produkt_update
go
if exists (select * from sysobjects where name='n5produkt_delete')
	drop procedure n5produkt_delete
go
if exists (select * from sysobjects where name='n5produkt_maxid')
	drop procedure n5produkt_maxid
go
if exists (select * from sysobjects where name='n5produkt_candel')
	drop procedure n5produkt_candel
go
if exists (select * from sysobjects where name='vlist_n5produkt_listOpakowania')
	drop view vlist_n5produkt_listOpakowania
go
---------------------------------------------------------------------------------------
-- alter table n5produkt
sp_rename 'n5produkt','upg___n5produkt','OBJECT'
go
create table n5produkt
(
	IdObj integer not null,
	VersionId integer not null,
	strNazwa varchar(128) not null,
	strNazwaMiedzynarodowa varchar(128) not null,
	strIndeks varchar(32) not null,
	prod_pKodCelny integer not null,
	strKodPKWiU varchar(32) not null,
	eVAT integer not null,
	strOpis varchar(512) not null,
	pUlotka integer not null,
	pInstrukcja integer not null,
	pJednostkaEwid integer not null,
	eAktywny integer not null,
	-- [virtual] listOpakowania,
	pGrupaProd integer not null,
	strCecha1 varchar(128) not null,
	strCecha2 varchar(128) not null,
	strCecha3 varchar(128) not null,
	-- [virtual] fZdjecie,
	eRodzaj integer not null,
	prod_cWyrob varchar(1) not null,
	prod_cSurowiec varchar(1) not null,
	prod_pDostawca integer not null,
	prod_cRolny varchar(1) not null,
	prod_strCN varchar(32) not null,
	prod_strCPC varchar(32) not null,
	prod_strNazwaObcojezyczna1 varchar(128) not null,
	prod_strNazwaObcojezyczna2 varchar(128) not null,
	prod_strNazwaObcojezyczna3 varchar(128) not null,
	prod_pKrajPoch integer not null,
	prod_cCheckPrice varchar(1) not null,
	prod_nCzasDostawy integer not null,
	prod_cCzasDostawyUwzglednij varchar(1) not null,
	prod_pPaletaKolorow integer not null,
	prod_pTabelaRozmiarow integer not null,
	prod_iDataWaznosci integer not null,
	prod_iNrFundRolny integer not null,
	prod_pProdMag integer not null,
	prod_strPKWiU2008 varchar(32) not null,
	prod_nVAT integer not null,
	prod_cProdEtyk varchar(1) not null,
	prod_pPracownik integer not null,
	prod_cTowarRot varchar(1) not null,
	prod_cTowarZam varchar(1) not null,
	prod_curMinWartZam decimal(12,2) not null,
	prod_strOpisZam varchar(64) not null,
	prod_cDoSprzed varchar(1) not null,
	prod_pZamiennik1 integer not null,
	prod_pZamiennik2 integer not null,
	prod_pZamiennik3 integer not null,
	prod_pZamiennik4 integer not null,
	prod_pZamiennik5 integer not null
)
go
create procedure upd_n5produkt as 
-- HINT - tutaj mozna wstawic procedury
-----insert ---------------------
insert into n5produkt(
	IdObj,VersionId,strNazwa,strNazwaMiedzynarodowa,strIndeks,prod_pKodCelny,strKodPKWiU,eVAT,strOpis,pUlotka
	,pInstrukcja,pJednostkaEwid,eAktywny,pGrupaProd,strCecha1,strCecha2,strCecha3
	,eRodzaj,prod_cWyrob,prod_cSurowiec,prod_pDostawca,prod_cRolny,prod_strCN,prod_strCPC
	,prod_strNazwaObcojezyczna1,prod_strNazwaObcojezyczna2,prod_strNazwaObcojezyczna3,prod_pKrajPoch,prod_cCheckPrice,prod_nCzasDostawy,prod_cCzasDostawyUwzglednij,prod_pPaletaKolorow
	,prod_pTabelaRozmiarow,prod_iDataWaznosci,prod_iNrFundRolny,prod_pProdMag,prod_strPKWiU2008,prod_nVAT,prod_cProdEtyk,prod_pPracownik
	,prod_cTowarRot,prod_cTowarZam,prod_curMinWartZam,prod_strOpisZam,prod_cDoSprzed,prod_pZamiennik1,prod_pZamiennik2,prod_pZamiennik3
	,prod_pZamiennik4,prod_pZamiennik5)
select
	IdObj,VersionId,strNazwa,strNazwaMiedzynarodowa,strIndeks,prod_pKodCelny,strKodPKWiU,eVAT,strOpis,pUlotka
	,pInstrukcja,pJednostkaEwid,eAktywny,pGrupaProd,strCecha1,strCecha2,strCecha3
	,eRodzaj,prod_cWyrob,prod_cSurowiec,prod_pDostawca,prod_cRolny,prod_strCN,prod_strCPC
	,prod_strNazwaObcojezyczna1,prod_strNazwaObcojezyczna2,prod_strNazwaObcojezyczna3,prod_pKrajPoch,prod_cCheckPrice,prod_nCzasDostawy,prod_cCzasDostawyUwzglednij,prod_pPaletaKolorow
	,prod_pTabelaRozmiarow,prod_iDataWaznosci,prod_iNrFundRolny,prod_pProdMag,prod_strPKWiU2008,prod_nVAT,prod_cProdEtyk,prod_pPracownik
	,prod_cTowarRot,prod_cTowarZam,prod_curMinWartZam,prod_strOpisZam,prod_cDoSprzed,0,0,0
	,0,0
from upg___n5produkt
go
exec upd_n5produkt
go
drop procedure upd_n5produkt
go
drop table upg___n5produkt
go

---------------------------------------------------------------------------------------
alter table n5produkt add constraint PK_n5produkt_IdObj primary key clustered (IdObj)
go
alter table n5produkt add constraint ENUM_n5produkt_eVAT_7 check (
eVAT between 0 and 14
)
go
alter table n5produkt add constraint FK_n5produkt_n5jednostka_11 foreign key (pJednostkaEwid ) references n5jednostka ( IdObj )
go
alter table n5produkt add constraint ENUM_n5produkt_eAktywny_12 check (
eAktywny between 0 and 2
)
go
alter table n5produkt add constraint FK_n5produkt_n5grupaproduktow_14 foreign key (pGrupaProd ) references n5grupaproduktow ( IdObj )
go
alter table n5produkt add constraint ENUM_n5produkt_eRodzaj_19 check (
eRodzaj between 0 and 2
)
go
alter table n5pozzakup add constraint FK_n5pozzakup_n5produkt_2 foreign key (pProdukt ) references n5produkt ( IdObj )
go
alter table n5pozdokmag add constraint FK_n5pozdokmag_n5produkt_2 foreign key (pProdukt ) references n5produkt ( IdObj )
go
alter table n5pozsprzedaz add constraint FK_n5pozsprzedaz_n5produkt_2 foreign key (pProdukt ) references n5produkt ( IdObj )
go
alter table n5pozrealprod add constraint FK_n5pozrealprod_n5produkt_2 foreign key (pProdukt ) references n5produkt ( IdObj )
go
alter table n5pozzamowienie add constraint FK_n5pozzamowienie_n5produkt_2 foreign key (pProdukt ) references n5produkt ( IdObj )
go
alter table n5pozrecepta add constraint FK_n5pozrecepta_n5produkt_2 foreign key (pProdukt ) references n5produkt ( IdObj )
go
alter table n5pozzlecprod add constraint FK_n5pozzlecprod_n5produkt_2 foreign key (pProdukt ) references n5produkt ( IdObj )
go


alter table n5egzemplarz add constraint FK_n5egzemplarz_n5produkt_2 foreign key (egze_pProdukt ) references n5produkt ( IdObj )
go
alter table n5ptstan add constraint FK_n5ptstan_n5produkt_2 foreign key (gms_pProd ) references n5produkt ( IdObj )
go
alter table n5gmop add constraint FK_n5gmop_n5produkt_8 foreign key (gmo_pProd ) references n5produkt ( IdObj )
go
alter table n5klient_produkt add constraint FK_n5klient_produkt_n5produkt_3 foreign key (klpr_pProdukt ) references n5produkt ( IdObj )
go
alter table n5ptop add constraint FK_n5ptop_n5produkt_8 foreign key (gmo_pProd ) references n5produkt ( IdObj )
go
alter table n5pozdokprod add constraint FK_n5pozdokprod_n5produkt_2 foreign key (pdp_pProdukt ) references n5produkt ( IdObj )
go
alter table n5pozdoketyk add constraint FK_n5pozdoketyk_n5produkt_3 foreign key (pdet_pWyrob ) references n5produkt ( IdObj )
go
alter table n5gmstan add constraint FK_n5gmstan_n5produkt_2 foreign key (gms_pProd ) references n5produkt ( IdObj )
go
alter table n5pozprojekt_abas add constraint FK_n5pozprojekt_abas_n5produkt_2 foreign key (pproj_pProdukt ) references n5produkt ( IdObj )
go
-- table: n5produkt
create procedure n5produkt_select(@idobj_par integer,@versionid_par integer output,
	@strNazwa_par varchar(128) output,
	@strNazwaMiedzynarodowa_par varchar(128) output,
	@strIndeks_par varchar(32) output,
	@prod_pKodCelny_par integer output,
	@strKodPKWiU_par varchar(32) output,
	@eVAT_par integer output,
	@strOpis_par varchar(512) output,
	@pUlotka_par integer output,
	@pInstrukcja_par integer output,
	@pJednostkaEwid_par integer output,
	@eAktywny_par integer output,
	@pGrupaProd_par integer output,
	@strCecha1_par varchar(128) output,
	@strCecha2_par varchar(128) output,
	@strCecha3_par varchar(128) output,
	@eRodzaj_par integer output,
	@prod_cWyrob_par varchar(1) output,
	@prod_cSurowiec_par varchar(1) output,
	@prod_pDostawca_par integer output,
	@prod_cRolny_par varchar(1) output,
	@prod_strCN_par varchar(32) output,
	@prod_strCPC_par varchar(32) output,
	@prod_strNazwaObcojezyczna1_par varchar(128) output,
	@prod_strNazwaObcojezyczna2_par varchar(128) output,
	@prod_strNazwaObcojezyczna3_par varchar(128) output,
	@prod_pKrajPoch_par integer output,
	@prod_cCheckPrice_par varchar(1) output,
	@prod_nCzasDostawy_par integer output,
	@prod_cCzasDostawyUwzglednij_par varchar(1) output,
	@prod_pPaletaKolorow_par integer output,
	@prod_pTabelaRozmiarow_par integer output,
	@prod_iDataWaznosci_par integer output,
	@prod_iNrFundRolny_par integer output,
	@prod_pProdMag_par integer output,
	@prod_strPKWiU2008_par varchar(32) output,
	@prod_nVAT_par integer output,
	@prod_cProdEtyk_par varchar(1) output,
	@prod_pPracownik_par integer output,
	@prod_cTowarRot_par varchar(1) output,
	@prod_cTowarZam_par varchar(1) output,
	@prod_curMinWartZam_par decimal(12,2) output,
	@prod_strOpisZam_par varchar(64) output,
	@prod_cDoSprzed_par varchar(1) output,
	@prod_pZamiennik1_par integer output,
	@prod_pZamiennik2_par integer output,
	@prod_pZamiennik3_par integer output,
	@prod_pZamiennik4_par integer output,
	@prod_pZamiennik5_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNazwa_par=strNazwa,
	@strNazwaMiedzynarodowa_par=strNazwaMiedzynarodowa,
	@strIndeks_par=strIndeks,
	@prod_pKodCelny_par=prod_pKodCelny,
	@strKodPKWiU_par=strKodPKWiU,
	@eVAT_par=eVAT,
	@strOpis_par=strOpis,
	@pUlotka_par=pUlotka,
	@pInstrukcja_par=pInstrukcja,
	@pJednostkaEwid_par=pJednostkaEwid,
	@eAktywny_par=eAktywny,
	@pGrupaProd_par=pGrupaProd,
	@strCecha1_par=strCecha1,
	@strCecha2_par=strCecha2,
	@strCecha3_par=strCecha3,
	@eRodzaj_par=eRodzaj,
	@prod_cWyrob_par=prod_cWyrob,
	@prod_cSurowiec_par=prod_cSurowiec,
	@prod_pDostawca_par=prod_pDostawca,
	@prod_cRolny_par=prod_cRolny,
	@prod_strCN_par=prod_strCN,
	@prod_strCPC_par=prod_strCPC,
	@prod_strNazwaObcojezyczna1_par=prod_strNazwaObcojezyczna1,
	@prod_strNazwaObcojezyczna2_par=prod_strNazwaObcojezyczna2,
	@prod_strNazwaObcojezyczna3_par=prod_strNazwaObcojezyczna3,
	@prod_pKrajPoch_par=prod_pKrajPoch,
	@prod_cCheckPrice_par=prod_cCheckPrice,
	@prod_nCzasDostawy_par=prod_nCzasDostawy,
	@prod_cCzasDostawyUwzglednij_par=prod_cCzasDostawyUwzglednij,
	@prod_pPaletaKolorow_par=prod_pPaletaKolorow,
	@prod_pTabelaRozmiarow_par=prod_pTabelaRozmiarow,
	@prod_iDataWaznosci_par=prod_iDataWaznosci,
	@prod_iNrFundRolny_par=prod_iNrFundRolny,
	@prod_pProdMag_par=prod_pProdMag,
	@prod_strPKWiU2008_par=prod_strPKWiU2008,
	@prod_nVAT_par=prod_nVAT,
	@prod_cProdEtyk_par=prod_cProdEtyk,
	@prod_pPracownik_par=prod_pPracownik,
	@prod_cTowarRot_par=prod_cTowarRot,
	@prod_cTowarZam_par=prod_cTowarZam,
	@prod_curMinWartZam_par=prod_curMinWartZam,
	@prod_strOpisZam_par=prod_strOpisZam,
	@prod_cDoSprzed_par=prod_cDoSprzed,
	@prod_pZamiennik1_par=prod_pZamiennik1,
	@prod_pZamiennik2_par=prod_pZamiennik2,
	@prod_pZamiennik3_par=prod_pZamiennik3,
	@prod_pZamiennik4_par=prod_pZamiennik4,
	@prod_pZamiennik5_par=prod_pZamiennik5 from n5produkt where IdObj=@idobj_par
return @@rowcount
go

create procedure n5produkt_insert(@idobj_par integer,@versionid_par integer,
	@strNazwa_par varchar(128),
	@strNazwaMiedzynarodowa_par varchar(128),
	@strIndeks_par varchar(32),
	@prod_pKodCelny_par integer,
	@strKodPKWiU_par varchar(32),
	@eVAT_par integer,
	@strOpis_par varchar(512),
	@pUlotka_par integer,
	@pInstrukcja_par integer,
	@pJednostkaEwid_par integer,
	@eAktywny_par integer,
	@pGrupaProd_par integer,
	@strCecha1_par varchar(128),
	@strCecha2_par varchar(128),
	@strCecha3_par varchar(128),
	@eRodzaj_par integer,
	@prod_cWyrob_par varchar(1),
	@prod_cSurowiec_par varchar(1),
	@prod_pDostawca_par integer,
	@prod_cRolny_par varchar(1),
	@prod_strCN_par varchar(32),
	@prod_strCPC_par varchar(32),
	@prod_strNazwaObcojezyczna1_par varchar(128),
	@prod_strNazwaObcojezyczna2_par varchar(128),
	@prod_strNazwaObcojezyczna3_par varchar(128),
	@prod_pKrajPoch_par integer,
	@prod_cCheckPrice_par varchar(1),
	@prod_nCzasDostawy_par integer,
	@prod_cCzasDostawyUwzglednij_par varchar(1),
	@prod_pPaletaKolorow_par integer,
	@prod_pTabelaRozmiarow_par integer,
	@prod_iDataWaznosci_par integer,
	@prod_iNrFundRolny_par integer,
	@prod_pProdMag_par integer,
	@prod_strPKWiU2008_par varchar(32),
	@prod_nVAT_par integer,
	@prod_cProdEtyk_par varchar(1),
	@prod_pPracownik_par integer,
	@prod_cTowarRot_par varchar(1),
	@prod_cTowarZam_par varchar(1),
	@prod_curMinWartZam_par decimal(12,2),
	@prod_strOpisZam_par varchar(64),
	@prod_cDoSprzed_par varchar(1),
	@prod_pZamiennik1_par integer,
	@prod_pZamiennik2_par integer,
	@prod_pZamiennik3_par integer,
	@prod_pZamiennik4_par integer,
	@prod_pZamiennik5_par integer) with encryption as 
	insert into n5produkt values(@idobj_par,@versionid_par,
	@strNazwa_par,
	@strNazwaMiedzynarodowa_par,
	@strIndeks_par,
	@prod_pKodCelny_par,
	@strKodPKWiU_par,
	@eVAT_par,
	@strOpis_par,
	@pUlotka_par,
	@pInstrukcja_par,
	@pJednostkaEwid_par,
	@eAktywny_par,
	@pGrupaProd_par,
	@strCecha1_par,
	@strCecha2_par,
	@strCecha3_par,
	@eRodzaj_par,
	@prod_cWyrob_par,
	@prod_cSurowiec_par,
	@prod_pDostawca_par,
	@prod_cRolny_par,
	@prod_strCN_par,
	@prod_strCPC_par,
	@prod_strNazwaObcojezyczna1_par,
	@prod_strNazwaObcojezyczna2_par,
	@prod_strNazwaObcojezyczna3_par,
	@prod_pKrajPoch_par,
	@prod_cCheckPrice_par,
	@prod_nCzasDostawy_par,
	@prod_cCzasDostawyUwzglednij_par,
	@prod_pPaletaKolorow_par,
	@prod_pTabelaRozmiarow_par,
	@prod_iDataWaznosci_par,
	@prod_iNrFundRolny_par,
	@prod_pProdMag_par,
	@prod_strPKWiU2008_par,
	@prod_nVAT_par,
	@prod_cProdEtyk_par,
	@prod_pPracownik_par,
	@prod_cTowarRot_par,
	@prod_cTowarZam_par,
	@prod_curMinWartZam_par,
	@prod_strOpisZam_par,
	@prod_cDoSprzed_par,
	@prod_pZamiennik1_par,
	@prod_pZamiennik2_par,
	@prod_pZamiennik3_par,
	@prod_pZamiennik4_par,
	@prod_pZamiennik5_par)
return @@rowcount
go

create procedure n5produkt_update(@idobj_par integer,@versionid_par integer,
	@strNazwa_par varchar(128),
	@strNazwaMiedzynarodowa_par varchar(128),
	@strIndeks_par varchar(32),
	@prod_pKodCelny_par integer,
	@strKodPKWiU_par varchar(32),
	@eVAT_par integer,
	@strOpis_par varchar(512),
	@pUlotka_par integer,
	@pInstrukcja_par integer,
	@pJednostkaEwid_par integer,
	@eAktywny_par integer,
	@pGrupaProd_par integer,
	@strCecha1_par varchar(128),
	@strCecha2_par varchar(128),
	@strCecha3_par varchar(128),
	@eRodzaj_par integer,
	@prod_cWyrob_par varchar(1),
	@prod_cSurowiec_par varchar(1),
	@prod_pDostawca_par integer,
	@prod_cRolny_par varchar(1),
	@prod_strCN_par varchar(32),
	@prod_strCPC_par varchar(32),
	@prod_strNazwaObcojezyczna1_par varchar(128),
	@prod_strNazwaObcojezyczna2_par varchar(128),
	@prod_strNazwaObcojezyczna3_par varchar(128),
	@prod_pKrajPoch_par integer,
	@prod_cCheckPrice_par varchar(1),
	@prod_nCzasDostawy_par integer,
	@prod_cCzasDostawyUwzglednij_par varchar(1),
	@prod_pPaletaKolorow_par integer,
	@prod_pTabelaRozmiarow_par integer,
	@prod_iDataWaznosci_par integer,
	@prod_iNrFundRolny_par integer,
	@prod_pProdMag_par integer,
	@prod_strPKWiU2008_par varchar(32),
	@prod_nVAT_par integer,
	@prod_cProdEtyk_par varchar(1),
	@prod_pPracownik_par integer,
	@prod_cTowarRot_par varchar(1),
	@prod_cTowarZam_par varchar(1),
	@prod_curMinWartZam_par decimal(12,2),
	@prod_strOpisZam_par varchar(64),
	@prod_cDoSprzed_par varchar(1),
	@prod_pZamiennik1_par integer,
	@prod_pZamiennik2_par integer,
	@prod_pZamiennik3_par integer,
	@prod_pZamiennik4_par integer,
	@prod_pZamiennik5_par integer) with encryption as 
	update n5produkt set VersionId=@versionid_par,
	strNazwa=@strNazwa_par,
	strNazwaMiedzynarodowa=@strNazwaMiedzynarodowa_par,
	strIndeks=@strIndeks_par,
	prod_pKodCelny=@prod_pKodCelny_par,
	strKodPKWiU=@strKodPKWiU_par,
	eVAT=@eVAT_par,
	strOpis=@strOpis_par,
	pUlotka=@pUlotka_par,
	pInstrukcja=@pInstrukcja_par,
	pJednostkaEwid=@pJednostkaEwid_par,
	eAktywny=@eAktywny_par,
	pGrupaProd=@pGrupaProd_par,
	strCecha1=@strCecha1_par,
	strCecha2=@strCecha2_par,
	strCecha3=@strCecha3_par,
	eRodzaj=@eRodzaj_par,
	prod_cWyrob=@prod_cWyrob_par,
	prod_cSurowiec=@prod_cSurowiec_par,
	prod_pDostawca=@prod_pDostawca_par,
	prod_cRolny=@prod_cRolny_par,
	prod_strCN=@prod_strCN_par,
	prod_strCPC=@prod_strCPC_par,
	prod_strNazwaObcojezyczna1=@prod_strNazwaObcojezyczna1_par,
	prod_strNazwaObcojezyczna2=@prod_strNazwaObcojezyczna2_par,
	prod_strNazwaObcojezyczna3=@prod_strNazwaObcojezyczna3_par,
	prod_pKrajPoch=@prod_pKrajPoch_par,
	prod_cCheckPrice=@prod_cCheckPrice_par,
	prod_nCzasDostawy=@prod_nCzasDostawy_par,
	prod_cCzasDostawyUwzglednij=@prod_cCzasDostawyUwzglednij_par,
	prod_pPaletaKolorow=@prod_pPaletaKolorow_par,
	prod_pTabelaRozmiarow=@prod_pTabelaRozmiarow_par,
	prod_iDataWaznosci=@prod_iDataWaznosci_par,
	prod_iNrFundRolny=@prod_iNrFundRolny_par,
	prod_pProdMag=@prod_pProdMag_par,
	prod_strPKWiU2008=@prod_strPKWiU2008_par,
	prod_nVAT=@prod_nVAT_par,
	prod_cProdEtyk=@prod_cProdEtyk_par,
	prod_pPracownik=@prod_pPracownik_par,
	prod_cTowarRot=@prod_cTowarRot_par,
	prod_cTowarZam=@prod_cTowarZam_par,
	prod_curMinWartZam=@prod_curMinWartZam_par,
	prod_strOpisZam=@prod_strOpisZam_par,
	prod_cDoSprzed=@prod_cDoSprzed_par,
	prod_pZamiennik1=@prod_pZamiennik1_par,
	prod_pZamiennik2=@prod_pZamiennik2_par,
	prod_pZamiennik3=@prod_pZamiennik3_par,
	prod_pZamiennik4=@prod_pZamiennik4_par,
	prod_pZamiennik5=@prod_pZamiennik5_par
	where idobj=@idobj_par
return @@rowcount
go

create procedure n5produkt_delete(@idobj_par integer) with encryption as 
	delete from n5produkt where idobj=@idobj_par
return @@rowcount
go

create procedure n5produkt_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5produkt
go

create procedure n5produkt_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10132 as integer),idobj from n5pozsprzedaz where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10132 as integer),idobj from n5pozsprzedaz where pProduktOrg=@idobj_par
union
select TOP 5 'typeid'=cast(10149 as integer),idobj from n5egzemplarz where egze_pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10234 as integer),idobj from n5klient_obiekt where klob_pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10251 as integer),idobj from n5ptstan where gms_pProd=@idobj_par
union
select TOP 5 'typeid'=cast(10228 as integer),idobj from n5pozistat where pistt_pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10279 as integer),idobj from n5produkt_magazyn where prmg_pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10225 as integer),idobj from n5gmop where gmo_pProd=@idobj_par
union
select TOP 5 'typeid'=cast(10205 as integer),idobj from n5pozrealprod where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10151 as integer),idobj from n5klient_produkt where klpr_pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10236 as integer),idobj from n5pltyppracy where tpr_pUsluga=@idobj_par
union
select TOP 5 'typeid'=cast(10131 as integer),idobj from n5produkt where prod_pProdMag=@idobj_par
union
select TOP 5 'typeid'=cast(10131 as integer),idobj from n5produkt where prod_pZamiennik1=@idobj_par
union
select TOP 5 'typeid'=cast(10131 as integer),idobj from n5produkt where prod_pZamiennik2=@idobj_par
union
select TOP 5 'typeid'=cast(10131 as integer),idobj from n5produkt where prod_pZamiennik3=@idobj_par
union
select TOP 5 'typeid'=cast(10131 as integer),idobj from n5produkt where prod_pZamiennik4=@idobj_par
union
select TOP 5 'typeid'=cast(10131 as integer),idobj from n5produkt where prod_pZamiennik5=@idobj_par
union
select TOP 5 'typeid'=cast(10250 as integer),idobj from n5ptop where gmo_pProd=@idobj_par
union
select TOP 5 'typeid'=cast(10173 as integer),idobj from n5pozzamowienie where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10173 as integer),idobj from n5pozzamowienie where pProduktOrg=@idobj_par
union
select TOP 5 'typeid'=cast(10238 as integer),idobj from n5pozdokprod where pdp_pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10167 as integer),idobj from n5pozdoketyk where pdet_pWyrob=@idobj_par
union
select TOP 5 'typeid'=cast(10184 as integer),idobj from n5pozrecepta where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10161 as integer),idobj from n5pozdokmag where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10212 as integer),idobj from n5bwinfo_produkt where wpProdGrupa=@idobj_par and wpProdGrupa_wrt=10131
union
select TOP 5 'typeid'=cast(10175 as integer),idobj from n5pozzakup where pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10226 as integer),idobj from n5gmstan where gms_pProd=@idobj_par
union
select TOP 5 'typeid'=cast(10243 as integer),idobj from n5pozprojekt_abas where pproj_pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10189 as integer),idobj from n5polrab where wpProdGrupa=@idobj_par and wpProdGrupa_wrt=10131
union
select TOP 5 'typeid'=cast(10274 as integer),idobj from n5prop where prop_pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10291 as integer),idobj from n5pozinwark where pia_pProdukt=@idobj_par
union
select TOP 5 'typeid'=cast(10186 as integer),idobj from n5pozzlecprod where pProdukt=@idobj_par
go

create view vlist_n5produkt_listOpakowania as select 
'coll_lp'=collections.lp,'p_versionid'=p.VersionId,'p_idobj'=p.IdObj
,'p_strnazwa'=p.strNazwa
,'p_strnazwamiedzynarodowa'=p.strNazwaMiedzynarodowa
,'p_strindeks'=p.strIndeks
,'p_prod_pkodcelny'=p.prod_pKodCelny
,'p_strkodpkwiu'=p.strKodPKWiU
,'p_evat'=p.eVAT
,'p_stropis'=p.strOpis
,'p_pulotka'=p.pUlotka
,'p_pinstrukcja'=p.pInstrukcja
,'p_pjednostkaewid'=p.pJednostkaEwid
,'p_eaktywny'=p.eAktywny
,'p_pgrupaprod'=p.pGrupaProd
,'p_strcecha1'=p.strCecha1
,'p_strcecha2'=p.strCecha2
,'p_strcecha3'=p.strCecha3
,'p_erodzaj'=p.eRodzaj
,'p_prod_cwyrob'=p.prod_cWyrob
,'p_prod_csurowiec'=p.prod_cSurowiec
,'p_prod_pdostawca'=p.prod_pDostawca
,'p_prod_crolny'=p.prod_cRolny
,'p_prod_strcn'=p.prod_strCN
,'p_prod_strcpc'=p.prod_strCPC
,'p_prod_strnazwaobcojezyczna1'=p.prod_strNazwaObcojezyczna1
,'p_prod_strnazwaobcojezyczna2'=p.prod_strNazwaObcojezyczna2
,'p_prod_strnazwaobcojezyczna3'=p.prod_strNazwaObcojezyczna3
,'p_prod_pkrajpoch'=p.prod_pKrajPoch
,'p_prod_ccheckprice'=p.prod_cCheckPrice
,'p_prod_nczasdostawy'=p.prod_nCzasDostawy
,'p_prod_cczasdostawyuwzglednij'=p.prod_cCzasDostawyUwzglednij
,'p_prod_ppaletakolorow'=p.prod_pPaletaKolorow
,'p_prod_ptabelarozmiarow'=p.prod_pTabelaRozmiarow
,'p_prod_idatawaznosci'=p.prod_iDataWaznosci
,'p_prod_inrfundrolny'=p.prod_iNrFundRolny
,'p_prod_pprodmag'=p.prod_pProdMag
,'p_prod_strpkwiu2008'=p.prod_strPKWiU2008
,'p_prod_nvat'=p.prod_nVAT
,'p_prod_cprodetyk'=p.prod_cProdEtyk
,'p_prod_ppracownik'=p.prod_pPracownik
,'p_prod_ctowarrot'=p.prod_cTowarRot
,'p_prod_ctowarzam'=p.prod_cTowarZam
,'p_prod_curminwartzam'=p.prod_curMinWartZam
,'p_prod_stropiszam'=p.prod_strOpisZam
,'p_prod_cdosprzed'=p.prod_cDoSprzed
,'p_prod_pzamiennik1'=p.prod_pZamiennik1
,'p_prod_pzamiennik2'=p.prod_pZamiennik2
,'p_prod_pzamiennik3'=p.prod_pZamiennik3
,'p_prod_pzamiennik4'=p.prod_pZamiennik4
,'p_prod_pzamiennik5'=p.prod_pZamiennik5
,'c_versionid'=c.VersionId,'c_idobj'=c.IdObj
,'c_strnazwa'=c.strNazwa
,'c_erodzaj'=c.eRodzaj
,'c_popakowaniejedn'=c.pOpakowanieJedn
,'c_currkrotnosc'=c.currKrotnosc
,'c_curilosc'=c.curIlosc
,'c_strean'=c.strEAN
,'c_curwaganetto'=c.curWagaNetto
,'c_curwagabrutto'=c.curWagaBrutto
,'c_pjednostkawagi'=c.pJednostkaWagi
,'c_curcenanetto1'=c.curCenaNetto1
,'c_curcenabrutto1'=c.curCenaBrutto1
,'c_curcenanetto2'=c.curCenaNetto2
,'c_curcenabrutto2'=c.curCenaBrutto2
,'c_curcenanetto3'=c.curCenaNetto3
,'c_curcenabrutto3'=c.curCenaBrutto3
,'c_curcenanetto4'=c.curCenaNetto4
,'c_curcenabrutto4'=c.curCenaBrutto4
,'c_curcenanetto5'=c.curCenaNetto5
,'c_curcenabrutto5'=c.curCenaBrutto5
,'c_curcenanetto6'=c.curCenaNetto6
,'c_curcenabrutto6'=c.curCenaBrutto6
,'c_pwaluta'=c.pWaluta
,'c_strkodopak'=c.strKodOpak
,'c_pjednopak'=c.pJednOpak
,'c_pzamiennik'=c.pZamiennik
,'c_strnazwamiedzynarodowa'=c.strNazwaMiedzynarodowa
,'c_curiloscmin'=c.curIloscMin
,'c_curiloscmax'=c.curIloscMax
,'c_curnarzutmin'=c.curNarzutMin
,'c_curnarzutmax'=c.curNarzutMax
,'c_curnarzutzal'=c.curNarzutZal
,'c_curstcelna'=c.curStCelna
,'c_opak_curdlugosc'=c.opak_curDlugosc
,'c_opak_curszerokosc'=c.opak_curSzerokosc
,'c_opak_curwysokosc'=c.opak_curWysokosc
,'c_opak_curobjetosc'=c.opak_curObjetosc
,'c_opak_curcenaminnetto'=c.opak_curCenaMinNetto
,'c_opak_curcenaminbrutto'=c.opak_curCenaMinBrutto
,'c_opak_pwalutamincenysprzed'=c.opak_pWalutaMinCenySprzed
,'c_opak_pwaluta2'=c.opak_pWaluta2
,'c_opak_pwaluta3'=c.opak_pWaluta3
,'c_opak_pwaluta4'=c.opak_pWaluta4
,'c_opak_pwaluta5'=c.opak_pWaluta5
,'c_opak_pwaluta6'=c.opak_pWaluta6
,'c_opak_erodzajnrser'=c.opak_eRodzajNrSer
,'c_opak_strsernomask'=c.opak_strSerNoMask
,'c_opak_nsernolicznik'=c.opak_nSerNoLicznik
,'c_opak_strrzc'=c.opak_strRZC
,'c_opak_strrzsm'=c.opak_strRZSM
,'c_opak_pkolor'=c.opak_pKolor
,'c_opak_prozmiar'=c.opak_pRozmiar
,'c_opak_popakmag'=c.opak_pOpakMag
,'c_curminzamdostawca'=c.curMinZamDostawca
,'c_curminzamodbiorca'=c.curMinZamOdbiorca
,'c_opak_curgrubosc'=c.opak_curGrubosc
 from n5produkt as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10131012
 join n5opakowanie_produktu as c on c.idobj = collections.idobj 
 go
--================================================================================================
--================================================================================================
create table n5inwark
(
	IdObj integer not null,
	VersionId integer not null,
	strNrDok varchar(32) not null,
	ia_dDataRozp datetime not null,
	ia_dDataZakon datetime not null,
	ia_pInwentaryzacja integer not null,
	ia_strUwagi varchar(7900) not null,
	-- [virtual] ia_listPozycje,
	ia_eStatus integer not null,
	ia_strKomisja1 varchar(96) not null,
	ia_strKomisja2 varchar(96) not null,
	ia_strKomisja3 varchar(96) not null,
	ia_strKomisja4 varchar(96) not null,
	ia_strKomisja5 varchar(96) not null,
	ia_strMiejsceSklad varchar(1024) not null,
	ia_strRodzajInw varchar(96) not null,
	ia_strSposobInw varchar(96) not null,
	ia_strExtra1 varchar(32) not null,
	ia_strExtra2 varchar(128) not null,
	ia_dExtra3 datetime not null,
	ia_curExtra4 decimal(12,2) not null,
	ia_curExtra5 decimal(12,2) not null,
	ia_pKwalifikatorEx integer not null
)
go

create table n5inwmag
(
	IdObj integer not null,
	VersionId integer not null,
	strNrDok varchar(32) not null,
	im_dDataInw datetime not null,
	ia_iNrOpMag integer not null,
	im_pMagazyn integer not null,
	im_pIR integer not null,
	im_pIP integer not null,
	im_eStatus integer not null,
	im_strUwagi varchar(1024) not null,
	im_strExtra1 varchar(32) not null,
	im_strExtra2 varchar(128) not null,
	im_dExtra3 datetime not null,
	im_curExtra4 decimal(12,2) not null,
	im_curExtra5 decimal(12,2) not null,
	im_pKwalifikatorEx integer not null
)
go

create table n5pozinwark
(
	IdObj integer not null,
	VersionId integer not null,
	pia_pProdukt integer not null,
	pia_pOpak integer not null,
	pia_curIloscEwid decimal(14,4) not null,
	pia_curIloscFakt decimal(14,4) not null,
	pia_curCenaFakt decimal(14,4) not null,
	pia_strUwagi varchar(7900) not null,
	pia_cChecked varchar(1) not null,
	pia_strExtra1 varchar(32) not null,
	pia_strExtra2 varchar(128) not null,
	pia_dExtra3 datetime not null,
	pia_curExtra4 decimal(12,2) not null,
	pia_curExtra5 decimal(12,2) not null,
	pia_pKwalifikatorEx integer not null
)
go
--================================================================================================
-- table: n5inwmag
if exists (select * from sysobjects where name='n5inwmag_select')
	drop procedure n5inwmag_select
go
if exists (select * from sysobjects where name='n5inwmag_insert')
	drop procedure n5inwmag_insert
go
if exists (select * from sysobjects where name='n5inwmag_update')
	drop procedure n5inwmag_update
go
if exists (select * from sysobjects where name='n5inwmag_delete')
	drop procedure n5inwmag_delete
go
if exists (select * from sysobjects where name='n5inwmag_maxid')
	drop procedure n5inwmag_maxid
go
if exists (select * from sysobjects where name='n5inwmag_candel')
	drop procedure n5inwmag_candel
go
--================================================================================================
-- table: n5inwmag
create procedure n5inwmag_select(@idobj_par integer,@versionid_par integer output,
	@strNrDok_par varchar(32) output,
	@im_dDataInw_par datetime output,
	@ia_iNrOpMag_par integer output,
	@im_pMagazyn_par integer output,
	@im_pIR_par integer output,
	@im_pIP_par integer output,
	@im_eStatus_par integer output,
	@im_strUwagi_par varchar(1024) output,
	@im_strExtra1_par varchar(32) output,
	@im_strExtra2_par varchar(128) output,
	@im_dExtra3_par datetime output,
	@im_curExtra4_par decimal(12,2) output,
	@im_curExtra5_par decimal(12,2) output,
	@im_pKwalifikatorEx_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNrDok_par=strNrDok,
	@im_dDataInw_par=im_dDataInw,
	@ia_iNrOpMag_par=ia_iNrOpMag,
	@im_pMagazyn_par=im_pMagazyn,
	@im_pIR_par=im_pIR,
	@im_pIP_par=im_pIP,
	@im_eStatus_par=im_eStatus,
	@im_strUwagi_par=im_strUwagi,
	@im_strExtra1_par=im_strExtra1,
	@im_strExtra2_par=im_strExtra2,
	@im_dExtra3_par=im_dExtra3,
	@im_curExtra4_par=im_curExtra4,
	@im_curExtra5_par=im_curExtra5,
	@im_pKwalifikatorEx_par=im_pKwalifikatorEx from n5inwmag where IdObj=@idobj_par
return @@rowcount
go

create procedure n5inwmag_insert(@idobj_par integer,@versionid_par integer,
	@strNrDok_par varchar(32),
	@im_dDataInw_par datetime,
	@ia_iNrOpMag_par integer,
	@im_pMagazyn_par integer,
	@im_pIR_par integer,
	@im_pIP_par integer,
	@im_eStatus_par integer,
	@im_strUwagi_par varchar(1024),
	@im_strExtra1_par varchar(32),
	@im_strExtra2_par varchar(128),
	@im_dExtra3_par datetime,
	@im_curExtra4_par decimal(12,2),
	@im_curExtra5_par decimal(12,2),
	@im_pKwalifikatorEx_par integer) with encryption as 
	insert into n5inwmag values(@idobj_par,@versionid_par,
	@strNrDok_par,
	@im_dDataInw_par,
	@ia_iNrOpMag_par,
	@im_pMagazyn_par,
	@im_pIR_par,
	@im_pIP_par,
	@im_eStatus_par,
	@im_strUwagi_par,
	@im_strExtra1_par,
	@im_strExtra2_par,
	@im_dExtra3_par,
	@im_curExtra4_par,
	@im_curExtra5_par,
	@im_pKwalifikatorEx_par)
return @@rowcount
go

create procedure n5inwmag_update(@idobj_par integer,@versionid_par integer,
	@strNrDok_par varchar(32),
	@im_dDataInw_par datetime,
	@ia_iNrOpMag_par integer,
	@im_pMagazyn_par integer,
	@im_pIR_par integer,
	@im_pIP_par integer,
	@im_eStatus_par integer,
	@im_strUwagi_par varchar(1024),
	@im_strExtra1_par varchar(32),
	@im_strExtra2_par varchar(128),
	@im_dExtra3_par datetime,
	@im_curExtra4_par decimal(12,2),
	@im_curExtra5_par decimal(12,2),
	@im_pKwalifikatorEx_par integer) with encryption as 
	update n5inwmag set VersionId=@versionid_par,
	strNrDok=@strNrDok_par,
	im_dDataInw=@im_dDataInw_par,
	ia_iNrOpMag=@ia_iNrOpMag_par,
	im_pMagazyn=@im_pMagazyn_par,
	im_pIR=@im_pIR_par,
	im_pIP=@im_pIP_par,
	im_eStatus=@im_eStatus_par,
	im_strUwagi=@im_strUwagi_par,
	im_strExtra1=@im_strExtra1_par,
	im_strExtra2=@im_strExtra2_par,
	im_dExtra3=@im_dExtra3_par,
	im_curExtra4=@im_curExtra4_par,
	im_curExtra5=@im_curExtra5_par,
	im_pKwalifikatorEx=@im_pKwalifikatorEx_par
	where idobj=@idobj_par
return @@rowcount
go

create procedure n5inwmag_delete(@idobj_par integer) with encryption as 
	delete from n5inwmag where idobj=@idobj_par
return @@rowcount
go

create procedure n5inwmag_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5inwmag
go

create procedure n5inwmag_candel(@idobj_par integer) with encryption as 
select TOP 5 'typeid'=cast(10290 as integer),idobj from n5inwark where ia_pInwentaryzacja=@idobj_par
go


--================================================================================================
-- table: n5pozinwark
if exists (select * from sysobjects where name='n5pozinwark_select')
	drop procedure n5pozinwark_select
go
if exists (select * from sysobjects where name='n5pozinwark_insert')
	drop procedure n5pozinwark_insert
go
if exists (select * from sysobjects where name='n5pozinwark_update')
	drop procedure n5pozinwark_update
go
if exists (select * from sysobjects where name='n5pozinwark_delete')
	drop procedure n5pozinwark_delete
go
if exists (select * from sysobjects where name='n5pozinwark_maxid')
	drop procedure n5pozinwark_maxid
go
if exists (select * from sysobjects where name='n5pozinwark_candel')
	drop procedure n5pozinwark_candel
go
--================================================================================================
-- table: n5pozinwark
create procedure n5pozinwark_select(@idobj_par integer,@versionid_par integer output,
	@pia_pProdukt_par integer output,
	@pia_pOpak_par integer output,
	@pia_curIloscEwid_par decimal(14,4) output,
	@pia_curIloscFakt_par decimal(14,4) output,
	@pia_curCenaFakt_par decimal(14,4) output,
	@pia_strUwagi_par varchar(7900) output,
	@pia_cChecked_par varchar(1) output,
	@pia_strExtra1_par varchar(32) output,
	@pia_strExtra2_par varchar(128) output,
	@pia_dExtra3_par datetime output,
	@pia_curExtra4_par decimal(12,2) output,
	@pia_curExtra5_par decimal(12,2) output,
	@pia_pKwalifikatorEx_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@pia_pProdukt_par=pia_pProdukt,
	@pia_pOpak_par=pia_pOpak,
	@pia_curIloscEwid_par=pia_curIloscEwid,
	@pia_curIloscFakt_par=pia_curIloscFakt,
	@pia_curCenaFakt_par=pia_curCenaFakt,
	@pia_strUwagi_par=pia_strUwagi,
	@pia_cChecked_par=pia_cChecked,
	@pia_strExtra1_par=pia_strExtra1,
	@pia_strExtra2_par=pia_strExtra2,
	@pia_dExtra3_par=pia_dExtra3,
	@pia_curExtra4_par=pia_curExtra4,
	@pia_curExtra5_par=pia_curExtra5,
	@pia_pKwalifikatorEx_par=pia_pKwalifikatorEx from n5pozinwark where IdObj=@idobj_par
return @@rowcount
go

create procedure n5pozinwark_insert(@idobj_par integer,@versionid_par integer,
	@pia_pProdukt_par integer,
	@pia_pOpak_par integer,
	@pia_curIloscEwid_par decimal(14,4),
	@pia_curIloscFakt_par decimal(14,4),
	@pia_curCenaFakt_par decimal(14,4),
	@pia_strUwagi_par varchar(7900),
	@pia_cChecked_par varchar(1),
	@pia_strExtra1_par varchar(32),
	@pia_strExtra2_par varchar(128),
	@pia_dExtra3_par datetime,
	@pia_curExtra4_par decimal(12,2),
	@pia_curExtra5_par decimal(12,2),
	@pia_pKwalifikatorEx_par integer) with encryption as 
	insert into n5pozinwark values(@idobj_par,@versionid_par,
	@pia_pProdukt_par,
	@pia_pOpak_par,
	@pia_curIloscEwid_par,
	@pia_curIloscFakt_par,
	@pia_curCenaFakt_par,
	@pia_strUwagi_par,
	@pia_cChecked_par,
	@pia_strExtra1_par,
	@pia_strExtra2_par,
	@pia_dExtra3_par,
	@pia_curExtra4_par,
	@pia_curExtra5_par,
	@pia_pKwalifikatorEx_par)
return @@rowcount
go

create procedure n5pozinwark_update(@idobj_par integer,@versionid_par integer,
	@pia_pProdukt_par integer,
	@pia_pOpak_par integer,
	@pia_curIloscEwid_par decimal(14,4),
	@pia_curIloscFakt_par decimal(14,4),
	@pia_curCenaFakt_par decimal(14,4),
	@pia_strUwagi_par varchar(7900),
	@pia_cChecked_par varchar(1),
	@pia_strExtra1_par varchar(32),
	@pia_strExtra2_par varchar(128),
	@pia_dExtra3_par datetime,
	@pia_curExtra4_par decimal(12,2),
	@pia_curExtra5_par decimal(12,2),
	@pia_pKwalifikatorEx_par integer) with encryption as 
	update n5pozinwark set VersionId=@versionid_par,
	pia_pProdukt=@pia_pProdukt_par,
	pia_pOpak=@pia_pOpak_par,
	pia_curIloscEwid=@pia_curIloscEwid_par,
	pia_curIloscFakt=@pia_curIloscFakt_par,
	pia_curCenaFakt=@pia_curCenaFakt_par,
	pia_strUwagi=@pia_strUwagi_par,
	pia_cChecked=@pia_cChecked_par,
	pia_strExtra1=@pia_strExtra1_par,
	pia_strExtra2=@pia_strExtra2_par,
	pia_dExtra3=@pia_dExtra3_par,
	pia_curExtra4=@pia_curExtra4_par,
	pia_curExtra5=@pia_curExtra5_par,
	pia_pKwalifikatorEx=@pia_pKwalifikatorEx_par
	where idobj=@idobj_par
return @@rowcount
go

create procedure n5pozinwark_delete(@idobj_par integer) with encryption as 
	delete from n5pozinwark where idobj=@idobj_par
return @@rowcount
go

create procedure n5pozinwark_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5pozinwark
go

create procedure n5pozinwark_candel(@idobj_par integer) with encryption as 
go
--================================================================================================
-- table: n5inwark
if exists (select * from sysobjects where name='n5inwark_select')
	drop procedure n5inwark_select
go
if exists (select * from sysobjects where name='n5inwark_insert')
	drop procedure n5inwark_insert
go
if exists (select * from sysobjects where name='n5inwark_update')
	drop procedure n5inwark_update
go
if exists (select * from sysobjects where name='n5inwark_delete')
	drop procedure n5inwark_delete
go
if exists (select * from sysobjects where name='n5inwark_maxid')
	drop procedure n5inwark_maxid
go
if exists (select * from sysobjects where name='n5inwark_candel')
	drop procedure n5inwark_candel
go

--================================================================================================
-- table: n5inwark
create procedure n5inwark_select(@idobj_par integer,@versionid_par integer output,
	@strNrDok_par varchar(32) output,
	@ia_dDataRozp_par datetime output,
	@ia_dDataZakon_par datetime output,
	@ia_pInwentaryzacja_par integer output,
	@ia_strUwagi_par varchar(7900) output,
	@ia_eStatus_par integer output,
	@ia_strKomisja1_par varchar(96) output,
	@ia_strKomisja2_par varchar(96) output,
	@ia_strKomisja3_par varchar(96) output,
	@ia_strKomisja4_par varchar(96) output,
	@ia_strKomisja5_par varchar(96) output,
	@ia_strMiejsceSklad_par varchar(1024) output,
	@ia_strRodzajInw_par varchar(96) output,
	@ia_strSposobInw_par varchar(96) output,
	@ia_strExtra1_par varchar(32) output,
	@ia_strExtra2_par varchar(128) output,
	@ia_dExtra3_par datetime output,
	@ia_curExtra4_par decimal(12,2) output,
	@ia_curExtra5_par decimal(12,2) output,
	@ia_pKwalifikatorEx_par integer output) with encryption as 
	select @versionid_par=VersionId,
	@strNrDok_par=strNrDok,
	@ia_dDataRozp_par=ia_dDataRozp,
	@ia_dDataZakon_par=ia_dDataZakon,
	@ia_pInwentaryzacja_par=ia_pInwentaryzacja,
	@ia_strUwagi_par=ia_strUwagi,
	@ia_eStatus_par=ia_eStatus,
	@ia_strKomisja1_par=ia_strKomisja1,
	@ia_strKomisja2_par=ia_strKomisja2,
	@ia_strKomisja3_par=ia_strKomisja3,
	@ia_strKomisja4_par=ia_strKomisja4,
	@ia_strKomisja5_par=ia_strKomisja5,
	@ia_strMiejsceSklad_par=ia_strMiejsceSklad,
	@ia_strRodzajInw_par=ia_strRodzajInw,
	@ia_strSposobInw_par=ia_strSposobInw,
	@ia_strExtra1_par=ia_strExtra1,
	@ia_strExtra2_par=ia_strExtra2,
	@ia_dExtra3_par=ia_dExtra3,
	@ia_curExtra4_par=ia_curExtra4,
	@ia_curExtra5_par=ia_curExtra5,
	@ia_pKwalifikatorEx_par=ia_pKwalifikatorEx from n5inwark where IdObj=@idobj_par
return @@rowcount
go

create procedure n5inwark_insert(@idobj_par integer,@versionid_par integer,
	@strNrDok_par varchar(32),
	@ia_dDataRozp_par datetime,
	@ia_dDataZakon_par datetime,
	@ia_pInwentaryzacja_par integer,
	@ia_strUwagi_par varchar(7900),
	@ia_eStatus_par integer,
	@ia_strKomisja1_par varchar(96),
	@ia_strKomisja2_par varchar(96),
	@ia_strKomisja3_par varchar(96),
	@ia_strKomisja4_par varchar(96),
	@ia_strKomisja5_par varchar(96),
	@ia_strMiejsceSklad_par varchar(1024),
	@ia_strRodzajInw_par varchar(96),
	@ia_strSposobInw_par varchar(96),
	@ia_strExtra1_par varchar(32),
	@ia_strExtra2_par varchar(128),
	@ia_dExtra3_par datetime,
	@ia_curExtra4_par decimal(12,2),
	@ia_curExtra5_par decimal(12,2),
	@ia_pKwalifikatorEx_par integer) with encryption as 
	insert into n5inwark values(@idobj_par,@versionid_par,
	@strNrDok_par,
	@ia_dDataRozp_par,
	@ia_dDataZakon_par,
	@ia_pInwentaryzacja_par,
	@ia_strUwagi_par,
	@ia_eStatus_par,
	@ia_strKomisja1_par,
	@ia_strKomisja2_par,
	@ia_strKomisja3_par,
	@ia_strKomisja4_par,
	@ia_strKomisja5_par,
	@ia_strMiejsceSklad_par,
	@ia_strRodzajInw_par,
	@ia_strSposobInw_par,
	@ia_strExtra1_par,
	@ia_strExtra2_par,
	@ia_dExtra3_par,
	@ia_curExtra4_par,
	@ia_curExtra5_par,
	@ia_pKwalifikatorEx_par)
return @@rowcount
go

create procedure n5inwark_update(@idobj_par integer,@versionid_par integer,
	@strNrDok_par varchar(32),
	@ia_dDataRozp_par datetime,
	@ia_dDataZakon_par datetime,
	@ia_pInwentaryzacja_par integer,
	@ia_strUwagi_par varchar(7900),
	@ia_eStatus_par integer,
	@ia_strKomisja1_par varchar(96),
	@ia_strKomisja2_par varchar(96),
	@ia_strKomisja3_par varchar(96),
	@ia_strKomisja4_par varchar(96),
	@ia_strKomisja5_par varchar(96),
	@ia_strMiejsceSklad_par varchar(1024),
	@ia_strRodzajInw_par varchar(96),
	@ia_strSposobInw_par varchar(96),
	@ia_strExtra1_par varchar(32),
	@ia_strExtra2_par varchar(128),
	@ia_dExtra3_par datetime,
	@ia_curExtra4_par decimal(12,2),
	@ia_curExtra5_par decimal(12,2),
	@ia_pKwalifikatorEx_par integer) with encryption as 
	update n5inwark set VersionId=@versionid_par,
	strNrDok=@strNrDok_par,
	ia_dDataRozp=@ia_dDataRozp_par,
	ia_dDataZakon=@ia_dDataZakon_par,
	ia_pInwentaryzacja=@ia_pInwentaryzacja_par,
	ia_strUwagi=@ia_strUwagi_par,
	ia_eStatus=@ia_eStatus_par,
	ia_strKomisja1=@ia_strKomisja1_par,
	ia_strKomisja2=@ia_strKomisja2_par,
	ia_strKomisja3=@ia_strKomisja3_par,
	ia_strKomisja4=@ia_strKomisja4_par,
	ia_strKomisja5=@ia_strKomisja5_par,
	ia_strMiejsceSklad=@ia_strMiejsceSklad_par,
	ia_strRodzajInw=@ia_strRodzajInw_par,
	ia_strSposobInw=@ia_strSposobInw_par,
	ia_strExtra1=@ia_strExtra1_par,
	ia_strExtra2=@ia_strExtra2_par,
	ia_dExtra3=@ia_dExtra3_par,
	ia_curExtra4=@ia_curExtra4_par,
	ia_curExtra5=@ia_curExtra5_par,
	ia_pKwalifikatorEx=@ia_pKwalifikatorEx_par
	where idobj=@idobj_par
return @@rowcount
go

create procedure n5inwark_delete(@idobj_par integer) with encryption as 
	delete from n5inwark where idobj=@idobj_par
return @@rowcount
go

create procedure n5inwark_maxid(@maxid_par integer output) with encryption as 
	select @maxid_par=max(idobj) from n5inwark
go

create procedure n5inwark_candel(@idobj_par integer) with encryption as 
go

--================================================================================================
--
--================================================================================================
if exists (select * from sysobjects where name='vlist_n5inwark_ia_listPozycje')
	drop view vlist_n5inwark_ia_listPozycje
go

create view vlist_n5inwark_ia_listPozycje as select 
'coll_lp'=collections.lp,'p_versionid'=p.VersionId,'p_idobj'=p.IdObj
,'p_strnrdok'=p.strNrDok
,'p_ia_ddatarozp'=p.ia_dDataRozp
,'p_ia_ddatazakon'=p.ia_dDataZakon
,'p_ia_pinwentaryzacja'=p.ia_pInwentaryzacja
,'p_ia_struwagi'=p.ia_strUwagi
,'p_ia_estatus'=p.ia_eStatus
,'p_ia_strkomisja1'=p.ia_strKomisja1
,'p_ia_strkomisja2'=p.ia_strKomisja2
,'p_ia_strkomisja3'=p.ia_strKomisja3
,'p_ia_strkomisja4'=p.ia_strKomisja4
,'p_ia_strkomisja5'=p.ia_strKomisja5
,'p_ia_strmiejscesklad'=p.ia_strMiejsceSklad
,'p_ia_strrodzajinw'=p.ia_strRodzajInw
,'p_ia_strsposobinw'=p.ia_strSposobInw
,'p_ia_strextra1'=p.ia_strExtra1
,'p_ia_strextra2'=p.ia_strExtra2
,'p_ia_dextra3'=p.ia_dExtra3
,'p_ia_curextra4'=p.ia_curExtra4
,'p_ia_curextra5'=p.ia_curExtra5
,'p_ia_pkwalifikatorex'=p.ia_pKwalifikatorEx
,'c_versionid'=c.VersionId,'c_idobj'=c.IdObj
,'c_pia_pprodukt'=c.pia_pProdukt
,'c_pia_popak'=c.pia_pOpak
,'c_pia_curiloscewid'=c.pia_curIloscEwid
,'c_pia_curiloscfakt'=c.pia_curIloscFakt
,'c_pia_curcenafakt'=c.pia_curCenaFakt
,'c_pia_struwagi'=c.pia_strUwagi
,'c_pia_cchecked'=c.pia_cChecked
,'c_pia_strextra1'=c.pia_strExtra1
,'c_pia_strextra2'=c.pia_strExtra2
,'c_pia_dextra3'=c.pia_dExtra3
,'c_pia_curextra4'=c.pia_curExtra4
,'c_pia_curextra5'=c.pia_curExtra5
,'c_pia_pkwalifikatorex'=c.pia_pKwalifikatorEx
 from n5inwark as p
 join collections on p.idobj=collections.idparent and collections.idcollection = 10290006
 join n5pozinwark as c on c.idobj = collections.idobj 
 go
 
 --================================================================================================

 --================================================================================================

 n2001_makegrants 'navo2002user'
go
--- mark current version
exec n2001_setprofile_value 1097, 'DB11F'
go

 --================================================================================================
 -- nak³adka DB11_F
 if exists (select * from sysobjects where name='WRT_n5transakcja_operacja_trop_wrefDokument_3')
	alter table n5transakcja_operacja drop constraint WRT_n5transakcja_operacja_trop_wrefDokument_3
go

alter table n5transakcja_operacja add constraint WRT_n5transakcja_operacja_trop_wrefDokument_3 check (
	trop_wrefDokument_wrt=0 or 
	trop_wrefDokument_wrt=10129 or 
	trop_wrefDokument_wrt=10176 or 
	trop_wrefDokument_wrt=10156 or 
	trop_wrefDokument_wrt=10121 or 
	trop_wrefDokument_wrt=10192 or 
	trop_wrefDokument_wrt=10147 or 
	trop_wrefDokument_wrt=10215
)
go

 -- table: n5plnieob
 if exists (select * from sysobjects where name='ENUM_n5plnieob_eTyp_10')
	alter table n5plnieob drop constraint ENUM_n5plnieob_eTyp_10
 go
 alter table n5plnieob add constraint ENUM_n5plnieob_eTyp_10 check (
 eTyp between 0 and 13
 )
 go

 
-- uprawnienia do n5inwmag -----------------------------------------
-- max idSodGroup
declare @maxIdSodGroup int
set @maxIdSodGroup = (select max(idobj)+1 from n5sodgroup)
-- id grupy 'Typy danych'
declare @maxIdTypyDanych int
set @maxIdTypyDanych = (select idobj from n5sodgroup where strNazwa = 'Typy danych')
if not exists(select * from n5sodgroup where strNazwa = 'Obiekty typu: Inwentaryzacja magazynu')
begin
	-- dodanie grupy dla obiektu n5inwmag
	insert into n5sodgroup values (@maxIdSodGroup,1,'Obiekty typu: Inwentaryzacja magazynu',@maxIdTypyDanych,'EB')

	-- kolejne uprawnienia
	declare @maxIdGroup int
	set @maxIdGroup = (select idobj from n5sodgroup where strNazwa = 'Obiekty typu: Inwentaryzacja magazynu')
	declare @maxIdSod int
	set @maxIdSod = (select max(idobj) from n5sod)
	insert into n5sod values (@maxIdSod+1,1,'Odczyt',@maxIdGroup,102891,0,'EB')
	insert into n5sod values (@maxIdSod+2,1,'Tworzenie',@maxIdGroup,102892,0,'EB')
	insert into n5sod values (@maxIdSod+3,1,'Edycja',@maxIdGroup,102893,0,'EB')
	insert into n5sod values (@maxIdSod+4,1,'Usuwanie',@maxIdGroup,102894,0,'EB')
end
go

-- uprawnienia do n5inwark -----------------------------------------
-- max idSodGroup
declare @maxIdSodGroup int
set @maxIdSodGroup = (select max(idobj)+1 from n5sodgroup)
-- id grupy 'Typy danych'
declare @maxIdTypyDanych int
set @maxIdTypyDanych = (select idobj from n5sodgroup where strNazwa = 'Typy danych')
if not exists(select * from n5sodgroup where strNazwa = 'Obiekty typu: Arkusz inwentaryzacyjny')
begin
	-- dodanie grupy dla obiektu n5inwark
	insert into n5sodgroup values (@maxIdSodGroup,1,'Obiekty typu: Arkusz inwentaryzacyjny',@maxIdTypyDanych,'EB')

	-- kolejne uprawnienia
	declare @maxIdGroup int
	set @maxIdGroup = (select idobj from n5sodgroup where strNazwa = 'Obiekty typu: Arkusz inwentaryzacyjny')
	declare @maxIdSod int
	set @maxIdSod = (select max(idobj) from n5sod)
	insert into n5sod values (@maxIdSod+1,1,'Odczyt',@maxIdGroup,102901,0,'EB')
	insert into n5sod values (@maxIdSod+2,1,'Tworzenie',@maxIdGroup,102902,0,'EB')
	insert into n5sod values (@maxIdSod+3,1,'Edycja',@maxIdGroup,102903,0,'EB')
	insert into n5sod values (@maxIdSod+4,1,'Usuwanie',@maxIdGroup,102904,0,'EB')
end
go

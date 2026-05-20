-- logowanie zmian, kompatybilne z NXM.System LoggedEvents

create table [dbo].[NxmCoreLoggedEvent] (

  [ID] nvarchar(32) not null,
  [Version] bigint not null,
  [EventType] nvarchar(64) not null,
  [Created] datetime not null,
  [SessionID] nvarchar(64) not null,
  [Login] nvarchar(64) not null,
  [ObjectRef] nvarchar(32) not null,
  [ObjectRef_Type] nvarchar(64) not null,
  [Description] nvarchar(2048) not null,
  [XVal1] nvarchar(64) not null,
  [XVal2] nvarchar(64) not null,
  [XVal3] nvarchar(2048) not null,
  [XVal4] nvarchar(2048) not null,
  [XVal5] datetime not null,
  [XVal6] datetime not null,
  [XVal7] decimal(19,4) not null,
  [XVal8] decimal(19,4) not null,
  [XVal9] decimal(19,4) not null,
  [XValA] decimal(19,4) not null
);
GO

-- Note: ID needn't be unique, so primary key is wrong and must not be applied

-- alter table [dbo].[NxmCoreLoggedEvent]
-- add constraint [PK_NxmCoreLoggedEvent]
    -- primary key clustered ([ID] asc);
-- GO

create TYPE _nxm_logged_event_set AS TABLE (

  [ID] nvarchar(32) not null,
  [Version] bigint not null,
  [EventType] nvarchar(64) not null,
  [Created] datetime not null,
  [SessionID] nvarchar(64) not null,
  [Login] nvarchar(64) not null,
  [ObjectRef] nvarchar(32) not null,
  [ObjectRef_Type] nvarchar(64) not null,
  [Description] nvarchar(2048) not null,
  [XVal1] nvarchar(64) not null,
  [XVal2] nvarchar(64) not null,
  [XVal3] nvarchar(2048) not null,
  [XVal4] nvarchar(2048) not null,
  [XVal5] datetime not null,
  [XVal6] datetime not null,
  [XVal7] decimal(19,4) not null,
  [XVal8] decimal(19,4) not null,
  [XVal9] decimal(19,4) not null,
  [XValA] decimal(19,4) not null
);
GO

CREATE PROCEDURE _nxm_insert_logged_events(@events_par as _nxm_logged_event_set READONLY)
as
	declare @id_base nvarchar(32)
	declare @timestamp as datetime
	select @timestamp = GETDATE()

	select @id_base = 'x-'+ rtrim(cast(cast(@timestamp as decimal(30,12)) as nvarchar)) + '-'
	
	insert into NxmCoreLoggedEvent
	select
		(select @id_base + substring(cast((100000+ROW_NUMBER() over (order by (select null))) as nvarchar),2,5) from @events_par),
		events_.Version,
		events_.EventType,
		@timestamp,
		events_.SessionID,
		events_.Login,
		events_.ObjectRef,
		events_.ObjectRef_Type,
		events_.Description,
		events_.XVal1,
		events_.XVal2,
		events_.XVal3,
		events_.XVal4,
		events_.XVal5,
		events_.XVal6,
		events_.XVal7,
		events_.XVal8,
		events_.XVal9,
		events_.XValA
	from @events_par as events_
go

-----------------------------------------
create trigger [dbo].[trig_n5sprzedaz_insupd]
on [dbo].[n5sprzedaz]
for insert, update
as
begin
    declare @events AS _nxm_logged_event_set;
	
    set nocount on;
    insert into @events 
	select 
	cast(IdObj as nvarchar) + '+', VersionId, 'eb/n5sprzedaz-save', {d '1900-01-01'}, '',
	(select n5uzytkownik.strLogin from n5uzytkownik where n5uzytkownik.IdObj = inserted.sprzed_pUzytModyf), 
	cast(IdObj as nvarchar), 'n5sprzedaz', '',
	strNrDok, 
	(select n5klient.strIndeks from n5klient where n5klient.idObj = inserted.pKlient), 
	'', 
	(select n5jednostka.strSkrot from n5jednostka where n5jednostka.idObj = inserted.pWaluta),
	dDataWyst, dDataPlat,
	curSumaNetto, curSumaVAT, curSumaBrutto, curSumaVAT
	from inserted
	
    exec _nxm_insert_logged_events @events
end
go
create trigger [dbo].[trig_n5sprzedaz_del]
on [dbo].[n5sprzedaz]
for delete
as
begin
    declare @events AS _nxm_logged_event_set;
	
    set nocount on;
    insert into @events 
	select 
	cast(IdObj as nvarchar) + '+', VersionId, 'eb/n5sprzedaz-delete', {d '1900-01-01'}, '',
	(select n5uzytkownik.strLogin from n5uzytkownik where n5uzytkownik.IdObj = deleted.sprzed_pUzytModyf),  
	cast(IdObj as nvarchar), 'n5sprzedaz', '',
	strNrDok, 
	(select n5klient.strIndeks from n5klient where n5klient.idObj = deleted.pKlient), 
	'', 
	(select n5jednostka.strSkrot from n5jednostka where n5jednostka.idObj = deleted.pWaluta),
	dDataWyst, dDataPlat,
	curSumaNetto, curSumaVAT, curSumaBrutto, curSumaVAT
	from deleted
	
    exec _nxm_insert_logged_events @events
end
go
-----------------------------------------
create trigger [dbo].[trig_n5zamowienie_insupd]
on [dbo].[n5zamowienie]
for insert, update
as
begin
    declare @events AS _nxm_logged_event_set;
	
    set nocount on;
    insert into @events 
	select 
	cast(IdObj as nvarchar) + '+', VersionId, 'eb/n5zamowienie-save', {d '1900-01-01'}, '',
	(select n5uzytkownik.strLogin from n5uzytkownik where n5uzytkownik.IdObj = inserted.zam_pUzytModyf), 
	cast(IdObj as nvarchar), 'n5zamowienie', '',
	strNrDok, 
	(select n5klient.strIndeks from n5klient where n5klient.idObj = inserted.pKlient), 
	'', 
	(select n5jednostka.strSkrot from n5jednostka where n5jednostka.idObj = inserted.pWaluta),
	dDataWyst, dDataPlat,
	curSumaNetto, curSumaVAT, curSumaBrutto, curSumaVAT
	from inserted
	
    exec _nxm_insert_logged_events @events
end
go
create trigger [dbo].[trig_n5zamowienie_del]
on [dbo].[n5zamowienie]
for delete
as
begin
    declare @events AS _nxm_logged_event_set;
	
    set nocount on;
    insert into @events 
	select 
	cast(IdObj as nvarchar) + '+', VersionId, 'eb/n5zamowienie-delete', {d '1900-01-01'}, '',
	(select n5uzytkownik.strLogin from n5uzytkownik where n5uzytkownik.IdObj = deleted.zam_pUzytModyf),  
	cast(IdObj as nvarchar), 'n5zamowienie', '',
	strNrDok, 
	(select n5klient.strIndeks from n5klient where n5klient.idObj = deleted.pKlient), 
	'', 
	(select n5jednostka.strSkrot from n5jednostka where n5jednostka.idObj = deleted.pWaluta),
	dDataWyst, dDataPlat,
	curSumaNetto, curSumaVAT, curSumaBrutto, curSumaVAT
	from deleted
	
    exec _nxm_insert_logged_events @events
end
go
-----------------------------------------
create trigger [dbo].[trig_n5dokmag_insupd]
on [dbo].[n5dokmag]
for insert, update
as
begin
    declare @events AS _nxm_logged_event_set;
	
    set nocount on;
   
    insert into @events 
	select 
	cast(IdObj as nvarchar) + '+', VersionId, 'eb/n5dokmag-save', {d '1900-01-01'}, '',
	(select n5uzytkownik.strLogin from n5uzytkownik where n5uzytkownik.IdObj = inserted.dm_pUzytModyf), 
	cast(IdObj as nvarchar), 'n5dokmag', '',
	strNrDok, 
	isnull((select n5klient.strIndeks from n5klient where n5klient.idObj = inserted.pKlient),''), 
	isnull((select n5magazyn.strNazwa from n5magazyn where n5magazyn.idObj = inserted.pMagZrod),''),
	isnull((select n5magazyn.strNazwa from n5magazyn where n5magazyn.idObj = inserted.pMagDocel),''),
	dDataWyst, {d '1900-01-01'},
	curSumaEwid, 0.0, 0.0, cast(nNumOper as decimal)
	from inserted
	
    exec _nxm_insert_logged_events @events
end
go
create trigger [dbo].[trig_n5dokmag_del]
on [dbo].[n5dokmag]
for delete
as
begin
    declare @events AS _nxm_logged_event_set;
	
    set nocount on;
    
	insert into @events 
	select 
	cast(IdObj as nvarchar) + '+', VersionId, 'eb/n5dokmag-delete', {d '1900-01-01'}, '',
	(select n5uzytkownik.strLogin from n5uzytkownik where n5uzytkownik.IdObj = deleted.dm_pUzytModyf), 
	cast(IdObj as nvarchar), 'n5dokmag', '',
	strNrDok, 
	isnull((select n5klient.strIndeks from n5klient where n5klient.idObj = deleted.pKlient),''), 
	isnull((select n5magazyn.strNazwa from n5magazyn where n5magazyn.idObj = deleted.pMagZrod),''),
	isnull((select n5magazyn.strNazwa from n5magazyn where n5magazyn.idObj = deleted.pMagDocel),''),
	dDataWyst, {d '1900-01-01'},
	curSumaEwid, 0.0, 0.0, cast(nNumOper as decimal)
	from deleted
	
    exec _nxm_insert_logged_events @events
end
go
-----------------------------------------
-----------------------------------------
create trigger [dbo].[trig_n5klient_insupd]
on [dbo].[n5klient]
for insert, update
as
begin
    declare @events AS _nxm_logged_event_set;
	
    set nocount on;
   
    insert into @events 
	select 
	cast(IdObj as nvarchar) + '+', VersionId, 'eb/n5klient-save', {d '1900-01-01'}, '',
	'', 
	cast(IdObj as nvarchar), 'n5klient', '',
	strIndeks, 
	strNIP,
	'',
	'',
	{d '1900-01-01'}, {d '1900-01-01'},
	0.0, 0.0, 0.0, 0.0
	from inserted
	
    exec _nxm_insert_logged_events @events
end
go
create trigger [dbo].[trig_n5klient_del]
on [dbo].[n5klient]
for delete
as
begin
    declare @events AS _nxm_logged_event_set;
	
    set nocount on;
    
	 insert into @events 
	select 
	cast(IdObj as nvarchar) + '+', VersionId, 'eb/n5klient-delete', {d '1900-01-01'}, '',
	'', 
	cast(IdObj as nvarchar), 'n5klient', '',
	strIndeks, 
	strNIP,
	'',
	'',
	{d '1900-01-01'}, {d '1900-01-01'},
	0.0, 0.0, 0.0, 0.0
	from deleted
	
    exec _nxm_insert_logged_events @events
end
go
-----------------------------------------
-----------------------------------------
create trigger [dbo].[trig_n5transakcja_insupd]
on [dbo].[n5transakcja]
for insert, update
as
begin
    declare @events AS _nxm_logged_event_set;
	
    set nocount on;
   
    insert into @events 
	select 
	cast(IdObj as nvarchar) + '+', VersionId, 'eb/n5transakcja-save', {d '1900-01-01'}, '',
	'', 
	cast(IdObj as nvarchar), 'n5transakcja', '',
	strSymTrans, 
	isnull((select n5klient.strIndeks from n5klient where n5klient.idObj = inserted.wrefPodmiot and inserted.wrefPodmiot_wrt = 10108),''),
	'',
	'',
	dDataRozp, dDataWym,
	curWn, curMa, trn_curWnVAT, trn_curMaVAT
	from inserted
	
    exec _nxm_insert_logged_events @events
end
go
create trigger [dbo].[trig_n5transakcja_del]
on [dbo].[n5transakcja]
for delete
as
begin
    declare @events AS _nxm_logged_event_set;
	
    set nocount on;
    
	insert into @events 
	select 
	cast(IdObj as nvarchar) + '+', VersionId, 'eb/n5transakcja-del', {d '1900-01-01'}, '',
	'', 
	cast(IdObj as nvarchar), 'n5transakcja', '',
	strSymTrans, 
	isnull((select n5klient.strIndeks from n5klient where n5klient.idObj = deleted.wrefPodmiot and deleted.wrefPodmiot_wrt = 10108),''),
	'',
	'',
	dDataRozp, dDataWym,
	curWn, curMa, trn_curWnVAT, trn_curMaVAT
	from deleted
	
    exec _nxm_insert_logged_events @events
end
go
-----------------------------------------
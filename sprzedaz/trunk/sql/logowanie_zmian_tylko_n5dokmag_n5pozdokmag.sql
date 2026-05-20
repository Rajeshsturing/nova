-- logowanie zmian, kompatybilne z NXM.System LoggedEvents

create table [dbo].[NxmCoreLoggedEvent] (

  [ID] nvarchar(32) null,
  [Version] bigint null,
  [EventType] nvarchar(64) null,
  [Created] datetime null,
  [SessionID] nvarchar(64) null,
  [Login] nvarchar(64) null,
  [ObjectRef] nvarchar(32) null,
  [ObjectRef_Type] nvarchar(64) null,
  [Description] nvarchar(2048) null,
  [XVal1] nvarchar(64) null,
  [XVal2] nvarchar(64) null,
  [XVal3] nvarchar(2048) null,
  [XVal4] nvarchar(2048) null,
  [XVal5] datetime null,
  [XVal6] datetime null,
  [XVal7] decimal(19,4) null,
  [XVal8] decimal(19,4) null,
  [XVal9] decimal(19,4) null,
  [XValA] decimal(19,4) null
);
GO

-- Note: ID needn't be unique, so primary key is wrong and must not be applied

-- alter table [dbo].[NxmCoreLoggedEvent]
-- add constraint [PK_NxmCoreLoggedEvent]
    -- primary key clustered ([ID] asc);
-- GO

create TYPE _nxm_logged_event_set AS TABLE (

  [ID] nvarchar(32) null,
  [Version] bigint null,
  [EventType] nvarchar(64) null,
  [Created] datetime null,
  [SessionID] nvarchar(64) null,
  [Login] nvarchar(64) null,
  [ObjectRef] nvarchar(32) null,
  [ObjectRef_Type] nvarchar(64) null,
  [Description] nvarchar(2048) null,
  [XVal1] nvarchar(64) null,
  [XVal2] nvarchar(64) null,
  [XVal3] nvarchar(2048) null,
  [XVal4] nvarchar(2048) null,
  [XVal5] datetime null,
  [XVal6] datetime null,
  [XVal7] decimal(19,4) null,
  [XVal8] decimal(19,4) null,
  [XVal9] decimal(19,4) null,
  [XValA] decimal(19,4) null
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


--  triggery n5dokmag
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
	curSumaEwid, curSumaMag, 0.0, cast(nNumOper as decimal)
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
	curSumaEwid, curSumaMag, 0.0, cast(nNumOper as decimal)
	from deleted
	
    exec _nxm_insert_logged_events @events
end
go



-- triggery n5pozdokmag
create trigger [dbo].[trig_n5pozdokmag_insupd]
on [dbo].[n5pozdokmag]
for insert, update
as
begin
    declare @events AS _nxm_logged_event_set;
	
    set nocount on;
   
    insert into @events 
	 select 
	  cast(IdObj as nvarchar) + '+', --[ID] nvarchar(32)
	  VersionId, --[Version] bigint
	  'eb/n5pozdokmag-save', --[EventType] nvarchar(64)
	  {d '1900-01-01'}, --[Created] datetime
	  '', --[SessionID] nvarchar(64)
	  '', -- [Login] nvarchar(64)
	  cast(IdObj as nvarchar), --[ObjectRef] nvarchar(32)
	  'n5pozdokmag', --[ObjectRef_Type] nvarchar(64)
	  '', --[Description] nvarchar(2048)
	  '', --[XVal1] nvarchar(64)
	  isnull((select n5produkt.strIndeks from n5produkt where n5produkt.idObj = inserted.pProdukt),''), --[XVal2] nvarchar(64)
	  curIloscOpak, --[XVal3] nvarchar(2048)
	  isnull((select Collections.IdParent from Collections where Collections.idObj = inserted.IdObj and Collections.IdCollection = 10162011),''), --[XVal4] nvarchar(2048)
	  {d '1900-01-01'}, --[XVal5] datetime
	  {d '1900-01-01'}, --[XVal6] datetime
	  curWartMag, --[XVal7] decimal(19,4)
	  curWartEwid, --[XVal8] decimal(19,4)
	  0.0, -- [XVal9] decimal(19,4)
	  0.0 -- [XValA] decimal(19,4)
	 from inserted
    exec _nxm_insert_logged_events @events
end
go

create trigger [dbo].[trig_n5pozdokmag_del]
on [dbo].[n5pozdokmag]
for delete
as
begin
    declare @events AS _nxm_logged_event_set;
	
    set nocount on;
    
	insert into @events 
	select 
	cast(IdObj as nvarchar) + '+', VersionId, 'eb/n5pozdokmag-delete', {d '1900-01-01'}, '',
	'', 
	cast(IdObj as nvarchar),
	'n5pozdokmag',
	'',
	'', 
	isnull((select n5produkt.strIndeks from n5produkt where n5produkt.idObj = deleted.pProdukt),''), 
	curIloscOpak,
	isnull((select Collections.IdParent from Collections where Collections.idObj = deleted.IdObj and Collections.IdCollection = 10162011),''),
	{d '1900-01-01'},
	{d '1900-01-01'},
	curWartMag, 
	curWartEwid, 
	0.0, 
	0.0
	from deleted
	
    exec _nxm_insert_logged_events @events
end
go
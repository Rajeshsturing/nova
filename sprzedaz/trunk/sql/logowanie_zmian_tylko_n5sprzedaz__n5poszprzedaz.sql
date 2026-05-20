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



--  triggery n5sprzedaz
create trigger [dbo].[trig_n5sprzedaz_insupd]
on [dbo].[n5sprzedaz]
for insert, update
as
begin
    declare @events AS _nxm_logged_event_set;
	
    set nocount on;
   
    insert into @events 
	select 
	cast(IdObj as nvarchar) + '+', --[ID] nvarchar(32)
	VersionId, --[Version] bigint
	'eb/n5sprzedaz-save', --[EventType] nvarchar(64)
	{d '1900-01-01'}, --[Created] datetime
	'', --[SessionID] nvarchar(64)
	(select n5uzytkownik.strLogin from n5uzytkownik where n5uzytkownik.IdObj = inserted.sprzed_pUzytModyf), -- [Login] nvarchar(64)
	cast(IdObj as nvarchar), --[ObjectRef] nvarchar(32)
	'n5sprzedaz', --[ObjectRef_Type] nvarchar(64)
	strUwagi, --[Description] nvarchar(2048)
	strNrDok, --[XVal1] nvarchar(64)
	isnull((select n5klient.strIndeks from n5klient where n5klient.idObj = inserted.pKlient),''), --[XVal2] nvarchar(64)
	'', --[XVal3] nvarchar(2048)
	'', --[XVal4] nvarchar(2048)
	dDataWyst, --[XVal5] datetime
	dDataPlat, --[XVal6] datetime
	curSumaNetto, --[XVal7] decimal(19,4)
	curSumaVAT, --[XVal8] decimal(19,4)
	curSumaBrutto, -- [XVal9] decimal(19,4)
	curSumaWalBrutto -- [XValA] decimal(19,4)
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
	cast(IdObj as nvarchar) + '+', --[ID] nvarchar(32)
	VersionId, --[Version] bigint
	'eb/n5sprzedaz-deleted', --[EventType] nvarchar(64)
	{d '1900-01-01'}, --[Created] datetime
	'', --[SessionID] nvarchar(64)
	(select n5uzytkownik.strLogin from n5uzytkownik where n5uzytkownik.IdObj = deleted.sprzed_pUzytModyf), -- [Login] nvarchar(64)
	cast(IdObj as nvarchar), --[ObjectRef] nvarchar(32)
	'n5sprzedaz', --[ObjectRef_Type] nvarchar(64)
	strUwagi, --[Description] nvarchar(2048)
	strNrDok, --[XVal1] nvarchar(64)
	isnull((select n5klient.strIndeks from n5klient where n5klient.idObj = deleted.pKlient),''), --[XVal2] nvarchar(64)
	'', --[XVal3] nvarchar(2048)
	'', --[XVal4] nvarchar(2048)
	dDataWyst, --[XVal5] datetime
	dDataPlat, --[XVal6] datetime
	curSumaNetto, --[XVal7] decimal(19,4)
	curSumaVAT, --[XVal8] decimal(19,4)
	curSumaBrutto, -- [XVal9] decimal(19,4)
	curSumaWalBrutto -- [XValA] decimal(19,4)
	from deleted
	
    exec _nxm_insert_logged_events @events
end
go


-- triggery n5pozsprzedaz
create trigger [dbo].[trig_n5pozsprzedaz_insupd]
on [dbo].[n5pozsprzedaz]
for insert, update
as
begin
    declare @events AS _nxm_logged_event_set;
	
    set nocount on;
   
    insert into @events 
	 select 
	  cast(IdObj as nvarchar) + '+', --[ID] nvarchar(32)
	  VersionId, --[Version] bigint
	  'eb/n5pozsprzedaz-save', --[EventType] nvarchar(64)
	  {d '1900-01-01'}, --[Created] datetime
	  '', --[SessionID] nvarchar(64)
	  '', -- [Login] nvarchar(64)
	  cast(IdObj as nvarchar), --[ObjectRef] nvarchar(32)
	  'n5pozsprzedaz', --[ObjectRef_Type] nvarchar(64)
	  '', --[Description] nvarchar(2048)
	  '', --[XVal1] nvarchar(64)
	  isnull((select n5produkt.strIndeks from n5produkt where n5produkt.idObj = inserted.pProdukt),''), --[XVal2] nvarchar(64)
	  curIloscOpak, --[XVal3] nvarchar(2048)
	  isnull((select Collections.IdParent from Collections where Collections.idObj = inserted.IdObj and Collections.IdCollection = 10129013),''), --[XVal4] nvarchar(2048)
	  {d '1900-01-01'}, --[XVal5] datetime
	  {d '1900-01-01'}, --[XVal6] datetime
	  curCenaBazNetto, --[XVal7] decimal(19,4)
	  curCenaNetto, --[XVal8] decimal(19,4)
	  curWartNetto, -- [XVal9] decimal(19,4)
	  curWartBrutto -- [XValA] decimal(19,4)
	 from inserted
    exec _nxm_insert_logged_events @events
end
go

create trigger [dbo].[trig_n5pozsprzedaz_del]
on [dbo].[n5pozsprzedaz]
for delete
as
begin
    declare @events AS _nxm_logged_event_set;
	
    set nocount on;
    
	insert into @events 
	select 
	cast(IdObj as nvarchar) + '+', --[ID] nvarchar(32)
	  VersionId, --[Version] bigint
	  'eb/n5pozsprzedaz-deleted', --[EventType] nvarchar(64)
	  {d '1900-01-01'}, --[Created] datetime
	  '', --[SessionID] nvarchar(64)
	  '', -- [Login] nvarchar(64)
	  cast(IdObj as nvarchar), --[ObjectRef] nvarchar(32)
	  'n5pozsprzedaz', --[ObjectRef_Type] nvarchar(64)
	  '', --[Description] nvarchar(2048)
	  '', --[XVal1] nvarchar(64)
	  isnull((select n5produkt.strIndeks from n5produkt where n5produkt.idObj = deleted.pProdukt),''), --[XVal2] nvarchar(64)
	  curIloscOpak, --[XVal3] nvarchar(2048)
	  isnull((select Collections.IdParent from Collections where Collections.idObj = deleted.IdObj and Collections.IdCollection = 10129013),''), --[XVal4] nvarchar(2048)
	  {d '1900-01-01'}, --[XVal5] datetime
	  {d '1900-01-01'}, --[XVal6] datetime
	  curCenaBazNetto, --[XVal7] decimal(19,4)
	  curCenaNetto, --[XVal8] decimal(19,4)
	  curWartNetto, -- [XVal9] decimal(19,4)
	  curWartBrutto -- [XValA] decimal(19,4)
	from deleted
	
    exec _nxm_insert_logged_events @events
end
go
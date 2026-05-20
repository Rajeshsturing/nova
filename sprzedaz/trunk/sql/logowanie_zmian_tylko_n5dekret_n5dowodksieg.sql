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




--  triggery n5dekret
create trigger [dbo].[trig_n5dekret_insupd]
on [dbo].[n5dekret]
for insert, update
as
begin
    declare @events AS _nxm_logged_event_set;
	
    set nocount on;
   
    insert into @events 
	select 
	cast(IdObj as nvarchar) + '+', --[ID] nvarchar(32)
	VersionId, --[Version] bigint
	'eb/n5dekret-save', --[EventType] nvarchar(64)
	{d '1900-01-01'}, --[Created] datetime
	'', --[SessionID] nvarchar(64)
	'', -- [Login] nvarchar(64)
	cast(IdObj as nvarchar), --[ObjectRef] nvarchar(32)
	'n5dekret', --[ObjectRef_Type] nvarchar(64)
	'', --[Description] nvarchar(2048)
	'', --[XVal1] nvarchar(64)
	isnull((select n5konto.strSymbol from n5konto where n5konto.idObj = inserted.pKonto),''), --[XVal2] nvarchar(64)
	isnull((select n5transakcja.strSymTrans from n5transakcja where n5transakcja.idObj = inserted.pTransakcja),''), --[XVal3] nvarchar(2048)
	strOpis, --[XVal4] nvarchar(2048)
	dDataKsieg, --[XVal5] datetime
	{d '1900-01-01'}, --[XVal6] datetime
	curWn, --[XVal7] decimal(19,4)
	curMa, --[XVal8] decimal(19,4)
	0.0, -- [XVal9] decimal(19,4)
	0.0 -- [XValA] decimal(19,4)
	from inserted
	
    exec _nxm_insert_logged_events @events
end
go
create trigger [dbo].[trig_n5dekret_del]
on [dbo].[n5dekret]
for delete
as
begin
    declare @events AS _nxm_logged_event_set;
	
    set nocount on;
    
	insert into @events 
	select 
	cast(IdObj as nvarchar) + '+', --[ID] nvarchar(32)
	VersionId, --[Version] bigint
	'eb/n5dekret-delete', --[EventType] nvarchar(64)
	{d '1900-01-01'}, --[Created] datetime
	'', --[SessionID] nvarchar(64)
	'', -- [Login] nvarchar(64)
	cast(IdObj as nvarchar), --[ObjectRef] nvarchar(32)
	'n5dekret', --[ObjectRef_Type] nvarchar(64)
	'', --[Description] nvarchar(2048)
	isnull((select Collections.IdParent from Collections where Collections.idObj = deleted.IdObj and Collections.IdCollection = 10148008),''), --[XVal1] nvarchar(64)
	isnull((select n5konto.strSymbol from n5konto where n5konto.idObj = deleted.pKonto),''), --[XVal2] nvarchar(64)
	isnull((select n5transakcja.strSymTrans from n5transakcja where n5transakcja.idObj = deleted.pTransakcja),''), --[XVal3] nvarchar(2048)
	strOpis, --[XVal4] nvarchar(2048)
	dDataKsieg, --[XVal5] datetime
	{d '1900-01-01'}, --[XVal6] datetime
	curWn, --[XVal7] decimal(19,4)
	curMa, --[XVal8] decimal(19,4)
	0.0, -- [XVal9] decimal(19,4)
	0.0 -- [XValA] decimal(19,4)
	from deleted
	
    exec _nxm_insert_logged_events @events
end
go



-- triggery n5dowodksieg
create trigger [dbo].[trig_n5dowodksieg_insupd]
on [dbo].[n5dowodksieg]
for insert, update
as
begin
    declare @events AS _nxm_logged_event_set;
	
    set nocount on;
   
    insert into @events 
	 select 
	  cast(IdObj as nvarchar) + '+', --[ID] nvarchar(32)
	  VersionId, --[Version] bigint
	  'eb/n5dowodksieg-save', --[EventType] nvarchar(64)
	  {d '1900-01-01'}, --[Created] datetime
	  '', --[SessionID] nvarchar(64)
	  (select n5uzytkownik.strLogin from n5uzytkownik where n5uzytkownik.IdObj = inserted.dk_pUzytModyf), -- [Login] nvarchar(64)
	  cast(IdObj as nvarchar), --[ObjectRef] nvarchar(32)
	  'n5dowodksieg', --[ObjectRef_Type] nvarchar(64)
	  strOpis, --[Description] nvarchar(2048)
	  strNrDok, --[XVal1] nvarchar(64)
	  nNumDow, --[XVal2] nvarchar(64)
	  '', --[XVal3] nvarchar(2048)
	  '', --[XVal4] nvarchar(2048)
	  {d '1900-01-01'}, --[XVal5] datetime
	  {d '1900-01-01'}, --[XVal6] datetime
	  0.0, --[XVal7] decimal(19,4)
	  0.0, --[XVal8] decimal(19,4)
	  0.0, -- [XVal9] decimal(19,4)
	  0.0 -- [XValA] decimal(19,4)
	 from inserted
    exec _nxm_insert_logged_events @events
end
go

create trigger [dbo].[trig_n5dowodksieg_del]
on [dbo].[n5dowodksieg]
for delete
as
begin
    declare @events AS _nxm_logged_event_set;
	
    set nocount on;
    
	insert into @events 
	select 
	cast(IdObj as nvarchar) + '+', --[ID] nvarchar(32)
	  VersionId, --[Version] bigint
	  'eb/n5dowodksieg-delete', --[EventType] nvarchar(64)
	  {d '1900-01-01'}, --[Created] datetime
	  '', --[SessionID] nvarchar(64)
	  (select n5uzytkownik.strLogin from n5uzytkownik where n5uzytkownik.IdObj = deleted.dk_pUzytModyf), -- [Login] nvarchar(64)
	  cast(IdObj as nvarchar), --[ObjectRef] nvarchar(32)
	  'n5dowodksieg', --[ObjectRef_Type] nvarchar(64)
	  strOpis, --[Description] nvarchar(2048)
	  strNrDok, --[XVal1] nvarchar(64)
	  nNumDow, --[XVal2] nvarchar(64)
	  '', --[XVal3] nvarchar(2048)
	  '', --[XVal4] nvarchar(2048)
	  {d '1900-01-01'}, --[XVal5] datetime
	  {d '1900-01-01'}, --[XVal6] datetime
	  0.0, --[XVal7] decimal(19,4)
	  0.0, --[XVal8] decimal(19,4)
	  0.0, -- [XVal9] decimal(19,4)
	  0.0 -- [XValA] decimal(19,4)
	from deleted
	
    exec _nxm_insert_logged_events @events
end
go
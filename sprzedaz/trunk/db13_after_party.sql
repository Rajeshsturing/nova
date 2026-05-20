raiserror('starting DB13 after-party (2017.12.12)',0,1)
go


--2017.12.12--
if exists (select * from sysindexes where name='NINXCollections3')
	drop index Collections.NINXCollections3
go
-- brak wspólnych dzieci (dziecko może wystąpić tylko raz)
CREATE UNIQUE INDEX NINXCollections3 ON Collections (IdCollection,IdObj) include (IdParent, LP)
go

n2001_makegrants 'navo2002user'
go

raiserror('completed DB13 after-party (2017.12.12)',0,1)
go

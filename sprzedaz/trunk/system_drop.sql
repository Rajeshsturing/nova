-- drop user from database
use navo2002
go
sp_droprolemember 'db_owner','navo2002user'
go
sp_dropsrvrolemember 'navo2002user','dbcreator'
go
sp_revokedbaccess N'navo2002user'
go
sp_droplogin  N'navo2002user'
go

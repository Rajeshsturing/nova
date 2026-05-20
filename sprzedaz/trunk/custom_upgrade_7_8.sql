-- updgrade kodu celnego (wywolac przed upgradem n5produkt


if exists (select * from sysobjects where name='upg7_8_kodcelny')
	drop procedure upg7_8_kodcelny
go

create procedure upg7_8_kodcelny with encryption
as

declare @strKod varchar(96)
declare @iter integer

delete from n5kodpcn

declare kod_cur cursor for 
	select distinct(strKodCelny) from n5produkt where strKodCelny <> ''
open kod_cur 
set @iter = 1

fetch next from kod_cur into @strKod
while @@fetch_status = 0
begin
	begin
		insert into n5kodpcn values(@iter,1,@strKod,@strKod)
	end
	fetch next from kod_cur into @strKod
	set @iter = @iter + 1
end
close kod_cur
deallocate kod_cur

go

exec upg7_8_kodcelny

drop procedure upg7_8_kodcelny
go
------------------------------------------------------------------------------
--update n5pozzakup set pzak_curWartWal = curCenaNettoWal * curIloscOpak
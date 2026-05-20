
-- skrypt uprawnienia generator cen
declare @sodName varchar(64)
declare @secId int
declare @idSodGroup int

set @sodName = 'Generator cen'
set @secId = 13681
set @idSodGroup = (select idobj from n5sodgroup where strNazwa = 'Operacja - zaawansowane')

if @idSodGroup > 0 and not exists (select IdObj from n5sod where strNazwa = @sodName)
insert into n5sod values ((select max(idobj)+1 from n5sod),1,@sodName,@idSodGroup,@secId,0,'EB')
go

-- skrypt uprawnienia dla raportu Transakcje niepowi¹zane
declare @sodName varchar(64)
declare @secId int
declare @idSodGroup int

set @sodName = 'Transakcje niepowi¹zane'
set @secId = 13941
set @idSodGroup = (select idobj from n5sodgroup where strNazwa = 'Raport - Naleznosci i zobowiazania - Inne')

if @idSodGroup > 0 and not exists (select IdObj from n5sod where strNazwa = @sodName)
insert into n5sod values ((select max(idobj)+1 from n5sod),1,@sodName,@idSodGroup,@secId,0,'EB')
go
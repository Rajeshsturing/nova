
-- skrypt uprawnienia dla raportu Rentownoœæ klientów wg pracownika dedykowanego
declare @sodName varchar(64)
declare @secId int
declare @idSodGroup int

set @sodName = 'Rentownoœæ klientów wg handlowców'
set @secId = 13991
set @idSodGroup = (select idobj from n5sodgroup where strNazwa = 'Raport - Sprzeda¿ - Rentownoœæ sprzeda¿y')

if @idSodGroup > 0 and not exists (select IdObj from n5sod where strNazwa = @sodName)
insert into n5sod values ((select max(idobj)+1 from n5sod),1,@sodName,@idSodGroup,@secId,0,'EB')
go
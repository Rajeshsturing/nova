
-- Uprawnienie blokady wystawiania OW i ZO w cenach ni¿szych ni¿ cena ostatniej dostawy
declare @idSodGroup int
set @idSodGroup = (select idobj from n5sodgroup where strNazwa = 'Operacje specjalne')
declare @maxIdSod int
set @maxIdSod = (select max(idobj)+1 from n5sod)
insert into n5sod values (@maxIdSod,1,'Blokada wyst. OW i ZO w cenach ni¿szych ni¿ ceny ost. dostawy',@idSodGroup,120044,0,'EB')
GO
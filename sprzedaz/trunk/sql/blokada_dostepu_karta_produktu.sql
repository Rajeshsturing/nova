
-- uprawnienie Blokady edycji wybranych pol na karcie produktu
declare @idSodGroup int
set @idSodGroup = (select idobj from n5sodgroup where strNazwa = 'Operacje specjalne')
declare @maxSecId int
set @maxSecId = (select max(nSecId)+1 from n5sod where pSODGroup = @idSodGroup)
declare @maxIdSod int
set @maxIdSod = (select max(idobj)+1 from n5sod)
insert into n5sod values (@maxIdSod,1,'Blokada edycji wybranych pol na karcie produktu',@idSodGroup,@maxSecId,0,'EB')
go
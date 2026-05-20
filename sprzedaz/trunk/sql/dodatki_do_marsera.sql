-- wersja raportu MARSER dla IOW Service
-- od 2012-01-18 wymaga istnienia ponizszej funkcji SQL
-- funkcja ta moze byc modelowana pod k¹tem regu³ okreslania ceny zakupu dla potrzeb raportu
-- uwaga! stala wartosc 5 odpowiada idObj waluty EUR (tak jest w bazie IOW)

Use navo2002
Go

create function cenazak4marser(@idProd integer, @idOpak integer)
returns decimal(12,4)
as
begin
      declare @curCena decimal(12,4)
      declare @iWaluta integer
      declare @curKurs decimal(12,4)
      declare @dtData datetime

      select top 1 
            @curCena= c_curcenanettowal * 1.2, @dtData = p_ddatazakupu, @iWaluta = p_pwaluta
            from vlist_n5zakup_listPozycje 
            where c_pprodukt=@idProd and c_popak = @idOpak
            order by vlist_n5zakup_listPozycje.p_idobj desc
            
      if isnull(@curCena,0) = 0.0
      begin
            select top 1 @curCena= curCenaNetto3 
            from n5opakowanie_produktu 
            where idobj = @idOpak 
      end
      else
      begin
            if @iWaluta <> 5 
            begin
                  select top 1 @curKurs = curAverageWal 
                  from n5kurswalut 
                  where dData <= @dtData and pWalZ = 5 and pWalN=@iWaluta 
                  order by dData desc
                  set @curCena = @curCena / @curKurs
            end 
      end
      
      if isnull(@curCena,0) = 0.0
            set @curCena =  0.0
      
      return (@curCena)
end
go


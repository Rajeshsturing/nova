

drop procedure SQLProc_Naprawa
go
drop procedure SQLProc_MakeRozchOnPtr2
go
CREATE Procedure SQLProc_MakeRozchOnPtr2
	@IdArt int,@IdMag int,@IdTrans int,@LP int,
	@pDate datetime,@IdTransOrg int,
	@dIlosc numeric(12,3),@dCenaS numeric(12,2),@cTT char,
	@NAVO_EPSILON numeric(12,3)
As
	declare @IdPR int
	declare @Ilosc numeric(12,3), @CenaZ numeric(12,2)
	declare @tmpLP int
	declare @lRes int

	DECLARE myx CURSOR FOR SELECT IdPR,IloscNU,CenaZ 
		FROM Przyroz WHERE IdPR = (SELECT min(IdPR) FROM Przyroz
		WHERE IdTrans = @IdTransOrg AND LP = - @LP)

	if @@error <> 0
		return (@@error)
	open myx
	fetch next from myx into @IdPR, @Ilosc, @CenaZ
	set @lRes = @@error
	close myx
	deallocate myx
	if (@lRes <> 0)
		return (1)

	
		
	if @@rowcount <> 0
		begin
			if @Ilosc >= -@dIlosc
				begin
					set @tmpLP = -@LP
					exec @lRes = SQLPrzyRoz_Insert2 @IdPR,@IdArt,@IdMag,@pDate,@cTT,@IdTrans,@tmpLP,@dIlosc,@CenaZ,@dCenaS
					if @@error <> 0
						return (@@error)
					set @Ilosc = @Ilosc + @dIlosc
					UPDATE Przyroz SET IloscNU = @Ilosc WHERE IdPR = @IdPR
					return (@@error)
				end
		end
	set @lRes = 0

	CREATE TABLE #IdPR_IloscNU_CenaZ
	(
	        IdPR              int PRIMARY KEY,
	        IloscNU          numeric(15,3) NULL,
	        CenaZ            numeric(12,2) NULL,
	)
	TRUNCATE TABLE #IdPR_IloscNU_CenaZ
	INSERT INTO #IdPR_IloscNU_CenaZ
	SELECT IdPR,IloscNU,CenaZ 	
		FROM Przyroz WHERE IdTrans = @IdTransOrg AND LP = - @LP
		ORDER BY IdPR

	DECLARE CurMap2 CURSOR FOR SELECT IdPR,IloscNU,CenaZ
		FROM #IdPR_IloscNU_CenaZ ORDER BY IdPR

	OPEN CurMap2
	set @NAVO_EPSILON = -@NAVO_EPSILON
	while @dIlosc < @NAVO_EPSILON
	begin
		FETCH NEXT FROM CurMap2 INTO @IdPR, @Ilosc, @CenaZ
		if @@fetch_status <> 0
			break;
		if @@error <> 0
			break
		declare @dZdejmij numeric(12,3)
		if @Ilosc >= -@dIlosc
			begin
				set @dZdejmij = @dIlosc
				set @Ilosc = @Ilosc + @dIlosc
				set @dIlosc = 0.0
			end
		else
			begin
				set @dZdejmij = - @Ilosc
				set @dIlosc = @dIlosc - @dZdejmij
				set @Ilosc = 0.0
			end
		set @tmpLP = - @LP
		exec @lRes = SQLPrzyRoz_Insert2 @IdPR,@IdArt,@IdMag,@pDate,@cTT,@IdTrans,@tmpLP,@dZdejmij,@CenaZ,@dCenaS
		if @lRes <> 0
			return @lRes
		UPDATE Przyroz SET IloscNU = @Ilosc WHERE IdPR = @IdPR
	end
	CLOSE CurMap2
	deallocate CurMap2
	if @dIlosc < @NAVO_EPSILON
		begin 
			exec @lRes = SQLProc_MakeRozchOnOrder2 @IdArt,@IdMag,@IdTrans,@LP,@pDate,@dIlosc,@dCenaS,@cTT,@NAVO_EPSILON
			return @lRes
		end
	return (0)
GO
drop procedure SQLProc_MakeRozchOnOrder2
go
create Procedure SQLProc_MakeRozchOnOrder2
	@IdArt int,@IdMag int,@IdTrans int,
	@LP int,@pDate datetime,
	@dIlosc numeric(12,3),@dCenaS numeric(12,2),@cTT char,
	@NAVO_EPSILON numeric(12,3)
As
	declare @lRes int
	declare @IdPR int
	declare @Ilosc numeric(12,3), @CenaZ numeric(12,2)
	declare @tmpLP int

	SELECT @IdPR=min(IdPR) FROM Przyroz
		WHERE (DataPR <= CONVERT(DATEtime,@pDate,105))
		AND IdArt=@IdArt AND IdMag=@IdMag AND IloscNU > 0.0 AND LP < 0
	if @@rowcount <> 0
		begin
			SELECT @Ilosc=IloscNU,@CenaZ=CenaZ FROM Przyroz WHERE IdPR = @IdPR
			if @@error <> 0 
				return @@error
			if @Ilosc >= -@dIlosc
				begin
					set @tmpLP = -@LP
					exec @lRes = SQLPrzyRoz_Insert2 @IdPR,@IdArt,@IdMag,@pDate,@cTT,@IdTrans,@tmpLP,@dIlosc,@CenaZ,@dCenaS
					if @lRes <> 0 
						return @lRes
					set @Ilosc = @Ilosc + @dIlosc
					UPDATE Przyroz SET IloscNU = @Ilosc WHERE IdPR = @IdPR
					return @@error
				end
		end
	set @lRes = 0

	DECLARE CurMar CURSOR LOCAL FORWARD_ONLY STATIC TYPE_WARNING FOR
	SELECT IdPR,IloscNU,CenaZ FROM Przyroz
		WHERE (DataPR <= @pDate) AND IdArt=@IdArt AND IdMag=@IdMag
		AND IloscNU > 0.0 AND LP < 0
		ORDER BY DataPR, IdPR
 
	OPEN CurMar
	while @dIlosc < -@NAVO_EPSILON
	begin
		FETCH NEXT FROM CurMar INTO @IdPR, @Ilosc, @CenaZ
		if @@fetch_status <> 0
			break
		if @@error <> 0 
			break
		declare @dZdejmij numeric(12,3)
		if @Ilosc >= -@dIlosc
			begin
				set @dZdejmij = @dIlosc
				set @Ilosc = @Ilosc + @dIlosc
				set @dIlosc = 0.0
			end
		else
			begin
				set @dZdejmij = -@Ilosc
				set @dIlosc = @dIlosc - @dZdejmij
				set @Ilosc = 0.0
			end
		set @tmpLP = -@LP
		exec @lRes = SQLPrzyRoz_Insert2 @IdPR,@IdArt,@IdMag,@pDate,@cTT,@IdTrans,@tmpLP,@dZdejmij,@CenaZ,@dCenaS
		if @lRes <> 0
			break
		UPDATE Przyroz SET IloscNU = @Ilosc WHERE IdPR = @IdPR
	end
	CLOSE CurMar
	deallocate CurMar
	if @lRes <> 0
		return @lRes
	set @tmpLP = -@LP
	if @dIlosc < -@NAVO_EPSILON
		exec @lRes = SQLPrzyRoz_Insert2 0,@IdArt,@IdMag,@pDate,@cTT,@IdTrans,@tmpLP,@dIlosc,0.0,@dCenaS
	return @lRes


GO
drop Procedure SQLPrzyRoz_Insert2
go
Create Procedure SQLPrzyRoz_Insert2
	@IdPROrg int,@IdArt int,@IdMag int,
	@pDate datetime,@cTT char,@IdTrans int,@LP int,
	@Ilosc numeric(12,3),@CenaZ numeric(12,2),@CenaS numeric(12,2)
As
	INSERT INTO Przyroz VALUES (@IdPROrg,@IdArt,@IdMag,
		@pDate, @cTT,@IdTrans,@LP,@Ilosc,@Ilosc,@CenaZ,@CenaS)
	if @@error <> 0 
		return (1)
	if @LP > 0
		--DODANE ABY USUNAC TRIGGER:  PrzyrozIns after insert
		exec SQLInsUpdKontrolaSM @IdArt, @IdMag, @pDate, @Ilosc

	return (0)

go
drop procedure SQLProc_MakePrzychOnPtr2
go 
CREATE Procedure SQLProc_MakePrzychOnPtr2
	@IdArt int,@IdMag int,@IdTrans int, @LP int,
	@pDate datetime, @IdTransOrg int,
	@dIlosc numeric(12,3),@dCenaS numeric(12,2),@cTT char,
	@NAVO_EPSILON numeric(12,3)

As
	declare @lRes int
	declare @dWspolcz numeric(12,3)
	declare @dPozostalo numeric(12,3)
	declare @IdTransTemp int
	declare @IdPRTemp int
	declare @IloscTemp numeric(12,3)
	declare @CenaZTemp numeric(12,2)
	declare @IloscToInsert numeric(12,3)
	declare @IloscNU numeric(12,3)
	declare @DataWyst datetime
	declare @DataZamOkresu datetime
	declare @bArch int
	declare @Iter int
	declare @IdTransOld int
	declare @noOfDay int
	set @Iter = 0
	set @IdTransTemp = @IdTrans


	if @cTT = 'O'
	begin
		declare @TempData varchar (20)
		set @TempData= (SELECT Value FROM NavoVars WHERE IdVar=90)		
--		PRINT 'Temp Data = ' + @TempData
		
		set @DataZamOkresu = CONVERT( DATETIME, @TempData, 105)
--		PRINT 'Data zamkniecia = ' +str(DAY (@DataZamOkresu)) + '-' +str(MONTH(@DataZamOkresu)) +'-'+str(YEAR(@DataZamOkresu))

			
		set @bArch = 0
		set @dPozostalo = @dIlosc
		
		WHILE (@dPozostalo > @NAVO_EPSILON)
		begin
			--ZnajdŸ IdTransOrg i datê wystawienia orygina³u
			--Zamienia @IdTransTemp na IdTrans Orygina³u
			exec @lRes = SQLProc_GetIdTransOrigFromCorrection @IdTransTemp, @cTT,@DataWyst out, @IdTransTemp out	
			if @lRes != 0
				raiserror('SQLProc_GetIdTransOrigFromCorrection nieudane: IdTrans = %d, Typ = %s (%d)' ,16, 1, @IdTransTemp,@cTT, @lRes )  
									
--			PRINT 'Data wyst = ' +str(DAY (@DataWyst)) + '-' +str(MONTH(@DataWyst)) +'-'+str(YEAR(@DataWyst))
			

			set @noOfDay =  DATEDIFF(day,  @DataWyst, @DataZamOkresu)
--			PRINT 'Days = ' + str(@noOfDay)
			if @noOfDay >0 --@DataZamOkresu > @DataWyst -- Szukaj w przyroz_arch
			begin	
				DECLARE FindRozchod CURSOR FOR SELECT IdPR, Ilosc, IloscNU, CenaZ FROM przyroz_arch WHERE LP = - @LP AND IloscNU <0 AND IdTrans = @IdTransTemp ORDER BY IdPR desc
				set @bArch = 1
--				PRINT '@DataZamOkresu > @DataWyst  ' 
	--			PRINT 'FIND IN ARCH IdTrans = ' + str( @IdTransTemp) + 'LP = ' +str(- @LP)
			end
			else
			begin
				DECLARE FindRozchod CURSOR FOR SELECT IdPR, Ilosc, IloscNU, CenaZ FROM przyroz WHERE LP = -@LP AND IloscNU <0 AND IdTrans = @IdTransTemp ORDER BY IdPR desc
				set @bArch = 0
--				PRINT '@DataZamOkresu <= @DataWyst  ' 
			end

			OPEN FindRozchod
			
			FETCH NEXT FROM FindRozchod INTO  @IdPRTemp,  @IloscTemp,@IloscNU, @CenaZTemp
			while (@@FETCH_STATUS = 0 AND @dPozostalo > @NAVO_EPSILON)
			begin
				if (@dPozostalo >= -@IloscTemp)
				begin
					set @IloscToInsert = - @IloscTemp
				end
				
				if (@dPozostalo < -@IloscTemp)
				begin
					set @IloscToInsert = @dPozostalo
				end
				declare @LPmin int
				set @LPmin = -@LP
				declare @IdPRTempmin int

				exec @lRes = SQLPrzyRoz_Insert2 @IdPRTemp, @IdArt, @IdMag, @pDate, @cTT, @IdTrans, @LPmin, @IloscToInsert, @CenaZTemp, @dCenaS

				if @lRes <> 0 
					raiserror('SQLPrzyRoz_Insert nieudane: IdTrans = %d, Typ = %s (%d)' ,16, 1, @IdTransTemp,@cTT, @lRes )  
				
				set @dPozostalo = @dPozostalo - @IloscToInsert
				
				if @bArch = 0
					UPDATE Przyroz SET IloscNU = (@IloscNU+ @IloscToInsert) WHERE IdPR =@IdPRTemp
				else
					UPDATE Przyroz_arch SET IloscNU = (@IloscNU+ @IloscToInsert) WHERE IdPR =@IdPRTemp
				
				FETCH NEXT FROM FindRozchod INTO  @IdPRTemp, @IloscTemp, @IloscNU,@CenaZTemp
				
				set @Iter = @Iter + 1
				if @Iter > 100
					raiserror('Nie znalaz³ dokumentu rozchodowego dla korekty przychodowej: IdTrans = %d ' ,16, 1, @IdTrans)  
			end

			CLOSE FindRozchod
			DEALLOCATE FindRozchod
						
			set @Iter = @Iter + 1
			if @Iter > 100
				raiserror('Nie znalaz³ dokumentu rozchodowego dla korekty przychodowej: IdTrans = %d ' ,16, 1, @IdTrans)  

		end
	return (0)
	end
	else --dla 'K'(MMA+) i 'J' (MM)
	begin
		declare @IdPR int
		declare @Ilosc numeric(12,3), @CenaZ numeric(12,2)
		declare @tmpLP int
		declare @tmpCena numeric(12,2)

		-- pobierz oryginal
		--if (@cTT='O' or @cTT='E')
		--begin
		--	if @LP>0
		--	begin
		--		declare @TmpIdOrig int
		--		set @TmpIdOrig = 0
		--		exec SQLProc_GetPROrigFromCorrection @IdTransOrg, @LP, @dCenaS, @TmpIdOrig out
		--		if @TmpIdOrig<>0
		--			set @IdTransOrg = @TmpIdOrig
		--	end
		--end

		DECLARE myx CURSOR FOR SELECT IdPR,IloscNU,CenaZ 
			FROM Przyroz WHERE IdPR = (SELECT min(IdPR) FROM Przyroz
			WHERE IdTrans = @IdTransOrg AND LP = - @LP)
		if @@error <> 0 
			return (1)
		open myx
		fetch next from myx into @IdPR, @Ilosc, @CenaZ
		if (@@error <> 0)
			return (1)
		close myx
		deallocate myx

		if @cTT = 'J'  --MM rozne waluty
		begin
			SET @dWspolcz = (SELECT Kurs*(1.0+(case
					when PrzesMM.DoliczClo = 'T' THEN Artykul.CloPoGr 
					ELSE 0.0 
					END)/100.0)
				FROM PrzesMM
				JOIN PozMM ON PozMM.IdTrans = PrzesMM.IdTrans
				JOIN Artykul ON Artykul.IdArt = PozMM.IdArt
				WHERE PozMM.IdTrans = @IdTransOrg AND PozMM.LP = @LP)
			if @@error <> 0 
				return (1)
		end
		else
			set @dWspolcz = 1.0

		if @@rowcount > 0
			begin
				if (-@Ilosc >= @dIlosc)
				begin
					set @tmpLP = -@LP
					set @tmpCena = (@CenaZ * @dWspolcz)
					exec @lRes = SQLPrzyRoz_Insert2 @IdPR, @IdArt, @IdMag, @pDate, @cTT, @IdTrans, @tmpLP, @dIlosc, @tmpCena, @dCenaS
					if @lRes <> 0 
						return (@lRes)
					set @Ilosc = @Ilosc + @dIlosc
					UPDATE Przyroz SET IloscNU = @Ilosc WHERE IdPR = @IdPR
					set @lRes = @@error
					return @lRes
				end
			end

		CREATE TABLE #IdPR_IloscNU_CenaZ
		(
				IdPR              int PRIMARY KEY,
				IloscNU          numeric(15,3) NULL,
				CenaZ            numeric(12,2) NULL,
		)
		TRUNCATE TABLE #IdPR_IloscNU_CenaZ

		-- trzeba brac pod uwage CenaS, bo dla wiekszej ilosci korekt bedzie za duzo rekordow
		INSERT INTO #IdPR_IloscNU_CenaZ
		SELECT IdPR,IloscNU,CenaZ FROM Przyroz
			WHERE IdTrans = @IdTransOrg AND LP = - @LP and CenaS=@dCenaS ORDER BY IdPR


		DECLARE CurMap CURSOR FOR SELECT IdPR,IloscNU,CenaZ
			FROM #IdPR_IloscNU_CenaZ
			ORDER BY IdPR

		OPEN CurMap
		declare @dWprowadz numeric(12,3)

		while @dIlosc > @NAVO_EPSILON
		begin
			FETCH NEXT FROM CurMap INTO @IdPR, @Ilosc, @CenaZ

			if @@fetch_status <> 0 
				break
			if @@error <> 0 
				break

			if -@Ilosc >= @dIlosc
				begin
					set @dWprowadz = @dIlosc
					set @Ilosc = @Ilosc + @dIlosc
					set @dIlosc = 0.0
				end
			else
				begin
					set @dWprowadz = -@Ilosc
					set @dIlosc = @dIlosc - @dWprowadz
					set @Ilosc = 0.0
				end
			set @tmpLP = -@LP
			set @tmpCena = (@CenaZ * @dWspolcz)
			exec @lRes = SQLPrzyRoz_Insert2 @IdPR,@IdArt,@IdMag,@pDate,@cTT,@IdTrans,@tmpLP,@dWprowadz,@tmpCena,@dCenaS
			if @lRes <> 0 
				break
			UPDATE Przyroz SET IloscNU = @Ilosc WHERE IdPR = @IdPR
		end
		CLOSE CurMap
		deallocate CurMap

		if @dIlosc > @NAVO_EPSILON
			return 0
		if @lRes <> 0 
			return (@lRes)
		return (0)
	end


GO

create procedure SQLProc_Naprawa as

declare @cTT char(2)
declare @idArt integer
declare @IdMag integer
declare @dDateOp datetime
declare @idTrans integer
declare @iLP integer
declare @curIlosc decimal(14,4)
declare @idPrOrg integer
declare @curCenaZ decimal(12,2)
declare @curCenaS decimal(12,2)
declare @cT char(1)
declare @iResult integer
declare @minusLP integer
print 'start of SQLProc_naprawa'
print 'deleting lp<0 from przyroz'
delete from przyroz where LP < 0
print 'updating iloscnu'
update przyroz set iloscnu=ilosc
print 'opening main cursor'
set @iResult = 0
declare crsr cursor forward_only for select
TypTran,IdArt,IdMag,DataPR,IdTrans,LP,Ilosc,IdPROrg,CenaZ,CenaS 
FROM naprawa_pr WHERE LP > 0 ORDER BY DataPR,kwal,IdTrans,LP,TypTran
OPEN crsr
FETCH NEXT FROM crsr INTO @cTT,@idArt,@idMag,@dDateOp,@idTrans,@iLP,@curIlosc,@idPrOrg,@curCenaZ,@curCenaS
while @@fetch_status = 0
begin
select @cT = left(@ctt,1)
--print str(@idTrans) + ',' + str(@iLP) 
if @ct = 'O' or @ct = 'K' or @ct = 'J'
begin
--print 'SQLProc_MakePrzychOnPtr ' + str(@idtrans)
exec @iResult = SQLProc_MakePrzychOnPtr2 @idArt,@idMag,@idTrans,@iLP,@dDateOp,@idPrOrg,@curIlosc,@curCenaS,@ct,0.0001
end
else
if @ct = 'A' or @ct = 'E' or @ct = 'C' or @ct = 'I' or @ct = 'U'
begin
--print 'SQLPrzyRoz_Insert ' + str(@idtrans)
set @minusLP = - @iLP
exec @iResult = SQLPrzyRoz_Insert2 0,@IdArt,@IdMag,@dDateOp,@ct,@IdTrans,@minusLP,@curIlosc,@curCenaZ,0.0
end
else
if @ct = 'G' or @ct = 'R' or @ct = 'M' or @ct= 'N'
or @ct = 'T' or @ct = 'D'
begin
--print 'SQLProc_MakeRozchOnOrder ' + str(@idtrans)
exec @iResult = SQLProc_MakeRozchOnOrder2 @IdArt,@IdMag,@IdTrans,@iLP,@dDateOp,@curIlosc,@curCenaS,@ct,0.0001
end
else
if @ct = 'W' 
begin
--print 'SQLProc_MakeRozchOnPtr ' + str(@idtrans)
exec @iResult = SQLProc_MakeRozchOnPtr2 @IdArt,@IdMag,@IdTrans,@iLP,@dDateOp,@IdPROrg,@curIlosc,@curCenaS,@ct,0.0001
end 
if @iResult <> 0 
begin
print 'error at idtrans=' + str(@idtrans) + ',' + str(@ilp) + ',code=' + str(@iResult)
end 
FETCH NEXT FROM crsr INTO @cTT,@idArt,@idMag,@dDateOp,@idTrans,@iLP,@curIlosc,@idPrOrg,@curCenaZ,@curCenaS
end 
CLOSE crsr
deallocate crsr

--SQLProc_Naprawa 
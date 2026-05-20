
-- gdy DB11 rozszerz do DB12 jednym skryptem
if not exists (select * from sys.columns where name = 'grp_iDataWaznosci') --pole dodane w DB11_B 
	begin
		PRINT N'Wersja DB11'
		PRINT N'Uruchomiæ skrypt:'
		PRINT N'upgrade_db11_to_db12.sql'
	end
else
	-- gdy DB11_B rozszerz do DB11_C
	if not exists (select * from sys.columns where name = 'kli_cDokumentyInfo') --pole dodane w DB11_C 
		begin
			PRINT N'Wersja DB11_B'
			PRINT N'Uruchomiæ skrypty wg kolejnoœci:'
			PRINT N'upgrade_db11b_to_db11c.sql'
			PRINT N'upgrade_db11c_to_db11d.sql'
			PRINT N'upgrade_db11d_to_db11e.sql'
			PRINT N'upgrade_db11e_to_db11f.sql'
			PRINT N'upgrade_db11f_to_db12.sql'
		end
	else
		-- gdy DB11_C rozszerz do DB11_D
		if not exists (select * from sys.columns where name = 'kli_iTerminSkonta') --pole dodane w DB11_D 
			begin
				PRINT N'Wersja DB11_C'
				PRINT N'Uruchomiæ skrypty wg kolejnoœci:'
				PRINT N'upgrade_db11c_to_db11d.sql'
				PRINT N'upgrade_db11d_to_db11e.sql'
				PRINT N'upgrade_db11e_to_db11f.sql'
				PRINT N'upgrade_db11f_to_db12.sql'
			end
		else
			-- gdy DB11_D rozszerz do DB11_E
			if not exists (select * from sys.columns where name = 'ank_pUzytRej') --pole dodane w DB11_E
				begin
					PRINT N'Wersja DB11_D'
					PRINT N'Uruchomiæ skrypty wg kolejnoœci:'
					PRINT N'upgrade_db11d_to_db11e.sql'
					PRINT N'upgrade_db11e_to_db11f.sql'
					PRINT N'upgrade_db11f_to_db12.sql'
				end
			else
				-- gdy DB11_E rozszerz do DB11_F
				if not exists (select * from sys.columns where name = 'prod_pZamiennik1') --pole dodane w DB11_F
					begin
						PRINT N'Wersja DB11_E'
						PRINT N'Uruchomiæ skrypty wg kolejnoœci:'
						PRINT N'upgrade_db11e_to_db11f.sql'
						PRINT N'upgrade_db11f_to_db12.sql'
					end
				else
					-- gdy DB11_F rozszerz do DB12
					if not exists (select * from sys.columns where name = 'kli_cCzynnyPodatnikVAT') --pole dodane w DB12
						begin
							PRINT N'Wersja DB11_F'
							PRINT N'Uruchomiæ skrypt:'
							PRINT N'upgrade_db11f_to_db12.sql'
						end
					else
						-- gdy DB12 rozszerz do DB12_B
						if not exists (select * from sys.columns where name = 'scs_strNazwa') --pole dodane w DB12_B
							begin
								PRINT N'Wersja DB12'
								PRINT N'Uruchomiæ skrypt:'
								PRINT N'upgrade_db12_to_db12b.sql'
							end
						else
							PRINT N'Wersja DB12_B. Nie ma potrzeby uruchamiania skryptu.'

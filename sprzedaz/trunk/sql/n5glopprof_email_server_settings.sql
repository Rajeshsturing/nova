
-- ustawienia serwera pocztowego oraz konta z którego wysy³ane s¹ wiadomoœci
-- 'serwer_poczty_wychodz¹cej;port_serwera;czy_uzywac_SSL;czy_uzywac_domyœlnych_poswiadczen;adres_nadawcy;haslo'
insert into n5globprof select (select max(idobj) from n5globprof)+1,1,1101,'XXXXXX;587;0;0;XXXXXX;XXXXXX'

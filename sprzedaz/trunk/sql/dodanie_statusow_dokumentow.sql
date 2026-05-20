
-- statusy dokumentów (Zamówienie obce)
IF NOT EXISTS (SELECT 1 FROM n5dokstatus WHERE dcs_strNazwa = 'Do realizacji')
INSERT INTO n5dokstatus (IdObj,VersionId,dcs_strNazwa,dcs_strTypDok)
VALUES (isnull((select max(IdObj)+1 from n5dokstatus),1),1,'Do realizacji','0000000010000000000000000')
GO

IF NOT EXISTS (SELECT 1 FROM n5dokstatus WHERE dcs_strNazwa = 'Bufor')
INSERT INTO n5dokstatus (IdObj,VersionId,dcs_strNazwa,dcs_strTypDok)
VALUES (isnull((select max(IdObj)+1 from n5dokstatus),1),1,'Bufor','0000000010000000000000000')
GO

IF NOT EXISTS (SELECT 1 FROM n5dokstatus WHERE dcs_strNazwa = 'Zrealizowane')
INSERT INTO n5dokstatus (IdObj,VersionId,dcs_strNazwa,dcs_strTypDok)
VALUES (isnull((select max(IdObj)+1 from n5dokstatus),1),1,'Zrealizowane','0000000010000000000000000')
GO

IF NOT EXISTS (SELECT 1 FROM n5dokstatus WHERE dcs_strNazwa = 'W realizacji')
INSERT INTO n5dokstatus (IdObj,VersionId,dcs_strNazwa,dcs_strTypDok)
VALUES (isnull((select max(IdObj)+1 from n5dokstatus),1),1,'W realizacji','0000000010000000000000000')
GO
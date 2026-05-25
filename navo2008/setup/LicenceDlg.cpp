// LicenceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "wizzarddlg.h"
#include "LicenceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLicenceDlg dialog


CLicenceDlg::CLicenceDlg(CWnd* pParent /*=NULL*/)
	: CWizzardDlg(CLicenceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLicenceDlg)
	m_strLicenceTxt = _T("");
	//}}AFX_DATA_INIT
}


void CLicenceDlg::DoDataExchange(CDataExchange* pDX)
{
	CWizzardDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLicenceDlg)
	DDX_Text(pDX, IDC_EDIT, m_strLicenceTxt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLicenceDlg, CWizzardDlg)
	//{{AFX_MSG_MAP(CLicenceDlg)
	ON_BN_CLICKED(ID_NEXT, OnNext)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLicenceDlg message handlers
BOOL CLicenceDlg::OnInitDialog() 
{
	CWizzardDlg::OnInitDialog();
	m_strLicenceTxt = 

"UMOWA LICENCYJNA I OGRANICZONA GWARANCJA NAVO\r\n NA OPROGRAMOWANIE.\r\n"
"Uwaga!\r\n"
"Przed zainstalowaniem oprogramowania nale¿y zapoznaæ\r\n"
"siê z poni¿szym tekstem,stanowi¹cym Umowê Licencyjn¹ i\r\n"
"Ograniczon¹ Gwarancjê na Oprogramowanie.Szanowny Kliencie \r\n"
"- w dalszej czêœci niniejszej umowy bêdziemy nazywaæ\r\n Ciê U¿ytkownikiem.\r\n"
"1. Umowa niniejsza zostaje zawarta miêdzy stronami,\r\n"
"czyli NAVO Sp. z o.o., a U¿ytkownikiem w chwili ca³kowitego\r\n"
"zainstalowania Oprogramowania na dysku twardym komputera.\r\n"
"Instaluj¹c Oprogramowanie, U¿ytkownik zgadza siê z \r\n"
"postanowieniami niniejszej umowy. U¿ytkownik, który \r\n"
"nie akceptuje Umowy Licencyjnej i Ograniczonej Gwarancji na\r\n"
"Oprogramowanie powinien przerwaæ instalacjê w tym punkcie\r\n"
"i niezw³ocznie zwróciæ niezainstalowany pakiet wraz z\r\n"
"dyskietkami lub CD-ROM oraz towarzysz¹ce mu materia³y - \r\n"
"uzyska wówczas zwrot pieniêdzy do wysokoœci zap³aconej kwoty,\r\n"
"pomniejszonej o koszty manipulacyjne.\r\n"
"2. Przedmiotem Umowy jest udzielenie Licencji U¿ytkownikowi,\r\n"
"która daje prawo do u¿ytkowania jednej kopii Oprogramowania na \r\n"
"pojedynczym komputerze. Oprogramowanie jest u¿ytkowane na\r\n"
"pojedynczym komputerze, wówczas gdy za³adowane jest do \r\n"
"tymczasowej pamiêci RAM komputera lub zainstalowane jest w\r\n"
"pamiêci sta³ej tego komputera.\r\n"
"3. Prawa Autorskie - Oprogramowanie jest wy³¹czn¹ w³asnoœci¹\r\n"
"NAVO Sp. z o.o. i jest chronione prawem autorskim jako \r\n"
"odrêbny przedmiot tego¿ prawa.U¿ytkownikowi i Dystrybutorom \r\n"
"zabrania siê bez uprzedniego pisemnego zezwolenia NAVO Sp. z o.o.\r\n"
"odstêpowania, po¿yczania, powielania, t³umaczenia \r\n"
"lub jakiejkolwiek innej formy rozpowszechniania i \r\n"
" udostêpniania Oprogramowania oraz Instrukcji Obs³ugi\r\n"
"osobom trzecim. Zabrania siê równie¿ t³umaczenia, \r\n"
"zmieniania, dekompilowania lub jakiejkolwiek innej\r\n"
"formy ingerowania w Oprogramowanie oraz tworzenia opracowañ\r\n"
"i rozszerzeñ bêd¹cych pochodn¹ Oprogramowania lub Instrukcji Obs³ugi.\r\n"
"4. Za³¹czona Licencja stanowi dowód zawarcia Umowy Licencyjnej\r\n"
"i musi byæ przez U¿ytkownika zachowana. U¿ytkownik nie mo¿e wynaj¹æ\r\n"
"lub wydzier¿awiæ Oprogramowania, mo¿e natomiast przenieœæ na\r\n"
"sta³e swoje prawa nabyte na mocy niniejszej Licencji.Warunkiem\r\n"
"przeniesienia Praw W³asnoœci na Oprogramowanie jest przekazanie \r\n"
"ca³ego Oprogramowania na oryginalnych noœnikach danych wraz z\r\n"
"Instrukcj¹ Obs³ugi i wszystkimi materia³ami towarzysz¹cymi.\r\n"
"Przekazanie Praw W³asnoœci musi zawieraæ ostatnie uaktualnienia\r\n"
"i wszystkie poprzednie wersje, oraz o przekazaniu w³asnoœci nale¿y \r\n"
"skutecznie zawiadomiæ NAVO Sp. z  o.o.\r\n"
"5. U¿ytkownikowi przys³uguje Ograniczona Gwarancja na okres\r\n"
"90 dni od daty zakupu Oprogramowania oraz w tym okresie prawo\r\n"
"do bezp³atnej porady i informacji telefonicznej (poza kosztami\r\n"
"telekomunikacyjnymi).Ograniczona Gwarancja dotyczy wy³¹cznie\r\n"
"funkcjonalnej zgodnoœci Oprogramowania z Instrukcj¹ Obs³ugi.\r\n"
"W przypadku gdy Oprogramowanie wspó³dzia³a z oprogramowaniem\r\n"
"innych producentów, NAVO gwarantuje zgodnoœæ Oprogramowania\r\n"
"ze Specyfikacj¹ udostêpnian¹ przez tych producentów. Ograniczona\r\n"
"Gwarancja nie dotyczy ca³kowitej bezb³êdnoœci Oprogramowania, \r\n"
"w szczególnoœci zaœ tego, ¿e zaspokoi ono wszystkie wymagania \r\n"
"U¿ytkownika. Odpowiedzialnoœæ za prawid³owy wybór i skutki \r\n"
"stosowania Oprogramowania, a zarazem zamierzone lub uzyskane \r\n"
"wyniki ponosi wy³¹cznie U¿ytkownik.\r\n"
"NAVO Spó³ka z o.o. i jej dystrybutorzy nie ponosz¹ ¿adnej \r\n"
"odpowiedzialnoœci za powsta³e uszkodzenia i straty w tym utratê \r\n"
"zysków, utratê informacji handlowej,ani straty pieniê¿ne wynik³e \r\n"
"z u¿ytkowania lub niemo¿noœci u¿ytkowania Oprogramowania,\r\n"
"nawet wówczas gdy NAVO jest zawiadomiona o mo¿liwoœci\r\n"
"powstania takich uszkodzeñ lub strat.W jakimkolwiek przypadku\r\n"
"ca³kowita odpowiedzialnoœæ NAVO i dystrybutorów bêdzie\r\n"
"ograniczona maksymalnie do sumy zap³aconej za Oprogramowanie.\r\n"
"6. Ca³kowita odpowiedzialnoœæ NAVO sprowadza siê, albo do\r\n"
"zwrotu ceny zap³aconej za Oprogramowanie albo do naprawy lub\r\n"
"wymiany czêœci Oprogramowania, które nie zgadzaj¹ siê z\r\n"
"Ograniczon¹ Gwarancj¹ i które zostan¹ zwrócone NAVO wraz \r\n"
"z kopi¹dokumentu nabycia. Wybór uprawnieñ nale¿y do NAVO.\r\n"
"Ograniczona Gwarancja nie ma zastosowania jeœli wada\r\n"
" Oprogramowaniajest rezultatem wypadku, niew³aœciwego\r\n"
"u¿ytkowania, lub zastosowania oraz zainstalowania go\r\n"
"na wadliwym sprzêcie komputerowym lub w wypadku \r\n"
"b³êdów wynikaj¹cych z nieprawid³owej instalacji lub \r\n"
"funkcjonowania systemów operacyjnych, na których \r\n"
"dzia³a Oprogramowanie lub w wyniku obecnoœci lub u¿ytkowania\r\n"
"innego oprogramowania\r\n"
"7. Legalny U¿ytkownik ma prawo do nabycia na preferencyjnych\r\n"
"warunkach tzw. upgrade nowych wersji Oprogramowania.\r\n"
"Wymiana wersji starej na now¹ jest realizowana przez \r\n"
"NAVO Sp. z o.o. lub jej Dystrybutorów wy³¹cznie dla \r\n"
"legalnych U¿ytkowników.\r\n"
"8. NAVO Spó³ka z o.o. zobowi¹zuje siê do udzielania porad i\r\n"
"informacji za dodatkow¹ odp³atnoœci¹, po ukoñczeniu okresu \r\n"
"gwarancji, a dotycz¹cych funkcjonowania oprogramowania. \r\n"
"Zakres i dostêpnoœæ tych us³ug zale¿y od aktualnych mo¿liwoœci\r\n" 
"technicznych i organizacyjnych NAVO Spó³ka z o.o.\r\n"
"9. Je¿eli do zakupionego oprogramowania za³¹czona jest formie\r\n"
"pisemnej umowa licencyjna o innej treœci ni¿ niniejsza, to \r\n"
"postanowienia tamtej umowy s¹ wi¹¿¹ce.\r\n\r\nNAVO Sp. z o.o.";

		

	UpdateData(FALSE);
	return TRUE;
}

void CLicenceDlg::OnNext() 
{
	EndDialog(ID_NEXT);
}

void CLicenceDlg::OnBack() 
{
	EndDialog(IDC_BACK);
}



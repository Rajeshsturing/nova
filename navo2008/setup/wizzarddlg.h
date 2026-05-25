/*
	NAVO Enterprise 2020
	setup application
*/

#ifndef _WIZZARDDLG_H_
#define _WIZZARDDLG_H_

class CPictureButton: public CBitmapButton
{
public:
	CPictureButton()
	{
	};
	bool LoadPicture(UINT nResource, CWnd * pParent);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);

private:
	CPalette m_palette;
};

class CWizzardDlg : public CDialog
{
public:
	CWizzardDlg(UINT nIDTemplate, CWnd* pParentWnd = NULL) :
		CDialog(nIDTemplate,pParentWnd)
	{}

protected:
	virtual BOOL OnInitDialog()
	{
		CDialog::OnInitDialog();
		m_oPicture.LoadPicture(IDC_PICTURE, this);
		return TRUE;
	}

	CPictureButton m_oPicture;
};

#else
	#error __FILE__ already included
#endif

/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	class:
		CTreeDataProvider__ = 	abstract class for different tree data providers
		CTreeXMLDataProvider=	implementation for XML files (currently on DOM)
*/


#ifndef _TREEDATAPROV_H_
#define _TREEDATAPROV_H_


class CTreeDataProvider__ : public CInterface__
{
protected:
	CTreeDataProvider__();
public:
	virtual void GetChildren(long IdNode,CArray<long,long> & roChildrenArray) = 0;
	virtual SCP<CHyperLinkInfo> GetNode(long IdNode) = 0;
};

class CTreeXMLDataProvider : public CTreeDataProvider__
{
public:
	CTreeXMLDataProvider(SCP<IStream> & rpoInputStreamSP);
	virtual void GetChildren(long IdNode,CArray<long,long> & roChildrenArray);
	virtual SCP<CHyperLinkInfo> GetNode(long IdNode);
	bool Add2Menu(long IdNode);
	SCP<IDispatch> get_automation_object();
private:
	class CNodeInfo : public CInterface__
	{
	public:
		CNodeInfo() :
			m_bAdd2Menu(true)
		{
		}
		
		CArray<long,long> m_oChildrenArray;
		SCP<CHyperLinkInfo> m_poHLISP;
		bool m_bAdd2Menu;
	};
	
	SCP<CNodeInfo> _get_node(long IdNode);

	CMap<long,long,SCP<CNodeInfo>,SCP<CNodeInfo> & > m_oNodesMap; 

	friend class CTreeXMLSAXHandler;
	friend class CTreeXMLNodeAutoObject;
	friend class CTreeXMLAutoObject;
};

#else
	#error __FILE__ already included
#endif


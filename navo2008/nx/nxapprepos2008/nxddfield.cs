using System;

namespace nxapprepos
{
	namespace nxdd
	{
		/// <summary>
		/// podstawowy element Data Description
		/// </summary>
		public abstract class nxdd_field_
		{
			public nxdd_field_(nxdd_field_block oOwner,string strFieldName)
			{
				m_oOwner = oOwner;
				m_strName = strFieldName;

				m_bUnique = false;
				m_bRequired = false;
				m_bHidden = false;

				m_oBrowserFieldDisplay = null;
				m_oSuggestionFieldDisplay = null;
				m_oFormBuildDisplay = null;
			}
			
			/// <summary>
			/// return expression code for geting pseudo-field value
			/// </summary>
			public string getexpression
			{
				get
				{
					return m_strGetExpression;
				}
				set
				{
					m_strGetExpression = value;
				}
			}
			#region Presentation
			/// <summary>
			/// zwraca funkcje odpowiedzialna za wyswietlanie pole
			/// "browser" - listy i typowa reprezentacja 'view-only'
			/// "suggestion_text" - dla celow tworzenia podpowiedzi
			/// </summary>
			/// <param name="strUsage"></param>
			/// <returns></returns>
			public nxobjfield.field_display get_display(string strUsage)
			{
				switch(strUsage[0])
				{
					case 'b':	//browser
						return m_oBrowserFieldDisplay;
					case 's':	//suggestion_text
						return m_oSuggestionFieldDisplay;
					case 'f':
						return m_oFormBuildDisplay;
					default:
					{
						return null;
					}
				}
			}
			#endregion

			#region persistency info
			public abstract int persistent_col_count
			{
				get;
			}
			public abstract int persistent_col_sqltype(int iColNr);
			public abstract string persistent_col_name(int iColNr);
			#endregion
			#region basic information
			public nxdd_field_block owner
			{
				get
				{
					return m_oOwner;
				}
			}
			
			public nxdd_object top_owner
			{
				get
				{
					nxdd_field_block oOwner = owner;
					while(oOwner.owner != null)
					{
						oOwner = oOwner.owner;
					}
					return (nxdd_object) oOwner;
				}
			}
			/// <summary>
			/// field's local name (as visible from inside of direct owner)
			/// </summary>
			public string local_name
			{
				get
				{
					return m_strName;
				}
				set
				{
					m_strName = value;
				}
			}

			/// <summary>
			/// returns field's full name, as visible from top-level object
			/// </summary>
			public string full_name
			{
				get
				{
					return owner.full_prefix + local_name;
				}
			}
			/// <summary>
			/// field's local (short) human name
			/// </summary>
			public string local_human_name
			{
				get
				{
					return m_strHumanName;
				}
				set
				{
					m_strHumanName = value;
				}
			}

			#endregion
			#region flags
			/// <summary>
			/// is field unique
			/// </summary>
			public bool unique
			{
				get
				{
					return m_bUnique;
				}
				set
				{
					m_bUnique = value;
					if(m_bUnique)
					{
						m_bRequired = true;
					}
				}
			}

			/// <summary>
			/// is field required
			/// </summary>
			public bool required
			{
				get
				{
					return m_bRequired;
				}
				set
				{
					m_bRequired = value;
				}
			}

			/// <summary>
			/// is field hidden
			/// </summary>
			public bool hidden
			{
				get
				{
					return m_bHidden;
				}
				set
				{
					m_bHidden = value;
				}
			}

			#endregion
			#region data members
	
			protected string m_strName;	//field name
			protected string m_strHumanName; //human name

			//--- flags --
			private bool m_bUnique;		//field holds unique values
			private bool m_bRequired;	//field must be non-empty
			private bool m_bHidden;		//field is hidden to end-user

			protected string m_strSQLExp4String;	//wyrazenie w SQL dla reprezentacji pola jako napis

			private nxobjfield.field_display m_oBrowserFieldDisplay;	//"display" for browser
			private nxobjfield.field_display m_oSuggestionFieldDisplay; //"display" for suggestion
			private nxobjfield.field_display m_oFormBuildDisplay;		//"display" for building forms

			private string m_strGetExpression;	//expression to retrieve field's value

			protected nxdd_field_block m_oOwner;
			#endregion
		}

	}
}

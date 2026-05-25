using System;
using System.Runtime.InteropServices;
using nxappcore;
using nxuibuilder;
using nxapprepos;
using rdbinding = nxapprepos.raportdefinition.filter.binding;

namespace nxraport_param
{
	/// <summary>
	/// base class for raport parameters
	/// 
	/// base form:
	/// bindexpression in (select idobj from table_name where compareexpression = ...)
	/// but also
	/// (1=1)
	/// etc.
	/// </summary>
    [ComVisible(true)]
    [GuidAttribute(global_config.gc_guid_nxraport_raportparam_)]
    public abstract class raportparam_
	{
		public raportparam_(repository oRepository,nxobjfield oCompareFieldInfo,
			string strCompareExpression,string strBindExpression,
			string strCompareCondition)
		{
			m_oCompareFieldInfo = oCompareFieldInfo;
			m_oRepository = oRepository;
			m_strHumanName = display.elipsis(oCompareFieldInfo.human_name_with_object,25);
			m_strCompareExpression = strCompareExpression;
			m_strBindExpression = strBindExpression;
			m_strCompareCondition = strCompareCondition;
			m_bAutoAnswer = false;
		}

		/// <summary>
		/// human readable name
		/// </summary>
		public string human_name
		{
			get
			{
				return m_strHumanName;
			}
		}

		/// <summary>
		/// expression used to build condition
		/// </summary>
		public string compare_expression
		{
			get
			{
				return m_strCompareExpression;
			}
		}

		public string compare_condition
		{
			get
			{
				return m_strCompareCondition;
			}
		}

		public string and_prepared_comp_cond
		{
			get
			{
				if(compare_condition == "")
				{
					return "";
				}
				else
				{
					return " and (" + String.Format(compare_condition,table_name) + ") ";
				}
			}
		}

		public string bind_expression
		{
			get
			{
				return m_strBindExpression;
			}
		}

		public string table_name
		{
			get
			{
				return m_oCompareFieldInfo.parent.table_name;
			}
		}
		
		/// <summary>
		/// czy parametr wymaga pytania sie uzytkownika
		/// czy tez jego ustawienia sa juz odpowiedzia ?
		/// </summary>
		
		public bool autoanswer
		{
			get
			{
				return m_bAutoAnswer;
			}
			set
			{
				m_bAutoAnswer = value;
			}
		}

		public abstract void build_ui_part(object oAspatorObject,int idParam);
		public abstract string build_where_part();

		protected readonly repository m_oRepository;
		protected readonly nxobjfield m_oCompareFieldInfo;
		protected readonly string m_strCompareExpression;
		protected readonly string m_strCompareCondition;
		protected readonly string m_strBindExpression;
		protected readonly string m_strHumanName;
		protected bool m_bAutoAnswer;
	}

	/// <summary>
	/// Raport Parameter Factory - creates new parameters
	/// </summary>
	[ComVisible(true)]
	[GuidAttribute(global_config.gc_guid_nxraport_raportparamfactory)]
	public class raportparamfactory
	{
		public raportparamfactory(repository oRepository)
		{
			m_oRepository = oRepository;
		}

		public raportparamtext new_text(nxobjfield oCompareFieldInfo,
			string strCompareExpression,string strBindExpression,string strCompareCondition)
		{
			return new raportparamtext(m_oRepository,oCompareFieldInfo,strCompareExpression,
				strBindExpression,strCompareCondition);
		}

		public raportparamdaterange new_date_range(nxobjfield oCompareFieldInfo,
			string strCompareExpression,string strBindExpression,string strCompareCondition,
				DateTime dtToday)
		{
			return new raportparamdaterange(m_oRepository,oCompareFieldInfo,
				strCompareExpression,strBindExpression,strCompareCondition,dtToday);
		}

		public raportparamdate new_date(nxobjfield oCompareFieldInfo,
			string strCompareExpression,string strBindExpression,string strCompareCondition,
				DateTime dtToday)
		{
			return new raportparamdate(m_oRepository,oCompareFieldInfo,
				strCompareExpression,strBindExpression,strCompareCondition,dtToday);
		}

		public raportparammultichoice new_multichoice(nxobjfield oCompareFieldInfo,
			string strCompareExpression,string strBindExpression,string strCompareCondition)
		{
			return new raportparammultichoice(m_oRepository,oCompareFieldInfo,strCompareExpression,
				strBindExpression,strCompareCondition);
		}

		public raportparamsinglechoice new_singlechoice(nxobjfield oCompareFieldInfo,
			string strCompareExpression,string strBindExpression,string strCompareCondition)
		{
			return new raportparamsinglechoice(m_oRepository,oCompareFieldInfo,strCompareExpression,
				strBindExpression,strCompareCondition);
		}

		public raportparamcurrency new_currency(nxobjfield oCompareFieldInfo,
			string strCompareExpression,string strBindExpression,string strCompareCondition,
			string strUnit,int iPrecision)
		{
			return new raportparamcurrency(m_oRepository,oCompareFieldInfo,
				strCompareExpression,strBindExpression,strCompareCondition,
				strUnit,iPrecision);
		}

		public raportparamint new_int(nxobjfield oCompareFieldInfo,
			string strCompareExpression,string strBindExpression,string strCompareCondition)
		{
			return new raportparamint(m_oRepository,oCompareFieldInfo,strCompareExpression,
				strBindExpression,strCompareCondition);
		}

		public raportparamtime new_time(nxobjfield oCompareFieldInfo,
			string strCompareExpression,string strBindExpression,string strCompareCondition)
		{
			return new raportparamtime(m_oRepository,oCompareFieldInfo,strCompareExpression,
				strBindExpression,strCompareCondition);
		}

		//---------------------------------------------
		// helper function
		//---------------------------------------------
		public rdbinding new_binding(int iTypeId,string strFieldName,
			string strCompareExpression,string strBindingExpression,
			string strCompareCondition)
		{
			nxobjectinfo oNXObject = m_oRepository.objects[iTypeId];
			nxobjfield oNXFieldInfo = oNXObject.fields[strFieldName];
			if(strCompareExpression == "")
			{
				strCompareExpression = strFieldName;
			}
			rdbinding oBinding = new rdbinding(oNXFieldInfo,strCompareExpression,
					strBindingExpression,"",strCompareCondition);
			
			return oBinding;
		}

		private repository m_oRepository;
	}
}

//--------------------------------------------------------------------------
// NAVO.Cocoon project
// Copyright NAVO Sp. z o.o. All Rights reserved 2016-18
// 
//--------------------------------------------------------------------------

using navo.cocoon.ebwrap;

using System;
using System.Collections.Generic;
using System.Text;

namespace navo.cocoon
{
    /// <summary>conflict resolving rule for equal items</summary>
    public enum eMergeConflictMode
    {
        only_right,     //output sequence contains only element from right sequence
        only_left,      //output sequence contains only element from left sequence
        left_right,     //output sequence contains element from left sequence, then from right one
        right_left,     //output sequence contains element from right sequence, then from left one
    }

    /// <summary>
    /// Indicates to developer that a method is called by its fixed name, full type name and assembly
    /// using late bound invoke mechanism
    /// do not change name or namespace or assembly without updating properly callers</summary>
    [Serializable]
    [AttributeUsage(AttributeTargets.Method | AttributeTargets.Class, AllowMultiple = false)]
    public sealed class FixedNameAttribute : Attribute
    {
        public FixedNameAttribute()
            : base()
        {
        }
    }
    /// <summary>some IEnumerable extensions</summary>
    public static partial class IEnumerable_Extension
    {
        /// <summary>converts single object to enumerable collection</summary>
        public static IEnumerable<TType> _as_enumerable_<TType>(this TType oObject)
        {
            if (Object.Equals(oObject, default(TType)))
            {
                yield break;
            }
            else
            {
                yield return oObject;
            }
        }
        /// <summary>perform action on each item in collection</summary>
        public static void _for_each_<TType>(this IEnumerable<TType> oEnumerable, Action<TType> fpAction = null)
        {
            if (oEnumerable == null)
            {
                return;
            }
            foreach (TType item_ in oEnumerable)
            {
                if (fpAction != null)
                {
                    fpAction(item_);
                }
                else
                {
                    //this lonely semicolon forces loop iteration
                    ;
                }
            }
        }
        /// <summary>perform action on each item in collection</summary>
        public static void _for_each_<TType>(this IEnumerable<TType> oEnumerable, Action<TType, int> fpAction)
        {
            if (oEnumerable == null)
            {
                return;
            }

            int iIndex = 0;
            foreach (TType item_ in oEnumerable)
            {
                if (fpAction != null)
                {
                    fpAction(item_, iIndex++);
                }
                else
                {
                    //this lonely semicolon forces loop iteration
                    ;
                }
            }
        }
    }

    public static class Dictionary_Extension
    {
        public static TValue try_get<TKey, TValue>(this IDictionary<TKey, TValue> oDictionary, TKey oKey, TValue oNotFound = default(TValue))
        {
            TValue oFound;
            if (oDictionary.TryGetValue(oKey, out oFound))
            {
                return oFound;
            }
            else
            {
                return oNotFound;
            }
        }
    }
    /// <summary>Decimal type extensions</summary>
    public static class Decimal_Extension
    {
        /// <summary>rounds value with specified quant</summary>
        static public decimal round(this decimal curValue, int iDecimalPlaces)
        {
            //note MidpointRounding.AwayFromZero - is standard rounding (0..4 -> down, 5..9 -> up)

            return Math.Round(curValue, iDecimalPlaces, MidpointRounding.AwayFromZero);
        }
    }
    public static class DateTime_Extension
    {
        /// <summary>returns dtValue as invariant string for use in text data streams</summary>
        public static string to_data_date(this DateTime dtValue)
        {
            return dtValue.ToString("yyyy-MM-dd");
        }
        /// <summary>convert Date to SQL-safe form</summary>
        public static string to_sql_date(this DateTime dtValue)
        {
            return "{d '" + to_data_date(dtValue) + "'}";
        }
    }
    public static class _date_
    {
        public static DateTime nulldate = new DateTime(1899, 12, 31);
    }
    public static class String_Extension
    {
        /// <summary>abbreviated form of String.IsNullOrWhiteSpace</summary>
        public static bool _is_void_(this string strString)
        {
            return string.IsNullOrWhiteSpace(strString);
        }
        /// <summary>convert string to SQL-safe form (for use with LIKE expressions)</summary>
        public static string to_sql_for_LIKE(this string strString)
        {
            if (strString._is_void_())
            {
                return "";
            }
            else
            {
                StringBuilder oSB = new StringBuilder(strString.Length);
                for (int iIter = 0; iIter < strString.Length; iIter++)
                {
                    char cChar = strString[iIter];
                    switch (cChar)
                    {
                        case '[':
                            oSB.Append("[[]");
                            break;
                        case '_':
                            oSB.Append("[_]");
                            break;
                        case '%':
                            oSB.Append("[%]");
                            break;
                        case '\'':
                            oSB.Append("''");
                            break;
                        default:
                            oSB.Append(cChar);
                            break;
                    }
                }
                return oSB.ToString();
            }
        }
        /// <summary>convert string to SQL-safe form (for use with expressions except LIKE)</summary>
        public static string to_sql(this string strString)
        {
            if (strString._is_void_())
            {
                return "";
            }
            else
            {
                return strString.Replace("'", "''");
            }
        }
    }

    public static partial class ne_trans_Extensions
    {
        /// <summary>perform query using EB raw (SQL level) recordsets</summary>
        public static IEnumerable<object[]> execute_raw_sql_query(this ne_trans oTransaction, string strQuery, int iSkip = 0, int iTake = 0)
        {
            iTake = (iTake == 0) ? int.MaxValue : (iTake + iSkip);

            using (ne_recordset oRecordset = oTransaction.createadors(strQuery))
            {
                while (!oRecordset.EOF && iTake-- > 0)
                {
                    if (--iSkip < 0)
                    {
                        object[] arrFields = new object[oRecordset.field_count];

                        for (int iIter = 0; iIter < oRecordset.field_count; iIter++)
                        {
                            arrFields[iIter] = oRecordset.get_field(iIter);
                        }

                        yield return arrFields;
                    }

                    oRecordset.MoveNext();
                }
            }
        }
    }
}
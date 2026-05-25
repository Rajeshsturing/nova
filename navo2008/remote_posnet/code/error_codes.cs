//--------------------------------------------------------------------------
// N8 project
// Copyright NAVO Sp. z o.o. All Rights reserved 2011-2012
//
// error codes and templates
// 
// created: 2011-09-21/../2012-07-13
//--------------------------------------------------------------------------

namespace n8.core
{
    /// <summary>error codes defined in this assembly</summary>
    public sealed class error_code
    {
        /// <summary>Unexpected [{0}] XML tag while reading {1}({2})</summary>
        public const string ERR_UNEXPECTED_XML_TAG = "CORE.F001";
        /// <summary>Invalid date-time value [{0}] while reading XML document</summary>
        public const string ERR_INVALID_DATETIME_VALUE = "CORE.F002";
        /// <summary>Invalid decimal value [{0}] while reading XML document</summary>
        public const string ERR_INVALID_DECIMAL_VALUE = "CORE.F003";
        /// <summary>Invalid int value [{0}] while reading XML document</summary>
        public const string ERR_INVALID_INT_VALUE = "CORE.F004";
        /// <summary>Value of {0} in {1}({2}) must be set, but is empty</summary>
        public const string ERR_VALUE_MUST_BE_SET = "CORE.F005";
        /// <summary>Object {0}({1}) not found</summary>
        public const string ERR_OBJECT_NOT_FOUND = "CORE.F006";
    }
}
/*
	NAVO Sp. z o.o. (2001)
	
	NAVO Enterprise

	SQLT_const
*/

#ifndef _NAVOSQLCONST_H_
#define _NAVOSQLCONST_H_


//SQL field TYPES
//------------------------------------------------------------
const long SQLT_CHAR0	= 0x0000;		//CHAR(0)
const long SQLT_VARCHAR0= 0x2000;		//VARCHAR(0)
const long SQLT_SMALL	= 0x4001;		//SMALLINT
const long SQLT_INT		= 0x4002;		//INTEGER
const long SQLT_DATE	= 0x4003;		//DATE
const long SQLT_MONEY	= 0x4004;		//DECIMAL(12,2)		- money
const long SQLT_QUANTITY= 0x4005;		//DECIMAL(15,3)		- quantity
const long SQLT_COEFF	= 0x4006;		//DECIMAL(24,12)	- coefficient
const long SQLT_IMAGE	= 0x4007;		//IMAGE				- BLOB
const long SQLT_TIME	= 0x4008;		//INTEGER			- time 0000-2359 or 2500 as 'null'
const long SQLT_OBJECT	= 0x4009;		//<object>			- automation object - virtual field only
const long SQLT_IGNORE	= 0x8000;		//ignore in database operations

inline long SQLT_CHAR(long nChars)	
{ 
	return (SQLT_CHAR0 + nChars); 
}

inline long SQLT_VARCHAR(long nChars)
{
	return (SQLT_VARCHAR0 + nChars);
}

inline long CHARLEN(long _type_)
{
	ASSERT( _type_ >= SQLT_CHAR0 && _type_ < 1024*1024);
	return ((_type_) - SQLT_CHAR0);
}

inline long VARCHARLEN(long _type_)
{
	ASSERT( _type_ >= SQLT_VARCHAR0 && _type_ < 1024*1024);
	return ((_type_) - SQLT_VARCHAR0);
}

#else
	#error __FILE__ included
#endif

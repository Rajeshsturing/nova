/*
	NAVO Enterprise (2001)
	StdObj class Definition parser
*/

#ifndef _STDOBJCLASSPARSER_H_
#define _STDOBJCLASSPARSER_H_

class CDefinitionManager;

bool ParseStdObjDefinition(
	/* input stream */ SCP<IStream> & rpoIStreamSP,
	/* object collecting definition */ SCP<CDefinitionManager> & rpoDefinitonManagerSP,
	/* error info object - out */ SCP<INavoErrorInfo> & rpoNavoErrorInfoSP);

#else
	#error __FILE__ already included
#endif

/**
* contains minimal set of independent utils (language support, for example)
*/

#pragma once

// ~Switch Begin
/**
* C++ case label.
* Does NOT fall through, rather returns the given value.
*/
#define M_CASE_RETURN(InCase, InReturnValue) case InCase: return InReturnValue

/**
* C++ case label that returns the given string for the given literal.
* @note: Text should NOT be inclosed into TEXT (will be enclosed automatically).
*/
#define M_CASE_ENUM_STRING(InCase) M_CASE_RETURN_STRING(InCase, #InCase)

/**
* C++ case label that returns the given string for the given literal.
* @note:
* Each enum is prepended with M_ENUM_PREFIX macro value.
* M_CASE_PREFIX() macro value must be defined Before the M_SWITCH_BEGIN (with #define M_CASE_PREFIX())
* and will must be undefined with #undef M_CASE_PREFIX;
* @note: Text should NOT be inclosed into TEXT (will be enclosed automatically).
*/
#define M_CASE_ENUM_PREFIX_STRING(InCase) M_CASE_RETURN_STRING(M_CASE_PREFIX()##InCase, #InCase)

/**
* Returns the given value for the given enum.
* @see M_CASE_ENUM_PREFIX_STRING.
*/
#define M_CASE_ENUM_PREFIX_STRING_CUSTOM(InCase, InReturnCString) M_CASE_RETURN_STRING(M_CASE_PREFIX()##InCase, InReturnCString)

/**
* C++ case label.
* Retuns FString from the given C-string literal.
* @note: Text should NOT be inclosed into TEXT (will be enclosed automatically).
*/
#define M_CASE_RETURN_STRING(InCase, InReturnCString) M_CASE_RETURN(InCase, FString(TEXT(InReturnCString)))

/**
* C++ case label.
* Returns the given TCHAR* C string literal.
* @note: Text should NOT be inclosed into TEXT (will be enclosed automatically)
*/
#define M_CASE_RETURN_C_STRING(InCase, InReturnCString) M_CASE_RETURN(InCase, TEXT(InReturnString))

/**
* Starts C++ switch instruction.
* @note: Pascal-style (no {}, rather M_SWITCH_BEGIN/M_SWITCH_END* brackets used)
*/
#define M_SWITCH_BEGIN(InExpr) switch(InExpr) {

/**
* Ends C++ switch instruction.
* Checks that no default entry.
*/
#define M_SWITCH_END() \
	default: checkNoEntry(); \
}

/**
* Ends C++ switch instruction.
* Returns the given value by default
*/
#define M_SWITCH_END_DEFAULT_TO(InDefault) \
	default: break; \
} \
return InDefault;

#define M_SWITCH_END_DEFAULT_WRONG_ENUM_STRING() \
	default: break; \
} \
return FString(TEXT("Wrong enum"));

#define M_SWITCH_END_DEFAULT_WRONG_ENUM_C_STRING() \
	default: break; \
} \
return TEXT("Wrong enum");
// ~Switch End

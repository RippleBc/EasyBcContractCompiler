#pragma once

#include "Exceptions.h"

namespace dev
{

#if defined(_MSC_VER)
#define ETH_FUNC __FUNCSIG__
#elif defined(__GNUC__)
#define ETH_FUNC __PRETTY_FUNCTION__
#else
#define ETH_FUNC __func__
#endif

/// Assertion that throws an exception containing the given description if it is not met.
/// Use it as assertThrow(1 == 1, ExceptionType, "Mathematics is wrong.");
/// Do NOT supply an exception object as the second parameter.
#define assertThrow(_condition, _ExceptionType, _description) \
	do \
	{ \
		if (!(_condition)) \
			::boost::throw_exception( \
				_ExceptionType() << \
				::dev::errinfo_comment(_description) << \
				::boost::throw_function(ETH_FUNC) << \
				::boost::throw_file(__FILE__) << \
				::boost::throw_line(__LINE__) \
			); \
	} \
	while (false)

}

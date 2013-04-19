#define BOOST_TEST_MODULE StreamLoggerTest

#include "StreamLogger.h"
#include "LogWriter.h"

#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <sstream>


BOOST_AUTO_TEST_CASE(test1)
{
    std::ostringstream buf;
    auto logger = core::CreateStreamLogger(buf);

    LogError(logger, "Title", "Message.");
    BOOST_CHECK(boost::algorithm::starts_with(buf.str(), " -E- Title: \"Message.\" -- "));
}


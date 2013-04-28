#include "LoggerTestHelpers.h"
#include "StreamLogger.h"
#include "DeferredLogger.h"
#include "LogWriter.h"
#include <sstream>

#define BOOST_TEST_MODULE LoggerTests
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>


auto c_testLogger = std::make_shared<TestLogger>();


BOOST_AUTO_TEST_CASE(StreamLoggerFunctional)
{
    std::ostringstream buf;
    auto logger = core::CreateStreamLogger(buf);

    LogError(logger, "Message.");
    BOOST_CHECK(boost::algorithm::starts_with(buf.str(), " -E- \"Message.\" -- "));
}


BOOST_AUTO_TEST_CASE(DeferredLoggerFunctional)
{
    std::ostringstream buf;
    auto tlogger = core::CreateStreamLogger(buf);
    auto dlogger = core::CreateDeferredLogger(tlogger);

    LogError(dlogger, "Message.");

    boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
    BOOST_CHECK(boost::algorithm::starts_with(buf.str(), " -E- \"Message.\" -- "));
}


BOOST_AUTO_TEST_CASE(LogWriter_WithNullLogger)
{
    LogInfo(nullptr, "Yohoho!");
}


BOOST_AUTO_TEST_CASE(LogWriter_NotEnoughParams)
{
    LogInfo(c_testLogger, "%s");
    BOOST_CHECK_EQUAL("", c_testLogger->getMessage());

    LogInfo(c_testLogger, "%s %d") << "x";
    BOOST_CHECK_EQUAL("x ", c_testLogger->getMessage());
}


BOOST_AUTO_TEST_CASE(LogWriter_TooManyParams)
{
    LogInfo(c_testLogger, "no params") << "abc";
    BOOST_CHECK_EQUAL("no params", c_testLogger->getMessage());

    LogInfo(c_testLogger, "value = %d") << 123 << 123;
    BOOST_CHECK_EQUAL("value = 123", c_testLogger->getMessage());
}


BOOST_AUTO_TEST_CASE(LogWriter_WrongParamType)
{
    LogInfo(c_testLogger, "%i") << "abc";
    BOOST_CHECK_EQUAL("abc", c_testLogger->getMessage());

    LogInfo(c_testLogger, "%s") << 666;
    BOOST_CHECK_EQUAL("666", c_testLogger->getMessage());
}

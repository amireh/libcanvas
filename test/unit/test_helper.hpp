#ifndef H_CANVAS_TEST_HELPER_H
#define H_CANVAS_TEST_HELPER_H

#include "canvas/canvas.hpp"
#include "canvas/utility.hpp"
#include <regex.h>
#include <gtest/internal/gtest-internal.h>
#include <fstream>

namespace Canvas {
  static const String CANVAS_SPEC_FIXTURE_PATH("../test/fixture");
  static const String CANVAS_SPEC_API_TOKEN("Ko4dCE6sX9CaYSknvpAHbmSVulsNx9TUtSK1EbT34fOBur8lNAm7L8AG2OjMNfPQ");

  inline static
  bool loadFile(std::ifstream &fs, String& out_buf)
  {
    if (!fs.is_open() || !fs.good()) {
      return false;
    }

    while (fs.good()) {
      out_buf.push_back(fs.get());
    }

    out_buf.erase(out_buf.size()-1,1);

    return true;
  }

  inline static
  bool loadFile(String const& path, String& out_buf)
  {
    bool rc;
    std::ifstream stream(path);

    rc = loadFile(stream, out_buf);

    stream.close();

    return rc;
  }

  static String fixture(String const& path) {
    return CANVAS_SPEC_FIXTURE_PATH + "/" + path;
  }

  static String loadFixture(String const& path) {
    String out;
    loadFile(fixture(path), out);
    return out;
  }

  namespace Utility {
    inline static
    std::string keywords(std::string const& s) {
      String out;
      partitioned_string_t parts = split(s, ' ');
      for (partitioned_string_t::const_iterator i = parts.begin(); i != parts.end(); ++i) {
        out += (*i) + ".*";
      }

      return out.substr(0, out.length() - 2);
    }
  }
}

// TODO: use internal RE instead of gtest's

#define ASSERT_THROW_WITH(statement, expected_exception, expected_msg) \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
  if (::testing::internal::ConstCharPtr gtest_msg = "") { \
    bool gtest_caught_expected = false; \
    try { \
      GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement); \
    } \
    catch (expected_exception const& e) { \
      using namespace ::testing::internal; \
      using Canvas::Utility::keywords; \
      std::string errmsg = e.what(); \
      std::transform(errmsg.begin(), errmsg.end(), errmsg.begin(), ::tolower); \
      std::string expmsg(expected_msg); \
      std::transform(expmsg.begin(), expmsg.end(), expmsg.begin(), ::tolower); \
      gtest_caught_expected = RE::PartialMatch(errmsg, RE(keywords(expmsg))); \
      if (!gtest_caught_expected) { \
        std::ostringstream m; \
        m << "Expected: " #statement " throws an exception of type " \
            #expected_exception " with message '" \
          << expmsg \
          << "'.\n Actual: it throws a different message: '" \
          << errmsg << "'."; \
        gtest_msg.value = strdup(m.str().c_str()); \
        goto GTEST_CONCAT_TOKEN_(gtest_label_testthrow_, __LINE__); \
      } \
    } \
    catch (std::exception const& e) { \
      std::ostringstream m; \
      m << \
          "Expected: " #statement " throws an exception of type " \
          #expected_exception ".\n  Actual: it throws a different type with message: " \
          << e.what() \
          << "."; \
      gtest_msg.value = strdup(m.str().c_str()); \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testthrow_, __LINE__); \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testthrow_, __LINE__); \
    } \
    if (!gtest_caught_expected) { \
      gtest_msg.value = \
          "Expected: " #statement " throws an exception of type " \
          #expected_exception ".\n  Actual: it throws nothing."; \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testthrow_, __LINE__); \
    } \
  } else \
    GTEST_CONCAT_TOKEN_(gtest_label_testthrow_, __LINE__): \
      GTEST_FATAL_FAILURE_(gtest_msg.value)

#define CNVS_ASSERT_THROW(statement, expected_exception) \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
  if (::testing::internal::ConstCharPtr gtest_msg = "") { \
    bool gtest_caught_expected = false; \
    try { \
      GTEST_SUPPRESS_UNREACHABLE_CODE_WARNING_BELOW_(statement); \
    } \
    catch (expected_exception const&) { \
      gtest_caught_expected = true; \
    } \
    catch (std::exception const& e) { \
      std::ostringstream m; \
      m << \
          "Expected: " #statement " throws an exception of type " \
          #expected_exception ".\n  Actual: it throws a different type with message: " \
          << e.what() \
          << "."; \
      gtest_msg.value = strdup(m.str().c_str()); \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testthrow_, __LINE__); \
    } \
    if (!gtest_caught_expected) { \
      gtest_msg.value = \
          "Expected: " #statement " throws an exception of type " \
          #expected_exception ".\n  Actual: it throws nothing."; \
      goto GTEST_CONCAT_TOKEN_(gtest_label_testthrow_, __LINE__); \
    } \
  } else \
    GTEST_CONCAT_TOKEN_(gtest_label_testthrow_, __LINE__): \
      GTEST_FATAL_FAILURE_(gtest_msg.value)


#ifdef ASSERT_THROW
  #undef ASSERT_THROW
#endif

#define ASSERT_THROW CNVS_ASSERT_THROW

#endif

#pragma once
#include "../datas/unit_testing.hpp"
#include "reflector_def.inl"

ES_STATIC_ASSERT(sizeof(EnumWrap02) == 1);
ES_STATIC_ASSERT(sizeof(EnumWrap03) == 2);
ES_STATIC_ASSERT(sizeof(EnumWrap04) == 4);

int test_reflector_enum00() {
  ReflectedEnum rEnum = GetReflectedEnum<EnumWrap00>();

  TEST_EQUAL(rEnum.hash, JenHash("EnumWrap00"));
  TEST_EQUAL(rEnum.size(), 3);
  TEST_EQUAL(rEnum.name, std::string("EnumWrap00"));

  static const char *names[] = {"E1", "E2", "E3"};
  static const uint64 ids[] = {0, 1, 7};

  for (int t = 0; t < 3; t++) {
    TEST_EQUAL(rEnum[t], names[t]);
    TEST_EQUAL(rEnum.values[t], ids[t]);
  }

  return 0;
}

int test_reflector_enum01() {
  ReflectedEnum rEnum = GetReflectedEnum<EnumWrap01>();

  TEST_EQUAL(rEnum.hash, JenHash("EnumWrap01"));
  TEST_EQUAL(rEnum.size(), 3);
  TEST_EQUAL(rEnum.name, std::string("EnumWrap01"));

  static const char *names[] = {"EnumWrap01_E1", "EnumWrap01_E2",
                                "EnumWrap01_E3"};
  static const uint64 ids[] = {0, 1, 2};

  for (int t = 0; t < 3; t++) {
    TEST_EQUAL(rEnum[t], names[t]);
    TEST_EQUAL(rEnum.values[t], ids[t]);
  }

  return 0;
}

int test_reflector_enum02() {
  ReflectedEnum rEnum = GetReflectedEnum<EnumWrap02>();

  TEST_EQUAL(rEnum.hash, JenHash("EnumWrap02"));
  TEST_EQUAL(rEnum.size(), 3);
  TEST_EQUAL(rEnum.name, std::string("EnumWrap02"));

  static const char *names[] = {"E4", "E5", "E6"};
  static const uint64 ids[] = {0, 1, 2};

  for (int t = 0; t < 3; t++) {
    TEST_EQUAL(rEnum[t], names[t]);
    TEST_EQUAL(rEnum.values[t], ids[t]);
  }

  return 0;
}

int test_reflector_enum03() {
  ReflectedEnum rEnum = GetReflectedEnum<EnumWrap03>();

  TEST_EQUAL(rEnum.hash, JenHash("EnumWrap03"));
  TEST_EQUAL(rEnum.size(), 3);
  TEST_EQUAL(rEnum.name, std::string("EnumWrap03"));

  static const char *names[] = {"E7", "E8", "E9"};
  static const uint64 ids[] = {7, 16586, 0x8bcd};

  for (int t = 0; t < 3; t++) {
    TEST_EQUAL(rEnum[t], names[t]);
    TEST_EQUAL(rEnum.values[t], ids[t]);
  }

  return 0;
}

int test_reflector_enum04() {
  ReflectedEnum rEnum = GetReflectedEnum<EnumWrap04>();

  TEST_EQUAL(rEnum.hash, JenHash("EnumWrap04"));
  TEST_EQUAL(rEnum.size(), 3);
  TEST_EQUAL(rEnum.name, std::string("EnumWrap04"));

  static const char *names[] = {"E10", "E11", "E12"};
  static const uint64 ids[] = {0, 1, 2};

  for (int t = 0; t < 3; t++) {
    TEST_EQUAL(rEnum[t], names[t]);
    TEST_EQUAL(rEnum.values[t], ids[t]);
  }

  return 0;
}

int test_reflector_bool(reflClass &input) {
  TEST_EQUAL(input.test1, false);
  TEST_EQUAL(input.SetReflectedValue("test1", "true"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test1, true);
  Reflector::KVPair cPair = input.GetReflectedPair(0);
  TEST_EQUAL(cPair.name, "test1");
  TEST_EQUAL(cPair.value, "true");

  TEST_EQUAL(input.SetReflectedValue("test1", "False"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test1, false);
  cPair = input.GetReflectedPair(0);
  TEST_EQUAL(cPair.name, "test1");
  TEST_EQUAL(cPair.value, "false");

  TEST_EQUAL(input.SetReflectedValue("test1", "TRUE"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test1, true);
  cPair = input.GetReflectedPair(0);
  TEST_EQUAL(cPair.name, "test1");
  TEST_EQUAL(cPair.value, "true");

  TEST_EQUAL(input.SetReflectedValue("test1", "tralse"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test1, false);
  cPair = input.GetReflectedPair(0);
  TEST_EQUAL(cPair.name, "test1");
  TEST_EQUAL(cPair.value, "false");

  TEST_EQUAL(input.SetReflectedValue("test1", "   TrUE   "),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test1, true);
  cPair = input.GetReflectedPair(0);
  TEST_EQUAL(cPair.name, "test1");
  TEST_EQUAL(cPair.value, "true");

  return 0;
}

int test_reflector_int8(reflClass &input) {
  TEST_EQUAL(input.test2, 0);
  TEST_EQUAL(input.SetReflectedValue("test2", "-107"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test2, -107);
  Reflector::KVPair cPair = input.GetReflectedPair(1);
  TEST_EQUAL(cPair.name, "test2");
  TEST_EQUAL(cPair.value, "-107");

  TEST_EQUAL(input.SetReflectedValue("test2", "-1070"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test2, -0x80);
  cPair = input.GetReflectedPair(1);
  TEST_EQUAL(cPair.name, "test2");
  TEST_EQUAL(cPair.value, "-128");

  TEST_EQUAL(input.SetReflectedValue("test2", "1070"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test2, 0x7f);
  cPair = input.GetReflectedPair(1);
  TEST_EQUAL(cPair.name, "test2");
  TEST_EQUAL(cPair.value, "127");

  TEST_EQUAL(input.SetReflectedValue("test2", "\t   107 \t  "),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test2, 107);
  cPair = input.GetReflectedPair(1);
  TEST_EQUAL(cPair.name, "test2");
  TEST_EQUAL(cPair.value, "107");

  TEST_EQUAL(input.SetReflectedValue("test2", "    107dis    "),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test2, 107);
  cPair = input.GetReflectedPair(1);
  TEST_EQUAL(cPair.name, "test2");
  TEST_EQUAL(cPair.value, "107");

  TEST_EQUAL(input.SetReflectedValue("test2", "    dis121    "),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test2, 107);
  cPair = input.GetReflectedPair(1);
  TEST_EQUAL(cPair.name, "test2");
  TEST_EQUAL(cPair.value, "107");

  TEST_EQUAL(input.SetReflectedValue("test2", "0x7f"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test2, 0x7f);
  cPair = input.GetReflectedPair(1);
  TEST_EQUAL(cPair.name, "test2");
  TEST_EQUAL(cPair.value, "127");

  TEST_EQUAL(input.SetReflectedValue("test2", "0x80"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test2, 0x7f);
  cPair = input.GetReflectedPair(1);
  TEST_EQUAL(cPair.name, "test2");
  TEST_EQUAL(cPair.value, "127");

  TEST_EQUAL(input.SetReflectedValue("test2", "-0x80"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test2, -0x80);
  cPair = input.GetReflectedPair(1);
  TEST_EQUAL(cPair.name, "test2");
  TEST_EQUAL(cPair.value, "-128");

  TEST_EQUAL(input.SetReflectedValueInt("test2", 56),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test2, 56);

  TEST_EQUAL(input.SetReflectedValueInt("test2", -107),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test2, -107);

  TEST_EQUAL(input.SetReflectedValueUInt("test2", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test2, -107);

  TEST_EQUAL(input.SetReflectedValueFloat("test2", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test2, -107);

  return 0;
}

int test_reflector_uint8(reflClass &input) {
  TEST_EQUAL(input.test3, 0);
  TEST_EQUAL(input.SetReflectedValue("test3", "157"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test3, 157);
  Reflector::KVPair cPair = input.GetReflectedPair(2);
  TEST_EQUAL(cPair.name, "test3");
  TEST_EQUAL(cPair.value, "157");

  TEST_EQUAL(input.SetReflectedValue("test3", "1258"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test3, 0xff);
  cPair = input.GetReflectedPair(2);
  TEST_EQUAL(cPair.name, "test3");
  TEST_EQUAL(cPair.value, "255");

  TEST_EQUAL(input.SetReflectedValue("test3", "-10"),
             Reflector::ErrorType::SignMismatch);
  TEST_EQUAL(input.test3, 246);
  cPair = input.GetReflectedPair(2);
  TEST_EQUAL(cPair.name, "test3");
  TEST_EQUAL(cPair.value, "246");

  TEST_EQUAL(input.SetReflectedValue("test3", "0x80"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test3, 0x80);
  cPair = input.GetReflectedPair(2);
  TEST_EQUAL(cPair.name, "test3");
  TEST_EQUAL(cPair.value, "128");

  TEST_EQUAL(input.SetReflectedValue("test3", "-0x80"),
             Reflector::ErrorType::SignMismatch);
  TEST_EQUAL(input.test3, 0x80);
  cPair = input.GetReflectedPair(2);
  TEST_EQUAL(cPair.name, "test3");
  TEST_EQUAL(cPair.value, "128");

  TEST_EQUAL(input.SetReflectedValueUInt("test3", -107),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test3, uint8(-107));

  TEST_EQUAL(input.SetReflectedValueUInt("test3", 157),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test3, 157);

  TEST_EQUAL(input.SetReflectedValueInt("test3", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test3, 157);

  TEST_EQUAL(input.SetReflectedValueFloat("test3", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test3, 157);

  return 0;
}

int test_reflector_int16(reflClass &input) {
  TEST_EQUAL(input.test4, 0);
  TEST_EQUAL(input.SetReflectedValue("test4", "-1070"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test4, -1070);
  Reflector::KVPair cPair = input.GetReflectedPair(3);
  TEST_EQUAL(cPair.name, "test4");
  TEST_EQUAL(cPair.value, "-1070");

  TEST_EQUAL(input.SetReflectedValue("test4", "-54987"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test4, -0x8000);
  cPair = input.GetReflectedPair(3);
  TEST_EQUAL(cPair.name, "test4");
  TEST_EQUAL(cPair.value, "-32768");

  TEST_EQUAL(input.SetReflectedValue("test4", "39641"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test4, 0x7fff);
  cPair = input.GetReflectedPair(3);
  TEST_EQUAL(cPair.name, "test4");
  TEST_EQUAL(cPair.value, "32767");

  TEST_EQUAL(input.SetReflectedValue("test4", "0x7fc"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test4, 0x7fc);
  cPair = input.GetReflectedPair(3);
  TEST_EQUAL(cPair.name, "test4");
  TEST_EQUAL(cPair.value, "2044");

  TEST_EQUAL(input.SetReflectedValue("test4", "0x80f2"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test4, 0x7fff);
  cPair = input.GetReflectedPair(3);
  TEST_EQUAL(cPair.name, "test4");
  TEST_EQUAL(cPair.value, "32767");

  TEST_EQUAL(input.SetReflectedValue("test4", "-0x4048"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test4, -0x4048);
  cPair = input.GetReflectedPair(3);
  TEST_EQUAL(cPair.name, "test4");
  TEST_EQUAL(cPair.value, "-16456");

  TEST_EQUAL(input.SetReflectedValueInt("test4", 56),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test4, 56);

  TEST_EQUAL(input.SetReflectedValueInt("test4", -1070),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test4, -1070);

  TEST_EQUAL(input.SetReflectedValueUInt("test4", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test4, -1070);

  TEST_EQUAL(input.SetReflectedValueFloat("test4", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test4, -1070);

  return 0;
}

int test_reflector_uint16(reflClass &input) {
  TEST_EQUAL(input.test5, 0);
  TEST_EQUAL(input.SetReflectedValue("test5", "1570"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test5, 1570);
  Reflector::KVPair cPair = input.GetReflectedPair(4);
  TEST_EQUAL(cPair.name, "test5");
  TEST_EQUAL(cPair.value, "1570");

  TEST_EQUAL(input.SetReflectedValue("test5", "105896"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test5, 0xffff);
  cPair = input.GetReflectedPair(4);
  TEST_EQUAL(cPair.name, "test5");
  TEST_EQUAL(cPair.value, "65535");

  TEST_EQUAL(input.SetReflectedValue("test5", "-10"),
             Reflector::ErrorType::SignMismatch);
  TEST_EQUAL(input.test5, 65526);
  cPair = input.GetReflectedPair(4);
  TEST_EQUAL(cPair.name, "test5");
  TEST_EQUAL(cPair.value, "65526");

  TEST_EQUAL(input.SetReflectedValue("test5", "0x8bca"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test5, 35786);
  cPair = input.GetReflectedPair(4);
  TEST_EQUAL(cPair.name, "test5");
  TEST_EQUAL(cPair.value, "35786");

  TEST_EQUAL(input.SetReflectedValue("test5", "-0x80"),
             Reflector::ErrorType::SignMismatch);
  TEST_EQUAL(input.test5, 65408);
  cPair = input.GetReflectedPair(4);
  TEST_EQUAL(cPair.name, "test5");
  TEST_EQUAL(cPair.value, "65408");

  TEST_EQUAL(input.SetReflectedValueUInt("test5", -107),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test5, uint16(-107));

  TEST_EQUAL(input.SetReflectedValueUInt("test5", 1570),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test5, 1570);

  TEST_EQUAL(input.SetReflectedValueInt("test5", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test5, 1570);

  TEST_EQUAL(input.SetReflectedValueFloat("test5", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test5, 1570);

  return 0;
}

int test_reflector_int32(reflClass &input) {
  TEST_EQUAL(input.test6, 0);
  TEST_EQUAL(input.SetReflectedValue("test6", "-1586954"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test6, -1586954);
  Reflector::KVPair cPair = input.GetReflectedPair(5);
  TEST_EQUAL(cPair.name, "test6");
  TEST_EQUAL(cPair.value, "-1586954");

  TEST_EQUAL(input.SetReflectedValue("test6", "-5896321478"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test6, std::numeric_limits<int32>::min());
  cPair = input.GetReflectedPair(5);
  TEST_EQUAL(cPair.name, "test6");
  TEST_EQUAL(cPair.value, "-2147483648");

  TEST_EQUAL(input.SetReflectedValue("test6", "5269874106"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test6, 0x7fffffff);
  cPair = input.GetReflectedPair(5);
  TEST_EQUAL(cPair.name, "test6");
  TEST_EQUAL(cPair.value, "2147483647");

  TEST_EQUAL(input.SetReflectedValue("test6", "0x5b6214a9"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test6, 0x5b6214a9);
  cPair = input.GetReflectedPair(5);
  TEST_EQUAL(cPair.name, "test6");
  TEST_EQUAL(cPair.value, "1533154473");

  TEST_EQUAL(input.SetReflectedValue("test6", "0xab6214a9"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test6, 0x7fffffff);
  cPair = input.GetReflectedPair(5);
  TEST_EQUAL(cPair.name, "test6");
  TEST_EQUAL(cPair.value, "2147483647");

  TEST_EQUAL(input.SetReflectedValue("test6", "-0x5b6214a9"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test6, -0x5b6214a9);
  cPair = input.GetReflectedPair(5);
  TEST_EQUAL(cPair.name, "test6");
  TEST_EQUAL(cPair.value, "-1533154473");

  TEST_EQUAL(input.SetReflectedValueInt("test6", 56),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test6, 56);

  TEST_EQUAL(input.SetReflectedValueInt("test6", -1586954),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test6, -1586954);

  TEST_EQUAL(input.SetReflectedValueUInt("test6", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test6, -1586954);

  TEST_EQUAL(input.SetReflectedValueFloat("test6", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test6, -1586954);

  return 0;
}

int test_reflector_uint32(reflClass &input) {
  TEST_EQUAL(input.test7, 0);
  TEST_EQUAL(input.SetReflectedValue("test7", "3896542158"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test7, 3896542158);
  Reflector::KVPair cPair = input.GetReflectedPair(6);
  TEST_EQUAL(cPair.name, "test7");
  TEST_EQUAL(cPair.value, "3896542158");

  TEST_EQUAL(input.SetReflectedValue("test7", "126987541236"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test7, 0xffffffff);
  cPair = input.GetReflectedPair(6);
  TEST_EQUAL(cPair.name, "test7");
  TEST_EQUAL(cPair.value, "4294967295");

  TEST_EQUAL(input.SetReflectedValue("test7", "-10"),
             Reflector::ErrorType::SignMismatch);
  TEST_EQUAL(input.test7, 4294967286);
  cPair = input.GetReflectedPair(6);
  TEST_EQUAL(cPair.name, "test7");
  TEST_EQUAL(cPair.value, "4294967286");

  TEST_EQUAL(input.SetReflectedValue("test7", "0x8bca7854"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test7, 0x8bca7854);
  cPair = input.GetReflectedPair(6);
  TEST_EQUAL(cPair.name, "test7");
  TEST_EQUAL(cPair.value, "2345302100");

  TEST_EQUAL(input.SetReflectedValue("test7", "-0x80"),
             Reflector::ErrorType::SignMismatch);
  TEST_EQUAL(input.test7, 4294967168);
  cPair = input.GetReflectedPair(6);
  TEST_EQUAL(cPair.name, "test7");
  TEST_EQUAL(cPair.value, "4294967168");

  TEST_EQUAL(input.SetReflectedValueUInt("test7", -107),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test7, uint32(-107));

  TEST_EQUAL(input.SetReflectedValueUInt("test7", 3896542158),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test7, 3896542158);

  TEST_EQUAL(input.SetReflectedValueInt("test7", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test7, 3896542158);

  TEST_EQUAL(input.SetReflectedValueFloat("test7", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test7, 3896542158);

  return 0;
}

int test_reflector_int64(reflClass &input) {
  TEST_EQUAL(input.test8, 0);
  TEST_EQUAL(input.SetReflectedValue("test8", "-125896354410"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test8, -125896354410);
  Reflector::KVPair cPair = input.GetReflectedPair(7);
  TEST_EQUAL(cPair.name, "test8");
  TEST_EQUAL(cPair.value, "-125896354410");

  TEST_EQUAL(input.SetReflectedValue("test8", "-58963214786424582492542623145"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test8, std::numeric_limits<int64>::min());
  cPair = input.GetReflectedPair(7);
  TEST_EQUAL(cPair.name, "test8");
  TEST_EQUAL(cPair.value, "-9223372036854775808");

  TEST_EQUAL(input.SetReflectedValue("test8", "984165254656562566174615456"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test8, 0x7fffffffffffffff);
  cPair = input.GetReflectedPair(7);
  TEST_EQUAL(cPair.name, "test8");
  TEST_EQUAL(cPair.value, "9223372036854775807");

  TEST_EQUAL(input.SetReflectedValue("test8", "0x59f5772c64b1a785"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test8, 0x59f5772c64b1a785);
  cPair = input.GetReflectedPair(7);
  TEST_EQUAL(cPair.name, "test8");
  TEST_EQUAL(cPair.value, "6482218271221327749");

  TEST_EQUAL(input.SetReflectedValue("test8", "0xd9f5772c64b1a785"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test8, 0x7fffffffffffffff);
  cPair = input.GetReflectedPair(7);
  TEST_EQUAL(cPair.name, "test8");
  TEST_EQUAL(cPair.value, "9223372036854775807");

  TEST_EQUAL(input.SetReflectedValue("test8", "-0x59f5772c64b1a785"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test8, -0x59f5772c64b1a785);
  cPair = input.GetReflectedPair(7);
  TEST_EQUAL(cPair.name, "test8");
  TEST_EQUAL(cPair.value, "-6482218271221327749");

  TEST_EQUAL(input.SetReflectedValueInt("test8", 56),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test8, 56);

  TEST_EQUAL(input.SetReflectedValueInt("test8", -125896354410),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test8, -125896354410);

  TEST_EQUAL(input.SetReflectedValueUInt("test8", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test8, -125896354410);

  TEST_EQUAL(input.SetReflectedValueFloat("test8", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test8, -125896354410);

  return 0;
}

int test_reflector_uint64(reflClass &input) {
  TEST_EQUAL(input.test9, 0);
  TEST_EQUAL(input.SetReflectedValue("test9", "86125863479851"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test9, 86125863479851);
  Reflector::KVPair cPair = input.GetReflectedPair(8);
  TEST_EQUAL(cPair.name, "test9");
  TEST_EQUAL(cPair.value, "86125863479851");

  TEST_EQUAL(
      input.SetReflectedValue("test9", "81529745125936574564614465245525426"),
      Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test9, 0xffffffffffffffff);
  cPair = input.GetReflectedPair(8);
  TEST_EQUAL(cPair.name, "test9");
  TEST_EQUAL(cPair.value, "18446744073709551615");

  TEST_EQUAL(input.SetReflectedValue("test9", "-10"),
             Reflector::ErrorType::SignMismatch);
  TEST_EQUAL(input.test9, 18446744073709551606ULL);
  cPair = input.GetReflectedPair(8);
  TEST_EQUAL(cPair.name, "test9");
  TEST_EQUAL(cPair.value, "18446744073709551606");

  TEST_EQUAL(input.SetReflectedValue("test9", "0x8bca78548514c6a9"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test9, 0x8bca78548514c6a9);
  cPair = input.GetReflectedPair(8);
  TEST_EQUAL(cPair.name, "test9");
  TEST_EQUAL(cPair.value, "10072995820972852905");

  TEST_EQUAL(input.SetReflectedValue("test9", "-0x80"),
             Reflector::ErrorType::SignMismatch);
  TEST_EQUAL(input.test9, 18446744073709551488ULL);
  cPair = input.GetReflectedPair(8);
  TEST_EQUAL(cPair.name, "test9");
  TEST_EQUAL(cPair.value, "18446744073709551488");

  TEST_EQUAL(input.SetReflectedValueUInt("test9", -107),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test9, uint64(-107));

  TEST_EQUAL(input.SetReflectedValueUInt("test9", 86125863479851),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test9, 86125863479851);

  TEST_EQUAL(input.SetReflectedValueInt("test9", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test9, 86125863479851);

  TEST_EQUAL(input.SetReflectedValueFloat("test9", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test9, 86125863479851);

  return 0;
}

int test_reflector_float(reflClass &input) {
  TEST_EQUAL(input.test10, 0);
  TEST_EQUAL(input.SetReflectedValue("test10", "1.56"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test10, 1.56f);
  Reflector::KVPair cPair = input.GetReflectedPair(9);
  TEST_EQUAL(cPair.name, "test10");
  TEST_EQUAL(cPair.value, "1.56");

  TEST_EQUAL(input.SetReflectedValue("test10", "3.41282347e+38"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test10, FLT_MAX);
  cPair = input.GetReflectedPair(9);
  TEST_EQUAL(cPair.name, "test10");
  TEST_EQUAL(cPair.value, "3.40282e+38");

  TEST_EQUAL(input.SetReflectedValue("test10", "-3.41282347e+38"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test10, -FLT_MAX);
  cPair = input.GetReflectedPair(9);
  TEST_EQUAL(cPair.name, "test10");
  TEST_EQUAL(cPair.value, "-3.40282e+38");

  TEST_EQUAL(input.SetReflectedValue("test10", "1.10549435e-38F"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test10, FLT_MIN);
  cPair = input.GetReflectedPair(9);
  TEST_EQUAL(cPair.name, "test10");
  TEST_EQUAL(cPair.value, "1.17549e-38");

  TEST_EQUAL(input.SetReflectedValue("test10", "-1.10549435e-38F"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test10, -FLT_MIN);
  cPair = input.GetReflectedPair(9);
  TEST_EQUAL(cPair.name, "test10");
  TEST_EQUAL(cPair.value, "-1.17549e-38");

  TEST_EQUAL(input.SetReflectedValue("test10", "\t   1.48 \t  "),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test10, 1.48f);
  cPair = input.GetReflectedPair(9);
  TEST_EQUAL(cPair.name, "test10");
  TEST_EQUAL(cPair.value, "1.48");

  TEST_EQUAL(input.SetReflectedValue("test10", "    5.97dis    "),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test10, 5.97f);
  cPair = input.GetReflectedPair(9);
  TEST_EQUAL(cPair.name, "test10");
  TEST_EQUAL(cPair.value, "5.97");

  TEST_EQUAL(input.SetReflectedValue("test10", "    dis8.05    "),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test10, 5.97f);
  cPair = input.GetReflectedPair(9);
  TEST_EQUAL(cPair.name, "test10");
  TEST_EQUAL(cPair.value, "5.97");

  TEST_EQUAL(input.SetReflectedValue("test10", "NaN"),
             Reflector::ErrorType::None);
  TEST_CHECK(std::isnan(input.test10));
  cPair = input.GetReflectedPair(9);
  TEST_EQUAL(cPair.name, "test10");
  TEST_EQUAL(cPair.value, "nan");

  TEST_EQUAL(input.SetReflectedValue("test10", "-NaN"),
             Reflector::ErrorType::None);
  TEST_CHECK(std::isnan(input.test10));
  cPair = input.GetReflectedPair(9);
  TEST_EQUAL(cPair.name, "test10");
  TEST_CHECK((cPair.value == "nan" || cPair.value == "-nan"));

  TEST_EQUAL(input.SetReflectedValue("test10", "inf"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test10, INFINITY);
  cPair = input.GetReflectedPair(9);
  TEST_EQUAL(cPair.name, "test10");
  TEST_EQUAL(cPair.value, "inf");

  TEST_EQUAL(input.SetReflectedValue("test10", "-inf"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test10, -INFINITY);
  cPair = input.GetReflectedPair(9);
  TEST_EQUAL(cPair.name, "test10");
  TEST_EQUAL(cPair.value, "-inf");

  TEST_EQUAL(input.SetReflectedValue("test10", "     inf\t"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test10, INFINITY);
  cPair = input.GetReflectedPair(9);
  TEST_EQUAL(cPair.name, "test10");
  TEST_EQUAL(cPair.value, "inf");

  TEST_EQUAL(input.SetReflectedValue("test10", "     infinity&beyond"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test10, INFINITY);
  cPair = input.GetReflectedPair(9);
  TEST_EQUAL(cPair.name, "test10");
  TEST_EQUAL(cPair.value, "inf");

  TEST_EQUAL(input.SetReflectedValue("test10", "it's a NaN"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test10, INFINITY);
  cPair = input.GetReflectedPair(9);
  TEST_EQUAL(cPair.name, "test10");
  TEST_EQUAL(cPair.value, "inf");

  TEST_EQUAL(input.SetReflectedValueFloat("test10", 1.56),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test10, 1.56f);

  TEST_EQUAL(input.SetReflectedValueUInt("test10", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test10, 1.56f);

  TEST_EQUAL(input.SetReflectedValueInt("test10", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test10, 1.56f);

  return 0;
}

int test_reflector_double(reflClass &input) {
  TEST_EQUAL(input.test11, 0);
  TEST_EQUAL(input.SetReflectedValue("test11", "1.567513"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test11, 1.567513);
  Reflector::KVPair cPair = input.GetReflectedPair(10);
  TEST_EQUAL(cPair.name, "test11");
  TEST_EQUAL(cPair.value, "1.567513");

  TEST_EQUAL(input.SetReflectedValue("test11", "3.41282347e+308F"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test11, DBL_MAX);
  cPair = input.GetReflectedPair(10);
  TEST_EQUAL(cPair.name, "test11");
  TEST_EQUAL(cPair.value, "1.797693134862e+308");

  TEST_EQUAL(input.SetReflectedValue("test11", "-3.41282347e+308F"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test11, -DBL_MAX);
  cPair = input.GetReflectedPair(10);
  TEST_EQUAL(cPair.name, "test11");
  TEST_EQUAL(cPair.value, "-1.797693134862e+308");

  TEST_EQUAL(input.SetReflectedValue("test11", "1.10549435e-308F"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test11, DBL_MIN);
  cPair = input.GetReflectedPair(10);
  TEST_EQUAL(cPair.name, "test11");
  TEST_EQUAL(cPair.value, "2.225073858507e-308");

  TEST_EQUAL(input.SetReflectedValue("test11", "-1.10549435e-308F"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test11, -DBL_MIN);
  cPair = input.GetReflectedPair(10);
  TEST_EQUAL(cPair.name, "test11");
  TEST_EQUAL(cPair.value, "-2.225073858507e-308");

  TEST_EQUAL(input.SetReflectedValueFloat("test11", 1.567513),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test11, 1.567513);

  TEST_EQUAL(input.SetReflectedValueUInt("test11", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test11, 1.567513);

  TEST_EQUAL(input.SetReflectedValueInt("test11", 100),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.test11, 1.567513);

  return 0;
}

int test_reflector_enum00(reflClass &input) {
  TEST_EQUAL(input.test14, EnumWrap00::E1);
  TEST_EQUAL(input.SetReflectedValue("test14", "E2"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test14, EnumWrap00::E2);
  Reflector::KVPair cPair = input.GetReflectedPair(13);
  TEST_EQUAL(cPair.name, "test14");
  TEST_EQUAL(cPair.value, "E2");

  TEST_EQUAL(input.SetReflectedValue("test14", "  \t E3   "),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test14, EnumWrap00::E3);
  cPair = input.GetReflectedPair(13);
  TEST_EQUAL(cPair.name, "test14");
  TEST_EQUAL(cPair.value, "E3");

  TEST_EQUAL(input.SetReflectedValue("test14", "pE2"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test14, EnumWrap00::E3);
  cPair = input.GetReflectedPair(13);
  TEST_EQUAL(cPair.name, "test14");
  TEST_EQUAL(cPair.value, "E3");

  TEST_EQUAL(input.SetReflectedValue("test14", "E25"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test14, EnumWrap00::E3);
  cPair = input.GetReflectedPair(13);
  TEST_EQUAL(cPair.name, "test14");
  TEST_EQUAL(cPair.value, "E3");

  return 0;
}

int test_reflector_enum01(reflClass &input) {
  TEST_EQUAL(input.test15, EnumWrap02::E4);
  TEST_EQUAL(input.SetReflectedValue("test15", "E6"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test15, EnumWrap02::E6);
  Reflector::KVPair cPair = input.GetReflectedPair(14);
  TEST_EQUAL(cPair.name, "test15");
  TEST_EQUAL(cPair.value, "E6");

  TEST_EQUAL(input.SetReflectedValue("test15", "  \t E5   "),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test15, EnumWrap02::E5);
  cPair = input.GetReflectedPair(14);
  TEST_EQUAL(cPair.name, "test15");
  TEST_EQUAL(cPair.value, "E5");

  TEST_EQUAL(input.SetReflectedValue("test15", "pE5"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test15, EnumWrap02::E5);
  cPair = input.GetReflectedPair(14);
  TEST_EQUAL(cPair.name, "test15");
  TEST_EQUAL(cPair.value, "E5");

  TEST_EQUAL(input.SetReflectedValue("test15", "E52"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test15, EnumWrap02::E5);
  cPair = input.GetReflectedPair(14);
  TEST_EQUAL(cPair.name, "test15");
  TEST_EQUAL(cPair.value, "E5");

  return 0;
}

int test_reflector_enum02(reflClass &input) {
  TEST_EQUAL(static_cast<int>(input.test16), 0);
  TEST_EQUAL(input.SetReflectedValue("test16", "E7"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test16, EnumWrap03::E7);
  Reflector::KVPair cPair = input.GetReflectedPair(15);
  TEST_EQUAL(cPair.name, "test16");
  TEST_EQUAL(cPair.value, "E7");

  TEST_EQUAL(input.SetReflectedValue("test16", "  \t E8   "),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test16, EnumWrap03::E8);
  cPair = input.GetReflectedPair(15);
  TEST_EQUAL(cPair.name, "test16");
  TEST_EQUAL(cPair.value, "E8");

  TEST_EQUAL(input.SetReflectedValue("test16", "pE9"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test16, EnumWrap03::E8);
  cPair = input.GetReflectedPair(15);
  TEST_EQUAL(cPair.name, "test16");
  TEST_EQUAL(cPair.value, "E8");

  TEST_EQUAL(input.SetReflectedValue("test16", "E92"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test16, EnumWrap03::E8);
  cPair = input.GetReflectedPair(15);
  TEST_EQUAL(cPair.name, "test16");
  TEST_EQUAL(cPair.value, "E8");

  TEST_EQUAL(input.SetReflectedValue("test16", "E9"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test16, EnumWrap03::E9);
  cPair = input.GetReflectedPair(15);
  TEST_EQUAL(cPair.name, "test16");
  TEST_EQUAL(cPair.value, "E9");

  return 0;
}

int test_reflector_enum03(reflClass &input) {
  TEST_EQUAL(input.test17, EnumWrap04::E10);
  TEST_EQUAL(input.SetReflectedValue("test17", "E11"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test17, EnumWrap04::E11);
  Reflector::KVPair cPair = input.GetReflectedPair(16);
  TEST_EQUAL(cPair.name, "test17");
  TEST_EQUAL(cPair.value, "E11");

  TEST_EQUAL(input.SetReflectedValue("test17", "  \t E12   "),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test17, EnumWrap04::E12);
  cPair = input.GetReflectedPair(16);
  TEST_EQUAL(cPair.name, "test17");
  TEST_EQUAL(cPair.value, "E12");

  TEST_EQUAL(input.SetReflectedValue("test17", "pE129"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test17, EnumWrap04::E12);
  cPair = input.GetReflectedPair(16);
  TEST_EQUAL(cPair.name, "test17");
  TEST_EQUAL(cPair.value, "E12");

  TEST_EQUAL(input.SetReflectedValue("test17", "E102"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test17, EnumWrap04::E12);
  cPair = input.GetReflectedPair(16);
  TEST_EQUAL(cPair.name, "test17");
  TEST_EQUAL(cPair.value, "E12");

  return 0;
}

int test_reflector_enumflags00(reflClass &input) {
  TEST_CHECK(!input.test12[EnumWrap00::E1]);
  TEST_CHECK(!input.test12[EnumWrap00::E2]);
  TEST_CHECK(!input.test12[EnumWrap00::E3]);
  TEST_EQUAL(input.SetReflectedValue("test12", "E1 | E2 | E3"),
             Reflector::ErrorType::None);
  TEST_CHECK(input.test12[EnumWrap00::E1]);
  TEST_CHECK(input.test12[EnumWrap00::E2]);
  TEST_CHECK(input.test12[EnumWrap00::E3]);
  Reflector::KVPair cPair = input.GetReflectedPair(11);
  TEST_EQUAL(cPair.name, "test12");
  TEST_EQUAL(cPair.value, "E1 | E2 | E3");

  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E1), "true");
  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E2), "true");
  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E3), "true");

  TEST_EQUAL(input.SetReflectedValue("test12", "\tE1   |   E2 \t|  E3\t   "),
             Reflector::ErrorType::None);
  TEST_CHECK(input.test12[EnumWrap00::E1]);
  TEST_CHECK(input.test12[EnumWrap00::E2]);
  TEST_CHECK(input.test12[EnumWrap00::E3]);
  cPair = input.GetReflectedPair(11);
  TEST_EQUAL(cPair.name, "test12");
  TEST_EQUAL(cPair.value, "E1 | E2 | E3");

  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E1), "true");
  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E2), "true");
  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E3), "true");

  TEST_EQUAL(input.SetReflectedValue("test12", "E1|E2|E3"),
             Reflector::ErrorType::None);
  TEST_CHECK(input.test12[EnumWrap00::E1]);
  TEST_CHECK(input.test12[EnumWrap00::E2]);
  TEST_CHECK(input.test12[EnumWrap00::E3]);
  cPair = input.GetReflectedPair(11);
  TEST_EQUAL(cPair.name, "test12");
  TEST_EQUAL(cPair.value, "E1 | E2 | E3");
  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E1), "true");
  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E2), "true");
  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E3), "true");

  TEST_EQUAL(input.SetReflectedValue("test12", "E1 | E2 | "),
             Reflector::ErrorType::EmptyInput);
  TEST_CHECK(input.test12[EnumWrap00::E1]);
  TEST_CHECK(input.test12[EnumWrap00::E2]);
  TEST_CHECK(!input.test12[EnumWrap00::E3]);
  cPair = input.GetReflectedPair(11);
  TEST_EQUAL(cPair.name, "test12");
  TEST_EQUAL(cPair.value, "E1 | E2");
  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E1), "true");
  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E2), "true");
  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E3), "false");

  TEST_EQUAL(input.SetReflectedValue("test12", "E1 |  | E3"),
             Reflector::ErrorType::EmptyInput);
  TEST_CHECK(input.test12[EnumWrap00::E1]);
  TEST_CHECK(!input.test12[EnumWrap00::E2]);
  TEST_CHECK(input.test12[EnumWrap00::E3]);
  cPair = input.GetReflectedPair(11);
  TEST_EQUAL(cPair.name, "test12");
  TEST_EQUAL(cPair.value, "E1 | E3");
  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E1), "true");
  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E2), "false");
  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E3), "true");

  TEST_EQUAL(input.SetReflectedValue("test12", " |  | E3"),
             Reflector::ErrorType::EmptyInput);
  TEST_CHECK(!input.test12[EnumWrap00::E1]);
  TEST_CHECK(!input.test12[EnumWrap00::E2]);
  TEST_CHECK(input.test12[EnumWrap00::E3]);
  cPair = input.GetReflectedPair(11);
  TEST_EQUAL(cPair.name, "test12");
  TEST_EQUAL(cPair.value, "E3");
  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E1), "false");
  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E2), "false");
  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E3), "true");

  TEST_EQUAL(input.SetReflectedValue("test12", "E1 | sirius | E3"),
             Reflector::ErrorType::InvalidFormat);
  TEST_CHECK(input.test12[EnumWrap00::E1]);
  TEST_CHECK(!input.test12[EnumWrap00::E2]);
  TEST_CHECK(input.test12[EnumWrap00::E3]);
  cPair = input.GetReflectedPair(11);
  TEST_EQUAL(cPair.name, "test12");
  TEST_EQUAL(cPair.value, "E1 | E3");
  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E1), "true");
  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E2), "false");
  TEST_EQUAL(input.GetReflectedValue(11, (size_t)EnumWrap00::E3), "true");

  return 0;
}

int test_reflector_enumflags01(reflClass &input) {
  TEST_CHECK(!input.test13[EnumWrap01_E1]);
  TEST_CHECK(!input.test13[EnumWrap01_E2]);
  TEST_CHECK(!input.test13[EnumWrap01_E3]);
  TEST_EQUAL(input.SetReflectedValue(
                 "test13", "EnumWrap01_E1 | EnumWrap01_E2 | EnumWrap01_E3"),
             Reflector::ErrorType::None);
  TEST_CHECK(input.test13[EnumWrap01_E1]);
  TEST_CHECK(input.test13[EnumWrap01_E2]);
  TEST_CHECK(input.test13[EnumWrap01_E3]);
  Reflector::KVPair cPair = input.GetReflectedPair(12);
  TEST_EQUAL(cPair.name, "test13");
  TEST_EQUAL(cPair.value, "EnumWrap01_E1 | EnumWrap01_E2 | EnumWrap01_E3");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E1), "true");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E2), "true");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E3), "true");

  TEST_EQUAL(input.SetReflectedValue(
                 "test13",
                 "\tEnumWrap01_E1   |   EnumWrap01_E2 \t|  EnumWrap01_E3\t   "),
             Reflector::ErrorType::None);
  TEST_CHECK(input.test13[EnumWrap01_E1]);
  TEST_CHECK(input.test13[EnumWrap01_E2]);
  TEST_CHECK(input.test13[EnumWrap01_E3]);
  cPair = input.GetReflectedPair(12);
  TEST_EQUAL(cPair.name, "test13");
  TEST_EQUAL(cPair.value, "EnumWrap01_E1 | EnumWrap01_E2 | EnumWrap01_E3");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E1), "true");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E2), "true");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E3), "true");

  TEST_EQUAL(input.SetReflectedValue(
                 "test13", "EnumWrap01_E1|EnumWrap01_E2|EnumWrap01_E3"),
             Reflector::ErrorType::None);
  TEST_CHECK(input.test13[EnumWrap01_E1]);
  TEST_CHECK(input.test13[EnumWrap01_E2]);
  TEST_CHECK(input.test13[EnumWrap01_E3]);
  cPair = input.GetReflectedPair(12);
  TEST_EQUAL(cPair.name, "test13");
  TEST_EQUAL(cPair.value, "EnumWrap01_E1 | EnumWrap01_E2 | EnumWrap01_E3");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E1), "true");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E2), "true");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E3), "true");

  TEST_EQUAL(
      input.SetReflectedValue("test13", "EnumWrap01_E1 | EnumWrap01_E2 | "),
      Reflector::ErrorType::EmptyInput);
  TEST_CHECK(input.test13[EnumWrap01_E1]);
  TEST_CHECK(input.test13[EnumWrap01_E2]);
  TEST_CHECK(!input.test13[EnumWrap01_E3]);
  cPair = input.GetReflectedPair(12);
  TEST_EQUAL(cPair.name, "test13");
  TEST_EQUAL(cPair.value, "EnumWrap01_E1 | EnumWrap01_E2");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E1), "true");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E2), "true");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E3), "false");

  TEST_EQUAL(
      input.SetReflectedValue("test13", "EnumWrap01_E1 |  | EnumWrap01_E3"),
      Reflector::ErrorType::EmptyInput);
  TEST_CHECK(input.test13[EnumWrap01_E1]);
  TEST_CHECK(!input.test13[EnumWrap01_E2]);
  TEST_CHECK(input.test13[EnumWrap01_E3]);
  cPair = input.GetReflectedPair(12);
  TEST_EQUAL(cPair.name, "test13");
  TEST_EQUAL(cPair.value, "EnumWrap01_E1 | EnumWrap01_E3");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E1), "true");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E2), "false");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E3), "true");

  TEST_EQUAL(input.SetReflectedValue("test13", " |  | EnumWrap01_E3"),
             Reflector::ErrorType::EmptyInput);
  TEST_CHECK(!input.test13[EnumWrap01_E1]);
  TEST_CHECK(!input.test13[EnumWrap01_E2]);
  TEST_CHECK(input.test13[EnumWrap01_E3]);
  cPair = input.GetReflectedPair(12);
  TEST_EQUAL(cPair.name, "test13");
  TEST_EQUAL(cPair.value, "EnumWrap01_E3");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E1), "false");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E2), "false");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E3), "true");

  TEST_EQUAL(input.SetReflectedValue(
                 "test13", "EnumWrap01_E1 | EnumWrap01_ | EnumWrap01_E3"),
             Reflector::ErrorType::InvalidFormat);
  TEST_CHECK(input.test13[EnumWrap01_E1]);
  TEST_CHECK(!input.test13[EnumWrap01_E2]);
  TEST_CHECK(input.test13[EnumWrap01_E3]);
  cPair = input.GetReflectedPair(12);
  TEST_EQUAL(cPair.name, "test13");
  TEST_EQUAL(cPair.value, "EnumWrap01_E1 | EnumWrap01_E3");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E1), "true");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E2), "false");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E3), "true");

  TEST_EQUAL(
      input.SetReflectedValue("test13", "EnumWrap01_E1 || EnumWrap01_E3"),
      Reflector::ErrorType::EmptyInput);
  TEST_CHECK(input.test13[EnumWrap01_E1]);
  TEST_CHECK(!input.test13[EnumWrap01_E2]);
  TEST_CHECK(input.test13[EnumWrap01_E3]);
  cPair = input.GetReflectedPair(12);
  TEST_EQUAL(cPair.name, "test13");
  TEST_EQUAL(cPair.value, "EnumWrap01_E1 | EnumWrap01_E3");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E1), "true");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E2), "false");
  TEST_EQUAL(input.GetReflectedValue(12, EnumWrap01_E3), "true");

  return 0;
}

int test_reflector_subclass(reflClass &input) {
  Reflector::KVPair cPair = input.GetReflectedPair(21);
  TEST_EQUAL(cPair.name, "test22");
  TEST_EQUAL(cPair.value, "SUBCLASS_TYPE");
  TEST_CHECK(input.IsReflectedSubClass(21));

  auto rClass = input.GetReflectedSubClass("test22");
  ReflectorPureWrap sClass(rClass);
  subrefl &lClass = input.test22;

  TEST_EQUAL(lClass.data0, 0);
  TEST_EQUAL(sClass.SetReflectedValue("data0", "-17845"),
             Reflector::ErrorType::None);
  TEST_EQUAL(lClass.data0, -17845);
  cPair = sClass.GetReflectedPair(0);
  TEST_EQUAL(cPair.name, "data0");
  TEST_EQUAL(cPair.value, "-17845");

  TEST_EQUAL(lClass.data1, 0);
  TEST_EQUAL(sClass.SetReflectedValue("data1", "-1.5975"),
             Reflector::ErrorType::None);
  TEST_EQUAL(lClass.data1, -1.5975f);
  cPair = sClass.GetReflectedPair(1);
  TEST_EQUAL(cPair.name, "data1");
  TEST_EQUAL(cPair.value, "-1.5975");

  return 0;
}

int test_reflector_vector(reflClass &input) {
  TEST_EQUAL(input.test18, Vector());
  TEST_EQUAL(input.SetReflectedValue("test18", "[1.5, 2.8, 5.4]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test18, Vector(1.5f, 2.8f, 5.4f));
  Reflector::KVPair cPair = input.GetReflectedPair(17);
  TEST_EQUAL(cPair.name, "test18");
  TEST_EQUAL(cPair.value, "[1.5, 2.8, 5.4]");
  TEST_EQUAL(input.GetReflectedValue(17, 0), "1.5");
  TEST_EQUAL(input.GetReflectedValue(17, 1), "2.8");
  TEST_EQUAL(input.GetReflectedValue(17, 2), "5.4");

  TEST_EQUAL(input.SetReflectedValue("test18", "[3.5, 2.1, 1.4,]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test18, Vector(3.5f, 2.1f, 1.4f));

  TEST_EQUAL(input.SetReflectedValue("test18", "[1.2, 2.1, 5.9, 1.0]"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test18, Vector(1.2f, 2.1f, 5.9f));

  TEST_EQUAL(input.SetReflectedValue("test18", "[1.6, 2.5,]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test18, Vector(1.6f, 2.5f, 5.9f));

  TEST_EQUAL(input.SetReflectedValue("test18", "[3.6, 8.5]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test18, Vector(3.6f, 8.5f, 5.9f));

  TEST_EQUAL(
      input.SetReflectedValue(
          "test18", "   [      1.5      ,      2.8      ,      5.4     ]   "),
      Reflector::ErrorType::None);
  TEST_EQUAL(input.test18, Vector(1.5f, 2.8f, 5.4f));

  TEST_EQUAL(input.SetReflectedValue("test18", "3.5, 2.1, 1.4,]"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test18, Vector(1.5f, 2.8f, 5.4f));

  TEST_EQUAL(input.SetReflectedValue("test18", "[3.5, 2.1, 1.4,"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test18, Vector(1.5f, 2.8f, 5.4f));

  TEST_EQUAL(input.SetReflectedValue("test18", "3.5, 2.1, 1.4,"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test18, Vector(1.5f, 2.8f, 5.4f));

  TEST_EQUAL(input.SetReflectedValue("test18", "[3.5 2.1, 1.4,]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test18, Vector(3.5f, 1.4f, 5.4f));

  TEST_EQUAL(input.SetReflectedValue("test18", "[1.2, , 2.1,]"),
             Reflector::ErrorType::ShortInput);
  TEST_EQUAL(input.test18, Vector(1.2f, 1.4f, 5.4f));

  return 0;
}

int test_reflector_vector2(reflClass &input) {
  TEST_EQUAL(input.test19, Vector2());
  TEST_EQUAL(input.SetReflectedValue("test19", "[1.5, 5.4]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test19, Vector2(1.5f, 5.4f));
  Reflector::KVPair cPair = input.GetReflectedPair(18);
  TEST_EQUAL(cPair.name, "test19");
  TEST_EQUAL(cPair.value, "[1.5, 5.4]");
  TEST_EQUAL(input.GetReflectedValue(18, 0), "1.5");
  TEST_EQUAL(input.GetReflectedValue(18, 1), "5.4");

  TEST_EQUAL(input.SetReflectedValue("test19", "[3.5, 2.1,]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test19, Vector2(3.5f, 2.1f));

  TEST_EQUAL(input.SetReflectedValue("test19", "[1.2, 2.1, 5.9]"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test19, Vector2(1.2f, 2.1f));

  TEST_EQUAL(input.SetReflectedValue("test19", "[1.6, 2.5,]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test19, Vector2(1.6f, 2.5f));

  TEST_EQUAL(input.SetReflectedValue("test19", "[3.6, 8.5]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test19, Vector2(3.6f, 8.5f));

  TEST_EQUAL(input.SetReflectedValue("test19",
                                     "   [      1.5      ,      2.8      ]   "),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test19, Vector2(1.5f, 2.8f));

  TEST_EQUAL(input.SetReflectedValue("test19", "3.5, 2.1,]"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test19, Vector2(1.5f, 2.8f));

  TEST_EQUAL(input.SetReflectedValue("test19", "[3.5, 2.1,"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test19, Vector2(1.5f, 2.8f));

  TEST_EQUAL(input.SetReflectedValue("test19", "3.5, 2.1,"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test19, Vector2(1.5f, 2.8f));

  TEST_EQUAL(input.SetReflectedValue("test19", "[3.5 2.1,]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test19, Vector2(3.5f, 2.8f));

  TEST_EQUAL(input.SetReflectedValue("test19", "[1.2, , 2.1,]"),
             Reflector::ErrorType::ShortInput);
  TEST_EQUAL(input.test19, Vector2(1.2f, 2.8f));

  return 0;
}

int test_reflector_vector4(reflClass &input) {
  TEST_EQUAL(input.test20, Vector4());
  TEST_EQUAL(input.SetReflectedValue("test20", "[1.5, 2.8, 5.4, 7.2]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test20, Vector4(1.5f, 2.8f, 5.4f, 7.2f));
  Reflector::KVPair cPair = input.GetReflectedPair(19);
  TEST_EQUAL(cPair.name, "test20");
  TEST_EQUAL(cPair.value, "[1.5, 2.8, 5.4, 7.2]");
  TEST_EQUAL(input.GetReflectedValue(19, 0), "1.5");
  TEST_EQUAL(input.GetReflectedValue(19, 1), "2.8");
  TEST_EQUAL(input.GetReflectedValue(19, 2), "5.4");
  TEST_EQUAL(input.GetReflectedValue(19, 3), "7.2");

  TEST_EQUAL(input.SetReflectedValue("test20", "[3.5, 2.1, 1.4, 6.1,]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test20, Vector4(3.5f, 2.1f, 1.4f, 6.1f));

  TEST_EQUAL(input.SetReflectedValue("test20", "[1.2, 2.1, 5.9, 3.2, 1.0]"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test20, Vector4(1.2f, 2.1f, 5.9f, 3.2f));

  TEST_EQUAL(input.SetReflectedValue("test20", "[1.6, 2.5, 7.3]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test20, Vector4(1.6f, 2.5f, 7.3f, 3.2f));

  TEST_EQUAL(input.SetReflectedValue("test20", "[3.6, 8.5, 2.1]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test20, Vector4(3.6f, 8.5f, 2.1f, 3.2f));

  TEST_EQUAL(
      input.SetReflectedValue(
          "test20",
          "   [      1.5      ,      2.8      ,      5.4  ,    6.7   ]   "),
      Reflector::ErrorType::None);
  TEST_EQUAL(input.test20, Vector4(1.5f, 2.8f, 5.4f, 6.7f));

  TEST_EQUAL(input.SetReflectedValue("test20", "3.5, 2.1, 1.4,]"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test20, Vector4(1.5f, 2.8f, 5.4f, 6.7f));

  TEST_EQUAL(input.SetReflectedValue("test20", "[3.5, 2.1, 1.4,"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test20, Vector4(1.5f, 2.8f, 5.4f, 6.7f));

  TEST_EQUAL(input.SetReflectedValue("test20", "3.5, 2.1, 1.4,"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test20, Vector4(1.5f, 2.8f, 5.4f, 6.7f));

  TEST_EQUAL(input.SetReflectedValue("test20", "[3.5 2.1, 1.4,]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test20, Vector4(3.5f, 1.4f, 5.4f, 6.7f));

  TEST_EQUAL(input.SetReflectedValue("test20", "[1.2, , 2.1,]"),
             Reflector::ErrorType::ShortInput);
  TEST_EQUAL(input.test20, Vector4(1.2f, 1.4f, 5.4f, 6.7f));

  return 0;
}

int test_reflector_vector4A16(reflClass &input) {
  TEST_EQUAL(input.test21, Vector4A16());
  TEST_EQUAL(input.SetReflectedValue("test21", "[1.5, 2.8, 5.4, 7.2]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test21, Vector4A16(1.5f, 2.8f, 5.4f, 7.2f));
  Reflector::KVPair cPair = input.GetReflectedPair(20);
  TEST_EQUAL(cPair.name, "test21");
  TEST_EQUAL(cPair.value, "[1.5, 2.8, 5.4, 7.2]");
  TEST_EQUAL(input.GetReflectedValue(20, 0), "1.5");
  TEST_EQUAL(input.GetReflectedValue(20, 1), "2.8");
  TEST_EQUAL(input.GetReflectedValue(20, 2), "5.4");
  TEST_EQUAL(input.GetReflectedValue(20, 3), "7.2");

  TEST_EQUAL(input.SetReflectedValue("test21", "[3.5, 2.1, 1.4, 6.1,]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test21, Vector4A16(3.5f, 2.1f, 1.4f, 6.1f));

  TEST_EQUAL(input.SetReflectedValue("test21", "[1.2, 2.1, 5.9, 3.2, 1.0]"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(input.test21, Vector4A16(1.2f, 2.1f, 5.9f, 3.2f));

  TEST_EQUAL(input.SetReflectedValue("test21", "[1.6, 2.5, 7.3]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test21, Vector4A16(1.6f, 2.5f, 7.3f, 3.2f));

  TEST_EQUAL(input.SetReflectedValue("test21", "[3.6, 8.5, 2.1]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test21, Vector4A16(3.6f, 8.5f, 2.1f, 3.2f));

  TEST_EQUAL(
      input.SetReflectedValue(
          "test21",
          "   [      1.5      ,      2.8      ,      5.4  ,    6.7   ]   "),
      Reflector::ErrorType::None);
  TEST_EQUAL(input.test21, Vector4A16(1.5f, 2.8f, 5.4f, 6.7f));

  TEST_EQUAL(input.SetReflectedValue("test21", "3.5, 2.1, 1.4,]"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test21, Vector4A16(1.5f, 2.8f, 5.4f, 6.7f));

  TEST_EQUAL(input.SetReflectedValue("test21", "[3.5, 2.1, 1.4,"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test21, Vector4A16(1.5f, 2.8f, 5.4f, 6.7f));

  TEST_EQUAL(input.SetReflectedValue("test21", "3.5, 2.1, 1.4,"),
             Reflector::ErrorType::InvalidFormat);
  TEST_EQUAL(input.test21, Vector4A16(1.5f, 2.8f, 5.4f, 6.7f));

  TEST_EQUAL(input.SetReflectedValue("test21", "[3.5 2.1, 1.4,]"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test21, Vector4A16(3.5f, 1.4f, 5.4f, 6.7f));

  TEST_EQUAL(input.SetReflectedValue("test21", "[1.2, , 2.1,]"),
             Reflector::ErrorType::ShortInput);
  TEST_EQUAL(input.test21, Vector4A16(1.2f, 1.4f, 5.4f, 6.7f));

  return 0;
}

int test_reflector_arrays(reflClass &input) {
  TEST_EQUAL(input.test40[0], false);
  TEST_EQUAL(input.test40[1], false);
  TEST_EQUAL(input.test40[2], false);
  TEST_EQUAL(input.test40[3], false);
  input.SetReflectedValue("test40", "{false, true, true, false}");
  TEST_EQUAL(input.test40[0], false);
  TEST_EQUAL(input.test40[1], true);
  TEST_EQUAL(input.test40[2], true);
  TEST_EQUAL(input.test40[3], false);
  Reflector::KVPair cPair = input.GetReflectedPair(22);
  TEST_EQUAL(cPair.name, "test40");
  TEST_EQUAL(cPair.value, "{false, true, true, false}");
  TEST_EQUAL(input.GetReflectedValue(22, 0), "false");
  TEST_EQUAL(input.GetReflectedValue(22, 1), "true");
  TEST_EQUAL(input.GetReflectedValue(22, 2), "true");
  TEST_EQUAL(input.GetReflectedValue(22, 3), "false");
  input.SetReflectedValue(22, "true", 0);
  TEST_EQUAL(input.test40[0], true);
  TEST_EQUAL(input.test40[1], true);
  TEST_EQUAL(input.test40[2], true);
  TEST_EQUAL(input.test40[3], false);
  input.SetReflectedValue(22, "false", 1);
  TEST_EQUAL(input.test40[0], true);
  TEST_EQUAL(input.test40[1], false);
  TEST_EQUAL(input.test40[2], true);
  TEST_EQUAL(input.test40[3], false);
  input.SetReflectedValue(22, "false", 2);
  TEST_EQUAL(input.test40[0], true);
  TEST_EQUAL(input.test40[1], false);
  TEST_EQUAL(input.test40[2], false);
  TEST_EQUAL(input.test40[3], false);
  input.SetReflectedValue(22, "true", 3);
  TEST_EQUAL(input.test40[0], true);
  TEST_EQUAL(input.test40[1], false);
  TEST_EQUAL(input.test40[2], false);
  TEST_EQUAL(input.test40[3], true);

  TEST_EQUAL(input.test41[0], 0);
  TEST_EQUAL(input.test41[1], 0);
  input.SetReflectedValue("test41", "{12, -69}");
  TEST_EQUAL(input.test41[0], 12);
  TEST_EQUAL(input.test41[1], -69);
  cPair = input.GetReflectedPair(23);
  TEST_EQUAL(cPair.name, "test41");
  TEST_EQUAL(cPair.value, "{12, -69}");
  TEST_EQUAL(input.GetReflectedValue(23, 0), "12");
  TEST_EQUAL(input.GetReflectedValue(23, 1), "-69");
  input.SetReflectedValue(23, "13", 0);
  TEST_EQUAL(input.test41[0], 13);
  TEST_EQUAL(input.test41[1], -69);
  input.SetReflectedValue(23, "-66", 1);
  TEST_EQUAL(input.test41[0], 13);
  TEST_EQUAL(input.test41[1], -66);

  TEST_EQUAL(input.test42[0], 0);
  TEST_EQUAL(input.test42[1], 0);
  TEST_EQUAL(input.test42[2], 0);
  TEST_EQUAL(input.test42[3], 0);
  input.SetReflectedValue("test42", "{128, 57, 251, -75}");
  TEST_EQUAL(input.test42[0], 128);
  TEST_EQUAL(input.test42[1], 57);
  TEST_EQUAL(input.test42[2], 251);
  TEST_EQUAL(input.test42[3], 181);
  cPair = input.GetReflectedPair(24);
  TEST_EQUAL(cPair.name, "test42");
  TEST_EQUAL(cPair.value, "{128, 57, 251, 181}");
  TEST_EQUAL(input.GetReflectedValue(24, 0), "128");
  TEST_EQUAL(input.GetReflectedValue(24, 1), "57");
  TEST_EQUAL(input.GetReflectedValue(24, 2), "251");
  TEST_EQUAL(input.GetReflectedValue(24, 3), "181");
  input.SetReflectedValue(24, "120", 0);
  TEST_EQUAL(input.test42[0], 120);
  TEST_EQUAL(input.test42[1], 57);
  TEST_EQUAL(input.test42[2], 251);
  TEST_EQUAL(input.test42[3], 181);
  input.SetReflectedValue(24, "50", 1);
  TEST_EQUAL(input.test42[0], 120);
  TEST_EQUAL(input.test42[1], 50);
  TEST_EQUAL(input.test42[2], 251);
  TEST_EQUAL(input.test42[3], 181);
  input.SetReflectedValue(24, "252", 2);
  TEST_EQUAL(input.test42[0], 120);
  TEST_EQUAL(input.test42[1], 50);
  TEST_EQUAL(input.test42[2], 252);
  TEST_EQUAL(input.test42[3], 181);
  input.SetReflectedValue(24, "172", 3);
  TEST_EQUAL(input.test42[0], 120);
  TEST_EQUAL(input.test42[1], 50);
  TEST_EQUAL(input.test42[2], 252);
  TEST_EQUAL(input.test42[3], 172);

  TEST_EQUAL(input.test43[0], 0);
  TEST_EQUAL(input.test43[1], 0);
  input.SetReflectedValue("test43", "{1200, -6956}");
  TEST_EQUAL(input.test43[0], 1200);
  TEST_EQUAL(input.test43[1], -6956);
  cPair = input.GetReflectedPair(25);
  TEST_EQUAL(cPair.name, "test43");
  TEST_EQUAL(cPair.value, "{1200, -6956}");
  TEST_EQUAL(input.GetReflectedValue(25, 0), "1200");
  TEST_EQUAL(input.GetReflectedValue(25, 1), "-6956");
  input.SetReflectedValue(25, "1208", 0);
  TEST_EQUAL(input.test43[0], 1208);
  TEST_EQUAL(input.test43[1], -6956);
  input.SetReflectedValue(25, "-5669", 1);
  TEST_EQUAL(input.test43[0], 1208);
  TEST_EQUAL(input.test43[1], -5669);

  TEST_EQUAL(input.test44[0], 0);
  TEST_EQUAL(input.test44[1], 0);
  TEST_EQUAL(input.test44[2], 0);
  TEST_EQUAL(input.test44[3], 0);
  input.SetReflectedValue("test44", "{1286, 572, 2515, -755}");
  TEST_EQUAL(input.test44[0], 1286);
  TEST_EQUAL(input.test44[1], 572);
  TEST_EQUAL(input.test44[2], 2515);
  TEST_EQUAL(input.test44[3], 64781);
  cPair = input.GetReflectedPair(26);
  TEST_EQUAL(cPair.name, "test44");
  TEST_EQUAL(cPair.value, "{1286, 572, 2515, 64781}");
  TEST_EQUAL(input.GetReflectedValue(26, 0), "1286");
  TEST_EQUAL(input.GetReflectedValue(26, 1), "572");
  TEST_EQUAL(input.GetReflectedValue(26, 2), "2515");
  TEST_EQUAL(input.GetReflectedValue(26, 3), "64781");
  input.SetReflectedValue(26, "1862", 0);
  TEST_EQUAL(input.test44[0], 1862);
  TEST_EQUAL(input.test44[1], 572);
  TEST_EQUAL(input.test44[2], 2515);
  TEST_EQUAL(input.test44[3], 64781);
  input.SetReflectedValue(26, "678", 1);
  TEST_EQUAL(input.test44[0], 1862);
  TEST_EQUAL(input.test44[1], 678);
  TEST_EQUAL(input.test44[2], 2515);
  TEST_EQUAL(input.test44[3], 64781);
  input.SetReflectedValue(26, "4879", 2);
  TEST_EQUAL(input.test44[0], 1862);
  TEST_EQUAL(input.test44[1], 678);
  TEST_EQUAL(input.test44[2], 4879);
  TEST_EQUAL(input.test44[3], 64781);
  input.SetReflectedValue(26, "62158", 3);
  TEST_EQUAL(input.test44[0], 1862);
  TEST_EQUAL(input.test44[1], 678);
  TEST_EQUAL(input.test44[2], 4879);
  TEST_EQUAL(input.test44[3], 62158);

  TEST_EQUAL(input.test45[0], 0);
  TEST_EQUAL(input.test45[1], 0);
  input.SetReflectedValue("test45", "{120053, -695641}");
  TEST_EQUAL(input.test45[0], 120053);
  TEST_EQUAL(input.test45[1], -695641);
  cPair = input.GetReflectedPair(27);
  TEST_EQUAL(cPair.name, "test45");
  TEST_EQUAL(cPair.value, "{120053, -695641}");
  TEST_EQUAL(input.GetReflectedValue(27, 0), "120053");
  TEST_EQUAL(input.GetReflectedValue(27, 1), "-695641");
  input.SetReflectedValue(27, "350021", 0);
  TEST_EQUAL(input.test45[0], 350021);
  TEST_EQUAL(input.test45[1], -695641);
  input.SetReflectedValue(27, "-415669", 1);
  TEST_EQUAL(input.test45[0], 350021);
  TEST_EQUAL(input.test45[1], -415669);

  TEST_EQUAL(input.test46[0], 0);
  TEST_EQUAL(input.test46[1], 0);
  TEST_EQUAL(input.test46[2], 0);
  TEST_EQUAL(input.test46[3], 0);
  input.SetReflectedValue("test46", "{128612, 572573, 2515513, -755613}");
  TEST_EQUAL(input.test46[0], 128612);
  TEST_EQUAL(input.test46[1], 572573);
  TEST_EQUAL(input.test46[2], 2515513);
  TEST_EQUAL(input.test46[3], 4294211683);
  cPair = input.GetReflectedPair(28);
  TEST_EQUAL(cPair.name, "test46");
  TEST_EQUAL(cPair.value, "{128612, 572573, 2515513, 4294211683}");
  TEST_EQUAL(input.GetReflectedValue(28, 0), "128612");
  TEST_EQUAL(input.GetReflectedValue(28, 1), "572573");
  TEST_EQUAL(input.GetReflectedValue(28, 2), "2515513");
  TEST_EQUAL(input.GetReflectedValue(28, 3), "4294211683");

  TEST_EQUAL(input.test47[0], 0);
  TEST_EQUAL(input.test47[1], 0);
  input.SetReflectedValue("test47", "{120053613654541, -6956415461654}");
  TEST_EQUAL(input.test47[0], 120053613654541);
  TEST_EQUAL(input.test47[1], -6956415461654);
  cPair = input.GetReflectedPair(29);
  TEST_EQUAL(cPair.name, "test47");
  TEST_EQUAL(cPair.value, "{120053613654541, -6956415461654}");
  TEST_EQUAL(input.GetReflectedValue(29, 0), "120053613654541");
  TEST_EQUAL(input.GetReflectedValue(29, 1), "-6956415461654");

  TEST_EQUAL(input.test48[0], 0);
  TEST_EQUAL(input.test48[1], 0);
  TEST_EQUAL(input.test48[2], 0);
  TEST_EQUAL(input.test48[3], 0);
  input.SetReflectedValue(
      "test48",
      "{128612465345, 5725735436343, 2515513435453, -75561345345321}");
  TEST_EQUAL(input.test48[0], 128612465345);
  TEST_EQUAL(input.test48[1], 5725735436343);
  TEST_EQUAL(input.test48[2], 2515513435453);
  TEST_EQUAL(input.test48[3], 18446668512364206295ULL);
  cPair = input.GetReflectedPair(30);
  TEST_EQUAL(cPair.name, "test48");
  TEST_EQUAL(
      cPair.value,
      "{128612465345, 5725735436343, 2515513435453, 18446668512364206295}");
  TEST_EQUAL(input.GetReflectedValue(30, 0), "128612465345");
  TEST_EQUAL(input.GetReflectedValue(30, 1), "5725735436343");
  TEST_EQUAL(input.GetReflectedValue(30, 2), "2515513435453");
  TEST_EQUAL(input.GetReflectedValue(30, 3), "18446668512364206295");

  TEST_EQUAL(input.test49[0], 0);
  TEST_EQUAL(input.test49[1], 0);
  input.SetReflectedValue("test49", "{1.5, -3.6}");
  TEST_EQUAL(input.test49[0], 1.5f);
  TEST_EQUAL(input.test49[1], -3.6f);
  cPair = input.GetReflectedPair(31);
  TEST_EQUAL(cPair.name, "test49");
  TEST_EQUAL(cPair.value, "{1.5, -3.6}");
  TEST_EQUAL(input.GetReflectedValue(31, 0), "1.5");
  TEST_EQUAL(input.GetReflectedValue(31, 1), "-3.6");
  input.SetReflectedValue(31, "1.22", 0);
  TEST_EQUAL(input.test49[0], 1.22f);
  TEST_EQUAL(input.test49[1], -3.6f);
  input.SetReflectedValue(31, "-3.72", 1);
  TEST_EQUAL(input.test49[0], 1.22f);
  TEST_EQUAL(input.test49[1], -3.72f);

  TEST_EQUAL(input.test50[0], 0);
  TEST_EQUAL(input.test50[1], 0);
  TEST_EQUAL(input.test50[2], 0);
  TEST_EQUAL(input.test50[3], 0);
  input.SetReflectedValue("test50", "{1.536, 9.861, 6.45521, -7.32123}");
  TEST_EQUAL(input.test50[0], 1.536);
  TEST_EQUAL(input.test50[1], 9.861);
  TEST_EQUAL(input.test50[2], 6.45521);
  TEST_EQUAL(input.test50[3], -7.32123);
  cPair = input.GetReflectedPair(32);
  TEST_EQUAL(cPair.name, "test50");
  TEST_EQUAL(cPair.value, "{1.536, 9.861, 6.45521, -7.32123}");
  TEST_EQUAL(input.GetReflectedValue(32, 0), "1.536");
  TEST_EQUAL(input.GetReflectedValue(32, 1), "9.861");
  TEST_EQUAL(input.GetReflectedValue(32, 2), "6.45521");
  TEST_EQUAL(input.GetReflectedValue(32, 3), "-7.32123");

  TEST_NOT_EQUAL(input.test51[0], EnumWrap00::E1);
  TEST_NOT_EQUAL(input.test51[0], EnumWrap00::E2);
  TEST_NOT_EQUAL(input.test51[0], EnumWrap00::E3);
  TEST_NOT_EQUAL(input.test51[1], EnumWrap00::E1);
  TEST_NOT_EQUAL(input.test51[1], EnumWrap00::E2);
  TEST_NOT_EQUAL(input.test51[1], EnumWrap00::E3);
  input.SetReflectedValue("test51", "{E1 | E3, E2}");
  TEST_EQUAL(input.test51[0], EnumWrap00::E1);
  TEST_NOT_EQUAL(input.test51[0], EnumWrap00::E2);
  TEST_EQUAL(input.test51[0], EnumWrap00::E3);
  TEST_NOT_EQUAL(input.test51[1], EnumWrap00::E1);
  TEST_EQUAL(input.test51[1], EnumWrap00::E2);
  TEST_NOT_EQUAL(input.test51[1], EnumWrap00::E3);
  cPair = input.GetReflectedPair(33);
  TEST_EQUAL(cPair.name, "test51");
  TEST_EQUAL(cPair.value, "{E1 | E3, E2}");
  TEST_EQUAL(input.GetReflectedValue(33, 0), "E1 | E3");
  TEST_EQUAL(input.GetReflectedValue(33, 1), "E2");
  TEST_EQUAL(input.GetReflectedValue(33, 0, (size_t)EnumWrap00::E1), "true");
  TEST_EQUAL(input.GetReflectedValue(33, 0, (size_t)EnumWrap00::E2), "false");
  TEST_EQUAL(input.GetReflectedValue(33, 0, (size_t)EnumWrap00::E3), "true");
  TEST_EQUAL(input.GetReflectedValue(33, 1, (size_t)EnumWrap00::E1), "false");
  TEST_EQUAL(input.GetReflectedValue(33, 1, (size_t)EnumWrap00::E2), "true");
  TEST_EQUAL(input.GetReflectedValue(33, 1, (size_t)EnumWrap00::E3), "false");
  input.SetReflectedValue(33, "E1", 0);
  TEST_EQUAL(input.test51[0], EnumWrap00::E1);
  TEST_NOT_EQUAL(input.test51[0], EnumWrap00::E2);
  TEST_NOT_EQUAL(input.test51[0], EnumWrap00::E3);
  TEST_NOT_EQUAL(input.test51[1], EnumWrap00::E1);
  TEST_EQUAL(input.test51[1], EnumWrap00::E2);
  TEST_NOT_EQUAL(input.test51[1], EnumWrap00::E3);
  input.SetReflectedValue(33, "E2 | E3", 1);
  TEST_EQUAL(input.test51[0], EnumWrap00::E1);
  TEST_NOT_EQUAL(input.test51[0], EnumWrap00::E2);
  TEST_NOT_EQUAL(input.test51[0], EnumWrap00::E3);
  TEST_NOT_EQUAL(input.test51[1], EnumWrap00::E1);
  TEST_EQUAL(input.test51[1], EnumWrap00::E2);
  TEST_EQUAL(input.test51[1], EnumWrap00::E3);

  TEST_NOT_EQUAL(input.test52[0], EnumWrap01_E1);
  TEST_NOT_EQUAL(input.test52[0], EnumWrap01_E2);
  TEST_NOT_EQUAL(input.test52[0], EnumWrap01_E3);
  TEST_NOT_EQUAL(input.test52[1], EnumWrap01_E1);
  TEST_NOT_EQUAL(input.test52[1], EnumWrap01_E2);
  TEST_NOT_EQUAL(input.test52[1], EnumWrap01_E3);
  TEST_NOT_EQUAL(input.test52[2], EnumWrap01_E1);
  TEST_NOT_EQUAL(input.test52[2], EnumWrap01_E2);
  TEST_NOT_EQUAL(input.test52[2], EnumWrap01_E3);
  TEST_NOT_EQUAL(input.test52[3], EnumWrap01_E1);
  TEST_NOT_EQUAL(input.test52[3], EnumWrap01_E2);
  TEST_NOT_EQUAL(input.test52[3], EnumWrap01_E3);
  input.SetReflectedValue("test52",
                          "{EnumWrap01_E1 | EnumWrap01_E3, EnumWrap01_E2, "
                          "EnumWrap01_E2 | EnumWrap01_E3}");
  TEST_EQUAL(input.test52[0], EnumWrap01_E1);
  TEST_NOT_EQUAL(input.test52[0], EnumWrap01_E2);
  TEST_EQUAL(input.test52[0], EnumWrap01_E3);
  TEST_NOT_EQUAL(input.test52[1], EnumWrap01_E1);
  TEST_EQUAL(input.test52[1], EnumWrap01_E2);
  TEST_NOT_EQUAL(input.test52[1], EnumWrap01_E3);
  TEST_NOT_EQUAL(input.test52[2], EnumWrap01_E1);
  TEST_EQUAL(input.test52[2], EnumWrap01_E2);
  TEST_EQUAL(input.test52[2], EnumWrap01_E3);
  TEST_NOT_EQUAL(input.test52[3], EnumWrap01_E1);
  TEST_NOT_EQUAL(input.test52[3], EnumWrap01_E2);
  TEST_NOT_EQUAL(input.test52[3], EnumWrap01_E3);
  cPair = input.GetReflectedPair(34);
  TEST_EQUAL(cPair.name, "test52");
  TEST_EQUAL(cPair.value, "{EnumWrap01_E1 | EnumWrap01_E3, EnumWrap01_E2, "
                          "EnumWrap01_E2 | EnumWrap01_E3, NULL}");
  TEST_EQUAL(input.GetReflectedValue(34, 0), "EnumWrap01_E1 | EnumWrap01_E3");
  TEST_EQUAL(input.GetReflectedValue(34, 1), "EnumWrap01_E2");
  TEST_EQUAL(input.GetReflectedValue(34, 2), "EnumWrap01_E2 | EnumWrap01_E3");
  TEST_EQUAL(input.GetReflectedValue(34, 3), "NULL");
  TEST_EQUAL(input.GetReflectedValue(34, 0, EnumWrap01_E1), "true");
  TEST_EQUAL(input.GetReflectedValue(34, 0, EnumWrap01_E2), "false");
  TEST_EQUAL(input.GetReflectedValue(34, 0, EnumWrap01_E3), "true");
  TEST_EQUAL(input.GetReflectedValue(34, 1, EnumWrap01_E1), "false");
  TEST_EQUAL(input.GetReflectedValue(34, 1, EnumWrap01_E2), "true");
  TEST_EQUAL(input.GetReflectedValue(34, 1, EnumWrap01_E3), "false");
  TEST_EQUAL(input.GetReflectedValue(34, 2, EnumWrap01_E1), "false");
  TEST_EQUAL(input.GetReflectedValue(34, 2, EnumWrap01_E2), "true");
  TEST_EQUAL(input.GetReflectedValue(34, 2, EnumWrap01_E3), "true");
  TEST_EQUAL(input.GetReflectedValue(34, 3, EnumWrap01_E1), "false");
  TEST_EQUAL(input.GetReflectedValue(34, 3, EnumWrap01_E2), "false");
  TEST_EQUAL(input.GetReflectedValue(34, 3, EnumWrap01_E3), "false");
  input.SetReflectedValue(34, "NULL", 0);
  TEST_NOT_EQUAL(input.test52[0], EnumWrap01_E1);
  TEST_NOT_EQUAL(input.test52[0], EnumWrap01_E2);
  TEST_NOT_EQUAL(input.test52[0], EnumWrap01_E3);
  TEST_NOT_EQUAL(input.test52[1], EnumWrap01_E1);
  TEST_EQUAL(input.test52[1], EnumWrap01_E2);
  TEST_NOT_EQUAL(input.test52[1], EnumWrap01_E3);
  TEST_NOT_EQUAL(input.test52[2], EnumWrap01_E1);
  TEST_EQUAL(input.test52[2], EnumWrap01_E2);
  TEST_EQUAL(input.test52[2], EnumWrap01_E3);
  TEST_NOT_EQUAL(input.test52[3], EnumWrap01_E1);
  TEST_NOT_EQUAL(input.test52[3], EnumWrap01_E2);
  TEST_NOT_EQUAL(input.test52[3], EnumWrap01_E3);
  input.SetReflectedValue(34, "EnumWrap01_E1 | EnumWrap01_E3", 1);
  TEST_NOT_EQUAL(input.test52[0], EnumWrap01_E1);
  TEST_NOT_EQUAL(input.test52[0], EnumWrap01_E2);
  TEST_NOT_EQUAL(input.test52[0], EnumWrap01_E3);
  TEST_EQUAL(input.test52[1], EnumWrap01_E1);
  TEST_NOT_EQUAL(input.test52[1], EnumWrap01_E2);
  TEST_EQUAL(input.test52[1], EnumWrap01_E3);
  TEST_NOT_EQUAL(input.test52[2], EnumWrap01_E1);
  TEST_EQUAL(input.test52[2], EnumWrap01_E2);
  TEST_EQUAL(input.test52[2], EnumWrap01_E3);
  TEST_NOT_EQUAL(input.test52[3], EnumWrap01_E1);
  TEST_NOT_EQUAL(input.test52[3], EnumWrap01_E2);
  TEST_NOT_EQUAL(input.test52[3], EnumWrap01_E3);
  input.SetReflectedValue(34, "EnumWrap01_E2", 2);
  TEST_NOT_EQUAL(input.test52[0], EnumWrap01_E1);
  TEST_NOT_EQUAL(input.test52[0], EnumWrap01_E2);
  TEST_NOT_EQUAL(input.test52[0], EnumWrap01_E3);
  TEST_EQUAL(input.test52[1], EnumWrap01_E1);
  TEST_NOT_EQUAL(input.test52[1], EnumWrap01_E2);
  TEST_EQUAL(input.test52[1], EnumWrap01_E3);
  TEST_NOT_EQUAL(input.test52[2], EnumWrap01_E1);
  TEST_EQUAL(input.test52[2], EnumWrap01_E2);
  TEST_NOT_EQUAL(input.test52[2], EnumWrap01_E3);
  TEST_NOT_EQUAL(input.test52[3], EnumWrap01_E1);
  TEST_NOT_EQUAL(input.test52[3], EnumWrap01_E2);
  TEST_NOT_EQUAL(input.test52[3], EnumWrap01_E3);
  input.SetReflectedValue(34, "EnumWrap01_E2 | EnumWrap01_E3", 3);
  TEST_NOT_EQUAL(input.test52[0], EnumWrap01_E1);
  TEST_NOT_EQUAL(input.test52[0], EnumWrap01_E2);
  TEST_NOT_EQUAL(input.test52[0], EnumWrap01_E3);
  TEST_EQUAL(input.test52[1], EnumWrap01_E1);
  TEST_NOT_EQUAL(input.test52[1], EnumWrap01_E2);
  TEST_EQUAL(input.test52[1], EnumWrap01_E3);
  TEST_NOT_EQUAL(input.test52[2], EnumWrap01_E1);
  TEST_EQUAL(input.test52[2], EnumWrap01_E2);
  TEST_NOT_EQUAL(input.test52[2], EnumWrap01_E3);
  TEST_NOT_EQUAL(input.test52[3], EnumWrap01_E1);
  TEST_EQUAL(input.test52[3], EnumWrap01_E2);
  TEST_EQUAL(input.test52[3], EnumWrap01_E3);

  TEST_EQUAL(input.test53[0], EnumWrap00::E1);
  TEST_EQUAL(input.test53[1], EnumWrap00::E1);
  input.SetReflectedValue("test53", "{E2, E1}");
  TEST_EQUAL(input.test53[0], EnumWrap00::E2);
  TEST_EQUAL(input.test53[1], EnumWrap00::E1);
  cPair = input.GetReflectedPair(35);
  TEST_EQUAL(cPair.name, "test53");
  TEST_EQUAL(cPair.value, "{E2, E1}");
  TEST_EQUAL(input.GetReflectedValue(35, 0), "E2");
  TEST_EQUAL(input.GetReflectedValue(35, 1), "E1");
  input.SetReflectedValue(35, "E3", 0);
  TEST_EQUAL(input.test53[0], EnumWrap00::E3);
  TEST_EQUAL(input.test53[1], EnumWrap00::E1);
  input.SetReflectedValue(35, "E2", 1);
  TEST_EQUAL(input.test53[0], EnumWrap00::E3);
  TEST_EQUAL(input.test53[1], EnumWrap00::E2);

  TEST_EQUAL(input.test54[0], EnumWrap02::E4);
  TEST_EQUAL(input.test54[1], EnumWrap02::E4);
  TEST_EQUAL(input.test54[2], EnumWrap02::E4);
  TEST_EQUAL(input.test54[3], EnumWrap02::E4);
  input.SetReflectedValue("test54", "{E5, E6, E4, E5}");
  TEST_EQUAL(input.test54[0], EnumWrap02::E5);
  TEST_EQUAL(input.test54[1], EnumWrap02::E6);
  TEST_EQUAL(input.test54[2], EnumWrap02::E4);
  TEST_EQUAL(input.test54[3], EnumWrap02::E5);
  cPair = input.GetReflectedPair(36);
  TEST_EQUAL(cPair.name, "test54");
  TEST_EQUAL(cPair.value, "{E5, E6, E4, E5}");
  TEST_EQUAL(input.GetReflectedValue(36, 0), "E5");
  TEST_EQUAL(input.GetReflectedValue(36, 1), "E6");
  TEST_EQUAL(input.GetReflectedValue(36, 2), "E4");
  TEST_EQUAL(input.GetReflectedValue(36, 3), "E5");

  TEST_EQUAL(int(input.test55[0]), 0);
  TEST_EQUAL(int(input.test55[1]), 0);
  input.SetReflectedValue("test55", "{E9, E8}");
  TEST_EQUAL(input.test55[0], EnumWrap03::E9);
  TEST_EQUAL(input.test55[1], EnumWrap03::E8);
  cPair = input.GetReflectedPair(37);
  TEST_EQUAL(cPair.name, "test55");
  TEST_EQUAL(cPair.value, "{E9, E8}");
  TEST_EQUAL(input.GetReflectedValue(37, 0), "E9");
  TEST_EQUAL(input.GetReflectedValue(37, 1), "E8");

  TEST_EQUAL(input.test56[0], EnumWrap04::E10);
  TEST_EQUAL(input.test56[1], EnumWrap04::E10);
  TEST_EQUAL(input.test56[2], EnumWrap04::E10);
  TEST_EQUAL(input.test56[3], EnumWrap04::E10);
  input.SetReflectedValue("test56", "{E11, E12, E10, E12}");
  TEST_EQUAL(input.test56[0], EnumWrap04::E11);
  TEST_EQUAL(input.test56[1], EnumWrap04::E12);
  TEST_EQUAL(input.test56[2], EnumWrap04::E10);
  TEST_EQUAL(input.test56[3], EnumWrap04::E12);
  cPair = input.GetReflectedPair(38);
  TEST_EQUAL(cPair.name, "test56");
  TEST_EQUAL(cPair.value, "{E11, E12, E10, E12}");
  TEST_EQUAL(input.GetReflectedValue(38, 0), "E11");
  TEST_EQUAL(input.GetReflectedValue(38, 1), "E12");
  TEST_EQUAL(input.GetReflectedValue(38, 2), "E10");
  TEST_EQUAL(input.GetReflectedValue(38, 3), "E12");

  TEST_EQUAL(input.test57[0], Vector());
  TEST_EQUAL(input.test57[1], Vector());
  input.SetReflectedValue("test57", "{[5.6, 51.6, 31.7], [18.1, 3.5, 6.1]}");
  TEST_EQUAL(input.test57[0], Vector(5.6f, 51.6f, 31.7f));
  TEST_EQUAL(input.test57[1], Vector(18.1f, 3.5f, 6.1f));
  cPair = input.GetReflectedPair(39);
  TEST_EQUAL(cPair.name, "test57");
  TEST_EQUAL(cPair.value, "{[5.6, 51.6, 31.7], [18.1, 3.5, 6.1]}");
  TEST_EQUAL(input.GetReflectedValue(39, 0), "[5.6, 51.6, 31.7]");
  TEST_EQUAL(input.GetReflectedValue(39, 1), "[18.1, 3.5, 6.1]");
  TEST_EQUAL(input.GetReflectedValue(39, 0, 0), "5.6");
  TEST_EQUAL(input.GetReflectedValue(39, 0, 1), "51.6");
  TEST_EQUAL(input.GetReflectedValue(39, 0, 2), "31.7");
  TEST_EQUAL(input.GetReflectedValue(39, 1, 0), "18.1");
  TEST_EQUAL(input.GetReflectedValue(39, 1, 1), "3.5");
  TEST_EQUAL(input.GetReflectedValue(39, 1, 2), "6.1");
  input.SetReflectedValue(39, "[7.1, 11.8, 105.1]", 0);
  TEST_EQUAL(input.test57[0], Vector(7.1f, 11.8f, 105.1f));
  TEST_EQUAL(input.test57[1], Vector(18.1f, 3.5f, 6.1f));
  input.SetReflectedValue(39, "[12.5, 78.1, 478.85]", 1);
  TEST_EQUAL(input.test57[0], Vector(7.1, 11.8f, 105.1f));
  TEST_EQUAL(input.test57[1], Vector(12.5f, 78.1f, 478.85f));
  input.SetReflectedValue(39, "8.11", 0, 1);
  TEST_EQUAL(input.test57[0], Vector(7.1f, 8.11f, 105.1f));
  TEST_EQUAL(input.test57[1], Vector(12.5f, 78.1f, 478.85f));
  input.SetReflectedValue(39, "54.62", 1, 2);
  TEST_EQUAL(input.test57[0], Vector(7.1f, 8.11f, 105.1f));
  TEST_EQUAL(input.test57[1], Vector(12.5f, 78.1f, 54.62f));

  TEST_EQUAL(input.test58[0], Vector2());
  TEST_EQUAL(input.test58[1], Vector2());
  TEST_EQUAL(input.test58[2], Vector2());
  TEST_EQUAL(input.test58[3], Vector2());
  input.SetReflectedValue(
      "test58", "{[5.6, 51.6], [31.7, 18.1], [3.5, 6.1], [7.5, 62.1]}");
  TEST_EQUAL(input.test58[0], Vector2(5.6f, 51.6f));
  TEST_EQUAL(input.test58[1], Vector2(31.7f, 18.1f));
  TEST_EQUAL(input.test58[2], Vector2(3.5f, 6.1f));
  TEST_EQUAL(input.test58[3], Vector2(7.5f, 62.1f));
  cPair = input.GetReflectedPair(40);
  TEST_EQUAL(cPair.name, "test58");
  TEST_EQUAL(cPair.value,
             "{[5.6, 51.6], [31.7, 18.1], [3.5, 6.1], [7.5, 62.1]}");
  TEST_EQUAL(input.GetReflectedValue(40, 0), "[5.6, 51.6]");
  TEST_EQUAL(input.GetReflectedValue(40, 1), "[31.7, 18.1]");
  TEST_EQUAL(input.GetReflectedValue(40, 2), "[3.5, 6.1]");
  TEST_EQUAL(input.GetReflectedValue(40, 3), "[7.5, 62.1]");
  TEST_EQUAL(input.GetReflectedValue(40, 0, 0), "5.6");
  TEST_EQUAL(input.GetReflectedValue(40, 0, 1), "51.6");
  TEST_EQUAL(input.GetReflectedValue(40, 1, 0), "31.7");
  TEST_EQUAL(input.GetReflectedValue(40, 1, 1), "18.1");
  TEST_EQUAL(input.GetReflectedValue(40, 2, 0), "3.5");
  TEST_EQUAL(input.GetReflectedValue(40, 2, 1), "6.1");
  TEST_EQUAL(input.GetReflectedValue(40, 3, 0), "7.5");
  TEST_EQUAL(input.GetReflectedValue(40, 3, 1), "62.1");

  TEST_EQUAL(input.test59[0], Vector4());
  TEST_EQUAL(input.test59[1], Vector4());
  input.SetReflectedValue("test59",
                          "{[5.6, 51.6, 31.7, 18.1], [3.5, 6.1, 7.5, 62.1]}");
  TEST_EQUAL(input.test59[0], Vector4(5.6f, 51.6f, 31.7f, 18.1f));
  TEST_EQUAL(input.test59[1], Vector4(3.5f, 6.1f, 7.5f, 62.1f));
  cPair = input.GetReflectedPair(41);
  TEST_EQUAL(cPair.name, "test59");
  TEST_EQUAL(cPair.value, "{[5.6, 51.6, 31.7, 18.1], [3.5, 6.1, 7.5, 62.1]}");
  TEST_EQUAL(input.GetReflectedValue(41, 0), "[5.6, 51.6, 31.7, 18.1]");
  TEST_EQUAL(input.GetReflectedValue(41, 1), "[3.5, 6.1, 7.5, 62.1]");

  TEST_EQUAL(input.test60[0], Vector4A16());
  TEST_EQUAL(input.test60[1], Vector4A16());
  TEST_EQUAL(input.test60[2], Vector4A16());
  TEST_EQUAL(input.test60[3], Vector4A16());
  input.SetReflectedValue("test60",
                          "{[5.6, 51.6, 31.7, 18.1], [3.5, 6.1, 7.5, 62.1], "
                          "[1.8, 57.5, 36.9, 5.78], [7.41, 5.8, 41.8, 6.12]}");
  TEST_EQUAL(input.test60[0], Vector4A16(5.6f, 51.6f, 31.7f, 18.1f));
  TEST_EQUAL(input.test60[1], Vector4A16(3.5f, 6.1f, 7.5f, 62.1f));
  TEST_EQUAL(input.test60[2], Vector4A16(1.8f, 57.5f, 36.9f, 5.78f));
  TEST_EQUAL(input.test60[3], Vector4A16(7.41f, 5.8f, 41.8f, 6.12f));
  cPair = input.GetReflectedPair(42);
  TEST_EQUAL(cPair.name, "test60");
  TEST_EQUAL(cPair.value, "{[5.6, 51.6, 31.7, 18.1], [3.5, 6.1, 7.5, 62.1], "
                          "[1.8, 57.5, 36.9, 5.78], [7.41, 5.8, 41.8, 6.12]}");
  TEST_EQUAL(input.GetReflectedValue(42, 0), "[5.6, 51.6, 31.7, 18.1]");
  TEST_EQUAL(input.GetReflectedValue(42, 1), "[3.5, 6.1, 7.5, 62.1]");
  TEST_EQUAL(input.GetReflectedValue(42, 2), "[1.8, 57.5, 36.9, 5.78]");
  TEST_EQUAL(input.GetReflectedValue(42, 3), "[7.41, 5.8, 41.8, 6.12]");
  TEST_EQUAL(input.GetReflectedValue(42, 0, 0), "5.6");
  TEST_EQUAL(input.GetReflectedValue(42, 0, 1), "51.6");
  TEST_EQUAL(input.GetReflectedValue(42, 0, 2), "31.7");
  TEST_EQUAL(input.GetReflectedValue(42, 0, 3), "18.1");
  TEST_EQUAL(input.GetReflectedValue(42, 1, 0), "3.5");
  TEST_EQUAL(input.GetReflectedValue(42, 1, 1), "6.1");
  TEST_EQUAL(input.GetReflectedValue(42, 1, 2), "7.5");
  TEST_EQUAL(input.GetReflectedValue(42, 1, 3), "62.1");
  TEST_EQUAL(input.GetReflectedValue(42, 2, 0), "1.8");
  TEST_EQUAL(input.GetReflectedValue(42, 2, 1), "57.5");
  TEST_EQUAL(input.GetReflectedValue(42, 2, 2), "36.9");
  TEST_EQUAL(input.GetReflectedValue(42, 2, 3), "5.78");
  TEST_EQUAL(input.GetReflectedValue(42, 3, 0), "7.41");
  TEST_EQUAL(input.GetReflectedValue(42, 3, 1), "5.8");
  TEST_EQUAL(input.GetReflectedValue(42, 3, 2), "41.8");
  TEST_EQUAL(input.GetReflectedValue(42, 3, 3), "6.12");

  return 0;
}

int test_reflector_array_subclass(reflClass &input) {
  Reflector::KVPair cPair = input.GetReflectedPair(43);
  TEST_EQUAL(cPair.name, "test61");
  TEST_EQUAL(cPair.value, "{SUBCLASS_TYPE, SUBCLASS_TYPE}");
  TEST_CHECK(input.IsReflectedSubClass("test61"));
  TEST_CHECK(input.IsArray("test61"));

  auto rClass = input.GetReflectedSubClass("test61");
  ReflectorPureWrap sClass(rClass);
  subrefl &lClass = input.test61[0];

  TEST_EQUAL(lClass.data0, 0);
  TEST_EQUAL(sClass.SetReflectedValue("data0", "-1451"),
             Reflector::ErrorType::None);
  TEST_EQUAL(lClass.data0, -1451);
  cPair = sClass.GetReflectedPair(0);
  TEST_EQUAL(cPair.name, "data0");
  TEST_EQUAL(cPair.value, "-1451");

  TEST_EQUAL(lClass.data1, 0);
  TEST_EQUAL(sClass.SetReflectedValue("data1", "81.65"),
             Reflector::ErrorType::None);
  TEST_EQUAL(lClass.data1, 81.65f);
  cPair = sClass.GetReflectedPair(1);
  TEST_EQUAL(cPair.name, "data1");
  TEST_EQUAL(cPair.value, "81.65");

  auto rClass2 = input.GetReflectedSubClass("test61", 1);
  ReflectorPureWrap sClass2(rClass2);
  subrefl &lClass2 = input.test61[1];

  TEST_EQUAL(lClass2.data0, 0);
  TEST_EQUAL(sClass2.SetReflectedValue("data0", "9841"),
             Reflector::ErrorType::None);
  TEST_EQUAL(lClass2.data0, 9841);
  cPair = sClass2.GetReflectedPair(0);
  TEST_EQUAL(cPair.name, "data0");
  TEST_EQUAL(cPair.value, "9841");

  TEST_EQUAL(lClass2.data1, 0);
  TEST_EQUAL(sClass2.SetReflectedValue("data1", "5.874"),
             Reflector::ErrorType::None);
  TEST_EQUAL(lClass2.data1, 5.874f);
  cPair = sClass2.GetReflectedPair(1);
  TEST_EQUAL(cPair.name, "data1");
  TEST_EQUAL(cPair.value, "5.874");

  return 0;
}

int test_reflector_string(reflClass &input) {
  TEST_CHECK(input.test80.empty());
  TEST_EQUAL(input.SetReflectedValue("test80", "This is a test string"),
             Reflector::ErrorType::None);
  TEST_EQUAL(input.test80, "This is a test string");
  Reflector::KVPair cPair = input.GetReflectedPair(44);
  TEST_EQUAL(cPair.name, "test80");
  TEST_EQUAL(cPair.value, "This is a test string");

  return 0;
}

int test_reflector_bitfield(reflClass &input) {
  Reflector::KVPair cPair = input.GetReflectedPair(45);
  TEST_EQUAL(cPair.name, "test23");
  TEST_EQUAL(cPair.value, "SUBCLASS_TYPE");
  TEST_CHECK(input.IsReflectedSubClass(45));

  auto rClass = input.GetReflectedSubClass("test23");
  ReflectorPureWrap sClass(rClass);
  auto &lClass = input.test23;

  TEST_EQUAL(lClass.Get<member0>(), 0);
  TEST_EQUAL(sClass.SetReflectedValue("member0", "2"),
             Reflector::ErrorType::None);
  TEST_EQUAL(lClass.Get<member0>(), 2);
  cPair = sClass.GetReflectedPair(0);
  TEST_EQUAL(cPair.name, "member0");
  TEST_EQUAL(cPair.value, "2");

  TEST_EQUAL(sClass.SetReflectedValue("member0", "4"),
             Reflector::ErrorType::OutOfRange);
  TEST_EQUAL(lClass.Get<member0>(), 3);
  cPair = sClass.GetReflectedPair(0);
  TEST_EQUAL(cPair.name, "member0");
  TEST_EQUAL(cPair.value, "3");

  TEST_EQUAL(sClass.SetReflectedValue("member0", "1"),
             Reflector::ErrorType::None);
  TEST_EQUAL(lClass.Get<member0>(), 1);

  TEST_EQUAL(lClass.Get<member1>(), 0);
  TEST_EQUAL(sClass.SetReflectedValue("member1", "25"),
             Reflector::ErrorType::None);
  TEST_EQUAL(lClass.Get<member1>(), 25);
  cPair = sClass.GetReflectedPair(1);
  TEST_EQUAL(cPair.name, "member1");
  TEST_EQUAL(cPair.value, "25");

  return 0;
}

struct ReflectedInstanceFriend : ReflectedInstance {
  void *Instance() { return instance; }
  const void *Instance() const { return constInstance; }
  const reflectorStatic *Refl() const { return rfStatic; }
};

int test_reflector(reflClass &input) {
  TEST_CHECK(input.UseNames());
  TEST_EQUAL(input.GetClassName(), es::string_view("reflClass"));
  TEST_EQUAL(input.SetReflectedValue("pest", ""),
             Reflector::ErrorType::InvalidDestination);
  TEST_CHECK(input.GetReflectedValue(200).empty());
  TEST_EQUAL(input.SetReflectedValueFloat("non existant", 0.0),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.SetReflectedValueInt("non existant", 0),
             Reflector::ErrorType::InvalidDestination);
  TEST_EQUAL(input.SetReflectedValueUInt("non existant", 0),
             Reflector::ErrorType::InvalidDestination);
  auto noClass = input.GetReflectedSubClass(0);
  auto &&ncls = static_cast<ReflectedInstanceFriend &&>(noClass);

  TEST_NOT_CHECK(ncls.Instance());
  TEST_NOT_CHECK(ncls.Refl());

  auto noPair = input.GetReflectedPair(200);

  TEST_CHECK(noPair.name.empty());
  TEST_CHECK(noPair.value.empty());

  TEST_NOT_CHECK(input.IsReflectedSubClass(0));
  TEST_NOT_CHECK(input.IsReflectedSubClass("non existant"));
  TEST_NOT_CHECK(input.IsArray(0));
  TEST_NOT_CHECK(input.IsArray("non existant"));

  return 0;
}

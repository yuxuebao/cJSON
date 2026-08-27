/*
  cJSON_Int extension verification test
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include "unity/examples/unity_config.h"
#include "unity/src/unity.h"
#include "common.h"
#include "../cJSON.h"

static void int_ext_should_create_int(void)
{
    cJSON *item = cJSON_CreateInt(9223372036854775807LL);
    TEST_ASSERT_NOT_NULL(item);
    TEST_ASSERT_TRUE(cJSON_IsInt(item));
    /* cJSON_IsNumber() returns true for cJSON_Int as well (Int is a subset of Number) */
    TEST_ASSERT_TRUE(cJSON_IsNumber(item));
    TEST_ASSERT_EQUAL_INT64(9223372036854775807LL, cJSON_GetIntValue(item));
    TEST_ASSERT_EQUAL_DOUBLE((double)9223372036854775807LL, item->valuedouble);
    cJSON_Delete(item);
}

static void int_ext_should_add_int_to_object(void)
{
    cJSON *root = cJSON_CreateObject();
    cJSON *item = NULL;
    TEST_ASSERT_NOT_NULL(root);

    item = cJSON_AddIntToObject(root, "big", -9223372036854775807LL - 1);
    TEST_ASSERT_NOT_NULL(item);
    TEST_ASSERT_TRUE(cJSON_IsInt(item));
    TEST_ASSERT_EQUAL_INT64(LLONG_MIN, cJSON_GetIntValue(item));

    cJSON_Delete(root);
}

static void int_ext_should_parse_int(void)
{
    cJSON *item = cJSON_Parse("{\"big\":9223372036854775807}");
    TEST_ASSERT_NOT_NULL(item);
    TEST_ASSERT_TRUE(cJSON_IsInt(cJSON_GetObjectItemCaseSensitive(item, "big")));
    TEST_ASSERT_EQUAL_INT64(9223372036854775807LL,
                            cJSON_GetIntValue(cJSON_GetObjectItemCaseSensitive(item, "big")));
    cJSON_Delete(item);
}

static void int_ext_should_parse_number_as_number(void)
{
    cJSON *item = cJSON_Parse("[1.5, 1e10, 1]");
    TEST_ASSERT_NOT_NULL(item);
    TEST_ASSERT_TRUE(cJSON_IsNumber(cJSON_GetArrayItem(item, 0)));
    TEST_ASSERT_TRUE(cJSON_IsNumber(cJSON_GetArrayItem(item, 1)));
    TEST_ASSERT_TRUE(cJSON_IsInt(cJSON_GetArrayItem(item, 2)));
    cJSON_Delete(item);
}

static void int_ext_should_print_int_exactly(void)
{
    cJSON *item = cJSON_CreateObject();
    char *printed = NULL;
    TEST_ASSERT_NOT_NULL(item);

    cJSON_AddIntToObject(item, "max", 9223372036854775807LL);
    cJSON_AddIntToObject(item, "min", LLONG_MIN);
    printed = cJSON_Print(item);
    TEST_ASSERT_NOT_NULL(printed);
    TEST_ASSERT_EQUAL_STRING("{\n\t\"max\":\t9223372036854775807,\n\t\"min\":\t-9223372036854775808\n}", printed);
    free(printed);
    cJSON_Delete(item);
}

static void int_ext_should_compare_int_and_number(void)
{
    cJSON *i = cJSON_CreateInt(10);
    cJSON *n = cJSON_CreateNumber(10);
    TEST_ASSERT_TRUE(cJSON_Compare(i, n, 1));
    cJSON_SetNumberValue(n, 20);
    TEST_ASSERT_FALSE(cJSON_Compare(i, n, 1));
    cJSON_Delete(i);
    cJSON_Delete(n);
}

static void int_ext_should_parse_bool_as_bool(void)
{
    cJSON *item = cJSON_Parse("[true, false]");
    TEST_ASSERT_NOT_NULL(item);
    TEST_ASSERT_TRUE(cJSON_IsBool(cJSON_GetArrayItem(item, 0)));
    TEST_ASSERT_TRUE(cJSON_IsTrue(cJSON_GetArrayItem(item, 0)));
    TEST_ASSERT_TRUE(cJSON_IsBool(cJSON_GetArrayItem(item, 1)));
    TEST_ASSERT_TRUE(cJSON_IsFalse(cJSON_GetArrayItem(item, 1)));
    cJSON_Delete(item);
}

int CJSON_CDECL main(void)
{
    UNITY_BEGIN();
    RUN_TEST(int_ext_should_create_int);
    RUN_TEST(int_ext_should_add_int_to_object);
    RUN_TEST(int_ext_should_parse_int);
    RUN_TEST(int_ext_should_parse_number_as_number);
    RUN_TEST(int_ext_should_print_int_exactly);
    RUN_TEST(int_ext_should_compare_int_and_number);
    RUN_TEST(int_ext_should_parse_bool_as_bool);
    return UNITY_END();
}

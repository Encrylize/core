/*
 *	MetaCall Library by Parra Studios
 *	A library for providing a foreign function interface calls.
 *
 *	Copyright (C) 2016 - 2021 Vicente Eduardo Ferrer Garcia <vic798@gmail.com>
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *	See the License for the specific language governing permissions and
 *	limitations under the License.
 *
 */

#include <gmock/gmock.h>

#include <metacall/metacall.h>
#include <metacall/metacall_value.h>
#include <metacall/metacall_loaders.h>

class metacall_rpc_test : public testing::Test
{
public:
};

TEST_F(metacall_rpc_test, DefaultConstructor)
{
	metacall_print_info();

	ASSERT_EQ((int) 0, (int) metacall_initialize());

	/* RPC */
	#if defined(OPTION_BUILD_LOADERS_RPC)
	{
		const char * rpc_scripts[] =
		{
			"remote.url"
		};

		EXPECT_EQ((int) 0, (int) metacall_load_from_file("rpc", rpc_scripts, sizeof(rpc_scripts) / sizeof(rpc_scripts[0]), NULL));

		/*
		const enum metacall_value_id hello_boy_double_ids[] =
		{
			METACALL_DOUBLE, METACALL_DOUBLE
		};

		void * ret = metacallt("hello_boy", hello_boy_double_ids, 3.0, 4.0);

		EXPECT_NE((void *) NULL, (void *) ret);

		EXPECT_EQ((double) metacall_value_to_double(ret), (double) 7.0);

		metacall_value_destroy(ret);
		*/
	}
	#endif /* OPTION_BUILD_LOADERS_RPC */

	/* Print inspect information */
	{
		size_t size = 0;

		struct metacall_allocator_std_type std_ctx = { &std::malloc, &std::realloc, &std::free };

		void * allocator = metacall_allocator_create(METACALL_ALLOCATOR_STD, (void *)&std_ctx);

		char * inspect_str = metacall_inspect(&size, allocator);

		EXPECT_NE((char *) NULL, (char *) inspect_str);

		EXPECT_GT((size_t) size, (size_t) 0);

		std::cout << inspect_str << std::endl;

		metacall_allocator_free(allocator, inspect_str);

		metacall_allocator_destroy(allocator);
	}

	EXPECT_EQ((int) 0, (int) metacall_destroy());
}

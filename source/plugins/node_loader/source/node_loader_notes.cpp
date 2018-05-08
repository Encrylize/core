#if 0

/* Catch exception in C/C++ */
/*
		if (status != napi_ok)
		{
			const napi_extended_error_info * error_info;

			napi_value ex, prop_list;

			uint32_t length;

			status = napi_get_last_error_info(env, &error_info);

			assert(status == napi_ok);

			printf("%s: %d, %d\n", error_info->error_message, error_info->engine_error_code, error_info->error_code);

			napi_get_and_clear_last_exception(env, &ex);

			status = napi_get_property_names(env, ex, &prop_list);

			assert(status == napi_ok);

			status = napi_get_array_length(env, prop_list, &length);

			assert(status == napi_ok);

			for (size_t index = 0; index < length; ++index)
			{
				napi_value result;

				const size_t buf_size = 255;

				char buf[buf_size];

				size_t buf_read = 0;

				status = napi_get_element(env, prop_list, index, &result);

				assert(status == napi_ok);

				status = napi_get_value_string_utf8(env, result, buf, buf_size, &buf_read);

				assert(status == napi_ok);

				printf("DEBUG: %s\n", buf);

				napi_value ex_code;

				status = napi_get_named_property(env, ex, "code", &ex_code);

				assert(status == napi_ok);

				status = napi_get_value_string_utf8(env, ex_code, buf, buf_size, &buf_read);

				assert(status == napi_ok);

				printf("DEBUG: %s\n", buf);
			}
		}
*/


 /* Warning: This should be updated because is not present in any header and it's hardcoded */
#ifndef NODE_CONTEXT_EMBEDDER_DATA_INDEX
#	define NODE_CONTEXT_EMBEDDER_DATA_INDEX 32
#endif /* NODE_CONTEXT_EMBEDDER_DATA_INDEX */

inline node::Environment * node_loader_environment_current(v8::Local<v8::Context> context)
{
	return static_cast<node::Environment *>(context->GetAlignedPointerFromEmbedderData(NODE_CONTEXT_EMBEDDER_DATA_INDEX));
}

/*node_impl->thread_loop = node::GetCurrentEventLoop(v8::Isolate::GetCurrent());*/

/*void Print(const v8::FunctionCallbackInfo<v8::Value>& args) {
	bool first = true;
	for (int i = 0; i < args.Length(); i++)
	{
		v8::HandleScope handle_scope(args.GetIsolate());
		if (first)
		{
			first = false;
		}
		else
		{
			printf(" ");
		}
		v8::String::Utf8Value str(args.GetIsolate(), args[i]);
		const char* cstr = *str;

		if (cstr)
			printf("%s", cstr);
	}
	printf("\n");
	fflush(stdout);
}*/

void node_loader_trampoline_initialize()
{
	v8::Isolate * isolate = v8::Isolate::GetCurrent();

	v8::HandleScope handle_scope(isolate);

	v8::Local<v8::Context> context(isolate->GetCurrentContext());

	v8::Context::Scope context_scope(context);

	v8::Local<v8::Object> global(context->Global());

	/*
	node::Environment * env = node_loader_environment_current(context);

	printf("POINTER: %p\n", (void *)env);
	*/

	/* DEBUG GLOBAL
	v8::Local<v8::String> global_str = v8::String::NewFromUtf8(isolate,
		"global", v8::NewStringType::kNormal).ToLocalChecked();

	v8::Local<v8::Object> global_impl = v8::Local<v8::Object>::Cast(global->Get(global_str));

	v8::Local<v8::Array> global_array = global_impl->GetOwnPropertyNames(context).ToLocalChecked();
	//v8::Local<v8::Array> global_array = global_impl->GetPropertyNames(context).ToLocalChecked();

	unsigned int length = global_array->Length();

	printf("------------------------------------------------\n");

	for (unsigned int i = 0; i < length; ++i)
	{
		v8::Local<v8::Value> element = global_array->Get(i);

		v8::String::Utf8Value utf8_value(element);

		printf("%s!!\n------------------\n", *utf8_value);
	}

	printf("------------------------------------------------\n");
	*/

	/* ENVIRONMENT
	v8::Isolate * isolate = v8::Isolate::GetCurrent();

	v8::HandleScope handle_scope(isolate);

	v8::Local<v8::Context> context(isolate->GetCurrentContext());

	node::IsolateData * isolate_data = node::CreateIsolateData(isolate, node_impl->thread_loop);

	char * argv[] = { "node_loader", NULL };

	int argc = 1;

	node::Environment * env = node::CreateEnvironment(isolate_data, context, argc, argv, argc, argv);

	node::LoadEnvironment(env);
	*/

	/* INSERT IN GLOBAL

	v8::Local<v8::String> node_loader_register_str = v8::String::NewFromUtf8(isolate,
		"node_loader_register", v8::NewStringType::kNormal).ToLocalChecked();

	global->Set(context, node_loader_register_str, v8::String::NewFromUtf8(isolate,
		"hello world", v8::NewStringType::kNormal).ToLocalChecked());
	*/

	/* DEBUG REQUIRE

	v8::Local<v8::String> global_str = v8::String::NewFromUtf8(isolate,
		"global", v8::NewStringType::kNormal).ToLocalChecked();

	v8::Local<v8::Value> global_impl;
	
	if (global->Get(context, global_str).ToLocal(&global_impl))
	{
		v8::Local<v8::Object> global_impl_obj = v8::Local<v8::Object>::Cast(global_impl);

		v8::Local<v8::String> require_str = v8::String::NewFromUtf8(isolate,
			"require", v8::NewStringType::kNormal).ToLocalChecked();

		v8::Local<v8::Value> require_impl;
	
		if (global_impl_obj->Get(context, require_str).ToLocal(&require_impl))
		{
			v8::Local<v8::Object> process_impl_obj = v8::Local<v8::Object>::Cast(require_impl);

			v8::String::Utf8Value utf8_value(process_impl_obj);

			printf("%s\n", *utf8_value);
		}
	}

	printf("_________________________________________________________\n");
	*/

	/* ENVIRONMENT FREE

	node::FreeEnvironment(env);

	node::FreeIsolateData(isolate_data);
	*/


	/* DEBUG PROCESS

	v8::Local<v8::String> global_str = v8::String::NewFromUtf8(isolate,
		"global", v8::NewStringType::kNormal).ToLocalChecked();

	v8::Local<v8::Value> global_impl;
	
	if (global->Get(context, global_str).ToLocal(&global_impl))
	{
		v8::Local<v8::Object> global_impl_obj = v8::Local<v8::Object>::Cast(global_impl);

		v8::Local<v8::String> process_str = v8::String::NewFromUtf8(isolate,
			"process", v8::NewStringType::kNormal).ToLocalChecked();

		v8::Local<v8::Value> process_impl;
	
		if (global_impl_obj->Get(context, process_str).ToLocal(&process_impl))
		{
			v8::Local<v8::Object> process_impl_obj = v8::Local<v8::Object>::Cast(process_impl);

			v8::Local<v8::Array> module_list_prop_array = process_impl_obj->GetOwnPropertyNames(context).ToLocalChecked();

			unsigned int length = module_list_prop_array->Length();

			printf("-----------------------\n");				

			for (unsigned int i = 0; i < length; ++i)
			{
				v8::Local<v8::Value> element = module_list_prop_array->Get(i);

				v8::Local<v8::Value> element_val;

				if (process_impl_obj->Get(context, element).ToLocal(&element_val))
				{
					v8::String::Utf8Value utf8_value(element_val);

					printf("%s\n", *utf8_value);
				}
			}

			printf("-----------------------\n");
		}
	}
	*/

	/* DEBUG MODULES LIST

	v8::Local<v8::String> global_str = v8::String::NewFromUtf8(isolate,
		"global", v8::NewStringType::kNormal).ToLocalChecked();

	v8::Local<v8::Value> global_impl;
	
	if (global->Get(context, global_str).ToLocal(&global_impl))
	{
		v8::Local<v8::Object> global_impl_obj = v8::Local<v8::Object>::Cast(global_impl);

		v8::Local<v8::String> process_str = v8::String::NewFromUtf8(isolate,
			"process", v8::NewStringType::kNormal).ToLocalChecked();

		v8::Local<v8::Value> process_impl;
	
		if (global_impl_obj->Get(context, process_str).ToLocal(&process_impl))
		{
			v8::Local<v8::Object> process_impl_obj = v8::Local<v8::Object>::Cast(process_impl);

			v8::Local<v8::String> module_list_str = v8::String::NewFromUtf8(isolate,
				"moduleLoadList", v8::NewStringType::kNormal).ToLocalChecked();

			v8::Local<v8::Value> module_list_impl;
		
			if (process_impl_obj->Get(context, module_list_str).ToLocal(&module_list_impl))
			{
				v8::Local<v8::Object> module_list_impl_obj = v8::Local<v8::Object>::Cast(module_list_impl);

				v8::Local<v8::Array> module_list_prop_array = module_list_impl_obj->GetOwnPropertyNames(context).ToLocalChecked();

				unsigned int length = module_list_prop_array->Length();

				printf("-----------------------\n");				

				for (unsigned int i = 0; i < length; ++i)
				{
					v8::Local<v8::Value> element = module_list_prop_array->Get(i);

					v8::Local<v8::Value> element_val;

					if (module_list_impl_obj->Get(context, element).ToLocal(&element_val))
					{
						v8::String::Utf8Value utf8_value(element_val);

						printf("%s\n", *utf8_value);
					}
				}

				printf("-----------------------\n");
			}
		}
	}*/

	/* TEST

	v8::Local<v8::Array> prop_array = global->GetOwnPropertyNames(context).ToLocalChecked();

	unsigned int length = prop_array->Length();

	for (unsigned int i = 0; i < length; ++i)
	{
		v8::Local<v8::Value> element = prop_array->Get(i);

		v8::Local<v8::Value> func_val;

		if (context->Global()->Get(context, element).ToLocal(&func_val)*//* &&
			func_val->IsFunction()*//*)
		{
			if (func_val->IsObject())
			{
				v8::Local<v8::Object> obj_val = v8::Local<v8::Object>::Cast(func_val);

				v8::Local<v8::Array> obj_array = obj_val->GetOwnPropertyNames(context).ToLocalChecked();

				for (unsigned int j = 0; j < obj_array->Length(); ++j)
				{
					v8::Local<v8::Value> inside_element = obj_array->Get(j);

					v8::String::Utf8Value utf8_value(inside_element);

					printf("%s!!\n~~~~~~~~~~~~~~~~~~~~\n", *utf8_value);

					v8::Local<v8::Value> func_val_vul;

					if (context->Global()->Get(context, inside_element).ToLocal(&func_val_vul))
					{
						if (std::strcmp("moduleLoadList", *utf8_value) == 0) // Loco loco loco (get from id)
						{
							v8::Local<v8::Object> obj_obj_val = v8::Local<v8::Object>::Cast(func_val_vul);

							v8::Local<v8::Array> obj_obj_array = obj_obj_val->GetOwnPropertyNames(context).ToLocalChecked();

							for (unsigned int k = 0; k < obj_obj_array->Length(); ++k)
							{
								v8::Local<v8::Value> modul_ele = obj_obj_array->Get(k);

								v8::String::Utf8Value utf8_value_oo(modul_ele);

								printf("%s!!\n~~~~~~~~~~~~~~~~~~~~\n", *utf8_value_oo);
							}
						}
					}
				}
			}

			//v8::String::Utf8Value utf8_value(func_val);
			v8::String::Utf8Value utf8_value(element);

			printf("%s!!\n------------------------------------------------------\n", *utf8_value);
		}
	}*/

	/*
	v8::Local<v8::Value> value = global->Get(v8::String::NewFromUtf8(isolate,
		"hello_boy", v8::NewStringType::kNormal).ToLocalChecked());

	v8::Local<v8::Function> func = v8::Handle<v8::Function>::Cast(value);

	v8::Local<v8::Value> args[2] =
	{
		v8::String::NewFromUtf8(isolate,
			"abc", v8::NewStringType::kNormal).ToLocalChecked(),
		v8::String::NewFromUtf8(isolate,
			"efg", v8::NewStringType::kNormal).ToLocalChecked()
	};

	
	v8::Local<v8::Value> result = func->Call(global, 2, args);
	*/

	(void)node_impl;

	/*

	v8::Local<v8::String> str_value = result->ToString();

	v8::String::Utf8Value utf8_value(str_value);
	printf("HELLO BOY RESULT: %s\n", *utf8_value);
	*/

	/* TODO: Change print for register callback */
	/*
	global->Set(
		v8::String::NewFromUtf8(isolate, "print_custom", v8::NewStringType::kNormal)
		.ToLocalChecked(),
		v8::FunctionTemplate::New(isolate, Print));
	*/
}

#endif

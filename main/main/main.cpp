// main.cpp : Определяет экспортированные функции для приложения DLL.
//

//#include "stdafx.h"
#include <v8.h>
#include <v8config.h>
#include <v8-inspector.h>
#include <v8-inspector-protocol.h>
#include <v8-internal.h>
#include <v8-platform.h>
#include <v8-profiler.h>
#include <v8-testing.h>
#include <v8-util.h>
#include <v8-value-serializer-version.h>
#include <v8-version.h>
#include <v8-version-string.h>
#include <v8-wasm-trap-handler-posix.h>
#include <v8-wasm-trap-handler-win.h>
#include <libplatform\libplatform.h>
using namespace v8; 
#include <nan.h>
using namespace std;
using namespace Nan;
using namespace v8;
#include <stdint.h>
#include <vector>

using namespace v8;


NAN_METHOD(Hello) {

	Local<Array> jsArr = Local<Array>::Cast(info[0]);
	std::vector<std::vector<double>> arr = {};

	for (unsigned int i = 0; i < jsArr->Length(); i++) {
		Local<Value> element = jsArr->Get(i);
		arr.push_back({});
		if (element->IsArray()) {
			Local<Array> jsUnderArr = Local<Array>::Cast(element);

			for (unsigned int k = 0; k < jsUnderArr->Length(); k++) {
				Local<Value> jsElement = jsUnderArr->Get(k);
				auto number = jsElement->NumberValue();
				arr[i].push_back(number);
			}
		}
	}

	//j + i*n
	int i = 0, j = 0, k = 0;

	const int n = 3;//arr.size();
	// std::vector<std::vector<int>> l = {};
	// std::vector<std::vector<int>> u = {};
	float l[3][3], u[3][3];

	for (i = 0; i < n; i++) {
		// l.push_back({});
		// u.push_back({});
		for (j = 0; j < n; j++) {
			if (j < i)
				l[j][i] = 0;
			else {
				l[j][i] = arr[j][i];
				for (k = 0; k < n; k++) {
					l[j][i] = l[j][i] - l[j][k] * u[k][i];
				}
			}
		}
		for (j = 0; j < n; j++) {
			if (j < i)
				u[i][j] = 0;
			else if (j == i)
				u[i][j] = 1;
			else {
				u[i][j] = arr[i][j] / l[i][i];
				for (k = 0; k < n; k++) {
					u[i][j] = u[i][j] - ((l[i][k] * u[k][j]) / l[i][i]);
				}
			}
		}
	}


	Local<Array> resultArrUpper = New<v8::Array>();
	for (unsigned int i = 0; i < jsArr->Length(); i++) {
		Local<Array> resultUnderArr = New<v8::Array>();
		auto underArr = u[i];
		for (unsigned int k = 0; k < size(u[i]); k++) {
			Nan::Set(resultUnderArr, k, Nan::New(underArr[k]));
		}
		Nan::Set(resultArrUpper, i, resultUnderArr);
	};

	Local<Array> resultArrLower = New<v8::Array>();
	for (unsigned int i = 0; i < jsArr->Length(); i++) {
		Local<Array> resultUnderArr = New<v8::Array>();
		auto underArr = l[i];
		for (unsigned int k = 0; k < size(l[i]); k++) {

			Nan::Set(resultUnderArr, k, Nan::New(underArr[k]));
		}
		Nan::Set(resultArrLower, i, resultUnderArr);
	};

	Local<Array> resArray = New<v8::Array>();
	resArray->Set(0, resultArrLower);
	resArray->Set(1, resultArrUpper);

	info.GetReturnValue().Set(resArray);

}

// Module initialization logic
NAN_MODULE_INIT(Initialize) {
	// Export the `Hello` function (equivalent to `export function Hello (...)` in JS)
	NAN_EXPORT(target, Hello);
}

// Create the module called "addon" and initialize it with `Initialize` function (created with NAN_MODULE_INIT macro)
NODE_MODULE(addon, Initialize);
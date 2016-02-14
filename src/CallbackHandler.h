#ifndef CALLBACK_HANDLER_H
#define CALLBACK_HANDLER_H

#include <v8.h>
#include <map>
#include <string>

#include <TError.h>
#include <TClassEdit.h>

#include "ObjectProxy.h"
#include "ObjectProxyFactory.h"
#include "FunctionProxy.h"
#include "FunctionProxyFactory.h"
#include "AsyncRunner.h"

namespace rootJS
{
	class CallbackHandler
	{
		public:
			static const std::string CALLBACK_DATA_DELIMITER;

			/**
			 * 	TODO: fill in description
			 *
			 *	@param name
			 *
			 *
			 *	@param proxy
			 *
			 *
			 */
			static void registerGlobalObject(const std::string &name, ObjectProxy* proxy);

			/**
			 * 	TODO: fill in description
			 *
			 *	@param property
			 *
			 *
			 *	@param info
			 *
			 *
			 */
			static void globalGetterCallback(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);

			/**
			 * 	TODO: fill in description
			 *
			 *	@param property
			 *
			 *
			 *	@param value
			 *
			 *
			 *	@param info
			 *
			 *
			 */
			static void globalSetterCallback(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);


			/**
			 * TODO: fill in description
			 *
			 * @param  info
			 *
			 *
			 */
			static void globalFunctionCallback(const v8::FunctionCallbackInfo<v8::Value>& info);

			/**
			 * 	TODO: fill in description
			 *
			 *	@param name
			 *
			 *
			 *	@param proxy
			 *
			 *
			 */
			static v8::Local<v8::Value> registerStaticObject(const std::string &name, TClass *scope, ObjectProxy* proxy);


			/**
			 * 	TODO: fill in description
			 *
			 *	@param property
			 *
			 *
			 *	@param info
			 *
			 *
			 */
			static void staticGetterCallback(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);

			/**
			 * 	TODO: fill in description
			 *
			 *	@param property
			 *
			 *
			 *	@param value
			 *
			 *
			 *	@param info
			 *
			 *
			 */
			static void staticSetterCallback(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);

			/**
			 * 	TODO: fill in description
			 *
			 *	@param info
			 *
			 *
			 */
			static void staticFunctionCallback(const v8::FunctionCallbackInfo<v8::Value>& info);

			/**
			 * 	This callback method may be invoked whenever a JavaScript prototype function of an encapsulated ROOT class was called.
			 *
			 * 	Based on the supplied arguments the suitable C++ constructor will be called.
			 * 	Then the newly created instance will be wrapped into an ObjectProxy.
			 * 	As result the ObjectProxy's corresponding JavaScript object will be returned to the Node.js application.
			 *
			 * 	In order to enable non blocking object creation one can supply a JavaScript callback function as last argument of the prototype function.
			 * 	After the asynchronous object creation is finished the supplied callback will be invoked for returning the generated JavasSript proxy.
			 *
			 *	@param info
			 *			the argument information given to this function call callback
			 *
			 */
			static void ctorCallback(const v8::FunctionCallbackInfo<v8::Value>& info);

			/**
			 * 	TODO: fill in description
			 *
			 *	@param property
			 *
			 *
			 *	@param info
			 *
			 *
			 */
			static void memberGetterCallback(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);

			/**
			 * 	TODO: fill in description
			 *
			 *	@param property
			 *
			 *
			 *	@param value
			 *
			 *
			 *	@param info
			 *
			 *
			 */
			static void memberSetterCallback(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);

			/**
			 * TODO: fill in description
			 *
			 * @param  info
			 *
			 *
			 */
			static void memberFunctionCallback(const v8::FunctionCallbackInfo<v8::Value>& info);

			/**
			 * Encapsulate the callback data for a function.
			 *
			 * @param fucntionName
			 *			the function name
			 *
			 * @param scope
			 *			the scope which contains the function named as specified
			 *
			 * @return the encapsulated data for usage in callbacks
			 *
			 */
			static v8::Local<v8::Value> createFunctionCallbackData(std::string functionName, TClass *scope);

			/**
			 * Encapsulate the callback data for a constructor function.
			 *
			 * @param scope
			 *			the scope which contains the function named as specified
			 *
			 * @return the encapsulated data for usage in callbacks
			 *
			 */
			static v8::Local<v8::Value> createFunctionCallbackData(TClass *scope);

		private:
			struct AsyncCallParam {
				v8::Persistent<v8::Array, v8::CopyablePersistentTraits<v8::Array>> params;
				FunctionProxy* proxy;
				void* selfAddress;
			};

			static std::map<std::string, ObjectProxy*> globalObjectMap;
			static std::map<std::string, ObjectProxy*> staticObjectMap;

			static v8::Local<v8::Array> getInfoArgs(v8::Local<v8::Function> *callback, v8::FunctionCallbackInfo<v8::Value> const& info);

			static TClass* resolveCallbackScope(v8::Local<v8::Value> data, bool allowNull) throw(std::invalid_argument);
			static std::string resolveCallbackName(v8::Local<v8::Value> data) throw(std::invalid_argument);

			static std::string toString(v8::Local<v8::Value> data) throw(std::invalid_argument);

			static void asyncMemberCall(AsyncRunner *runner, void *param);
	};
}

#endif

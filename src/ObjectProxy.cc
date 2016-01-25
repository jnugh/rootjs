#include "ObjectProxy.h"

#include <TObject.h>
#include <TGlobal.h>

namespace RootJS {

ObjectProxy::ObjectProxy(TDataMember &type, TClassRef scope)
    : Proxy(nullptr, type, scope) {
  currentmode = MemberMode(type);
}

ObjectProxy::ObjectProxy(TGlobal &type, TClassRef scope)
    : Proxy(nullptr, type, scope) {
  this->currentmode = GlobalMode(type);
}

ObjectProxy::~ObjectProxy() {}

const ProxyObject &ObjectProxy::getType() {
  return dynamic_cast<const TDataMember &>(type);
}

char *const ObjectProxy::getTypeName() {
  // TODO implement (if this is even necessary)
  return nullptr;
}

Long_t ObjectProxy::getOffset() { return currentmode.getOffset(); }

void ObjectProxy::set(ObjectProxy &value) {
  // TODO: validate type equality
  address = value.getAddress();
}

v8::Local<v8::Value> ObjectProxy::get() {
  // objects just return their holder - i.e the proxy member
  return getProxy();
}

void ObjectProxy::setProxy(v8::Local<v8::Object> proxy) {
  this->proxy.Reset(v8::Isolate::GetCurrent(), proxy);
}

v8::Local<v8::Object> ObjectProxy::getProxy() {
  return v8::Local<v8::Object>::New(v8::Isolate::GetCurrent(), proxy);
}

bool ObjectProxy::isPrimitive() { return false; }

bool ObjectProxy::isTemplate() {
  return false; // TODO
}

bool ObjectProxy::isGlobal() { return currentmode.isGlobal(); }

bool ObjectProxy::isConst() {
  return false; // TODO
}

bool ObjectProxy::isStatic() {
  return false; // TODO
}
}

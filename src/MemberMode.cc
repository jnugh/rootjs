#include "MemberMode.h"
namespace RootJS {

MemberMode::MemberMode(const TDataMember& type) : ProxyMode(type)  {
currentObject = &type;
}
MemberMode::~MemberMode(){
}
bool MemberMode::isGlobal() {
	return false;
}
Long_t MemberMode::GetOffset() {
	return currentObject->GetOffset();
}
}

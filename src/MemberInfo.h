#ifndef SRC_MEMBERINFO_H_
#define SRC_MEMBERINFO_H_

#include <v8.h>
#include <TDataMember.h>
#include <TClassRef.h>
#include <TGlobal.h>
#include "MetaInfo.h"

namespace rootJS {

	class MemberInfo : public MetaInfo {
		public:
			MemberInfo(const TDataMember &, void* baseAddress);
			~MemberInfo();

			virtual bool isGlobal();
			virtual Long_t getOffset();

			virtual bool isConst();
			virtual bool isStatic();
			virtual const char* getTypeName();

			const TDataMember &currentObject;
			virtual MetaInfo* clone() {
				return new MemberInfo(currentObject, baseAddress);
			};
		protected:
	};
}
#endif
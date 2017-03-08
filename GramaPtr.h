#pragma once
#ifndef _GRAMA_H_
#define _GRAMA_H_

#include <memory>

namespace Grama {
	template <typename T>
	class GPtr {
	private:
		class RefCountedObject {
			friend class GPtr<T>;
			int refCount;
			T * objectPtr;
			RefCountedObject(T * objPtr) :objectPtr(objPtr), refCount(1) {}
			~RefCountedObject() { delete object; }
		};

		RefCountedObject * refCountedObject;
		//other value-type
	public:
		GPtr(T * objPtr = nullptr) :refCountedObject(new RefCountedObject(objPtr)) {}
		GPtr(const GPtr & rhs) :refCountedObject(rhs.refCountedObject) { refCountedObject->refCount++; }
		GPtr & operator=(const GPtr & rhs) {
			rhs.refCountedObject->refCount++;
			if (--refCountedObject->refCount) {
				delete refCountedObject;
			}
			refCountedObject = rhs.refCountedObject;
			return *this;
		}
		~GPtr() {
			if (--refCountedObject->refCount == 0)
				delete refCountedObject;
		}
	};
};

#endif // !_GRAMA_H_

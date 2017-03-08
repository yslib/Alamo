
#ifndef _ALAMO_PTR_H_
#define _ALAMO_PTR_H_

#include "Alamo.h"

//
//a simple smart pointer for object management
//
namespace Alamo
{

	//class alaPtr
	template <typename T>
	class alaPtr
	{
	public:
		alaPtr() {};
		alaPtr(T * objectPointer = NULL);
		alaPtr(const alaPtr & sourceObject);
		~alaPtr();

		alaPtr & operator=(const alaPtr & rhs);

		const T * operator->()const;
		T * operator->();
		const T & operator*()const;
		T & operator*();

		bool operator!()const;

		bool operator==(const alaPtr & rhs)const;
		bool operator!=(const alaPtr & rhs)const;
	private:
		struct RefCountedObject
		{
			//
			RefCountedObject() { Init(); }
			RefCountedObject(const RefCountedObject & sourceObject);
			~RefCountedObject()
			{
				if (dataPointer != NULL)
					delete dataPointer;
			}
			RefCountedObject & operator=(const RefCountedObject & sourceObject);

			void Init() { refCount = 0; shareable = true; }

			void Inc_Reference() { refCount++; }
			void Dec_Reference() {
				refCount--;
				if (refCount == 0)
					delete this;			//never seen before
			}
			void Make_Unshareable() { shareable = false; }
			bool Is_Shareable()const { return shareable; }
			bool Is_Shared()const { return (refCount > 1); }

			//Data

			T *dataPointer;
			bool shareable;
			int refCount;
		};
	private:
		RefCountedObject * refCountedObjectPointer;

	private:

		void Init();

		void MakeCopy();


	};



	//class definition for alaPtr----------------------------------

	template<class T>
	alaPtr<T>::alaPtr(T * objectPointer /* = NULL */)
	{
		if ((refCountedObjectPointer = new RefCountedObject) == NULL)
		{
			throw alaError(ALAES_OUT_OF_MEMORY);
		}
		refCountedObjectPointer->dataPointer = objectPointer;
		Init();
	}

	template<class T>
	alaPtr<T>::alaPtr(const alaPtr & sourceObject)
	{
		Init();
	}

	template<class T>
	alaPtr<T>::~alaPtr()
	{
		if (refCountedObjectPointer != NULL)
		{
			refCountedObjectPointer->Dec_Reference();
		}
	}

	template<class T>
	alaPtr<T> & 
		alaPtr<T>::operator=(
			const alaPtr & sourceObject)
	{
		if (refCountedObjectPointer != sourceObject.refCountedObjectPointer)
		{
			if (refCountedObjectPointer)
			{
				refCountedObjectPointer->Dec_Reference();
			}
			refCountedObjectPointer = sourceObject.refCountedObjectPointer;
			Init();
		}
		return (*this);
	}
	template<class T>
	const T * alaPtr<T>::operator->()const 
	{
		return (refCountedObjectPointer->dataPointer);
	}

	template<class T>
	T * alaPtr<T>::operator->()
	{
		MakeCopy();
		return (refCountedObjectPointer->dataPointer);
	}

	template<class T>
	const T & alaPtr<T>::operator*()const
	{
		return (*(refCountedObjectPointer->dataPointer));
	}

	template<class T>
	T & alaPtr<T>::operator*()
	{
		MakeCopy();
		return (*(refCountedObjectPointer->dataPointer));
	}

	template<typename T>
	bool alaPtr<T>::operator!()const
	{
		return (refCountedObjectPointer->dataPointer == NULL);
	}

	template<class T>
	inline bool alaPtr<T>::operator==(const alaPtr & rhs) const
	{
		return refCountedObjectPointer->dataPointer == rhs.refCountedObjectPointer->dataPointer;
	}

	template<class T>
	inline bool alaPtr<T>::operator!=(const alaPtr & rhs) const
	{
		return !(*this == rhs);
	}

	template<typename T>
	void alaPtr<T>::Init()
	{
		assert(refCountedObjectPointer != NULL);

		if (refCountedObjectPointer->Is_Shareable() == false)
		{
			T * oldData = refCountedObjectPointer->dataPointer;

			if ((refCountedObjectPointer = new RefCountedObject) == NULL)		//call operator= of RefCountedObject
			{
				throw alaError(ALAES_OUT_OF_MEMORY);
			}
			if ((refCountedObjectPointer->dataPointer = new T(*oldData)) == NULL)
			{
				throw alaError(ALAES_OUT_OF_MEMORY);
			}
		}
		refCountedObjectPointer->Inc_Reference();
	}

	template<typename T>
	void alaPtr<T>::MakeCopy()
	{
		if (refCountedObjectPointer->Is_Shared())
		{
			T *oldData = refCountedObjectPointer->dataPointer;
			refCountedObjectPointer->Dec_Reference();

			if ((refCountedObjectPointer = new RefCountedObject) == NULL)
			{
				throw alaError(ALAES_OUT_OF_MEMORY);
			}
			if ((refCountedObjectPointer->dataPointer = new T(*oldData)) == NULL)
			{
				throw alaError(ALAES_OUT_OF_MEMORY);
			}
			
		}
	}

	template<typename T>
	alaPtr<T>::RefCountedObject::RefCountedObject(
		const RefCountedObject & sourceObject)
	{
		Init();
		if (sourceObject.dataPointer != NULL)
		{
			dataPointer = new T(*sourceObject.dataPointer);
			if (dataPointer == NULL)
			{
				throw alaError(ALAES_OUT_OF_MEMORY);
			}
			else
			{
				refCount++;
			}
		}
	}


	//Notice that the way to define a method outside 
	//of a class within another template class
	template<typename T>
	typename alaPtr<T>::RefCountedObject &
		alaPtr<T>::RefCountedObject::operator=(
			const RefCountedObject & sourceObject)
	{
		refCount = sourceObject.refCount;
		shareable = sourceObject.shareable;

		if (dataPointer != NULL)
		{
			delete dataPointer;
			if (sourceObject.dataPointer != NULL)
			{
				dataPointer = new T(*sourceObject.dataPointer);
				if (dataPointer == NULL)
				{
					throw alaError(ALAES_OUT_OF_MEMORY);
				}

			}
		}
		else
		{
			if (sourceObject.dataPointer != NULL)
			{
				dataPointer = new T(*sourceObject.dataPointer);
				if (dataPointer == NULL)
				{
					throw alaError(ALAES_OUT_OF_MEMORY);
				}
			}
		}
		return (*this);
	}

	//template<class T>
	//void alaPtr<T>::RefCountedObject::Make_Unshareable()
	//{
	//	shareable = false;
	//}

	//template<class T>
	//bool alaPtr<T>::RefCountedObject::Is_Shareable()const
	//{
	//	return (shareable);
	//}

	//template<typename T>
	//bool alaPtr::RefCountedObject::Is_Shared()const
	//{
	//	return (refCount > 1);
	//}

	//template<class T>
	//void alaPtr::RefCountedObject::Init()
	//{
	//	refCount = 0;
	//}


}//Namespace 

#endif /*_ALAMO_REF_CNT_H_*/
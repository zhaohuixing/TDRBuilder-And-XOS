// Project: Visual System Builder
//
// File Name: tvsb_cpputil.h
//
// Description: The utility algorithm
//
// Author: Zhaohui Xing
//
// Copyright: (c) Zhaohui Xing. 2005, All rights reserved.
//
// Creation Date: 01/19/2005	
//
// History:
// 1.    01/19/2005: Create	
//
#ifndef __TVSB_CPPUTIL_H__
#define __TVSB_CPPUTIL_H__
#include <algorithm>
#include <functional>

template <class Type> class TVSB_Deletor
{
public:
	TVSB_Deletor(){};

    void operator () (Type* elem)
    {
		if(elem)
			delete elem;
    }
};

template<typename TPair>class TVSB_PairDeletor
{
public:
	TVSB_PairDeletor(){};

    void operator () (TPair& tElem)
    {
		if(tElem.second)
		{
			delete tElem.second;
			tElem.second = NULL;
		}
    }
};

// Container dellocator
template<typename TContainer, typename TDelete>class TVSB_Dealloc
{
public:
	TVSB_Dealloc(){};

	void operator()(TContainer& tc)
	{
		TDelete mdel;
		std::for_each<TContainer::iterator>(tc.begin(), tc.end(), mdel);
		tc.clear();
	}
};

template<typename TType, typename TFunc>class TVSB_PtrComparse
{
public:
	TVSB_PtrComparse(const TFunc& func, bool bAsc = true):m_fFunc(func), m_bAsc(bAsc){};

    bool operator () (TType* t1, TType* t2)
    {
		if(m_bAsc)   // Ascending sort
			return (m_fFunc(t1) <= m_fFunc(t2));
		else		 // descending sort
			return (m_fFunc(t2) < m_fFunc(t1));
    }

private:
	TFunc	m_fFunc;   // The member function object
	bool	m_bAsc;    // Sort order, true: ascending sort, false: descending sort 
};

template<typename TType, typename TFunc>class TVSB_RefComparse
{
public:
	TVSB_RefComparse(const TFunc& func, bool bAsc = true):m_fFunc(func), m_bAsc(bAsc){};

    bool operator () (const TType& t1, const TType& t2)
    {
		if(m_bAsc)   // Ascending sort
			return (m_fFunc(t1) <= m_fFunc(t2));
		else		 // descending sort
			return (m_fFunc(t2) < m_fFunc(t1));
    }

private:
	TFunc	m_fFunc;   // The member function object
	bool	m_bAsc;    // Sort order, true: ascending sort, false: descending sort 
};

template<typename TPair, typename TFunc>
class TVSB_PairFunctor
{
public:
	TVSB_PairFunctor(const TFunc& Func):m_func(Func){};

    void operator () (TPair& elem)
    {
		 m_func(elem.second);
    }

private:
	TFunc  m_func;
};

template<typename TPair, typename TFunc, typename TReturn>
class TVSB_PairRFunctor
{
public:
	TVSB_PairRFunctor(const TFunc& Func):m_func(Func){};

    TReturn operator () (TPair& elem)
    {
		 return m_func(elem.second);
    }

private:
	TFunc  m_func;
};

template<typename TClass, typename TValue, typename TFunc>class TVSB_BinaryEqualP
{
public:
	typedef TClass* first_argument_type; 
    typedef TValue second_argument_type;
	typedef bool result_type;

	TVSB_BinaryEqualP(const TFunc& func):m_Func(func){};

	// Overload the operator()
	bool operator()(TClass* tc, const TValue& tv) const
	{
		bool bRet = false;
		if(tc)
		{
			bRet = (tv == m_Func(tc));
		}
		return bRet;
	}

private:
	TFunc	m_Func;   // The member function object
};

template<typename TClass, typename TValue, typename TFunc>class TVSB_BinaryEqualR
{
public:
	typedef TClass first_argument_type; 
    typedef TValue second_argument_type;
	typedef bool result_type;

	TVSB_BinaryEqualR(const TFunc& func):m_Func(func){};

	// Overload the operator()
	bool operator()(const TClass& tc, const TValue& tv) const
	{
		bool bRet = false;
		if(tc)
		{
			bRet = (tv == m_Func(tc));
		}
		return bRet;
	}

private:
	TFunc	m_Func;   // The member function object
};

template<typename TPair, typename TValue, typename TFunc>class TVSB_PairBinaryEqual1
{
public:
	typedef TPair	first_argument_type; 
    typedef TValue	second_argument_type;
	typedef bool	result_type;

	TVSB_PairBinaryEqual1(const TFunc& func):m_Func(func){};

	// Overload the operator()
	bool operator()(TPair& tp, const TValue& tv) const
	{
		bool bRet = false;
		if(tp)
		{
			bRet = (tv == m_Func(tp.first));
		}
		return bRet;
	}

private:
	TFunc	m_Func;   // The member function object
};

template<typename TPair, typename TValue, typename TFunc>class TVSB_PairBinaryEqual2
{
public:
	typedef TPair	first_argument_type; 
    typedef TValue	second_argument_type;
	typedef bool	result_type;

	TVSB_PairBinaryEqual2(const TFunc& func):m_Func(func){};

	// Overload the operator()
	bool operator()(TPair& tp, const TValue& tv) const
	{
		bool bRet = false;
		if(tp)
		{
			bRet = (tv == m_Func(tp.second));
		}
		return bRet;
	}

private:
	TFunc	m_Func;   // The member function object
};

template<typename TPair, typename TValue>class TVSB_SimplePairEqual1
{
public:
	typedef TPair first_argument_type; 
    typedef TValue second_argument_type;
	typedef bool result_type;

	TVSB_SimplePairEqual1(){};

	// Overload the operator()
	bool operator()(TPair& tp, const TValue& tv) const
	{
		bool bRet = (tv == tp.first);
		return bRet;
	}
};

template<typename TPair, typename TValue>class TVSB_SimplePairEqual2
{
public:
	typedef TPair first_argument_type; 
    typedef TValue second_argument_type;
	typedef bool result_type;

	TVSB_SimplePairEqual2(){};

	// Overload the operator()
	bool operator()(TPair& tp, const typename TValue& tv) const
	{
		bool bRet = (tv == tp.second);
		return bRet;
	}
};

template <typename TContainer, typename TIterator, typename TValue, typename TFunc> class TVSB_Find
{
public:
	TVSB_Find(const TFunc& func): m_Func(func){};

	TIterator operator()(TContainer& tl, const TValue& tv)
	{
		TIterator   iter;
		iter = std::find_if<TIterator>(tl.begin(), tl.end(), std::bind2nd(m_Func, tv));
		return iter;
	}

	TIterator operator()(TIterator iter1, TIterator iter2, const TValue& tv)
	{
		TIterator   iter;
		iter = std::find_if<TIterator>(iter1, iter2, std::bind2nd(m_Func, tv));
		return iter;
	}

private:
	TFunc	m_Func;   // The member function object
};

#endif
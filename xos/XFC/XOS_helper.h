// Date: 06/06/2004	
#ifndef __XOS_HELPER_H__
#define __XOS_HELPER_H__

#include <algorithm>
#include <functional>
#include <string>

template <class Type> class TXOS_Deletor
{
public:
	TXOS_Deletor(){};

    void operator () (Type* elem)
    {
		if(elem)
			delete elem;
    }
};

template<typename TPair>class TXOS_PairDeletor
{
public:
	TXOS_PairDeletor(){};

    void operator () (TPair& tElem)
    {
		if(tElem.second)
		{
			delete tElem.second;
		}
    }
};

// Container dellocator
template<typename TContainer, typename TDelete>class TXOS_Dealloc
{
public:
	TXOS_Dealloc(){};

	void operator()(TContainer& tc)
	{
		TDelete mdel;
		std::for_each<TContainer::iterator>(tc.begin(), tc.end(), mdel);
		tc.clear();
	}
};

template<typename TType, typename TFunc>class TXOS_Comparsion
{
public:
	TXOS_Comparsion(const TFunc& func, bool bAsc = true):m_fFunc(func), m_bAsc(bAsc){};

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

class CXOS_WStrCmp
{
public:
	CXOS_WStrCmp(){};
	
	// Overload the operator()
	bool operator() (const wchar_t* str1, const wchar_t* str2) const
	{
        return (wcscmp(str1, str2) < 0 ? true : false);
	}
};

class CXOS_WStrIdentical
{
public:
	CXOS_WStrIdentical(){};

	// Overload the operator()
	bool operator() (const wchar_t* str1, const wchar_t* str2) const
	{
        return (wcscmp(str1, str2) == 0 ? true : false);
	}
};

#endif
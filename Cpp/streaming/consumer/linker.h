#ifndef __LINKER_H
#define __LINKER_H

#include "adaptor.h"

template<typename UT, typename T>
class LinkedConsumer: public Consumer<T>
{
public:
	template<typename DT>
	LinkedConsumer<T, DT>* Pipe(Adaptor<T, DT>* ipAdaptor)
	{
		return new LinkedConsumer<T, DT>(this, ipAdaptor);
	}

private:
	Consumer<UT>* mpUpstream;
	Adaptor<UT, T>* mpAdaptor;
};


#endif
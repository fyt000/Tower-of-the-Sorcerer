#include "LabelBinder.h"

USING_NS_CC;

template<class T>
LabelBinder<T>::LabelBinder(T val):value(val),theLabel(NULL)
{
}

template<class T>
LabelBinder<T>::LabelBinder(T val,Label * label):value(val),theLabel(label)
{
}

template<class T>
void LabelBinder<T>::attach(Label * label)
{
	theLabel=label;
	notify();
}

template<class T>
void LabelBinder<T>::setVal(T newVal)
{
	value=newVal;
	notify();
}

template<class T>
void LabelBinder<T>::addVal(T v)
{
	value+=v;
	notify();
}

template<class T>
void LabelBinder<T>::subVal(T v)
{
	value-=v;
	notify();
}

template<class T>
void LabelBinder<T>::notify()
{
	if (doNotify&&theLabel!=NULL)
		theLabel->setString(ToString(value));
}

template<class T>
void LabelBinder<T>::setNofify(bool b)
{
	doNotify=b;
}

template<class T>
T LabelBinder<T>::V()
{
	return value;
}



template class LabelBinder<int>; //Explicit instantiation
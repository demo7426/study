#include "Publisher.h"
#include "Observer.h"

int CAbstractPublisher::AddObserver(CAbstractObserver* _pAbstractObserver)
{
	for (const auto& item : m_listObserver)
	{
		if (item == _pAbstractObserver)
			return -1;
	}

	m_listObserver.push_back(_pAbstractObserver);
	return 0;
}

int CAbstractPublisher::RemoveObserver(CAbstractObserver* _pAbstractObserver)
{
	m_listObserver.remove(_pAbstractObserver);
	return 0;
}

int CGossipPublisher::Notify(string _Msg) const
{
	cout << "GossipPublisher have " << m_listObserver.size() << " observers." << endl;
	for (const auto& item : m_listObserver)
	{
		item->Updata(_Msg);
	}
	return 0;
}

int COfficialPublisher::Notify(string _Msg) const
{
	cout << "OfficialPublisher have " << m_listObserver.size() << " observers." << endl;
	for (const auto& item : m_listObserver)
	{
		item->Updata(_Msg);
	}
	return 0;
}

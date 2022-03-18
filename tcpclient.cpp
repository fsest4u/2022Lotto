#include <QFile>
#include <QImage>

#include "tcpclient.h"

#include "log.h"

#define CONTENT_TYPE			"application/x-www-form-urlencoded"

TCPClient::TCPClient(QObject *parent)
	: QObject(parent)
	, m_pManager(new QNetworkAccessManager)
{
}

TCPClient::~TCPClient()
{

	if (m_pManager) {
		delete m_pManager;
		m_pManager = nullptr;
	}
}

void TCPClient::RequestWebPage(QString fullpath)
{
	QEventLoop loop;

	const QUrl url = QUrl::fromUserInput(fullpath);
	QNetworkRequest request;

	request.setUrl(url);

	m_pReply = m_pManager->get(request);

	connect(m_pReply, SIGNAL(finished()), &loop, SLOT(quit()));

	loop.exec();

	if (m_pReply->error() == QNetworkReply::NoError)
	{
		QString html = m_pReply->readAll();
		emit SigRespWebPage(html);
	}
	else
	{
		QString err = m_pReply->errorString();
		LogCritical("Network Error : [%s] fullPath [%s]"
					, err.toUtf8().data()
					, fullpath.toUtf8().data());
	}

	if (m_pReply)
	{
		delete m_pReply;
		m_pReply = nullptr;
	}
}

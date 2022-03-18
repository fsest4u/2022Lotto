#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QtNetwork>

class TCPClient : public QObject
{
	Q_OBJECT
public:
	explicit TCPClient(QObject *parent = nullptr);
	~TCPClient();

	void		RequestWebPage(QString fullpath);

signals :

	void		SigRespWebPage(QString html);

public slots :


private :

	QNetworkAccessManager		*m_pManager;
	QNetworkReply               *m_pReply;

	QString						m_Addr;


};

#endif // TCPCLIENT_H

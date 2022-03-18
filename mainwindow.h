#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QRandomGenerator>

class TCPClient;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:

	void SlotBtnReference();
	void SlotBtnClear();
	void SlotBtnGenerate();

	void SlotRespWebPage(QString html);

private:

	void ConnectSigToSlot();
	void Initialize();

	void ClearMapData();
	void ClearInputNumber();
	void ClearOutputNumber();

	void ReadInputNumber();
	void SetValidate();

	void InputNumber();
	void OutputNumber();

	QMap<int, bool> mapNumber;
	QMap<int, QString> mapGame;

	QRandomGenerator *gererator;

	TCPClient	*m_pTcpClient;

	Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

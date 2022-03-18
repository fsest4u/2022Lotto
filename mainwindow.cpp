#include <QIntValidator>
#include <QDesktopServices>
#include <QUrl>
//#include <QtTest/QTest>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "log.h"
#include "tcpclient.h"

//QTEST_MAIN(MainWindow)
//#include "MainWindow.moc"

#define	MIN_NUMBER			1
#define	MAX_NUMBER			45
#define GAME_NUMBER			6
#define GAME_COUNT			5

#define LOTTO_URL			"https://animalface.site/lotto.html"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	m_pTcpClient(new TCPClient(this)),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ConnectSigToSlot();
	Initialize();
}

MainWindow::~MainWindow()
{
	if (m_pTcpClient)
	{
		delete m_pTcpClient;
		m_pTcpClient = nullptr;
	}

	delete ui;
}

void MainWindow::SlotBtnReference()
{
	QDesktopServices::openUrl(QUrl(LOTTO_URL));
}

void MainWindow::SlotBtnClear()
{
	ClearMapData();
	ClearInputNumber();
	ClearOutputNumber();
}

void MainWindow::SlotBtnGenerate()
{
	InputNumber();
	OutputNumber();
}

void MainWindow::SlotRespWebPage(QString html)
{
	LogDebug("html [%s]", html.toUtf8().data());
	int start = html.indexOf("<section class=\"container mt-4 mb-5 d-flex flex-column align-items-center justify-content-center\">");
	int end = html.indexOf("</section>", start);

	QStringRef subHtml(&html, start, end - start);
	LogDebug("subHtml [%s]", subHtml.toUtf8().data());
	start = subHtml.indexOf("<li class=\"text-center\">");
	end = subHtml.lastIndexOf("</li>");

	html = subHtml.toString();
	QStringRef liHtml(&html, start, end - start);
	LogDebug("liHtml [%s]", liHtml.toUtf8().data());

	html = liHtml.toString();
	html.replace("<li class=\"text-center\">", "").replace("\n", "").replace("[", "").replace("]", "");
	QStringList arrGame = html.split("</li>");
	for (int i = 0; i < arrGame.count(); i++)
	{
		LogDebug("index [%d] list [%s]", i, arrGame.at(i).trimmed().toUtf8().data());
		mapGame.insert(i, arrGame.at(i).trimmed());
	}
}

void MainWindow::ConnectSigToSlot()
{
	connect(ui->btnRef, SIGNAL(clicked()), this, SLOT(SlotBtnReference()));
	connect(ui->btnClear, SIGNAL(clicked()), this, SLOT(SlotBtnClear()));
	connect(ui->btnGenerate, SIGNAL(clicked()), this, SLOT(SlotBtnGenerate()));

	connect((QObject*)m_pTcpClient, SIGNAL(SigRespWebPage(QString)), this, SLOT(SlotRespWebPage(QString)));

}

void MainWindow::Initialize()
{
	ReadInputNumber();
	SetValidate();

	ClearMapData();
	ClearInputNumber();
	ClearOutputNumber();

	gererator = QRandomGenerator::global();
}

void MainWindow::ClearMapData()
{
	for(int i = 0; i < MAX_NUMBER; i++)
	{
		mapNumber.insert(i, false);
	}
}

void MainWindow::ClearInputNumber()
{
	QStringList arrNumber;

	arrNumber =	mapGame.value(0).split(',');

	ui->lineEdit_1_1->setText(arrNumber[0]);
	ui->lineEdit_1_2->setText(arrNumber[1]);
	ui->lineEdit_1_3->setText(arrNumber[2]);
	ui->lineEdit_1_4->setText(arrNumber[3]);
	ui->lineEdit_1_5->setText(arrNumber[4]);
	ui->lineEdit_1_6->setText(arrNumber[5]);

	arrNumber =	mapGame.value(1).split(',');

	ui->lineEdit_2_1->setText(arrNumber[0]);
	ui->lineEdit_2_2->setText(arrNumber[1]);
	ui->lineEdit_2_3->setText(arrNumber[2]);
	ui->lineEdit_2_4->setText(arrNumber[3]);
	ui->lineEdit_2_5->setText(arrNumber[4]);
	ui->lineEdit_2_6->setText(arrNumber[5]);

	arrNumber =	mapGame.value(2).split(',');

	ui->lineEdit_3_1->setText(arrNumber[0]);
	ui->lineEdit_3_2->setText(arrNumber[1]);
	ui->lineEdit_3_3->setText(arrNumber[2]);
	ui->lineEdit_3_4->setText(arrNumber[3]);
	ui->lineEdit_3_5->setText(arrNumber[4]);
	ui->lineEdit_3_6->setText(arrNumber[5]);

	arrNumber =	mapGame.value(3).split(',');

	ui->lineEdit_4_1->setText(arrNumber[0]);
	ui->lineEdit_4_2->setText(arrNumber[1]);
	ui->lineEdit_4_3->setText(arrNumber[2]);
	ui->lineEdit_4_4->setText(arrNumber[3]);
	ui->lineEdit_4_5->setText(arrNumber[4]);
	ui->lineEdit_4_6->setText(arrNumber[5]);

	arrNumber =	mapGame.value(4).split(',');

	ui->lineEdit_5_1->setText(arrNumber[0]);
	ui->lineEdit_5_2->setText(arrNumber[1]);
	ui->lineEdit_5_3->setText(arrNumber[2]);
	ui->lineEdit_5_4->setText(arrNumber[3]);
	ui->lineEdit_5_5->setText(arrNumber[4]);
	ui->lineEdit_5_6->setText(arrNumber[5]);

	arrNumber =	mapGame.value(5).split(',');

	ui->lineEdit_6_1->setText(arrNumber[0]);
	ui->lineEdit_6_2->setText(arrNumber[1]);
	ui->lineEdit_6_3->setText(arrNumber[2]);
	ui->lineEdit_6_4->setText(arrNumber[3]);
	ui->lineEdit_6_5->setText(arrNumber[4]);
	ui->lineEdit_6_6->setText(arrNumber[5]);

	arrNumber =	mapGame.value(6).split(',');

	ui->lineEdit_7_1->setText(arrNumber[0]);
	ui->lineEdit_7_2->setText(arrNumber[1]);
	ui->lineEdit_7_3->setText(arrNumber[2]);
	ui->lineEdit_7_4->setText(arrNumber[3]);
	ui->lineEdit_7_5->setText(arrNumber[4]);
	ui->lineEdit_7_6->setText(arrNumber[5]);

	arrNumber =	mapGame.value(7).split(',');

	ui->lineEdit_8_1->setText(arrNumber[0]);
	ui->lineEdit_8_2->setText(arrNumber[1]);
	ui->lineEdit_8_3->setText(arrNumber[2]);
	ui->lineEdit_8_4->setText(arrNumber[3]);
	ui->lineEdit_8_5->setText(arrNumber[4]);
	ui->lineEdit_8_6->setText(arrNumber[5]);

	arrNumber =	mapGame.value(8).split(',');

	ui->lineEdit_9_1->setText(arrNumber[0]);
	ui->lineEdit_9_2->setText(arrNumber[1]);
	ui->lineEdit_9_3->setText(arrNumber[2]);
	ui->lineEdit_9_4->setText(arrNumber[3]);
	ui->lineEdit_9_5->setText(arrNumber[4]);
	ui->lineEdit_9_6->setText(arrNumber[5]);

	arrNumber =	mapGame.value(9).split(',');

	ui->lineEdit_10_1->setText(arrNumber[0]);
	ui->lineEdit_10_2->setText(arrNumber[1]);
	ui->lineEdit_10_3->setText(arrNumber[2]);
	ui->lineEdit_10_4->setText(arrNumber[3]);
	ui->lineEdit_10_5->setText(arrNumber[4]);
	ui->lineEdit_10_6->setText(arrNumber[5]);
}

void MainWindow::ClearOutputNumber()
{
	ui->label_1_1->setText("-");
	ui->label_1_2->setText("-");
	ui->label_1_3->setText("-");
	ui->label_1_4->setText("-");
	ui->label_1_5->setText("-");
	ui->label_1_6->setText("-");

	ui->label_2_1->setText("-");
	ui->label_2_2->setText("-");
	ui->label_2_3->setText("-");
	ui->label_2_4->setText("-");
	ui->label_2_5->setText("-");
	ui->label_2_6->setText("-");

	ui->label_3_1->setText("-");
	ui->label_3_2->setText("-");
	ui->label_3_3->setText("-");
	ui->label_3_4->setText("-");
	ui->label_3_5->setText("-");
	ui->label_3_6->setText("-");

	ui->label_4_1->setText("-");
	ui->label_4_2->setText("-");
	ui->label_4_3->setText("-");
	ui->label_4_4->setText("-");
	ui->label_4_5->setText("-");
	ui->label_4_6->setText("-");

	ui->label_5_1->setText("-");
	ui->label_5_2->setText("-");
	ui->label_5_3->setText("-");
	ui->label_5_4->setText("-");
	ui->label_5_5->setText("-");
	ui->label_5_6->setText("-");

//	QVERIFY(ui->label_1_1->text() == "-");
//	QCOMPARE(ui->label_1_1->text(), QString("-"));

}

void MainWindow::ReadInputNumber()
{
	m_pTcpClient->RequestWebPage(LOTTO_URL);
}


void MainWindow::SetValidate()
{
	QIntValidator *validator = new QIntValidator(1, 45, this);

	ui->lineEdit_1_1->setValidator(validator);
	ui->lineEdit_1_2->setValidator(validator);
	ui->lineEdit_1_3->setValidator(validator);
	ui->lineEdit_1_4->setValidator(validator);
	ui->lineEdit_1_5->setValidator(validator);
	ui->lineEdit_1_6->setValidator(validator);

	ui->lineEdit_2_1->setValidator(validator);
	ui->lineEdit_2_2->setValidator(validator);
	ui->lineEdit_2_3->setValidator(validator);
	ui->lineEdit_2_4->setValidator(validator);
	ui->lineEdit_2_5->setValidator(validator);
	ui->lineEdit_2_6->setValidator(validator);

	ui->lineEdit_3_1->setValidator(validator);
	ui->lineEdit_3_2->setValidator(validator);
	ui->lineEdit_3_3->setValidator(validator);
	ui->lineEdit_3_4->setValidator(validator);
	ui->lineEdit_3_5->setValidator(validator);
	ui->lineEdit_3_6->setValidator(validator);

	ui->lineEdit_4_1->setValidator(validator);
	ui->lineEdit_4_2->setValidator(validator);
	ui->lineEdit_4_3->setValidator(validator);
	ui->lineEdit_4_4->setValidator(validator);
	ui->lineEdit_4_5->setValidator(validator);
	ui->lineEdit_4_6->setValidator(validator);

	ui->lineEdit_5_1->setValidator(validator);
	ui->lineEdit_5_2->setValidator(validator);
	ui->lineEdit_5_3->setValidator(validator);
	ui->lineEdit_5_4->setValidator(validator);
	ui->lineEdit_5_5->setValidator(validator);
	ui->lineEdit_5_6->setValidator(validator);

	ui->lineEdit_6_1->setValidator(validator);
	ui->lineEdit_6_2->setValidator(validator);
	ui->lineEdit_6_3->setValidator(validator);
	ui->lineEdit_6_4->setValidator(validator);
	ui->lineEdit_6_5->setValidator(validator);
	ui->lineEdit_6_6->setValidator(validator);

	ui->lineEdit_7_1->setValidator(validator);
	ui->lineEdit_7_2->setValidator(validator);
	ui->lineEdit_7_3->setValidator(validator);
	ui->lineEdit_7_4->setValidator(validator);
	ui->lineEdit_7_5->setValidator(validator);
	ui->lineEdit_7_6->setValidator(validator);

	ui->lineEdit_8_1->setValidator(validator);
	ui->lineEdit_8_2->setValidator(validator);
	ui->lineEdit_8_3->setValidator(validator);
	ui->lineEdit_8_4->setValidator(validator);
	ui->lineEdit_8_5->setValidator(validator);
	ui->lineEdit_8_6->setValidator(validator);

	ui->lineEdit_9_1->setValidator(validator);
	ui->lineEdit_9_2->setValidator(validator);
	ui->lineEdit_9_3->setValidator(validator);
	ui->lineEdit_9_4->setValidator(validator);
	ui->lineEdit_9_5->setValidator(validator);
	ui->lineEdit_9_6->setValidator(validator);

	ui->lineEdit_10_1->setValidator(validator);
	ui->lineEdit_10_2->setValidator(validator);
	ui->lineEdit_10_3->setValidator(validator);
	ui->lineEdit_10_4->setValidator(validator);
	ui->lineEdit_10_5->setValidator(validator);
	ui->lineEdit_10_6->setValidator(validator);
}

void MainWindow::InputNumber()
{
	mapNumber.insert(ui->lineEdit_1_1->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_1_2->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_1_3->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_1_4->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_1_5->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_1_6->text().toInt(), true);

	mapNumber.insert(ui->lineEdit_2_1->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_2_2->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_2_3->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_2_4->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_2_5->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_2_6->text().toInt(), true);

	mapNumber.insert(ui->lineEdit_3_1->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_3_2->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_3_3->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_3_4->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_3_5->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_3_6->text().toInt(), true);

	mapNumber.insert(ui->lineEdit_4_1->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_4_2->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_4_3->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_4_4->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_4_5->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_4_6->text().toInt(), true);

	mapNumber.insert(ui->lineEdit_5_1->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_5_2->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_5_3->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_5_4->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_5_5->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_5_6->text().toInt(), true);

	mapNumber.insert(ui->lineEdit_6_1->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_6_2->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_6_3->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_6_4->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_6_5->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_6_6->text().toInt(), true);

	mapNumber.insert(ui->lineEdit_7_1->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_7_2->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_7_3->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_7_4->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_7_5->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_7_6->text().toInt(), true);

	mapNumber.insert(ui->lineEdit_8_1->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_8_2->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_8_3->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_8_4->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_8_5->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_8_6->text().toInt(), true);

	mapNumber.insert(ui->lineEdit_9_1->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_9_2->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_9_3->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_9_4->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_9_5->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_9_6->text().toInt(), true);

	mapNumber.insert(ui->lineEdit_10_1->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_10_2->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_10_3->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_10_4->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_10_5->text().toInt(), true);
	mapNumber.insert(ui->lineEdit_10_6->text().toInt(), true);

	QMap<int, bool>::iterator i;
	for (i = mapNumber.begin(); i != mapNumber.end(); i++)
	{
		LogDebug("key [%d] value [%d]", i.key(), i.value());
	}

}

void MainWindow::OutputNumber()
{
	// generate
	QMap<int, QMap<int, bool>> mapOutput;
	QMap<int, bool> mapGame;

	for (int i = 0; i < GAME_COUNT; i++)
	{
		LogDebug("========");
		mapGame.clear();
		while (mapGame.count() < GAME_NUMBER)
		{
			int lucky = gererator->bounded(MIN_NUMBER, MAX_NUMBER);
			if (mapNumber.find(lucky).value())
			{
				LogDebug("find [%d]", lucky);
				mapGame.insert(lucky, true);
			}
		}
		mapOutput.insert(i, mapGame);
	}

	// make
	QMap<int, QMap<int, bool>>::iterator output;
	for (output = mapOutput.begin(); output != mapOutput.end(); output++)
	{
		mapGame.clear();
		mapGame = output.value();

		QMap<int, bool>::iterator game;
		for (game = mapGame.begin(); game != mapGame.end(); game++)
		{
			LogDebug("output key [%d] game key [%d] value [%d]", output.key(), game.key(), game.value());
		}

		QList<int> keys = mapGame.keys();

		if (output.key() == 0)
		{
			ui->label_1_1->setText(QString::number(keys.at(0)));
			ui->label_1_2->setText(QString::number(keys.at(1)));
			ui->label_1_3->setText(QString::number(keys.at(2)));
			ui->label_1_4->setText(QString::number(keys.at(3)));
			ui->label_1_5->setText(QString::number(keys.at(4)));
			ui->label_1_6->setText(QString::number(keys.at(5)));
		}
		else if (output.key() == 1)
		{
			ui->label_2_1->setText(QString::number(keys.at(0)));
			ui->label_2_2->setText(QString::number(keys.at(1)));
			ui->label_2_3->setText(QString::number(keys.at(2)));
			ui->label_2_4->setText(QString::number(keys.at(3)));
			ui->label_2_5->setText(QString::number(keys.at(4)));
			ui->label_2_6->setText(QString::number(keys.at(5)));
		}
		else if (output.key() == 2)
		{
			ui->label_3_1->setText(QString::number(keys.at(0)));
			ui->label_3_2->setText(QString::number(keys.at(1)));
			ui->label_3_3->setText(QString::number(keys.at(2)));
			ui->label_3_4->setText(QString::number(keys.at(3)));
			ui->label_3_5->setText(QString::number(keys.at(4)));
			ui->label_3_6->setText(QString::number(keys.at(5)));
		}
		else if (output.key() == 3)
		{
			ui->label_4_1->setText(QString::number(keys.at(0)));
			ui->label_4_2->setText(QString::number(keys.at(1)));
			ui->label_4_3->setText(QString::number(keys.at(2)));
			ui->label_4_4->setText(QString::number(keys.at(3)));
			ui->label_4_5->setText(QString::number(keys.at(4)));
			ui->label_4_6->setText(QString::number(keys.at(5)));
		}
		else if (output.key() == 4)
		{
			ui->label_5_1->setText(QString::number(keys.at(0)));
			ui->label_5_2->setText(QString::number(keys.at(1)));
			ui->label_5_3->setText(QString::number(keys.at(2)));
			ui->label_5_4->setText(QString::number(keys.at(3)));
			ui->label_5_5->setText(QString::number(keys.at(4)));
			ui->label_5_6->setText(QString::number(keys.at(5)));
		}
	}
}


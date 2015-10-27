#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <longscroll-qt/contentwidget.h>
#include <longscroll-qt/contentwidgetitemfactory.h>
#include "itemfactories.h"

MainWindow::MainWindow(int demoNr, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	QVBoxLayout * layout = new QVBoxLayout();
	layout->setMargin(0);
	ui->scrollAreaWidgetContents->setLayout(layout);

	ContentWidget * cw;
	ContentWidgetItemFactory * cwif = 0;
	switch (demoNr)
	{
		default:
		case 0:
			cw = new ContentWidget();
			cwif = new ContentWidgetLoaderImageItemFactory(false);
			break;
		case 1:
			cw = new ContentWidget(100, 100, false, false, false, 200);
			cwif = new ContentWidgetLoaderImageItemFactory(true);
			break;
		case 2:
			cw = new ContentWidget(100, -1, true, true, false, 200);
			cwif = new ContentWidgetLoaderImageItemFactory(true);
			break;
		case 3:
			cw = new ContentWidget(100, 200, false, false, false, 200);
			cwif = new ContentWidgetImageInfoFactory();
			break;
	}
	if (cwif != 0)
		cw->setItemFactory(cwif);

	layout->addWidget(cw);
	connect(cw, SIGNAL(scrollToRequest(int,int)), ui->scrollArea, SLOT(scrollTo(int,int)));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::setItemInfos(const QList<ContentItemInfo> & infos)
{
	ContentWidget * test = ui->scrollAreaWidgetContents->findChild<ContentWidget *>();
	test->setItemInfos(infos);
}

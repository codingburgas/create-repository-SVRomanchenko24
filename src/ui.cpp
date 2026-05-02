#include "../include/ui.h"
#include "../include/quiz.h"
#include "../include/utils.h"
#include <cstdint>
#include <iostream>
#include <string>

void mainWindow::onItemSetup(const Glib::RefPtr<Gtk::ListItem>& listItem)
{
	listItem->set_child(*Gtk::make_managed<Gtk::Label>(""));
}

void mainWindow::onItemBind(const Glib::RefPtr<Gtk::ListItem>& listItem)
{
	auto position = listItem->get_position();
	if (position==GTK_INVALID_LIST_POSITION) return;
	((Gtk::Label*)listItem->get_child())->set_label(quizStrings->get_string(position));
}

void mainWindow::initQuiz()
{
	id = selectionModel->get_selected();
	current = 0;
	correct = 0;
	total = getTotalQuestions(id);
	updateContents();

	set_child(textButtonSplit);
}

void mainWindow::showMainMenu()
{
	id = 0;
	set_child(box);
}

void mainWindow::updateContents()
{
	if (total==current)
	{
		std::cout << correct;
		showMainMenu(); // TODO show result screen
		return;
	}
	
	char *questionText, *optionsText[4];
	correctOption = getQuizQuestionContent(id, current, questionText, optionsText);

	progress.set_label(getProgressString(current, total));

	// set question
	question.set_label(questionText);
	delete questionText;

	// set button text
	for (int i = 0; i<4; ++i)
	{
		options[i].set_label(optionsText[i]);
		delete optionsText[i];
	}
}

void mainWindow::handleInput(uint8_t button)
{
	++current;
	if (button==correctOption) ++correct;
	updateContents();
}

void mainWindow::handleButton1()
{
	handleInput(0);
}

void mainWindow::handleButton2()
{
	handleInput(1);
}

void mainWindow::handleButton3()
{
	handleInput(2);
}

void mainWindow::handleButton4()
{
	handleInput(3);
}

mainWindow::mainWindow() : startQuiz("Start quiz"), box(Gtk::Orientation::VERTICAL)
{
	// MAIN WINDOW

	// layout
	listScroll.set_child(quizList);
	box.append(listScroll);
	box.append(startQuiz);
	set_child(box);

	startQuiz.signal_clicked().connect(sigc::mem_fun(*this, &mainWindow::initQuiz));

	// list
	
	quizStrings = Gtk::StringList::create(getQuizNameList());
	selectionModel = Gtk::SingleSelection::create(quizStrings);
	selectionModel->set_autoselect(true);
	quizList.set_model(selectionModel);
	
	auto factory = Gtk::SignalListItemFactory::create();
	factory->signal_setup().connect(sigc::mem_fun(*this, &mainWindow::onItemSetup));
	factory->signal_bind().connect(sigc::mem_fun(*this, &mainWindow::onItemBind));	
	quizList.set_factory(factory);

	// content
	set_title("Main Menu");

	// QUIZ WINDOW
	
	// layout
	textButtonSplit = Gtk::Box(Gtk::Orientation::VERTICAL, 5);
	textButtonSplit.append(progress);
	progress.set_margin(15);
	textButtonSplit.append(question);
	question.set_margin(15);
	textButtonSplit.append(buttonGrid);
	for (int i = 0; i<4; ++i)
	{
		buttonGrid.attach(options[i], i/2, i%2);
		options[i].set_margin(15);
	}

	set_resizable(false);

	// click handlers
	options[0].signal_clicked().connect(sigc::mem_fun(*this, &mainWindow::handleButton1));
	options[1].signal_clicked().connect(sigc::mem_fun(*this, &mainWindow::handleButton2));
	options[2].signal_clicked().connect(sigc::mem_fun(*this, &mainWindow::handleButton3));
	options[3].signal_clicked().connect(sigc::mem_fun(*this, &mainWindow::handleButton4));

	// quiz parameter setup
}

mainWindow::~mainWindow()
{
	cleanUpQuizData();
}

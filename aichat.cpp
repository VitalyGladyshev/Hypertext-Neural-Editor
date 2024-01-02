#include "aichat.h"
#include "ui_aichat.h"

AIChat::AIChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AIChat),
    _currentLLM(AIModels::GigaChat)
{
    ui->setupUi(this);
}

AIChat::~AIChat()
{
    delete ui;
}

// Задать текст клавиши "Настройки" для перевода
void AIChat::SetPropertiesButtonText(const QString buttonText)
{
    ui->pushButtonProperties->setText(buttonText);
}

// Задать текст клавиши "Отправить" для перевода
void AIChat::SetSendButtonText(const QString buttonText)
{
    ui->pushButtonSend->setText(buttonText);
}

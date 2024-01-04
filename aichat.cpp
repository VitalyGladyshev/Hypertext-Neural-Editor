#include "aichat.h"
#include "ui_aichat.h"
#include "settings.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

AIChat::AIChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AIChat),
    _currentLLM(AIModels::GigaChat)
{
    ui->setupUi(this);

    _pNetworkInterface = new QNetworkAccessManager(this);

    connect(ui->pushButtonProperties, SIGNAL(clicked(bool)),
            this, SLOT(SlotPropertiesButtonClicked()));
    connect(ui->pushButtonSend, SIGNAL(clicked(bool)),
            this, SLOT(SlotSendButtonClicked()));
    connect(_pNetworkInterface, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(SlotReceptionFinished(QNetworkReply*)));
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

// Слот на клик клавиши "Настройки"
void AIChat::SlotPropertiesButtonClicked()
{
    qDebug() << "PropertiesButtonClicked";
}

// Слот на клик клавиши "Отправить"
void AIChat::SlotSendButtonClicked()
{
    qDebug() << "SendButtonClicked";

//    const QUrl authUrlAuth { "https://ngw.devices.sberbank.ru:9443/api/v2/oauth" };
//    const QString authorization { "Bearer " + Settings::GetInstance().GetGigaChatAuthorization() };
//    const QString payload { "scope=GIGACHAT_API_PERS" };
//    qDebug() << authorization;

//    QNetworkRequest request(authUrlAuth);

//    request.setRawHeader("RqUID", "6f0b1291-c7f3-43c6-bb2e-9f3efb2dc98e");
//    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
//    request.setRawHeader("Authorization", authorization.toLocal8Bit());

//    _pNetworkInterface->post(request, payload.toLocal8Bit());

//    const QUrl authUrl { "https://gigachat.devices.sberbank.ru/api/v1/models" };
    const QString token { "Bearer eyJjdHkiOiJqd3QiLCJlbmMiOiJBMjU2Q0JDLUhTNTEyIiwiYWxnIjoiUlNBLU9BRVAtMjU2In0.bn21ptxGhtoEDa81ys13-jYr4O52m4LwMAFBdMVd5kqiAu_2ZAPLA2fEEoB9x6BJ2aSOPxly0xe3LeX6DYd-AXO6t58cgxAopW1mop6MpmLcgC048KJRyfyHiP7ney0DeS2Z06ScmVGLohc_r6EQXtFRSrTxH_8-rX3tFbcd8HJwuJsQrNEVJxRwhBJNT6RDI3t6ja2GYvW-UyizWabldtl3xNzYpKt9Nf5JpIrxd6m4C_RuF7jybhZrFD3zgw-IHNpGWTdc7boeVhU1XSo8Zptz8iD__W_Fvd51-McLIRSD6tp5XSOVQEprz34jP7ZN-12iKQM_fYqs16NeJ9Oj-Q.2ilLvXRpdMbyJWwnLtBDFQ.zPbQmpoCWJaesEibsFUaGovyCuTd5J4xyWgZvrmRtX9OpenhPy7Yr0mI45NAMvypnu-oJht5iE-ep9MReIHYmZmxon7cMZSzehNAiNOp5BR30sZ0hqwAZWnk5XZFverFB_EqEZv-I06W1Eaabv2CaUaSGdVxUM3K1ZN8TV5XW5Ee0zLB9XqVmCDgeM-_tp_O9PUMr-ZBrk3QTV30eClnbolDNSJXekKbwublPz9tQJcBSSFlmsBim9Lf4ce-xehr9fw0bdOy-og8NBjPxkrYMgY0Hkec3c0IJOfJ2DpHc7gwTE0PWcUCknQ33pdCmO1dA2ZAxyvEBlCNGVgrUlyHkjKsMRMq02ZBjrElTwShDtAdgQ5KkwuijqVpKoh2z7OdWE5m-Mkt6eJvBCokjaxF--IGvC6g25LmC4PXLNXqjpeaiTcL93T750gY4aB5Z03NEAh2I2aeEq0v3RJ-AP0wyryKFZHnu4WbnjESMUUYosxC4jk8EqB-PtwnCYo78GYxbN9G9zE23Gmw4o4DuVKAj_giNq0xsm1SnRDmmc893KDQS7k1zvRmvvr2Q3LeY7xDYeLsOwkRnh6dnFef_3g7XQpfIG0h1SgAimvpvBEd_debRAGDExrH7uXjlh_WO8lNdJ9BwHAkVOENjJb5TU0dCSokbWTFMcYJg6yXiWDod_gOjO17f1dMxlkR2RLw269am0PdAimVjRMGd4glXtpB-8BEMC5O7LkoU1Qkx6l5Rwo.EtgFzHGL9OuolsefauyOtu2aji6xVnhPHuzwxGdJegc" };
//    QNetworkRequest requestList(authUrl);
//    requestList.setRawHeader("Authorization", token.toLocal8Bit());

//    _pNetworkInterface->get(requestList);

    const QUrl authUrlCompletion { QString("https://gigachat.devices.sberbank.ru/api/v1") + "/chat/completions"};
    QJsonObject dataForMessage
    {
        {"model", "GigaChat:latest"},
        {"temperature", 0.87},
        {"top_p", 0.47},
        {"n", 1},
        {"max_tokens", 512},
        {"repetition_penalty", 1.07},
        {"stream", false},
        {"update_interval", 0},
    };
    QJsonObject systemMessage
    {
        {"role", "system"},
        {"content", "Отвечай как научный сотрудник"}
    };
    QJsonObject userMessage
    {
        {"role", "user"},
        {"content", "Напиши 5 вариантов названий для космической станции"}
    };
    QJsonArray messages;
    messages.append(systemMessage);
    messages.append(userMessage);
    dataForMessage["messages"] = messages;

    QJsonDocument jsonDocument(dataForMessage);

    qDebug() << jsonDocument.toJson(QJsonDocument::Compact);

    QNetworkRequest requestCompletion(authUrlCompletion);
    requestCompletion.setRawHeader("Content-Type", "application/json");
    requestCompletion.setRawHeader("Authorization", token.toLocal8Bit());

    _pNetworkInterface->post(requestCompletion, jsonDocument.toJson(QJsonDocument::Compact));
}

// Слот на окончание передачи
void AIChat::SlotReceptionFinished(QNetworkReply* pReply)
{
    if (pReply->error() != QNetworkReply::NoError)
    {
        qDebug() << "ReceptionFinished error!";

        qDebug() << pReply->rawHeaderList();
        qDebug() << pReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        qDebug() << pReply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        qDebug() << pReply->errorString() << pReply->error();
    }
    else
    {
        qDebug() << "ReceptionFinished";
        ui->textEditChat->append("ReceptionFinished");
    }

    auto replyData = pReply->readAll();
    ui->textEditChat->append(QString(replyData));
    qDebug() << replyData;

    pReply->deleteLater();
}
